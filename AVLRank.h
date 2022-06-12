//
// Created by Eyal on 02/06/2022.
//

#ifndef HW2_WET_AVLRANK_H
#define HW2_WET_AVLRANK_H

#include <cmath>
#include <exception>
#include <cstdlib>
#include "Employee.h"


template <class T>
struct node {
    node *left;
    node *right;
    T *data;
    long long int sonsNum;
    long long int sonsGradesSum;
    int grade;
    long long int height;

    node(T* data, int grade = 0) : data (data), grade(grade) , sonsGradesSum(grade)
    {
        left = nullptr;
        right = nullptr;
        height = 0;
        sonsNum =1;
    }
};

template <class T>
class AVLRankTree {
public:
    node<T> * root;
    int size;

    AVLRankTree() {
        this->root = nullptr;
        size=0;
    }
    ~AVLRankTree(){
        this->deleteAllNodes(root);
    }
    long long int calHeight (node<T>* p) const{
        if (!(p->left) && !(p->right)){
            return 0;
        }
        else if (!(p->left))
        {
            return p->right->height + 1;
        }
        else if (!(p->right))
        {
            return p->left->height + 1;
        }
        if (p->left->height > p->right->height)
        {
            return p->left->height +1;
        }
        return p->right->height +1;
    }

    void updateHeight (node<T>* top)
    {
        top->right->height = calHeight(top->right);
        top->left->height = calHeight(top->left);
        top->height= calHeight(top);
    }

    void updateSonsNum (node<T>* top)
    {
        if (top == nullptr)
        {
            return;
        }
        if (top->right == nullptr && top->left == nullptr)
        {
            top->sonsNum = 1;
            top->sonsGradesSum = top->grade;

            return;
        }
        if(top->right == nullptr)
        {
            top->sonsNum = top->left->sonsNum + 1;
            top->sonsGradesSum = top->left->sonsGradesSum + top->grade;
            return;
        }
        if (top->left == nullptr)
        {
            top->sonsNum = top->right->sonsNum + 1;
            top->sonsGradesSum = top->right->sonsGradesSum + top->grade;
            return;
        }
        top->sonsNum = top->right->sonsNum + top->left->sonsNum +1;
        top->sonsGradesSum = top->right->sonsGradesSum + top->left->sonsGradesSum + top->grade;

    }

    int calBF (node<T>* p) const{
        if (p->right && p->left){
            return p->left->height - p->right->height;
        }
        else if (p->left && !(p->right)){
            return (p->left->height)+1;
        }
        else if (!(p->left) && p->right){
            return -1-(p->right->height);
        }
        return 0;
    }

    node<T>* ll_rotation (node<T>* p){
        node<T>* top =p->left;
        p->left= top->right;
        top->right= p;
        if(p==root)
        {
            root=top;
        }
        updateHeight(top);

        return top;
    }

    node<T>* rr_rotation (node<T>* p){
        node<T>* top = p->right;
        p->right = top->left;
        top->left = p;
        if(p==root)
        {
            root=top;
        }
        updateHeight (top);

        return top;
    }

    node<T>* rl_rotation (node<T>* p){
        node<T>* top1 = p->right;
        node<T>* top2 = p->right->left;
        p->right = top2->left;
        top1->left = top2->right;
        top2->left = p;
        top2->right = top1;
        if(p==root)
        {
            root=top2;
        }
        updateHeight(top2);

        return top2;
    }

    node<T>* lr_rotation (node<T>* p){
        node<T>* top1 = p->left;
        node<T>* top2 = p->left->right;
        p->left = top2->right;
        top1->right = top2->left;
        top2->right = p;
        top2->left = top1;
        if(p==root)
        {
            root=top2;
        }
        updateHeight(top2);
        return top2;
    }

    node<T>* insert (T* data , int grade)
    {
        return insertAux(root,data , grade);
    }

