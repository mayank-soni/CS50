SELECT title from movies, stars, people
WHERE movies.id in (SELECT movies.id FROM movies, stars, people
                    WHERE movies.id = movie_id
                    AND person_id = people.id
                    AND name = "Helena Bonham Carter")
AND movies.id = movie_id
AND person_id = people.id
AND name = "Johnny Depp";
