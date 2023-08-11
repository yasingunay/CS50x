--In 6.sql, write a SQL query to determine the average rating of all movies released in 2012.
--Your query should output a table with a single column and a single row (not counting the header) containing the average rating.

SELECT title, rating
FROM movies
JOIN ratings on movies.id = ratings.movie_id
WHERE year = 2010
AND rating IS NOT NULL
ORDER BY	rating DESC, title ASC;