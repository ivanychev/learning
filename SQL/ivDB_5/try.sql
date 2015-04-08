use ivKVN

select	main_stats.uni_id,
		main_stats.team_id,
		main_stats.year,
		main_stats.league_id,
		main_stats.league_name,
		main_stats.score
from 	university,
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

where main_stats.uni_id = university.uni_id
and   main_stats.score  = ( select max(temp_stats.score) 		-- THE SAME
			    from (select  university.uni_id uni_id, 
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
			    where temp_stats.uni_id = university.uni_id)
