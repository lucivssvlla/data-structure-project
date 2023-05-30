# ifndef MAP_H
# define MAP_H
# include <iostream>
# include<vector>
# include <limits>
# include <queue>
# include <climits>
class Vertex{
     private:
        int id;
        std::string information;
    public:
        Vertex(int vertexId, const std::string& vertexInfo):id(vertexId), information(vertexInfo){}
        int getId();
        std::string getInfomation();
};

class Graph{
    private:
        int numVertices;
        std::vector<Vertex> vertices;
        std::vector<std::vector<int>> adjacencyMatrix;
        std::vector<std::vector<int>> distanceMatrix;
    public:
        Graph(int vertices);
        void addEdge(int src, int dest, int weight);
        void addVertex(Vertex& vertex);
        std::string getVertexInfo(int id);
        void dijkstraAlgorithm(int startVertex, int endVertex);
        int getVertexId(std::string input);
};

Graph setSchoolMap();

#endif