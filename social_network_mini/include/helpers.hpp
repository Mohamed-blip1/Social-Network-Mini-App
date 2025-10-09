#pragma once
// helpers.hpp
#include <iostream>
#include <chrono>

struct Time
{
    using system_clock = std::chrono::system_clock;
    system_clock::time_point tp;
    std::time_t tt;
    std::tm tm;

    Time()
    {
        tp = system_clock::now();
        tt = system_clock::to_time_t(tp);
        tm = *std::gmtime(&tt);
    }
    ~Time() = default;
};

struct MessagesInfo
{
    using time_point = std::chrono::system_clock::time_point;
    time_point time;
    std::string content;

    // MessagesInfo() = default;
    MessagesInfo(const time_point &tp, const std::string &st)
        : time(tp), content(st) {}
};
