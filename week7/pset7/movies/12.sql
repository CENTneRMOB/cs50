SELECT jennifer.title as title from (SELECT title FROM people JOIN stars ON people.id = stars.person_id JOIN movies ON stars.movie_id = movies.id WHERE name = 'Bradley Cooper') as bradley JOIN (SELECT title FROM people JOIN stars ON people.id = stars.person_id JOIN movies ON stars.movie_id = movies.id WHERE name = 'Jennifer Lawrence') as jennifer ON bradley.title = jennifer.title;