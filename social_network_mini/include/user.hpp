#pragma once
// user.hpp
#include <unordered_map>
#include <unordered_set>
#include "helpers.hpp"
#include <vector>
#include <deque>

constexpr size_t expected_friends_number = 25;
constexpr float grow_by = 1.5;

constexpr size_t MAX_RECENT = 10; // Recent action
constexpr size_t DAY = 24;        // Hour

class UserInfo
{
public:
    using time_point = std::chrono::system_clock::time_point;
    using system_clock = std::chrono::system_clock;

public:
    // tuning
    UserInfo() noexcept;

public:
    // Add time
    bool add_friend(const std::string &name,
                    const std::ostringstream &oss) noexcept;

    // Here to
    bool unfriend(const std::string &name) noexcept;

    bool display_friends() const noexcept;

    bool display_recent_actions() const noexcept;

    bool display_notifications() const noexcept;

    bool display_messages(const std::string &name) const noexcept;

    bool verify_password(const std::string &password) const noexcept;

    void new_day(const std::string &name, std::ostringstream &oss, Time &time) noexcept;

    void add_notification(const time_point &tp, const std::string &str) noexcept;
    void add_message(const std::string &name,
                     const time_point &tp,
                     const std::ostringstream &oss,
                     const std::string &str) noexcept;

    void set_info(const std::string &name, const std::string &password) noexcept;

    void clean_old_actions() noexcept;
    void clear_notifications() noexcept;
    void clear_messages(const std::string &name) noexcept;

    const std::unordered_set<std::string> &
    get_friends_set() const noexcept { return friends_set_; }
    const std::vector<std::string> &
    get_friends_vec() const noexcept { return friends_vec; }

    bool check_if_friend_exist(const std::string &name) const noexcept;

private:
    std::string password_;
    std::string user_name_;
    std::unordered_map<std::string, std::deque<MessagesInfo>> boxes_;
    std::unordered_set<std::string> friends_set_;
    std::vector<std::string> friends_vec;
    std::deque<std::pair<std::string, std::string>> latest_10_;
    std::deque<MessagesInfo> notifications_;
    system_clock::time_point day_check;
    bool new_day_;
};