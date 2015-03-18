use [25];

SELECT first_name, last_name, university_name
		FROM PEOPLE, UNIVERSITY
		WHERE UNIVERSITY.university_id = PEOPLE.university_id;

GO
use [25];
GO
CREATE VIEW inf ([Имя],[Фамилия],[Университет]) AS
	SELECT first_name, last_name, university_name
		FROM PEOPLE, UNIVERSITY
		WHERE UNIVERSITY.university_id = PEOPLE.university_id;
GO
SELECT * FROM inf;