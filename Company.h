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
    float value;
    AVLRankTree<Employee>* salary_tree;
    HashTable<Employee>* employees;

public:
    Company(int id , float value) : id(id) , value(value) {
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




    Company setValue(float num)
    {
        value = num;
        return *this;
    }


    Company addEmployee (Employee* employee)
    {


        return *this;
    }

    Company removeEmployee (Employee* employeeRemove)
    {

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
