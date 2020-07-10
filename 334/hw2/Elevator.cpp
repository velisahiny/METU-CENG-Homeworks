#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include "monitor.h"
using namespace std;
#define HP 1 
#define LP 2
void waitMicroSeconds(int microseconds){
    usleep(microseconds);
};
enum State {IDLE,MOVING_UP, MOVING_DOWN};
class Person {
    public:
        int personID;
        int weight, initial_floor, destination_floor,priority;
        Person(){}
        Person(int id, int WP,int IF,int DF,int P){
            personID=id;
            weight= WP; 
            initial_floor=IF; 
            destination_floor=DF;
            priority=P;
        };
        void printPerson(){
            cout<<"weight: "<<weight<<" ";
            cout<<"initial Floor : "<< initial_floor<<" ";
            cout<<"destination floor: "<< destination_floor<<" ";
            cout<<"priority: "<< priority<<"\n";
        }
        ~Person(){}
};

class Elevator : public  Monitor{
    private:
        int numFloors;
        int personCapacity;
        int weightCapacity;
        int currentPeople;
        int currentWeight;
        int numActivePeople;
        vector<int> floorPerson;
        State state;
        int currentFloor; 
        Condition stopped, allowLP, canLeave,canRequest,personLeft,allTriedToEnter;
        set<int> destQueue;
        vector<Person> enteredPeople;
        vector<int> requestedPeople;
        int requestCount;
    public :
        int travelTime;
        int idleTime;
        int inOutTime;
        Elevator(vector<int> arguments): stopped(this), allowLP(this),canLeave(this),canRequest(this),personLeft(this), allTriedToEnter(this)  {
            //vector<int> arguments=vector<int>{numFloors, numPeople, weight_capacity, person_capacity, travelTime, idleTime, inOutTime};
            numFloors=arguments[0];
            numActivePeople=arguments[1];
            weightCapacity=arguments[2];
            personCapacity=arguments[3];
            travelTime=arguments[4];
            idleTime=arguments[5];
            inOutTime=arguments[6];
            floorPerson=vector<int>(numFloors);
            state=IDLE;
            currentFloor=0;
            destQueue=set<int>();
            currentPeople=0;
            currentWeight=0;
            enteredPeople=vector<Person>();
            requestedPeople=vector<int>(numFloors);
            requestCount=0;
        }
        void newPerson(Person& person ){
            __synchronized__;
            State direction;
            int initial=person.initial_floor;
            int dest=person.destination_floor;
            bool eligible=false;
            if( initial<dest){
                direction= MOVING_UP;
            }
            else {
                direction=MOVING_DOWN;
            }
            while(!eligible){
                if(state==IDLE || direction==state){
                    eligible=true;
                    if(state==MOVING_DOWN){
                        if(initial> currentFloor){
                            eligible=false;
                         //   cout<<person.personID<<" moving down initial>currentFloor\n";
                        }
                    }
                    else if(state==MOVING_UP){
                        if(initial < currentFloor){
                            eligible=false;
                         //   cout<<person.personID<<" moving up initial<currentFloor\n";
                        }
                    }
                }
                if(eligible){
                    request(person);//requested
                    requestCount++;
                    bool waited=false;
                    while(currentFloor!=initial){//wait until it comes to initial
                       // cout<<person.personID<<" waiting stopped\n";
                        stopped.wait();
                        waited=true;
                      //  cout<<person.personID<<" get stopped\n";
                    }
                    if(waited){
                        pretendRequest(person);
                    }
                    //elevator is at my floor
                    bool entered=enter(person);
                    if(requestedPeople[currentFloor]==0){
                        allTriedToEnter.notify();
                    }
                    if(entered){//try to enter
                        destQueue.erase(person.initial_floor);
                        destQueue.insert(person.destination_floor);
                        printEntered(person);
                        printElevator();
                        while(currentFloor!=person.destination_floor){
                         //   cout<<"Person "<<person.personID<<" waiting canLeave\n";
                            canLeave.wait();
                         //   cout<<"Person "<<person.personID<<" got canLeave\n";
                        }
                       // cout<<person.personID<<"leaves\n";
                        leave(person);
                        return;
                    }else{ //if cannot enter
                      //  cout<<person.personID<<"couldn't enter\n";
                        eligible=false;
                    }
                    requestCount--; 
                }
                else{
                    //cout<<"eligible==false for person: "<<person.personID<<"\n";
                    canRequest.wait();
                }
                if(currentFloor==person.initial_floor){
                //        cout<<person.personID<<" waiting here\n";
                        canRequest.wait();
                //        cout<<person.personID<<" not waiting anymore floor is: "<<currentFloor<<"\n";
                }

            }
        }
        void pretendRequest(Person &person){
            if(state==IDLE){
                if(person.initial_floor<currentFloor){ 
                   state=MOVING_DOWN;
                }
                else if(person.initial_floor>currentFloor){
                    state=MOVING_UP;
                }
                else{//initial==currentFloor then it will enter
                    if(person.destination_floor>currentFloor){
                       state=MOVING_UP; 
                    }
                    else{//dest<current
                        state=MOVING_DOWN;
                    }
                }
            } 
            printRequested(person);
            printElevator();
        }
        void request(Person& person){
            if(person.priority==HP){
                floorPerson[person.initial_floor]++;
            }
            if(person.initial_floor!=currentFloor){
                destQueue.insert(person.initial_floor);
            }
            if(state==IDLE){
                if(person.initial_floor<currentFloor){ 
                   state=MOVING_DOWN;
                }
                else if(person.initial_floor>currentFloor){
                    state=MOVING_UP;
                }
                else{//initial==currentFloor then it will enter
                    if(person.destination_floor>currentFloor){
                       state=MOVING_UP; 
                    }
                    else{//dest<current
                        state=MOVING_DOWN;
                    }
                }
            }
            requestedPeople[person.initial_floor]++;
            printRequested(person);
            printElevator();
        }
        bool enter(Person& person){
        //    cout<<person.personID<<" trying to enter\n";
            State direction;
            requestedPeople[person.initial_floor]--;
            if(person.destination_floor>currentFloor){
                direction=MOVING_UP;
            }
            else if(person.destination_floor<currentFloor){
                direction=MOVING_DOWN;
            }
            if(state==IDLE || direction==state){
                if(person.priority==LP){//low priority tries to enter
                    while(floorPerson[person.initial_floor]!=0){//wait all high priority person to signal
                        allowLP.wait();
                    }
                    if(currentPeople+1 <= personCapacity && currentWeight+person.weight<=weightCapacity){
                        enteredPeople.push_back(person);
                        currentPeople++;
                        currentWeight+=person.weight;
                        if(state==IDLE){
                            if(person.destination_floor<currentFloor){ 
                                state=MOVING_DOWN;
                            }
                            else if(person.destination_floor>currentFloor){
                                state=MOVING_UP;
                            }
                        }
                        return true;
                    }else{
                        return false;
                    }
                }
                else{//High priority tries to enter
                    floorPerson[person.initial_floor]--;// one high priority person entered or cannot entered. whichever happens decrement count
                    if(currentPeople+1 <= personCapacity && currentWeight+person.weight<=weightCapacity){
                        enteredPeople.push_back(person);
                        currentPeople++;
                        currentWeight+=person.weight;
                        if(floorPerson[person.initial_floor]==0){
                            allowLP.notifyAll();
                        }
                        if(state==IDLE){
                            if(person.destination_floor<currentFloor){ 
                                state=MOVING_DOWN;
                            }
                            else if(person.destination_floor>currentFloor){
                                state=MOVING_UP;
                            }
                        }
                        return true;
                    }else{
                        return false;
                    }
                }
            }
            else{
                if(person.priority==HP){
                    floorPerson[person.initial_floor]--;
                }
                return false;
            }
        }
        void leave(Person &person){
            currentPeople--;
            currentWeight-=person.weight;
            numActivePeople--;
            destQueue.erase(person.destination_floor);
           // cout<<person.personID<<"trying to exit\n";
            for(vector<Person>::iterator it = enteredPeople.begin();it!=enteredPeople.end();it++){
            //    cout<<"iterator deniyor "<<person.personID<<"\n";
                if(it->personID==person.personID){
            //        cout<<person.personID<<"erased\n";
                    enteredPeople.erase(it);
                    break;
                }
            }
            requestCount--;
            /*if(requestCount==0){
                state=IDLE;
                canRequest.notifyAll();
            }*/
            bool flag=true;
            for(Person p: enteredPeople){
                    if(p.destination_floor==currentFloor){
                        flag=false;
                        break;
                    }
            }
            if(flag){
                personLeft.notify();
            }
            printLeft(person);
            printElevator();
        }
        void printRequested(Person &person){
            string pri;
            if(person.priority==HP){
                pri="hp";
            }
            else{
                pri="lp";
            }
            cout<<"Person (";
            cout<<person.personID<<", ";
            cout<<pri<<", ";
            cout<<person.initial_floor<<" -> ";
            cout<<person.destination_floor<<", ";
            cout<<person.weight<<") made a request"<<endl;
        }
        void printEntered(Person &person){
            string pri;
            if(person.priority==HP){
                pri="hp";
            }
            else{
                pri="lp";
            }
            cout<<"Person (";
            cout<<person.personID<<", ";
            cout<<pri<<", ";
            cout<<person.initial_floor<<" -> ";
            cout<<person.destination_floor<<", ";
            cout<<person.weight<<") entered the elevator"<<endl;
        }
        void printLeft(Person &person){
            string pri;
            if(person.priority==HP){
                pri="hp";
            }
            else{
                pri="lp";
            }
            cout<<"Person (";
            cout<<person.personID<<", ";
            cout<<pri<<", ";
            cout<<person.initial_floor<<" -> ";
            cout<<person.destination_floor<<", ";
            cout<<person.weight<<") has left the elevator"<<endl;
        }
        void printElevator(){
            string st;
            if(state==MOVING_UP){
                st="Moving-up";
            }else if(state==MOVING_DOWN){
                st="Moving-down";
            }else
            {
                st="Idle";
            }
            cout<<"Elevator (";
            cout<<st<<", ";
            cout<<currentWeight<<", ";
            cout<<currentPeople<<", ";
            cout<<currentFloor<<" -> ";
            if(!destQueue.empty() && state==MOVING_UP){
                set<int>::iterator it=destQueue.begin();
                cout<<*it;
                it++;
                for(it;it!=destQueue.end();it++){
                    cout<<","<<*it;
                }
            }else if(!destQueue.empty() && state==MOVING_DOWN){
                set<int>::iterator it=destQueue.end();
                it--;
                for(it;it!=destQueue.begin();it--){
                    cout<<*it<<",";
                }
                cout<<*it;
            }
            cout<<")"<<endl;
        }
        bool activePeople(){
            __synchronized__;
            return numActivePeople!=0;
        }
        bool isIDLE(){
            __synchronized__;
            return state==IDLE;
        }
        bool isMOVING_UP(){
            __synchronized__;
            return state==MOVING_UP;
        }
        bool isMOVING_DOWN(){
            __synchronized__;
            return state==MOVING_DOWN;
        }
        int getRequestCount(){
            __synchronized__;
            return requestCount;
        }
        void moveUp(){
            __synchronized__;
            currentFloor++;
            canRequest.notifyAll();
        }
        void moveDown(){
            __synchronized__;
            currentFloor--;
            canRequest.notifyAll();
        }
        void enterLeave(){
            __synchronized__;
            int size = enteredPeople.size();
            bool flag=false;
            for(Person p: enteredPeople){
                    if(p.destination_floor==currentFloor){
                        flag=true;
                        break;
                    }
            }
            //cout<<"canLeave.notifyAll();\n";
            canLeave.notifyAll();
            if(flag){
                //cout<<"personLeft.wait();\n";
                personLeft.wait();
            }
            //cout<<"stopped.notifyAll()\n";
            stopped.notifyAll();
            if(requestedPeople[currentFloor]>0){//if there are people waiting to enter at currentFloor
                allTriedToEnter.wait();//wait all possible persons to enter
            }
            if(destQueue.empty()){ //if destQueue is empty
                //state= IDLE then let possible persons to request and enter again
                state=IDLE;
                canRequest.notifyAll();
            }
      //      cout<<"enterleaveFinished\n";
        }
        bool atDestination(){
            __synchronized__;
            bool value = destQueue.find(currentFloor)!=destQueue.end();
            if(value){
                destQueue.erase(currentFloor);
            }
            if(destQueue.empty()){
                state=IDLE;
                //canRequest.notifyAll();
            }
            printElevator();
            return value;
        }
        bool destQueueisEmpty(){
            __synchronized__;
            return destQueue.size()==0;
        }
        ~Elevator(){}
};
struct PersonStruct{
    Elevator* elevator;
    Person person;
};
void* PersonThread(void *p ){
    PersonStruct* ps= (PersonStruct*)p;
    Elevator* elevator = ps->elevator;
    Person person = ps->person; 
    elevator->newPerson(person);
    return NULL;
}


