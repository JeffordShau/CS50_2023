


SELECT name
FROM people
    INNER JOIN stars on people.id = stars.person_id
    INNER JOIN movies on stars.movie_id = movies.id
WHERE movies.id IN
    (SELECT movies.id
    FROM movies
        INNER JOIN stars on movies.id = stars.movie_id
        INNER JOIN people on stars.person_id = people.id
    WHERE name = "Kevin Bacon"
        AND birth = 1958
    )
    AND name <> "Kevin Bacon";