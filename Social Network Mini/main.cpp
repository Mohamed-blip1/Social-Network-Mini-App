#include <iostream>
#include "Social_Network.h"
#include "utils.h"

int main()
{
    Network network;

    size_t choice;

    do
    {
        utils::menu();
        choice = utils::get_valid_number_from_user();
        switch (choice)
        {
        case 0:
            // exit:
            std::cout << "Goodbye!";
            break;
        case 1:
            // Login:
            {
                std::string user_name = utils::get_name("Enter Your Name: ");

                if (!network.Login(user_name))
                {
                    std::cout << "No account found. Please sign up to create a new account.\n";
                    break;
                }
                // inter user space.
                std::cout << "Welcome back " << user_name << "!\n";
                do
                {
                    utils::user_menu();
                    choice = utils::get_valid_number_from_user();
                    switch (choice)
                    {
                    case 0:
                        // logout
                        std::cout << "Goodbye!\n";
                        break;
                        // add friend
                    case 1:
                    {
                        std::string other = utils::get_name("Enter a Name: ");

                        try
                        {
                            network.add_friendship(user_name, other);
                            std::cout << "You and '" << other << "' are friends now.\n";
                        }
                        catch (const std::exception &e)
                        {
                            std::cout << "Error: " << e.what() << "\n";
                        }
                    }
                    break;
                    case 2:
                        if (!network.Friends_suggestions(user_name))
                            std::cout << "There are no friend suggestions.\n";
                        break;
                    }

                } while (choice);
                choice++;
                break;
            }
        case 2:
            // Sign-up:
            {
                std::string name = utils::get_name("Enter Your Name: ");

                if (!network.sign_up(name))
                    std::cout << "The account already exists. Please log in.\n";
                else
                    // inter user space.
                    std::cout << "Welcome '" << name << "'. Please log in to access your account.\n";

                break;
            }
        }
    } while (choice);

    return 0;
}