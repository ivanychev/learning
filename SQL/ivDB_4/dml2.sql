
use ivKVN

declare @year int = 2004;


insert into team ( name, uni_id)
	values('First top half', NULL)
insert into team ( name, uni_id)
	values('Second top half', NULL)

declare @first_half_id int = 
(
	select team.team_id 
	from team 
	where team.name = 'First top half'
)

declare @second_half_id int = 
(
	select team.team_id 
	from team 
	where team.name = 'Second top half'
)

declare @successful int = 
(
	select top 1 team.team_id as per_id
	from  team, marks, game
	where team.team_id   = marks.team_id
	and   marks.game_id  = game.game_id
	and   year(game.game_date) = @year
	group by team.team_id
	order by SUM(marks.team_id) desc
);

declare @squad1 table(person_id int, team_id int, role_id int, season_id int, league_id int)
declare @squad2 table(person_id int, team_id int, role_id int, season_id int, league_id int)

insert into @squad1
	select distinct top 50 percent roles.person_id, @first_half_id, 1, 4, 1
	from roles, season
	where roles.team_id = @successful
	and   year(season.begin_date) = @year
	and   roles.season_id = season.season_id
	order by roles.person_id asc

insert into @squad2
	select distinct roles.person_id, @second_half_id, 1, 4, 1
	from roles, season
	where roles.team_id = @successful
	and   year(season.begin_date) = @year
	and   roles.season_id = season.season_id
	and   roles.person_id not in (select person_id from @squad1)

insert into roles(person_id, team_id, role_id, season_id, league_id)
	select * from @squad1

insert into roles(person_id, team_id, role_id, season_id, league_id)
	select * from @squad2
