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
#include <cmath>

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
    if (root == nullptr) {
        std::cout << "����ʧ��" << std::endl;
        return nullptr;
    }

    if (root->data.team_number == targetTeamNumber) {
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
    file << "�����ӱ��" << '\t'<<'#'<<'\t'
         << "������Ʒ����" << '\t'<<'#'<<'\t'
         << "����ѧУ" << '\t'<<'#'<<'\t'
         << "�������" << '\t'<<'#'<<'\t'
         << "������" << '\t'<<'#'<<'\t'
         << "ָ����ʦ" << '\n';
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
    file << "�����ӱ��" << '\t'<<'#'<<'\t'
         << "������Ʒ����" << '\t'<<'#'<<'\t'
         << "����ѧУ" << '\t'<<'#'<<'\t'
         << "�������" << '\t'<<'#'<<'\t'
         << "������" << '\t'<<'#'<<'\t'
         << "ָ����ʦ" << '\n';

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
        if(modifyItem == "�����ӱ��"){
            reviseTeam->team_number = std::stoll(reviseInfo);
        }
        else if(modifyItem == "������Ʒ����"){
            reviseTeam->project_name = reviseInfo;
        }
        else if(modifyItem == "����ѧУ"){
            reviseTeam->uni_name = reviseInfo;
        }
        else if(modifyItem == "�������"){
            reviseTeam->match_name = reviseInfo;
        }
        else if(modifyItem == "������"){
            reviseTeam->contestant_name = reviseInfo;
        }
        else if(modifyItem == "ָ����ʦ"){
            reviseTeam->teacher_name = reviseInfo;
        }
        else{
            std::cout<<"��������";
            return;
        }
    } 
    else {
        std::cout << "�����ڸ���ֻ���� " << reviseTeamNumber << std::endl;
        return;
    }

    std::ofstream file("team.txt");
    file << "�����ӱ��" << '\t'<<'#'<<'\t'
         << "������Ʒ����" << '\t'<<'#'<<'\t'
         << "����ѧУ" << '\t'<<'#'<<'\t'
         << "�������" << '\t'<<'#'<<'\t'
         << "������" << '\t'<<'#'<<'\t'
         << "ָ����ʦ" << '\n';
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
    std::cout<<"�����ţ�"<<teamData.team_number<<std::endl;
    std::cout<<"������Ʒ����:"<<teamData.project_name<<std::endl;
    std::cout<<"����ѧУ:"<<teamData.uni_name<<std::endl;
    std::cout<<"�������:"<<teamData.match_name<<std::endl;
    std::cout<<"�����ߣ�"<<teamData.contestant_name<<std::endl;
    std::cout<<"ָ����ʦ:"<<teamData.teacher_name<<std::endl;

}

