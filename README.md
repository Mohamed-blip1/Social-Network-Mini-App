🧑‍🤝‍🧑 Social Network Mini App

A console-based C++ application that simulates a simple social networking system.
It allows users to sign up, log in, post messages, and interact with each other in a basic terminal UI.

✨ Features

🔐 User sign-up and login system

🧾 Create user profiles

🗨️ Post messages / updates

🧑‍💼 View and interact with other users

💾 Simple data handling via memory (no database)

📁 Project Structure
Social-Network-Mini-App/
| Social_Network_Mini/
| ├── include/                # Header files
| │   ├── user.h              # User class definition
| │   ├── user_menu.h         # User interface logic
| │   ├── social_network.h    # Core network logic
| │   └── utils.h             # Utility functions
| │
| ├── src/                    # Implementation files
| │   ├── user.cpp
| │   ├── user_menu.cpp
| │   ├── social_network.cpp
| │   └── utils.cpp
| ├── main.cpp                # Program entry point
| └── Makefile                # Build configuration
├── .gitignore
└── README.md               # This file

⚙️ Build Instructions
🛠 Prerequisites

A C++17 compiler (g++, clang++, or MSVC)

Make
 (optional, for using the Makefile)

A terminal or shell (Linux, macOS, Windows with MSYS2)

🧪 Compile & Run
✅ Option 1: Using make
# Navigate to project folder
cd Social_Network_Mini

# Compile
make

# Run
./main.exe  # (or ./main on Linux/macOS)

⚙️ Option 2: Manual compilation
g++ -std=c++17 -Iinclude -Isrc src/*.cpp main.cpp -o main.exe
./main.exe

📌 Example Usage

Once running, you’ll see a menu like this:

===== Social Network Menu =====
1 - Login
2 - Sign-up
3 - Menu
0 - Exit
>


You can:

Create a user account

Log in to your account

After Login:

Post messages to your feed

Interact with other user data

💡 Notes

This is a simple educational project — no database or file storage yet.

All data is stored in memory for the session.

📜 License

MIT License — free to use, modify, and share.
