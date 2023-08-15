SELECT title
FROM movies
WHERE id IN
    (SELECT movie_id
    FROM stars
        INNER JOIN people on stars.person_id = id
    WHERE name = "Jennifer Lawrence"
    )
AND id IN
    (SELECT movie_id
    FROM stars
        INNER JOIN people on stars.person_id = id
    WHERE name = "Bradley Cooper"
    );