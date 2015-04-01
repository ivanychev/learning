-- Определить, какие команды играют в этом сезоне хуже, чем в прошлом. 

declare @current_year datetime2 = cast('2005' as datetime2)

declare @previous_year datetime2 = cast(cast((year(@current_year) - 1) as nvarchar(5)) as datetime2);

select outer_.name
from  team outer_
where  
(select sum(marks.score)
from team, marks, game
where team.team_id = outer_.team_id
and	  team.team_id = marks.team_id
and   marks.game_id = game.game_id
and   year(game.game_date) = year(@current_year))
<
-- if one of subqueries returns null, there is no comparison
(select sum(marks.score)
from team, marks, game
where team.team_id = outer_.team_id
and	  team.team_id = marks.team_id
and   marks.game_id = game.game_id
and   year(game.game_date) = year(@previous_year));



