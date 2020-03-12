/*
 *  Yet another AVL tree edition
 * 
 *  Contributors:
 *      Aaron S. Crandall <acrandal@wsu.edu> - 2018
 * 
 */

#ifndef __AVLTree_H
#define __AVLTree_H

#include <ostream>
#include <algorithm>     // Includes a max(a,b) function
#include <exception>

#include "AVLNode.h"

// AVLTree class
// ******************PUBLIC OPERATIONS*********************
// bool empty( )          --> Test for empty tree
// int size( )            --> Quantity of elements in tree
// int height( )          --> Height of the tree (nullptr == -1)
// void add( x )          --> Insert new value x
// void remove( x )       --> Remove node with value x
// void clear ( )         --> Removes all elements from tree
// bool contains( x )     --> Return true if x is present
// T findMin( )           --> Return smallest item value
// T findMax( )           --> Return largest item value
// void printPreOrder( )  --> Print tree in pre order to an ostream
// void ~AVLTree( )       --> Big Five Destructor
// AVLTree( )             --> Basic constructor


template <typename T>
class AVLTree
{
private:
    AVLNode<T> * _root;

public:
    AVLTree() : _root(nullptr) {}    // initializes root to nullptr

    /* Returns true if the tree is empty */
    bool empty() {
        empty(_root);
        // TODO: Properly return t/f if the tree is empty or not
    }

    void add(const T & newVal) {
        // TODO: implement adding a value to the tree
        add(_root, newVal);
    }

    void remove(const T & remVal) {
        // TODO: Implemente properly removing a node and rebalancing the tree
         remove(remVal, _root);
    }

    void clear() {
        // TODO: Delete all elements in the tree
        makeEmptyHelper(_root);
    }

    bool contains(const T & findVal) {
        // TODO: Return t/f if a given value is currently in the tree
        return contains(findVal, _root);
    }

    int height() {
        return height(_root);
        // TODO: Return the current height of the tree
        // Remember! A null pointer is height -1
    }

    T findMin() {
        // Return the minimum *value* in the tree (not a tree node)
        return findMin(_root); // this is to allow the tests to fail - should definitely be changed!
    }

    T findMax() {
        // Return the maximum *value* in the tree (not a tree node)
        return findMax(_root); // this is to allow the tests to fail - should definitely be changed!
    }

    // Prints the tree to ostream out in preorder traversal
    void printPreOrder(std::ostream& out) {
        printPreOrder(this->_root, out);
    }

    int size() {
        return size(_root);
        // TODO: Return the size of the tree (number of nodes in the tree)
    }

// *************** Private /internal function implementation ******* //

private:
    // Should put your various internal balancing, rotating, and calculating functions here

    // Freebie: neat little function to safely get a node's height
    int height( AVLNode<T> * t ) const
    {
        return t == nullptr ? -1 : t->height;
    }

    // Traverses the tree and prints in pre order
    // This is used a lot in the testing system, changing it would be troublesome
    void printPreOrder(AVLNode<T> * & t, std::ostream& out)
    {
        if( t != nullptr )
        {
            out << t->val << " ";
            printPreOrder(t->left, out);
            printPreOrder(t->right, out);
        }
    }

    bool empty(AVLNode<T> *& t) {
        if(t == nullptr)
        {
            return true;
        }
        else{
        return false;}
        // TODO: Properly return t/f if the tree is empty or not
    }
    
    void remove (const T  & x, AVLNode<T> *& t)
    {
         if(t ==nullptr)
        {
            return;
        }
        
        if(x < t->val)
        {
            remove(x, t->left);
        }
        else if(t->val < x)
        {
            remove(x, t->right);
        }
        // else if(t->left ==NULL && t->right == NULL)
        // {
        //     delete t;
            
        // }
        //having 2 children
        else if(t->left != nullptr && t->right!=nullptr)
        {
            t->val = findMin(t->right);
            remove(t->val, t->right);
        }
        else//having 1 or 0 children
        {
            AVLNode<T>* oldNode = t;
            t =(t->left != nullptr)? t->left :t->right;
            delete oldNode;
            oldNode =nullptr;
        }
        
        if(t ==nullptr)
        {
            return;
        }
        //balance

       balance(t,x);
    }
     T findMin(AVLNode<T> *& t) {
        // Return the minimum *value* in the tree (not a tree node)
         if(t ==nullptr)
        {return (T)NULL;
        }
        else if(t->left == nullptr)
        {
            return t->val;
        }
       
        findMin(t->left);
        //return (T)NULL;
         // this is to allow the tests to fail - should definitely be changed!
    }

