#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <climits>
#include <string>
#include <time.h>
#include <stdlib.h>
using namespace std;

struct graphNode {
  string data;
  unordered_map<graphNode*, int> neighbors;
  graphNode* next;
};

//********************************question 5b)*******************************
class WeightedGraph {
  private:
    
  public:
    vector<graphNode*> vertices;
    graphNode* addNode(string nodeVal){
          graphNode* node = new graphNode; 
          node->data = nodeVal;// assign data to the new node 
          node->neighbors = {};
          return node;
    }
    void addWeightedEdge(graphNode* first,graphNode* second,int edgeWeight){
         // Add an edge from first to second. A new element is inserted to the neighbors of first. 
        first->neighbors.insert(make_pair(second,edgeWeight)); 
    }
    void removeDirectedEdge(graphNode* first,graphNode* second){
     
        // remove the edge from first. A element is deleted to the neighbors of first. 
         first->neighbors.erase(second); 
    }
    vector <graphNode*>  getallNodes(){
        return vertices;
    }
    graphNode* getNode(string nodeValue){
        for (auto u : vertices){
          if (u->data==nodeValue){
            return u;
          }
        }
        return NULL;

    }
  
};
vector<int> getRandomWeight(int n){
      int totalEdges=n*(n-1);
      unordered_set<int> uniqList; 
      srand(time(NULL));
      vector <int> numList;
      int num;
      int i=0;
      while(i<totalEdges){
        num=rand()%totalEdges+1;
        //cout<<num<<endl;
        i++;
        if (uniqList.find(num) == uniqList.end()){//the number is not in the set
            uniqList.insert(num); 
            numList.push_back(num);//push it to the list 
        }
        else //the number is in the set, so decrease the counter i by one to generate a new random number
         i=i-1;
      }
     
      return numList;

  }
//********************************question 5c)*******************************    
WeightedGraph createRandomUnweightedGraphIter(int n){
    WeightedGraph graph1;
    graphNode**	node = new graphNode*[n]();
    for (int i = 0; i < n; ++i){
      string nodeVal=to_string(i);
      node[i] = graph1.addNode(nodeVal);
    }
    int weightIndex=0;
    vector<int> numWeight=getRandomWeight(n);
    for (int i=0;i<n;i++){
      for (int j=0;j<n;j++){
        if (i!=j){
          graph1.addWeightedEdge(node[i],node[j],numWeight[weightIndex]);
          cout<<"from "<<node[i]->data<<" to "<<node[j]->data<<" Weight is "<<numWeight[weightIndex]<<"\n";
          weightIndex++;
          graph1.vertices.push_back(node[i]);
        }
      }
    }
    
    return graph1;
}
//********************************question 5d)*******************************
WeightedGraph createLinkedList(int n){
    WeightedGraph graph1;
    graphNode**	node = new graphNode*[n]();// initialize head pointer for all vertices
    for (int i = 0; i < n; ++i){
      string nodeVal=to_string(i);
      node[i] = graph1.addNode(nodeVal);
    }
    int i;
    for (i = 0; i < n-1; i++){// add edges to the directed graph
        node[i]->next = node[i+1]; // Link first node with second
        graph1.addWeightedEdge(node[i],node[i+1],1);
        graph1.vertices.push_back(node[i]);//add the node to vertices
        
    }
     graph1.vertices.push_back(node[i]);
    return graph1;
}
graphNode* minDist(unordered_map<graphNode*, int>& distances, unordered_set<graphNode*>& visited) {
  graphNode* ans = nullptr;
  int m = INT_MAX;
  for (auto p : distances) 
    if (!visited.count(p.first) && p.second <= m) {
      m = p.second;
      ans = p.first;
    }
  return ans;
}
//********************************question 5e)*******************************
unordered_map<graphNode*, int> djkstras(graphNode* start){
      unordered_map<graphNode*, int> distances;
      unordered_set<graphNode*> visited;

     // Set the distance for the origin to 0.
     distances.insert(make_pair(start, 0)); 
     // Let curr be the origin.
     graphNode* curr=start;
     // While curr is not null and its distance is not infinity.
     while(curr!=NULL && distances[curr]!=INT_MAX){
          visited.insert(curr);// “Finalize” curr.
          // Iterate over its neighbors, “relax” each neighbor:
          for (auto neighbor :curr->neighbors){  
                 
              //if the node is not present in the hashmap, its distance will be infinity
              if ( distances.find(neighbor.first) == distances.end() )  
                    distances.insert(make_pair(neighbor.first, INT_MAX));    
              // For each neighbor that is not finalized, update its distance (if less than its current distance) to the sum of curr’s distance and the weight of the edge between curr and this neighbor.
               if  (!visited.count(neighbor.first)&&(distances[curr]+neighbor.second)<distances[neighbor.first])
                             
               			distances[neighbor.first] = distances[curr] + neighbor.second; 		                 
          }

          // Set curr to the next min distance node – the node with the smallest distance that is not yet finalized.
          curr=minDist(distances,visited);
     }
  return  distances;
}
 

int main(){
   int n = 5; 
   WeightedGraph graph1=createRandomUnweightedGraphIter(n);
   unordered_map<graphNode*, int> distances;
   distances=djkstras(graph1.getNode("0"));
  for (auto curr=distances.begin(); curr!=distances.end(); ++curr){//go through each key
        	cout << "Path from vertex 0 to vertex " << curr->first->data << " has minimum cost of " << curr->second << "\n";
        
  }
	
   return(0);
}
