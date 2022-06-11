//
// Created by Omer Meushar on 11/06/2022.
//

#include "library2.h"
#include "HashTable1.h"
#include "LIst1.h"
#include "Company.h"
#include "UF.h"
#include "AVLRank.h"
#include "Employee.h"

class EmployeeManager
{

public:
    /** EmployeeManager Members **/
    Company** companyArray;
    UF* companyUF;
    Company* systemCompany;

    /** EmployeeManager Methods **/

    //default c'tor:
    EmployeeManager()=delete;

    //user c'tor
    EmployeeManager(int k)
    {
        //init companyArray
        companyArray = new Company*[k];
        for (int i = 0; i < k; ++i)
        {
            companyArray[i] = new Company(i,i);
        }

        //init companyUF
        companyUF = new UF(k);

        //init systemCompany
        systemCompany = new Company(0, 0);
    }



};

void *Init(int k)
{
    if(k<=0)
    {
        ///return FAILURE;
    }

}

StatusType AddEmployee(int employeeID, int companyID, int grade)
{

}

StatusType RemoveEmployee(int employeeID)
{

}

StatusType AcquireCompany(int companyID1, int companyID2, double factor)
{

}

StatusType EmployeeSalaryIncrease(int employeeID, int salaryIncrease)
{

}

StatusType PromoteEmployee(int employeeID, int bumpGrade)
{

}

StatusType SumOfBumpGradeBetweenTopWorkersByGroup(int companyID, int m)
{

}

StatusType AverageBumpGradeBetweenSalaryByGroup(int companyID, int lowerSalary, int higherSalary)
{

}

StatusType CompanyValue(int companyID)
{

}

/**
 * 20 point Bonus function:
StatusType BumpGradeToEmployees(void *DS, int lowerSalary, int higherSalary, int bumpGrade);
 **/

void Quit()
{

}

