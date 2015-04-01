use ivKVN

-- Удаляем команды из таблицы, не участвовавшие в играх более @year_interval лет
-- Каскадно удаляются их результаты и записи в таблице ролей

declare @year_interval int = 9;

select distinct team.name
from team, marks, game
where	team.team_id  = marks.team_id
and		marks.game_id = game.game_id
-- and     datediff(year, game.game_date, GETDATE()) <= @year_interval;


delete from team
where team.name not in (
	select team.name
	from  team, marks, game
	where team.team_id  = marks.team_id
	and   marks.game_id = game.game_id
	and	  datediff(year, game.game_date, GETDATE()) <= @year_interval)

select distinct team.name
from team, marks, game
where	team.team_id  = marks.team_id
and		marks.game_id = game.game_id
-- and     datediff(year, game.game_date, GETDATE()) <= @year_interval;