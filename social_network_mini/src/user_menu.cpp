// user_menu.cpp
#include "user_menu.hpp"

void user_menu(Network &network, const std::string &user_name, const std::string &password)
{
    network.Login(user_name, password);

    // user space.
    std::cout << "Welcome back " << user_name << "!\n";
    size_t choice = std::numeric_limits<size_t>::max();
    utils::user_menu();
    while (choice != 0)
    {
        choice = utils::get_valid_number_from_user();
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
        {
            std::string other = utils::get_valid_string_from_user("Enter a friend Name: ");
            if (!network.check_if_user_exist_and_friend(user_name, other))
                std::cout << "No account found!\n";
            else
            {
                if (!network.show_messages(user_name, other))
                    std::cout << "No messages received yet!\n";
            }
        }
        break;

        case 3:
        {
            std::string other = utils::get_valid_string_from_user("Enter a Name: ");

            if (!network.check_if_user_exist_and_friend(user_name, other))
            {
                std::cout << "No account found!\n";
                break;
            }

            else
            {
                std::string message;
                std::cout << "Enter your messages and type [exit] to end:\n";
                message =
                    utils::get_valid_string_from_user(
                        "-");
                while (message != "exit")
                {
                    network.send_message(user_name, other, message);
                    std::cout << "Message sent.\n";
                    message =
                        utils::get_valid_string_from_user(
                            "-");
                }
            }
        }
        break;

        case 4:
            std::cout << "Notifications:\n";
            if (!network.notifications(user_name))
                std::cout << "Empty notifications!\n";
            break;

        case 5:
            std::cout << "Friends:\n";
            if (!network.show_friends(user_name))
                std::cout << "No friends yet!\n";
            break;
        case 6:
            std::cout << "Friends of Friends:\n";
            if (!network.bfs(user_name))
                std::cout << "No friends-of-friends yet!\n";
            break;
        case 7:
            std::cout << "Friends suggestions:\n";
            if (!network.Friends_suggestions(user_name))
                std::cout << "There are no friend suggestions!\n";
            break;

        case 8:
            std::cout << "Recent actions:\n";
            if (!network.recent_actions(user_name))
                std::cout << "No recent actions!\n";
            break;

        case 9:
        {
            std::string other = utils::get_valid_string_from_user("Enter a name: ");
            if (!network.check_if_user_exist_and_friend(user_name, other))
                std::cout << "No account found!\n";
            else
            {
                network.clear_messages(user_name, other);
                std::cout << "Messages have been cleared!\n";
            }
        }
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
        case 12:
            utils::user_menu();
            break;

        default:
            std::cout << "'" << choice << "' Is not a choice!\n";
        }
    }
}