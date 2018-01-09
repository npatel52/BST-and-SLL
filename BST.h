#ifndef _BST_H_
#define _BST_H_
#pragma once
#include<iostream>
#include<stdexcept>
#include <iomanip>
#include "list.h"

template <typename T>

class BST: public List<T>{  
 private:
  struct Tree;
  Tree* root;
 public:
 BST(): root( 0 ){ };
 BST (const BST& obj); // copy constructor
 bool operator==(const BST& rhs); // equality operator
 void is_equal(Tree* rhs, Tree* lhs, bool& isequal);
 //BST ( BST&& other); // move constructor
 void make_copy(Tree* copyFrom, Tree*& copyTo);
 void print();
 void do_print(Tree* tree,std::string tabs);
 BST<T>& operator=( const BST<T>& obj);
 void insert( T value );
 void remove ( T value );
 bool contains ( T const value );
 bool do_contains( Tree* tree, T const value);
 unsigned int size();
 unsigned int rsize(Tree* const rt);
 unsigned int lsize(Tree* const lt);
 T* content_as_array();
 void do_content_as_array(Tree* tree, T*& arr);
 void fill_array(T*& arr, T const value, int repeated);
 inline bool is_empty(){ return root == 0; };
 inline bool is_empty( Tree* tree ) { return tree == 0; };
 inline bool is_empty_tree( Tree* tree ) { return (tree->rTree == 0 && tree->lTree == 0); };
 void recursiveDelete(Tree* tree, Tree* rootTree );
 void postorder(Tree* p, int indent);
 unsigned int leaf_count();
 unsigned int do_leaf_count(Tree* tree);
 unsigned int even_count( );
 unsigned int do_even_count( Tree* root );
 unsigned int getHeight();
 unsigned int do_getHeight( Tree* root, unsigned int count, unsigned int max);
 void delete_min();
 void do_delete_min( Tree* previous);
 T min_value();
 T do_min_value( Tree* root );
 T max_value();
 T do_max_value( Tree* root );
 void clear();
 void do_clear( Tree* tree);
 ~BST();
};

template <typename T>
struct
BST<T>::Tree{
  T data;
  int count;
  Tree* lTree;
  Tree* rTree;
 Tree(T value, int repeated = 1,  Tree* leftTree = 0, Tree* rightTree = 0):count( repeated ), data(value), lTree(leftTree), rTree(rightTree){};
  void do_remove(Tree*& parent, T const value);
  void do_left_replacement(Tree*& parent, Tree*& replacement);
  void do_right_replacement(Tree*& parent, Tree*& replacement);

};


/*************************************
 *************deleteMIN***************
 ************************************/
template <typename T>
void
BST<T>::delete_min(){
  if( root ){
    if( root->lTree ){
      do_delete_min( root );
    }else{
      Tree* tmp = root->rTree;
      delete root;
      root = tmp;
    }
  }
}

template <typename T>
void
BST<T>::do_delete_min( Tree* previous ){
  if(previous->lTree->lTree){
    do_delete_min( previous->lTree );
  }else{
    Tree* tmp = previous->lTree->rTree; // store rTree ( may have some value or may be null)
    delete previous->lTree; // delete min value;
    previous->lTree = tmp; // may be null or the right sub tree
  }

}

/*************************************
 ************* MIN & MAX ************
 ************************************/
template <typename T>
unsigned int
BST<T>::getHeight(){
  if( root )
    return do_getHeight( root, 0, 0);
  return 0;
}

template <typename T>
unsigned int
BST<T>::do_getHeight( Tree* root, unsigned int count, unsigned int max){
  if( !root->lTree && !root->rTree ) // at leaf node
    return count > max ? count : max;
  
  if( root->lTree )
    max = do_getHeight( root->lTree, count + 1, max );

  if( root->rTree )
    max = do_getHeight( root->rTree, count + 1, max );

  return max;
}

  

/*************************************
 ************* MIN & MAX ************
 ************************************/
template <typename T>
T
BST<T>::min_value(){
  if( root )
    return do_min_value( root );
  else
    throw std::runtime_error("min_value(): BST is empty!");
}

template <typename T>
T
BST<T>::do_min_value( Tree* root){
  if(root->lTree)
    return do_min_value( root->lTree );
  return root->data;
}


template <typename T>
T
BST<T>::max_value(){
  if( root )
    return do_max_value( root );
  else
    throw std::runtime_error("min_value(): BST is empty!");
}

