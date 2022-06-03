#include <iostream>
#include "UF.h"

int main() {
    //testing union find
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


}
