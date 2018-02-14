"CREATE TABLE IF NOT EXISTS articles ( \
    id int PRIMARY KEY, \
    title text, \
    url text, \
    feedId int, \
    author text, \
    isFavorite int, \
    featuredImage text, \
    content text, \
    excerpt text, \
    isRead int, \
    pubDate date \
); \
CREATE TABLE IF NOT EXISTS feeds ( \
    id int PRIMARY KEY, \
    title text, \
    url text, \
    feedUrl text, \
    icon text, \
    isFavorite int, \
    lastPolled date, \
    whitelist text, \
    blacklist text \
);"
