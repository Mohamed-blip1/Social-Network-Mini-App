// social_network.cpp
#include "social_network.h"

Network::Network() noexcept
{

    user_info_.rehash(USERS_EXPECTED * GROW_BY);
    user_info_.max_load_factor(0.7);

    users_set_.rehash(USERS_EXPECTED * GROW_BY);
    users_set_.max_load_factor(0.7);

    users_vec_.reserve(USERS_EXPECTED * GROW_BY);
}

void Network::Login(const std::string &name, const std::string &password) const
{
    // if Not exist
    if (!users_set_.count(name))
        throw std::runtime_error("Username not found!");

    if (!user_info_.at(name).verify_password(password))
        throw std::runtime_error("Incorrect password!");
}

bool Network::sign_up(const std::string &name, const std::string &password) noexcept
{
    // if exist
    if (users_set_.count(name))
        return false;

    users_set_.emplace(name);
    users_vec_.emplace_back(name);
    user_info_[name].set_password(password);

    return true;
}

void Network::add_friendship(const std::string &user, const std::string &name)
{
    Time time;
    std::ostringstream oss;
    time.tm = *std::localtime(&time.tt);
    oss << std::put_time(&time.tm, "%Y-%m-%d %H:%M");

    if (!users_set_.count(name))
        throw std::runtime_error("No account found!");

    if (user == name)
        throw std::runtime_error("You can't add yourself as a friend!");

    if (!user_info_[user].add_friend(name, oss))
        throw std::runtime_error("Friend already exist!");

    // add friendship on bout users
    // and send a notification to the other user (He can remove)
    user_info_[name].add_friend(user, oss);
    user_info_[name].add_notification(time.tp, oss.str() + " :You and [" + user + "] are friends now!");
    user_info_[user].add_notification(time.tp, oss.str() + " :You and [" + name + "] are friends now!");
}

void Network::remove_friendship(const std::string &user, const std::string &name)
{
    Time time;
    std::ostringstream oss;
    time.tm = *std::localtime(&time.tt);
    oss << std::put_time(&time.tm, "%Y-%m-%d %H:%M");

    if (!users_set_.count(name))
        throw std::runtime_error("No account found!");

    if (user == name)
        throw std::runtime_error("You can't remove yourself!");

    if (!user_info_[user].unfriend(name))
        throw std::runtime_error("'" + name + "' is not your friend!");

    user_info_[name].unfriend(user);
    user_info_[name].add_notification(time.tp, oss.str() + " :You and [" + user + "] are no longer friends!");
    user_info_[user].add_notification(time.tp, oss.str() + " :You and [" + name + "] are no longer friends!");
}

void Network::send_message(const std::string &user, const std::string &name, const std::string &message)
{
    Time time;
    std::ostringstream oss;
    time.tm = *std::localtime(&time.tt);

    if (user != name)
        user_info_[user].new_day(oss, time);
    user_info_[name].new_day(oss, time);

    oss << std::put_time(&time.tm, "%H:%M");
    if (user == name)
        user_info_[name].add_message(time.tp, oss.str() + " [me]: " + message);

    else
    {
        user_info_[name].add_message(time.tp, oss.str() + " [" + user + "]: " + message);
        user_info_[user].add_message(time.tp, oss.str() + " [me->" + name + "]: " + message);
    }
}
// suggest 10 friend then shuffle the first 10 elements of the vector
bool Network::Friends_suggestions(const std::string &user) noexcept
{
    const size_t _size = users_vec_.size();

    limited_shuffle(_size);

    // there is only 1 user
    if (_size <= ONE_USER)
        return false;

    int n = 1;
    for (int i = 0; i < _size; ++i)
    {
        // skip if candidate is self or already a friend
        if (users_vec_[i] == user ||
            user_info_[user].get_friends_set().count(users_vec_[i]))
            continue;

        // show friend suggestion
        std::cout << std::setw(SPACE) << std::left << n++ << "- " << users_vec_[i] << "\n";

        if (n >= DISPLAY_LIMITS)
            break;
    }

    // if no friend printed
    if (n == _0_FRIENDS_DISPLAYED)
        return false;

    return true;
}

// max friend of friend suggesting: 8
bool Network::bfs(const std::string &user) noexcept
{
    bfs_.clear();

    const auto &user_friends = user_info_[user].get_friends_vec();
    const size_t &_size = user_friends.size();

    if (user_friends.empty())
        return false;

    for (size_t i = 0; i < _size; ++i)
    {
        const auto &friends_of_friend = user_info_[user_friends[i]].get_friends_vec();

        size_t max = 0;
        for (size_t j = 0; j < friends_of_friend.size(); ++j)
        {
            if (!filter(user_friends, user, friends_of_friend[j]))
                continue;

            bfs_.push_front(friends_of_friend[j]);

            if (++max >= LIMITS_TAKING)
                break;
        }
        if (bfs_.size() >= DISPLAY_LIMITS)
            break;
    }

    if (!show_bfs())
        return false;

    return true;
}
bool Network::show_messages(const std::string &user) const noexcept
{
    if (!user_info_.at(user).display_messages())
        return false;

    return true;
}

bool Network::show_friends(const std::string &user) const noexcept
{
    if (!user_info_.at(user).display_friends())
        return false;

    return true;
}

// show recent 5 friend actions
bool Network::recent_actions(const std::string &user) const noexcept
{
    if (!user_info_.at(user).display_recent_actions())
        return false;

    return true;
}

bool Network::notifications(const std::string &user) const noexcept
{
    if (!user_info_.at(user).display_notifications())
        return false;

    return true;
}

// splited Fisher-Yates shuffle only for first 10 slots
void Network::limited_shuffle(size_t _max) noexcept
{
    // In Friends_suggestions, you shuffle all users. Ideally, only shuffle non-friends that are candidates.
    std::random_device rd;
    std::mt19937 gen(rd());

    size_t limits_shuffle = std::min<size_t>(LIMITS, _max);
    for (size_t i = 0; i < limits_shuffle; ++i)
    {
        std::uniform_int_distribution<size_t> distrib(i, _max - 1);

        size_t j = distrib(gen);

        if (i != j)
            std::swap(users_vec_[i], users_vec_[j]);
    }
}

bool Network::filter(const std::vector<std::string> &user_friends,
                     const std::string &user, const std::string &target) const noexcept
{
    // if self
    if (target == user)
        return false;

    // if already printed
    bool already_exist = false;
    for (size_t i = 0; i < bfs_.size(); ++i)
        if (bfs_[i] == target)
        {
            already_exist = true;
            break;
        }
    if (already_exist)
        return false;

    // existing friends
    auto it = std::lower_bound(user_friends.begin(), user_friends.end(), target);
    if (it != user_friends.end() && *it == target)
        return false;

    return true;
}

bool Network::show_bfs() const noexcept
{
    // if no friends
    if (!bfs_.size())
        return false;

    for (const auto &bfs : bfs_)
        std::cout << std::setw(SPACE) << std::left << "- " << bfs << "\n";

    return true;
}