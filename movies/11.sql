SELECT title
FROM movies
    INNER JOIN ratings on id = movie_id
WHERE id IN
    (SELECT movie_id
    FROM stars
    WHERE person_id IN
        (SELECT id
        FROM people
        WHERE name = "Chadwick Boseman"
        )
    )
ORDER BY rating DESC
LIMIT 5;