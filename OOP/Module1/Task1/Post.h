#ifndef MODULE1_TASK1_POST_H
#define MODULE1_TASK1_POST_H

#include "Theme.h"
#include "User.h"

#include <unordered_set>
#include <string>

namespace SocialNet {

    using PostId = std::size_t;
    using UserId = std::size_t;

    class Post {
    public:
        Post(PostId id, UserId author,
             std::string content,
             std::unordered_set<Theme> themes,
             std::unordered_set<UserId> users_ref = {},
             std::unordered_set<PostId> posts_ref = {});

        void AddUsersRef(std::unordered_set<UserId> users_ref){
            this->users_ref.merge(std::move(users_ref));
        }

    private:
        friend class Server;

        const PostId id;
        const UserId author;
        std::string content;
        std::unordered_set<Theme> themes;
        std::unordered_set<UserId> users_ref;
        std::unordered_set<PostId> posts_ref;
        int64_t rating = 0;
    };

} //namespace SocialNet

#endif //MODULE1_TASK1_POST_H
