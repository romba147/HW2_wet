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
    auto* newEmployee = new Employee(Id,0,0);
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

}

StatusType EmployeeManager::RemoveEmployee(int employeeID)
{

}

StatusType EmployeeManager::PromoteEmployee(int employeeID, int bumpGrade)
{
    if (employeeID < =0)
    {
        return INVALID_INPUT;
    }
    Employee* req_employee = getEmployee(employeeID);
    if (req_employee == nullptr)
    {
        return FAILURE;
    }
    req_employee->BumpGrade(bumpGrade);
    companyArray[req_employee->getCompany()]->employeeGradeWasChanged(req_employee);
    return SUCCESS;

}

StatusType EmployeeManager::EmployeeSalaryIncrease(int employeeID, int salaryIncrease)
{
    if (employeeID < =0)
    {
        return INVALID_INPUT;
    }
    Employee* req_employee = getEmployee(employeeID);
    if (req_employee == nullptr)
    {
        return FAILURE;
    }
    req_employee->IncreaseSalary(salaryIncrease);
    companyArray[req_employee->getCompany()]->employeeSalaryChanged(req_employee);
    return SUCCESS;
}

StatusType EmployeeManager::AcquireCompany(int companyID1, int companyID2, double factor)
{

}

StatusType EmployeeManager::SumOfBumpGradeBetweenTopWorkersByGroup(int companyID, int m)
{

}

StatusType EmployeeManager::AverageBumpGradeBetweenSalaryByGroup(int companyID, int lowerSalary, int higherSalary)
{

}

StatusType EmployeeManager::CompanyValue(int companyID)
{

}

