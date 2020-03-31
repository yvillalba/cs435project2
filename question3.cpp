#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <set>
#include<string> // for string and to_string() 
#include<queue>
using namespace std; 
  
struct graphNode { 
   
    string data;
    vector<graphNode*> neighbors;
    graphNode* next;
    bool visited;
   
}; 

//********************************question 3a)*******************************
class Graph {
  private:
      
  public:

     set<graphNode*> vertices;
     graphNode* addNode(string nodeVal){
        graphNode* node = new graphNode; 
        node->data = nodeVal;// assign data in first node 
        //node->neighbors =  
        node->next =NULL;
        node->visited = false;
        //verticesNoNeigh.insert(node);
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
      cout<<nodeVal<<endl;
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
       set<graphNode*> nodes1;
       set<graphNode*> nodes2;

  public:
     void DFSRecHelper(graphNode* start,graphNode* end){
       cout<<"starjjjjjjt: ";
        //start->visited = true;// mark source vertex as visited
        //nodes2.insert(start);
        /*if (start->data==end->data){
              cout<<"starjjjjjjt: "<<end->data<<endl;
  
           return;}
        for (auto u : start->neighbors){  // Recur for all the vertices adjacent 
          cout<<"starjjjjjjt: "<<u->data<<endl;
          if (!u->visited){
             DFSRecHelper(u,end);
              }
          }*/
     }
     set<graphNode*> DFSRec(graphNode* start,graphNode* end){
        
        // Call the recursive helper function to store the visited node
        DFSRecHelper(start, end); 
        return nodes2;
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
        set<graphNode*> allNodes=graph1.vertices;
        queue<graphNode*> q;// create a queue 
        // Do BFT traversal from all  nodes 
        for (auto node = allNodes.begin(); node != allNodes.end(); node++){
           //cout<<endl<<(*node)->visited<<endl;
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
              nodes1.insert(node);
              //cout<<endl<<endl;
              for (auto u :node->neighbors){
                  //cout<<u->data<<endl;
                  if (!u->visited){// mark it visited and push it into queue
			              u->visited = true;
			              q.push(u);
		              }
              }
	        }
      }

     set<graphNode*> BFTIter(Graph graph1){
        set<graphNode*> allNodes=graph1.vertices;
      
	       // Do BFT traversal from all  nodes 
         for (auto node = allNodes.begin(); node != allNodes.end(); node++){
           //cout<<endl<<(*node)->visited<<endl;
              if ((*node)->visited == false){
                BFTIterHelper(graph1, *node); // start BFS traversal from vertex node
              }
        }
        return nodes1;
    }
};
void resetNodestounvisited(Graph  graph1){
        set<graphNode*> allNodes=graph1.getallNodes();
        // Do BFT traversal from all  nodes 
        for (auto node = allNodes.begin(); node != allNodes.end(); node++){
            (*node)->visited = false;
        }
}

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
   GraphSearch BFT;
   
   Graph graph2=createLinkedList(n);
   cout << "\n\ncreateLinkedList for GRAPH2: "; 
   printGraph(graph2.getallNodes());

   graphNode* start=getNode(graph2,"2");
   graphNode* end=getNode(graph2,"4");
   cout << "\n\nDFSRec--createLinkedList for GRAPH2:: ";
   printGraph(BFT.DFSRec(start,end));
   cout << "\n\nBFTRec--createLinkedList for GRAPH2:: "; 
   resetNodestounvisited(graph2);
   printGraph(BFTRecLinkedList(graph2));
   cout << "\n\nBFTIter--createLinkedList for GRAPH2:: "; 
   resetNodestounvisited(graph2);
   printGraph(BFTIterLinkedList(graph2));
  // removeUndirectedEdges(b,c);*/
  return 0;
}
