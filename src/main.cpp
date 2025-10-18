// main.cpp
#include "user_menu.hpp"

enum class MainMenu
{
    Exit,
    Login,
    SignUp,
    ShowMenu
};

int main()
{
    Network network;

    MainMenu choice;
    std::string user_name;
    std::string password;
    utils::menu();
    while (true)
    {
        choice = static_cast<MainMenu>(utils::get_valid_number_from_user());
        switch (choice)
        {
        case MainMenu::Exit:

            std::cout << "Goodbye!\n";
            break;

        case MainMenu::Login:
        {
            user_name = utils::get_valid_string_from_user("Enter Your Name: ");
            password = utils::get_valid_string_from_user("Enter Your Password: ");
            user_menu(network, user_name, password);
        }
        break;
        case MainMenu::SignUp:

            user_name = utils::get_valid_string_from_user("Enter Your Name: ");
            password = utils::get_valid_string_from_user("Enter Your Password: ");

            if (!network.sign_up(user_name, std::move(password)))
                std::cout << "Username already exists!\n";
            else
                // Enter user space.
                std::cout << "Welcome '" << user_name << "'. Please log in to access your account.\n";

            break;
        case MainMenu::ShowMenu:
            utils::menu();
            break;

        default:
            std::cout << "'" << (size_t)choice << "' Is not a choice!\n";
            break;
        }
        if (choice == MainMenu::Exit)
            break;
    }

    return 0;
}
