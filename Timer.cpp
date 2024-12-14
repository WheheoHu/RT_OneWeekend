//
// Created by Wheheohu on 4/5/23.
//

#include "Timer.h"

Timer::Timer() {
    start_timepoint=std::chrono::high_resolution_clock ::now();

}

Timer::~Timer() {
    Stop();

}

void Timer::Stop() {
    auto end_time_point = std::chrono::high_resolution_clock::now();
    auto start = std::chrono::time_point_cast<std::chrono::microseconds>(start_timepoint).time_since_epoch().count();
    auto end = std::chrono::time_point_cast<std::chrono::microseconds>(end_time_point).time_since_epoch().count();

    auto duration = end - start;
    double ms = duration * 0.001;
    std::cout << std::endl;
    std::cout << "time: " << ms << " ms" << std::endl;

}
