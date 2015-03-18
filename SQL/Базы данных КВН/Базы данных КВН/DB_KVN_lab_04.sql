/*
1. Выбрать наиболее успешную команду из Москвы;
*/
SELECT TOP 1 team_name, SUM(marks)
FROM TEAM, MARKS, CITY
WHERE (MARKS.team_id=TEAM.team_id)
AND (TEAM.city_id=CITY.city_id)
AND (city_name='Moscow')
GROUP BY team_name
ORDER BY SUM(marks) desc;

/*
(SELECT SUM(MARKS.marks)/count(*)
FROM MARKS
GROUP BY game_id) 

select sum(marks)
FROM MARKS
WHERE team_id='410'
*/

/*SELECT distinct team.team_name, count(*)/(SELECT COUNT(comp_id)
													FROM MARKS)
FROM TEAM, MARKS, GAME
WHERE TEAM.team_id=MARKS.team_id
AND MARKS.game_id=GAME.game_id
AND game_name='Letniy kubok'
GROUP BY team_name, marks.comp_id, marks.game_id*/


/*
DECLARE @T TABLE (team_name VARCHAR(20), summa INT)
INSERT INTO @T 
SELECT team_name, sum(marks) as summa
FROM team, marks,game
WHERE team.team_id=marks.team_id
and GAME.game_id = marks.game_id
and game.game_name='Letniy kubok'
GROUP BY team_name
select * from @T


select *
from (

select team_name, count(*) as amount
from
(select distinct MARKS.game_id, team_name
from marks,TEAM, GAME
where TEAM.team_id=MARKS.team_id 
AND game.game_name='Letniy kubok'
AND marks.game_id = GAME.game_id) as t
group by team_name
) as колво inner join 

(

select t1.team_name, count(*) as a
FROM
@T AS t1, @T as t2
WHERE t1.summa <= t2.summa --and t1.team_name != t2.team_name
GROUP BY t1.team_name
/*order by a*/) as места
on колво.team_name = места.team_name
*/


/*
2. Определить команду, которая лучше всех сыграла на "Летнем кубке" (в вмысле соотношения количество игр/место);
*/
DECLARE @T TABLE (team_name VARCHAR(20), summa INT)
INSERT INTO @T 
SELECT team_name, sum(marks) as summa
FROM team, marks,game
WHERE team.team_id=marks.team_id
and GAME.game_id = marks.game_id
and game.game_name='Letniy kubok'
GROUP BY team_name

SELECT TOP 1 T.team_name, summa/amount AS [Коэффициент успешности]
from @T as T  inner join
(select team_name, count(*) as amount
from
(select distinct MARKS.game_id, team_name
from marks,TEAM, GAME
where TEAM.team_id=MARKS.team_id 
AND game.game_name='Letniy kubok'
AND marks.game_id = GAME.game_id) as t
group by team_name
) as колво
on T.team_name = колво.team_name
ORDER BY summa/amount DESC;


/*
SELECT team_name, ISNULL(last_date, GETDATE())
FROM TEAM, PLAYER
WHERE ISNULL(last_date, GETDATE())=(SELECT MAX( ISNULL(last_date, GETDATE()))
				FROM PLAYER, TEAM
				WHERE )
	AND TEAM.team_id=PLAYER.team_id
ORDER BY ISNULL(last_date, GETDATE())
*/

/*
3. Вывести названия команд, которые не играют уже более 5 лет;
*/

SELECT DISTINCT team_name
FROM TEAM, MARKS, GAME,
(SELECT MAX([date]) AS A, team_id
					FROM GAME, MARKS
					WHERE GAME.game_id=MARKS.game_id
					GROUP BY MARKS.team_id) AS LAST_DATES
WHERE TEAM.team_id=MARKS.team_id
AND MARKS.game_id=GAME.game_id
AND (DATEDIFF(YY, LAST_DATES.A, GETDATE()) > 5)
AND MARKS.team_id=LAST_DATES.team_id;

/*
DECLARE @A TABLE (team_id SMALLINT, team_name VARCHAR(20), summa NUMERIC(1,0), [date] datetime 
*/

/*
4. Определить команды, которые сыграли в этом сезоне хуже, чем в прошлом.
*/

SELECT team_name, t1.year, t1.summa, t2.year, t2.summa
FROM (SELECT  team_id, SUM(marks) as summa, YEAR(GAME.date) as [year]
		FROM MARKS, GAME
		WHERE MARKS.game_id=GAME.game_id
		AND YEAR(GAME.date)='2004'--YEAR(GETDATE())
		GROUP BY team_id, YEAR(GAME.date)) t1,
	(SELECT  team_id, SUM(marks) as summa, YEAR(GAME.date) as [year]
		FROM MARKS, GAME
		WHERE MARKS.game_id=GAME.game_id
		AND YEAR(GAME.date)='2005'--YEAR(GETDATE())
		GROUP BY team_id, YEAR(GAME.date)) t2,
	TEAM
	WHERE t1.team_id=t2.team_id
	AND t1.summa > t2.summa
	AND TEAM.team_id=t1.team_id;


/*
Изменения таблицы
*/

delete from city
	where city_name = 'Jurmala';

delete from PEOPLE
	where last_name = 'Gusman';

alter table game drop constraint FK__GAME__league_id__1CFC3D38;
alter table game add constraint FK__GAME__league_id__1CFC3D38
foreign key (league_id)
references league(league_id) on delete no action;

delete from league
	where league_name='Vysshaya liga';

update TEAM
	set team_name =  'Уральские пельмени'
	where team_name = 'Uralskie pelmeni';

select * from team

/*Разделить на две команды самую успешную команду в прошлом сезоне пополам, отсортировав фамилии по алфавиту*/



insert into TEAM values('Uralskie pelmeni 2',104);
insert into TEAM values('Uralskie pelmeni 1',104);

WITH T (Per_ID)
(SELECT A.Per_ID	FROM
									(SELECT DISTINCT TOP 50 PERCENT player.person_id AS Per_ID, last_name
										FROM PEOPLE, PLAYER, TEAM, GAME, MARKS
										WHERE PEOPLE.person_id=PLAYER.person_id
										AND PLAYER.team_id=TEAM.team_id
										AND YEAR(GAME.[date])=2004
										AND GAME.game_id=MARKS.game_id
										AND MARKS.team_id=TEAM.team_id
										AND team_name=(SELECT TOP 1 team_name
																FROM TEAM, MARKS
																WHERE MARKS.team_id=TEAM.team_id
																GROUP BY team_name
																ORDER BY SUM(marks) DESC) 
										ORDER BY last_name) AS A);
										

UPDATE PLAYER
	SET team_id=422
	WHERE person_id = T.Per_ID

		
		
		
		/*AND TEAM.team_id=PLAYER.team_id
		AND TEAM.team_name='Uralskie pelmeni 2'




insert into player


SELECT * FROM PLAYER

update PLAYER
set team_id=PLAYER.team_id+1
WHERE PLAYER.team_id=(SELECT TEAM.team_id
							FROM TEAM
							WHERE team_name = 'Uralskie pelmeni 2')