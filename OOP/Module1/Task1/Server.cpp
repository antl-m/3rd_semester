#include "Server.h"

#include <exception>

namespace SocialNet {

    UserId Server::AddUser(std::string name, std::string surname) {
        UserId id = users.size();
        users.emplace_back( id, std::move(name), std::move(surname));
        return id;
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

    PostId Server::UserAddPost(UserId author_id, std::string content, std::unordered_set<Theme> themes,
                               std::unordered_set<UserId> users_ref, std::unordered_set<PostId> posts_ref) {
        check_user_id(author_id, "UserAddPost");

        PostId post_id = posts.size();
        posts.emplace_back(post_id, author_id, std::move(content),
                           std::move(themes), std::move(users_ref), std::move(posts_ref));
        users[author_id].AddPosted(post_id);
        return post_id;
    }

    PostId Server::UserReplyPost(UserId user_id, PostId post_id, std::string content, std::unordered_set<Theme> themes,
                                 std::unordered_set<UserId> users_ref, std::unordered_set<PostId> posts_ref) {
        check_user_id(user_id, "UserReplyPost");
        check_post_id(post_id, "UserReplyPost");

        posts_ref.insert(post_id);
        return UserAddPost(user_id, std::move(content), std::move(themes), std::move(users_ref), std::move(posts_ref));
    }

    PostId Server::UserRepostPost(UserId user_id, PostId post_id, std::unordered_set<UserId> users_ref) {
        check_user_id(user_id, "UserRepostPost");
        check_post_id(post_id, "UserRepostPost");

        Post new_post = posts[post_id];
        new_post.AddUsersRef(std::move(users_ref));
        return UserAddPost(user_id, std::move(new_post.content), std::move(new_post.themes), std::move(new_post.users_ref),
                           std::move(new_post.posts_ref));
    }

    void Server::UserLikePost(UserId user_id, PostId post_id) {
        check_user_id(user_id, "UserLikePost");
        check_post_id(post_id, "UserLikePost");

        users[user_id].AddLiked(post_id);
        ++posts[post_id].rating;
    }

    void Server::UserDislikePost(UserId user_id, PostId post_id) {
        check_user_id(user_id, "UserDislikePost");
        check_post_id(post_id, "UserDislikePost");

        users[user_id].AddDisliked(post_id);
        --posts[post_id].rating;
    }

} //namespace SocialNet