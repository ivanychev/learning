
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
