#ifndef _BIN_SEARCH_TREE_H_
#define _BIN_SEARCH_TREE_H_

#include <functional>
#include <cstddef>
#include <stack>
#include <list>
#include <ostream>
//do not add any other library
//modify parts as directed by assignment text & comments here

template <typename Key, typename Object,
          typename Comparator=std::less<Key> >
class BinarySearchTree
{
  private: //do not change
    struct BinaryNode //node definition: a dependent type
    {
      Key key; //keys will be kept constant
      Object data; //objects that are referred to by keys may change
      BinaryNode * left;
      BinaryNode * right;
      size_t height; //height info should be updated per insert & delete

      BinaryNode(const Key &, const Object &,
                 BinaryNode *, BinaryNode *, size_t =0);
    };

  public: //do not change except for your own private utility functions
    class Iterator //iterator class will encapsulate the location within the BST
    {
      public:
        Iterator( ); //dummy constructor for type declaration purposes
        Iterator & operator++( ); //inorder increment

        Object & operator*( );  //update data
        const Object & operator*( ) const; //view data

        bool operator==(const Iterator & rhs) const; //compare iterators
        bool operator!=(const Iterator & rhs) const; //compare iterators

      private:
        BinaryNode * current; //position
        const BinaryNode * root; //for error check not implemented
        std::stack<BinaryNode *> s; //will be used to conduct in order traversal if
        bool useStack; //this variable is set to true, ignored in == and !=

      private:
        Iterator(BinaryNode *, const BinarySearchTree &, bool =true);
        //other private utility functions can be declared by you

      friend class BinarySearchTree<Key, Object, Comparator>;
    };

  public: //do not change
    BinarySearchTree( ); //empty tree
    ~BinarySearchTree( ); //reclaim all dyn allocated mem

    void insert(const Key &, const Object &); //to insert new key,item
    void remove(const Key &); //remove the node with the key value (and also data)

  public: //do not change
    Iterator find(const Key &) const; //single item
    std::list<Iterator> find(const Key &, const Key &) const;//range queries

    Iterator begin( ) const; //inorder begin
    Iterator end( ) const; //dummy NULL iterator

  public: //do not change
    int height( ) const; //return height of the tree
    size_t size( ) const; //return the number of items in the tree
    bool empty( ) const; //return whether the tree is empty or not
    void print(std::ostream &) const;

  private: //do not change
    BinaryNode * root; //designated root
    size_t nodes; //number of nodes
    Comparator isLessThan; //function object to compare keys

  private:
    /* private utility functions that are implemented */
    void makeEmpty(BinaryNode * &);

    BinaryNode * find(const Key &, BinaryNode *) const;
    int height(BinaryNode *) const;
    void print(BinaryNode *, std::ostream &) const;

    template <typename T> //static utility function
    static const T & max(const T &, const T &);

    //balancing functions
    void rotateWithLeftChild(BinaryNode * &);
    void rotateWithRightChild(BinaryNode * &);
    void doubleWithLeftChild(BinaryNode * &);
    void doubleWithRightChild(BinaryNode * &);

    //you may add your own private utility functions down here
    void insertfind(const Key & , const Object & , BinaryNode * & );
    void rebalance(std::stack<BinaryNode*> );
    std::stack<BinaryNode*> findremove(const Key &, BinaryNode* );
  private: //not copiable, DO NOT IMPLEMENT or change
    BinarySearchTree(const BinarySearchTree &);
    const BinarySearchTree & operator=(const BinarySearchTree &);
};

//node constructor, implemented do not change
template <typename K, typename O, typename C>
BinarySearchTree<K,O,C>::BinaryNode::
BinaryNode(const K & _k, const O & _d,
           BinaryNode * _l, BinaryNode * _r, size_t _h)
  : key(_k), data(_d), left(_l), right(_r), height(_h)
{
}

//default constructor, implemented do not change
template <typename K, typename O, typename C>
BinarySearchTree<K,O,C>::BinarySearchTree( )
  : root(NULL), nodes(0)
{
}

//destructor, implemented do not change
template <typename K, typename O, typename C>
BinarySearchTree<K,O,C>::~BinarySearchTree( )
{
  makeEmpty(root);
}

//private utility function for destructor, do not change
template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::makeEmpty(BinaryNode * & t)
{
  if (t != NULL)
  {
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
    --nodes;
  }

  t = NULL;
}

