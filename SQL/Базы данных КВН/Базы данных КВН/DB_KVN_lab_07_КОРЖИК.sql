---
DROP LOGIN viewer;
DROP USER viewer;
DROP USER Gusman;
EXEC sp_droplogin Gusman;
---

GO
CREATE LOGIN viewer
	WITH PASSWORD = '' MUST_CHANGE, 
	CHECK_EXPIRATION = ON;
GO
CREATE USER viewer
	FOR LOGIN viewer;

EXEC sp_addlogin Gusman,  'imgod', '25';

CREATE USER Gusman
	FOR LOGIN Gusman;
---



DROP VIEW success;

GO
CREATE VIEW success ([Команда], [Сумма баллов]) AS
	SELECT TOP 100 PERCENT team_name, SUM(marks)
		FROM TEAM, MARKS
		WHERE (MARKS.team_id=TEAM.team_id)
		GROUP BY team_name
		ORDER BY SUM(marks);
GO
---

GRANT SELECT ON success TO viewer;

REVOKE SELECT ON success TO viewer;
---




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
CREATE VIEW teams_from_finals ([Город], [Количество команд], [Побед в финале]) AS
	SELECT DISTINCT CITY.city_name,
		CASE WHEN CITY.city_id NOT IN (SELECT city_id FROM team_count) THEN 0
			ELSE (SELECT [count] FROM team_count WHERE team_count.city_id=CITY.city_id) END,
		CASE WHEN CITY.city_id NOT IN (SELECT city_id FROM finalists) THEN 0
			ELSE (SELECT fin_count FROM finalists WHERE CITY.city_id = finalists.city_id) END
	FROM CITY;
GO
SELECT * FROM teams_from_finals;
---


GRANT SELECT ON teams_from_finals TO viewer;
REVOKE SELECT ON teams_from_finals TO viewer;
---

GRANT select ON MARKS  TO Gusman;
grant delete on marks to Gusman;

DENY UPDATE(CITY_NAME) ON CITY TO Gusman CASCADE  with grant option;

grant create database to Gusman;

информация о пользов, которые подключены к серверу

select * from [25]..sysprocesses  where loginame != 'sa';