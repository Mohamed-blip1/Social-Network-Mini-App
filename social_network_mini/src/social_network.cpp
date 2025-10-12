// social_network.cpp
#include "social_network.hpp"

Network::Network() noexcept
{
    user_info_.rehash(USERS_EXPECTED * GROW_BY);
    user_info_.max_load_factor(0.7);

    users_vec_.reserve(USERS_EXPECTED * GROW_BY);
// #ifdef DEBUG
//     std::string st;
//     for (size_t i = 0; i < 20; ++i)
//     {
//         st = 'a' + i;
//         sign_up(st, st);
//     }
// #endif
}

Result Network::login(const std::string &name, const std::string &password) const noexcept
{
    auto user = get_user(name);
    // if Not exist
    if (!user)
        return Result::UserNotFound;

    if (!user->verify_password(password))
        return Result::IncorrectPassword;

    return Result::Success;
}

bool Network::sign_up(const std::string &name, std::string password) noexcept
{
    // if exist
    if (user_exist(name))
        return false;

    // here
    users_vec_.emplace_back(name);
    user_info_.try_emplace(name, std::move(password));
    (void)add_friendship(name, name);
    return true;
}

Result Network::add_friendship(const std::string &user, const std::string &other) noexcept
{

    auto other_it = get_user(other);
    if (!other_it)
        return Result::UserNotFound;

    auto user_it = get_user(user);
    if (user_it->friend_exist(other))
        return Result::AlreadyFriends;

    Time time;
    std::ostringstream oss;
    oss << std::put_time(&time.tm, "%Y-%m-%d %H:%M");

    // In sign-up every account add it self as a friend
    user_it->add_friend(other, oss.str());
    user_it->add_notification(
        time.tp, notification_msg(oss.str(), other, AdFriendMsg));

    if (user_it != other_it)
    {
        other_it->add_friend(user, oss.str());
        other_it->add_notification(
            time.tp, notification_msg(oss.str(), user, AdFriendMsg));
    }

    return Result::Success;
}

Result Network::remove_friendship(const std::string &user, const std::string &other) noexcept
{
    auto other_it = get_user(other);
    if (!other_it)
        return Result::UserNotFound;

    auto user_it = get_user(user);
    if (user_it == other_it)
        return Result::SameUser;

    if (!user_it->unfriend(other))
        return Result::NotFriend;

    other_it->unfriend(user);

    Time time;
    std::ostringstream oss;
    oss << std::put_time(&time.tm, "%Y-%m-%d %H:%M");

    other_it->add_notification(time.tp, notification_msg(oss.str(), user, UnfriendMsg));
    user_it->add_notification(time.tp, notification_msg(oss.str(), other, UnfriendMsg));

    return Result::Success;
}

void Network::send_message(const std::string &user, const std::string &other, const std::string &message) noexcept
{
    Time time;
    std::ostringstream oss;

    auto user_it = get_user(user);
    auto other_it = get_user(other);

    if (user_it != other_it)
        user_it->new_day(other, oss, time);
    other_it->new_day(user, oss, time);

    oss << std::put_time(&time.tm, "%H:%M");
    if (user_it != other_it)
        other_it->add_message(user, time.tp, oss.str(), oss.str() + " [" + user + "]: " + message);
    user_it->add_message(other, time.tp, oss.str(), oss.str() + " [me]: " + message);
}

// suggest 10 friend then shuffle the first 10 elements of the vector
bool Network::Friends_suggestions(const std::string &user) noexcept
{
    const size_t _size = users_vec_.size();

    // there is only 1 user
    if (_size <= ONE_USER)
        return false;

    limited_shuffle(_size);
    auto user_it = get_user(user);

    size_t n = 1;
    for (size_t i = 0; i < _size && n < DISPLAY_LIMITS; ++i)
    {
        std::string &candidate = users_vec_[i];
        // skip if candidate is self or already a friend
        if (candidate == user ||
            user_it->friend_exist(candidate))
            continue;

        // show friend suggestion
        std::cout << std::setw(SPACE) << std::left << n++ << "- " << candidate << "\n";
    }

    return n != _0_FRIENDS_DISPLAYED;
}

