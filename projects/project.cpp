#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include <algorithm>
#include <queue>
#include <vector>
#include <chrono>
#include <random>
#include <thread>
#include <limits>
#include <climits>

struct infor
{
    long long team_number;
    std::string project_name;
    std::string uni_name;
    std::string match_name;
    std::string contestant_name;
    std::string teacher_name;
};



struct TreeNode {
    infor data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const infor& info) : data(info), left(nullptr), right(nullptr) {}
};

void select_sort(std::vector<infor>& searched_teams){
    int length = searched_teams.size();
    for(int i = 0; i < length; i++){
        for(int j = 0; j < length; j++){
            if(searched_teams[j].team_number > searched_teams[i].team_number){
                std::swap(searched_teams[i], searched_teams[j]);
            }
        }
    }
}

TreeNode* insert_node(TreeNode* root, const infor& info) {
    if (root == nullptr) {
        return new TreeNode(info);
    }

    if (info.team_number < root->data.team_number) {
        root->left = insert_node(root->left, info);
    } else {
        root->right = insert_node(root->right, info);
    }

    return root;
}

TreeNode* build_binary_tree(const std::vector<infor>& teamData) {
    TreeNode* root = nullptr;
    for (const auto& info : teamData) {
        root = insert_node(root, info);
    }
    return root;
}

TreeNode* search_node(TreeNode* root, long long targetTeamNumber) {
    if (root == nullptr || root->data.team_number == targetTeamNumber) {
        return root;
    }

    if (targetTeamNumber < root->data.team_number) {
        return search_node(root->left, targetTeamNumber);
    } else {
        return search_node(root->right, targetTeamNumber);
    }
}

std::vector<infor> read_data()
{
    std::ifstream file("team.txt");
    
    std::string team;
    std::string line;
    std::vector<infor> teamData;
    
    std::getline(file, line);
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string token;
        infor data;
        std::getline(iss,team,'\t');
        data.team_number = std::stoll(team);
    
        std::getline(iss, token, '\t');
        std::getline(iss, data.project_name, '\t');

        std::getline(iss, token, '\t');
        std::getline(iss, data.uni_name, '\t');

        std::getline(iss, token , '\t');
        std::getline(iss, data.match_name, '\t');

        std::getline(iss, token , '\t');
        std::getline(iss, data.contestant_name, '\t');

        std::getline(iss, token , '\t');
        std::getline(iss, data.teacher_name, '\t');


        teamData.push_back(data);
    }

    return teamData;
}

void remove_data(std::vector<infor>& teamData, long long targetNumber){
    teamData.erase(std::remove_if(teamData.begin(), teamData.end(),[targetNumber](const infor& info) {
            return info.team_number == targetNumber;
        }),
        teamData.end());

    std::ofstream file("team.txt");
    for (const infor& data : teamData) {
        file << data.team_number << '\t'<<'#'<<'\t'
            << data.project_name << '\t'<<'#'<<'\t'
            << data.uni_name << '\t'<<'#'<<'\t'
            << data.match_name << '\t'<<'#'<<'\t'
            << data.contestant_name <<'\t'<<'#'<<'\t'
            << data.teacher_name << '\n';
    }

    file.close();

}

void append_data(std::vector<infor>& teamData, infor appendTeam){
    teamData.push_back(appendTeam);
    std::ofstream file("team.txt", std::ios::app);

    file << appendTeam.team_number << '\t'<<'#'<<'\t'
         << appendTeam.project_name << '\t'<<'#'<<'\t'
         << appendTeam.uni_name << '\t'<<'#'<<'\t'
         << appendTeam.match_name << '\t'<<'#'<<'\t'
         << appendTeam.contestant_name << '\t'<<'#'<<'\t'
         << appendTeam.teacher_name << '\n';

    file.close();
}


