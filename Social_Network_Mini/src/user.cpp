// user.cpp
#include "user.h"
#include <iostream>
#include <iomanip>

UserInfo::UserInfo() noexcept
{

    friends_set.rehash(expected_friends_number * grow_by);
    friends_set.max_load_factor(0.7);

    friends_vec.reserve(expected_friends_number * grow_by);
    new_day_ = true;
    day_check = system_clock::now();
}

bool UserInfo::add_friend(const std::string &name,
                          const std::ostringstream &oss) noexcept
{
    // if exist
    if (friends_set.count(name))
        return false;

    friends_set.emplace(name);

    auto it = std::lower_bound(friends_vec.begin(), friends_vec.end(), name);
    friends_vec.emplace(it, name);

    if (latest_5_.size() >= MAX_RECENT)
        latest_5_.pop_back();

    latest_5_.emplace_front(oss.str(), name);

    return true;
}

bool UserInfo::unfriend(const std::string &name) noexcept
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
        if (it->second == name)
            it = latest_5_.erase(it);
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

    if (latest_5_.empty())
        return false;

    for (const auto &[time, name] : latest_5_)
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

bool UserInfo::display_messages() const noexcept
{

    if (messages_.empty())
        return false;

    for (auto it = messages_.rbegin(); it != messages_.rend(); ++it)
        std::cout << "- " << it->content << "\n";

    return true;
}

bool UserInfo::verify_password(const std::string &password) const noexcept
{
    if (password_ != password)
        return false;
    return true;
}

void UserInfo::new_day(std::ostringstream &oss, Time &time) noexcept
{
    auto duration = std::chrono::duration_cast<std::chrono::hours>(time.tp - day_check);
    if (duration >= std::chrono::hours(DAY) || messages_.empty())
        new_day_ = true;

    if (new_day_)
    {
        oss << std::put_time(&time.tm, "%Y-%m-%d");

        messages_.emplace_front(time.tp, oss.str());
        new_day_ = false;
        oss.str("");
        oss.clear();
    }
}

void UserInfo::add_notification(
    const time_point &tp,
    const std::string &str) noexcept { notifications_.emplace_front(tp, str); }

void UserInfo::add_message(
    const time_point &tp,
    const std::string &str) noexcept { messages_.emplace_front(tp, str); }

void UserInfo::set_password(
    const std::string &password) noexcept { password_ = password; }

void UserInfo::clear_notifications() noexcept { notifications_.clear(); }
void UserInfo::clear_messages() noexcept { messages_.clear(); }
