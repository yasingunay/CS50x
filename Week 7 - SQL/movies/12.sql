--In 12.sql, write a SQL query to list the titles of all movies in which both Bradley Cooper and Jennifer Lawrence starred.
--Your query should output a table with a single column for the title of each movie.
--You may assume that there is only one person in the database with the name Bradley Cooper.
--You may assume that there is only one person in the database with the name Jennifer Lawrence.

SELECT title FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN	 people ON stars.person_id = people.id
WHERE name = 'Bradley Cooper'
AND title IN (
    SELECT title FROM movies
    JOIN stars ON movies.id = stars.movie_id
    JOIN	 people ON stars.person_id = people.id
    WHERE name = 'Jennifer Lawrence')
ORDER BY movie_id;