//public function to insert into BST, IMPLEMENT
template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::insert(const K & k, const O & x)
{
   insertfind(k,x,root);
}

//public function to remove key, IMPLEMENT
template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::remove(const K & k)
{
  std::stack<typename BinarySearchTree<K,O,C>::BinaryNode*> s = findremove(k,root);
  rebalance(s);

}

//public function to search elements, do not change
template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::Iterator
BinarySearchTree<K,O,C>::find(const K & key) const
{
  BinaryNode * node = find(key, root);

  if (node == NULL)
  {
    return end();
  }
  else
  {               //not inorder iterator
    return Iterator(node, *this, false);
  }
}

/*
 * private utility function to search elements
 * do not change
 */
template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::BinaryNode *
BinarySearchTree<K,O,C>::find(const K & key, BinaryNode * t) const
{
  if (t == NULL)
  {
    return NULL;
  }
  else if (isLessThan(key, t->key))
  {
    return find(key, t->left);
  }
  else if (isLessThan(t->key, key))
  {
    return find(key, t->right);
  }
  else //found
  {
    return t;
  }
}

//range queries those within range are inserted to the list
//IMPLEMENT
template <typename K, typename O, typename C>
std::list<typename BinarySearchTree<K,O,C>::Iterator>
BinarySearchTree<K,O,C>::find(const K & lower, const K & upper) const
{

  std::list <Iterator> lst;

  Iterator it =this->begin();

  for( it =this->begin() ; it != this->end(); ++it){
    if(it.current->key > upper){
        return lst;}
    //if( it.current->key >= lower && it.current->key <= upper){

     if( !isLessThan(it.current->key,lower ) && !isLessThan(upper,it.current->key) ){
      lst.push_back(it);

    }

  }

  return lst;
}

//INORDER iterator begins at ++root, do not change
template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::Iterator
BinarySearchTree<K,O,C>::begin() const
{
  return Iterator(root, *this);
}

//no more increment after end() also
//returned in case of unsuccessful search
//or when no more applicance of ++ is possible
//do not change
template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::Iterator
BinarySearchTree<K,O,C>::end() const
{
  return Iterator(NULL, *this);
}

//public function to return height, do not change
template <typename K, typename O, typename C>
int
BinarySearchTree<K,O,C>::height( ) const
{
  return height(root);
}

/* private utility function for computing height */
//do not change
template <typename K, typename O, typename C>
int
BinarySearchTree<K,O,C>::height(BinaryNode * t) const
{
  return (t == NULL) ? -1 : t->height;
}

//public function to return number of nodes in the tree
//do not change
template <typename K, typename O, typename C>
size_t
BinarySearchTree<K,O,C>::size( ) const
{
  return nodes;
}

//public true if empty false o.w.
//do not change
template <typename K, typename O, typename C>
bool
BinarySearchTree<K,O,C>::empty( ) const
{
  return nodes == 0;
}

//public function to print keys inorder to some ostream
//do not change
template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::print(std::ostream & out) const
{
  print(root, out);
  out << '\n';
}

/* private utility function to print, do not change */
template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::print(BinaryNode * t, std::ostream & out) const
{
  if (t != NULL && t->left != NULL)
  {
    out << '[';
    print( t->left, out );
  }
  else if (t != NULL && t->left == NULL && t->right != NULL)
  {
    out << "[";
  }

  if (t != NULL)
  {
    if (t->left == NULL && t->right == NULL)
    {
      out << '(' << (t->key) << ')';
    }
    else if (t->left != NULL || t->right != NULL)
    {
      out << '{' << (t->key) << ",H" << t->height << '}';
    }
  }

  if (t != NULL && t->right != NULL)
  {
    print( t->right, out );
    out << ']';
  }
  else if (t != NULL && t->left != NULL && t->right == NULL)
  {
    out << "]";
  }
}

/* static function to compute maximum of two elements */
//do not change
template <typename K, typename O, typename C>
template <typename T>
const T &
BinarySearchTree<K,O,C>::max(const T & el1, const T & el2)
{
  return el1 > el2 ? el1 : el2;
}

/* ROTATIONS, do not change */
template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::rotateWithLeftChild(BinaryNode * & k2)
{
  BinaryNode *k1 = k2->left;
  k2->left = k1->right;
  k1->right = k2;
  k2->height = BinarySearchTree<K,O,C>::max(height(k2->left),
                                            height(k2->right)) + 1;
  k1->height = BinarySearchTree<K,O,C>::max(height(k1->left),
                                            height(k2)) + 1;
  k2 = k1;
}

