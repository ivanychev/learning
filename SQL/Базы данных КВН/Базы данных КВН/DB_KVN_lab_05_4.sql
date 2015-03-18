DROP VIEW game_information;
GO
CREATE VIEW game_information (team, league, [date], city) AS
	SELECT TEAM.team_name, LEAGUE.league_name, CONVERT(VARCHAR, GAME.date, 105), city_name
		FROM TEAM, LEAGUE, GAME, MARKS, CITY
		WHERE TEAM.team_id=MARKS.team_id
			AND LEAGUE.league_id=GAME.league_id
			AND GAME.game_id=MARKS.game_id
			AND CITY.city_id=GAME.city_id
		GROUP BY team_name,  league_name, GAME.game_id, [date], city_name;
GO
SELECT *
	FROM game_information;

 game_information
	WHERE city = 'Moscow'


/*
DECLARE @T TABLE (team_name VARCHAR(20), summa INT)
INSERT INTO @T 
SELECT team_name, sum(marks) as summa
FROM team, marks, GAME
WHERE team.team_id=MARKS.team_id
AND GAME.game_id=MARKS.game_id
GROUP BY team_name, GAME.game_id;

select места.team_name, a
from 
(select team_name
from
(select distinct team_name
from marks,TEAM, GAME
where TEAM.team_id=MARKS.team_id 
AND marks.game_id = GAME.game_id) as t
group by team_name) as колво
inner join
(select t1.team_name, count(*) as a
FROM
@T AS t1, @T as t2, GAME
WHERE t1.summa <= t2.summa --and t1.team_name != t2.team_name
GROUP BY t1.team_name, game.game_id
--order by a
) as места
on колво.team_name = места.team_name
*/