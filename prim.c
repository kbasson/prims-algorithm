/*
    Name: Karanvir Basson
    Title: Prim's MST Algorithm
    Date: 05-08-2022
*/

#include "prim.h"

int main() {

    int adjacencyMatrix[NUM_NODES][NUM_NODES]; //Integer matrix representing adjacency matrix
    int res = getAdjacencyMatrix(adjacencyMatrix); //Initialize adjacency matrix from file
    if (res == 0) return -1; //If file read doesn't work

    Node* nodes[NUM_NODES]; //Array of nodes in graph

    for (int i = 0; i < NUM_NODES; i++) { //Create all nodes in array

        nodes[i] = createNode(i); //Create node
        if (nodes[i] == NULL) return -1; //If node creation fails

    }

    int numEdges = connectNodes(nodes, adjacencyMatrix); //Connect all nodes using adjacency matrix
    if (numEdges < 0) return -1; //If node connection fails

    printf("numEdges = %d\n", numEdges);

    Node* mst = prims(nodes, numEdges);
    printMST(mst);
    freeMST(mst);

    for (int i = 0; i < NUM_NODES; i++) { //For all nodes

        freeNode(nodes[i]); //Free current node

    }

    return 1;

}