template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::rotateWithRightChild(BinaryNode * & k1)
{
  BinaryNode *k2 = k1->right;
  k1->right = k2->left;
  k2->left = k1;
  k1->height = BinarySearchTree<K,O,C>::max(height(k1->left),
                                            height(k1->right)) + 1;
  k2->height = BinarySearchTree<K,O,C>::max(height(k2->right),
                                            height(k1)) + 1;
  k1 = k2;
}

template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::doubleWithLeftChild(BinaryNode * & k3)
{
  rotateWithRightChild(k3->left);
  rotateWithLeftChild(k3);
}

template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::doubleWithRightChild(BinaryNode * & k1)
{
  rotateWithLeftChild(k1->right);
  rotateWithRightChild(k1);
}

/* ITERATOR functions */

// dummy constructor, do not change
template <typename K, typename O, typename C>
BinarySearchTree<K,O,C>::Iterator::Iterator( )
  : current(NULL), root(NULL), useStack(false)
{
}

// dereferencing operator non-const version, IMPLEMENT
template <typename K, typename O, typename C>
O &
BinarySearchTree<K,O,C>::Iterator::operator*( )
{return current->data;
}

// dereferencing operator const version, IMPLEMENT
template <typename K, typename O, typename C>
const O &
BinarySearchTree<K,O,C>::Iterator::operator*( ) const
{ return current->data;
}

// compare Iterators ignoring useStack var, do not change
template <typename K, typename O, typename C>
bool
BinarySearchTree<K,O,C>::Iterator::
operator==(const Iterator & rhs) const
{
  return current == rhs.current &&
         root == rhs.root;
}

// compare Iterators ignoring useStack var, do not change
template <typename K, typename O, typename C>
bool
BinarySearchTree<K,O,C>::Iterator::
operator!=(const Iterator & rhs) const
{
  return !(*this == rhs);
}

// increment Iterator to point to the inorder next
// node of then-current node, in case that no further
// advances are possible return an Iterator that is
// equal to end( ) , IMPLEMENT
template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::Iterator &
BinarySearchTree<K,O,C>::Iterator::operator++( )
{
  if(!useStack){
    
    current = NULL;
    return *this;
  }
  else if(current){
     if(current->right){
      current = current->right;
      BinaryNode*q = current;
      while(q->left){
        s.push(q);
        q=q->left;
      }
      current =q;
      return *this;
    }
    else{
      if(s.empty()){
        current=NULL;
        return *this;
      }
      else if(s.top()){
      current=s.top();
      s.pop();
      return *this;
      }
      else{
        current=NULL;
        return *this;
      }
    }
  }
    return *this;
}

/* real Iterator constructor will be invoked by
 * BST member function only. if no inorder iterator
 * is required by the computation designer should
 * explicitly set useStack variable to false, o.w.
 * it will be assumed to be true. IMPLEMENT
 */
