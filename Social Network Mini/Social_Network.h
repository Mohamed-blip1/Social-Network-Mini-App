#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <unordered_map>
#include <random>
#include "user.h"

class Network
{
public:
    Network()
    {
        size_t expected_users_number = 100;
        // unorderedmap
        user_info_.rehash(expected_users_number * 1.5);
        user_info_.max_load_factor(0.7);
        // unorderedset
        users_set_.rehash(expected_users_number * 1.5);
        users_set_.max_load_factor(0.7);
        // vector
        users_vec_.reserve(expected_users_number * 1.5);
    }

public:
    bool Login(const std::string &name)
    {
        // if Not exist
        if (users_set_.find(name) == users_set_.end())
            return false;

        return true;
    }

    bool sign_up(const std::string &name)
    {
        // if exist
        if (users_set_.find(name) != users_set_.end())
            return false;

        user_info_[name];
        users_set_.emplace(name);
        users_vec_.emplace_back(name);

        return true;
    }

public:
    // user space actions.

    void add_friendship(const std::string &user, const std::string &name)
    {
        if (user == name)
            throw std::runtime_error("You can't add yourself as a friend!");

        if (users_set_.find(name) == users_set_.end())
            throw std::runtime_error("No account found!");

        if (!user_info_[user].add_friend(name))
            throw std::runtime_error("Friend already exist!");

        user_info_[user].add_friend(name);
        user_info_[name].add_friend(user);
    }

    bool Friends_suggestions(const std::string &user)
    {
        size_t _size = users_vec_.size();
        if (_size <= 1)
            return false;

        int n = 1;
        size_t limit = std::min<size_t>(8, _size);
        for (int i = 0; i < limit; ++i)
        {
            // skip if candidate is self or already a friend
            if (users_vec_[i] == user ||
                user_info_[user].getfriends().count(users_vec_[i]))
                continue;

            // show friend suggestion
            std::cout << n++ << " - " << users_vec_[i] << "\n";
        }

        // if no friend printed
        if (n == 1)
            return false;

        // reshuffle to get different suggestions next time
        shuffle_first_8(_size);

        return true;
    }

private:
    void shuffle_first_8(size_t _size)
    {

        std::random_device rd;
        std::mt19937 gen(rd());

        // Fisher-Yates shuffle only for first 8 slots
        size_t shuffle_limit = std::min<size_t>(8, _size);
        for (size_t i = 0; i < shuffle_limit; ++i)
        {
            std::uniform_int_distribution<size_t> distrib(i, _size - 1);
            size_t j = distrib(gen);

            if (i != j)
                std::swap(users_vec_[i], users_vec_[j]);
        }
    }

private:
    std::unordered_map<std::string, UserInfo> user_info_;
    std::unordered_set<std::string> users_set_;
    std::vector<std::string> users_vec_;
};