-- Команда, лига, дата, игра, место. 

drop function dbo.get_stage
go

create function dbo.get_stage(@team_id int, @game_id int)
returns int
as begin

declare @stage int;
declare @team_score int;
declare @results table 
(
	team_id int,
	sum_points int
);

insert into @results (team_id, sum_points)
	select team.team_id as cur_team, SUM(marks.score) as sum_points
	from team, marks, game
	where team.team_id = marks.team_id
	and   marks.game_id = @game_id
	group by team.team_id;

set @team_score = (select sum_points
from @results
where team_id = @team_id);

if @team_score is null
	return null;

select @stage = count(team_id)
from  @results
where @team_score is not null
and   sum_points > @team_score;

return @stage + 1;
end
go

drop view team_info
go

create view team_info(team, league, date, game, place)
	as select	distinct team.name, 
				league.name, 
				game.game_date, 
				game.name, 
				dbo.get_stage(team.team_id, game.game_id)
	from marks, game, team, league
	where game.game_id = marks.game_id
	and   team.team_id = marks.team_id
	and   league.league_id = game.league_id
go

select *
from team_info
where place = 1
and game like '%final%'

