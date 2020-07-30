"CREATE TABLE IF NOT EXISTS articles ( \
    id int PRIMARY KEY, \
    title text, \
    url text, \
    feed_id int, \
    author text, \
    is_favorite int, \
    featured_image text, \
    content text, \
    excerpt text, \
    is_read int, \
    published_date date \
); \
CREATE TABLE IF NOT EXISTS feeds ( \
    id int PRIMARY KEY, \
    title text, \
    site_url text, \
    feed_url text, \
    icon text, \
    is_favorite int, \
    last_polled date, \
    filter_accept text, \
    filter_reject text \
);"
