#pragma once
// utils.h
#include <iostream>
#include <iomanip>
#include <algorithm>

std::string trim(const std::string &str, char target = ' ');

namespace utils
{
    std::string get_valid_string_from_user(const std::string &UI) noexcept;

    void menu() noexcept;

    void user_menu() noexcept;

    size_t get_valid_number_from_user() noexcept;

}