    node<T>* insertAux (node<T>* r,T* data , int grade)
    {
        if (!r){
            auto* newNode = new node<T>(data, grade);
            if (!newNode)
            {
                return nullptr;
            }
            if (root == nullptr)
            {
                root = newNode;
            }
            r = newNode;
            size++;
            return r;
        }
        else{
            if (*(data) < *(r->data))
                r->left = insertAux(r->left,data,grade);
            else
                r->right = insertAux(r->right,data,grade);
        }

        r->height = calHeight(r);

        if (calBF(r)==2 && calBF(r->left)==1){
            r = ll_rotation(r);
        }
        else if (calBF(r)==-2 && calBF(r->right)==-1){
            r = rr_rotation(r);
        }
        else if (calBF(r)==-2 && calBF(r->right)==1){
            r = rl_rotation(r);
        }
        else if (calBF(r)==2 && calBF(r->left)==-1){
            r = lr_rotation(r);
        }

        updateSonsNum(r->left);
        updateSonsNum(r->right);
        updateSonsNum(r);

        return r;
    }

    node<T>* smallest (node<T>* r) {
        if (r == nullptr)
        {
            return nullptr;
        }
        while (r->left){
            r = r->left;
        }
        return r;
    }
    node<T>* biggest (node<T>* r) {
        if (r == nullptr)
        {
            return nullptr;
        }
        while (r->right){
            r = r->right;
        }
        return r;
    }

    node<T>* deleteNode (node<T>* r , T* data) {
        ///added this condition. if there are problems with delete - check here
        if (r == nullptr)
        {
            return nullptr;
        }
        if (!(r->left) && !(r->right)){
            if (r == this->root){
                this->root = nullptr;
            }
            delete r;
            size--;
            return nullptr;
        }

        node<T>* s;
        node<T>* b;

        if (*(r->data) < *(data)){
            r->right = deleteNode(r->right,data);
        }
        else if (*(r->data) > *(data)){
            r->left = deleteNode(r->left,data);
        }
        else
        {
            if (r->left)
            {
                s = biggest(r->left);
                r->data = s->data;
                r->grade = s->grade;
                r->left = deleteNode(r->left,s->data);
            }
            else
            {
                b = smallest(r->right);
                r->data = b->data;
                r->grade = b->grade;
                r->right = deleteNode(r->right,b->data);
            }
        }
        r->height = calHeight(r);

        if (calBF(r)==2 && calBF(r->left)==1){
            r = ll_rotation(r);
        }
        else if (calBF(r)==-2 && calBF(r->right)==-1){
            r = rr_rotation(r);
        }
        else if (calBF(r)==-2 && calBF(r->right)==1){
            r = rl_rotation(r);
        }
        else if (calBF(r)==2 && calBF(r->left)==-1){
            r = lr_rotation(r);
        }
        else if (calBF(r)==2 && calBF(r->left)==0){
            r = ll_rotation(r);
        }
        else if (calBF(r)==-2 && calBF(r->right)==0){
            r = rr_rotation(r);
        }

        updateSonsNum(r->left);
        updateSonsNum(r->right);
        updateSonsNum(r);

        return r;
    }

    node<T>* findNode (node<T>* r , T* data) const
    {
        if (r == nullptr)
        {
            return nullptr;
        }

        if (*(data) == *(r->data))
        {
            return r;
        }

        else if (*(data) < *(r->data))
        {
            return findNode(r->left,data);
        }
        else if ((*(data) > *(r->data)))
        {
            return  findNode(r->right,data);
        }
        return nullptr;
    }

    //inorder - calling the function creates an array using malloc
    //if no need to limit array size - insert tree size as max
    T** inorderArray (long long int max ) const
    {
        long long int counter=0;
        T** arr = (T**)malloc(max*sizeof(T*));
        inorderArrayAux(root, arr, &counter, max);
        return arr;
    }

    void inorderArrayAux (node<T>* r, T* arr[], long long int* counter , long long int max) const
    {
        if (!r)
        {
            return;
        }
        inorderArrayAux (r->left, arr , counter,max);
        if (*counter < max) {
            arr[*counter] = r->data;
            *counter = *counter + 1;
            inorderArrayAux(r->right, arr, counter, max);
        }
    }

    T** reverseInorderArray (long long int max) const
    {
        long long int counter=0;
        T** arr = (T**)malloc(max*sizeof(T*));
        reverseInorderArrayAux(root, arr, &counter, max);
        return arr;
    }

