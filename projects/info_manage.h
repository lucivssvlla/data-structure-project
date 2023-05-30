# ifndef INFO_MANAGE_H
# define INFO_MANAGE_H
# include<iostream>
# include<fstream>
# include<vector>
# include<string>
# include<sstream>
# include <algorithm>

struct infor
{
    long long team_number;
    std::string project_name;
    std::string uni_name;
    std::string match_name;
    std::string contestant_name;
    std::string teacher_name;
};
struct TreeNode;
void select_sort(std::vector<infor>& searched_teams);
TreeNode* insert_node(TreeNode* root, const infor& info);
TreeNode* build_binary_tree(const std::vector<infor>& teamData);
TreeNode* search_node(TreeNode* root, long long targetTeamNumber);
std::vector<infor> read_data();
void remove_data(std::vector<infor>& teamData, long long targetNumber);
void append_data(std::vector<infor>& teamData, infor appendTeam);
void revise_data(std::vector<infor>& teamData, long long reviseTeamNumber, std::string modifyItem, std::string reviseInfo);
void print_data(infor teamData);
infor search_by_team_number(std::vector<infor> teamData, long long team_number, bool isASL = false);
std::vector<infor> search_by_uni_name(std::vector<infor> teamData, std::string uni_name);
std::vector<long long> get_team_numbers();

# endif
