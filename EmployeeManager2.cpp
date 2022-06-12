//
// Created by Omer Meushar on 11/06/2022.
//

#define MAXID 2147483647
#define MINID 0

#include "EmployeeManager2.h"

static void updateAllNodesAux(node<Employee>* r , AVLRankTree<Employee>* tree)
{
    if (!r)
    {
        return;
    }
    updateAllNodesAux(r->left , tree);
    updateAllNodesAux(r->right , tree);
    r->grade = r->data->getGrade();
    tree->updateSonsNum(r);
}


static void updateAllNodes(AVLRankTree<Employee>* tree)
{
    updateAllNodesAux(tree->root, tree);
}

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

void EmployeeManager::updateSalaryTrees(Employee *employee, int increase ,
                                        Company* company, bool was_zero)
{
    auto tree1 = company->getSalaryTree();
    auto tree2 = companyArray[0]->getSalaryTree();
    if (!was_zero) {
        tree1->deleteNode(tree1->root, employee);
        tree2->deleteNode(tree2->root, employee);
    }
    employee->IncreaseSalary(increase);
    tree1->insert(employee,employee->getGrade());
    tree2->insert(employee,employee->getGrade());
}

void EmployeeManager::updateGradeTrees (Employee* employee , int bump, Company* company)
{
    auto tree1 = company->getSalaryTree();
    auto tree2 = companyArray[0]->getSalaryTree();

    tree1->deleteNode(tree1->root, employee);
    tree2->deleteNode(tree2->root, employee);

    employee->BumpGrade(bump);
    tree1->insert(employee,employee->getGrade());
    tree2->insert(employee,employee->getGrade());
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

    Employee* newEmployee = new Employee(employeeID,0,grade,companyUF->find(companyID));
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
    if(toRemoveEmp == nullptr)
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
    if (req_employee->getSalary() > 0)
    {
        updateGradeTrees(req_employee,bumpGrade, companyArray[req_employee->getCompany()]);
    }
    return SUCCESS;
}
//
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
    updateSalaryTrees(req_employee,salaryIncrease,  companyArray[req_employee->getCompany()],was_zero);

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
    updateCompanyAfterAcquire(acquirerCompany); //update sum of grades
    ///unite trees?
    ///create a new tree?
    auto* newTree = new AVLRankTree<Employee>;
    uniteTrees(acquirerCompany->getSalaryTree(),targetCompany->getSalaryTree(),newTree);
    delete acquirerCompany->getSalaryTree();
    delete targetCompany->getSalaryTree();
    updateAllNodes(newTree);
    //
    acquirerCompany->setSalaryTree(newTree);
    return SUCCESS;

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
    long long int to_return=0;
    if (m == req_company->getSalaryTree()->size)
    {
        to_return =  req_company->getSalaryTree()->root->sonsGradesSum;
    }
    auto tree = req_company->getSalaryTree();
    long long int to_find = tree->size - m ;
    if(to_return==0) {
        to_return = tree->getGradesSum() - tree->findGradesBelow(tree->findRankedNode(to_find)->data);
    }
    printf("SumOfBumpGradeBetweenTopWorkersByGroup %d\n" , to_return);
    return SUCCESS;


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
    auto* dummy_emplpoyee = new Employee(MAXID,higherSalary , 0,0);
    long long int elements_below_max = tree->findRank(dummy_emplpoyee);
    long long int grades_below_max = tree->findGradesBelow(dummy_emplpoyee);
    if (lowerSalary == 0)
    {
        elements_below_max += (reqCompany->getEmployeesNum() - tree->size);
        grades_below_max += (reqCompany->getGradesNum() - tree->getGradesSum());
    }
    delete dummy_emplpoyee;
    auto* dummy_emplpoyee2 = new Employee (MINID,lowerSalary , 0,0);
    Employee *low_employee;
    long long int elements_below_min =0;
    long long int grades_below_min =0;
    if(tree->findMinNode(dummy_emplpoyee2)) {
        low_employee = tree->findMinNode(dummy_emplpoyee2)->data;
        elements_below_min = tree->findRank(low_employee);
        grades_below_min = tree->findGradesBelow(low_employee);
    }

    long long int total_num = elements_below_max - elements_below_min;
    if (total_num == 0)
    {
        return FAILURE;
    }
    delete dummy_emplpoyee2;
    long long int total_grades = grades_below_max - grades_below_min;
    double to_return = double (total_grades)/double (total_num);
    printf("AverageBumpGradeBetweenSalaryByGroup %.1f\n" , to_return);
    return SUCCESS;

}

StatusType EmployeeManager::CompanyValue(int companyID)
{
    if(companyID > this->size  || companyID < 0)
    {
        return INVALID_INPUT;
    }
    double to_return =this->companyUF->getValue(companyID);
    printf("CompanyValue %.1f\n" , to_return);
    return SUCCESS;
}