    void reverseInorderArrayAux (node<T>* r, T* arr[], long long int* counter , long long int max) const
    {
        if (!r)
        {
            return;
        }
        reverseInorderArrayAux (r->right, arr , counter,max);
        if (*counter < max) {
            arr[*counter] = r->data;
            *counter = *counter + 1;
            reverseInorderArrayAux(r->left, arr, counter, max);
        }

    }

    T** smartInorderArray (T* min , T* max , int* numMatching) const
    {
        int counter=0;
        T** arr = (T**)malloc(size*sizeof(T*));
        smartInorderArrayAux(root, arr, &counter,  min , max);
        *numMatching = counter;
        T** arr2 = (T**)malloc((counter)*sizeof(T*));
        while (counter > 0){
            arr2[counter-1] = arr [counter-1];
            counter --;
        }
        free (arr);
        return arr2;
    }

    void smartInorderArrayAux (node<T>* r, T* arr[], int* counter , T* min , T* max) const {
        if (!r) {
            return;
        }
        if (*(r->data) > *(min) || *(r->data) == *(min)) {
            smartInorderArrayAux(r->left, arr, counter, min, max);
        }
        if ((*(r->data) < *(max) ||*(r->data) == *(max) ) && (*(r->data) > *(min) || *(r->data) == *(min))) {
            arr[*counter] = r->data;
            *counter = *counter + 1;
        }

        if (*(r->data) < *(max) ||*(r->data) == *(max)) {
            smartInorderArrayAux(r->right, arr, counter, min, max);
        }
    }

    void deleteLeafsFromRight (long long int numToDelete)
    {
        root = deleteLeafsFromRightAux(root, &numToDelete);
    }

    node<T>* deleteLeafsFromRightAux (node<T>* r, long long int* numToDelete)
    {
        if (!r)
        {
            return nullptr;
        }
        r->right = deleteLeafsFromRightAux (r->right, numToDelete);
        if (*numToDelete!=0 && (!(r->left) && !(r->right)))
        {
            r = deleteNode(r, nullptr);
            (*numToDelete)--;
            return nullptr;
        }
        if(*numToDelete==0)
        {
            return r;
        }
        r->left = deleteLeafsFromRightAux(r->left, numToDelete);
        r->height = calHeight(r);
        return r;
    }

    void fillEmptyTreeFromSortedArray (T** arr)
    {
        long long int counter=0;
        fillEmptyTreeFromSortedArrayAux(root, arr, &counter);
    }

    void fillEmptyTreeFromSortedArrayAux (node<T>* r, T* arr[], long long int* counter)
    {
        if (!r)
        {
            return;
        }
        fillEmptyTreeFromSortedArrayAux (r->left, arr , counter);
        if (*counter < size) {
            r->data = arr[*counter];
            *counter = *counter + 1;
            fillEmptyTreeFromSortedArrayAux(r->right, arr, counter);
        }
    }

    node<T>* deleteAllNodes(node<T>* r) {
        if(r== nullptr)
        {
            return nullptr;
        }
        node<T> *base = r;
        r = deleteAllNodesAux(base, r);
        deleteNode(r, nullptr);
        return nullptr;
    }

    node<T>* deleteAllNodesAux(node<T>* base, node<T>* r)
    {
        if (r== nullptr)
        {
            return nullptr;
        }                       //added condition
        if ((!(r->left) && !(r->right))) //changed condition
        {
            r = deleteNode(r, nullptr);
            return nullptr;
        }
        r->left = deleteAllNodesAux(base, r->left);
        r->right = deleteAllNodesAux(base, r->right);
        if ((!(r->left) && !(r->right)) && r!=base)
        {
            r = deleteNode(r, nullptr);
            return nullptr;
        }
        ///check if return here is ok
        return r;
    }

    node<T>* deleteTreeWithData(node<T>* r) {
        if(r == nullptr)
        {
            return nullptr;
        }
        node<T> *base = r;
        r = deleteTreeWithDataAux(base, r);
        delete r->data;
        return r;
    }

