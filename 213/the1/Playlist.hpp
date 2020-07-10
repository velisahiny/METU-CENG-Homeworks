#ifndef _PLAYLIST_H_
#define _PLAYLIST_H_

#include <string>
#include "LinkedList.hpp"
#include "Entry.hpp"
#include "HistoryRecord.hpp"
#include "MyStack.hpp"


class Playlist {
private:
	LinkedList<Entry> entries;
	MyStack< HistoryRecord > history;
	/* Generate a random integer such that i ≤ j < n */
	int getRandomNumber(int i, int n) const;
public:
	Playlist();
	/*load the list of playlist entries from the given file.*/
	void load(std::string fileName);
	/*Inserts a new entry to the end of playlist entries.
	 *For UNDO operation, you should save the insert operation.*/
	void insertEntry(const Entry &e);
	/*Deletes the entry with given title from the list.
	 *If the delete operation is successful (i.e. the entry with given title is in the playlist and deleted successfully)..
	 *you should save the this  operation for UNDO operation.*/
	void deleteEntry(const std::string &_title);
	/*Moves the entry with given title to the left.*/
	void moveLeft(const std::string &title);
	/*Moves the entry with given title to the right.*/
	void moveRight(const std::string &title);
	/*Reverse the playlist entries.*/
	void reverse();
	/*Sort the entries of the playlist from lowest to highest according to their “title”s.*/
	void sort();
	/*Merge the sorted lists while keeping the sort order*/
	void merge(const Playlist & pl);
	/*Shuffle the playlist entries. Use getRandomNumber function to generate a random number. */
	void shuffle();
	/*UNDO the the operations*/
	void undo();
	/*print the list entries. It is already implemented. DO NOT MODIFY*/
	void print();
	/*Prints the contents of the history stack from top to bottom.*/
	void printHistory();
    void swap(Node<Entry>* x, Node<Entry>* y);
};
/*void Playlist::load(std::string fileName){
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
		HistoryRecord lastoper(DELETE,*ptr);
		history.push(lastoper);
	}
}
void Playlist::moveLeft(const std::string &title){
	Node<Entry>* ptr = entries.getHead();

	while(ptr->getData().getTitle() != title){
		ptr=ptr->getNext();
	}
	if(ptr==entries.getHead()){return;}

	Node<Entry>* prev1 = findPrev(ptr->getData());
	Node<Entry>* prev2 = findPrev(prev1->getData());
	if(prev2==NULL){
		prev1->setNext(ptr->getNext());
		ptr->setNext(prev1);
		head= ptr;
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
	Node<Entry>* ptr = entries.getHead();
	Entry headEntry(ptr->getData().getTitle(),ptr->getData()->getGenre,ptr->getData->getYear());
	stackentry.push(headEntry);
	ptr= ptr->getNext();
	while(ptr){
		Entry newEntry(ptr->getData().getTitle(),ptr->getData()->getGenre,ptr->getData->getYear());
		stackentry.push(newEntry);
		ptr=ptr->getNext();
	}
	entries.clear();
	Node<Entry>* ptr(entries.getHead());
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
	Node<Entry>* minimum(entries.getHead());
	Node<Entry>* unsorted(entries.getHead());
	for(int i=0; i<entries.getSize()-1;i++){
		unsorted=minimum;
		while(ptr){
			if(ptr->getData()-getTitle() < minimum->getData().getTitle()){
				minimum= ptr;
			}
			else{
				ptr=ptr->getNext();
			}
		}
			//swap
			if(unsorted==minimum){
				minimum=minimum->getNext();
				ptr=minimum;
				continue;}
			 if (unsorted==entries.getHead()){entries.setHead(minimum);}
			Node<Entry>* tempmin(minimum->getNext());
			minimum->setNext(unsorted->getNext());
			unsorted->setNext(tempmin);
			entries.findPrev(minimum->getData())->setNext(unsorted);
			minimum = minimum->getNext();
			ptr= minimum;
		}
}
void Playlist::merge(const Playlist& pl){
	Node<Entry>* rhs_ptr(entries.getHead());
	Node<Entry>* lhs_ptr(pl.entries.getHead());
	while(rhs_ptr||lhs_ptr){
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
				entries.insertNode(entries.findPrev(rhs_ptr->getData()),lhs_ptr->getData());
				lhs_ptr=lhs_ptr->getNext();
			}
		}
	}
	pl.entries.clear();
}
void Playlist::shuffle(){
	for(int i=0;i<entries.getSize()-2;i++){
		int j= getRandomNumber(i,entries.getSize());
		Node<Entry>* j_ptr(entries.getHead());
		for(int jcount=0;j<j;j++){
			j_ptr=j_ptr->getNext();
		}
		Node<Entry>* i_ptr(entris.getHead());
		for(icount=0;icount<i;i++){
			i_ptr=i_ptr->getNext();
		}
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
			i_prev->setNext(j_ptr;
		}
		if(j_ptr==entries.getTail()){
			entries.setTail(i_ptr);
		}
		else if(i_ptr==entries.getTal()){
			entries.setTail(j_ptr);
		}
	}
}
void undo(){
	Operation c = history.Top().getOperation()==INSERT
	switch (c) {
		case INSERT:
			entries.deleteEntry(history.Top().getEntry().getTitle());
			break;
		case DELETE:
			entries.insertEntry(history.Top().getEntry());
			break;
		case REVERSE:
			entries.reverse();
			break;
	}
}
*/

#endif