template <typename T>
T
BST<T>::do_max_value( Tree* root ){
  if(root->rTree)
    return do_max_value( root->rTree );
  return root->data;
}

/**************************************
 **************evenCount***************
 ***************************************/
template <typename T>
unsigned int
BST<T>::even_count( ){
  if(root)
    return do_even_count( root );

  return 0;
}

template <typename T>
unsigned int
BST<T>::do_even_count( Tree* root ){
  unsigned int count = 0;
  
  if(!(root->data & 1)) // not odd  .......0 & 000000001 yields 0 so !0 for even
      ++count;
  
  if( root ){
    if(root->lTree)
      count += do_even_count( root->lTree );

    if(root->rTree)
      count += do_even_count( root->rTree );
  }
  return count;

}

/****************************************
 *****************print**************
 ***************************************/
template <typename T>
void
BST<T>::print(){

  if(root){
    std::string str;
    do_print(root, str);
  }
}

template <typename T>
void
BST<T>::do_print(Tree* tree, std::string tabs){
  if(tree){
    

    if(tree->rTree) // Go all the way right first
      do_print( tree->rTree , tabs + "\t");

    // Printing
    if(!tree->rTree){
       std::cout<< tabs << "\t[ ]\n\n"; // Print empty node, Go to next line
    }
    
    std::cout<< tabs << "[ " << tree->data << " : " << tree->count << " ]" <<"\n" << std::endl; // Go to next line

    if(!tree->lTree){
       std::cout<< tabs << "\t[ ]\n\n"; // Print empty node, Go to next line
    }
    
    if(tree->lTree) // Go left afterwards
      do_print( tree->lTree, tabs + "\t" );
  }
}







/*******************************
 ************operator== ********
 ******************************/
/*template <typename T>
bool
BST<T>::operator!=(const BST& rhs){ // the two arguments is reference to the obj to compare
  bool isequal = true;
  is_equal(this->root, rhs.root, isequal);
  return !isequal;
}

template <typename T>
bool
BST<T>::operator==(const BST& rhs){ // the two arguments is reference to the obj to compare
  bool isequal = true;
  is_equal(this->root, rhs.root, isequal);
  return isequal;
}
*/
template <typename T>
void
BST<T>::is_equal(Tree* lhs, Tree* rhs, bool& isequal){
  
  if(lhs && rhs){ // both has to non-nullptr to compare values
    
    if(lhs->data == rhs->data && lhs->count == rhs->count){ // check for equality of data and instances

      if( lhs->rTree){
	is_equal(lhs->rTree, rhs->rTree, isequal);
      }

      if( lhs->lTree ){
	is_equal(lhs->lTree, rhs->lTree, isequal);
      }
    }else{
      isequal = false;
      return;
    }
  }else if(lhs || rhs){ // one of them is nullptr and one is not
    isequal = false;
    return;
  }
  
}

/********************
 *****leaf-count****
 ******************/

template <typename T>
unsigned int
BST<T>::leaf_count(){
  if(root)
    return do_leaf_count(root);
  return 0;
}

template <typename T>
unsigned int
BST<T>::do_leaf_count(Tree* tree){
  unsigned int count = 0u;
  if(tree){
    if( tree->lTree)
      count += do_leaf_count( tree->lTree);
    if( !tree->lTree && !tree->rTree){
      ++count;
      return count;
    }
    if( tree->rTree )
      count += do_leaf_count( tree->rTree ); 
  } 
  return count;
}

/*************************************
 ****************operator=************
 ***********************************/
template <typename T>
BST<T>&
BST<T>::operator=( const BST<T>& obj){
  // Check for self-assignment
  if(this != &obj){
    this->clear();
    make_copy(obj.root, this->root);
  }
  
  return *this;
}

/***********************************
***************move-constructor***
*********************************/
/*
template <typename T>
BST<T>::BST( BST&& other){
  // steal from other
  root = other.root;

  // destruct other
  other.root = 0;

}
*/


