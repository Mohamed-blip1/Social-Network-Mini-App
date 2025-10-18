// user_menu.cpp
#include "user_menu.hpp"

enum class UserMenu
{
    Logout,
    AddFriend,
    RecentMessages,
    SendMessage,
    Notifications,
    ShowFriends,
    FriendsOfSriendsSuggestions,
    FriendsSuggestions,
    RecentActions,
    ClearMessages,
    ClearNotifications,
    RemoveFriend,
    Menu,
};

void user_menu(Network &network, const std::string &user_name, const std::string &password)
{
    switch (network.login(user_name, password))
    {
    case Result::UserNotFound:
        std::cout << "User name not found!\n";
        return;
    case Result::IncorrectPassword:
        std::cout << "Incorrect password!\n";
        return;
    case Result::Success:
        std::cout << "Welcome back " << user_name << "!\n";
        break;
    default:
        break;
    }

    // user space.
    UserMenu choice;
    utils::user_menu();
    while (true)
    {
        choice = static_cast<UserMenu>(utils::get_valid_number_from_user());
        switch (choice)
        {
        case UserMenu::Logout:

            std::cout << "Goodbye!\n";
            break;

        case UserMenu::AddFriend:
        {
            std::string other = utils::get_valid_string_from_user("Enter a Name: ");

            switch (network.add_friendship(user_name, other))
            {
            case Result::Success:
                std::cout << "You and '" << other << "' are friends now.\n";
                break;
            case Result::UserNotFound:
                std::cout << "User not found!\n";
                break;
            case Result::AlreadyFriends:
                std::cout << "Friend already exist!\n";
                break;
            default:
                break;
            }
        }
        break;

        case UserMenu::RecentMessages:
        {
            std::string other = utils::get_valid_string_from_user("Enter a friend Name: ");
            if (!network.user_and_friend_exist(user_name, other))
            {
                std::cout << "No account found!\n";
                break;
            }

            if (!network.show_messages(user_name, other))
                std::cout << "No messages received yet!\n";
        }
        break;

        case UserMenu::SendMessage:
        {
            std::string other = utils::get_valid_string_from_user("Enter a Name: ");

            if (!network.user_and_friend_exist(user_name, other))
            {
                std::cout << "No account found!\n";
                break;
            }

            std::string message;
            std::cout << "Enter your messages and type [exit] to end:\n";

            while (true)
            {
                message =
                    utils::get_valid_string_from_user("-");

                if (message == "exit")
                    break;

                network.send_message(user_name, other, message);
                std::cout << "Message sent.\n";
            }
        }
        break;

        case UserMenu::Notifications:
            std::cout << "Notifications:\n";
            if (!network.notifications(user_name))
                std::cout << "Empty notifications!\n";
            break;

        case UserMenu::ShowFriends:
            std::cout << "Friends:\n";
            if (!network.show_friends(user_name))
                std::cout << "No friends yet!\n";
            break;
        case UserMenu::FriendsOfSriendsSuggestions:
            std::cout << "Friends of Friends:\n";
            if (!network.bfs(user_name))
                std::cout << "No friends-of-friends yet!\n";
            break;
        case UserMenu::FriendsSuggestions:
            std::cout << "Friends suggestions:\n";
            if (!network.Friends_suggestions(user_name))
                std::cout << "There are no friend suggestions!\n";
            break;

        case UserMenu::RecentActions:
            std::cout << "Recent actions:\n";
            if (!network.recent_actions(user_name))
                std::cout << "No recent actions!\n";
            break;

        case UserMenu::ClearMessages:
        {
            std::string other =
                utils::get_valid_string_from_user("Enter a name: ");

            if (!network.user_and_friend_exist(user_name, other))
            {
                std::cout << "No account found!\n";
                break;
            }

            network.clear_messages(user_name, other);
            std::cout << "Messages have been cleared!\n";
        }
        break;

        case UserMenu::ClearNotifications:
            network.clear_notifications(user_name);
            std::cout << "Notifications have been cleared!\n";
            break;

        case UserMenu::RemoveFriend:
        {
            std::string other = utils::get_valid_string_from_user("Enter a Name: ");

            switch (network.remove_friendship(user_name, other))
            {
            case Result::Success:
                std::cout << "You and '" + other + "' are no longer friends!\n";
                break;
            case Result::UserNotFound:
                std::cout << "No account found!\n";
                break;
            case Result::SameUser:
                std::cout << "Can't unfriend your self!\n";
                break;
            case Result::NotFriend:
                std::cout << "'" << other << "' is not a friend!\n";
                break;
            default:
                break;
            }
        }
        break;
        case UserMenu::Menu:
            utils::user_menu();
            break;

        default:
            std::cout << "'" << (size_t)choice << "' Is not a choice!\n";
            break;
        }
        if (choice == UserMenu::Logout)
            break;
    }
}