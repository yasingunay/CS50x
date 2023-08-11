## Problem
(https://cs50.harvard.edu/x/2023/psets/7/movies/)

## Tips
* I wanted to bring to your attention an issue I encountered while using Check50 in 9.sql.
Upon reviewing the Check50 results, I noticed that an incorrect query was marked as correct, despite producing an output that differs in row count from the expected result. 
The query in question is as follows:

  Incorrect Query :
  SELECT DISTINCT name 
  FROM people 
  JOIN stars ON stars.person_id = people.id 
  JOIN movies ON movies.id = stars.movie_id 
  WHERE year = 2004 
  ORDER BY birth;
  
  The problem with this query lies in its result set, as it generates rows that do not align with the expected output. 
  After further analysis, I have identified the correct query that should be used for this task:
  
  Correct Query:
   SELECT name FROM people 
  WHERE id IN ( 
  	SELECT DISTINCT person_id FROM stars 
  	JOIN movies ON stars.movie_id = movies.id 
  	WHERE movies.year = 2004 ) 
  ORDER BY birth;
  
  This accurate query not only produces the desired outcome but also maintains the expected row count.
  (https://cs50.stackexchange.com/questions/35409/pset7-movies-q9-why-is-my-number-of-rows-generated-different-from-what-the-assi)
