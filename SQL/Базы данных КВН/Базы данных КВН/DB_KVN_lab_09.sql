DROP TRIGGER Del_Results;

go
CREATE TRIGGER Del_Results
	ON GAME
	FOR DELETE
	AS
		DELETE FROM MARKS
		WHERE game_id IN (
							SELECT DISTINCT MARKS.game_id
								FROM MARKS, GAME
								WHERE [date] >= (YEAR(GETDATE())-2)
								AND GAME.game_id = MARKS.game_id)
		BEGIN
		RAISERROR ('Нельзя удалить результаты двух последних сезонов',9,1);
		ROLLBACK;
		END;

SELECT * FROM MARKS
SELECT * FROM GAME

GO

DROP TRIGGER OLD_GAMES;

GO
CREATE TRIGGER OLD_GAMES
	ON GAME
	INSTEAD OF DELETE AS	
	
			DECLARE @Del TABLE (game_id smallint)
			INSERT INTO @Del
			SELECT deleted.game_id
				FROM deleted
	
	/*	SELECT * FROM deleted;
		SELECT * FROM GAME;

		SELECT TOP 1 DATE FROM deleted ORDER BY date

		SELECT * FROM MARKS WHERE game_id = 721

		SELECT DISTINCT MARKS.team_id
										FROM deleted AS D, MARKS, (
													SELECT MAX(DATE) AS MAXDATE, TEAM.team_id AS ID
														FROM GAME, MARKS, TEAM
														WHERE TEAM.team_id = MARKS.team_id
															AND MARKS.game_id = GAME.game_id 
														GROUP BY TEAM.team_id
													) AS T
										WHERE YEAR(T.MAXDATE) < (YEAR(GETDATE())-5)
											AND D.game_id = MARKS.game_id
											AND MARKS.team_id = T.ID*/

		IF YEAR((SELECT TOP 1 DATE FROM deleted ORDER BY date)) < (YEAR(GETDATE())-5)
		BEGIN
			DELETE FROM TEAM
				WHERE team_id IN (
									SELECT DISTINCT MARKS.team_id
										FROM deleted AS D, MARKS, (
													SELECT MAX(DATE) AS MAXDATE, TEAM.team_id AS ID
														FROM GAME, MARKS, TEAM
														WHERE TEAM.team_id = MARKS.team_id
															AND MARKS.game_id = GAME.game_id 
														GROUP BY TEAM.team_id
													) AS T
										WHERE YEAR(T.MAXDATE) < (YEAR(GETDATE())-5)
											AND D.game_id = MARKS.game_id
											AND MARKS.team_id = T.ID					
									)
			DELETE FROM GAME
				WHERE GAME.game_id in( select d.game_id from @del as d);
		END;
GO

BEGIN TRANSACTION
DELETE FROM GAME
	WHERE game_id = 720;
SELECT * FROM GAME;
SELECT * FROM MARKS;
SELECT * FROM TEAM;
ROLLBACK;




CREATE TABLE LOGIN_DATA 
(
	"user_login" VARCHAR(40),
	"logon_date" DATETIME
);
GO
CREATE TRIGGER LOGON_EVENT
	ON ALL SERVER
	AFTER LOGON AS
	INSERT INTO [25].[dbo].LOGIN_DATA VALUES (ORIGINAL_LOGIN(), GETDATE())