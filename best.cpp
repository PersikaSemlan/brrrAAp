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

//Create initial adjacency matrix
//If self set distance to "infinity"
vector<vector<int>> getAdjMatrix(vector<vector<double>> coordinates, int noVertices){
    vector<vector<int>> adjMatrix(noVertices, vector<int>(noVertices));
    for (int i = 0; i < noVertices; i++) {
        for (int j = 0; j <= i; j++) {
            if(i == j) {
                adjMatrix[i][j] = 100000000;
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