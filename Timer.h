//
// Created by Wheheohu on 4/5/23.
//
#include <iostream>
#include <chrono>
#ifndef RAYTRACING_TIMER_H
#define RAYTRACING_TIMER_H


class Timer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock > start_timepoint;
public:
    Timer();
    ~Timer();
    void Stop();
};


#endif //RAYTRACING_TIMER_H
