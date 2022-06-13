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
    long long int GradesNum;
    double value;
    AVLRankTree<Employee>* salary_tree;
    HashTable<Employee>* employees;

public:
    Company(int id , double value) : id(id) , value(value) {
        GradesNum=0;
        salary_tree = new AVLRankTree<Employee>();
        employees = new HashTable<Employee>();
    };

    ~Company()
    {
        //if (salary_tree) {   ///omer: deleted because clion said
            delete salary_tree;
        //}
        //if(employees) {      ///omer: deleted because clion said
            delete employees;
        //}
    }


    int getId () const {
        return this->id;
    }

    long long int getEmployeesNum() const
    {
        return this->employees->nElements;
    }

    double getValue () const
    {
        return value;
    }
    long long int getGradesNum() const
    {
        return GradesNum;
    }

    void setGradesNum(long long int n)
    {
        GradesNum = n;
    }

    void setSalaryTree(AVLRankTree<Employee>* tree)
    {
        salary_tree = tree;
    }

    void setHT(HashTable<Employee>* ht)
    {
        employees = ht;
    }

    void bumpTotalGrade(int bump) ///omer: didn't change to long long int - because the argument is int - given from user.
    {
        if(bump>0)
        {
            GradesNum += bump;
        }
    }

    AVLRankTree<Employee>* getSalaryTree () const {
        return salary_tree;
    }


    HashTable<Employee>* getEmployeesHT () const {
        return employees;
    }

    Company& setValue(double num)
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
        GradesNum+=employee->getGrade();
        return *this;
    }

    /*
    int calculateGradesSum()
    {
        int newGrades =0;
        for (int i = 0; i < employees->nCells; ++i)
        {
            listNode<Employee>* curNode = employees->table[i]->head->next;
            while (curNode)
            {
                newGrades+=curNode->data->getGrade();
                curNode=curNode->next;
            }
        }
        return newGrades;
    }
     */


    Company& employeeGradeWasChanged(Employee* employee , int bumpGrade) ///omer: what is this? not used
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
