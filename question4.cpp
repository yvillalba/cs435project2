#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <set>
#include <unordered_set>
#include <string> 
#include <queue>
#include <stack>
using namespace std; 
  
struct graphNode { 
   
    string data;
    vector<graphNode*> neighbors;
    bool visited;
   
}; 

//********************************question 3a)*******************************

class Graph {
 
  public:
     vector<graphNode*> vertices;
     graphNode* addNode(string nodeVal){
        graphNode* node = new graphNode; 
        node->data = nodeVal;// assign data to the new node 
        node->visited = false;
        return node;
    }

    void addUndirectedEdge(graphNode* first,graphNode* second){
         // Add an edge from first to second. A new element is inserted to the neighbors of first. 
		vector<graphNode*>::iterator it;
        it = find (	first->neighbors.begin(), first->neighbors.end(),second);
  		if (it == first->neighbors.end())
			 first->neighbors.push_back(second); 
        
		// Since graph is undirected, add an edge from second to first also 
        it = find (	second->neighbors.begin(), second->neighbors.end(),first);
  		if (it == second->neighbors.end())
			 second->neighbors.push_back(first); 
    }

    void removeUndirectedEdges(graphNode* first,graphNode* second){
        // remove yhe edge from first. A element is deleted to the neighbors of first. 
        first->neighbors.erase(remove(first->neighbors.begin(), first->neighbors.end(), second));   
       // Since graph is undirected, delete an edge from second to first also 
        second->neighbors.erase(remove(second->neighbors.begin(), second->neighbors.end(), first)); 
    }

    vector <graphNode*>  getallNodes(){
        //set<graphNode*> allNodes= vertices;    
        return vertices;
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
		srand(time(NULL));
		for (int i=0;i<n;i++){
        int numEdges=rand()%n;
			for (int j=0;j<numEdges;j++){
        		int randIndx =rand()%n;
				graph1.addUndirectedEdge(node[i],node[randIndx]);
			}
			graph1.vertices.push_back(node[i]);//add the node to vertices
		}
                   
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
		graph1.addUndirectedEdge(node[i],node[i+1]);
        graph1.vertices.push_back(node[i]);//add the node to vertices
        
    }
    graph1.vertices.push_back(node[i]);
    return graph1;

}


class GraphSearch {
  private:
       vector<graphNode*> nodes;
  public:
  //********************************question 3d)*******************************
     void DFSRecHelper(graphNode* start,graphNode* end){

        start->visited = true;// mark source vertex as visited
        nodes.push_back(start);
        if (start->data==end->data){ 
           return;}
        for (auto u : start->neighbors){  // Recur for all the vertices adjacent 
          if (!u->visited){
             DFSRecHelper(u,end);
          }
        }
     }

     vector<graphNode*> DFSRec(graphNode* start,graphNode* end){
        nodes.clear(); 
        // Call the recursive helper function to store the visited node
        DFSRecHelper(start, end); 
        return nodes;
     }

  //********************************question 3e)*******************************
  vector<graphNode*> DFSIter(graphNode* start,graphNode* end){
    nodes.clear();
		stack<graphNode*> stackNode; // Create a stack for DFS
		unordered_set<graphNode*> visited;
		stackNode.push(start);// Push the source node. 
		while (!stackNode.empty()){
			start = stackNode.top();
			stackNode.pop();// Pop a vertex from stack
			// if the vertex is already visited yet, ignore it
			if (visited.find(start)!=visited.end())
				continue;
			visited.insert(start);
			nodes.push_back(start);
			if (start->data==end->data){ 
            return nodes;}
			// go through  all the vertices adjacent
			for (auto it = start->neighbors.rbegin();it != start->neighbors.rend(); ++it){
				graphNode* u = *it;
				if (visited.find(u)==visited.end())
					stackNode.push(u);// Push the node. 
			}
		}

   return nodes;
}
  
  //********************************question 3f)*******************************
     void BFTHelper(Graph  graph1, queue<graphNode*> &q,	unordered_set<graphNode*> &visited){
        if (q.empty())
            return;
        graphNode* v = q.front();
        nodes.push_back(v);
        q.pop();// pop front node from queue 
        for (auto u : v->neighbors){
            if (visited.find(u)==visited.end()){// mark it visited and push it into queue
              visited.insert(u);
              q.push(u);
            }
        }
        BFTHelper(graph1, q,visited);
      }

