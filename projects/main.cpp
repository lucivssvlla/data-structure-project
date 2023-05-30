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
        std::cout<<"1.���¹���ϵͳ"<<std::endl;
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
                }
                else if(manageSymbol == 2){
                    std::string input;
                    std::cout<<"������Ҫ��ӵĶ�����Ϣ(���ո�ֿ�)";
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
                            std::cout << "������: " << newTeam.team_number << std::endl;
                            std::cout << "��Ŀ����: " << newTeam.project_name << std::endl;
                            std::cout << "��ѧ����: " << newTeam.uni_name << std::endl;
                            std::cout << "��������: " << newTeam.match_name << std::endl;
                            std::cout << "����������: " << newTeam.contestant_name << std::endl;
                            std::cout << "ָ����ʦ����: " << newTeam.teacher_name << std::endl;
                        }
                        append_data(data, newTeam);
                }
                else if(manageSymbol == 3){
                    std::string modifyItem;
                    std::string reviseInfo;
                    long long reviseTeamNumber;

                    std::cout<<"�������޸Ķ�����";
                    std::cin>>reviseTeamNumber;
                    std::cout<<std::endl;

                    std::cout<<"�������޸��";
                    std::cin>>modifyItem;
                    std::cout<<std::endl;

                    std::cout<<"�������޸���Ϣ��";
                    std::cin>>reviseInfo;
                    std::cout<<std::endl;

                    infor reviseTeam =  search_by_team_number(data, reviseTeamNumber);
                    std::cout<<"�޸�ǰ������Ϣ��";
                    print_data(reviseTeam);
                    revise_data(data, reviseTeamNumber, modifyItem, reviseInfo);
                    

                    std::cout<<"�޸ĺ������Ϣ: ";
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
                    std::cout<<"����������ţ�";
                    std::cin>>teamNumber;
                    std::cout<<std::endl;
                    infor searchedTeam = search_by_team_number(data,teamNumber,true);
                    print_data(searchedTeam);
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
            calling();

        }
        else if(symbol == 3){
            Graph schoolMap = setSchoolMap();
            int mapSymbol = 0;
            std::cout<<"1.��ѯĿ��ص���Ϣ��"<<std::endl;
            std::cout<<"2.��ѯ���·��:"<<std::endl;
            std::cin>>mapSymbol;
            if (mapSymbol == 1){
                int vertexNum = 0;
                std::cout<<"������ڵ���ţ�";
                std::cin>>vertexNum;
                std::string name = schoolMap.getVertexInfo(vertexNum);
                std::cout<<name<<std::endl;;
            }
            else if (mapSymbol == 2){
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
