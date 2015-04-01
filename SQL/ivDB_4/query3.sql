-- Вывести названия команд, которые не играют более 5 лет.


select team.name
from team
where team.name not in (
select distinct team.name
from  team, marks, game
where team.team_id  = marks.team_id
and   marks.game_id = game.game_id
and	  datediff(year, game.game_date, GETDATE()) <= 5);