     vector<graphNode*> BFTRec(Graph graph1){
        nodes.clear(); 
				unordered_set<graphNode*> visited;
        vector<graphNode*> allNodes=graph1.vertices;
        queue<graphNode*> q;// create a queue 
        // Do BFT traversal from all  nodes 
        for (auto node = allNodes.begin(); node != allNodes.end(); node++){
          if (visited.find(*node)==visited.end()){
             visited.insert(*node);// mark source vertex as visited
             q.push(*node);// push source vertex into the queue
             BFTHelper(graph1, q,visited); // start BFS traversal from vertex node
          }
        }
        return nodes;
    }

    //********************************question 3g)*******************************
    void BFTIterHelper(Graph  graph1, graphNode* node,unordered_set<graphNode*> &visited){
        queue<graphNode*> q;// create a queue used to do BFS
        visited.insert(node);// mark source vertex as visited
        q.push(node);// push source vertex into the queue
        while (!q.empty())	{
            node = q.front();// pop front node from queue
            q.pop();
            nodes.push_back(node);    
            for (auto u :node->neighbors){
                if (visited.find(u)==visited.end()){// mark it visited and push it into queue
		    		visited.insert(u);// mark source vertex as visited
		    		q.push(u);
				}
            }
		}
    }

    vector<graphNode*> BFTIter(Graph graph1){
        nodes.clear(); 
				unordered_set<graphNode*> visited;
        vector<graphNode*> allNodes=graph1.vertices;
        // Do BFT traversal from all  nodes 
        for (auto node = allNodes.begin(); node != allNodes.end(); node++){
					if (visited.find(*node)==visited.end()){
                BFTIterHelper(graph1, *node,visited); // start BFS traversal from vertex node
             }
        }
        return nodes;
    }
};


//********************************question 3h)*******************************
 vector<graphNode*>  BFTRecLinkedList(Graph  graph2) {
    GraphSearch BFT;
    return BFT.BFTRec(graph2);
}

//********************************question 3i)*******************************
vector<graphNode*>  BFTIterLinkedList(Graph  graph2) {
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

void printGraph(vector <graphNode*> allNodes) { 
    // prints the element 
    cout << "\nThe elements are: "; 
    for (auto it = allNodes.begin(); it != allNodes.end(); it++) 
      cout << (*it)->data << " "; 
} 


int main(){
   int n = 6; 
   Graph graph1=createRandomUnweightedGraphIter(n);
   cout << "createRandomUnweightedGraphIter for GRAPH1: "; 
   vector <graphNode*> allNodes=graph1.getallNodes();
   cout << "\nThe elements are: "<<endl; 
    for (auto it = allNodes.begin(); it != allNodes.end(); it++){ 
      cout << (*it)->data << ":{ "; 
			 for (auto u :(*it)->neighbors){
				 cout<<u->data<<" ";
			 }
			 cout<<endl;	
		}
   GraphSearch search;
   cout << "\ncreateLinkedList for GRAPH2: 6 vertices :: ";  
   Graph graph2=createLinkedList(n);
   printGraph(graph2.getallNodes());

   graphNode* start=getNode(graph2,"1");
   graphNode* end=getNode(graph2,"4");
   cout << "\n\nDFSRec--createLinkedList for GRAPH2 from "<<start->data<<" to "<<end->data;
   printGraph(search.DFSRec(start,end));
   
   cout << "\n\nDFSIter--createLinkedList for GRAPH2 from "<<start->data<<" to "<<end->data;
   printGraph(search.DFSIter(start,end));
   
   cout << "\n\nBFTRec--createLinkedList for GRAPH2:: "; 
   printGraph(search.BFTRec(graph2));
   
   cout << "\n\nBFTRecLinkedList--createLinkedList for GRAPH2:: ";
   printGraph(BFTRecLinkedList(graph2));
  
   cout << "\n\nBFTIter--createLinkedList for GRAPH2:: "; 
   printGraph(search.BFTIter(graph2));
   
   cout << "\n\nBFTIterLinkedList--createLinkedList for GRAPH2:: ";
   printGraph(BFTIterLinkedList(graph2));
  
  return 0;
}
