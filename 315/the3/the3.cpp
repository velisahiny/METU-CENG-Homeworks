#include "the3.h"

// You  can define extra functions here
using namespace std;



class Node{
public:
  char color;
  int discoverTime;
  int finishTime;
  int number;
  Node* predecessor;
  vector<int> adjacencyList;
  Node(){
  }
  Node(int _number){
    this->number = _number;
    this->predecessor = NULL;
  }

};

void createAdjacencyList(vector<Node> &Nodes, int** edgeList,int n ){
  for(int i=0;i<n;i++){
    vector<int> &adjacencyList = Nodes[i].adjacencyList;
    for (int j = 0; j < n ; j++) {
      if( edgeList[i][j] > 0){
        adjacencyList.push_back(j);
      }
    }
  }
}
vector<Node> createNodes(int size){
  vector<Node> Nodes;
  for(int i=0;i<size;i++){
    Node newNode(i);
    Nodes.push_back(newNode);
  }
  return Nodes;
}
void DFS_VISIT(int &time, Node &u, vector<int> &reachableList, vector<Node>& Nodes ){
  time++;
  u.discoverTime=time;
  u.color='g';
  for(int i : u.adjacencyList){   
    Node &v = Nodes[i];
    if(v.color=='w'){
      v.predecessor = &u;
      reachableList.push_back(v.number);
      DFS_VISIT(time,v,reachableList, Nodes);
    }
  }
  u.color='b';
  time++;
  u.finishTime=time;
};
vector<vector<int>> DFS(vector<Node>& Nodes){

  vector<vector<int>> connectedList;
  for(Node &u: Nodes){
    u.color = 'w';
    u.predecessor=NULL;
  }
int time = 0;
for(Node &u: Nodes ){
  if (u.color=='w'){
    vector<int> reachableList;
    reachableList.push_back(u.number);
    DFS_VISIT(time,u,reachableList, Nodes);
    connectedList.push_back(reachableList);
  }
}
  return connectedList;
}

vector<vector<int>> Help(int n, int**  edgeList){
  vector<Node> Nodes = createNodes(n);
  createAdjacencyList(Nodes, edgeList, n);
  vector<vector<int>> connectedList = DFS(Nodes);
  return connectedList;
}


vector<vector<int>> FloydWarshall(int n, int** edgeList){
  //initialize vector
  vector<int> innervector = vector<int>(n);
  vector<vector<int>> v = vector<vector<int>>(n) ;
  for(int i=0;i<n;i++){
    v.push_back(innervector);
    for(int j=0;j<n;j++){
      int x=edgeList[i][j];
      if(i!=j && x==0){
        x=-1;// -1 =infinity
      }
      v[i].push_back(x);
    }
  }

  for(int k=0;k<n;k++){
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        int x1=v[i][j];
        int x2=v[i][k];
        int x3= v[k][j];
        if(x1!=-1 && x2!=-1 && x3!=-1){
          v[i][j]= min(x1,x2+x3);
        }
        else if (x1!=-1){
          v[i][j]= x1;
        }
        else{//x1=-1
          if(x2!=-1 && x3!=-1){
            v[i][j]= x2+x3;
          }
          else{
            v[i][j] = x1;
          }
        }
        
      }
    }
  } 
  return v;
}

vector<double> getScores(vector<vector<int>>& connectedList,vector<vector<int>>& shortestpath,int n){
  vector<double> scores = vector<double>(n);
  double score=0;
  double pairs;
  double given;
  for(auto &myvector: connectedList ){
    
    for(int v: myvector){
      
      score=0;
      for(int s: myvector){
        for(int t:myvector){
          if(s==t){
            pairs=1;
          }
          else{
            pairs = shortestpath[s][t];
          }
          if(v==s || v==t ){
            given=0;
          }
          else{
            given = shortestpath[s][v]+shortestpath[v][t];
          }
          score += given/pairs;
        }
        
      }
      scores[v]=score;
    }
  }

  return scores;
  }
  // INPUT :
//            n         : number of nodes in the graph
//            edgeList  : edges in the graph
//            scores    : importance scores
// return value :
//                 number of disconnected components
int Important (int n, int**& edgeList, double*& scores)
{
  
  vector<vector<int>> connectedList = Help(n,edgeList);
  int components = connectedList.size();
  if(components < 1){
    return components;
  }
  vector<vector<int>> shortestpath = FloydWarshall(n,edgeList);
  vector<double> vectorscores = getScores(connectedList,shortestpath,n);
  scores = new double[n];
  for(int i=0;i<n;i++){
    scores[i] = vectorscores[i];
  }
  return components;
}

