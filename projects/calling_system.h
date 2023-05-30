#ifndef CALLING_SYSTEM_H
#define CALLING_SYSTEM_H
#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <random>
#include <thread>


void distributeElements(const std::vector<long long>& data);
std::vector<std::queue<long long>> set_rooms();
void calling();

#endif

