DROP VIEW copy_league;
GO
CREATE VIEW copy_league AS
	SELECT *
		FROM LEAGUE;
GO
SELECT *
FROM copy_league;
GO
INSERT INTO copy_league (league_name) VALUES ('1_LIGA');
SELECT * FROM copy_league;
SELECT * FROM LEAGUE;

DELETE FROM LEAGUE
	WHERE league_name='1_LIGA';