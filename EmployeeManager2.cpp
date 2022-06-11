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

    Employee* newEmployee = new Employee(employeeID,0,grade,0);
    companyArray[0]->addEmployee()


    return SUCCESS;

}

StatusType EmployeeManager::RemoveEmployee(int employeeID)
{
    if (employeeID <= 0)
    {
        return INVALID_INPUT;
    }
    if (companyArray[0]->findEmployee())

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

StatusType EmployeeManager::AcquireCompany(int companyID1, int companyID2, double factor)
{

}

StatusType EmployeeManager::SumOfBumpGradeBetweenTopWorkersByGroup(int companyID, int m)
{
    if (companyID > this->size  || companyID < 0 || m <= 0)
    {
        return  INVALID_INPUT;
    }
    auto req_company = getCompany(companyID);
    if (req_company.)

}

StatusType EmployeeManager::AverageBumpGradeBetweenSalaryByGroup(int companyID, int lowerSalary, int higherSalary)
{

}

StatusType EmployeeManager::CompanyValue(int companyID)
{

}

