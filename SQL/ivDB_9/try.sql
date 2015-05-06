select distinct team.name
from team, marks, game
where team.team_id = marks.team_id
and marks.game_id = game.game_id
and year(getdate()) - year(game.game_date) <= 5


-- This team has played earlier than 5 years ago

select distinct game.game_id, game_date
from team, marks, game
where team.team_id = marks.team_id
and marks.game_id = game.game_id
and team.name like '%Uventus%'
order by game_date desc

select distinct team.name
from team, marks, game
where team.team_id = marks.team_id
and marks.game_id = game.game_id
and game.game_id = 20

select * from team

delete from game 
where game_id = 8


-- All teams will be removed
delete from game 
where game_id = 2

-- No teams will be removed
delete from game
where year(getdate()) - year(game_date) <= 5

--
delete from game
where year(getdate()) - year(game_date) > 5

select * from game
order by game_date desc
select * from team
