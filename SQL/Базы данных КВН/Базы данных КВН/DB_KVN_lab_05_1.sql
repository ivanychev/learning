DROP VIEW success;
GO
CREATE VIEW success (team_name, sum_marks) AS
	SELECT TOP 1 team_name, SUM(marks)
		FROM TEAM, MARKS, CITY
		WHERE (MARKS.team_id=TEAM.team_id)
			AND (TEAM.city_id=CITY.city_id)
			AND (city_name='Moscow')
		GROUP BY team_name
		ORDER BY SUM(marks) desc;
GO
SELECT * FROM success;