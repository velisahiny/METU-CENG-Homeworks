#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <iostream>
#include "Node.hpp"

using namespace std;

/*....DO NOT EDIT BELOW....*/
template <class T>
class LinkedList {
    private:
		/*First node of the linked-list*/
        Node<T>* head;
        /*Last node of the linked-list*/
		Node<T>* tail;
		/*size of the linked-list*/
		size_t  size;
    public:

        LinkedList();
        LinkedList(const LinkedList<T>& ll);
        LinkedList<T>& operator=(const LinkedList<T>& ll);
        ~LinkedList();

        /* Return head of the linked-list*/
        Node<T>* getHead() const;
        /* Set head of the linked-list*/
        void setHead(Node<T>* n);
        /* Return tail of the linked-list*/
        Node<T>* getTail() const;
        /* Set tail of the linked-list*/
        void setTail(Node<T>* n);
        /* Get the previous node of the node that contains the data item.
         * If the head node contains the data item, this method returns NULL.*/
        Node<T>* findPrev(const T& data) const;
        /* Get the node that stores the data item.
         * If data is not found in the list, this function returns NULL.*/
        Node<T>* findNode(const T& data) const;
        /* Insert a new node to store the data item.
         * The new node should be placed after the “prev” node.
         * If prev is NULL then insert new node to the head.*/
        void insertNode(Node<T>* prev, const T& data);
        /* This method is used to delete the node that is next to “prevNode”.
         * PS:prevNode is not the node to be deleted. */
        void deleteNode(Node<T>* prevNode);
        /* This method is used to clear the contents of the list.*/
        void clear();
        /* This method returns true if the list empty, otherwise returns false.*/
        bool isEmpty() const;
        /* This method returns the current size of the list. */
        size_t getSize() const;
        /*Prints the list. This method was already implemented. Do not modify.*/
        void print() const;
};

template <class T>
void LinkedList<T>::print() const{
    const Node<T>* node = head;
    while (node) {
        std::cout << node->getData();
        node = node->getNext();
    }
    std::cout<<std::endl;
}

/*....DO NOT EDIT ABOVE....*/

/* TO-DO: method implementations below */
template<class T>
LinkedList<T>::LinkedList(){
    head=NULL;
    tail=NULL;
    size = 0;

}
template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& ll){
      head = new Node<T>(ll.getHead()->getData());
      Node<T>* lhs_prev(head);
      Node<T>* rhs_ptr(ll.getHead()->getNext());
      while(rhs_ptr->getNext()){
  	Node<T>* newNode = new Node<T>(rhs_ptr->getData());
  	lhs_prev->setNext(newNode);
  	lhs_prev=lhs_prev->getNext();
  	rhs_ptr=rhs_ptr->getNext();
  	}
  	Node<T>* newNode = new Node<T>(rhs_ptr->getData());
  	lhs_prev->setNext(newNode);
  	this->tail= lhs_prev->getNext();

  size=ll.getSize();

}

template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& ll){
if(head == ll.getHead()){
    return *this;}
else{

    clear();

    head = new Node<T>(ll.getHead()->getData());
    Node<T>* lhs_prev(head);
    Node<T>* rhs_ptr(ll.getHead()->getNext());
    while(rhs_ptr->getNext()){
	Node<T>* newNode = new Node<T>(rhs_ptr->getData());
	lhs_prev->setNext(newNode);
	lhs_prev=lhs_prev->getNext();
	rhs_ptr=rhs_ptr->getNext();
	}

	Node<T>* newNode = new Node<T>(rhs_ptr->getData());
	lhs_prev->setNext(newNode);
	this->tail= lhs_prev->getNext();
	}
size=ll.getSize();


return *this;
}

template<class T>
LinkedList<T>::~LinkedList(){

  clear();
}

template<class T>
Node<T>* LinkedList<T>:: getHead() const{
  return head;
}
template<class T>
void LinkedList<T>:: setHead(Node<T>* n){
  head=n;
  return;
}
template<class T>
Node<T>* LinkedList<T>::getTail()const{
  return tail;
}
template<class T>
void LinkedList<T>::setTail(Node<T>* n){
  tail=n;
  return ;
}
template<class T>
Node<T>* LinkedList<T>::findPrev(const T& data) const{
  Node<T>* prev=NULL;
  Node<T>* current(head);
  if (!(current->getData()==data)){
  prev = current;
  current = current->getNext();
    while(current){
  	    if(current->getData()==data){return prev;}
	    prev=current;
	    current=current->getNext();
}
   }
 return NULL;
}
template<class T>
Node<T>* LinkedList<T>::findNode(const T& data) const{
  Node<T>* current(head);
  while(current){
    if(current->getData()==data){
        return current;
    }
    current=current->getNext();
  }
  return NULL;
}

template<class T>
void LinkedList<T>::insertNode(Node<T>* prev, const T& data){
  Node<T>* newNode = new Node<T>(data);
  newNode->setNext(NULL);
 if (prev==NULL){
    if(head == NULL){
      head = newNode;
      tail = newNode;
      size+=1;
      return;
    }
    newNode->setNext(head);
    head=newNode;
    size+=1;
    return;
 }
  newNode->setNext(prev->getNext());
  prev->setNext(newNode);
  size+=1;
  if (newNode->getNext()==NULL){tail=newNode;}
}

template<class T>
void LinkedList<T>::deleteNode(Node<T>* prevNode){
//if prev == NULL delete head
  if (prevNode==NULL){

	Node<T>* tmp(head);
	head = head->getNext();
    tmp->setNext(NULL);
	delete tmp;
  size -=1;
	return;
  }

  if (prevNode==tail){return;}

  // if prevNode->getNext == Tail do smt. else




  Node<T>* tmp(prevNode->getNext()->getNext());
  prevNode->getNext()->setNext(NULL);
  delete prevNode->getNext();

  prevNode->setNext(tmp);
  if(tmp==NULL){
    tail=prevNode;
  }
  size-=1;
}
template<class T>
void LinkedList<T>::clear(){
  if(head==NULL){return;}

  Node<T>* current(head);
  Node<T>* temp;
  while (current && current->getNext()){
    deleteNode(current);
  }
	deleteNode(NULL);
    head = NULL;
    tail=NULL;
}
template<class T>
bool LinkedList<T>::isEmpty() const{
 if(head==NULL){
  return 1;
}
  return 0;
}
template<class T>
size_t LinkedList<T>:: getSize() const{
return size;
}


/* end of your implementations*/

#endif
