#include<iostream>
#include <string>
#include <chrono>
#include <thread>
#include"info_manage.h"
#include"calling_system.h"
#include"map.h"

int main() {
    std::vector<infor> data = read_data();

    while(true){
        std::cout<<"1.赛事管理系统"<<std::endl;
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
            calling();

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
