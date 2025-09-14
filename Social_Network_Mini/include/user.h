#pragma once
// user.h
#include <unordered_set>
#include "helpers.h"
#include <vector>
#include <deque>

constexpr size_t expected_friends_number = 25;
constexpr float grow_by = 1.5;

constexpr size_t MAX_RECENT = 5; // Recent action
constexpr size_t DAY = 24;       // Hour

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

    bool display_messages() const noexcept;

    bool verify_password(const std::string &password) const noexcept;

    void new_day(std::ostringstream &oss, Time &time) noexcept;

    void add_notification(const time_point &tp, const std::string &str) noexcept;
    void add_message(const time_point &tp, const std::string &str) noexcept;

    void set_password(const std::string &password) noexcept;

    void clear_notifications() noexcept;
    void clear_messages() noexcept;

    const std::unordered_set<std::string> &
    get_friends_set() const noexcept { return friends_set; }
    const std::vector<std::string> &
    get_friends_vec() const noexcept { return friends_vec; }

private:
    std::string password_;
    std::unordered_set<std::string> friends_set;
    std::vector<std::string> friends_vec;
    std::deque<std::pair<std::string, std::string>> latest_5_;
    std::deque<MessagesInfo> messages_;
    std::deque<MessagesInfo> notifications_;
    system_clock::time_point day_check;
    bool new_day_;
};