    node<T>* deleteTreeWithDataAux(node<T>* base, node<T>* r)
    {
        if (r== nullptr)
        {
            return nullptr;
        }
        if ((!(r->left) && !(r->right)) && r!=base)
        {
            r = deleteLeafWithData(r);
            return nullptr;
        }
        r->left = deleteTreeWithDataAux(base, r->left);
        r->right = deleteTreeWithDataAux(base, r->right);
        if ((!(r->left) && !(r->right)) && r!=base)
        {
            r = deleteLeafWithData(r);
            return nullptr;
        }
        ///check if return here is ok
        return r;
    }

    node<T>* deleteLeafWithData (node<T>* r)
    {
        if (r->data!= nullptr)
        {
            delete r->data;
        }
        delete r;
        size--;
        return nullptr;
    }

    ///////////rank tree functions

    node<T>* findMaxNode(T* data)
    {
        if (this->root == nullptr)
        {
            return nullptr;
        }
        auto to_return = new node<T>*;
        *(to_return) = nullptr;
        findMaxNodeAux(this->root , data , to_return);
        return  *(to_return);
    }
//finds maximum node with data
    void findMaxNodeAux (node<T>* r , T* data , node<T>** to_return )
    {
        if (r == nullptr)
        {
            return;
        }

        if (*(r->data) > *(data) )
        {
            *(to_return) = r;
            findMaxNodeAux(r->left,data,to_return);
        }

        else
        {
            findMaxNodeAux(r->right,data,to_return);
        }


    }
//find minumum node with data
    node<T>* findMinNode(T* data)
    {
        if (this->root == nullptr)
        {
            return nullptr;
        }
        auto to_return = new node<T>*;
        *(to_return) = nullptr;
        findMinNodeAux(this->root , data , to_return);
        return  *(to_return);
    }

    void findMinNodeAux (node<T>* r , T* data, node<T>** to_return)
    {
        if (r == nullptr)
        {
            return;
        }

        if (*(r->data) < *(data) )
        {
                *(to_return) = r;
                findMinNodeAux(r->right,data,to_return);
        }

        else
        {
            findMinNodeAux(r->left,data,to_return);
        }


    }
//find the rank of data (number of nodes smaller or equal)
    long long int findRank (T* data)
    {
        auto rank = new long long int (0);
        if(*(data) < *(this->smallest(this->root)->data))
        {
            return 0;
        }
        auto reqNode = findMaxNode(data);
        if (!reqNode)
        {
            return this->root->sonsNum;
        }
        findRankAux(this->root,reqNode->data, rank);
        long long int to_return = *rank;
        return to_return;
    }

    void findRankAux (node<T>* r,T* data, long long int* rank)
    {
        {
            if (r == nullptr)
            {
                return;
            }

            if (*(data) == *(r->data))
            {
                if (r->left) {
                    *(rank) = *(rank) + r->left->sonsNum;
                }
                else{
                    *(rank) = *(rank);
                }
                return;
            }

            else if (*(data) < *(r->data))
            {
                findRankAux(r->left,data,rank);
            }
            else if ((*(data) > *(r->data)))
            {
                if (r->left) {
                    *(rank) = *(rank) + r->left->sonsNum + 1;
                }
                else{
                    *(rank) = *(rank)+1;
                }
                findRankAux(r->right,data,rank);
            }
            return;
        }
    }
//find the element in index n
    node<T>* findRankedNode(long long int n)
    {
       return findRankedNodeAux(this->root, n);
    }

    node<T>* findRankedNodeAux(node<T>* r,long long int n)
    {
        long long int k =0;
        if (r->left)
        {
            k = r->left->sonsNum;
        }
        if (k == n-1)
        {
            return r;
        }
        else if (k> n-1)
        {
            return findRankedNodeAux(r->left,n);
        }
        else
        {
            return findRankedNodeAux(r->right,n-k-1);
        }
    }
//sum of grades below or equal data
    long long int findGradesBelow (T* data)
    {
        auto grades = new long long int (0);
        findGradesAux(this->root,data, grades);
        long long int to_return = *grades;
        return to_return;
    }

