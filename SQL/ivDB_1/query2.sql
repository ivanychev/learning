-- Выбрать зимний день, в который был продан товар на максимальную сумму в Нью Йорке

declare @needed_location int;
set @needed_location = (select location_id
						from LOCATION
						where regional_group = 'NEW YORK');
						
declare @needed_departments table (department_id int);
insert @needed_departments
	select department_id
	from DEPARTMENT
	where location_id = @needed_location

declare @needed_salers table (saler_id int);
insert @needed_salers
	select employee_id
	from EMPLOYEE
	where department_id in (select department_id 
							from @needed_departments);

declare @needed_customers table (customers_id int);
insert @needed_customers
	select customer_id
	from CUSTOMER
	where salesperson_id in (select saler_id
							 from @needed_salers)

declare @needed_orders table (order_id int)
insert @needed_orders
	select	order_id
	from	SALES_ORDER
	where	MONTH(ship_date) in (12, 1, 2);
	
declare @max_total int;

select @max_total = max(total)
					from ITEM
					where order_id in (	select order_id
										from @needed_orders);
declare @dates table (ship_date DATETIME)
insert @dates
	select order_date
	from SALES_ORDER
	where	order_id in (	select order_id
							from @needed_orders)
	and		order_id in (	select order_id
							from ITEM
							where total = @max_total)
print cast(@max_total as varchar)
select *
from @dates