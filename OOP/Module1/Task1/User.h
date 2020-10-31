#ifndef MODULE1_TASK1_USER_H
#define MODULE1_TASK1_USER_H

#include "Theme.h"
#include "Post.h"

#include <unordered_set>
#include <string>

namespace SocialNet {

    using PostId = std::size_t;
    using UserId = std::size_t;

    class User {
    public:
        User(UserId id, std::string name, std::string surname) :
                id(id),
                name(std::move(name)),
                surname(std::move(surname)) {}

        void AddPosted(PostId post_id){
            posted.insert(post_id);
        }

        void AddLiked(PostId post_id){
            liked.insert(post_id);
        }

        void AddDisliked(PostId post_id){
            disliked.insert(post_id);
        }

    private:
        friend class Server;

        const UserId id;
        std::string name, surname;
        std::unordered_set<UserId> friends;
        std::unordered_set<Theme> themes;
        std::unordered_set<PostId> liked, disliked, posted;
    };

} //namespace SocialNet

#endif //MODULE1_TASK1_USER_H
