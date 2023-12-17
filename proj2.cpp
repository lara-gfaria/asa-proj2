#include <iostream>
#include <vector>
#include <stack>
#include <list>
#define max(a, b) (a > b ? a : b)

using namespace std;

enum Color { WHITE, GREY, BLACK };
//white- not visited
//grey - being visited
//black - visited

class Graph {

public:
    int vertices;
    vector<vector<int>> adjacencyList;

    Graph(int v) : vertices(v), adjacencyList(v + 1) {}

    void addConnection(int u, int v) {
        adjacencyList[u].push_back(v);
    }


    list<int> DFS(int startVertex) {
        vector<Color> color(vertices + 1, WHITE);
        stack<int> vertexStack;
        list<int> orderedVertices;                           // list to store vertices in descending order of time

        for (int v = 1; v <= vertices; ++v) {
            if (color[v] == WHITE) {
                vertexStack.push(v);

                while (!vertexStack.empty()) {
                    int currentVertex = vertexStack.top();
                    vertexStack.pop();

                    if (color[currentVertex] == WHITE) {
                        color[currentVertex] = GREY;
                        vertexStack.push(currentVertex);

                        for (int adjacentVertex : adjacencyList[currentVertex]) {
                            if (color[adjacentVertex] == WHITE) 
                                vertexStack.push(adjacentVertex);
                        }
                    } 
                    else if (color[currentVertex] == GREY) {
                        color[currentVertex] = BLACK;
                        orderedVertices.push_front(currentVertex);
                    }
                }
            }
        }
        return orderedVertices;
    }


    int calculateMaxJump(Graph tpGraph){
        vector<Color> color(vertices + 1, WHITE);
        vector<int> dp(vertices + 1, 0);                     // stores the max jumps for each subproblem (each vertex)   
        stack<int> vertexStack;

        // do DFS in original graph
        list<int> orderedVertices = DFS(1);                  // start DFS at vertex 1

        int maxJump = 0;
        
        // do DFS in transpose graph
        for(const int& v: orderedVertices){
            if (color[v] == WHITE) {
                vertexStack.push(v);
                while (!vertexStack.empty()) {
                    int currentVertex = vertexStack.top();
                    vertexStack.pop();

                    if (color[currentVertex] == WHITE) {
                        color[currentVertex] = GREY;
                        vertexStack.push(currentVertex);

                        for (int adjacentVertex : tpGraph.adjacencyList[currentVertex]) {
                            if (color[adjacentVertex] == WHITE){
                                vertexStack.push(adjacentVertex);
                            }   
                            dp[currentVertex] = max(dp[currentVertex], dp[adjacentVertex] + 1);
                            maxJump = max(maxJump, dp[currentVertex]);  
                        }
                    } 
                    else if (color[currentVertex] == GREY) {
                        color[currentVertex] = BLACK;
                    }
                }
            }
        }
        return maxJump;
    }
     

};



int main(){
    int numInd, numConnect;                                  // reads graph information
    scanf("%d %d", &numInd, &numConnect);                    // num_ind -> num of vertices; num_connect -> num of edges
    
    if(numInd < 2 || numConnect < 0) {                       // checks arguments
        printf("Invalid arguments\n");
        return 1;
    }

    Graph TugaNet(numInd);                                   // create graph
    Graph transposeTugaNet(numInd);                          // create transpose graph
    
    for (int i = 0; i < numConnect; i++){          
        int u, v;
        scanf("%d %d", &u, &v);
        TugaNet.addConnection(u, v);                         // adds the edges to the graph
        transposeTugaNet.addConnection(v, u);                // adds reverse edges to transpose graph
    } 
    
    int maxJump = TugaNet.calculateMaxJump(transposeTugaNet);
    printf("%d\n", maxJump);

 /*
    // PRINT PARA VERIFICAR SE A 1ªDFS ESTÁ CERTA ******************************
    list<int> result = TugaNet.DFS(1);
    printf("ordem decrescente de tempos finais:\n");
    for (const int& element : result) {
        printf("    vertice: %d\n",element);
    }
    // *************************************************************************
*/
    return 0;
}