//
// Created by Eyal on 11/06/2022.
//

#ifndef HW2_WET_LIST1_H
#define HW2_WET_LIST1_H

///create statuses: node exists, node doesn't exist,....???
typedef enum {
    SUCCESS_LIST = 0,
    ELEMENT_ALREADY_IN_LIST = -1,
    ELEMENT_NOT_IN_LIST = -2,
    INVALID_INPUT_LIST = -3
} ListStatus;

//#include "dummy_lib.h" ///delete after!!!

template<class T>
struct listNode
{
    T* data;
    listNode* next;

    ///listNode* prev;
    ///do we need height? other?
    /// if want to create dummy node by c'tor: listNode() : data(nullptr), next(nullptr) {}
    explicit listNode(T* data) : data(data), next(nullptr) {}
};

template<class T>
class List
{
public:
    /** List Members **/
    listNode<T>* head;
    int size;      //is int ok? "big numbers". I guess yes
    //do we need other members?
    //friend class HashTable;

    /** List Methods **/
    explicit List() {
        head = new listNode<T>(nullptr);
        size = 0;
    }

    ~List()
    {
        this->clear(); //delete all data nodes
        delete head; //delete dummy node
    }

    listNode<T>* find(const T* const data) const {
        if (data == nullptr)
        {
            return nullptr;
        }
        listNode<T>* temp = head->next;
        while (temp)
        {
            if (*(temp->data) == *data)
            {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    //insert to list as new head (after dummy node)
    ///listNode<T>* insertHead(const T* const data)
    ListStatus insertHead(T* const data)
    {
        if (data == nullptr) ///not inserting null data
        {
            return INVALID_INPUT_LIST;
        }
        if(find(data))
        {
            return ELEMENT_ALREADY_IN_LIST; // element already in list
        }
        auto* newNode = new listNode<T>(data); ///changed c'tor
        newNode->next = head->next;
        head->next = newNode;
        size++;
        return SUCCESS_LIST;
    }

    //gets the wanted node data, returns the ptr to the removed node
    ListStatus removeNode(T* data)
    {
        if (data == nullptr) //not inserting null data
        {
            return INVALID_INPUT_LIST;
        }

        listNode<T>* temp = head;
        while (temp->next)
        {
            if (*(temp->next->data) == *data)
            {
                listNode<T>* rmNode = temp->next;
                temp->next = rmNode->next;
                rmNode->next = nullptr;   //think there is no need
                delete rmNode;
                size--;
                return SUCCESS_LIST;
            }
            temp = temp->next;
        }
        return ELEMENT_NOT_IN_LIST; // element not in list
    }

    void clear()
    {
        while (head->next)
        {
            listNode<T>* rmNode = head->next;
            head->next = rmNode->next;
            rmNode->next = nullptr;
            delete rmNode;
        }
        size=0;
    }

    void deleteListData()
    {
        listNode<T>* rmNode = head->next;
        while (rmNode)
        {
//            head->next = rmNode->next;
//            rmNode->next = nullptr;
            delete rmNode->data;
            rmNode=rmNode->next;
            //delete rmNode;
        }
        size=0;
    }

};


#endif //HW2_WET_LIST1_H
