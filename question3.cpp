#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <set>
#include <string> 
#include <queue>
#include <stack>
using namespace std; 
  
struct graphNode { 
   
    string data;
    vector<graphNode*> neighbors;
    graphNode* next;
    bool visited;
   
}; 

//********************************question 3a)*******************************
class Graph {
 
  public:

     set<graphNode*> vertices;
     graphNode* addNode(string nodeVal){
        graphNode* node = new graphNode; 
        node->data = nodeVal;// assign data to the new node 
        node->next =NULL;
        node->visited = false;
        return node;
    }
    void addUndirectedEdge(graphNode* first,graphNode* second){
         // Add an edge from first to second. A new element is inserted to the neighbors of first. 
        first->neighbors.push_back(second); 
  
        // Since graph is undirected, add an edge from second to first also 
        second->neighbors.push_back(first); 
    }
    void removeUndirectedEdges(graphNode* first,graphNode* second){
        // remove yhe edge from first. A element is deleted to the neighbors of first. 
        first->neighbors.erase(remove(first->neighbors.begin(), first->neighbors.end(), second));   
       // Since graph is undirected, delete an edge from second to first also 
        second->neighbors.erase(remove(second->neighbors.begin(), second->neighbors.end(), first)); 
    }
    set <graphNode*>  getallNodes(){
        set<graphNode*> allNodes= vertices;
        
        return allNodes;
    }
  
};
//********************************question 3b)******************************* 
Graph createRandomUnweightedGraphIter(int n){
    Graph graph1;
    graphNode**	node = new graphNode*[n]();
    for (int i = 0; i < n; ++i){
      string nodeVal=to_string(i);
      node[i] = graph1.addNode(nodeVal);
    }
    int i;
    for (i=0;i<n-1;i++){
      graph1.addUndirectedEdge(node[i],node[i+1]);
      graph1.vertices.insert(node[i]);
    }
    graph1.vertices.insert(node[i]);
    return graph1;
}
//********************************question 3c)*******************************
Graph createLinkedList(int n){
    Graph graph1;
    graphNode**	node = new graphNode*[n]();// initialize head pointer for all vertices
    for (int i = 0; i < n; ++i){
      string nodeVal=to_string(i);
      node[i] = graph1.addNode(nodeVal);
    }
    int i;
    for (i = 0; i < n-1; i++){// add edges to the directed graph
        node[i]->next = node[i+1]; // Link first node with second
        node[i]->neighbors.push_back(node[i+1]);
        graph1.vertices.insert(node[i]);//add the node to vertices
        
    }
     graph1.vertices.insert(node[i]);
    return graph1;

}
class GraphSearch {
  private:
       set<graphNode*> nodes;
  public:
  //********************************question 3d)*******************************
     void DFSRecHelper(graphNode* start,graphNode* end){

        start->visited = true;// mark source vertex as visited
        nodes.insert(start);
        if (start->data==end->data){ 
           return;}
        for (auto u : start->neighbors){  // Recur for all the vertices adjacent 
          if (!u->visited){
             DFSRecHelper(u,end);
              }
          }
     }
     set<graphNode*> DFSRec(graphNode* start,graphNode* end){
        nodes.clear(); 
        // Call the recursive helper function to store the visited node
        DFSRecHelper(start, end); 
        return nodes;
     }
  //********************************question 3e)*******************************
  set<graphNode*> DFSIter(graphNode* start,graphNode* end){
    nodes.clear(); 
    stack<graphNode*> stackNode; // Create a stack for DFS
    stackNode.push(start); // Push the source node. 
    while (!stackNode.empty()) { 
        start = stackNode.top(); 
        stackNode.pop(); // Pop a vertex from stack
        if (!start->visited){
              start->visited = true;// mark it visited
              nodes.insert(start);
              }
        if (start->data==end->data){ 
           break;}
        for (auto u : start->neighbors){  // go through  all the vertices adjacent 
          //cout<<"data  "<<u->data<<u->visited;
          if (!u->visited){
             stackNode.push(u); 
              }
          }
    } 
        return nodes;
  }
     
  //********************************question 3f)*******************************
     void BFTHelper(Graph  graph1, queue<graphNode*> &q){
        if (q.empty())
            return;
        graphNode* v = q.front();
        nodes.insert(v);
        q.pop();// pop front node from queue 
         for (auto u : v->neighbors){
          if (!u->visited){// mark it visited and push it into queue
              u->visited = true;
              q.push(u);
              }
          }
          BFTHelper(graph1, q);
      }