void* ElevatorController(void *p){
    //cout<<"ElevatorController\n";
    Elevator* elevator= (Elevator*) p;
    int IDLE_TIME=elevator->idleTime;
    int TRAVEL_TIME=elevator->travelTime;
    int IN_OUT_TIME=elevator->inOutTime;
    //cout<<elevator->inOutTime;
    while(elevator->activePeople()){
        //cout<<"here\n";
        if(elevator->isIDLE()){
            //cout<<"IDLE\n";
            while(elevator->getRequestCount()==0){
                //cout<<"NoRequest\n";
                waitMicroSeconds(IDLE_TIME);//wait requests to come
            }
        }
        else{
            //cout<<"elsedeyim\n";
            while(!elevator->destQueueisEmpty()){
                if(elevator->isMOVING_UP()){
                    waitMicroSeconds(TRAVEL_TIME);
                    elevator->moveUp();
                    if(elevator->atDestination()){
                        //cout<<"enterLeave\n";
                        elevator->enterLeave();
                        waitMicroSeconds(IN_OUT_TIME);
                    }
                }
                else if(elevator->isMOVING_DOWN()){
                    waitMicroSeconds(TRAVEL_TIME);
                    elevator->moveDown();
                    if(elevator->atDestination()){
                        //cout<<"enterLeave\n";
                        elevator->enterLeave();
                        waitMicroSeconds(IN_OUT_TIME);
                    }
                }        
            }
        }
    }
    return NULL;
};

