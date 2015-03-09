-- Выбрать среднюю зарплату сотрудника компании, учитывая комиссионные.
-- Считаем, что компания работает с 1989 по 1991 и зарплата платится в месяц
-- Так как не знаем, как менялась зарплата у сотрудников в течение трех лет
-- находим среднюю зарплату за ноябрь 1991 (последний месяц с продажами)

declare @month_and_year as datetime;
set @month_and_year = '01-09-1991';
declare @salary_sum int;
declare @employees  int;

select @salary_sum = SUM(salary), @employees = COUNT(employee_id) 
from EMPLOYEE

-- Теперь считаем сумму заработанных комиссий каждого продавца. Каждый за месяц заработал количество * его комиссия
declare @comission_sum int

set @comission_sum = 
(	select sum(saler_comm_table.money)
	from (	
	select sum(employee.commission) as money
			from SALES_ORDER, CUSTOMER, EMPLOYEE
			where	 year( order_date) = year (@month_and_year) 
			and		 month(order_date) = month(@month_and_year)
			and		 CUSTOMER.customer_id = SALES_ORDER.customer_id
			and		 EMPLOYEE.employee_id = customer.salesperson_id
			group by EMPLOYEE.employee_id) saler_comm_table
)

select (isnull(@salary_sum, 0) + isnull(@comission_sum, 0))/@employees