#pragma once

// Social_Network.hpp

#include "user.hpp"

// STL:
#include <unordered_map>
#include <cstddef>
#include <chrono>
#include <string>
#include <vector>
#include <deque>


constexpr std::size_t USERS_EXPECTED = 100;
constexpr float GROW_BY = 1.5;
constexpr std::size_t SPACE = 3;
constexpr std::size_t DISPLAY_LIMITS = 10;
constexpr std::size_t ONE_USER = 1;
constexpr std::size_t _0_FRIENDS_DISPLAYED = 1;
constexpr std::size_t LIMITS_TAKING = 4;
constexpr std::size_t LIMITS = 10;
constexpr bool UnfriendMsg = 0;
constexpr bool AdFriendMsg = 1;

enum class Result
{
    Success,
    UserNotFound,
    IncorrectPassword,
    AlreadyFriends,
    NotFriend,
    SameUser
};

class Network
{
public:
    using system_clock = std::chrono::system_clock;

public:
    // tuning
    explicit Network() noexcept;

public:
    // Use Error handling (try/catch)!!!!!!
    [[nodiscard]] Result login(const std::string &name, const std::string &password) const noexcept;

    bool sign_up(const std::string &name, std::string password) noexcept;

public:
    // user SPACE actions.

    [[nodiscard]] Result add_friendship(const std::string &user, const std::string &other) noexcept;

    [[nodiscard]] Result remove_friendship(const std::string &user, const std::string &other) noexcept;

    void send_message(const std::string &user,
                      const std::string &other, const std::string &message) noexcept;

    // suggest 10 friend then shuffle the first 10 elements of the vector
    bool Friends_suggestions(const std::string &user) noexcept;

    // max friend of friend suggesting: 8
    bool bfs(const std::string &user) noexcept;

    bool show_messages(const std::string &user,
                       const std::string &other) const noexcept;
    bool show_friends(const std::string &user) const noexcept;
    // show recent 5 friend actions
    bool recent_actions(const std::string &user) const noexcept;
    bool notifications(const std::string &user) const noexcept;

    bool change_password(const std::string &name, std::string new_pass) noexcept;

    void clear_notifications(const std::string &user) noexcept;
    void clear_messages(const std::string &user, const std::string &name) noexcept;

    // befor send message
    bool user_and_friend_exist(const std::string &user, const std::string &other) const noexcept;
    inline bool user_exist(const std::string &name) const noexcept;

    inline UserInfo *get_user(const std::string &name) noexcept;
    inline const UserInfo *get_user(const std::string &name) const noexcept;

private:
    // splited Fisher-Yates shuffle only for first 10 slots
    void limited_shuffle(std::size_t _max) noexcept;

    bool filter(const std::vector<std::string> &user_friends,
                const std::string &user, const std::string &target) const noexcept;

    bool show_bfs() const noexcept;

    const std::string notification_msg(const std::string &time_st, const std::string &name,
                                       bool choice = AdFriendMsg) const noexcept;

private:
    std::unordered_map<std::string, UserInfo> user_info_;
    std::vector<std::string> users_vec_;
    std::deque<std::string> bfs_;
};