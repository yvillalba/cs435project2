#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include <climits>
#include <string>
#include <time.h>
#include <stdlib.h>
using namespace std;

struct GridNode {
  int data;
  unordered_set<GridNode*> neighbors;
   //graphNode* next;
};
//********************************question 6a)*******************************
class GridGraph {
  private:
      bool isNeighbor(int first, int second, int n) { 
      //check neighbor above 
        if ((first%n)-1==(second%n) && (first/n)==(second/n))
          return true;
      //check neighbor below 
        if ((first%n)+1==(second%n) && (first/n)==(second/n))
          return true;
      //check left neighbor     
        if ((first%n)==(second%n) and (first/n)-1==(second/n))
          return true;
      //check right neighbor  
        if ((first%n)==(second%n) and (first/n)+1==(second/n))
          return true;
        return false;
      }
      
  public:
      vector<GridNode*> vertices;
      GridNode* addNode(int nodeVal){
          GridNode* node = new GridNode; 
          node->data = nodeVal;// assign data to the new node 
          node->neighbors = {};
          //node->visited = false;
          return node;
    }
   
    void addUndirectedEdge(GridNode* first,GridNode* second, int n){
      //chech if first and second are neighbors
      cout<<"from "<<first->data<<" to "<<second->data<<"\n";
      if (isNeighbor(first->data,second->data,n)){
        cout<<"yes\n";
         // Add an edge from first to second. A new element is inserted to the neighbors of first. 
        first->neighbors.insert(second); 
        // Since graph is undirected, add an edge from second to first also 
        second->neighbors.insert(first); 
      }
    }
    void removeUndirectedEdges(GridNode* first,GridNode* second){
        // remove yhe edge from first. A element is deleted to the neighbors of first. 
        first->neighbors.erase(second);
       // Since graph is undirected, delete an edge from second to first also 
        second->neighbors.erase(first); 
    }
    vector <GridNode*>  getallNodes(){
        vector<GridNode*> allNodes= vertices;
        
        return allNodes;
    }
    GridNode* getNode(int nodeValue){
        for (auto u : vertices){
          if (u->data==nodeValue){
            return u;
          }
        }
        return NULL;

    }
};
//********************************question 6b)*******************************    
GridGraph createRandomGridGraph(int n){
    GridGraph graph1;
    int newN=n*n;
    GridNode**	node = new GridNode*[newN]();
    for (int i = 0; i < newN; ++i){
      int nodeVal=i;
      node[i] = graph1.addNode(nodeVal);
    }
    srand(time(NULL));
    for (int i=0;i<newN;i++){
      for (int j=0;j<newN;j++){
        if (i!=j){
          int chance=rand()%2;
          if (chance==1){
            //cout<<"despues "<<node[i]->data<<" to "<<node[j]->data<<"\n";
            graph1.addUndirectedEdge(node[i],node[j],n);
            
            graph1.vertices.push_back(node[i]);
          }
        }
      }
    }
    return graph1;
}
//********************************question 6d)*******************************
//unordered_map<GridNode*, pair<int, int>> distances;
vector<GridNode*> astar(GridNode* sourceNode,GridNode* dstNode){
   vector<GridNode*> listNodes;
   //1.Create an empty map of nodes to pairs of distances (g, h). g is the distance so far, and his the estimated distance to the goal using the heuristic. Initialize every node to map to infinity g
   
   //2.Calculate the heuristic value for the origin h and set the distance for the origin to (0, h). Let curr be the origin.
   
   //3.While curr is not the destination node:
        //a.“Finalize” curr.
        //b.Iterate over its neighbors, “relax” each neighbor:
            //c.For each neighbor that is not finalized, update its distance (if less than the current g value) to the sum of curr’s distance and the weight of the edge between curr and this neighbor.  Calculate the heuristic value for this neighbor and assign it to h.
        //d.Set curr to the next min node – the node with the smallest g+h value not yet finalized.
    //4.Return the g value for the destination node
   return listNodes; 
}
int main(){
   int n = 3; 
   GridGraph graph1=createRandomGridGraph(n);
   GridNode* souceNode=graph1.getNode(0);//node zero is (0,0)
   GridNode* destNode=graph1.getNode(99);//node 99 is (99,99)
   vector<GridNode*> listNodes;
   listNodes=astar(souceNode,destNode);
   
	
   return(0);
}
