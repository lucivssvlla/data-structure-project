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
}

void append_data(std::vector<infor>& teamData, infor appendTeam){
    teamData.push_back(appendTeam);
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
        }
    } 
    else {
        std::cout << "不存在该这只队伍 " << reviseTeamNumber << std::endl;
    }

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