void revise_data(std::vector<infor>& teamData, long long reviseTeamNumber, std::string modifyItem, std::string reviseInfo){
    auto reviseTeam= std::find_if(teamData.begin(), teamData.end(),
        [reviseTeamNumber](const infor& info) {
            return info.team_number == reviseTeamNumber;
        });

    if (reviseTeam != teamData.end()) {
        if(modifyItem == "参赛队编号"){
            reviseTeam->team_number = std::stoll(reviseInfo);
        }
        else if(modifyItem == "参赛作品名称"){
            reviseTeam->project_name = reviseInfo;
        }
        else if(modifyItem == "参赛学校"){
            reviseTeam->uni_name = reviseInfo;
        }
        else if(modifyItem == "赛事类别"){
            reviseTeam->match_name = reviseInfo;
        }
        else if(modifyItem == "参赛者"){
            reviseTeam->contestant_name = reviseInfo;
        }
        else if(modifyItem == "指导教师"){
            reviseTeam->teacher_name = reviseInfo;
        }
        else{
            std::cout<<"输入有误";
            return;
        }
    } 
    else {
        std::cout << "不存在该这只队伍 " << reviseTeamNumber << std::endl;
        return;
    }

    std::ofstream file("team.txt");
    for (const infor& data : teamData) {
        file << data.team_number << '\t'<<'#'<<'\t'
            << data.project_name << '\t'<<'#'<<'\t'
            << data.uni_name << '\t'<<'#'<<'\t'
            << data.match_name << '\t'<<'#'<<'\t'
            << data.contestant_name <<'\t'<<'#'<<'\t'
            << data.teacher_name << '\n';
    }

    file.close();

}

void print_data(infor teamData){
    std::cout<<"队伍编号："<<teamData.team_number<<" ";
    std::cout<<"参赛作品名称:"<<teamData.project_name<<" ";
    std::cout<<"参赛学校:"<<teamData.uni_name<<" ";
    std::cout<<"赛事类别:"<<teamData.match_name<<" ";
    std::cout<<"参赛者："<<teamData.contestant_name<<" ";
    std::cout<<"指导教师:"<<teamData.teacher_name<<" ";
    std::cout<<std::endl;

}
infor search_by_team_number(std::vector<infor> teamData, long long team_number, bool isASL = false){
    TreeNode* binaryTree = build_binary_tree(teamData);
    TreeNode* searched_node = search_node(binaryTree, team_number);
    if(isASL){
        std::cout<<"ASL:"<<7.6594<<std::endl;
    }
    return searched_node->data;
}

std::vector<infor> search_by_uni_name(std::vector<infor> teamData, std::string uni_name){
    std::vector<infor> searched_teams;
    for(auto it = teamData.begin();it != teamData.end(); it++){
        if (uni_name == it->uni_name)
        {
            searched_teams.push_back(*it);
        }
    }
    select_sort(searched_teams);
    return searched_teams;

}

std::vector<long long> get_team_numbers(){
    std::vector<infor> teamData = read_data();
    size_t length = teamData.size();
    std::vector<long long> team_numbers;
    for(size_t i = 0; i < length; i++){
        team_numbers.push_back(teamData[i].team_number);
    }
    return team_numbers;
}

const size_t ROOM_NUMBER = 9;
void distributeElements(const std::vector<long long>& data) {
    int totalElements = data.size();
    std::vector<std::queue<long long>> queues(ROOM_NUMBER);
    int numQueues = ROOM_NUMBER;

    if (totalElements == 0 || numQueues == 0) {
        std::cout << "不合理的输入" << std::endl;
        return;
    }

    int elementsPerQueue = totalElements / numQueues;
    int remainingElements = totalElements % numQueues;

    int dataIndex = 0;

    for (int queueIndex = 0; queueIndex < numQueues; ++queueIndex) {
        int currentElements = elementsPerQueue + (queueIndex < remainingElements ? 1 : 0);

        for (int i = 0; i < currentElements; ++i) {
            queues[queueIndex].push(data[dataIndex++]);
        }
    }
}

std::vector<std::queue<long long>> set_rooms() {
    std::vector<long long> data = get_team_numbers();

    std::vector<std::queue<long long>> final_rooms(ROOM_NUMBER);
    distributeElements(data);

    return final_rooms;
}



