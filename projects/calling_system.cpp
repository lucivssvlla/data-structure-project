#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <random>
#include <thread>
#include "info_manage.h"

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

void calling(){
    std::vector<std::queue<long long>> final_rooms = set_rooms();
    distributeElements(get_team_numbers());
    std::cout<<"请输入查看的房间号：";
    int select_number;
    std::cin>>select_number;
    std::queue<long long> selected_room = final_rooms[select_number];


    int minTime = 1000; 
    int maxTime = 2000;

    for(int i = 0; i < 5; i ++){
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
        std::cout<<"队伍比赛结束,下一队入场。"<<std::endl;
        selected_room.pop();
    }
    std::cout<<"当前该房间比赛如上所示"<<std::endl;

}

    
