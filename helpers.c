/*
    Name: Karanvir Basson
    Title: Prim's MST Algorithm
    Date: 05-08-2022
*/

#include "prim.h"

int getAdjacencyMatrix(int adjacencyMatrix[NUM_NODES][NUM_NODES]) { //Given a file containing an adjacency matrix and store it in 2d array

    FILE* file = fopen(FILENAME, "r"); //Open file for reading

    if (file == NULL) { //If file doesn't exist

        printf("%s not found!\n", FILENAME);
        return 0;

    }
    
    for (int i = 0; i < NUM_NODES; i++) { //Initialize matrix to all zeores

        for (int j = 0; j < NUM_NODES; j++) {

            adjacencyMatrix[i][j] = 0;

        }

    }

    int size = ((NUM_NODES * 2) + 2) * sizeof(char); //Get size of string contining row of matrix
    char matrixRow[size]; //Initialize string contining row of matrix

    int i = 0; //Row index

    while (fgets(matrixRow, size, file)) { //Read matrix

        int j = 0; //Column index
        char* entry = strtok(matrixRow, " \n"); //Get current matrix entry as string

        while (entry != NULL) { //If string entry is not null

            adjacencyMatrix[i][j] = atoi(entry); //Convert string to int
            entry = strtok(NULL, " \n"); //Get next entry
            j++;

        }

        i++;

    }

    fclose(file); //Close file ptr
    return 1;

}

int connectNodes(Node* nodes[NUM_NODES], int adjacencyMatrix[NUM_NODES][NUM_NODES]) { //Given a list of nodes and an adjacency matrix, create graph edges

    int numEdges = 0;

    for (int i = 0; i < NUM_NODES; i++) { //For all rows in matrix

        for (int j = i; j < NUM_NODES; j++) { //For all columns in matrix

            if (adjacencyMatrix[i][j]) { //If edge exists

                Edge* new = createEdge(nodes[j], adjacencyMatrix[i][j]);
                if (new == NULL) return -1;
                else addEdge(&(nodes[i] -> edges), new);
            
                new = createEdge(nodes[i], adjacencyMatrix[i][j]);
                if (new == NULL) return -1;
                else addEdge(&(nodes[j] -> edges), new);

                numEdges++;

            }

        }

    }

    return numEdges;

}

Node* createNode(int ID) { //Given an id, create a node with that id

    Node* node = malloc(sizeof(Node)); //Allocate memory
    if (node == NULL) return NULL; //NULL ptr check

    //Initialize Node
    node -> ID = ID;
    node -> visited = 0;
    node -> edges = NULL;

    return node; //Return node

}

void freeNode(Node* node) { //Given a node, free it

    if (node == NULL) return; //NULL ptr check

    //FREE NODE EDGES
    while (node -> edges != NULL) {

        Edge* temp = node -> edges;
        node -> edges = node -> edges -> next;
        free(temp);

    }

    //FREE NODE
    free(node);

}

Edge* createEdge(Node* dest, int weight) { //Given a destination, create edge

    if (dest == NULL) return NULL; //NULL ptr check

    Edge* edge = malloc(sizeof(Edge)); //Allocate struct
    if (edge == NULL) return NULL; //NULL ptr check

    //INITIALIZE EDGE
    edge -> weight = weight;
    edge -> dest = dest;
    edge -> next = NULL;

    return edge; //Return newly allocated edge

}

void addEdge(Edge** root, Edge* new) {

    if (*root == NULL) {

        *root = new;

    } else {

        Edge* temp = *root; //Temp pointer to first edge

        while (temp -> next != NULL) { //Get last edge

            temp = temp -> next;

        }

        temp -> next = new; //Create edge

    }

}

Node* prims(Node* nodes[NUM_NODES], int numEdges) { //Construct MST using Prims Algorithm

    if (nodes == NULL || NUM_NODES <= 0) return NULL; //NULL ptr check

    //Create starting node for MST
    Node* mst = createNode(nodes[0] -> ID);
    if (mst == NULL) return NULL;

    Node* current = mst; //Used to create MST
    Node* temp = nodes[0]; //Used to traverse graph

    int numVisited = 0; //Number of visited nodes
    Edge* edges = NULL; //List of edges to choose from

    while (temp != NULL) { //While not all nodes visited

        printf("At node %d\n", temp -> ID);

        //Visit current node
        numVisited++; 
        temp -> visited = 1;

        Edge* curEdge = temp -> edges; //Get edges of current graph node

        while (curEdge != NULL) { //For all current graph node edges
                
            if (curEdge -> dest -> visited == 0) { //If destination hasn't been visited yet

                //addEdge(&edges, curEdge); //Add to list of edges
                printf("Added edge with weight %d and dest %d\n", curEdge -> weight, curEdge -> dest -> ID);

            }

            curEdge = curEdge -> next; //Go to next edge
            printf("Going to edge with weight %d and dest %d\n", curEdge -> weight, curEdge -> dest -> ID);

        }

        if (edges != NULL) { //If next vertex exists

            curEdge = edges; //For all edges in possible edges choices

            //Stores minimum edge from edges list
            int minCost = INF_VAL;
            Edge* minEdge = NULL;

            while (curEdge != NULL) { //For all edges in list

                if (curEdge -> weight < minCost) { //If min edge found

                    minCost = curEdge -> weight;
                    minEdge = curEdge;

                }

                curEdge = curEdge -> next;

            }

            //Create copy of destination of min edge
            Node* new = createNode(minEdge -> dest -> ID);
            if (new == NULL) return NULL;

            //Create edge from current MST node to new node
            current -> edges = createEdge(new, minCost);
            if (current -> edges == NULL) return NULL;
            
            current = new;
            temp = minEdge -> dest;

        } else {

            break;

        }

    }

    return mst;
    
}

void printMST(Node* mst) { //Print the nodes of MST

    Node* temp = mst; //Initialize traversal pointer

    while (temp != NULL) { //For all nodes in MST

        printf("currently at Node %d\n", temp -> ID);
        temp = temp -> edges -> dest;

    }

}

void freeMST(Node* mst) { //Free the nodes of MST

    while (mst != NULL) { //For all nodes in MST

        Node* temp = mst;
        mst = mst -> edges -> dest;
        freeNode(temp); //Free current node

    }

}
