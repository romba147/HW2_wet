//
// Created by Omer Meushar on 12/06/2022.
//

#include "library2.h"
#include "EmployeeManager2.h"

void *Init(int k)
{
    auto* DS = new EmployeeManager(k);
    return (void*)DS;
}

StatusType AddEmployee(void *DS, int employeeID, int companyID, int grade)
{
    if (DS==NULL)
    {
        return INVALID_INPUT;
    }
        return ((EmployeeManager*)DS)->AddEmployee(employeeID,companyID,grade);
}

StatusType RemoveEmployee(void *DS, int employeeID)
{
    if (DS==NULL)
    {
        return INVALID_INPUT;
    }
    return ((EmployeeManager*)DS)->RemoveEmployee(employeeID);
}

StatusType AcquireCompany(void *DS, int companyID1, int companyID2, double factor)
{
    if (DS==NULL)
    {
        return INVALID_INPUT;
    }
    return ((EmployeeManager*)DS)->AcquireCompany(companyID1,companyID2,factor);
}

StatusType EmployeeSalaryIncrease(void *DS, int employeeID, int salaryIncrease)
{
    if (DS==NULL)
    {
        return INVALID_INPUT;
    }
    return ((EmployeeManager*)DS)->EmployeeSalaryIncrease(employeeID,salaryIncrease);
}

StatusType PromoteEmployee(void *DS, int employeeID, int bumpGrade)
{
    if (DS==NULL)
    {
        return INVALID_INPUT;
    }
    return ((EmployeeManager*)DS)->PromoteEmployee(employeeID,bumpGrade);
}

StatusType SumOfBumpGradeBetweenTopWorkersByGroup(void *DS, int companyID, int m)
{
    if (DS==NULL)
    {
        return INVALID_INPUT;
    }
    return ((EmployeeManager*)DS)->SumOfBumpGradeBetweenTopWorkersByGroup(companyID,m);
}

StatusType AverageBumpGradeBetweenSalaryByGroup(void *DS, int companyID, int lowerSalary, int higherSalary)
{
    if (DS==NULL)
    {
        return INVALID_INPUT;
    }
    return ((EmployeeManager*)DS)->AverageBumpGradeBetweenSalaryByGroup(companyID,lowerSalary,higherSalary);
}

StatusType CompanyValue(void *DS, int companyID)
{
    if (DS==NULL)
    {
        return INVALID_INPUT;
    }
    return ((EmployeeManager*)DS)->CompanyValue(companyID);
}

/*
 * 20 point Bonus function:
StatusType BumpGradeToEmployees(void *DS, int lowerSalary, int higherSalary, int bumpGrade);
 */

void Quit(void** DS)
{
    if(!(*DS))
    {
        return;
    }
    EmployeeManager* steve = (EmployeeManager*)(*DS);
    delete (steve);
    *DS = nullptr;
}


