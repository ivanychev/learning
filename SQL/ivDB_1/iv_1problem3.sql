-- Для каждого сотрудника вывести количество подчиненных


select EMPLOYEE.employee_id
from EMPLOYEE,
	(
		with rec
		as
		(

		)
		select EMPLOYEE.employee_id, EMPLOYEE.employee_id
		from EMPLOYEE
	)


/*
with 
rec
as (

)
select *
*/