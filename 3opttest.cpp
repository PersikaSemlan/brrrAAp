#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <random>
#include <stack>
#include <algorithm>
 
using namespace std;

vector<int> path;
//Just for printing methods (felsökning typ)
void printMatrix(vector<vector<int>> matrix){
    for (int i = 0; i < matrix.size(); i++){
            for (int j = 0; j < matrix[i].size(); j++){
                cout << matrix[i][j] << ' ';
            }
            cout << endl;
        }
}


//Christofides ?
// jämnt antal shows i parents eller existerar inte i parents

//Gets the neighbours from the parent vector
vector<vector<int>> neighbours(vector<int> parents, int noVertices){
      vector<vector<int>> neighbours(noVertices, vector<int>(1));

    for(int i = 1; i < noVertices; i++){
        int index = parents[i]; //9
        neighbours[index].push_back(i); 
        neighbours[i].push_back(index);
    }
    return neighbours;
}

//Sets current node as visited and traverses the MST until all vertices are visited.
vector<bool> recursDFS(vector<vector<int>> neighbours, vector<bool> isVisited, int currentVertex){
    isVisited[currentVertex] = true;
    path.push_back(currentVertex);

    for(int v = 1; v < neighbours[currentVertex].size(); v++){
        if(!isVisited[neighbours[currentVertex][v]]){
            isVisited = recursDFS(neighbours, isVisited, neighbours[currentVertex][v]);
        }
    }
    return isVisited;
}

//Setup for recursive DFS
void DFS(vector<vector<int>> neighbours, int noVertices){
    vector<bool> isVisited(noVertices, false);
    int currentVertex = 0;
    isVisited = recursDFS(neighbours, isVisited, currentVertex);
    //path.push_back(0);
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

    // 2. Find shortest edge from source in adjMatrix, then find next shortest edge to unvisited node etc
    for(int i = 0; i < (noVertices - 1); i++){ 
        int minDistance = INT32_MAX;
        int closestIndex = i; 
        
        for(int v = 0; v < noVertices; v++) {
            if (isIncluded[v] == false && shortestDist[v] < minDistance){
                minDistance = shortestDist[v]; 
                closestIndex = v;   
            }
        } 
        isIncluded[closestIndex] = true;
    
    // 3. Update parents, to keep track of route
        for(int c = 0; c < noVertices; c++){
            if(adjMatrix[closestIndex][c] && isIncluded[c] == false && adjMatrix[closestIndex][c] < shortestDist[c]){
                parents[c] = closestIndex;
                shortestDist[c] = adjMatrix[closestIndex][c];
            }
        }
    }
    return parents;
}


void threeOpt(vector<vector<int>> adjMatrix, int N) {
    int node1, node2, node3, node4, node5, node6;
    double newTour[5];
    int maxIterations = 1;
    int iterations = 0;
    do{
        for(int i = 1; i < N-2; i++) 
			for(int j = N - 2; j>i+2; j--)  
                for(int k = j+2; k < N + (i > 0); k++) {
                    node1 = path[i-1];
                    node2 = path[i];
                    node3 = path[j-1];
                    node4 = path[j];
                    node5 = path[k-1];
                    node6 = path[k % (path.size() - 1)];

                    newTour[0] = adjMatrix[node1][node2] + adjMatrix[node3][node4] + adjMatrix[node5][node6];
                    newTour[1] = adjMatrix[node1][node3] + adjMatrix[node2][node4] + adjMatrix[node5][node6];
                    newTour[2] = adjMatrix[node1][node2] + adjMatrix[node3][node5] + adjMatrix[node4][node6];
                    newTour[3] = adjMatrix[node1][node4] + adjMatrix[node5][node2] + adjMatrix[node3][node6];
                    newTour[4] = adjMatrix[node6][node2] + adjMatrix[node3][node4] + adjMatrix[node5][node1];

                    vector<int> swap;
                    int tmp = i;

                    if(newTour[0] > newTour[1])
                        reverse(path.begin() + (i+1), path.begin() + (j));
                    else if(newTour[0] > newTour[2])
                        reverse(path.begin() + (j+1), path.begin() + (k));
                    else if(newTour[0] > newTour[4])
                        reverse(path.begin() + (i+1), path.begin() + (k));
                    
                    else if(newTour[0] > newTour[3]) {
                        swap = path;
                        for(int l = j; l < k; l++) {
                            path[tmp++] = swap[l];

                        }

                        for(int l = i; l < j; l++) {
                            path[tmp++] = swap[l];
                        }
                          
                    }
                    
                }  


        iterations++;
    }while(iterations < maxIterations);




}











void twoOpt(vector<vector<int>> adjMatrix, int N) {
 
    //För varje kant, testa byt ut mot kanter du får (Du får bara byta 2 kanter om kanterna ej delar någon nod)
    //Kolla för varje bytt kant, om kostnaden blir mindre
    //Om ett byte ger lägre kostnad, fortsätt på samma sätt från den "nya" grafen.
    //Sluta om ingen ny graf är strikt billigare
 
    int currentWeight1, currentWeight2, newWeight1, newWeight2, mini, minj;
    int iterations = 0;
    int maxIterations = 300;
    int minChange;
    do {
        minChange = 0;
        for(int i = 0; i < N - 2; i++) 
            for(int j = i + 2; j < N; j++) {

                //cout << i << 'i' << endl;
               // cout << j << 'j' << endl;

                //Weight on edges we try to swap
                newWeight1 =  adjMatrix[path[i]][path[i+1]];
                newWeight2 = adjMatrix[path[j]][path[(j+1)%(N-1)]];
 
                //Weight on new edges
                currentWeight1 = adjMatrix[path[i]][path[j]];
                currentWeight2 = adjMatrix[path[i+1]][path[(j+1)%(N-1)]];
                
                int change = currentWeight1 + currentWeight2 - newWeight1 - newWeight2;
                
                if(minChange > change) {
                    //cout << minChange << " " << change << endl;
                    minChange = change;
                    mini = i;
                    minj = j;
                } 
            }
        reverse(path.begin() + (mini+1), path.begin() + (minj + 1));
        iterations++;
    } while(iterations < maxIterations && minChange < 0);
}

//Create initial adjacency matrix           
// Optimize: change from 2D matrix to list to avoid double counting, potentially doubles
vector<vector<int>> getAdjMatrix(vector<vector<double>> coordinates, int noVertices){
    vector<vector<int>> adjMatrix(noVertices, vector<int>(noVertices));
    for (int i = 0; i < noVertices; i++) {
        for (int j = 0; j <= i; j++) {
            if(i == j) {
                adjMatrix[i][j] = INT32_MAX; //If self set distance to "infinity"
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
    //printMatrix(adjMatrix);

    vector<int> parents = primMST(coordinates, adjMatrix, noVertices);

    vector<vector<int>> neighbourList = neighbours(parents, noVertices);

    DFS(neighbourList, noVertices);
    //twoOpt(adjMatrix, path.size());
    threeOpt(adjMatrix, path.size());

    for (int j = 0; j < path.size(); j++){
        cout << path[j] << endl;
    }

    return 0; 
}