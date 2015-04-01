-- Определить команду, которая лучше(соотношения количество игр/место) всех играла на "Летнем кубке". 

-- лучшим считается минимальное соотношение место / количество игр

drop function dbo.get_stage;
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



select top 1 team.name, AVG(CAST(dbo.get_stage(team.team_id, game.game_id) as float))
from game, team, marks
where game.name = 'Letniy kubok'
and   game.game_id = marks.game_id
and   team.team_id = marks.team_id
group by team.team_id, team.name
order by AVG(CAST(dbo.get_stage(team.team_id, game.game_id) as float)) asc;


/*
select team.team_id, SUM(marks.score), game.game_id, dbo.get_stage(team.team_id, game.game_id)
from game, team, marks
where game.name = 'Letniy kubok'
and   game.game_id = marks.game_id
and   team.team_id = marks.team_id
group by team.team_id, game.game_id
*/


-- select distinct team.team_id
-- from game, team, marks
-- where game.game_id = marks.game_id
-- and   team.team_id = marks.team_id
-- and   game.game_id = 5;
-- go

--print cast(dbo.get_stage(2, 5) as nvarchar(50))
--print cast(dbo.get_stage(5, 5) as nvarchar(50))
--print cast(dbo.get_stage(6, 5) as nvarchar(50))
--print cast(dbo.get_stage(7, 5) as nvarchar(50))

