-- Выбрать среднюю зарплату сотрудника компании, учитывая комиссионные.
use King_Corp

select	DEPARTMENT.department_id, 
		(sum(distinct EMPLOYEE.salary) + sum(all EMPLOYEE.commission * SALES_ORDER.total))/count(distinct EMPLOYEE.employee_id) as average
from	DEPARTMENT, EMPLOYEE, CUSTOMER, SALES_ORDER
where	DEPARTMENT.department_id = EMPLOYEE.department_id
and		EMPLOYEE.employee_id = CUSTOMER.salesperson_id
and		CUSTOMER.customer_id = SALES_ORDER.customer_id
group by DEPARTMENT.department_id
order by average desc;