class FileParser {
    private :
        string fileName;
        vector<Person> personList; 
        int numFloors, numPeople, weight_capacity, person_capacity, travelTime, idleTime, inOutTime;
    public:
        FileParser(string filePath){

                ifstream file;
                file.open(filePath);
                string line;
                string firstline;
                Person newPerson;
                
                int WP,IF,DF,P;
                char endline;
                if(file.is_open()){
                    file>>numFloors>>numPeople>>weight_capacity>>person_capacity>>travelTime>>idleTime>>inOutTime;
                    personList = vector<Person>();
                    for(int i=0;i<numPeople;i++){
                        file>>WP>>IF>>DF>>P;
                        newPerson= Person(i,WP,IF,DF,P);
                        personList.push_back(newPerson);
                    }
                }
        }
        void printPersonList(){
            for(Person p: personList){
                p.printPerson();
            }
        };
        void printAll(){
            cout<<numFloors<<" "<<numPeople<<" "<<weight_capacity<<" "<<person_capacity<<" "<<travelTime<<" "<<idleTime<<" "<<inOutTime<<"\n";
            printPersonList();
        };
        vector<Person> getPersonList(){
            return personList;
        }
        vector<int> getMonitorArguments(){
            vector<int> arguments=vector<int>{numFloors, numPeople, weight_capacity, person_capacity, travelTime, idleTime, inOutTime};
            return arguments;
        }

};



int main(int argc, char * argv[]){
    
    string filePath;
    if(argc>1){
        pthread_t * people,controllerTh;
        filePath = argv[1];
        FileParser fp = FileParser(filePath);
        vector<int> monitorArguments = fp.getMonitorArguments();
        Elevator elevator = Elevator(monitorArguments); 
        int numPeople=monitorArguments[1];
        PersonStruct* psParams= new PersonStruct[numPeople];
        people=new pthread_t[numPeople];
        int i=0;
        vector<Person>personList=fp.getPersonList();
        pthread_create(&controllerTh,NULL,ElevatorController,(void*) (&elevator));
        for(Person person:personList){
            psParams[i].elevator=&elevator;
            psParams[i].person=person;
            pthread_create(&people[i],NULL,PersonThread,(void*) (psParams+i) );
            i++;
        }
        for(int i=0;i<numPeople;i++){
            pthread_join(people[i],NULL);
        }
        pthread_join(controllerTh,NULL);
        delete [] psParams;
        delete [] people;
        

    }
}
    
    