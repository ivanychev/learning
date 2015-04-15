-- ВУЗ, количество команд из этого ВУЗа, лига и год, когда команда из этого вуза достигла наибольшего успеха.
use ivKVN
go

drop view university_stats
go
drop view tmmp
create view tmmp as 
with main_stats as
	(select  university.uni_id uni_id, 				-- THE SAME
			team.team_id team_id, 
			year(game.game_date) year, 
			league.league_id league_id, 
			league.name league_name, 
			sum(marks.score) score
		from 	university,
			team,
			marks,
			game,
			league
		where 	university.uni_id = team.uni_id
		and 	league.league_id = game.league_id
		and   	game.game_id 	 = marks.game_id
		and  	team.team_id  	 = marks.team_id
		group by university.uni_id, 
			team.team_id, 
			year(game.game_date), 
			league.league_id, 
			league.name
			)
select *
from main_stats 

select * from tmmp
go

create view university_stats(name, amount, league, year)
	as select distinct a.name, b.amount, c.league, c.year
	from (
		select 	university.uni_id uni_id, 
			university.name name
		from university
		) a
-- =========================================================================================
	left outer join (
		select 	university.uni_id uni_id2, 
			count(team.team_id) amount
		from   	university, 
			team
		where  university.uni_id = team.uni_id
		group by university.uni_id
		) b
	on a.uni_id = b.uni_id2
-- =========================================================================================
	left outer join (
	select	main_stats.uni_id uni_id,
		main_stats.team_id team_id,
		main_stats.year year,
		main_stats.league_id league_id,
		main_stats.league_name league,
		main_stats.score score
	from 	university,
	-----------------------------------------------------------------
		(select  university.uni_id uni_id, 				-- THE SAME
			team.team_id team_id, 
			year(game.game_date) year, 
			league.league_id league_id, 
			league.name league_name, 
			sum(marks.score) score
		from 	university,
			team,
			marks,
			game,
			league
		where 	university.uni_id = team.uni_id
		and 	league.league_id = game.league_id
		and   	game.game_id 	 = marks.game_id
		and  	team.team_id  	 = marks.team_id
		group by university.uni_id, 
			team.team_id, 
			year(game.game_date), 
			league.league_id, 
			league.name) main_stats
-----------------------------------------------------------------------
	where    main_stats.score  = ( 				
						select max(main_stats.score) 		
				    	from main_stats
/*						(
-----------------------------------------------------------------------					
				    		select  university.uni_id uni_id, -- THE SAME
							team.team_id team_id, 
							year(game.game_date) year, 
							league.league_id league_id, 
							league.name league_name, 
							sum(marks.score) score
						from 	university,
							team,
							marks,
							game,
							league
						where 	university.uni_id = team.uni_id
						and 	league.league_id = game.league_id
						and   	game.game_id 	 = marks.game_id
						and  	team.team_id  	 = marks.team_id
						group by university.uni_id, 
							team.team_id, 
							year(game.game_date), 
							league.league_id, 
							league.name) temp_stats
*/
--------------------------------------------------------------------------
			    		where main_stats.uni_id = university.uni_id
			    ) 
		and main_stats.uni_id = university.uni_id
	) c
	on a.uni_id = c.uni_id
	go


	select *
	from university_stats
	where amount is NULL

	update univercity_stats
	set year = 'BSU'
	where name = 'BGU'

	select * 
	from univercity_stats


 