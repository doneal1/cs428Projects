#include<iostream>
#include<fstream>
#include<stdio.h>
#include<vector>
#include <utility>
#include <string>
using namespace std;

int main(int argc, char * argv[]){
	if(argc != 4){
		cout << "Run as ./dijkstra file.txt nodeSize start, where:\n file.txt is the file containing adjacency matrix \nnodeSize is the number of nodes \nstart is the starting node from 0 to nodeSize-1.\n";
		return 1;
	}

	ifstream adjFile;
	adjFile.open(argv[1]);
	if(!adjFile.is_open()){
		cout << "Could not open file.\n";
		return 1;
	}

	vector<vector<int>> adjMatrix;
	int nodeSize = argv[2];
	int startNode = argv[3];
	
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
	return 0;
}

vector<int> dijkstra(vector<vector<int>> adj, int nSize, int start){
	vector<int> retPath;
	
	int nextNode = start;
	vector<pair<int,int>> minPath;
	
	for(int i = 0; i < nSize; i++){
		if(adj[start][i] >= 0) 
			minPath.push_back(make_pair(adj[start][i], start));
		else
			minPath.push_back(-1, -1));
	}	
	
	while(retPath.size < nSize){
		retPath.push_back(nextNode);
	}
}
