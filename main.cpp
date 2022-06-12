#include <iostream>
#include "UF.h"
#include "AVLRank.h"
#include "EmployeeManager2.h"

int main() {
 /*   //testing union find
    auto uf = UF(6);
    std::cout << "num of groups " << uf.getGroupsNum() <<std::endl;
    uf.merge(4,5);
    std::cout << "num of groups " << uf.getGroupsNum() <<std::endl;
    std::cout << uf.find(4) << std::endl;
    uf.merge(3,1);
    uf.merge(2,4);
    std::cout << "num of groups " << uf.getGroupsNum() <<std::endl;
    std::cout << uf.find(2) << std::endl;
    std::cout << uf.find(3) << std::endl;
    std::cout << uf.getGroupSize(5) << std::endl;
*/

/*     auto tree = new AVLRankTree<int>();
     auto a = new int (1);
     auto b = new int (2);
     auto c = new int (3);
     auto d = new int (4);
     auto e = new int (5);
     auto f = new int (6);
     auto g = new int (7);
     auto h = new int (8);

     tree->insert(a,3);
     tree->insert(c,2);
     tree->insert(e,3);
     tree->insert(g,2);
     tree->insert(h,3);
     tree->insert(d,2);
     tree->insert(b,2);
    std::cout << tree->findRank(a) << std::endl;
    std::cout << tree->findRank(b) << std::endl;
    std::cout << tree->findRank(c) << std::endl;
    std::cout << tree->findRank(d) << std::endl;
    std::cout << tree->findRank(e) << std::endl;
    std::cout << tree->findRank(g) << std::endl;
    std::cout << tree->findRank(h) << std::endl;


    std::cout << tree->findGradesBelow(a) << std::endl;
    std::cout << tree->findGradesBelow(b) << std::endl;
    std::cout << tree->findGradesBelow(c) << std::endl;
    std::cout << tree->findGradesBelow(d) << std::endl;
    std::cout << tree->findGradesBelow(e) << std::endl;
    std::cout << tree->findGradesBelow(g) << std::endl;
    std::cout << tree->findGradesBelow(h) << std::endl;

    tree->deleteNode(tree->root,a);
    tree->deleteNode(tree->root,e);
    std::cout << tree->findRank(h) << std::endl;
    std::cout << tree->findGradesBelow(h) << std::endl;


    return 0;

*/

/** TESTING EMPLOYEE MANAGER **/
/*
////   add employee testing:
    auto* steve = new EmployeeManager(10);
    steve->AddEmployee(5,5,5);
    steve->AddEmployee(6,5,5);
    steve->AddEmployee(7,5,5);
    steve->AddEmployee(8,5,5);
    steve->AddEmployee(9,5,5);

    steve->AddEmployee(10,1,5);
    steve->AddEmployee(11,2,5);
    steve->AddEmployee(12,3,5);
    steve->AddEmployee(13,4,5);

    auto check = steve->getCompany(5);
    auto check2 = steve->getCompany(0);
    auto check3 = steve->getCompany(3);
    auto check4 = steve->getCompany(4);
    auto checkr = steve->getCompany(5);

   auto* steve = new EmployeeManager(10);
    steve->AddEmployee(5,5,5);
    steve->AddEmployee(6,5,5);
    steve->AddEmployee(7,5,5);
    steve->AddEmployee(8,5,5);
    steve->AddEmployee(9,5,5);*/

/**increase salary testing **/
/*
   auto* steve = new EmployeeManager(10);
    steve->AddEmployee(5,5,5);
    steve->AddEmployee(6,5,5);
    steve->AddEmployee(7,5,5);
    steve->AddEmployee(8,5,5);
    steve->AddEmployee(9,5,5);

    steve->EmployeeSalaryIncrease(5,100);
    steve->EmployeeSalaryIncrease(5,100);
    steve->EmployeeSalaryIncrease(5,100);
    auto check = steve->getCompany(5);
    steve->EmployeeSalaryIncrease(7,100);
    steve->EmployeeSalaryIncrease(8,100);
    steve->EmployeeSalaryIncrease(9,100);
    steve->EmployeeSalaryIncrease(7,200);
    steve->EmployeeSalaryIncrease(6,400);
    steve->EmployeeSalaryIncrease(5,100);
    auto check2 = steve->getCompany(5);
    steve->EmployeeSalaryIncrease(5,100);*/

/** bump grade check + remove employee **/

/*   auto* steve = new EmployeeManager(10);
    steve->AddEmployee(5,5,5);
    steve->AddEmployee(6,5,5);
    steve->AddEmployee(7,5,5);
    steve->AddEmployee(8,5,5);
    steve->AddEmployee(9,5,5);
    steve->EmployeeSalaryIncrease(7,100);
    steve->EmployeeSalaryIncrease(8,100);
    steve->EmployeeSalaryIncrease(9,100);
    steve->EmployeeSalaryIncrease(7,200);
    steve->EmployeeSalaryIncrease(6,400);
    steve->EmployeeSalaryIncrease(5,100);
    auto check2 = steve->getCompany(5);

    steve->PromoteEmployee(5,3);
    steve->PromoteEmployee(6,5);
    steve->PromoteEmployee(8,6);
    steve->PromoteEmployee(7,4);
    steve->PromoteEmployee(9,3);
    steve->PromoteEmployee(6,8);
    steve->PromoteEmployee(5,9);
    steve->PromoteEmployee(5,11);
    steve->PromoteEmployee(5,11);
    steve->PromoteEmployee(5,11);
    steve->RemoveEmployee(6);
    steve->RemoveEmployee(7);
    steve->RemoveEmployee(5);
    steve->RemoveEmployee(9);
    steve->RemoveEmployee(8);*/

/** acquire company testing **/

/*    auto* steve = new EmployeeManager(10);
    steve->AddEmployee(5,5,5);
    steve->AddEmployee(6,5,5);
    steve->AddEmployee(7,5,5);
    steve->AddEmployee(8,5,5);
    steve->AddEmployee(9,5,5);
    steve->EmployeeSalaryIncrease(7,100);
    steve->EmployeeSalaryIncrease(8,100);
    steve->EmployeeSalaryIncrease(9,100);
    steve->EmployeeSalaryIncrease(7,200);
    steve->EmployeeSalaryIncrease(6,400);
    steve->EmployeeSalaryIncrease(5,100);

    steve->AddEmployee(15,6,5);
    steve->AddEmployee(16,6,5);
    steve->AddEmployee(17,6,5);
    steve->AddEmployee(18,6,5);
    steve->AddEmployee(19,6,5);
    steve->EmployeeSalaryIncrease(17,100);
    steve->EmployeeSalaryIncrease(18,100);
    steve->EmployeeSalaryIncrease(19,100);
    steve->EmployeeSalaryIncrease(17,200);
    steve->EmployeeSalaryIncrease(16,400);
    steve->EmployeeSalaryIncrease(15,100);
    auto check1 = steve->getCompany(5);
    auto check2 = steve->getCompany(6);


    steve->AcquireCompany(5,6,1.1);
    auto check = steve->getCompany(5);
    steve->AddEmployee(20,6,3);
    steve->AddEmployee(22,6,3);
    steve->EmployeeSalaryIncrease(22,70);
    steve->PromoteEmployee(22, 17);
    steve->AddEmployee(20,6,3); */


/** sum of bump grades **/

 /*   auto* steve = new EmployeeManager(10);
    steve->AddEmployee(5,5,5);
    steve->AddEmployee(6,5,6);
    steve->AddEmployee(7,5,7);
    steve->AddEmployee(8,5,8);
    steve->AddEmployee(9,5,9);
    steve->EmployeeSalaryIncrease(7,100);
    steve->EmployeeSalaryIncrease(8,100);
    steve->EmployeeSalaryIncrease(9,100);
    steve->EmployeeSalaryIncrease(7,200);
    steve->EmployeeSalaryIncrease(6,400);
    steve->EmployeeSalaryIncrease(5,100);

    steve->SumOfBumpGradeBetweenTopWorkersByGroup(5,3);
    steve->getCompany(5);
    steve->SumOfBumpGradeBetweenTopWorkersByGroup(5,1);
    steve->SumOfBumpGradeBetweenTopWorkersByGroup(5,5);*/

/** average grades **/

/*    auto* steve = new EmployeeManager(10);
    steve->AddEmployee(5,5,5);
    steve->AddEmployee(6,5,6);
    steve->AddEmployee(7,5,7);
    steve->AddEmployee(8,5,8);
    steve->AddEmployee(9,5,9);
    steve->EmployeeSalaryIncrease(7,100);
    steve->EmployeeSalaryIncrease(8,100);
    steve->EmployeeSalaryIncrease(9,100);
    steve->EmployeeSalaryIncrease(7,200);
    steve->EmployeeSalaryIncrease(6,400);
    steve->EmployeeSalaryIncrease(5,100);

    steve->AverageBumpGradeBetweenSalaryByGroup(5,150,1000);
    steve->AverageBumpGradeBetweenSalaryByGroup(5,90,350); */

/** check values **/
    auto* steve = new UF(10);
    steve->merge(4,9,1);
    steve->merge(10,8,3);
    steve->merge(8,7,4);
    int a = steve->getValue(8);
    int b = steve->getValue(7);
    int c = steve->getValue(10);


/** test 1 segel **/
/*
    auto* steve = new EmployeeManager(10);
    steve->AddEmployee (18 ,6 ,31);
    steve->AddEmployee (1, 2 ,4);
    steve->AddEmployee (499104, 2 ,15);
    steve->AddEmployee (-2, -2 ,33);
    steve->AddEmployee (16, 3, 13);
    steve->AddEmployee (13, 9 ,13);
    steve->RemoveEmployee (1);
    steve->RemoveEmployee (18);
    steve-> AddEmployee (3, 10 ,39);
    steve-> AcquireCompany (4 ,9, 1);
    steve-> EmployeeSalaryIncrease (16, 2);
    steve->PromoteEmployee (13, 1);
    steve->SumOfBumpGradeBetweenTopWorkersByGroup  (4 ,1);
    steve-> AverageBumpGradeBetweenSalaryByGroup  (4 ,-1 ,2);
    steve-> CompanyValue (8);
    steve-> AcquireCompany (10, 8 ,3);
    steve-> AcquireCompany (8 ,7 ,4);
    steve->EmployeeSalaryIncrease (499104 ,6);
    steve->EmployeeSalaryIncrease (3 ,1);
    steve-> PromoteEmployee (13 ,10);
    steve->CompanyValue (8);
    steve-> CompanyValue (7);
    steve-> PromoteEmployee (16 ,7);
    steve->AverageBumpGradeBetweenSalaryByGroup  (5 ,2 ,6);
    steve->SumOfBumpGradeBetweenTopWorkersByGroup  (9 ,1);
    steve->CompanyValue (10);
*/
}
