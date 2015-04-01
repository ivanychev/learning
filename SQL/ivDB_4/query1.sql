-- Выбрать наиболее успешную команду из Москвы. 

use ivKVN;

select top 1 team.name
from team, marks, university, city

where team.uni_id = university.uni_id
and   university.city_id = city.city_id
and   city.name = 'Moscow'
and   team.team_id = marks.team_id
group by team.team_id, team.name
order by AVG(marks.score) desc;