template <typename T>
void
BST<T>::insert( T value ) {

  // CASE 0: No tree exist then create one
  if( is_empty() ){
    root = new Tree(value);
    std::cout<< "Inserted in root: " << value << std::endl;
  }else{
    // tmp pointer to tree for traversal 
    Tree* tmp = root;
    while(!is_empty(tmp)){
       // CASE 1: if insertion value is greater than root's data 
      if( value > tmp->data){
	// If the right tree is empty then allocat a new Tree with a value
	if(is_empty( tmp->rTree )){
	  tmp->rTree = new Tree( value );
	  // Insertion happened!
	  std::cout<< "Inserted in rTree: " << value << std::endl;
	  return;
	}else{
	  tmp = tmp->rTree;
	}
      }
      // CASE 2: if insertion value is smaller than root's data
      else if( value < tmp->data ){
	// if left Tree is empty then allocate new Tree with a value
	if( is_empty( tmp-> lTree) ){
	  tmp->lTree = new Tree( value );
	  // Insertion happened!
	  std::cout<< "Inserted in lTree: " << value << std::endl;
	  return;
	}else{
	  tmp = tmp->lTree;
	}
      }
      // CASE 3: the value must have been equal to root's data
      else{
	// No insertion needed! Only update count.
	tmp->count += 1;
	return;
      }
    }
  }

}

/**************************************
 **********copy constructor************
 *************************************/
template <typename T>
BST<T>::BST(const BST& obj){
 if(obj.root){
   root = 0;
   make_copy(obj.root, root);
 }else{
   root = 0;
 }
}

template <typename T>
void
BST<T>::make_copy(Tree* copyFrom, Tree*& copyTo){
  
  if(copyFrom){
    copyTo = new Tree(copyFrom->data, copyFrom->count);
    if(copyFrom->rTree){
      make_copy(copyFrom->rTree, copyTo->rTree);
    }
    if(copyFrom->lTree){
      make_copy( copyFrom->lTree, copyTo->lTree);
    }
  }
}


template <typename T>
unsigned int
BST<T>::rsize(Tree* const rt){
  // Base Case: if no tree exist
  if(!rt)
    return 0;
  // Recursive step: there is a tree so, find the size of the tree and find the size of the right tree
  // rt->count for counting duplictes
  return rt->count + lsize(rt->lTree) + rsize(rt->rTree);
}

template <typename T>
unsigned int
BST<T>::lsize(Tree* const lt){
  // Base Case: if no tree exist
  if(!lt)
    return 0;
  // Recursive step: there is a tree so, find the size of the left tree and size of the right tree
  return lt->count + lsize(lt->lTree) + rsize(lt->rTree);
}

template <typename T>
unsigned int
BST<T>::size(){
  // Base Case: there is no tree
  if(!root)
    return 0;
  // Recursive step: There is a tree then find size of the left tree and size of the right tree
  return root->count + rsize(root->rTree) + lsize(root->lTree); 
}

template <typename T>
void
BST<T>::do_clear(Tree* const tree){

  if(tree->rTree)
    do_clear(tree->rTree);
    // When the tree has no child
  std::cout<< "Deleting tree with data: " << tree->data << std::endl;
  delete tree;
  
  if(tree->lTree)
    do_clear(tree->lTree);


  return;
}


/********************************
 ***************print()**********
 ********************************/
template <typename T>
void
BST<T>::postorder(Tree* p, int indent){
    if(p != NULL) {
        if(p->lTree) postorder(p->lTree, indent+4);
        if(p->rTree) postorder(p->rTree, indent+4);
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
	std::cout<< p->data << "\n ";
    }
}


template <typename T>
void
BST<T>::clear(){
  if(root)
    do_clear(root);
  return;
}

template <typename T>
void
BST<T>::recursiveDelete(Tree* prevTree, Tree* current){
  // If root is empty
  if(is_empty(prevTree)){
    delete prevTree;
    return;
  }

  // If tree has leaf node
  if(is_empty_tree(prevTree)){
    std::cout<< "All Deleted : " << current->data << std::endl;
    delete prevTree;
    prevTree = 0;
    return;
  }  

  // if lead node reached
  if(is_empty_tree( current )){
  	std::cout<< "Deleted : " << current->data << std::endl;
    delete current;
    // when rigt rootTree is already empty
    if(!prevTree->rTree){
      prevTree->lTree = 0;
    }else{
      prevTree->rTree = 0;
    }
    return;
  }

  // if the current tree has more roots on right
  if(current->rTree){
    recursiveDelete( current, current->rTree);
  }

  // if current didn't had more tree on right, go on left to check for more tree
  if(current->lTree){
    recursiveDelete ( current, current->lTree);
  }
  
  recursiveDelete ( prevTree, current);
}


