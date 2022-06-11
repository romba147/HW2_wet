//
// Created by Omer Meushar on 11/06/2022.
//

#include "EmployeeManager2.h"

Company *EmployeeManager::getCompany(int n)
{
    int to_return = 0;
    if (n== 0)
    {
        return this->companyArray[0];
    }
    if (n > this->size)
    {
        return nullptr;
    }
    to_return = this->companyUF->find(n);
    return  this->companyArray[to_return];
}

Employee *EmployeeManager::getEmployee(int id)
{
    auto* newEmployee = new Employee(id,0,0,0);
    auto* checkIfHere = companyArray[0]->findEmployee(newEmployee);
    if (checkIfHere == nullptr)
    {
        delete newEmployee;
        return nullptr;
    }
    delete newEmployee;
    Employee* data = checkIfHere;
    return data;
}

StatusType EmployeeManager::AddEmployee(int employeeID, int companyID, int grade)
{
    if (employeeID<=0 || companyID <=0 || companyID > size || grade < 0)
    {
        return INVALID_INPUT;
    }
    if (getEmployee(employeeID))
    {
        return FAILURE;
    }

    Employee* newEmployee = new Employee(employeeID,0,grade,companyID);
    companyArray[0]->addEmployee(newEmployee);
    getCompany(companyID)->addEmployee(newEmployee);

    return SUCCESS;

}

StatusType EmployeeManager::RemoveEmployee(int employeeID)
{
    if (employeeID <= 0)
    {
        return INVALID_INPUT;
    }

    Employee* toRemoveEmp = getEmployee(employeeID);
    if(toRemoveEmp== nullptr)
    {
        return FAILURE;
    }

    companyArray[0]->removeEmployee(toRemoveEmp);
    companyArray[toRemoveEmp->getCompany()]->removeEmployee(toRemoveEmp);

    return SUCCESS;
}

StatusType EmployeeManager::PromoteEmployee(int employeeID, int bumpGrade)
{
    if (employeeID <=0)
    {
        return INVALID_INPUT;
    }
    Employee* req_employee = getEmployee(employeeID);
    if (req_employee == nullptr)
    {
        return FAILURE;
    }
    req_employee->BumpGrade(bumpGrade);
    companyArray[req_employee->getCompany()]->employeeGradeWasChanged(req_employee, bumpGrade);
    return SUCCESS;

}

StatusType EmployeeManager::EmployeeSalaryIncrease(int employeeID, int salaryIncrease)
{
    if (employeeID <=0)
    {
        return INVALID_INPUT;
    }
    Employee* req_employee = getEmployee(employeeID);
    if (req_employee == nullptr)
    {
        return FAILURE;
    }
    bool was_zero = (req_employee->getSalary() == 0);
    req_employee->IncreaseSalary(salaryIncrease);
    companyArray[req_employee->getCompany()]->employeeSalaryChanged(req_employee, was_zero);
    return SUCCESS;
}

void EmployeeManager::updateCompanyAfterAcquire(Company* company)
{
    HashTable<Employee>* empHash = company->getEmployeesHT();
    int companyID = companyUF->find(company->getId());

    int newGrades=0;
    for (int i = 0; i < empHash->nCells; ++i)
    {
        listNode<Employee>* curNode = empHash->table[i]->head->next;
        while (curNode)
        {
            curNode->data->setCompany(companyID);
            newGrades+=curNode->data->getGrade();
            curNode=curNode->next;
        }
    }
    company->setGradesNum(newGrades);
}

StatusType EmployeeManager::AcquireCompany(int acquirerID, int targetID, double factor)
{
    if(acquirerID <= 0 || acquirerID > size || targetID <= 0 || targetID > size ||
    (getCompany(acquirerID) == getCompany(targetID)) || factor <= 0.0)
    {
        return INVALID_INPUT;
    }

    //int realAcquirerID = companyUF->find(acquirerID);
    Company* acquirerCompany = getCompany(acquirerID);
    Company* targetCompany = getCompany(targetID);

    companyUF->merge(acquirerID,targetID,factor); ///did that update company values?
    unite(acquirerCompany->getEmployeesHT(),targetCompany->getEmployeesHT());
    updateCompanyAfterAcquire(acquirerCompany);
    ///unite trees?
    ///create a new tree?
    AVLRankTree<Employee>* newTree = new AVLRankTree<Employee>;
    uniteTrees(acquirerCompany->getSalaryTree(),targetCompany->getSalaryTree(),newTree);
    delete acquirerCompany->getSalaryTree();
    delete targetCompany->getSalaryTree();
    acquirerCompany->setSalaryTree(newTree);



}

StatusType EmployeeManager::SumOfBumpGradeBetweenTopWorkersByGroup(int companyID, int m)
{
    if (companyID > this->size  || companyID < 0 || m <= 0)
    {
        return  INVALID_INPUT;
    }
    Company* req_company = getCompany(companyID);
    if (req_company->getSalaryTree()->size < m)
    {
        return FAILURE;
    }
    auto tree = req_company->getSalaryTree();
    int to_find = tree->size - m +1;
    int to_return = tree->getGradesSum() - tree->findGradesBelow(tree->findRankedNode(m)->data);


}

StatusType EmployeeManager::AverageBumpGradeBetweenSalaryByGroup(int companyID, int lowerSalary, int higherSalary)
{
    if (companyID > this->size  || companyID < 0 || lowerSalary < 0 || higherSalary < 0 || higherSalary < lowerSalary)
    {
        return INVALID_INPUT;
    }

    auto reqCompany= getCompany(companyID);
    auto tree = reqCompany->getSalaryTree();
    ///calculate number of employees in range
    auto* dummy_emplpoyee = new Employee (99999999,higherSalary , 0,0);
    int elements_below_max = tree->findRank(dummy_emplpoyee);
    int grades_below_max = tree->findGradesBelow(dummy_emplpoyee);
    if (lowerSalary == 0)
    {
        elements_below_max += (reqCompany->getEmployeesNum() - tree->size);
        grades_below_max += (reqCompany->getGradesNum() - tree->getGradesSum());
    }
    delete dummy_emplpoyee;
    auto* dummy_emplpoyee2 = new Employee (0,lowerSalary , 0,0);
    Employee *low_employee;
    int elements_below_min =0;
    int grades_below_min =0;
    if(tree->findMinNode(dummy_emplpoyee2)) {
        low_employee = tree->findMinNode(dummy_emplpoyee2)->data;
        below_min = tree->findRank(low_employee) - 1;
        grades_below_min = tree->findGradesBelow(low_employee) - tree->findMinNode(dummy_emplpoyee2)->grade;
    }

    int total_num = elements_below_max - elements_below_min;
    if (total_num == 0)
    {
        return FAILURE;
    }
    int total_grades = grades_below_max - grades_below_min;




}

StatusType EmployeeManager::CompanyValue(int companyID)
{

}