int countHeight(TreeNode* treeNode, int height) {
    if (treeNode != nullptr) {
        return (height + countHeight(treeNode->left, height + 1) + countHeight(treeNode->right, height + 1));
    }
    else {
        return 0;
    }
}   
double calculateASL(int n, TreeNode* binaryTree) {
    int startHeight = 1;
    double nodes = (countHeight(binaryTree, startHeight));
    double nodeNumber = n;
    double result = nodes / n;
    return result;
}
infor search_by_team_number(std::vector<infor> teamData, long long team_number, bool isASL = false){
    TreeNode* binaryTree = build_binary_tree(teamData);
    TreeNode* searched_node = search_node(binaryTree, team_number);

    if(isASL && searched_node != nullptr){
        double asl = calculateASL(teamData.size(), binaryTree);
        std::cout<<"ƽ�����ҳ���Ϊ��"<<asl<<std::endl;
        std::cout<<"ASL���㹫ʽΪ:�ܽ�����֮��/������(countHeight/nodeNumber)"<<std::endl;
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



const size_t ROOM_NUMBER = 9;

std::vector<std::string> getMatchName(std::vector<infor> data){
    std::vector<std::string> matchName;
    for (const infor& team : data) {
        if(!matchName.empty()){
            bool isRepeat = false;
            for(const std::string& name : matchName){
                if(name == team.match_name){
                    isRepeat = true;
                }
            }
            if(!isRepeat){
                matchName.push_back(team.match_name);
            }
        }
        else{
            matchName.push_back(team.match_name);
        }
    }
    return matchName;
}

std::vector<std::queue<long long>> set_rooms(std::vector<infor> teamData) {
    std::vector<std::string> matchName = getMatchName(teamData);
    std::vector<std::queue<long long>> final_rooms(ROOM_NUMBER);
    for (int i = 0; i < matchName.size(); i++) {
        std::vector<infor> matchTeams;
        for (const infor& team : teamData) {
            if (team.match_name == matchName[i]) {
                matchTeams.push_back(team);
            }
        }
        int roomNumber = i % ROOM_NUMBER;
        for (const infor& team : matchTeams) {
            final_rooms[roomNumber].push(team.team_number);
        }
    }
    return final_rooms;
}
void calling(std::vector<infor> teamData){
    std::vector<std::queue<long long>> rooms = set_rooms(teamData);
    std::cout<<"������鿴�ķ���ţ�";
    int select_number;
    std::cin>>select_number;
    std::queue<long long> selected_room = rooms[select_number];
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

    for(int i = 0; i < 5; i ++){
        long long present_team = selected_room.front();
        std::cout<<"��ǰ�����ţ�"<<present_team<<'\t';

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(500, 1000);
        int sleepTime = dis(gen);
        auto start = std::chrono::steady_clock::now();
        while (std::chrono::duration_cast<std::chrono::milliseconds >
        (std::chrono::steady_clock::now() - start).count() < sleepTime) {
        }
        for(int j = 0; j < 3; j++){
            if(j == select_number){
                continue;
            }
            rooms[j].pop();
        }
        std::cout<<"�����������,��һ���볡��"<<std::endl;
        selected_room.pop();
    }
    std::cout<<"��ǰ�÷������������ʾ"<<std::endl;

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
            std::vector<int> previous(numVertices, -1); // ���ڼ�¼ÿ�������ǰ������

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
                        previous[v] = u; // ��¼����v��ǰ������Ϊu
                        pq.push(std::make_pair(distance[v], v));
                    }
                }
            }   

            std::string startPlace = vertices[startVertex].getInfomation();
            std::string endPlace = vertices[endVertex].getInfomation();
        
        // ������·��
            std::cout << "��" << startPlace << "��" << endPlace << "�����·������Ϊ:" << distance[endVertex] << std::endl;

        // ��������ĵ�
            std::cout << ";��:";
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
void searchInfo(std::string target){
    if (target == "3������"){
        std::cout<<"����������λ��У԰���ϲ��ѧ������¥��";
    }
    else if (target == "��ʳ��"){
        std::cout<<"��ʳ��λ��ѧУ���࣬�����ٳ��Աߣ�Ϊʦ���ṩ���͡�";
    }
    else if (target == "����԰"){
        std::cout<<"����԰����ʳ�ö�������80m��,���ֳ��ԡ���ѧ����������ѧУ��ѧ��������������";
    }
    else if (target == "��������"){
        std::cout<<"��������λ�����ٳ��ϲ࣬�ڲ����кܶ��˶����ģ���ѧ���ʹ�á�";
    }
    else if (target == "���ٳ�"){
        std::cout<<"���ٳ�����ʳ�ö���120m��,����ѧ���ڴ�����";
    }
    else if (target == "�����¥"){
        std::cout<<"�����¥λ��У԰�����룬��ȫУ��ߵĽ�����";
    }
    else if (target == "������¥"){
        std::cout<<"������¥λ�ڱ��Ž������ֱߣ�ְ��������������������Ա������";
    }
    else if (target == "����԰"){
        std::cout<<"����԰λ��ͼ������࣬Ԣ����׷��֪ʶ���ǻۺʹ��µľ���";
    }
    else if (target == "��ʳ��"){
        std::cout<<"��ʳ��λ��ѧУ���࣬����ͼ��ݺͶ������ᡣ";
    }
    else if (target == "ͼ���"){
        std::cout<<"ͼ��ݹ������㣬��ѧ�������鼮��ͬʱ����Ϊѧ���ṩ��ϰ������";
    }
    else{
        std::cout<<"�������";
    }
    
}
Graph setSchoolMap(){
    Graph schoolMap(10);
    Vertex v0(0, "3������");
    Vertex v1(1, "��ʳ��");
    Vertex v2(2, "����԰");
    Vertex v3(3, "��������");
    Vertex v4(4, "���ٳ�");
    Vertex v5(5, "�����¥");
    Vertex v6(6, "������¥");
    Vertex v7(7, "����԰");
    Vertex v8(8, "��Էʳ��");
    Vertex v9(9, "ͼ���");
    
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

    while(true){
        std::cout<<"1.������Ϣ����"<<std::endl;
        std::cout<<"2.�����к�ϵͳ"<<std::endl;
        std::cout<<"3.У԰����ϵͳ"<<std::endl;
        std::cout<<"����������ִ�еĹ��ܣ�";
        int symbol = 0;
        std::cin>>symbol;
        
        if(symbol == 1){
            TreeNode* dataTree = build_binary_tree(data);

            int infoSymbol = 0;
            std::cout<<"1.�������������Ϣ"<<std::endl;
            std::cout<<"2.��ȡ����������Ϣ"<<std::endl;
            std::cout<<"ѡ������ִ�еĹ��ܵ���ţ�";
            std::cin>>infoSymbol;
            std::cout<<std::endl;

            if(infoSymbol == 1){
                int manageSymbol = 0;
                std::cout<<"1.�Ƴ�����"<<std::endl;
                std::cout<<"2.���Ӷ���"<<std::endl;
                std::cout<<"3.�޸Ķ�����Ϣ"<<std::endl;
                std::cout<<"ѡ������ִ�еĹ��ܵ���ţ�";
                std::cin>>manageSymbol;
                std::cout<<std::endl;

                if(manageSymbol == 1){
                    long long removeNumber = 0;
                    std::cout<<"�������Ƴ�Ҫ����ı��:";
                    std::cin>>removeNumber;

                    remove_data(data, removeNumber);
                    std::cout<<"ɾ���ɹ�"<<std::endl;
                }
                else if(manageSymbol == 2){
                    std::cout<<"������Ҫ��ӵĶ�����Ϣ(���ո�ֿ�)\n";
                    
                    infor newTeam;
                    long long team_number;
                    
                    std::string team_number_str;
                    std::getline(std::cin, team_number_str);
                    std::cout<<"����������ӱ��:";
                    std::getline(std::cin, team_number_str);
                    std::cout<<"��������Ŀ����:";
                    std::getline(std::cin, newTeam.project_name);
                    std::cout<<"�������ѧ����:";
                    std::getline(std::cin, newTeam.uni_name);
                    std::cout<<"�������������:";
                    std::getline(std::cin, newTeam.match_name);
                    std::cout<<"���������������:";
                    std::getline(std::cin, newTeam.contestant_name);
                    std::cout<<"������ָ����ʦ����:";
                    std::cin>>newTeam.teacher_name;
                    
                    newTeam.team_number = std::stoll(team_number_str);


                    team_number = std::stoll(team_number_str);
                    newTeam.team_number = team_number;
                    std::cout<<std::endl;
                    std::cout << "������: " << newTeam.team_number << std::endl;
                    std::cout << "��Ŀ����: " << newTeam.project_name << std::endl;
                    std::cout << "��ѧ����: " << newTeam.uni_name << std::endl;
                    std::cout << "��������: " << newTeam.match_name << std::endl;
                    std::cout << "����������: " << newTeam.contestant_name << std::endl;
                    std::cout << "ָ����ʦ����: " << newTeam.teacher_name << std::endl;

                    append_data(data, newTeam);
                    std::cout<<"��ӳɹ�"<<std::endl;
                }
                else if(manageSymbol == 3){
                    std::string modifyItem;
                    std::string reviseInfo;
                    long long reviseTeamNumber;

                    std::cout<<"�������޸Ķ�����:";
                    std::cin>>reviseTeamNumber;
                    std::cout<<std::endl;

                    std::cout<<"�������޸��";
                    std::cin>>modifyItem;
                    std::cout<<std::endl;

                    std::cout<<"�������޸���Ϣ��";
                    std::cin>>reviseInfo;
                    std::cout<<std::endl;

                    infor reviseTeam =  search_by_team_number(data, reviseTeamNumber);
                    std::cout<<"�޸�ǰ������Ϣ��\n";
                    print_data(reviseTeam);
                    revise_data(data, reviseTeamNumber, modifyItem, reviseInfo);
                    

                    std::cout<<"�޸ĺ������Ϣ: \n";
                    if(modifyItem == "�����ӱ��"){
                        infor revisedTeam = search_by_team_number(data, std::stoll(reviseInfo));
                        print_data(revisedTeam);
                    }
                    else{
                        infor revisedTeam = search_by_team_number(data, reviseTeamNumber);
                        print_data(revisedTeam);
                    }

                }
                else{
                std::cout<<"�����쳣���˳�����";
                break;
                }
            }
            else if(infoSymbol == 2){
                int searchSymbol;
                std::cout<<"1.����Ų�ѯ����"<<std::endl;
                std::cout<<"2.��ѧУ��ѯ����"<<std::endl;
                std::cout<<"ѡ������ִ�еĹ��ܵ���ţ�";
                std::cin>>searchSymbol;
                std::cout<<std::endl;

                if(searchSymbol == 1){
                    long long teamNumber;
                    std::cout<<"�������ѯ����";
                    std::cin>>teamNumber;
                    std::cout<<std::endl;
                    infor searchedTeam = search_by_team_number(data,teamNumber,true);
                    if(searchedTeam.team_number != 0){
                        print_data(searchedTeam);
                    }
                }
                else if(searchSymbol == 2){
                    std::string uniName;
                    std::cout<<"������ѧУ��:";
                    std::cin>>uniName;
                    std::cout<<std::endl;

                    std::vector<infor> searchedTeams = search_by_uni_name(data, uniName);

                    for (const infor& team : searchedTeams) {
                        print_data(team);
                    }
                }
                else{
                    std::cout<<"�������"<<std::endl;
                }

            }
            else{
                std::cout<<"�����쳣���˳�����";
                break;
                }
        }
        else if(symbol == 2){
            calling(data);

        }
        else if(symbol == 3){
            Graph schoolMap = setSchoolMap();
            int mapSymbol = 0;
            std::cout<<"1.��ѯĿ��ص���Ϣ��"<<std::endl;
            std::cout<<"2.��ѯ���·��:"<<std::endl;
            std::cin>>mapSymbol;
            if (mapSymbol == 1){
                std::string target;
                std::cout<<"��������������";
                std::cin>>target;
                searchInfo(target);
                std::cout<<std::endl;
            }
            else if (mapSymbol == 2){
                std::cout<<"Ŀ��ص���:3�����š���ʳ�á�����԰���������ġ����ٳ��������¥��������¥������԰����Էʳ�á�ͼ���\n";
                int start,end;
                std::string input;

                std::cout<<"��������ʼ�ص㣺";
                std::cin>>input;
                start = schoolMap.getVertexId(input);

                std::cout<<"������Ŀ�ĵص㣺";
                std::cin>>input;
                end = schoolMap.getVertexId(input);

                schoolMap.dijkstraAlgorithm(start, end);
            }
            else{
                std::cout<<"�����쳣���˳�����";
                break;
                }
        }
        else{
            std::cout<<"�����쳣���˳�����";
            break;
        }

        std::string isExit;
        std::cout<<"�Ƿ��˳����ǻ��:";
        std::cin>>isExit;
        if(isExit == "��"){
            break;
        }        
    }
}
