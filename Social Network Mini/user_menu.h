#pragma once
#include <iostream>
#include "Social_Network.h"
#include "utils.h"
#include <iomanip>

void user_menu(Network &network, const std::string &user_name, const std::string &password)
{
    network.Login(user_name, password);

    // user space.
    std::cout << "Welcome back " << user_name << "!\n";
    size_t choice;
    do
    {
        utils::user_menu();
        choice = utils::get_valid_number_from_user();
        std::cout << "\n";
        switch (choice)
        {
        case 0:
            // logout
            std::cout << "Goodbye!\n";
            break;

        case 1:
        {
            std::string other = utils::get_valid_string_from_user("Enter a Name: ");

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
            if (!network.show_messages(user_name))
                std::cout << "No messages received yet!\n";
            break;

        case 3:
        {
            std::string other = utils::get_valid_string_from_user("Enter a Name: ");

            if (!network.check_if_user_exist(other))
            {
                std::cout << "No account found!\n";
                break;
            }

            else
            {
                std::string message = utils::get_valid_string_from_user("Enter a message: ");

                network.send_message(user_name, other, message);
                std::cout << "Message sent.\n";
            }

            break;
        }

        case 4:
            if (!network.notifications(user_name))
                std::cout << "Empty notifications!\n";
            break;

        case 5:
            if (!network.show_friends(user_name))
                std::cout << "No friends yet!\n";
            break;
        case 6:
            if (!network.bfs(user_name))
                std::cout << "No friends-of-friends yet!\n";
            break;
        case 7:
            if (!network.Friends_suggestions(user_name))
                std::cout << "There are no friend suggestions!\n";
            break;

        case 8:
            if (!network.recent_actions(user_name))
                std::cout << "No recent actions!\n";
            break;

        case 9:
            network.clear_messages(user_name);
            std::cout << "Messages have been cleared!\n";
            break;

        case 10:
            network.clear_notifications(user_name);
            std::cout << "Notifications have been cleared!\n";
            break;

        case 11:
        {
            std::string other = utils::get_valid_string_from_user("Enter a Name: ");

            try
            {
                network.remove_friendship(user_name, other);
                std::cout << "You and '" + other + "' are no longer friends!\n";
            }
            catch (const std::exception &e)
            {
                std::cout << "Error: " << e.what() << "\n";
            }
        }
        break;

        default:
            std::cout << "'" << choice << "' Is not a choice!\n";
        }

    } while (choice);
    choice++;
}