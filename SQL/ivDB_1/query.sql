


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