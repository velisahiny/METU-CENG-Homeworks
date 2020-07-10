#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Playlist.hpp"
#include "Entry.hpp"

using namespace std;


Playlist::Playlist()
{
    srand(15);
}

int Playlist::getRandomNumber(int i, int n) const
{
    int range=n-i;
    int random = rand() % range + i;
    return random;
}

void Playlist::print()
{
    cout << "[PLAYLIST SIZE=" << entries.getSize() <<"]";
    entries.print();
}
void Playlist::printHistory()
{
    cout<<"[HISTORY]";
    history.print();
}

/* TO-DO: method implementations below */
void Playlist::load(std::string fileName){
	ifstream file(fileName.c_str());
	string line;
	while(getline(file,line)){
		int index = line.find(";");
		string newtitle = line.substr(0,index);
		string genreyear = line.substr(index+1);
		index = genreyear.find(";");
		string newgenre = genreyear.substr(0,index);
		string newyear = genreyear.substr(index+1);
		Entry newEntry(newtitle,newgenre,newyear);
		insertEntry(newEntry);
	}
}
void Playlist::insertEntry(const Entry &e){
	entries.insertNode(entries.getTail(),e);
	HistoryRecord lastoper(INSERT,e);
	history.push(lastoper);
}
void Playlist::deleteEntry(const std::string &_title){
	Node<Entry>* ptr = entries.getHead();
	while(ptr->getData().getTitle() != _title){
		ptr=ptr->getNext();
	}
	Node<Entry>* prev(entries.findPrev(ptr->getData()));
	entries.deleteNode(prev);
	if(ptr){
		HistoryRecord lastoper(DELETE,ptr->getData());
		history.push(lastoper);
	}
}
void Playlist::moveLeft(const std::string &title){
	Node<Entry>* ptr = entries.getHead();

	while(!(ptr->getData().getTitle() == title)){
		ptr=ptr->getNext();
	}
	if(ptr==entries.getHead()){return;}

	Node<Entry>* prev1 = entries.findPrev(ptr->getData());
	Node<Entry>* prev2 = entries.findPrev(prev1->getData());
	if(prev2==NULL){
		prev1->setNext(ptr->getNext());
		ptr->setNext(prev1);
		entries.setHead(ptr);
	}
	else{
		prev1->setNext(ptr->getNext());
		prev2->setNext(ptr);
		ptr->setNext(prev1);
	}
}
void Playlist::moveRight(const std::string &title){
	Node<Entry>* ptr = entries.getHead();
	while(ptr->getData().getTitle() != title){
		ptr=ptr->getNext();
	}
	if(ptr==entries.getTail()){return;}
	else{
		moveLeft(ptr->getNext()->getData().getTitle());
	}
}
void Playlist::reverse() {
	MyStack<Entry> stackentry;
	Node<Entry>* ptr(entries.getHead());
	Entry headEntry(ptr->getData().getTitle(),ptr->getData().getGenre(),ptr->getData().getYear());
	stackentry.push(headEntry);
	ptr= ptr->getNext();
	while(ptr){
		Entry newEntry(ptr->getData().getTitle(),ptr->getData().getGenre(),ptr->getData().getYear());
		stackentry.push(newEntry);
		ptr=ptr->getNext();
	}
	entries.clear();
	entries.insertNode(NULL,stackentry.Top()->getData());
	stackentry.pop();
	ptr=(entries.getHead());
	while(!stackentry.isEmpty()){
		entries.insertNode(ptr,stackentry.Top()->getData());
		ptr=ptr->getNext();
		stackentry.pop();
	}
	HistoryRecord lastoper(REVERSE);
	history.push(lastoper);
}

void Playlist::sort(){
	Node<Entry>* ptr(entries.getHead());
	Node<Entry>* minimum=entries.getHead();
	Node<Entry>* unsorted=entries.getHead();
	for(int i=0; i<entries.getSize()-1;i++){
	    if(i){
	        minimum=minimum->getNext();
	    }
	    unsorted=minimum;
	    ptr=unsorted->getNext();
	    
		while(ptr){
           // cout<<ptr->getData().getTitle()<<minimum->getData().getTitle()<<endl;
			if(ptr->getData().getTitle().compare(minimum->getData().getTitle()) < 0){
				minimum = ptr;
			}
			ptr=ptr->getNext();
		}
		
		swap(unsorted,minimum);
	}
}
	    
	    
		
		/*string mintitle,mingenre,minyear,unstitle,unsgenre,unsyear;
		mintitle = minimum->getData().getTitle();
		mingenre = minimum->getData().getGenre();
		minyear = minimum->getData().getYear();
		unstitle = unsorted->getData().getTitle();
		unsgenre = unsorted->getData().getGenre();
		unsyear = unsorted->getData().getYear();
		
		Node<Entry>* unsprev = entries.findPrev(unsorted->getData());
		entries.deleteNode(unsprev);
		Entry newEntry(mintitle,mingenre,minyear);
		cout<<newEntry.getTitle()<<endl;
		entries.insertNode(unsprev,newEntry);
		
		Node<Entry>* minprev = entries.findPrev(minimum->getData());
		Entry newEntry2(unstitle,unsgenre,unsyear);
		cout<<newEntry2.getTitle()<<endl;;
		entries.deleteNode(minprev);
		entries.insertNode(minprev,newEntry2);
		
	
		ptr= unsprev->getNext()->getNext();
		
		cout<<"2"<<endl;*/
	
		
		
		
		
		
			//swap
			/*if(unsorted==minimum){
				minimum=minimum->getNext();
				ptr=minimum;
				continue;}
			 if (unsorted==entries.getHead()){entries.setHead(minimum);}
			
			Node<Entry>*tempuns = entries.findPrev(unsorted->getData());
			Node<Entry>* tempmin(minimum->getNext());
			if(ptr->getNext()==minimum){
			    moveLeft(minimum->getData().getTitle());
			    minimum=minimum->getNext();
			    ptr=minimum;
			}
			else if(!tempuns){
			    minimum->setNext(unsorted->getNext());
			    unsorted->setNext(tempmin);
			    entries.findPrev(minimum->getData())->setNext(unsorted);
			    minimum = minimum->getNext();
			    ptr= minimum;
			}
			else {
			    minimum->setNext(unsorted->getNext());
			    unsorted->setNext(tempmin);
			    entries.findPrev(minimum->getData())->setNext(unsorted);
			    tempuns->setNext(minimum);
			    minimum = minimum->getNext();
			    ptr= minimum;
			}*/
			

