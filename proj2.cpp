#include <iostream>
#include <vector>
#include <stack>
#include <list>

using namespace std;

enum Color { WHITE, GREY, BLACK };

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
        list<int> finalTimes;

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
                        finalTimes.push_front(currentVertex);
                    }
                }
            }
        }
        return finalTimes;
    }


    Graph transposeGraph() const {
        Graph transposedGraph(vertices);

        for (int v = 1; v <= vertices; ++v) {
            for (int u : adjacencyList[v]) {
                transposedGraph.addConnection(u, v);
            }
        }

        return transposedGraph;
    }
};



int main(){
    int num_ind, num_connect;                       // reads graph information
    scanf("%d %d", &num_ind, &num_connect);         // num_ind -> num of vertices; num_connect -> num of edges
    
    if(num_ind < 2 || num_connect < 0) {            // checks arguments
        printf("Invalid arguments\n");
        return 1;
    }

    Graph TugaNet(num_ind);
    
    for (int i = 0; i < num_connect; i++){          // adds the edges to the graph
        int u, v;
        scanf("%d %d", &u, &v);
        TugaNet.addConnection(u, v);
    }
    
    //int max_jump = calculateMaxJump(TugaNet);
    //printf("%d\n", max_jump);

    // PRINT PARA VERIFICAR SE A 1ªDFS ESTÁ CERTA
    list<int> result = TugaNet.DFS(1);
    for (const int& element : result) {
        printf("%d\n",element);
    }

    return 0;
}