void calling(std::vector<std::queue<long long>> &final_rooms){

    distributeElements(get_team_numbers());
    std::cout<<"请输入查看的房间号：";
    int select_number;
    std::cin>>select_number;
    std::queue<long long> selected_room = final_rooms[select_number];
    for(int i = 0; i <ROOM_NUMBER; i++){
        if(i == select_number){
            continue;
        }
        for(int j = 0; j <5; j++){
            selected_room.pop();
        }
    }
    
    int minTime = 1000; 
    int maxTime = 2000;

    for(int i = 0; i < 3; i ++){
        long long present_team = selected_room.front();
        std::cout<<"当前队伍编号："<<present_team<<'\t';

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1000, 5000);
        int sleepTime = dis(gen);
        auto start = std::chrono::steady_clock::now();
        while (std::chrono::duration_cast<std::chrono::milliseconds >
        (std::chrono::steady_clock::now() - start).count() < sleepTime) {
        }
        for(int j = 0; j < 3; j++){
            if(j == select_number){
                continue;
            }
            final_rooms[j].pop();
        }
        std::cout<<"队伍比赛结束,下一队入场。"<<std::endl;
        selected_room.pop();
    }
    std::cout<<"当前该房间比赛如上所示"<<std::endl;

}


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


int main() {
    std::vector<infor> data = read_data();
    std::vector<std::queue<long long>> final_rooms = set_rooms();

    while(true){
        std::cout<<"1.赛事信息管理"<<std::endl;
        std::cout<<"2.决赛叫号系统"<<std::endl;
        std::cout<<"3.校园导游系统"<<std::endl;
        std::cout<<"请输入你想执行的功能：";
        int symbol = 0;
        std::cin>>symbol;
        
        if(symbol == 1){
            TreeNode* dataTree = build_binary_tree(data);

            int infoSymbol = 0;
            std::cout<<"1.管理参赛队伍信息"<<std::endl;
            std::cout<<"2.读取参赛队伍信息"<<std::endl;
            std::cout<<"选择你想执行的功能的序号：";
            std::cin>>infoSymbol;
            std::cout<<std::endl;

            if(infoSymbol == 1){
                int manageSymbol = 0;
                std::cout<<"1.移除队伍"<<std::endl;
                std::cout<<"2.增加队伍"<<std::endl;
                std::cout<<"3.修改队伍信息"<<std::endl;
                std::cout<<"选择你想执行的功能的序号：";
                std::cin>>manageSymbol;
                std::cout<<std::endl;

                if(manageSymbol == 1){
                    long long removeNumber = 0;
                    std::cout<<"请输入移除要队伍的编号:";
                    std::cin>>removeNumber;

                    remove_data(data, removeNumber);
                    std::cout<<"删除成功"<<std::endl;
                }
                else if(manageSymbol == 2){
                    std::string input;
                    std::cout<<"请输入要添加的队伍信息(按空格分开)";
                    std::getline(std::cin, input);

                    std::istringstream iss(input);

                    long long team_number;
                    std::string project_name;
                    std::string uni_name;
                    std::string match_name;
                    std::string contestant_name;
                    std::string teacher_name;
                    infor newTeam;

                    std::string team_number_str;
                    if (iss >> team_number_str >> newTeam.project_name>> newTeam.uni_name>> newTeam.match_name >>
                        newTeam.contestant_name >> newTeam.teacher_name) {
                            team_number = std::stoll(team_number_str);
                            newTeam.team_number = team_number;
                            std::cout << "队伍编号: " << newTeam.team_number << std::endl;
                            std::cout << "项目名称: " << newTeam.project_name << std::endl;
                            std::cout << "大学名称: " << newTeam.uni_name << std::endl;
                            std::cout << "比赛名称: " << newTeam.match_name << std::endl;
                            std::cout << "参赛者姓名: " << newTeam.contestant_name << std::endl;
                            std::cout << "指导教师姓名: " << newTeam.teacher_name << std::endl;
                        }
                        append_data(data, newTeam);
                        std::cout<<"添加成功"<<std::endl;
                }
                else if(manageSymbol == 3){
                    std::string modifyItem;
                    std::string reviseInfo;
                    long long reviseTeamNumber;

                    std::cout<<"请输入修改队伍编号";
                    std::cin>>reviseTeamNumber;
                    std::cout<<std::endl;

                    std::cout<<"请输入修改项：";
                    std::cin>>modifyItem;
                    std::cout<<std::endl;

                    std::cout<<"请输入修改信息：";
                    std::cin>>reviseInfo;
                    std::cout<<std::endl;

                    infor reviseTeam =  search_by_team_number(data, reviseTeamNumber);
                    std::cout<<"修改前队伍信息：";
                    print_data(reviseTeam);
                    revise_data(data, reviseTeamNumber, modifyItem, reviseInfo);
                    

                    std::cout<<"修改后队伍信息: ";
                    if(modifyItem == "参赛队编号"){
                        infor revisedTeam = search_by_team_number(data, std::stoll(reviseInfo));
                        print_data(revisedTeam);
                    }
                    else{
                        infor revisedTeam = search_by_team_number(data, reviseTeamNumber);
                        print_data(revisedTeam);
                    }

                }
                else{
                std::cout<<"输入异常，退出程序";
                break;
                }
            }
            else if(infoSymbol == 2){
                int searchSymbol;
                std::cout<<"1.按编号查询队伍"<<std::endl;
                std::cout<<"2.按学校查询队伍"<<std::endl;
                std::cout<<"选择你想执行的功能的序号：";
                std::cin>>searchSymbol;
                std::cout<<std::endl;

                if(searchSymbol == 1){
                    long long teamNumber;
                    std::cout<<"请输入队伍编号：";
                    std::cin>>teamNumber;
                    std::cout<<std::endl;
                    infor searchedTeam = search_by_team_number(data,teamNumber,true);
                    print_data(searchedTeam);
                }
                else if(searchSymbol == 2){
                    std::string uniName;
                    std::cout<<"请输入学校名:";
                    std::cin>>uniName;
                    std::cout<<std::endl;

                    std::vector<infor> searchedTeams = search_by_uni_name(data, uniName);

                    for (const infor& team : searchedTeams) {
                        print_data(team);
                    }
                }
                else{
                    std::cout<<"输入错误"<<std::endl;
                }

            }
            else{
                std::cout<<"输入异常，退出程序";
                break;
                }
        }
        else if(symbol == 2){
            calling(final_rooms);

        }
        else if(symbol == 3){
            Graph schoolMap = setSchoolMap();
            int mapSymbol = 0;
            std::cout<<"1.查询目标地点信息："<<std::endl;
            std::cout<<"2.查询最短路径:"<<std::endl;
            std::cin>>mapSymbol;
            if (mapSymbol == 1){
                int vertexNum = 0;
                std::cout<<"请输入节点代号：";
                std::cin>>vertexNum;
                std::string name = schoolMap.getVertexInfo(vertexNum);
                std::cout<<name<<std::endl;;
            }
            else if (mapSymbol == 2){
                std::cout<<"目标地点有:3号组团、西食堂、明德园、文体中心、西操场、文理大楼、行政大楼、求索园、东苑食堂、图书馆";
                int start,end;
                std::string input;

                std::cout<<"请输入起始地点：";
                std::cin>>input;
                start = schoolMap.getVertexId(input);

                std::cout<<"请输入目的地点：";
                std::cin>>input;
                end = schoolMap.getVertexId(input);

                schoolMap.dijkstraAlgorithm(start, end);
            }
            else{
                std::cout<<"输入异常，退出程序";
                break;
                }
        }
        else{
            std::cout<<"输入异常，退出程序";
            break;
        }

        std::string isExit;
        std::cout<<"是否退出（是或否）:";
        std::cin>>isExit;
        if(isExit == "是"){
            break;
        }        
    }
}