void Playlist::merge(const Playlist& pl){
	Node<Entry>* rhs_ptr(entries.getHead());
	Node<Entry>* lhs_ptr(pl.entries.getHead());
	while(rhs_ptr&&lhs_ptr){
		if(rhs_ptr->getData().getTitle() < lhs_ptr->getData().getTitle()){
			if(rhs_ptr->getNext()==NULL){
				while(lhs_ptr){
					entries.insertNode(rhs_ptr,lhs_ptr->getData());
					lhs_ptr=lhs_ptr->getNext();
				}
			}
			rhs_ptr=rhs_ptr->getNext();
		}
		else{
			if(rhs_ptr==entries.getHead()){
				entries.insertNode(NULL,lhs_ptr->getData());
				lhs_ptr=lhs_ptr->getNext();
			}
			else{
				entries.insertNode( entries.findPrev(rhs_ptr->getData()), lhs_ptr->getData() );
				lhs_ptr=lhs_ptr->getNext();
			}
		}
	}
	if(rhs_ptr){
	    return;
	}
	if(lhs_ptr){
	    while(lhs_ptr){
	        entries.insertNode(entries.getTail(),lhs_ptr->getData());
	        entries.setTail(entries.getTail()->getNext());
	        lhs_ptr=lhs_ptr->getNext();
	    }
	}
//pl.entries.clear()
}
void Playlist::shuffle(){
	for(int i=0;i<entries.getSize()-1;i++){
		int j= getRandomNumber(i,entries.getSize());
		Node<Entry>* j_ptr(entries.getHead());
		for(int jcount=0;jcount<j;jcount++){
			j_ptr=j_ptr->getNext();
		}
		Node<Entry>* i_ptr(entries.getHead());
		for(int icount=0;icount<i;icount++){
			i_ptr=i_ptr->getNext();
		}
		swap(i_ptr,j_ptr);
		/*
		Node<Entry>* i_tmp= i_ptr->getNext();
		Node<Entry>* j_tmp= j_ptr->getNext();
		Node<Entry>* i_prev= entries.findPrev(i_ptr->getData());
		Node<Entry>* j_prev= entries.findPrev(j_ptr->getData());
		if(i==0){
			j_ptr->setNext(i_tmp);
			i_ptr->setNext(j_tmp);
			j_prev->setNext(i_ptr);
			entries.setHead(j_ptr);
		}
		else if(j==0){
			i_ptr->setNext(j_tmp);
			j_ptr->setNext(i_tmp);
			i_prev->setNext(j_ptr);
			entries.setHead(i_ptr);
		}
		else{
			i_ptr->setNext(j_tmp);
			j_ptr->setNext(i_tmp);
			j_prev->setNext(i_ptr);
			i_prev->setNext(j_ptr);
		}
		if(j_ptr==entries.getTail()){
			entries.setTail(i_ptr);
		}
		else if(i_ptr==entries.getTail()){
			entries.setTail(j_ptr);
		}*/
	}
}

void Playlist::undo(){
	Operation c = history.Top()->getData().getOperation();
	switch (c) {
		case INSERT:
			deleteEntry(history.Top()->getData().getEntry().getTitle());
			history.pop();
			history.pop();
			break;
		case DELETE:
			insertEntry(history.Top()->getData().getEntry());
			history.pop();
			history.pop();
			break;
		case REVERSE:
			reverse();
			history.pop();
			history.pop();
			break;
	}
}
void Playlist::swap(Node<Entry>*x, Node<Entry>*y){
    if(x==y){
        return;
    }

        Node<Entry>* prevx= entries.findPrev(x->getData());
        Node<Entry>* prevy = entries.findPrev(y->getData());
        if(!(prevx==NULL)){
            prevx->setNext(y);
        }
        else{
            entries.setHead(y);
        }
        if(!(prevy==NULL)){
            prevy->setNext(x);
        }
        else{
            entries.setHead(x);
        }
        Node<Entry>* temp = y->getNext();
        y->setNext(x->getNext());
        x->setNext(temp);
        if(x->getNext()==NULL){
            entries.setTail(x);
        }
        if(y->getNext()==NULL){
            entries.setTail(y);
        }

}
