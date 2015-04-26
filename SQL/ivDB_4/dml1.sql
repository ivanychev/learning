use ivKVN

-- ������� ������� �� �������, �� ������������� � ����� ����� @year_interval ���
-- �������� ��������� �� ���������� � ������ � ������� �����

declare @year_interval int = 9;

select distinct team.name
from team, marks, game
where	team.team_id  = marks.team_id
and		marks.game_id = game.game_id
-- and     datediff(year, game.game_date, GETDATE()) <= @year_interval;


delete from team
where team.name not in (
	select team.name
	from  team, marks, game
	where team.team_id  = marks.team_id
	and   marks.game_id = game.game_id
	and	  datediff(year, game.game_date, GETDATE()) <= @year_interval)

select distinct team.name
from team, marks, game
where	team.team_id  = marks.team_id
and		marks.game_id = game.game_id
-- and     datediff(year, game.game_date, GETDATE()) <= @year_interval;