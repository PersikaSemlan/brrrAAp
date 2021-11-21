#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <random>
#include <stack>
#include <algorithm>
 
using namespace std;

//Just for printing methods (felsökning typ)
void printMatrix(vector<vector<int>> matrix){
    for (int i = 0; i < matrix.size(); i++){
            for (int j = 0; j < matrix[i].size(); j++){
            cout << matrix[i][j] << ' ';
            }
            cout << endl;
        }
}

//Uses Prim's algorithm to calculate the minimum spanning tree (MST)
vector<int> primMST( vector<vector<double>> coordinates, vector<vector<int>> adjMatrix, int noVertices){ 
    vector<int> parents(noVertices); //stores parents to indices (children)
    vector<bool> isIncluded(noVertices, false); //bitmap
    vector<int> shortestDist(noVertices);

    // 1. Initialize source vertex, and initialize distance to all other vertices to "infinity"
    shortestDist[0] = 0; 
    parents[0] = -1; 
    isIncluded[0] = true;

    for(int i = 1; i < noVertices; i++)
        shortestDist[i] = INT32_MAX; 

    // 2. Find shortest edge from source in adjMatrix 
    int minDistance = INT32_MAX, closestIndex; 
    
    for (int v = 0; v < noVertices; v++)
        if (isIncluded[v] == false && shortestDist[v] < minDistance){
            minDistance = shortestDist[v]; 
            closestIndex = v;
        }
            
    // 3. Find next shortest edge to unvisited node
    // 4. Continue until isIncluded is all true


    return parents;
}


//Create initial adjacency matrix           If self set distance to "infinity"
// Optimize: change from 2D matrix to list to avoid double counting
vector<vector<int>> getAdjMatrix(vector<vector<double>> coordinates, int noVertices){
    vector<vector<int>> adjMatrix(noVertices, vector<int>(noVertices));
    for (int i = 0; i < noVertices; i++) {
        for (int j = 0; j <= i; j++) {
            if(i == j) {
                adjMatrix[i][j] = INT32_MAX;
            } else {
                adjMatrix[i][j] = round(sqrt(pow(coordinates[i][0] - coordinates[j][0], 2)+ pow(coordinates[i][1] - coordinates[j][1], 2)));
                adjMatrix[j][i] = adjMatrix[i][j];
            }
        }
    }
    return adjMatrix;
 }


int main(){
    int noVertices;
    cin >> noVertices; 
    
    vector<vector<double>> coordinates(noVertices, vector<double>(2));
    for(int i = 0; i < noVertices; i++) {
        cin >> coordinates[i][0];
        cin >> coordinates[i][1];
    }

    //printMatrix(coordinates);
    vector<vector<int>> adjMatrix = getAdjMatrix(coordinates, noVertices);
    printMatrix(adjMatrix);




    return 0; 
}