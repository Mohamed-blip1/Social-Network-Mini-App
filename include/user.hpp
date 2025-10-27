#pragma once

// user.hpp

#include "helpers.hpp"

// STL:
#include <unordered_map>
#include <cstddef>
#include <vector>
#include <chrono>
#include <string>
#include <deque>

constexpr std::size_t expected_friends_number = 25;
constexpr float grow_by = 1.5;

constexpr std::size_t MAX_RECENT = 10; // Recent action
constexpr std::size_t DAY = 24;        // Hour

class UserInfo
{
public:
    using time_point = std::chrono::system_clock::time_point;
    using system_clock = std::chrono::system_clock;

public:
    // tuning
    // UserInfo() noexcept = default;
    explicit UserInfo(std::string pass) noexcept;

public:
    // Add time
    bool add_friend(const std::string &name,
                    std::string st_time) noexcept;

    // Here to
    bool unfriend(const std::string &name) noexcept;

    bool display_friends() const noexcept;

    bool display_recent_actions() const noexcept;

    bool display_notifications() const noexcept;

    bool display_messages(const std::string &name) const noexcept;

    bool verify_password(const std::string &password) const noexcept;

    bool new_day(const std::string &name, std::ostringstream &oss, Time &time) noexcept;

    void add_notification(const time_point &tp, std::string str) noexcept;
    void add_message(const std::string &name,
                     const time_point &tp,
                     std::string str,
                     std::string message) noexcept;

    void set_password(std::string password) noexcept;

    void clean_old_actions() noexcept;
    void clear_notifications() noexcept;
    void clear_messages(const std::string &name) noexcept;

    const std::vector<std::string> &
    get_friends_vec() const noexcept { return friends_vec_; }

    bool friend_exist(const std::string &name) const noexcept;
    std::deque<MessagesInfo> *get_friend_chat(const std::string &name) noexcept;
    const std::deque<MessagesInfo> *get_friend_chat(const std::string &name) const noexcept;

private:
    std::string password_;
    std::unordered_map<std::string, std::deque<MessagesInfo>> boxes_;
    std::vector<std::string> friends_vec_;
    std::deque<std::pair<std::string, std::string>> latest_10_;
    std::deque<MessagesInfo> notifications_;
    system_clock::time_point day_check;
    bool new_day_;
};
