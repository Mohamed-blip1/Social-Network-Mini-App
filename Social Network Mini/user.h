// user.h
#pragma once
#include <iostream>
#include <unordered_set>
#include <deque>
#include <chrono>
#include <fstream>

constexpr size_t expected_friends_number = 25;
constexpr float grow_by = 1.5;

constexpr size_t MAX_RECENT = 5;
constexpr size_t DAY = 24; // Hour

class UserInfo
{
public:
    using system_clock = std::chrono::system_clock;

public:
    // tuning
    UserInfo() noexcept
    {

        friends_set.rehash(expected_friends_number * grow_by);
        friends_set.max_load_factor(0.7);

        friends_vec.reserve(expected_friends_number * grow_by);
        new_day_ = true;
        day_check = system_clock::now();
    }

public:
    // Add time
    bool add_friend(const std::string &name) noexcept
    {
        // if exist
        if (friends_set.count(name))
            return false;

        friends_set.emplace(name);

        auto it = std::lower_bound(friends_vec.begin(), friends_vec.end(), name);
        friends_vec.emplace(it, name);

        if (latest_5_.size() >= MAX_RECENT)
            latest_5_.pop_back();

        latest_5_.push_front(name);

        return true;
    }
    // Here to
    bool unfriend(const std::string &name) noexcept
    {
        auto _it = friends_set.find(name);

        // if Not exist
        if (_it == friends_set.end())
            return false;

        friends_set.erase(_it);

        auto it = std::lower_bound(friends_vec.begin(), friends_vec.end(), name);
        if (it != friends_vec.end() && *it == name)
            friends_vec.erase(it);

        for (auto it = latest_5_.begin(); it != latest_5_.end();)
            if (*it == name)
                it = latest_5_.erase(it);
            else
                ++it;

        return true;
    }

    bool display_friends() const noexcept
    {
        if (friends_vec.empty())
            return false;

        for (const auto &friends : friends_vec)
            std::cout << "- " << friends << "\n";

        return true;
    }

    bool display_recent_actions() const noexcept
    {

        if (latest_5_.empty())
            return false;

        for (const auto &last_5_actions : latest_5_)
            std::cout << "- " << last_5_actions << "\n";

        return true;
    }

    bool display_notifications() const noexcept
    {

        if (notifications_.empty())
            return false;

        for (const auto &notification : notifications_)
            std::cout << "- " << notification << "\n";

        return true;
    }

    bool display_messages() const noexcept
    {

        if (messages_.empty())
            return false;

        for (auto it = messages_.rbegin(); it != messages_.rend(); ++it)
            std::cout << "- " << *it << "\n";

        return true;
    }

    bool verify_password(const std::string &password)
    {
        if (password_ != password)
            return false;
        return true;
    }

    void new_day(std::ostringstream &oss, const std::tm &tm, const system_clock::time_point &tp)
    {
        auto duration = std::chrono::duration_cast<std::chrono::hours>(tp - day_check);
        if (duration >= std::chrono::hours(DAY))
            new_day_ = true;

        if (new_day_)
        {
            oss << std::put_time(&tm, "%Y-%m-%d");

            messages_.push_front(oss.str());
            new_day_ = false;
            oss.str("");
            oss.clear();
        }
    }

    const std::unordered_set<std::string> &get_friends_set() const noexcept { return friends_set; }
    const std::vector<std::string> &get_friends_vec() const noexcept { return friends_vec; }

    std::deque<std::string> &set_notifications() noexcept { return notifications_; }
    std::deque<std::string> &set_messages() noexcept { return messages_; }
    void set_password(const std::string &password) { password_ = password; }

private:
    std::string password_;
    std::unordered_set<std::string> friends_set;
    std::vector<std::string> friends_vec;
    std::deque<std::string> latest_5_;
    std::deque<std::string> messages_;
    std::deque<std::string> notifications_;
    bool new_day_;
    system_clock::time_point day_check;
};