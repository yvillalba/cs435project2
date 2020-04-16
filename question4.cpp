#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <string> 
#include <queue>
#include <stack>
#include <unordered_map> 
#include <unordered_set>
using namespace std; 
  
struct graphNode { 
   
    string data;
    vector<graphNode*> neighbors;
   
}; 

//********************************question 4b)*******************************
class DirectedGraph {
  public:
     vector<graphNode*> vertices;

     graphNode* addNode(string nodeVal){
        graphNode* node = new graphNode; 
        node->data = nodeVal;// assign data to the new node 
        return node;
    }

    void addDirectedEdge(graphNode* first,graphNode* second){
        // Add an edge from first to second. A new element is inserted to the neighbors of first. 
        first->neighbors.push_back(second); 
    }

    void removeDirectedEdge(graphNode* first,graphNode* second){
        // remove the edge from first. A element is deleted to the neighbors of first. 
        first->neighbors.erase(remove(first->neighbors.begin(), first->neighbors.end(), second));   
    }

    vector <graphNode*>  getallNodes(){
        return vertices;
    }
  
};


class TopSort {
  private:   
    	unordered_map<graphNode*, int> initializeInDegreeMap(DirectedGraph graph) {
          unordered_map<graphNode*, int> inDegree;// initialize inDegree unordered_map with all 0s
          for (graphNode* node : graph.vertices) {
             inDegree.insert(make_pair(node, 0)); 
          }
          // populate inDegree with the current numbers of incoming edges
          for (auto node : graph.vertices) {
            for (auto neighbor : node->neighbors) {
               inDegree[neighbor] = inDegree[neighbor]+1;
            }
          }
         return inDegree;
      }
  
	void addNodWithoutDepToQ(unordered_map<graphNode*, int> &inDegree, queue<graphNode*> &q) {
  
      for (auto curr=inDegree.begin(); curr!=inDegree.end(); ++curr){//go through each key
        if (curr->second == 0) {
            q.push(curr->first);// add node to the queue
            inDegree[curr->first] = inDegree[curr->first]-1; //decrement the current value's in-degree to -1
        }
      }
  }

  public:
  //********************************question 4d)******************************* 
	//This is used to perform a topological sort on a directed acyclic graph    
  vector<graphNode*> Kahns(DirectedGraph graph){
          unordered_map<graphNode*, int> inDegree;
          for (graphNode* node : graph.vertices) {
               inDegree.insert(make_pair(node, 0)); 
          }
          
          // populate inDegree with the current numbers of incoming edges
          for (auto node : graph.vertices) {
              for (auto neighbor : node->neighbors) {
                inDegree[neighbor] = inDegree[neighbor]+1;
              }
          }  
          vector<graphNode*> topSort;
          queue<graphNode*> q;  
          addNodWithoutDepToQ(inDegree, q);
          while (!q.empty())	{
                graphNode* curr = q.front();// first element in q
                q.pop();
                topSort.push_back(curr);// add cuur to tail of topSort
                // decrement all neighbors' in degrees because we've removed curr from our nodes list.
                for (graphNode* neighbor : curr->neighbors) {
                    inDegree[neighbor] = inDegree[neighbor]-1;			
									  if (inDegree[neighbor] == 0)
                         q.push(neighbor);
                }
              
          }
      return topSort;
    }
    
  //********************************question 4e)******************************* 
	//This is used to perform a topological sort on a directed acyclic graph
  vector<graphNode*> mDFS(DirectedGraph graph){   
		  unordered_set<graphNode*> visited;
      stack<graphNode*> stackmDFS;
			stack<graphNode*> stackTemp;
      vector<graphNode*> topSort;
      for (auto node : graph.vertices) {
           if(visited.find(node)==visited.end()){
            visited.insert(node);
            stackTemp.push(node);
          }
					while(!stackTemp.empty()){
            graphNode* currNode = stackTemp.top();// top element in stackTemp
            stackTemp.pop();
            for(auto neighNode:currNode->neighbors){
                visited.insert(node);
                stackTemp.push(neighNode);
            }
          }
					stackmDFS.push(node);
      }
      while (!stackmDFS.empty()) {
          graphNode* currNode = stackmDFS.top();// top element in stackmDFS
          stackmDFS.pop();
          topSort.push_back(currNode);
      }
     reverse(topSort.begin(),topSort.end());//reverse the order of topSort vector 
     return topSort;
  }    
};
void printGraph(vector <graphNode*> allNodes) { 
    cout<<"The elements are: ";
    for (auto node : allNodes) {
            cout<<"->" << node->data;
    }
		 cout<<endl; 
} 
//********************************question 4c)*******************************
 DirectedGraph createRandomDAGIter(int n){
    DirectedGraph graph1;
    TopSort sort;
    graphNode**	node = new graphNode*[n]();
    for (int i = 0; i < n; ++i){
      string nodeVal=to_string(i);
      node[i] = graph1.addNode(nodeVal);
    }
    int i;
    for (i=0;i<n;i++){
        for (int j=i+1;j<n;j++){
           graph1.addDirectedEdge(node[i],node[j]);

        }
       graph1.vertices.push_back(node[i]);
    }
    
    vector<graphNode*> topSort =sort.Kahns(graph1);   
    cout<<"Output of Kahn's:\n"; 
    printGraph(topSort);
    topSort.clear();
   
    topSort =sort.mDFS(graph1); 
    cout<<"Output of mDFS's:\n"; 
    printGraph(topSort);
    return graph1;
}

int main(){
   int n = 1000; 
   DirectedGraph graph1=createRandomDAGIter(n);

   return(0);
}
