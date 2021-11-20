#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <random>
#include <stack>
#include <chrono>
#include <algorithm>
 
using namespace std;
using namespace std::chrono;


int printMatrix(vector<vector<double>> matrix){
    for (int i = 0; i < matrix.size(); i++){
            for (int j = 0; j < matrix[i].size(); j++){
            cout << matrix[i][j] << ' ';
            }
            cout << endl;
        }
    return 0;
}

int main(){
    int noVertices;
    cin >> noVertices; 
    
    vector<vector<double>> coordinates(noVertices, vector<double>(2));
    for(int i = 0; i < noVertices; i++) {
        cin >> coordinates[i][0];
        cin >> coordinates[i][1];
    }
    printMatrix(coordinates);
    
    


    return 0; 
}