-- Лига, год, количество игр в этом году, количество команд, принявших участие в турнире. 
use ivKVN
go

drop view games
go

create view games (league, year, games_amount, teams_amount)
	as select name, year, participants, games
	from
		(
	select	league.league_id, 
			league.name as name, 
			year(game.game_date) as year, 
			count(distinct marks.team_id) participants, 
			count(distinct game.game_id)  games
	from league, game, marks
	where 
		    league.league_id = game.league_id
	and 	game.game_id 	 = marks.game_id
	group by league.league_id, league.name, year(game.game_date)
		) as temp
go

select * 
from games

select sum(games_amount)
from games
where league like '%liga%'