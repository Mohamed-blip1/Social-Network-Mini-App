# 🧑‍🤝‍🧑 Social Network Mini App

A console-based C++ application that simulates a simple social networking system.
It allows users to sign up, log in, post messages, and interact with each other in a basic terminal UI.

## ✨ Features

🔐 User sign-up and login system

🧾 Create user profiles

🗨️ Post messages / updates

🧑‍💼 View and interact with other users

💾 Simple data handling via memory (no database)

## 📁 Project Structure
```
cpp-Social-Network/
├── .gitignore
├── README.md                 # This file
├── include/              # Header files
│   ├── user.h            # User class
│   ├── user_menu.h       # User interface logic
│   ├── social_network.h  # Core logic
│   └── utils.h           # Utilities

├── src/                  # Source files
|   ├── main.cpp              # Program entry point
│   ├── user.cpp
│   ├── user_menu.cpp
│   ├── social_network.cpp
│   └── utils.cpp

└── Makefile              # Build configuration
```

# ⚙️ Build Instructions
## 🛠 Prerequisites

A C++17 compiler (g++, clang++, or MSVC)

Make
 (optional, for using the Makefile)

A terminal or shell (Linux, macOS, Windows with MSYS2)

# 🧪 Compile & Run
## ✅ Option 1: Using make
- Navigate to project folder
```
cd /home/your_path/cpp-Social-Network/social_network_mini
```
- Compile
```
make
```
# Run
```
./main      # Linux/macOS
./main.exe  # Windows
```
## ⚙️ Option 2: Manual compilation
```
g++ -std=c++17 -Iinclude -Isrc src/*.cpp -o main.exe
./main      # Linux/macOS
./main.exe  # Windows
```
# 📌 Example Usage

- Once running, you’ll see a menu like this:
```
===== Social Network Menu =====
1 - Login
2 - Sign-up
3 - Menu
0 - Exit
>
```
- After creating an account and logging in
```
---- User Menu ----
1  - Add friend
2  - Recent messages
3  - Send message
4  - Notifications
5  - Show friends
6  - Friends-of-friends suggestions
7  - Friends suggestions
8  - recent actions
9  - Clear Messages
10 - Clear Notifications
11 - Remove friend
12 - Menu
0  - Logout
> 
```

- You can:
```
- Create a user account

- Log in to your account
```
- After Login:
```
- Post messages to your feed

- Interact with other user data
```
## 💡 Notes

This is a simple educational project — no database or file storage yet.

All data is stored in memory for the session.

## 📜 License

MIT License — free to use, modify, and share.
