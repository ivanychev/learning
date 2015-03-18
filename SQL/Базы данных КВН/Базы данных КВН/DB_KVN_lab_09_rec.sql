DROP TRIGGER OLD_GAMES;

GO

/*“риггер срабатывает на удаление строк из таблицы GAME. ≈го задача - удалить те команды,
которые, во-первых, участвовали в играх, которые мы удале€м из бд, во-вторых, те,
последнее выступление которых было более 5 лет назад. –езультаты удал€емых игр удал€ютс€ автоматически 
(CREATE TABLE MARKS (
	game_id SMALLINT REFERENCES Game(game_id) ON DELETE CASCADE)) */

CREATE TRIGGER OLD_GAMES
	ON GAME
	INSTEAD OF DELETE AS									--«десь € пыталась использовать FOR DELETE AS, поскольку сразу же после удалени€ игры,
			DECLARE @Del TABLE (game_id smallint)			-- удал€ютс€ и ее результаты, а значит, мы не сможем св€зать таблицы TEAM и GAME без таблицы MARKS.
			INSERT INTO @Del								-- ¬место этого, € сначала удал€ю команду, а затем вручную прописываю удаление, на которое и сработал триггер.
			SELECT deleted.game_id
				FROM deleted
	
	

		IF YEAR((SELECT TOP 1 DATE FROM deleted ORDER BY date)) < (YEAR(GETDATE())-5)			-- «десь провер€етс€ условие того, что
		BEGIN																					-- хот€ бы одна из удал€емых игр прошла более п€ти лет назад.
			DELETE FROM TEAM
				WHERE team_id IN (
									SELECT DISTINCT MARKS.team_id									--Ётот селект выбирает команды, которые удовлетвор€ют двум услови€м:
										FROM deleted AS D, MARKS, (
													SELECT MAX(DATE) AS MAXDATE, TEAM.team_id AS ID		
														FROM GAME, MARKS, TEAM
														WHERE TEAM.team_id = MARKS.team_id
															AND MARKS.game_id = GAME.game_id 
														GROUP BY TEAM.team_id
													) AS T
										WHERE YEAR(T.MAXDATE) < (YEAR(GETDATE())-5)						-- 1) ѕоследнее выступление более п€ти лет назад

											AND D.game_id = MARKS.game_id								--\	
																										--->		2)  оманда участвовала в удал€емой игре
											AND MARKS.team_id = T.ID									--/
									)
			DELETE FROM GAME
				WHERE GAME.game_id in( select d.game_id from @del as d);								-- Ќепосредственно удаление строк
		END;
GO


/*¬ 720 игре участвовали 416, 417, 420 и 421 команды. ¬се они не выступали после 2005 года. «начит, все они должны быть удалены.*/

BEGIN TRANSACTION
DELETE FROM GAME
	WHERE game_id = 720;
SELECT * FROM GAME;
SELECT * FROM MARKS;
SELECT * FROM TEAM;
ROLLBACK;

/*¬ 721 игре участвовали команды 407 и 408, но дл€ 408 последнее выступление было больше п€ти лет назад,
 а дл€ 407 была еще игра в 2010. “аким образом, триггер должен удалить 408, а все остальные команды оставить без изменений.*/

BEGIN TRANSACTION
DELETE FROM GAME
	WHERE game_id = 721;
SELECT * FROM GAME;
SELECT * FROM MARKS;
SELECT * FROM TEAM;
ROLLBACK;

/*¬ этих двух играх участвовали 402, 407 и 408 команды. ѕри чем 402 и 407 участвовали в игре 2010 года,
 а 408 не выступает уже более п€ти лет. “риггер удал€ет только 408 команду.*/

BEGIN TRANSACTION
DELETE FROM GAME
	WHERE game_id = 721 OR game_id = 722;
SELECT * FROM GAME;
SELECT * FROM MARKS;
SELECT * FROM TEAM;
ROLLBACK;

BEGIN TRANSACTION
DELETE FROM GAME
	WHERE YEAR(date) < (YEAR(GETDATE())-5);
SELECT * FROM GAME
	WHERE YEAR([date]) < (YEAR(GETDATE()) - 5);
SELECT team_id, game_id FROM MARKS
	WHERE game_id IN (722, 723, 724)
	GROUP BY team_id, game_id;
SELECT * FROM TEAM;
ROLLBACK;