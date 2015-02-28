-- Выбрать самый эффективный отдел продаж - лучшее соотношение количество работников/сумма продаж

select top 1 DEPARTMENT.department_id, DEPARTMENT.name, count(distinct EMPLOYEE.employee_id)/sum(SALES_ORDER.total)
from DEPARTMENT, EMPLOYEE, CUSTOMER, SALES_ORDER
where	DEPARTMENT.department_id = EMPLOYEE.department_id
and		EMPLOYEE.employee_id = CUSTOMER.salesperson_id
and		CUSTOMER.customer_id = SALES_ORDER.customer_id
group by DEPARTMENT.department_id, DEPARTMENT.name
order by sum(SALES_ORDER.total)/count(distinct EMPLOYEE.employee_id) asc;


-- create function year_diff
-- (@start_date DATETIME, @end_date DATETIME)
-- returns int
-- begin
-- 	declare @diff = abs(datepart(year, @start_date) - datepart(year, @end_date));
-- 	select @diff
-- 	case datepart(month, @start_date) - datepart(month, @end_date) 
-- 	when > 0 then return 	@diff + 1;
-- 	else 			@diff;

-- 	select @diff
-- 	case date_part(month, @start_date) - datepart(month, @end_date)
-- 	when = 0 then (
-- 			case datepart(day, @start_date) - datepart(day, @end_date)
-- 			when >= 0 then 	@diff + 1
-- 			else 		@diff)
-- 	else @diff;



	-- case datepart(month, @start_date) - datepart(month, @end_date) 
	-- when = 0
	-- then
	-- 	case datepart(day, @start_date) - datepart(day, @end_date) 
	-- 	when >= 0
	-- 	then
	-- 		return @diff + 1;
	-- return @diff;
	-- end;