#include <fstream>
#include <iostream>
#include <cstdio>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <unistd.h>
#include <stack>

using namespace std;

double distance(int point1[], int point2[])
{
    double distance = sqrt(pow((point2[0] - point1[0]), 2) + pow((point2[1] - point1[1]), 2));
    return distance;
}

int main()
{
    // receive input
    int numVertices = 0;
    cin >> numVertices;

    // global variables
    double vertices[numVertices][2];
    for (int i = 0; i < numVertices; i++)
    {
        cin >> vertices[i][0] >> vertices[i][1];
    }
    int finalTour[numVertices];

    // greedy algorithm
    // variable initialization for greedy
    bool greedyVisited[numVertices];
    int greedyTour[numVertices];
    greedyTour[0] = 0;
    greedyVisited[0] = true;
    for (int i = 1; i < numVertices; i++)
    {
        greedyTour[i] = -1;
        greedyVisited[i] = false;
    }

    // find the  greedy Tour
    for (int i = 1; i < numVertices; i++)
    {
        int closestNeighbour = -1;
        double closestDistance = INFINITY;
        for (int j = 0; j < numVertices; j++)
        {
            if (greedyVisited[j] == false)
            {
                int currentVertexIndex = greedyTour[i - 1];
                double currentDistance = distance(vertices[currentVertexIndex], vertices[j]);
                if (currentDistance < closestDistance)
                {
                    closestDistance = currentDistance;
                    closestNeighbour = j;
                }
            }
        }
        greedyTour[i] = closestNeighbour;
        greedyVisited[closestNeighbour] = true;
    }
    
    for(int i = 0; i< numVertices; i++)
        printf("\n Vertice no: %d", greedyTour[i]);

    // 2-opt algorithm
    // http://on-demand.gputechconf.com/gtc/2014/presentations/S4534-high-speed-2-opt-tsp-solver.pdf
    // variable initialization for 2-opt
    int mini;
    int minj;
    double minChange;
    int iter = 0;
    int maxIter = 100;

    // find the 2-opt tour
    do
    {
        //check if two edges are worth swapping
        minChange = 0;
        for (int i = 0; i < numVertices - 2; ++i)
        {
            for (int j = i + 2; j < numVertices; ++j)
            {
                double currentEdge1 = distance(vertices[greedyTour[i]], vertices[greedyTour[i + 1]]);
                double currentEdge2 = distance(vertices[greedyTour[j]], vertices[greedyTour[j + 1]]);
                double newEdge1 = distance(vertices[greedyTour[i]], vertices[greedyTour[j]]);
                double newEdge2 = distance(vertices[greedyTour[i + 1]], vertices[greedyTour[j + 1]]);

                double change = newEdge1 + newEdge2 - currentEdge1 - currentEdge2;

                if (minChange > change)
                {
                    minChange = change;
                    mini = i;
                    minj = j;
                }
            }
        }

        //swap edges
        //i to j and j+1 to i+1

        stack<int> s;
        for (int i = 0; i < numVertices; ++i)
        {
            if (i > mini && i <= minj)
            {
                int temp = greedyTour[i];
            }
        }
        for (int i = mini + 1; i <= minj; ++i)
        {
            finalTour[i] = s.top();
            s.pop();
        }
        ++iter;

    } while (minChange < 0 && iter < maxIter);

    // return
    for (int i = 0; i < numVertices; i++)
    {
        cout << finalTour[i] << "\n";
    }
}