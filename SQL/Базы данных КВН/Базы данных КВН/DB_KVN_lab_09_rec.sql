DROP TRIGGER OLD_GAMES;

GO

/*������� ����������� �� �������� ����� �� ������� GAME. ��� ������ - ������� �� �������,
�������, ��-������, ����������� � �����, ������� �� ������� �� ��, ��-������, ��,
��������� ����������� ������� ���� ����� 5 ��� �����. ���������� ��������� ��� ��������� ������������� 
(CREATE TABLE MARKS (
	game_id SMALLINT REFERENCES Game(game_id) ON DELETE CASCADE)) */

CREATE TRIGGER OLD_GAMES
	ON GAME
	INSTEAD OF DELETE AS									--����� � �������� ������������ FOR DELETE AS, ��������� ����� �� ����� �������� ����,
			DECLARE @Del TABLE (game_id smallint)			-- ��������� � �� ����������, � ������, �� �� ������ ������� ������� TEAM � GAME ��� ������� MARKS.
			INSERT INTO @Del								-- ������ �����, � ������� ������ �������, � ����� ������� ���������� ��������, �� ������� � �������� �������.
			SELECT deleted.game_id
				FROM deleted
	
	

		IF YEAR((SELECT TOP 1 DATE FROM deleted ORDER BY date)) < (YEAR(GETDATE())-5)			-- ����� ����������� ������� ����, ���
		BEGIN																					-- ���� �� ���� �� ��������� ��� ������ ����� ���� ��� �����.
			DELETE FROM TEAM
				WHERE team_id IN (
									SELECT DISTINCT MARKS.team_id									--���� ������ �������� �������, ������� ������������� ���� ��������:
										FROM deleted AS D, MARKS, (
													SELECT MAX(DATE) AS MAXDATE, TEAM.team_id AS ID		
														FROM GAME, MARKS, TEAM
														WHERE TEAM.team_id = MARKS.team_id
															AND MARKS.game_id = GAME.game_id 
														GROUP BY TEAM.team_id
													) AS T
										WHERE YEAR(T.MAXDATE) < (YEAR(GETDATE())-5)						-- 1) ��������� ����������� ����� ���� ��� �����

											AND D.game_id = MARKS.game_id								--\	
																										--->		2) ������� ����������� � ��������� ����
											AND MARKS.team_id = T.ID									--/
									)
			DELETE FROM GAME
				WHERE GAME.game_id in( select d.game_id from @del as d);								-- ��������������� �������� �����
		END;
GO


/*� 720 ���� ����������� 416, 417, 420 � 421 �������. ��� ��� �� ��������� ����� 2005 ����. ������, ��� ��� ������ ���� �������.*/

BEGIN TRANSACTION
DELETE FROM GAME
	WHERE game_id = 720;
SELECT * FROM GAME;
SELECT * FROM MARKS;
SELECT * FROM TEAM;
ROLLBACK;

/*� 721 ���� ����������� ������� 407 � 408, �� ��� 408 ��������� ����������� ���� ������ ���� ��� �����,
 � ��� 407 ���� ��� ���� � 2010. ����� �������, ������� ������ ������� 408, � ��� ��������� ������� �������� ��� ���������.*/

BEGIN TRANSACTION
DELETE FROM GAME
	WHERE game_id = 721;
SELECT * FROM GAME;
SELECT * FROM MARKS;
SELECT * FROM TEAM;
ROLLBACK;

/*� ���� ���� ����� ����������� 402, 407 � 408 �������. ��� ��� 402 � 407 ����������� � ���� 2010 ����,
 � 408 �� ��������� ��� ����� ���� ���. ������� ������� ������ 408 �������.*/

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