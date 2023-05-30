#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <climits>

class Vertex{
    private:
        int id;
        std::string information;
    public:
        Vertex(int vertexId, const std::string& vertexInfo):id(vertexId), information(vertexInfo){}
        int getId(){
            return id;
        }
        std::string getInfomation(){
            return information;
        }

};

class Graph{
    private:
    int numVertices;
    std::vector<Vertex> vertices;
    std::vector<std::vector<int>> adjacencyMatrix;
    std::vector<std::vector<int>> distanceMatrix;
    public:
        Graph(int vertices): numVertices(vertices){
            adjacencyMatrix.resize(numVertices, std::vector<int>(numVertices, 0));
            distanceMatrix.resize(numVertices, std::vector<int>(numVertices, std::numeric_limits<int>::max()));
        };

        void addEdge(int src,int dest, int weight){
            adjacencyMatrix[src][dest] = 1;
            adjacencyMatrix[dest][src] = 1;
            distanceMatrix[src][dest] = weight;
            distanceMatrix[dest][src] = weight;
        }

        void addVertex(Vertex& vertex){
            vertices.push_back(vertex);
        }

        std::string getVertexInfo(int id);

        int getVertexId(std::string input);

        void dijkstraAlgorithm(int startVertex, int endVertex);
        
};

std::string Graph::getVertexInfo(int id){
            return vertices[id].getInfomation();
        }

int Graph::getVertexId(std::string input){
            bool found = false;
            for (Vertex& vertex : vertices) {
                if (vertex.getInfomation() == input) {
                    return vertex.getId();
                }
            }
            return 0;
        }
void Graph::dijkstraAlgorithm(int startVertex, int endVertex){
            std::vector<int> distance(numVertices, std::numeric_limits<int>::max());
            std::vector<bool> visited(numVertices, false);
            std::vector<int> previous(numVertices, -1); // 用于记录每个顶点的前驱顶点

            distance[startVertex] = 0;
            std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
            pq.push(std::make_pair(0, startVertex));

            while (!pq.empty()) {
                int u = pq.top().second;
                pq.pop();
                visited[u] = true;

                for (int v = 0; v < numVertices; ++v) {
                    if (adjacencyMatrix[u][v] && !visited[v] && distance[u] + distanceMatrix[u][v] < distance[v]) {
                        distance[v] = distance[u] + distanceMatrix[u][v];
                        previous[v] = u; // 记录顶点v的前驱顶点为u
                        pq.push(std::make_pair(distance[v], v));
                    }
                }
            }   

            std::string startPlace = vertices[startVertex].getInfomation();
            std::string endPlace = vertices[endVertex].getInfomation();
        
        // 输出最短路径
            std::cout << "从" << startPlace << "到" << endPlace << "的最短路径长度为:" << distance[endVertex] << std::endl;

        // 输出经过的点
            std::cout << "途径:";
            int currentVertex = endVertex;
            std::vector<int> path;
            while (currentVertex != -1) {
                path.push_back(currentVertex);
                currentVertex = previous[currentVertex];
            }
            for (int i = path.size() - 1; i >= 0; --i) {
                std::cout << vertices[path[i]].getInfomation();
                if (i != 0) {
                    std::cout << " -> ";
                }
            }
            std::cout << std::endl;
        }
Graph setSchoolMap(){
    Graph schoolMap(10);
    Vertex v0(0, "3号组团");
    Vertex v1(1, "西食堂");
    Vertex v2(2, "明德园");
    Vertex v3(3, "文体中心");
    Vertex v4(4, "西操场");
    Vertex v5(5, "文理大楼");
    Vertex v6(6, "行政大楼");
    Vertex v7(7, "求索园");
    Vertex v8(8, "东苑食堂");
    Vertex v9(9, "图书馆");
    
    schoolMap.addVertex(v0);
    schoolMap.addVertex(v1);
    schoolMap.addVertex(v2);
    schoolMap.addVertex(v3);
    schoolMap.addVertex(v4);
    schoolMap.addVertex(v5);
    schoolMap.addVertex(v6);
    schoolMap.addVertex(v7);
    schoolMap.addVertex(v8);
    schoolMap.addVertex(v9);

    schoolMap.addEdge(0,1,100);
    schoolMap.addEdge(0,3,200);
    schoolMap.addEdge(1,2,80);
    schoolMap.addEdge(1,3,150);
    schoolMap.addEdge(2,4,120);
    schoolMap.addEdge(2,5,110);
    schoolMap.addEdge(3,4,50);
    schoolMap.addEdge(4,7,150);
    schoolMap.addEdge(4,8,230);
    schoolMap.addEdge(5,6,80);
    schoolMap.addEdge(5,7,60);
    schoolMap.addEdge(6,9,100);
    schoolMap.addEdge(7,8,90);
    schoolMap.addEdge(7,9,70);
    schoolMap.addEdge(8,9,50);
    return schoolMap;
}

