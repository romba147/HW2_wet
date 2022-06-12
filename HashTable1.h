//
// Created by Omer Meushar on 07/06/2022.
//

#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#define MIN_HASH_SIZE 16

typedef enum {
    SUCCESS_HASH = 0,
    ELEMENT_ALREADY_IN_HASH = -1,
    ELEMENT_NOT_IN_HASH = -2,
    INVALID_INPUT_HASH = -3
} HashStatus;

#include "LIst1.h"
//#include "Employee.h"
//lala

template<class T>
class HashTable
{
public:
    /** Hash Members **/
    List<T>** table;
    long long int nCells;
    long long int nElements;
    //others?

    /** Hash Methods **/

    //c'tor - Min Size
    explicit HashTable()
    {
        table = new List<T>*[MIN_HASH_SIZE];
        nCells = MIN_HASH_SIZE;
        ///do we need this loop?
        for (int i = 0; i < nCells; ++i)
        {
            table[i] = new List<T>();
        }
        nElements = 0;
    }

    //c'tor - known size (for inner usage)
    //not using
    explicit HashTable(long long int nCells) : nCells(nCells)
    {
        table = new List<T>*[nCells];
        ///do we need this loop?
        for (int i = 0; i < nCells; ++i)
        {
            table[i] = new List<T>();
        }
        nElements = 0;
    }

    ~HashTable()
    {
        ///this->clear(); ///do we need this? or use just the line below?
        if(table)
        {
            for (int i = 0; i < nCells; ++i)
            {
                if(table[i])
                {
                    delete table[i];
                    table[i] = nullptr;
                }
            }
            delete[] table;
            table = nullptr;
        }
    }

    int hashFunc(T* const data) const //changed return type from listNode<T>* to int
    {
        return *(data) % nCells;  ///not sure if to do modulo on *(data) or int/long/ll...
    }

    listNode<T>* find(T* const data) const
    {
        if (data == nullptr)
        {
            return nullptr;
        }

        listNode<T>* temp = table[hashFunc(data)]->find(data);
        return temp;
    }

    HashStatus insert(T* const data)
    {
        if (data == nullptr) ///not inserting null data
        {
            return INVALID_INPUT_HASH;
        }

        ListStatus rStatus = table[hashFunc(data)]->insertHead(data);

        if(rStatus == ELEMENT_ALREADY_IN_LIST)
        {
            return ELEMENT_ALREADY_IN_HASH; // element already in hash
        }

        nElements++;
        this->resize();
        return SUCCESS_HASH;
    }

    //for uniting knowing the end size.
    HashStatus noResizeInsert(T* const data)
    {
        if (data == nullptr) ///not inserting null data
        {
            return INVALID_INPUT_HASH;
        }

        ListStatus rStatus = table[hashFunc(data)]->insertHead(data);

        if(rStatus == ELEMENT_ALREADY_IN_LIST)
        {
            return ELEMENT_ALREADY_IN_HASH; // element already in hash
        }

        nElements++;
        //this->resize();
        return SUCCESS_HASH;
    }

    HashStatus remove(T* const data)
    {
        if (data == nullptr) //not inserting null data
        {
            return INVALID_INPUT_HASH;
        }

        ListStatus rStatus = table[hashFunc(data)]->removeNode(data);

        if(rStatus == ELEMENT_NOT_IN_LIST)
        {
            return ELEMENT_NOT_IN_HASH; // element not in hash
        }

        nElements--;
        this->resize();
        return SUCCESS_HASH;

    }

    void resize()
    {
        if (nElements >= nCells)
        {
            this->expand(); // double hash
        }
        else if (nElements <= nCells/4 && nCells > MIN_HASH_SIZE)
        {
            this->shrink(); // cut hash by half
        }
    }

    void expand()
    {
        int cur_nCells = nCells;
        nCells*=2; // hash size is changed here
        reHash(cur_nCells);
    }

    void shrink()
    {
        int cur_nCells = nCells;
        nCells/=2; // hash size is changed here
        reHash(cur_nCells);
    }


