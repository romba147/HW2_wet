//
// Created by Omer Meushar on 11/06/2022.
//

#ifndef HW2_WET_EMPLOYEEMANAGER2_H
#define HW2_WET_EMPLOYEEMANAGER2_H
#include "library2.h"

void *Init(int k);

StatusType AddEmployee(int employeeID, int companyID, int grade);

StatusType RemoveEmployee(int employeeID);

StatusType AcquireCompany(int companyID1, int companyID2, double factor);

StatusType EmployeeSalaryIncrease(int employeeID, int salaryIncrease);

StatusType PromoteEmployee(int employeeID, int bumpGrade);

StatusType SumOfBumpGradeBetweenTopWorkersByGroup(int companyID, int m);

StatusType AverageBumpGradeBetweenSalaryByGroup(int companyID, int lowerSalary, int higherSalary);

StatusType CompanyValue(int companyID);

/**
 * 20 point Bonus function:
StatusType BumpGradeToEmployees(void *DS, int lowerSalary, int higherSalary, int bumpGrade);
 **/

void Quit();

#endif //HW2_WET_EMPLOYEEMANAGER2_H
