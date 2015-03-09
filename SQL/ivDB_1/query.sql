

with rec_table(id)
as (
		select	EMPLOYEE.job_id
		from	EMPLOYEE
		where	employee.manager_id in 
						(select id
						 from rec_table)
	)
select	EMPLOYEE.job_id
from	EMPLOYEE
where	employee.manager_id is null
	




/*
select JOB.job_id, 'CHICAGO:', isnull(chicago.quant, 0), 'BOSTON:', isnull(boston.quant, 0)
from
	JOB
	full join
	(
		(
		select job.job_id job_id, count(*) quant
		from JOB, EMPLOYEE, DEPARTMENT, LOCATION
		where	JOB.job_id = EMPLOYEE.job_id
		and		EMPLOYEE.department_id = DEPARTMENT.department_id
		and		DEPARTMENT.location_id = LOCATION.location_id
		and		LOCATION.regional_group = 'CHICAGO'
		group by job.job_id) as chicago

	full join

		(
		select job.job_id job_id, count(*) quant
		from JOB, EMPLOYEE, DEPARTMENT, LOCATION
		where	JOB.job_id = EMPLOYEE.job_id
		and		EMPLOYEE.department_id = DEPARTMENT.department_id
		and		DEPARTMENT.location_id = LOCATION.location_id
		and		LOCATION.regional_group = 'BOSTON'
		group by job.job_id) as boston
	
		on chicago.job_id = boston.job_id
	)
	on JOB.job_id = chicago.job_id
	or JOB.job_id = boston.job_id;
*/

/*
select job.job_id job_id, count(*) quant
	from JOB, EMPLOYEE, DEPARTMENT, LOCATION
	where	JOB.job_id = EMPLOYEE.job_id
	and		EMPLOYEE.department_id = DEPARTMENT.department_id
	and		DEPARTMENT.location_id = LOCATION.location_id
	and		LOCATION.regional_group = 'BOSTON'
	group by job.job_id
*/






/*
	union

	select job.job_id job_id, 0 quant
	from	JOB
	where	JOB.job_id not in 
			(	select JOB.job_id
				from JOB, EMPLOYEE, CUSTOMER, DEPARTMENT, LOCATION
				where	JOB.job_id = EMPLOYEE.job_id
				and		EMPLOYEE.department_id = DEPARTMENT.department_id
				and		DEPARTMENT.location_id = LOCATION.location_id
				and		LOCATION.regional_group = 'BOSTON')
*/

-- -- 38
--
-- select year(sales_order.ship_date), sum(item.total)
-- from item, product, sales_order
-- where 	product.description = 'DUNK BASKETBALL INDOOR'
-- and 	product.product_id = item.product_id
-- and 	item.order_id = sales_order.order_id

-- group by year(sales_order.ship_date)

-- -- 32
--
-- select EMPLOYEE.last_name
-- from EMPLOYEE
-- where employee.employee_id in
-- (	select employee.manager_id
-- 	from employee
-- 	where employee.employee_id in 
-- 	(	select employee.employee_id
-- 		from EMPLOYEE
-- 		where EMPLOYEE.employee_id in ( select employee.manager_id
-- 										from EMPLOYEE)
-- 	)
-- )
-- and manager_id is not NULL

-- -- 31
--
-- select dep_id, d_quant/quant, d_sal/sal
-- from (	select count(*) as quant, sum(salary) as sal
-- 		from EMPLOYEE) temp1,
-- 	 (  select department_id as dep_id, count(*) as d_quant, sum(salary) as d_sal
-- 		from EMPLOYEE
-- 		group by department_id) temp2

-- -- 30 
--
-- select EMPLOYEE.first_name, EMPLOYEE.middle_initial, EMPLOYEE.last_name
-- from employee
-- where last_name in
-- 	(select	EMPLOYEE.last_name
-- 	from	EMPLOYEE
-- 	group by EMPLOYEE.last_name
-- 	having count(EMPLOYEE.last_name) > 1)
					

-- -- 29
--
-- select EMPLOYEE.last_name, EMPLOYEE.salary - (select AVG(EMPLOYEE.salary)
-- 				 from EMPLOYEE
-- 				 where EMPLOYEE.job_id = 670)
-- from   EMPLOYEE
-- where  EMPLOYEE.job_id = 670