// max friend of friend suggesting: 8
bool Network::bfs(const std::string &user) noexcept
{
    bfs_.clear();

    const auto &user_friends = user_info_.at(user).get_friends_vec();
    const size_t &_size = user_friends.size();

    if (user_friends.empty())
        return false;

    const std::string *name;
    for (size_t i = 0; i < _size; ++i)
    {
        const auto &friends_of_friend = user_info_.at(user_friends[i]).get_friends_vec();

        size_t max = 0;
        for (size_t j = 0; j < friends_of_friend.size(); ++j)
        {
            name = &friends_of_friend[j];

            if (!filter(user_friends, user, *name))
                continue;

            bfs_.push_front(*name);

            if (++max >= LIMITS_TAKING)
                break;
        }
        if (bfs_.size() >= DISPLAY_LIMITS)
            break;
    }

    // If no friends of friends
    if (!show_bfs())
        return false;

    return true;
}

bool Network::show_messages(const std::string &user, const std::string &name) const noexcept
{
    return user_info_.at(user).display_messages(name);
}

bool Network::show_friends(const std::string &user) const noexcept
{
    return user_info_.at(user).display_friends();
}

// show recent 5 friend actions
bool Network::recent_actions(const std::string &user) const noexcept
{
    return user_info_.at(user).display_recent_actions();
}

bool Network::notifications(const std::string &user) const noexcept
{
    return user_info_.at(user).display_notifications();
}

// splited Fisher-Yates shuffle only for first 10 slots
void Network::limited_shuffle(size_t _max) noexcept
{
    // Later: only shuffle non-friends that are candidates.
    std::mt19937 gen(std::random_device{}());

    for (size_t i = 0, limits = std::min<size_t>(LIMITS, _max); i < limits; ++i)
        std::swap(users_vec_[i],
                  users_vec_[std::uniform_int_distribution<size_t>(i, _max - 1)(gen)]);
}

bool Network::filter(const std::vector<std::string> &user_friends,
                     const std::string &user, const std::string &target) const noexcept
{
    // if self
    if (target == user)
        return false;

    // if already printed
    if (std::find(bfs_.begin(),
                  bfs_.end(), target) != bfs_.end())
        return false;

    // existing friends
    if (std::binary_search(user_friends.begin(),
                           user_friends.end(), target))
        return false;

    return true;
}

bool Network::change_password(const std::string &user, std::string new_pass) noexcept
{
    // is it butter to change hole disane a bit and send the user pointer as a parameter instead of sending the name as a string ?
    auto user_it = get_user(user);
    if (!user_it)
        return false;

    user_it->set_password(std::move(new_pass));
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

UserInfo *Network::get_user(const std::string &name) noexcept
{
    auto it = user_info_.find(name);
    return (it != user_info_.end()) ? &it->second : nullptr;
}
const UserInfo *Network::get_user(const std::string &name) const noexcept
{
    auto it = user_info_.find(name);
    return (it != user_info_.end()) ? &it->second : nullptr;
}

bool Network::user_exist(const std::string &name) const noexcept
{
    return user_info_.find(name) != user_info_.end();
}

bool Network::user_and_friend_exist(const std::string &user, const std::string &other) const noexcept
{
    if (!user_exist(other))
        return false;

    return user_info_.at(user).friend_exist(other);
}

const std::string Network::notification_msg(const std::string &time_st, const std::string &name, bool choice) const noexcept
{
    if (choice == UnfriendMsg)
        return time_st + " :You and [" + name + "] are no longer friends!";
    // AdFriendMsg
    return time_st + " :You and [" + name + "] are friends now!";
}