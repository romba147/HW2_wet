//
// Created by Eyal on 11/06/2022.
//

#ifndef HW2_WET_HASHTABLE1_H
#define HW2_WET_HASHTABLE1_H


#define MIN_HASH_SIZE 16

//typedef enum {
//    SUCCESS_HASH = 0,
//    ELEMENT_ALREADY_IN_HASH = -1,
//    ELEMENT_NOT_IN_HASH = -2,
//    INVALID_INPUT_HASH = -3
//} HashStatus;

#include "dummy_lib.h" ///delete after!!!
#include "LIst1.h"

template<class T>
class HashTable
{
public:
    /** Hash Members **/
    List<T>** table;
    int nCells;
    int nElements;
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
    explicit HashTable(int nCells) : nCells(nCells)
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
        delete[] table;
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

    StatusType insert(T* const data)
    {
        if (data == nullptr) ///not inserting null data
        {
            return INVALID_INPUT;
        }

        StatusType rStatus = table[hashFunc(data)]->insertHead(data);

        if(rStatus == FAILURE)
        {
            return FAILURE; // element already in hash
        }

        nElements++;
        this->resize();
        return SUCCESS;
    }

    StatusType remove(T* const data)
    {
        if (data == nullptr) //not inserting null data
        {
            return INVALID_INPUT;
        }

        StatusType rStatus = table[hashFunc(data)]->removeNode(data);

        if(rStatus == FAILURE)
        {
            return FAILURE; // element not in hash
        }

        nElements--;
        this->resize();
        return SUCCESS;

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

};




#endif //HW2_WET_HASHTABLE1_H
