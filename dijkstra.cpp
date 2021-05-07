#include<iostream>
#include<fstream>
#include<climits>
#include<stdio.h>
#include<vector>
#include <utility>
#include <string>
using namespace std;


vector<int> dijkstra(vector<vector<int>> adj, int nSize, int start){
	vector<int> retPath; //return value that contains completed least cost path

	bool visited[nSize]; //array used to check whether a node is already in the path
	pair<int,int> minPath[nSize]; //contains the minimum cost edges for each step of the algorithm
	int nextNode = start;
	
	
	for(int i = 0; i < nSize; i++){
		if(adj[start][i] > 0) minPath[i] = make_pair(adj[start][i], start);
		else minPath[i] = make_pair(-1, -1); //no direct edge between start and node i
		visited[i] = false;
	}	
	
	while(retPath.size() < nSize){
		retPath.push_back(nextNode);
		visited[nextNode] = true;
		for(int i = 0; i < nSize; i++){
			if(!visited[i] && adj[nextNode][i] > 0){
				if(minPath[i].first == -1 || adj[nextNode][i] < minPath[i].first){
					minPath[i].first = adj[nextNode][i];
					minPath[i].second = nextNode;
				}
			}
		}
		
		int minNode = 0, minCost = INT_MAX;
		for(int i = 0; i < nSize; i++){
			if(!visited[i]){
				if(minPath[i].first != -1 && minPath[i].first<minCost){
					minCost = minPath[i].first;
					minNode = i;
				}	
			}
		}
		
		nextNode = minNode;
	}

	return retPath;
}

/*
* The program takes a file containing an adjacency matrix for nodes 0 to nodeSize-1, where
* entry (i,j) is the edge weight between nodes i and j.
*
* For any two nodes with no edges connecting them, the weight is set to -1. 
*/
int main(int argc, char * argv[]){
	if(argc != 4){
		cout << "Run as ./dijkstra fileName nodeSize start, where:\n  fileName is the file containing the adjacency matrix \n  nodeSize is the number of nodes \n  start is the starting node from 0 to nodeSize-1.\n";
		return 1;
	}

	ifstream adjFile;
	adjFile.open(argv[1]);
	if(!adjFile.is_open()){
		cout << "Could not open file.\n";
		return 1;
	}

	vector<vector<int>> adjMatrix;
	int nodeSize = stoi(argv[2]);
	int startNode = stoi(argv[3]);
	
	//Filling out the matrix
	for(int i = 0; i < nodeSize; i++){
		vector<int> row;
		for(int j = 0; j < nodeSize; j++){
			int dist;
			adjFile >> dist;
			row.push_back(dist);
		}
		adjMatrix.push_back(row);
	}

	vector<int> path = dijkstra(adjMatrix, nodeSize, startNode);
	cout << "Shortest path: " << path[0];
	for(int c = 1; c < path.size(); c++){
		cout << ", " << path[c];
	}
	cout << "\n";
	return 0;
}

