use ivKVN

declare @desired_game int = 5;

select marks.game_id, marks.score, person.first_name, person.last_name
from marks, person
where marks.game_id = @desired_game
and   marks.jury_id = person.person_id


update marks
	set marks.score += case when person.sex = 'm' then 1 else 2 end
	from
		marks
	inner join
		person
	on
	(
		marks.jury_id = person.person_id
		and
		marks.game_id = @desired_game
		and
		person.sex = 'm'
	)

/*
update marks
	set marks.score += 2
	from
		marks
	inner join
		person
	on
	(
		marks.jury_id = person.person_id
		and
		marks.game_id = @desired_game
		and
		person.sex = 'f'
	)
*/


select marks.game_id, marks.score, person.first_name, person.last_name
from marks, person
where marks.game_id = @desired_game
and   marks.jury_id = person.person_id