template <typename K, typename O, typename C>
BinarySearchTree<K,O,C>::Iterator::
Iterator(BinaryNode * p, const BinarySearchTree & rhs, bool stk)
{
  useStack=stk;
  if(p ==NULL){
    root=rhs.root;
    current=NULL;
  }
  else if(stk){
  BinaryNode* q =p;
  root=rhs.root;
  while(q->left){
    s.push(q);
    q=q->left;
  }
  current = q;
 }
 else{
   current=p;
   root=rhs.root;
 }
}
template <typename K, typename O, typename C>
void BinarySearchTree<K,O,C>::insertfind(const K& key , const O & obj , BinaryNode * & p){
  if(p==NULL){

    p = new BinaryNode(key,obj,NULL,NULL);
    nodes++;

    return;
  }
  else if(isLessThan(key,p->key)){
    insertfind(key,obj,p->left);
    if(height(p->left)-height(p->right)==2){
      if( isLessThan(key,p->left->key) )
        rotateWithLeftChild(p);
      else
        doubleWithLeftChild(p);
    }
  }
  else if (isLessThan(p->key,key)){
    insertfind(key,obj,p->right);
    if (height(p->right)-height(p->left) == 2) {
      if (isLessThan(p->right->key,key)) {
        rotateWithRightChild(p);
      }
      else {
        doubleWithRightChild(p);
      }
    }
  }
  else;
  p->height = max(height(p->left),height(p->right))+1;
}
template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>:: rebalance(std::stack<BinaryNode *> s ){
  
  int flag=0;
  int popped=0;
  if(s.empty()){
    
    return;
  }
  else if(height(s.top()->left)-height(s.top()->right)==2 ){
    if(root==s.top()){
      flag=1;
    }
    if(height(s.top()->left->left) < height(s.top()->left->right) ){
      doubleWithLeftChild(s.top());
    }
    else{
    rotateWithLeftChild(s.top());
    }
    if(flag){
      root = s.top();
    }
    if(!s.empty()){
        BinaryNode* p = s.top();
        s.top()->height= max(height(s.top()->right),height(s.top()->left) ) +1;
        s.pop();
        popped=1;
        if(!s.empty() && isLessThan(p->key ,s.top()->key )  ){
            s.top()->left = p;
        }
        else if(!s.empty() && isLessThan(s.top()->key, p->key )  ){
            s.top()->right = p;
        }
    }
  }
  else if(height(s.top()->right)-height(s.top()->left)==2){
    if(root==s.top()){
      flag=1;
    }
    if(height(s.top()->right->right)<height(s.top()->right->left) ){
      
      doubleWithRightChild(s.top());

    }
    else{
    rotateWithRightChild(s.top());
    }
    if(flag){
      root = s.top();
    }
    if(!s.empty()){
        BinaryNode* p = s.top();
        s.top()->height= max(height(s.top()->right),height(s.top()->left) ) +1;
        s.pop();
        popped=1;
        if(!s.empty() && isLessThan(p->key,s.top()->key )  ){
            s.top()->left = p;
        }
        else if(!s.empty() && isLessThan(s.top()->key ,p->key ) ){
            s.top()->right = p;
        }
    }
    
}
  if(s.empty()){
    return;}
  s.top()->height= max(height(s.top()->right),height(s.top()->left) ) +1;

  if(!popped){
    s.pop();
  }
  rebalance(s);
}
template <typename K, typename O, typename C>
std::stack<typename BinarySearchTree<K,O,C>::BinaryNode*> BinarySearchTree<K,O,C>::findremove(const K & key, BinaryNode* t ){
    std::stack<typename BinarySearchTree<K,O,C>::BinaryNode*> s;
    char c;
    while(t ){
      if(isLessThan(t->key,key)){
        s.push(t);
        t=t->right;
        c='r';
    
      }
      else if(isLessThan(key ,t->key)){
        s.push(t);
        t=t->left;
        c='l';
        
      }
      else{
        if( !(t->right||t->left) ){ /*if leaf node*/
          
          if(!s.empty()){
            BinaryNode* prenode = s.top();
            if(c=='r'){
              prenode->right = NULL;
            }
            else if(c=='l'){
              prenode ->left = NULL;
            }
            prenode->height = max(height(prenode->left),height(prenode->right))+1;
            delete t;
          }
          else{
            delete t;
            root = NULL;
          }

          this->nodes--;
          return s;
        }
        else{
         
          BinaryNode * prenode;
          if(!s.empty()){
            prenode = s.top();
          }
          Iterator it = Iterator(t->right,*this,true);
          BinaryNode* q = t->right;


          while(q && q->left  && q->left->left ){
            q=q->left;
          }
        
          if(it.current && (it.current != q) ){
            q->left=it.current->right;
            
            it.current->right = t->right;
            it.current->left = t->left;
          }
          else if(it.current && it.current == q) {
            
              it.current->left = t->left;
          }
          else if(it.current == NULL){
            
            it = Iterator(t->left,*this,false);
          }
          if(q){
           q->height= max(height(q->left),height(q->right))+1;
          }
          if(c=='l'){
        
            prenode->left = it.current;
          }
          else if(c=='r'){
           
            prenode->right = it.current;
          }
          else{
            root = it.current;
            root->height = max(height(root->right),height(root->left))+1;
          }

          
          delete t;
          this->nodes--;
         it.current->height=max(height(it.current->right),height(it.current->left))+1;
          if(q){
          while(it.current != q->left){ //sildikten sonra currenttan q'ya kadar pushla
            
            s.push(it.current);
            if(isLessThan(it.current->key,q->key)){
                it.current=it.current->right;
            }
            else if(isLessThan(q->key,it.current->key)){
                it.current=it.current->left;
            }
            else{
                it.current = q->left;
            }
          }
        }
          return s;
        }
      }

    }
    return s;

}
#endif
