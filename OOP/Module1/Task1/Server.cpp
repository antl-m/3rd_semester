#include "Server.h"

#include <exception>

namespace SocialNet {

    void Server::AddUser(std::string name, std::string surname) {
        users.emplace_back(users.size(),
                           std::move(name), std::move(surname));
    }

    void Server::check_user_id(UserId id, std::string message) const {
        if(id < 0 || id >= users.size())
            throw std::invalid_argument(std::move(message) +
                                        ": User with id = " + std::to_string(id) + " doesn't exist");
    }

    void Server::check_post_id(PostId id, std::string message) const {
        if(id < 0 || id >= posts.size())
            throw std::invalid_argument(std::move(message) +
                                        ": Post with id = " + std::to_string(id) + " doesn't exist");
    }

    void Server::UserAddPost(UserId author_id, std::string content, std::unordered_set<Theme> themes,
                             std::unordered_set<UserId> users_ref, std::unordered_set<PostId> posts_ref) {
        check_user_id(author_id, "UserAddPost");

        PostId post_id = posts.size();
        posts.emplace_back(post_id, author_id, std::move(content),
                           std::move(themes), std::move(users_ref), std::move(posts_ref));
        users[author_id].AddPosted(post_id);
    }

    void Server::UserReplyPost(UserId user_id, PostId post_id, std::string content, std::unordered_set<Theme> themes,
                               std::unordered_set<UserId> users_ref, std::unordered_set<PostId> posts_ref) {
        check_user_id(user_id, "UserReplyPost");
        check_post_id(post_id, "UserReplyPost");

        posts_ref.insert(post_id);

        PostId reply_id = posts.size();
        posts.emplace_back(reply_id, user_id, std::move(content),
                           std::move(themes), std::move(users_ref), std::move(posts_ref));
        users[user_id].AddPosted(post_id);
    }

} //namespace SocialNet