// main.cpp
#include "user_menu.hpp"

int main()
{
    Network network;

    size_t choice = std::numeric_limits<size_t>::max();
    std::string user_name;
    std::string password;
    utils::menu();
    while (choice != 0)
    {
        choice = utils::get_valid_number_from_user();
        switch (choice)
        {
        case 0:
            // exit:
            std::cout << "Goodbye!\n";
            break;

        case 1:
        {
            // Login:
            user_name = utils::get_valid_string_from_user("Enter Your Name: ");
            password = utils::get_valid_string_from_user("Enter Your Password: ");
            user_menu(network, user_name, password);
        }
        break;
        case 2:
            // Sign-up:
            user_name = utils::get_valid_string_from_user("Enter Your Name: ");
            password = utils::get_valid_string_from_user("Enter Your Password: ");

            if (!network.sign_up(user_name, std::move(password)))
                std::cout << "Username already exists!\n";
            else
                // Enter user space.
                std::cout << "Welcome '" << user_name << "'. Please log in to access your account.\n";

            break;
        case 3:
            utils::menu();
            break;

        default:
            std::cout << "'" << choice << "' Is not a choice!\n";
        }
    }

    return 0;
}
