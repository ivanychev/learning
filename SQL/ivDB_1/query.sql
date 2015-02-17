-- Выбрать продавца, с максимальными комиссионными.
-- Выбрать зимний день, в который был продан товар на максимальную сумму в Нью Йорке
-- Выбрать самый эффективный отдел продаж - лучшее соотношение количество работников/сумма продаж
-- Выбрать среднюю зарплату сотрудника компании, учитывая комиссионные.

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