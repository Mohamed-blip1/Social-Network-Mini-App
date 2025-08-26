#pragma once
#include <iostream>
#include <unordered_set>
#include <deque>

class UserInfo
{
public:
    UserInfo()
    {
        size_t expected_friends_number = 25;
        // unordredset
        friends_.rehash(expected_friends_number * 1.5);
        friends_.max_load_factor(0.7);
    }

public:
    bool add_friend(const std::string &name)
    {
        // if exist
        if (friends_.find(name) != friends_.end())
            return false;

        friends_.emplace(name);
        if (latest_5_.size() >= 5)
            latest_5_.pop_front();

        latest_5_.push_back(name);

        return true;
    }

    bool Unfriend(const std::string &name)
    {
        auto _it = friends_.find(name);

        // if Not exist
        if (_it == friends_.end())
            return false;

        friends_.erase(_it);

        return true;
    }
    std::unordered_set<std::string> &getfriends() { return friends_; }

private:
    std::unordered_set<std::string> friends_;
    std::deque<std::string> latest_5_;
    std::deque<std::string> Friend_requests_;
};