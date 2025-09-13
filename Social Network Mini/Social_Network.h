#pragma once
// Social_Network.h
#include <unordered_map>
#include <array>
#include <random>
#include <iomanip>
#include "user.h"

constexpr size_t USERS_EXPECTED = 100;
constexpr float GROW_BY = 1.5;

constexpr size_t SPACE = 3;
constexpr size_t DISPLAY_LIMITS = 10;
constexpr size_t ONE_USER = 1;
constexpr size_t _0_FRIENDS_DISPLAYED = 1;

constexpr size_t LIMITS_TAKING = 4;

constexpr size_t LIMITS = 10;

struct Time
{
    using system_clock = std::chrono::system_clock;
    system_clock::time_point now_time;
    std::time_t tt;
    std::tm tm;

    Time()
    {
        now_time = system_clock::now();
        tt = system_clock::to_time_t(now_time);
        tm = *std::localtime(&tt);
    }
    ~Time() = default;
};

class Network
{
public:
    using system_clock = std::chrono::system_clock;

public:
    // tuning
    Network() noexcept;

public:
    // Use Error handling (try/catch)!!!!!!
    void Login(const std::string &name, const std::string &password) const;

    bool sign_up(const std::string &name, const std::string &password) noexcept;

public:
    // user SPACE actions.

    void add_friendship(const std::string &user, const std::string &name);

    void remove_friendship(const std::string &user, const std::string &name);

    void send_message(const std::string &user, const std::string &name, const std::string &message);

    // suggest 10 friend then shuffle the first 10 elements of the vector
    bool Friends_suggestions(const std::string &user) noexcept;

    // max friend of friend suggesting: 8
    bool bfs(const std::string &user) noexcept;

    bool show_messages(const std::string &user) const noexcept;
    bool show_friends(const std::string &user) const noexcept;
    // show recent 5 friend actions
    bool recent_actions(const std::string &user) const noexcept;
    bool notifications(const std::string &user) const noexcept;

    void clear_notifications(const std::string &user) { user_info_[user].clear_notifications(); }
    void clear_messages(const std::string &user) { user_info_[user].clear_messages(); }

    // befor send message
    bool check_if_user_exist(const std::string &user)
    {
        if (!users_set_.count(user))
            return false;
        return true;
    }

private:
    // splited Fisher-Yates shuffle only for first 10 slots
    void limited_shuffle(size_t _max) noexcept;

    bool filter(const std::vector<std::string> &user_friends,
                const std::string &user, const std::string &target) const noexcept;

    bool show_bfs() const noexcept;

private:
    std::unordered_map<std::string, UserInfo> user_info_;
    std::unordered_set<std::string> users_set_;
    std::vector<std::string> users_vec_;
    std::deque<std::string> bfs_;
};