    void reHash(int cur_nCells)
    {
        auto* newTable = new List<T>*[nCells];
        ///do we need this loop?
        for (int i = 0; i < nCells; ++i)
        {
            newTable[i] = new List<T>();
        }

        for (int i = 0; i < cur_nCells; ++i)
        {
            listNode<T>* curNode = table[i]->head->next;
            while (curNode)
            {
                int newIdx = hashFunc(curNode->data); // nCells is ok
                newTable[newIdx]->insertHead(curNode->data);
                curNode = curNode->next;
            }
        }

        for (int i = 0; i < cur_nCells; ++i)
        {
            delete table[i];
        }
        delete[] table;

        table = newTable;

    }

    //clear doesn't resize the dynamic Array!!
    //havn't used clear - don't think we need it..
    void clear()
    {
        for (int i = 0; i < nCells; ++i)
        {
            assert(table[i]); ///for debugging
            table[i]->clear();
        }
        nElements = 0;
    }

    void addHash(HashTable<T>* hAdded)
    {

        for (int i = 0; i < hAdded->nCells; ++i)
        {
            listNode<T>* curNode = hAdded->table[i]->head->next;
            while (curNode)
            {
                insert(curNode->data);
                //int newIdx = hashFunc(curNode->data); // nCells is ok
                //table[newIdx]->insertHead(curNode->data);
                curNode = curNode->next;
            }
        }
    }
/*
 *     ~HashTable()
    {
        ///this->clear(); ///do we need this? or use just the line below?
        if(table)
        {
            for (int i = 0; i < nCells; ++i)
            {
                if(table[i])
                {
                    delete table[i];
                    table[i] = nullptr;
                }
            }
            delete[] table;
            table = nullptr;
        }
    }
 * */
    void deleteHashData()
    {
        if(table)
        {
            for (int i = 0; i < nCells; ++i)
            {
                if(table[i]) ///check if not addressing deleted lists
                {
                    table[i]->deleteListData();
                    //table[i]= nullptr;
                }
            }
            //delete[] table;
            //table = nullptr;
        }
    }

};


/** Hash General Non-Member Functions **/
//template<class T>
//void swapHashes(HashTable<T>* hBase, HashTable<T>* hAdded)
//{
//    List<T>** tempTable = hBase->table;
//    int tempNElements = hBase->nElements;
//    int tempNCells = hBase->nCells;
//
//    hBase->table = hAdded->table;
//    hBase->nCells = hAdded->nCells;
//    hBase->nElements = hAdded->nElements;
//
//    hAdded->table = tempTable;
//    hAdded->nCells = tempNCells;
//    hAdded->nElements = tempNElements;
//}

template<class T>
void unite(HashTable<T>* hBase, HashTable<T>* hAdded)
{
        hBase->addHash(hAdded);
        delete hAdded;
//    else //hBase is smaller
//    {
//        hAdded->addHash(hBase);
//        swapHashes(hBase, hAdded);
//        delete hAdded;
//    }
}

///not checked







/*
template<class T>
void unite(HashTable<T>* hBase, HashTable<T>* hAdded)
{
    int newNElements = hBase->nElements + hAdded->nElements;
    int newNCells = MIN_HASH_SIZE;
    while (newNElements>=newNCells)
    {
        newNCells *= 2;
    }

    HashTable<T>* hNew= new HashTable<T>*(newNCells);
    ///do we need this loop?
    for (int i = 0; i < newNCells; ++i)
    {
        hNew->table[i] = new List<T>();
    }

    for (int i = 0; i < hBase; ++i)
    {
        listNode<T>* curNode = hBase->table[i]->head->next;
        while (curNode)
        {
            int newIdx = hNew->hashFunc(curNode->data); // nCells is ok
            hNew->table[newIdx]->insertHead(curNode->data);
            curNode = curNode->next;
        }
    }

    for (int i = 0; i < hAdded; ++i)
    {
        listNode<T>* curNode = hAdded->table[i]->head->next;
        while (curNode)
        {
            int newIdx = hNew->hashFunc(curNode->data); // nCells is ok
            hNew->table[newIdx]->insertHead(curNode->data);
            curNode = curNode->next;
        }
    }

    delete[] hBase->table;
    hBase->table = hNew->table;
    hBase->nElements = newNElements;
    hBase->nCells = newNCells;

}*/






#endif //HASHTABLE_HASHTABLE_H
