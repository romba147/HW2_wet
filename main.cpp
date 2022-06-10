#include <iostream>
#include "UF.h"
#include "AVLRank.h"

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

     auto tree = new AVLRankTree<int>();
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


    return 0;




}
