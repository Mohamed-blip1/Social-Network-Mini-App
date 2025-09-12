// main.cpp
#include "user_menu.h"

int main()
{
    Network network;

    size_t choice;
    std::string user_name;
    std::string password;
    do
    {
        utils::menu();
        choice = utils::get_valid_number_from_user();
        std::cout << "\n";
        switch (choice)
        {
        case 0:
            // exit:
            std::cout << "Goodbye!";
            break;

        case 1:
        {
            // Login:
            user_name = utils::get_valid_string_from_user("Enter Your Name: ");
            password = utils::get_valid_string_from_user("Enter Your Password: ");
            try
            {
                user_menu(network, user_name, password);
            }
            catch (const std::exception &e)
            {
                std::cout << "Error: " << e.what() << "\n";
            }
            break;
        }
        case 2:
            // Sign-up:
            user_name = utils::get_valid_string_from_user("Enter Your Name: ");
            password = utils::get_valid_string_from_user("Enter Your Password: ");

            if (!network.sign_up(user_name, password))
                std::cout << "Username already exists!\n";
            else
                // Enter user space.
                std::cout << "Welcome '" << user_name << "'. Please log in to access your account.\n";

            break;

        default:
            std::cout << "'" << choice << "' Is not a choice!\n";
        }
    } while (choice);

    return 0;
}
