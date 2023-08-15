SELECT title, rating
FROM movies
    INNER JOIN ratings on id = movie_id
WHERE year = 2010
ORDER BY rating DESC, title;