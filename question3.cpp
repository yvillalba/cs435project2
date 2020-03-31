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
// This function prints contents of linked list starting from the given node 
void printList(graphNode* n) 
{ 
    while (n != NULL) { 
        cout << n->data << " "; 
        n = n->next; 
    } 
} 

//********************************question 3a)*******************************
class Graph {
  private:
       //graphNode *first;
       // vector<graphNode*> vertices;
  public:
     set<graphNode*> vertices;
     graphNode* addNode(string nodeVal){
        graphNode* node = new graphNode; 
        node->data = nodeVal;// assign data in first node 
        //node->neighbors =  
        node->next =NULL;
        node->visited = false;
        vertices.insert(node);
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
   //int i=0;
   for (int i = 0; i < n; ++i){
      string nodeVal=to_string(i);
       cout<<nodeVal<<endl;
			node[i] = graph1.addNode(nodeVal);
    }
   for (int i=0;i<n-1;i++){
      graph1.addUndirectedEdge(node[i],node[i+1]);
  }
  return graph1;

}
//********************************question 3c)*******************************
Graph createLinkedList(int n){
   Graph graph1;
   // allocate memory
	 graphNode**	node = new graphNode*[n]();
		// initialize head pointer for all vertices
		for (int i = 0; i < n; ++i){
      string nodeVal=to_string(i);
			node[i] = graph1.addNode(nodeVal);
    }
    int i;
    for (i = 0; i < n-1; i++){// add edges to the directed graph
        node[i]->next = node[i+1]; // Link first node with second 
		}
     //cout<<endl;
     //printList(node[0]);
     return graph1;

}
class GraphSearch {
  private:
       set<graphNode*> nodes;
       set<graphNode*> nodes1;
       //graphNode *first;
       // vector<graphNode*> vertices;
  public:
  //********************************question 3f)*******************************
     void BFTHelper(Graph  graph1, queue<graphNode*> &q){
	        if (q.empty())
		          return;
          graphNode* v = q.front();
         // cout<<endl<<v->data<<endl;
         nodes.insert(v);
          q.pop();// pop front node from queue and print it
          for (auto u : graph1.getallNodes()){
            if (!u->visited){// mark it visited and push it into queue
			          u->visited = true;
			          q.push(u);
		        }
	        }
	        
        	BFTHelper(graph1, q);
      }

     set<graphNode*> BFTRec(Graph graph1){ 
        set<graphNode*> allNodes=graph1.getallNodes();
        queue<graphNode*> q;// create a queue 

        // Do BFT traversal from all  nodes 
         for (auto node = allNodes.begin(); node != allNodes.end(); node++){
           //cout<<endl<<(*node)->visited<<endl;
              if ((*node)->visited == false){
                  	(*node)->visited = true;// mark source vertex as visited
                    q.push(*node);// push source vertex into the queue
	              		BFTHelper(graph1, q); // start BFS traversal from vertex node
		            }
                //nodes.insert(*node);
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
              for (auto u : graph1.getallNodes())
                  if (!u->visited){// mark it visited and push it into queue
			              u->visited = true;
			              q.push(u);
		              }
	        }
      }

     set<graphNode*> BFTIter(Graph graph1){
        set<graphNode*> allNodes=graph1.getallNodes();
      
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
    cout << "\n\nBFTRec--createLinkedList: "; 
   printGraph(BFT.BFTRec(graph2));
    cout << "\n\nBFTIter--createLinkedList: "; 
   Graph graph3=createLinkedList(n);
   printGraph(BFT.BFTIter(graph3));
  // removeUndirectedEdges(b,c);
  return 0;
}
