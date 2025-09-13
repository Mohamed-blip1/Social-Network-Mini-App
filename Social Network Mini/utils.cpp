// utils.cpp
#include "utils.h"

std::string trim(const std::string &str, char target)
{
    size_t start = str.find_first_not_of(target);
    size_t end = str.find_last_not_of(target);

    if (start == std::string::npos)
        return "";

    return str.substr(start, end - start + 1);
}

std::string utils::get_valid_string_from_user(const std::string &UI) noexcept
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

void utils::menu() noexcept
{
    constexpr size_t space = 2;
    std::cout << "\n===== Social Network Menu =====\n";
    std::cout << std::setw(space) << std::left << "1" << "- Login\n";
    std::cout << std::setw(space) << std::left << "2" << "- Sign-up\n";
    std::cout << std::setw(space) << std::left << "3" << "- Menu\n";
    std::cout << std::setw(space) << std::left << "0" << "- Exit\n";
}

void utils::user_menu() noexcept
{

    constexpr size_t space = 3;

    std::cout << "\n---- User Menu ----\n";
    std::cout << std::setw(space) << std::left << "1" << "- Add friend\n";
    std::cout << std::setw(space) << std::left << "2" << "- Recent messages\n";
    std::cout << std::setw(space) << std::left << "3" << "- Send message\n";
    std::cout << std::setw(space) << std::left << "4" << "- Notifications\n";
    std::cout << std::setw(space) << std::left << "5" << "- Show friends\n";
    std::cout << std::setw(space) << std::left << "6" << "- Friends-of-friends suggestions\n";
    std::cout << std::setw(space) << std::left << "7" << "- Friends suggestions\n";
    std::cout << std::setw(space) << std::left << "8" << "- recent actions\n";
    std::cout << std::setw(space) << std::left << "9" << "- Clear Messages\n";
    std::cout << std::setw(space) << std::left << "10" << "- Clear Notifications\n";
    std::cout << std::setw(space) << std::left << "11" << "- Remove friend\n";
    std::cout << std::setw(space) << std::left << "12" << "- Menu\n";
    std::cout << std::setw(space) << std::left << "0" << "- Logout\n";
}

size_t utils::get_valid_number_from_user() noexcept
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