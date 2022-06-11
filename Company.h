//
// Created by Eyal on 10/06/2022.
//

#ifndef HW2_WET_COMPANY_H
#define HW2_WET_COMPANY_H
#include <iostream>
#include "Employee.h"
#include "AVLRank.h"
#include "HashTable1.h"



class Company {
    int id;
    int GradesNum;
    float value;
    AVLRankTree<Employee>* salary_tree;
    HashTable<Employee>* employees;

public:
    Company(int id , float value) : id(id) , value(value) {
        GradesNum=0;
        salary_tree = new AVLRankTree<Employee>();
        employees = new HashTable<Employee>();
    };


    int getId () const {
        return this->id;
    }

    float getValue () const
    {
        return value;
    }


    AVLRankTree<Employee>* getSalaryTree () const {
        return salary_tree;
    }

    Company& setValue(float num)
    {
        value = num;
        return *this;
    }

    Employee* findEmployee (Employee* req_employee)
    {
        auto to_return =  employees->find(req_employee);
        if (!to_return)
        {
            return nullptr;
        }
        return to_return->data;
    }


    Company& addEmployee (Employee* employee)
    {
        employees->insert(employee);
        return *this;
    }

    Company& employeeSalaryChanged(Employee* employee, bool was_zero)
    {
       if (!was_zero)
       {
           salary_tree->deleteNode(salary_tree->root,employee);
       }
       salary_tree->insert(employee,employee->getGrade());
       return *this;
    }

    Company& employeeGradeWasChanged(Employee* employee , int bumpGrade)
    {
        if (employee->getSalary() > 0)
        {
            salary_tree->deleteNode(salary_tree->root,employee);
            salary_tree->insert(employee,employee->getGrade());
        }
        GradesNum+=bumpGrade;
        return *this;
    }

    Company& removeEmployee (Employee* employeeRemove)
    {
        if (employeeRemove->getSalary() > 0)
        {
            salary_tree->deleteNode(salary_tree->root,employeeRemove);
        }
        employees->remove(employeeRemove);
        GradesNum -= employeeRemove->getGrade();
        return *this;
    }

    bool operator == (const Company& cmp1) const {
        return this->id == cmp1.id;
    }
    bool operator < (const Company& cmp1) const {
        return this->id < cmp1.id;
    }
    bool operator > (const Company& cmp1) const {
        return this->id > cmp1.id;
    }

    void deleteCompanyTrees ()
    {
        salary_tree->deleteAllNodes(salary_tree->root);
        delete salary_tree;
    }



};


#endif //HW2_WET_COMPANY_H
