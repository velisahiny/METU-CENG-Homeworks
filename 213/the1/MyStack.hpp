#ifndef MYSTACK_HPP
#define MYSTACK_HPP
#include "Node.hpp"

/*You are free to add private/public members inside this template..*/
template <class T>
class MyStack{
    private:
    Node<T> *top;
    public:
    /*Default constructor*/
    MyStack();
    /*copy constructor*/
    MyStack(const MyStack<T>& rhs);
    /*destructor*/
    ~MyStack();
    /*overloaded = operator*/
    MyStack<T>& operator=(const MyStack<T>& rhs);
    /*returns true if stack is empty*/
    bool isEmpty() const;
    /*push newItem to stack*/
    void push(const T& newItem);
    /*pop item from stack*/
    void pop();
    /*return top item of the stack*/
    Node<T>* Top() const;
	/*Prints the stack entries. This method was already implemented. Do not modify.*/
    void print() const;
};

template <class T>
void MyStack<T>::print() const{
    const Node<T>* node = top;
    while (node) {
        std::cout << node->getData();
        node = node->getNext();
    }
    cout<<std::endl;
}

/* TO-DO: method implementations below */
//Default constructor
template <class T>
MyStack<T>::MyStack(){
  top = NULL;
}
template<class T>
bool MyStack<T>::isEmpty() const {
  if (top==NULL){return 1;}

    return 0;
}
//copy constructor
template <class T>
MyStack<T>::MyStack(const MyStack<T>& rhs){

    if(!rhs.Top()){   //if rhs is empty
      top = NULL;
   }
   else{

     top = new Node<T>(rhs.Top()->getData());

     Node<T>* rhs_ptr = rhs.Top()->getNext();

     Node<T>* lhs_ptr = top;

     while(rhs_ptr){

       Node<T>* newNode = new Node<T>(rhs_ptr->getData());
       lhs_ptr->setNext(newNode);
       rhs_ptr=rhs_ptr->getNext();
       lhs_ptr=lhs_ptr->getNext();
     }

     lhs_ptr->setNext(NULL);
   }

  }
//assignment
template <class T>
MyStack<T>& MyStack<T>:: operator=(const MyStack<T>& rhs){
  if(top != rhs.Top()){  //if not assigned to itself
    while(!isEmpty()) {pop();} //delete former elements of lhs
    if(!rhs.Top()){               //if rhs is empty
      top = NULL;
   }
   else{
     top = new Node<T>(rhs.Top()->getData());
     Node<T>* rhs_ptr = rhs.Top()->getNext();
     Node<T>* lhs_ptr = top;
     while(rhs_ptr){
       Node<T>* newNode=new Node<T>(rhs_ptr->getData());
       lhs_ptr->setNext(newNode);
       rhs_ptr=rhs_ptr->getNext();
       lhs_ptr=lhs_ptr->getNext();
     }
     lhs_ptr->setNext(NULL);
   }
  }
  return *this;
}
//destructor
template<class T>
MyStack<T>::~MyStack(){
  while(top){
    pop();
  }
  delete top;
}
template<class T>
void MyStack<T>::push(const T& newItem){
  Node<T>* newNode=new Node<T>(newItem);
  newNode->setNext(top);
  top=newNode;
}
template<class T>
void MyStack<T>::pop(){
  if(isEmpty()){return;}
  Node<T>* tmp(top);
  top=top->getNext();
  delete tmp;
}
template<class T>
Node<T>* MyStack<T>:: Top() const{
  return top;
}



#endif /* MYSTACK_HPP */
