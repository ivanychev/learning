-- Город, количество команд из этого города, количество побед в играх в названии которых 
-- имеется слово 'финал' за последние десять лет. 

-- get_stage() function need to be defined

-- VIEW

use ivKVN

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

drop view finalists
go

create view finalists(city, amount/*, wins*/)
as
select city.name, tmp.amount
from city join (
	select c.name as  name, a.amount as amount, isnull(b.wins, 0) as wins
	from   (
		select city.city_id as city_id, isnull(count(team.team_id), 0) as amount
		from  city, university, team
		where city.city_id = university.city_id
		and   university.uni_id = team.uni_id
		group by city.city_id
		) as a

	left outer join (
		select city.city_id as city2_id, isnull(count(distinct game.game_id), 0) as wins
		from  city, university, team, marks, game
		where game.name like '%final%'
	 	and   city.city_id = university.city_id
	 	and   university.uni_id = team.uni_id
	 	and   team.team_id = marks.team_id
	 	and   marks.game_id = game.game_id
	 	and   dbo.get_stage(team.team_id, game.game_id) = 1
		group by city.city_id
		) as b
	on a.city_id = b.city2_id

	inner join (
		select city.name as name, city.city_id as city3_id
		from   city
		) as c
	on a.city_id = c.city3_id ) as tmp on tmp.name =city.name
where tmp.amount > 2
go

select * from finalists




-- query
select * from university






	-- on select city.name, count(*)
	-- from ( 
	-- 	select city.city_id, team.team_id
	-- 	from  city, university, team, marks, game
	-- 	where game.name like '%final%'
	-- 	and   city.city_id = university.city_id
	-- 	and   university.uni_id = team.uni_id
	-- 	and   team.team_id = role.team_id
	-- 	and   marks.game_id = game.game_id
	-- 	and   get_stage(team.team_id, game.game_id) = 1