template <typename T>
bool
BST<T>::contains ( T const value ){
   return do_contains(root, value);
}

template <typename T>
bool
BST<T>::do_contains ( Tree* tree, T const value ){
  // Base Case: nullptr reached! value not found!
  if(!tree){
    return false;
  }
	
  // Match found
  if(tree->data == value){
    return true;
  }
	
  // Value is greater than current tree's value
  // Go right
  if( value > tree->data){
    return do_contains(tree->rTree, value);
  }

  // Value is less than current tree's value
  // Go left
  return do_contains(tree->lTree, value);
}

template <typename T>
void
BST<T>::fill_array(T*& tmp, T const value, int repeated){
  if(repeated){
    *tmp = value;
    ++tmp;
    fill_array(tmp, value, repeated - 1); 
  }
}

template <typename T>
void
BST<T>::do_content_as_array(Tree* tree, T*& arr){
  // Go all the way left to get smallest value
  if(tree->lTree)
    do_content_as_array(tree->lTree, arr);

  // fill the array the number of times it is repeated
    fill_array(arr, tree->data, tree->count);
    
  // Now, check for right tree for larger value
  if(tree->rTree)
    do_content_as_array(tree->rTree, arr);

  return;
}

template <typename T>
T*
BST<T>::content_as_array(){
  // Dynamically allocating size for an array 
  T* arr = new T[size()];
  T* result = arr;
  if(!is_empty(root)){
    do_content_as_array(root, result);
  }
  
  return arr;
}


template <typename T>
void
BST<T>::remove(T value){

  if(root)
    root->do_remove(root, value );
   else
    throw std::runtime_error("remove( value ) => No such value in Tree");  
}

// Find if there is such a value in Tree
template <typename T>
void
BST<T>::Tree::do_remove(Tree*& parent, T const value){
  
  if(value == data){ // match found
    if(--count == 0){ // update count

      // Call for replacement
      if(lTree){
	Tree* replacement = parent;
	lTree->do_left_replacement(parent, replacement);
      }else if(rTree){
	Tree* replacement = parent;
	rTree->do_right_replacement(parent, replacement);
      }else{ // leaf Node
	delete parent;
	parent = 0;
      }
      return;
      
    }else{
      //count more than one, No deletion required!
      return;
    }   
  }
  
  
  if ( value < data ){ // check left
    if(!lTree){ 
      throw std::runtime_error("remove( value ) => No such value in Tree ");  
    }
    lTree->do_remove(lTree, value );
  }else if( value > data ) { // check right
     if(!rTree){ 
     throw std::runtime_error("remove( value ) => No such value in Tree ");  
    }
    rTree->do_remove(rTree, value );
  }
  
}


template <typename T>
void
BST<T>::Tree::do_left_replacement(Tree*& parent, Tree*& replacement){

  // Finding the right-most child
  if(rTree){
    if( parent != replacement){
      replacement = rTree;
      rTree->do_left_replacement( parent, replacement);
    }else{
      replacement = parent->lTree; 
      rTree->do_left_replacement( parent, replacement);
    }
  }else{
    parent->data = data;
    parent->count = 1;

    if(parent == replacement){
      parent->lTree = lTree;
      delete replacement->lTree;
    }
    else{
      if(lTree){
	Tree* tmp = replacement->lTree;
	delete replacement->rTree;
	replacement->rTree = tmp;
      }
      else{
	delete replacement->rTree;
	replacement->rTree = 0;
      }
    }
  }
}

template <typename T>
void
BST<T>::Tree::do_right_replacement(Tree*& parent, Tree*& replacement){

  // Find left-most
  if(lTree){
    if( parent != replacement){
      replacement = lTree;
      rTree->do_right_replacement( parent, replacement);
    }else{
      replacement = parent->rTree; 
      rTree->do_right_replacement( parent, replacement);
    }
  }else{
    parent->data = data;
    parent->count = 1;

    if(parent == replacement){
      parent->rTree = rTree;
      delete replacement->lTree;
    }
    else{
      if(rTree){
	Tree* tmp = replacement->rTree;
	delete replacement->lTree;
	replacement->lTree = tmp;
      }
      else{
	delete replacement->lTree;
	replacement->lTree = 0;
      }
    }
  }
}


template <typename T>
BST<T>::~BST(){
  postorder(root ,0 );
  clear();
}

#endif
