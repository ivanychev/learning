declare @max_date int;
declare @min_date int;

select @max_date = max(employee.hire_date)
from employee

select @min_date = min(employee.hire_date)
from employee

select EMPLOYEE.last_name, EMPLOYEE.salary, EMPLOYEE.hire_date
from EMPLOYEE
where EMPLOYEE.hire_date = @min_date
or	  EMPLOYEE.hire_date = @max_date
order by EMPLOYEE.hire_date desc