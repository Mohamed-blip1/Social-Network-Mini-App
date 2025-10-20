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
├─ include/
│ ├─ helpers.hpp
│ ├─ user.hpp
│ ├─ social_network.hpp
│ ├─ user_menu.hpp
│ └─ utils.hpp
├─ src/
│ ├─ main.cpp
│ ├─ social_network.cpp
│ ├─ user.cpp
│ ├─ user_menu.cpp
│ └─ utils.cpp
├─ pch.hpp
├─ Makefile
├─ README.md
└─ .gitignore
```

# ⚙️ Build Instructions
## 🛠 Prerequisites

A C++20 compiler (g++, clang++, or MSVC)

Make
 (optional, for using the Makefile)

A terminal or shell (Linux, macOS, Windows with MSYS2)

# 🧪 Compile & Run
## ✅ Option 1: Using make
- Navigate to project folder
```
cd /home/your_path/cpp-Social-Network/
```
- Compile
```
make
make g  # For g++
make debug # For debuging
make run # To build and run
```
# Run
```
./main      # Linux/macOS
./main.exe  # Windows
```
## ⚙️ Option 2: Manual compilation
```
g++ -std=c++20 -Iinclude -include pch.hpp -Isrc src/*.cpp -o main.exe
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
