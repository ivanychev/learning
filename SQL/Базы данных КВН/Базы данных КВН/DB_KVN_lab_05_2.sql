DROP VIEW team_count;
DROP VIEW finalists;
DROP VIEW teams_from_finals;

GO
CREATE VIEW team_count (city_id, [count]) AS
	SELECT city_id,
		COUNT(team_id)
		FROM TEAM
		GROUP BY city_id;
GO
--SELECT * FROM team_count;

GO
CREATE VIEW finalists (city_id, fin_count) AS 
	SELECT TEAM.city_id,
		COUNT(DISTINCT GAME.game_id)
		FROM GAME, TEAM, MARKS
		WHERE game_stage='final'
			AND MARKS.game_id = GAME.game_id
			AND MARKS.team_id=TEAM.team_id
			AND DATEDIFF(YY, [date], GETDATE()) <= 10
		GROUP BY TEAM.city_id;
GO
--SELECT * FROM finalists;

GO
CREATE VIEW teams_from_finals (city_name, teams_number, wins_in_final) AS
	SELECT DISTINCT CITY.city_name,
		CASE WHEN CITY.city_id NOT IN (SELECT city_id FROM team_count) THEN 0
			ELSE (SELECT [count] FROM team_count WHERE team_count.city_id=CITY.city_id) END,
		CASE WHEN CITY.city_id NOT IN (SELECT city_id FROM finalists) THEN 0
			ELSE (SELECT fin_count FROM finalists WHERE CITY.city_id = finalists.city_id) END
	FROM CITY;
GO
SELECT * FROM teams_from_finals;