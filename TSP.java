import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

class Node {                                                            
    double x;
    double y;
    int id;
    
    public Node (double x, double y, int id) {                          
        this.x = x;
        this.y = y;
        this.id = id;
    }
}

public class TSP {
    
    public static int N;
    
    public static void main(String[] args) {
        //Read input
        Scanner in = new Scanner(System.in);
        N = Integer.parseInt(in.nextLine());
        
        Node[] nodes = new Node[N];
        for(int i = 0; i < N; i++) 
            nodes[i] = new Node(Double.parseDouble(in.next()), Double.parseDouble(in.next()), i);          
        
        //Build adjacency matrix
        int[][] adjMatrix = new int[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = i; j < N; j++) {
                if(i == j) {
                    adjMatrix[i][j] = Integer.MAX_VALUE;
                } else {
                    adjMatrix[i][j] = adjMatrix[j][i] = (int)Math.round(Math.sqrt(Math.pow(nodes[i].x - nodes[j].x, 2) + Math.pow(nodes[i].y - nodes[j].y, 2)));
                }
            }
        }
        ArrayList<Node> tour = twoOpt(nearestNeighbour(adjMatrix, nodes), adjMatrix);
        
        for(int i = 0; i < N; i++) 
            System.out.println(tour.get(i).id);

        
        in.close();
    }
    
    //Applies the Nearest Neighbour heuristic - find all closest unvisited neighbours
    public static ArrayList<Node> nearestNeighbour(int[][] adjMatrix, Node[] nodes) {
        /*
            https://iq.opengenus.org/approximation-algorithm-for-travelling-salesman-problem/
            1. Let 0 be the starting and ending point for salesman.
            2. Construct Minimum Spanning Tree from with 0 as root using Prim’s Algorithm.
            3. List vertices visited in preorder walk/Depth First Search of the constructed MST and add source node at the end.


        */
        Node current = nodes[0];
        ArrayList<Node> tour = new ArrayList<Node>();
        tour.add(current);
     
        while(tour.size() < N){
            final Node a = current;
            
            int index = -1;
            double minCost = Double.MAX_VALUE;

            for(int i = 0; i<=N-1; i++){
                double currCost = adjMatrix[a.id][i];                                           
                if(currCost < minCost && !tour.contains(nodes[i])){
                    minCost = currCost;
                    index = i;
                }
            }
            current = nodes[index];
            tour.add(current);
        }
        return tour;
    }
    
    
    //Update the tour with the latest best edges and their corresponding nodes                      
    public static ArrayList<Node> twoChange(ArrayList<Node> tour, int i, int j) {
        ArrayList<Node> head = new ArrayList<Node>();
        ArrayList<Node> tail = new ArrayList<Node>();
        ArrayList<Node> improved = new ArrayList<Node>();
        ArrayList<Node> newTour = new ArrayList<Node>(N);
        
        head.addAll(tour.subList(0, i + 1));         //Get all first edges that are the same as the old tour
        improved.addAll(tour.subList(i + 1, j));     //Get the improved edges
        Collections.reverse(improved);               //Reverse for correct order

        newTour.addAll(head);
        newTour.addAll(improved);

        if(j >= N) {                             //If we are adding to the end of the tour, no tail needed bc new edges are tail
            return newTour;
        }
        else {                                           //If we are adding in the middle of the tour, tail needed
            tail.addAll(tour.subList(j, N));     //Get all last edges that are the same as the old tour
            newTour.addAll(tail);
            return newTour;
        }   
    }

    
    //Decrease in cost = New cost - Previous cost                                                                   går att optimera - bara return ingen diff
    public static int compareCost(int[][] adjMatrix, int i, int j, ArrayList<Node> tour) {
        if(j >= N) {    //Last edge pair
            return (adjMatrix[tour.get(i).id][tour.get(N - 1).id] + adjMatrix[tour.get(i + 1).id][tour.get(0).id]) - (adjMatrix[tour.get(i).id][tour.get(i + 1).id] + adjMatrix[tour.get(N - 1).id][tour.get(0).id]);
        }
        else {
            return (adjMatrix[tour.get(i).id][tour.get(j - 1).id] + adjMatrix[tour.get(i + 1).id][tour.get(j).id]) - (adjMatrix[tour.get(i).id][tour.get(i + 1).id] + adjMatrix[tour.get(j - 1).id][tour.get(j).id]);
        }
    }
    
    //For each pair of edges in the tour try to exdiff them. Try to decrease the cost as much as possible.
    public static ArrayList<Node> twoOpt(ArrayList<Node> path, int[][] adjMatrix) {
        ArrayList<Node> tour = (ArrayList<Node>) path.clone();
        int decrease = -1;
        while(decrease < 0) {                                                   
            decrease = 0;
            for(int i = 0; i < N - 2; i++) {                                    //Maximum number of shared edges between two distinct tours - without start and end node- max allowed change: 2 edges
                for(int j = i + 3; j < N + 1; j++) {                            //Remove 3 nodes because 2 edges where removed
                    int diff = compareCost(adjMatrix, i, j, tour);   
                    if(decrease > diff) {
                        decrease = diff;
                        tour = twoChange(tour, i, j);
                    }
                }
            }
        }
        return tour;                    //When no more decreases can be made return the tour
    }

}