     set<graphNode*> BFTRec(Graph graph1){
        nodes.clear(); 
        set<graphNode*> allNodes=graph1.vertices;
        queue<graphNode*> q;// create a queue 
        // Do BFT traversal from all  nodes 
        for (auto node = allNodes.begin(); node != allNodes.end(); node++){
          
           if ((*node)->visited == false){
              (*node)->visited = true;// mark source vertex as visited
              q.push(*node);// push source vertex into the queue
              BFTHelper(graph1, q); // start BFS traversal from vertex node
            }
         }
         return nodes;
    }
     //********************************question 3g)*******************************
     void BFTIterHelper(Graph  graph1, graphNode* node){
          queue<graphNode*> q;// create a queue used to do BFS
        	node->visited = true;// mark source vertex as visited
          q.push(node);// push source vertex into the queue
          while (!q.empty())	{
              node = q.front();// pop front node from queue
              q.pop();
              nodes.insert(node);
              
              for (auto u :node->neighbors){
                  
                  if (!u->visited){// mark it visited and push it into queue
			              u->visited = true;
			              q.push(u);
		              }
              }
	        }
      }

     set<graphNode*> BFTIter(Graph graph1){
        nodes.clear(); 
        set<graphNode*> allNodes=graph1.vertices;
      
	       // Do BFT traversal from all  nodes 
         for (auto node = allNodes.begin(); node != allNodes.end(); node++){
          
              if ((*node)->visited == false){
                BFTIterHelper(graph1, *node); // start BFS traversal from vertex node
              }
        }
        return nodes;
    }
};


//********************************question 3h)*******************************
 set<graphNode*>  BFTRecLinkedList(Graph  graph2) {
    GraphSearch BFT;
    return BFT.BFTRec(graph2);
}
//********************************question 3i)*******************************
set<graphNode*>  BFTIterLinkedList(Graph  graph2) {
    GraphSearch BFT;
    return BFT.BFTIter(graph2);
}
graphNode* getNode(Graph graph2,string nodeValue){
  
  for (auto u : graph2.vertices){
    if (u->data==nodeValue){
        return u;
    }
  }
  return NULL;

}
void resetNodesToNotVisited(Graph  graph1){
        set<graphNode*> allNodes=graph1.getallNodes();
        // Do BFT traversal from all  nodes 
        for (auto node = allNodes.begin(); node != allNodes.end(); node++){
            (*node)->visited = false;
        }
}
void printGraph(set <graphNode*> allNodes) { 
    // prints the element 
    cout << "\nThe elements are: "; 
    for (auto it = allNodes.begin(); it != allNodes.end(); it++) 
        cout << (*it)->data << " "; 
} 
int main(){
   int n = 6; 
   Graph graph1=createRandomUnweightedGraphIter(n);
   cout << "\ncreateRandomUnweightedGraphIter for GRAPH1: "; 
   printGraph(graph1.getallNodes());
   
   GraphSearch search;
   cout << "\n\ncreateLinkedList for GRAPH2: 6 vertices :: ";  
   Graph graph2=createLinkedList(n);
   printGraph(graph2.getallNodes());

   graphNode* start=getNode(graph2,"1");
   graphNode* end=getNode(graph2,"4");
   cout << "\n\nDFSRec--createLinkedList for GRAPH2 from "<<start->data<<" to "<<end->data;
   printGraph(search.DFSRec(start,end));
   resetNodesToNotVisited(graph2);
   
   cout << "\n\nDFSIter--createLinkedList for GRAPH2 from "<<start->data<<" to "<<end->data;
   printGraph(search.DFSIter(start,end));
   
   cout << "\n\nBFTRec--createLinkedList for GRAPH2:: "; 
   resetNodesToNotVisited(graph2);
   printGraph(search.BFTRec(graph2));
   
   cout << "\n\nBFTRecLinkedList--createLinkedList for GRAPH2:: ";
   resetNodesToNotVisited(graph2);
   printGraph(BFTRecLinkedList(graph2));

   cout << "\n\nBFTIter--createLinkedList for GRAPH2:: "; 
   resetNodesToNotVisited(graph2);
   printGraph(search.BFTIter(graph2));
   
   cout << "\n\nBFTIterLinkedList--createLinkedList for GRAPH2:: ";
   resetNodesToNotVisited(graph2);
   printGraph(BFTIterLinkedList(graph2));
  
  return 0;
}
