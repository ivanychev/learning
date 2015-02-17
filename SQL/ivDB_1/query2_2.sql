-- Выбрать зимний день, в который был продан товар на максимальную сумму в Нью Йорке

select top 1 SALES_ORDER.order_date, sum(SALES_ORDER.total)
from LOCATION, DEPARTMENT, EMPLOYEE, CUSTOMER, SALES_ORDER
where	LOCATION.location_id = DEPARTMENT.location_id
and		DEPARTMENT.department_id = EMPLOYEE.department_id
and		EMPLOYEE.employee_id = CUSTOMER.salesperson_id
and		CUSTOMER.customer_id = SALES_ORDER.customer_id
and		LOCATION.regional_group = 'NEW YORK'
and		MONTH(SALES_ORDER.order_date) in (12, 1, 2)
group by SALES_ORDER.order_date
order by sum(SALES_ORDER.total) desc;