    void findGradesAux (node<T>* r,T* data, long long int* grades)
    {
        {
            if (r == nullptr)
            {
                return;
            }

            if (*(data) == *(r->data))
            {
                if (r->left) {
                    *(grades) = *(grades) + r->left->sonsGradesSum + r->grade;
                }
                else
                {
                    *(grades) = *(grades) + r->grade;
                }
                return;
            }

            else if (*(data) < *(r->data))
            {
                findGradesAux(r->left,data,grades);
            }
            else if ((*(data) > *(r->data)))
            {
                if (r->left) {
                    *(grades) = *(grades) + r->left->sonsGradesSum + r->grade;
                }
                else
                {
                    *(grades) = *(grades) + r->grade;
                }
                findGradesAux(r->right,data,grades);
            }
            return;
        }
    }

    long long int getGradesSum()
    {
        if (root) {
            return this->root->sonsGradesSum;
        }
        return 0;
    }
};

template<class T>
node<T>* createEmptyCompleteTreeAux (node<T>* r, long long int completeH)
{
    if(completeH==-1)
    {
        return nullptr;
    }
    r = new node<T>(nullptr,0);
    r->height=completeH;
    r->left = createEmptyCompleteTreeAux(r->left, completeH-1);
    r->right = createEmptyCompleteTreeAux(r->right, completeH-1);
    return r;
}


template<class T>
///gets pointer to tree - with no nodes
void createEmptyCompleteTree (AVLRankTree<T>* completeTree ,long long int completeH)
{
    completeTree->root = createEmptyCompleteTreeAux(completeTree->root, completeH);
    completeTree->size = exp2(completeH+1)-1;
}

template<class T>
///needs to get ptr to tree - with no nodes
void createEmptyNearlyCompleteTree (AVLRankTree<T>* emptyTree, long long int finalSize)
{
    long long int newH= ceil(log2(finalSize+1))-1;
    createEmptyCompleteTree<T>(emptyTree,newH);
    emptyTree->deleteLeafsFromRight(emptyTree->size - finalSize);
    emptyTree->size=finalSize;
}

template<class T>
void mergeArrays (T** arr1, T** arr2, T** destArr , long long int t1size, long long int t2size)
{
    T** p1=arr1;
    T** p2=arr2;
    T** pDest=destArr;
    long long int t1 = t1size;
    long long int t2 = t2size;
    while (t1 > 0 && t2 > 0)
    {
        if (*(*p1)<*(*p2) || *(*p1)==*(*p2))
        {
            *pDest=*p1;
            p1++;
            t1 -- ;
        }
        else
        {
            *pDest=*p2;
            p2++;
            t2 --;
        }
        pDest++;
    }
    while (t1 > 0)
    {
        *pDest=*p1;
        p1++;
        pDest++;
        t1--;

    }
    while (t2>0)
    {
        *pDest=*p2;
        p2++;
        pDest++;
        t2 -- ;
    }
}

template<class T>
void uniteTrees (AVLRankTree<T>* t1 , AVLRankTree<T>* t2, AVLRankTree<T>* destTree)
{
    T** arr1 = t1->inorderArray(t1->size);
    T** arr2 = t2->inorderArray(t2->size);
    T** uniteArr = (T**)malloc((t1->size + t2->size)*sizeof(T*));
    mergeArrays(arr1, arr2, uniteArr, t1->size,t2->size);
    createEmptyNearlyCompleteTree<T>(destTree,t1->size+t2->size);
    destTree->fillEmptyTreeFromSortedArray(uniteArr);
    free(arr1);
    free(arr2);
    free(uniteArr);
}

//void updateAllNodesAux(node<Employee>* r , AVLRankTree<Employee>* tree)
//{
//    if (!r)
//    {
//        return;
//    }
//    updateAllNodesAux(r->left , tree);
//    updateAllNodesAux(r->right , tree);
//    tree->updateSonsNum(r);
//    r->grade = r->data->getGrade();
//}
//
//
//void updateAllNodes(AVLRankTree<Employee>* tree)
//{
//    updateAllNodesAux(tree->root, tree);
//}






#endif //HW2_WET_AVLRANK_H
