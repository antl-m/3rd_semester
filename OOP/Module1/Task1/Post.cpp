#include "Post.h"

namespace SocialNet {

    Post::Post(PostId id, UserId author, std::string content, std::unordered_set<Theme> themes,
               std::unordered_set<UserId> users_ref, std::unordered_set<PostId> posts_ref) :
            id(id), author(author),
            content(std::move(content)),
            themes(std::move(themes)),
            users_ref(std::move(users_ref)),
            posts_ref(std::move(posts_ref)) {}

} //namespace SocialNet