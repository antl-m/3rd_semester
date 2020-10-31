#ifndef MODULE1_TASK1_SERVER_H
#define MODULE1_TASK1_SERVER_H

#include "Post.h"
#include "User.h"

#include "vector"

namespace SocialNet {

    class Server {
    public:
        Server() = default;

        void AddUser(std::string name, std::string surname);

        void UserAddPost(UserId author_id, std::string content,
                     std::unordered_set<Theme> themes,
                     std::unordered_set<UserId> users_ref = {},
                     std::unordered_set<PostId> posts_ref = {});

        void UserReplyPost(UserId user_id, PostId post_id,
                           std::string content,
                           std::unordered_set<Theme> themes,
                           std::unordered_set<UserId> users_ref = {},
                           std::unordered_set<PostId> posts_ref = {});

        void UserRepostPost(UserId user_id, PostId post_id,
                            std::unordered_set<UserId> users_ref);

        void UserLikePost(UserId user_id, PostId post_id);

    private:
        void check_user_id(UserId id, std::string message) const;
        void check_post_id(PostId id, std::string message) const;

        std::vector<Post> posts;
        std::vector<User> users;
    };

} //namespace SocialNet

#endif //MODULE1_TASK1_SERVER_H
