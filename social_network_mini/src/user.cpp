// user.cpp
#include "user.hpp"
#include <iostream>
#include <iomanip>

UserInfo::UserInfo() noexcept
{

    friends_set_.rehash(expected_friends_number * grow_by);
    friends_set_.max_load_factor(0.7);

    boxes_.rehash(expected_friends_number * grow_by);
    boxes_.max_load_factor(0.7);

    friends_vec.reserve(expected_friends_number * grow_by);
    day_check = system_clock::now();
    new_day_ = true;
}

bool UserInfo::add_friend(const std::string &name,
                          const std::ostringstream &oss) noexcept
{
    // if exist
    if (friends_set_.count(name))
        return false;

    friends_set_.emplace(name);

    auto it = std::lower_bound(friends_vec.begin(), friends_vec.end(), name);
    friends_vec.emplace(it, name);

    clean_old_actions();
    latest_10_.emplace_front(oss.str(), name);
    boxes_[name];

    return true;
}

bool UserInfo::unfriend(const std::string &name) noexcept
{
    auto _it = friends_set_.find(name);

    // if Not exist
    if (_it == friends_set_.end())
        return false;

    friends_set_.erase(_it);
    boxes_.erase(name);

    auto it = std::lower_bound(friends_vec.begin(), friends_vec.end(), name);
    if (it != friends_vec.end() && *it == name)
        friends_vec.erase(it);

    for (auto it = latest_10_.begin(); it != latest_10_.end();)
        if (it->second == name)
            it = latest_10_.erase(it);
        else
            ++it;

    return true;
}

bool UserInfo::display_friends() const noexcept
{
    if (friends_vec.empty())
        return false;

    for (const auto &friends : friends_vec)
        std::cout << "- " << friends << "\n";

    return true;
}
bool UserInfo::display_recent_actions() const noexcept
{

    if (latest_10_.empty())
        return false;

    for (const auto &[time, name] : latest_10_)
        std::cout << "- " << time << " : [" << name << "]\n";

    return true;
}

bool UserInfo::display_notifications() const noexcept
{

    if (notifications_.empty())
        return false;

    for (const auto &notification : notifications_)
        std::cout << "- " << notification.content << "\n";

    return true;
}

bool UserInfo::display_messages(const std::string &name) const noexcept
{
    // Check if friend exist
    // Before
    if (boxes_.at(name).empty())
        return false;

    for (auto it = boxes_.at(name).rbegin(); it != boxes_.at(name).rend(); ++it)
        std::cout << "- " << it->content << "\n";

    return true;
}

bool UserInfo::verify_password(const std::string &password) const noexcept
{
    if (password_ != password)
        return false;
    return true;
}

void UserInfo::new_day(const std::string &name, std::ostringstream &oss, Time &time) noexcept
{
    auto duration = std::chrono::duration_cast<std::chrono::hours>(time.tp - day_check);
    // Check
    // Before if friend exist
    if (duration >= std::chrono::hours(DAY) || boxes_.at(name).empty())
        new_day_ = true;

    if (new_day_)
    {
        oss << std::put_time(&time.tm, "%Y-%m-%d");
    
        // Here
        boxes_.at(name).emplace_front(time.tp, oss.str());
        new_day_ = false;
        oss.str("");
        oss.clear();
    }
}

void UserInfo::add_notification(
    const time_point &tp,
    const std::string &str) noexcept { notifications_.emplace_front(tp, str); }

void UserInfo::add_message(const std::string &name,
                           const time_point &tp,
                           const std::ostringstream &oss, const std::string &str) noexcept
{
    boxes_.at(name).emplace_front(tp, str);

    clean_old_actions();
    latest_10_.emplace_front(oss.str(),name);
}

void UserInfo::set_info(
    const std::string &name,
    const std::string &password) noexcept
{
    user_name_ = name;
    password_ = password;
}

void UserInfo::clean_old_actions() noexcept
{
    if (latest_10_.size() >= MAX_RECENT)
        latest_10_.pop_back();
}
void UserInfo::clear_notifications() noexcept { notifications_.clear(); }
void UserInfo::clear_messages(const std::string &name) noexcept { boxes_.at(name).clear(); }

bool UserInfo::check_if_friend_exist(const std::string &name) const noexcept
{
    if (!friends_set_.count(name))
        return false;
    else
        return true;
}
