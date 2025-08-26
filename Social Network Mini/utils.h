#pragma once
#include <iostream>

std::string trim(const std::string &str, char target = ' ')
{
    size_t start = str.find_first_not_of(target);
    size_t end = str.find_last_not_of(target);

    if (start == std::string::npos)
        return "";

    return str.substr(start, end - start + 1);
}

namespace utils
{
    inline std::string get_name(const std::string &UI)
    {
        std::string name;
        do
        {
            std::cout << UI;
            std::getline(std::cin, name);
            name = trim(name);
            if (name.empty())
                std::cout << "Input cannot be empty. Please try again.\n";

        } while (name.empty());

        return name;
    }

    void menu()
    {
        std::cout << "\n===== Social Network Menu =====\n";
        std::cout << "1 - Login\n";
        std::cout << "2 - Sign-up\n";
        std::cout << "0 - Exit\n";
    }
    void user_menu()
    {
        std::cout << "\n---- User Menu ----\n";
        std::cout << "1 - Add friend\n";
        std::cout << "2 - Friends suggestions\n";
        std::cout << "0 - Logout\n";
    }

    size_t get_valid_number_from_user()
    {
        size_t number;
        while (true)
        {
            std::cout << "> ";
            std::cin >> number;
            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "\nPlease Enter A Valid Number: ";
            }
            else
            {
                std::cin.ignore(1000, '\n');
                return number;
            }
        }
    }

}