// structureTesting.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <thread>
#include <iostream>
#include "deque.h"
#include "stack.h"

std::string text = "";

void insert(deque<int> & q) {
    for (int i = 65; i < 70; i++) {
        q.pushBack(i);
        std::cout << "d";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void erase(deque<int>& q) {
    for(int i = 0 ; i < 10;i++) {
        std::cout << q.popBack_wait();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}


void insertS(stack<int>& q) {
    for (int i = 65; i < 70; i++) {
        q.push(i);
        std::cout << "d";
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void eraseS(stack<int>& q) {
    for (int i = 0; i < 10; i++) {
        try {

            std::cout << "size: " << q.size();
            if (auto v = q.pop())
                std::cout << *v;
        }
        catch (...) {
            std::cout << "------------------err\n";
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}


int main()
{
        /*deque<int> dq;
        std::thread th{ insert, std::ref(dq) };
        std::thread th1{ erase, std::ref(dq) };
        th.join();
        th1.join();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << dq.findIndex(66);*/

    /*stack<int> s;
    std::thread th{ insertS, std::ref(s) };
    std::thread th1{ eraseS, std::ref(s) };
    th.join();
    th1.join();*/


}
