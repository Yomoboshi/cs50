-- Find the ID of Kevin Bacon (the one born in 1958!)
WITH kevin_bacon_id AS (
    SELECT id
    FROM people
    WHERE people.name = 'Kevin Bacon' AND people.birth = 1958
),

-- Find the IDs of movies associated with Kevin Bacon’s ID
kevin_bacon_movies AS (
    SELECT movies.id
    FROM movies
    JOIN stars ON stars.movie_id = movies.id
    JOIN people ON people.id = stars.person_id
    WHERE stars.person_id = (SELECT id FROM kevin_bacon_id)
),

-- Find the IDs of people associated with those movie IDs
starred_with_kevin_bacon AS (
    SELECT DISTINCT stars.person_id
    FROM stars
    WHERE stars.movie_id IN (SELECT id FROM kevin_bacon_movies)
)

-- Find the names of people with those people IDs
SELECT people.name
FROM people
WHERE people.id IN (SELECT person_id FROM starred_with_kevin_bacon) AND people.name != 'Kevin Bacon'
