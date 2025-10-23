// user.cpp
#include "user.hpp"

// STL:
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <utility>
#include <string>

UserInfo::UserInfo(std::string pass) noexcept
    : password_(std::move(pass))
{
    boxes_.rehash(static_cast<std::size_t>(expected_friends_number * grow_by));
    boxes_.max_load_factor(0.7f);

    friends_vec.reserve(static_cast<std::size_t>(expected_friends_number * grow_by));
    day_check = system_clock::now();
    new_day_ = true;
}

bool UserInfo::add_friend(const std::string &name,
                          std::string st_time) noexcept
{
    // if exist
    if (friend_exist(name))
        return false;
    auto it = std::lower_bound(friends_vec.begin(), friends_vec.end(), name);
    friends_vec.emplace(it, name);

    boxes_.try_emplace(name);
    clean_old_actions();
    latest_10_.emplace_front(std::move(st_time), name);

    return true;
}

bool UserInfo::unfriend(const std::string &name) noexcept
{

    // if Not exist
    if (!friend_exist(name))
        return false;

    boxes_.erase(name);

    auto it = std::lower_bound(friends_vec.begin(), friends_vec.end(), name);
    if (it != friends_vec.end() && *it == name)
        friends_vec.erase(it);

    latest_10_.erase(std::remove_if(latest_10_.begin(), latest_10_.end(),
                                    [name](const std::pair<std::string, std::string> &user)
                                    {
                                        return user.second == name;
                                    }),
                     latest_10_.end());

    // for (auto it = latest_10_.begin(); it != latest_10_.end();)
    //     if (it->second == name)
    //         it = latest_10_.erase(it);
    //     else
    //         ++it;

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
    auto chat_it = get_friend_chat(name);
    // if friend not exist or chat empty
    if (!chat_it || chat_it->empty())
        return false;

    for (auto it = chat_it->rbegin(); it != chat_it->rend(); ++it)
        std::cout << "- " << it->content << "\n";

    return true;
}

bool UserInfo::verify_password(const std::string &password) const noexcept
{
    return password_ == password;
}

bool UserInfo::new_day(const std::string &name, std::ostringstream &oss, Time &time) noexcept
{
    auto duration = std::chrono::duration_cast<std::chrono::hours>(time.tp - day_check);

    auto chat_it = get_friend_chat(name);
    // if friend not exist
    if (!chat_it)
        return false;

    if (duration >= std::chrono::hours(DAY) || chat_it->empty())
        new_day_ = true;

    if (new_day_)
    {
        oss << std::put_time(&time.tm, "%Y-%m-%d");

        // Here ?
        chat_it->emplace_front(time.tp, oss.str());
        new_day_ = false;
        oss.str("");
        oss.clear();
    }
    return true;
}

void UserInfo::add_notification(
    const time_point &tp,
    std::string str) noexcept { notifications_.emplace_front(tp, std::move(str)); }

void UserInfo::add_message(const std::string &name,
                           const time_point &tp,
                           std::string time_st,
                           std::string message) noexcept
{
    boxes_.at(name).emplace_front(tp, std::move(message));

    clean_old_actions();
    latest_10_.emplace_front(std::move(time_st), name);
}

void UserInfo::set_password(
    std::string password) noexcept { password_ = std::move(password); }

void UserInfo::clean_old_actions() noexcept
{
    if (latest_10_.size() >= MAX_RECENT)
        latest_10_.pop_back();
}
void UserInfo::clear_notifications() noexcept { notifications_.clear(); }
void UserInfo::clear_messages(const std::string &name) noexcept { boxes_.at(name).clear(); }

bool UserInfo::friend_exist(const std::string &name) const noexcept
{
    return boxes_.find(name) != boxes_.end();
}

std::deque<MessagesInfo> *UserInfo::get_friend_chat(const std::string &name) noexcept
{
    auto it = boxes_.find(name);
    return (it != boxes_.end()) ? &it->second : nullptr;
}
const std::deque<MessagesInfo> *UserInfo::get_friend_chat(const std::string &name) const noexcept
{
    auto it = boxes_.find(name);
    return (it != boxes_.end()) ? &it->second : nullptr;
}
