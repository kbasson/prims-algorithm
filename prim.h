/*
    Name: Karanvir Basson
    Title: Prim's MST Algorithm
    Date: 05-08-2022
*/

//INCLUDE HEADER FILES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_NODES 7 //Number of nodes in graph
#define FILENAME "graph.txt" //Name of file containing adjacency matrix
#define INF_VAL 100 //Number used to represent infinity

typedef struct node { //Struct representing graph node

    int ID; //ID of node
    int visited; //Integer indicating if node has been visited
    struct edge* edges; //List of edges

} Node;

typedef struct edge { //Struct representing graph edge

    int weight; //Weight of edge
    int inMST; //Int to indicate if edge is currently in MST

    struct node* dest; //String containing destination node ID
    struct edge* next; //Pointer to next edge

} Edge;

int getAdjacencyMatrix(int adjacencyMatrix[NUM_NODES][NUM_NODES]); //Given a file containing an adjacency matrix and store it in 2d array
int connectNodes(Node* nodes[NUM_NODES], int adjacencyMatrix[NUM_NODES][NUM_NODES]); //Given a list of nodes and an adjacency matrix, create graph edges

Node* createNode(int ID); //Given an id, create a node with that id
void freeNode(Node* node); //Given a node, free it

Edge* createEdge(Node* dest, int weight); //Given a destination and a weight, create edge
void addEdge(Edge** root, Edge* new); //Add new edge to list of edges in node

Node* prims(Node* nodes[NUM_NODES], int numEdges); //Construct MST using Prims Algorithm
void printMST(Node* mst); //Print the nodes of MST
void freeMST(Node* mst); //Free the nodes of MST