    T findMax(AVLNode<T> *& t) {
        /*
        if(t ==nullptr)
        {return (T)NULL;
        }
        else if(t->right == nullptr)
        {
            return t->val;
        }
       
        findMax(t->right);*/
        if(t ==nullptr)
        {return (T)NULL;
        }
        AVLNode<T>* current = t;
        while(current->right != nullptr)
        {
            current = current->right;
        }
        return current->val;
        // Return the maximum *value* in the tree (not a tree node)
        //return (T)NULL; // this is to allow the tests to fail - should definitely be changed!
    }

    bool contains(const T & findVal, AVLNode<T> *& t) {
        // TODO: Return t/f if a given value is currently in the tree
        if(t ==NULL)
        {
            return false;
        }
        if(t->val == findVal)
        {
            return true;
        }
        
        if(findVal < t->val)
        {
            contains(findVal, t->left);
        }
        else if(t->val < findVal)
        {
            contains(findVal, t->right);
        }
        
    }

    void makeEmptyHelper(AVLNode<T> *&t) {
        if( t != nullptr ) {
            makeEmptyHelper( t->left );
            makeEmptyHelper( t->right );
            delete t;
            t = nullptr;
        }
    }
    int size(AVLNode<T>* t) {
        if(t == nullptr)
        {
            return 0;
        }
        else{
           return( size(t->left) +1 + size(t->right));
            
            

        }
        // TODO: Return the size of the tree (number of nodes in the tree)
    }

    // get balance factor for node t
    int getBalance(AVLNode<T>*t)
    {
        if(t ==nullptr)
        {
            return 0;
        }
        return height(t->left) - height(t->right);
    }

    //single rotation for right (single left Rotate)
    void rotateWithleftChild(AVLNode<T> *& k2)
    {
        std::cout<<"Rotate withleft child: " << k2->val << std::endl;
        AVLNode<T> *k1 = k2->left;
        //AVLNode<T> *T2 = k1->right;
        //rotation
         
        k2->left = k1->right;
        k1->right = k2;
        
        //update height
        k2->height = max (height(k2->left), height(k2->right))+1;
        k1->height = max(height(k1->left), height(k1->right))+1;
        k2 =k1;
        
    }
    
    //single left Rotate
    void rotateWithRightChild(AVLNode<T> *& k1)
    {

        std::cout<<"Rotate with right child: " << k1->val << std::endl;
        AVLNode<T> *k2 = k1->right;
        //AVLNode<T> *T2 = k2->left;
        
        
        k1->right = k2->left;
        k2->left = k1;
        
        
        
        k1->height = max (height(k1->right), height(k1->left))+1;
        k2->height = max(height(k2->right), height(k2->left))+1;
        k1 =k2;
        
    }

    void doubleWithLeftChild(AVLNode<T>*& k3)//double left
    {
        rotateWithRightChild(k3->left);
        k3->height =  1 + max(height(k3->left),height(k3->right));
        rotateWithleftChild(k3);
    }
    void doubleWithRightChild(AVLNode<T>*& k1)//double right
    {
        rotateWithleftChild(k1->right);
        k1->height =  1 + max(height(k1->left),height(k1->right));
        rotateWithRightChild(k1);
    }
    void add( AVLNode<T>*& node, const T & newVal)
    {
        // perform normal BST insertion
        
        if(node == nullptr)
       {
           node = new AVLNode<T>(newVal);
           node->left = nullptr;
           node->right = nullptr;
           //node->val = newVal;
       }
    


       else if(node->val == newVal)
        {
            return;
        }
       
       else if(newVal < node->val)
       {
           add(node->left,newVal);
       }
       else if(newVal> node->val){
           add(node->right, newVal);
       }
       //node->height =  1 + max(height(node->left),height(node->right));
        
        balance(node,newVal);

    }

    void balance(AVLNode<T>*& node,const T & newVal)
    {
        if(node ==nullptr)
        {
            return;
        }
        //update height
        //node->height =  1 + max(height(node->left),height(node->right));


       

        //get balance
        int balance = getBalance(node);

        //left left case
        if(balance >1 && newVal < node->left->val)
        {
            rotateWithleftChild(node);
        }
        //right right case
        if(balance < -1 && newVal > node->right->val)
        {
            
             
             rotateWithRightChild(node);
        }
        // left righ case 
        if(balance > 1 && newVal >node->left->val )
        {
             
           
           doubleWithLeftChild(node);
        }
        //right left case
        if(balance <-1 && newVal < node->right->val)
        {
          
          doubleWithRightChild(node);
            
        }
        //update height
        node->height =  1 + max(height(node->left),height(node->right));
    }
    int max(int a , int b)
    {
        if(a>b)
        {return a;}
        else
        {
            return b;
        }
    }
    AVLNode<T>* minValueNode(AVLNode<T>* node)
    {
        AVLNode<T>* current = node;
        while(current->left != NULL)
        {
            current = current->left;
        }
        return current;
    }

};




#endif
