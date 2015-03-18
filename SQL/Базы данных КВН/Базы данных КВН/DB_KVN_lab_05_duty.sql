DROP VIEW table1;
go
CREATE VIEW table1 (city, univ) AS
	((SELECT city.city_name as cityn, city_id
			from city) as t1
			join
		(select university_name as univn, city_id
		from university) as t2
		ON t1.city_id = t2.city_id);
GO
SELECT * FROM table1;

UPDATE table1
	SET city = 'Москва'
	WHERE city = 'Moscow';


UPDATE table1
	SET city = 'Moscow'
	WHERE city = 'Москва';