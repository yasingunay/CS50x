--In 3.sql, write a SQL query to list the titles of all movies with a release date on or after 2018, in alphabetical order.
--Your query should output a table with a single column for the title of each movie.


SELECT title FROM movies WHERE year >= 2018 ORDER BY title;