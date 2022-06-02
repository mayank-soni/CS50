SELECT DISTINCT name FROM stars, people
WHERE people.id = person_id
AND NOT (name = "Kevin Bacon" AND birth = 1958)
AND movie_id in
    (SELECT movie_id FROM people, stars
     WHERE people.id = person_id
     AND name = "Kevin Bacon" and birth = 1958);