use ivKVN
go

--	Trigger is invoked at the attempt of deleting GAME arrows
--
--	It is aimed at choosing teams, which are participants of deleting games and
--	which last game was 5 years ago
--	Choosed teams will be deleted
--	Game results from table MARKS will be deleted on cascade (automatically)

drop trigger outdate_deleter
go

create trigger outdate_deleter
on game 
instead of delete
as
--	can't use FOR because GAME and TEAM tables are linked with arrows from MARK
declare @temp_del table (game_id int, game_date datetime2)
insert into @temp_del
	select game_id, game_date
	from deleted

delete from @temp_del
where year(getdate()) - year(game_date) <= 5

declare @team_del table (team_id int, name varchar(1000))

insert into @team_del
select distinct team.team_id cur_team, team.name
from team, marks, @temp_del
where [@temp_del].game_id = marks.game_id
and	  marks.team_id = team.team_id

declare @actual_teams table (team_id int)

insert into @actual_teams
select distinct team.team_id
from team, marks, game
where team.team_id = marks.team_id
and   marks.game_id = game.game_id
and   year(getdate()) - year(game.game_date) <= 5

delete from @team_del
where team_id in (select team_id from @actual_teams)

-- Printing table of deleating teams
select name 'Deleated teams'
from @team_del

delete from marks
where game_id in (select game_id from deleted)
or	  team_id in (select team_id from @team_del)

delete from game
where game.game_id in (select game_id from deleted)

delete from team
where team.team_id in (select team_id from @team_del)


go




