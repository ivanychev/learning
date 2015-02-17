-- ������� ��������, � ������������� �������������.
-- ������� ������ ����, � ������� ��� ������ ����� �� ������������ ����� � ��� �����
-- ������� ����� ����������� ����� ������ - ������ ����������� ���������� ����������/����� ������
-- ������� ������� �������� ���������� ��������, �������� ������������.

declare @max_commission INT;

 
set @max_commission = (select max(commission)
from EMPLOYEE);

select first_name, last_name, commission
from EMPLOYEE
where	commission is not null
and		commission = @max_commission;



-- select first_name, last_name, commission
--    from employee
--    where	commission is not null
--    and		commission = 
-- 			(select max(commission)
-- 				from EMPLOYEE;);