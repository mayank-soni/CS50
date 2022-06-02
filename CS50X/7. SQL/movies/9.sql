SELECT name FROM people
WHERE ID in (SELECT DISTINCT person_id FROM movies, stars
                WHERE movie_id = id and year = 2004)
ORDER BY birth;