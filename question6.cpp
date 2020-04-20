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
};
//********************************question 6a)*******************************
class GridGraph {
  private:
      bool isNeighbor(GridNode* first, GridNode* second, int n) { 
        int firstX=(first->data)%n;
	int firstY=(first->data)/n;
	int secondX=(second->data)%n;
	int secondY=(second->data)/n;
      //check neighbor above 
        if (firstX-1==secondX && firstY==secondY)
          return true;
      //check neighbor below 
        if (firstX+1==secondX && firstY==secondY)
          return true;
      //check left neighbor     
        if (firstX==secondX && firstY-1==secondY)
          return true;
      //check right neighbor  
        if (firstX==secondX && firstY+1==secondY)
          return true;
        return false;
      }
      
  public:
      unordered_map<int,GridNode*> vertices;
      GridNode* addNode(int nodeVal){
          GridNode* node = new GridNode; 
          node->data = nodeVal;// assign data to the new node 
          node->neighbors = {};
          //node->visited = false;
          return node;
    }
   
    void addUndirectedEdge(GridNode* first,GridNode* second, int n){
      //chech if first and second are neighbors
    
      if (isNeighbor(first,second,n)){
        cout<<"from "<<first->data<<":("<<(first->data%n)<<","<<(first->data)/n<<") to " <<second->data<<":("<<(second->data%n)<<","<<(second->data)/n<<") and vice versa\n";
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
	
    unordered_map <int,GridNode*>  getallNodes(){
        return vertices;
    }
	
    GridNode* getNode(int nodeValue){
	if ( vertices.find(nodeValue) == vertices.end() )  
	    return NULL;
	else
	    return vertices.find(nodeValue)->second;
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
            graph1.vertices.insert(make_pair(node[i]->data,node[i])); 
        
          }
        }
      }
    }
    return graph1;
}
int manhattanDist(GridNode* current,GridNode* dstNode,int n){
    int cx=(current->data)%n;//current square
    int cy=(current->data)/n;
    int gx=(dstNode->data)%n;//goal suare
    int gy=(dstNode->data)/n;
    int h = abs(cx-gx) + abs(cy-gy);
    return h;
}

 // the node with the smallest g+h value not yet finalized.
GridNode* minDist(unordered_map<GridNode*, pair<int, int>>& distances, unordered_set<GridNode*>& visited) {
  GridNode* ans = nullptr;
  int m = INT_MAX;
  for (auto p : distances) 
    if (!visited.count(p.first) && (p.second.first+p.second.second) <= m) {
      m = p.second.first+p.second.second;
      ans = p.first;
    }
  return ans;
}
void generatePath(unordered_map<GridNode*,GridNode*> parent,vector<GridNode*> &path,GridNode* sourceNode,GridNode* curr){
  if (curr==sourceNode)
     return;
  curr=parent[curr];
  path.push_back(curr);
  generatePath(parent,path,sourceNode,curr);
}
//********************************question 6d)*******************************

vector<GridNode*> astar(GridNode* sourceNode,GridNode* dstNode,int n){
   vector<GridNode*> path;

   unordered_set<GridNode*> visited;
   // stores predecessor of a vertex 
   unordered_map<GridNode*,GridNode*> parent;
   
   int h=0;
   //1.Create an empty map of nodes to pairs of distances (g, h). g is the distance so far, and h is the estimated distance to the goal using the heuristic. 
   unordered_map<GridNode*, pair<int, int>> distances;
   //2.Calculate the heuristic value for the origin h  
   h=manhattanDist(sourceNode,dstNode,n);
   //set the distance for the origin to (0, h).
   distances.insert(make_pair(sourceNode, make_pair(0,h))); 
   // Let curr be the origin.
    GridNode* curr=sourceNode;
   //3.While curr is not the destination node:
    while(curr!=NULL){
        //a.“Finalize” curr.
        visited.insert(curr);
       
        //b.Iterate over its neighbors, “relax” each neighbor:
        for (auto neighbor :curr->neighbors){
            
            //if the node is not present in the hashmap, its distance will be infinity
            if ( distances.find(neighbor) == distances.end() )  {
                    distances.insert(make_pair(neighbor, make_pair(INT_MAX,0)));
                    parent.insert(make_pair(neighbor, nullptr));   
						}
            //c.For each neighbor that is not finalized, update its distance (if less than the current g value) to the sum of curr’s distance and the weight of the edge between curr and this neighbor.                
            if  (!visited.count(neighbor)&&(distances[curr].first+1)<distances[neighbor].first){
                   distances[neighbor].first = distances[curr].first + 1;
                   //Calculate the heuristic value for this neighbor
                   h=manhattanDist(neighbor,dstNode,n); 
                   //and assign it to h.
                   distances[neighbor].second = h;
                   parent[neighbor] = curr;
                }          
        }
        //d.Set curr to the next min node.
          curr=minDist(distances,visited);
    }
    //4.Return path from source to destination 
    if ( parent.find(dstNode) == parent.end()){  
       cout<<"\nThere is not path between "<< sourceNode->data<<" and "<<dstNode->data;
		}
    else{
        path.push_back(dstNode);
        generatePath(parent,path,sourceNode,dstNode);
     }
      
   return path; 
}
int main(){
   int n = 3; //node i is (i%n,i/n)->node 0 is (0,0), node 1 is (1,0), node 2 is (2,0) 
   cout<<"Undirected graph"<<endl;
   GridGraph graph1=createRandomGridGraph(n);
   GridNode* sourceNode=graph1.getNode(0);//node zero is (0,0)
   GridNode* destNode=graph1.getNode(n*n-1);//node 99 is (99,99)
   vector<GridNode*> path;
   cout<<"\nPath from "<<sourceNode->data<<":("<<(sourceNode->data%n)<<","<<(sourceNode->data)/n<<") to " <<destNode->data<<":("<<(destNode->data%n)<<","<<(destNode->data)/n<<")"<<endl;

   path=astar(sourceNode,destNode,n);
   for (auto p : path) {
          cout<<p->data<<"("<<(p->data)%n<<","<<(p->data)/n<<")<-";
      } 
   return(0);
}
