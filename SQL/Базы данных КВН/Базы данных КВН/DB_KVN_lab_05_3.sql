DROP VIEW tournament;
GO
CREATE VIEW tournament (league, [year], games_count, teams_count) AS
	SELECT league_name,
		YEAR(date),
		COUNT(DISTINCT GAME.game_id),
		COUNT(DISTINCT TEAM.team_id)
		FROM GAME, LEAGUE, MARKS, TEAM
		WHERE LEAGUE.league_id=GAME.league_id
			AND GAME.game_id=MARKS.game_id
			AND MARKS.team_id=TEAM.team_id
		GROUP BY YEAR(date), league_name;
GO
SELECT * FROM tournament;