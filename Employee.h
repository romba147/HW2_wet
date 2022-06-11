//
// Created by Eyal on 10/06/2022.
//

#ifndef HW2_WET_EMPLOYEE_H
#define HW2_WET_EMPLOYEE_H


class Employee {
    int id;
    int salary;
    int grade;
    int company;
public:
    Employee (int id, int salary , int grade , int company) : id(id) , salary(salary) ,grade(grade),
    company(company){};

    bool operator == (const Employee& emp1) const {
        return this->id==emp1.id;
    }

    virtual ~Employee() = default;

    int getId () const {
        return this->id;
    }

    int getSalary () const
    {
        return salary;
    }

    int getGrade () const
    {
        return grade;
    }

    int getCompany() const
    {
        return company;
    }

    void setCompany(int companyID) ///no validation check
    {
        company = companyID;
    }

    Employee BumpGrade(int num){
        if (num> 0){
            this->grade = this->grade +1;
        }
        return *this;
    }

    Employee IncreaseSalary(int num) {
        this->salary = this->salary + num;
        return *this;
    }



    virtual bool operator < (const Employee& emp1) const{
        if (this->salary == emp1.salary){
            return this->id < emp1.id;
        }
        return this->salary < emp1.salary;
    }

    virtual bool operator > (const Employee& emp1) const{
        if (this->salary == emp1.salary){
            return this->id > emp1.id;
        }
        return this->salary > emp1.salary;
    }

    virtual int operator % (int num) const
    {
        return (this->id % num);
    }
};




#endif //HW2_WET_EMPLOYEE_H
