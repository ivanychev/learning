-- Вывести среднюю зарплату с учетом комиссионных за 1990-1991 года

/*
select 
from	EMPLOYEE, CUSTOMER, SALES_ORDER
where	EMPLOYEE.employee_id = CUSTOMER.salesperson_id
and		customer.customer_id = SALES_ORDER.customer_id
and		year(SALES_ORDER.order_date) in (1990, 1991)
*/



select (isnull(temp1.salary_sum, 0) + isnull(temp2.comm_sum / 24, 0))/temp1.employees
from 
	(select SUM(salary) salary_sum, COUNT(employee_id) employees
	from EMPLOYEE) as temp1
 	join
	(select sum(saler_comm_table.money) comm_sum
	from (	
		select sum(employee.commission) as money
		from SALES_ORDER, CUSTOMER, EMPLOYEE
		where	 year( order_date) in (1990, 1991)
		and		 CUSTOMER.customer_id = SALES_ORDER.customer_id
		and		 EMPLOYEE.employee_id = customer.salesperson_id
		group by EMPLOYEE.employee_id) saler_comm_table
	) as temp2
	on 1 = 1;
