//
// Created by Omer Meushar on 11/06/2022.
//

#ifndef HW2_WET_EMPLOYEEMANAGER2_H
#define HW2_WET_EMPLOYEEMANAGER2_H
#include "HashTable1.h"
#include "LIst1.h"
#include "Company.h"
#include "UF.h"
#include "AVLRank.h"
#include "Employee.h"
#include "library2.h" ///need to change? lib2 not including employeeManager?

class EmployeeManager
{

public:
    /** EmployeeManager Members **/
    Company** companyArray;
    UF* companyUF;
    //Company* systemCompany;
    int size; ///omer: didn't change - cause given as int from user and not changed

    /** EmployeeManager Methods **/


    //user c'tor
    explicit EmployeeManager(int k)
    {
        size = k;
        //init companyArray
        //element 0 is the general company
        companyArray = new Company*[(long int)k+1];
        for (int i = 0; i < (long int)k+1; ++i) ///omer: changed to long int in case of choosing max int
        {
            companyArray[i] = new Company(i,i);
        }

        //init companyUF
        companyUF = new UF(k);

        //init systemCompany
        //systemCompany = new Company(0, 0);
    }

    ~EmployeeManager()
    {
        for (int i = 1; i < (long int)size + 1; ++i)
        {
            delete companyArray[i];
        }
        delete companyUF;
        companyArray[0]->getEmployeesHT()->deleteHashData();
        delete companyArray[0];
        delete[] companyArray;

    }

    Company* getCompany (int n);

    Employee* getEmployee (int  id);

    void updateCompanyAfterAcquire(Company* company, int newCompany);

    void updateSalaryTrees (Employee* employee , int increase, Company* company , bool was_zero);

    void updateGradeTrees (Employee* employee , int bump, Company* company);

    StatusType AddEmployee(int employeeID, int companyID, int grade);

    StatusType RemoveEmployee(int employeeID);

    StatusType AcquireCompany(int companyID1, int companyID2, double factor);

    StatusType EmployeeSalaryIncrease(int employeeID, int salaryIncrease);

    StatusType PromoteEmployee(int employeeID, int bumpGrade);

    StatusType SumOfBumpGradeBetweenTopWorkersByGroup(int companyID, int m);

    StatusType AverageBumpGradeBetweenSalaryByGroup(int companyID, int lowerSalary, int higherSalary);

    StatusType CompanyValue(int companyID);



};





/**
 * 20 point Bonus function:
StatusType BumpGradeToEmployees(void *DS, int lowerSalary, int higherSalary, int bumpGrade);
 **/


#endif //HW2_WET_EMPLOYEEMANAGER2_H
