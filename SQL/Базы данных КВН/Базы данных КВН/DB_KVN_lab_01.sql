select customer.name
from customer, employee
where customer.salesperson_id = employee.employee_id
AND employee.first_name = 'MARY'

select first_name, employee_id
from employee

SELECT salesperson_id
from customer

SELECT first_name,
case
when FIRST_name = 'MARY' then 'chikaboom'
else 'ok' end
from employee	

select *
from department inner join
	employee on
	department.department_id = employee.department_id

select *
from department, employee
where department.department_id = employee.department_id

select name
from department

select *
from department right join
	employee on
	department.department_id = employee.department_id





/*  Лабораторная №1*/

/*  1)	Выбрать продавца с максимальными комиссионными.*/

SELECT (First_Name + ' ' + Last_Name) as [Продавец]
	FROM EMPLOYEE
	WHERE Commission = 
						(SELECT MAX(Commission)
							FROM EMPLOYEE)

/* SELECT TOP 1 First_Name
FROM EMPLOYEE
ORDER BY Commission DESC */


/*  2)	Выбрать зимний день, в который был продан
		товар на максимальную сумму в Нью Йорке.*/


SELECT CONVERT(VARCHAR(10), order_date, 104)
	FROM Sales_order, CUSTOMER, EMPLOYEE, DEPARTMENT, LOCATION
	WHERE MONTH(Order_Date) in (1,2,12)
	AND SALES_ORDER.customer_id = CUSTOMER.customer_id
	AND CUSTOMER.salesperson_id = EMPLOYEE.employee_id
	AND EMPLOYEE.department_id = DEPARTMENT.department_id
	AND department.location_id = location.location_id
	AND LOCATION.regional_group = 'NEW YORK'
	AND SALES_ORDER.total =
						 (SELECT TOP 1 SUM(SALES_ORDER.total) AS mxx
							FROM SALES_ORDER, CUSTOMER, EMPLOYEE, DEPARTMENT, LOCATION
							WHERE SALES_ORDER.customer_id = CUSTOMER.customer_id
							AND CUSTOMER.salesperson_id = EMPLOYEE.employee_id
							AND EMPLOYEE.department_id = DEPARTMENT.department_id
							AND department.location_id = location.location_id
							AND LOCATION.regional_group = 'NEW YORK'
							GROUP BY order_date
							ORDER BY mxx DESC)


/*  3)	Выбрать самый эффективный отдел продаж - лучшее
		соотношение количество работников/сумма продаж.*/

SELECT TOP 1 table1.department_id
	FROM 
		(SELECT EMPLOYEE.department_id, COUNT(EMPLOYEE.employee_id) AS amount
			FROM EMPLOYEE
			GROUP BY EMPLOYEE.department_id) AS table1
			INNER JOIN
			DEPARTMENT
			ON DEPARTMENT.department_id = table1.department_id
			INNER JOIN
			(SELECT EMPLOYEE.department_id, SUM(SALES_ORDER.total) AS SUMma
				FROM SALES_ORDER, CUSTOMER, EMPLOYEE
				WHERE SALES_ORDER.customer_id = CUSTOMER.customer_id
				AND CUSTOMER.salesperson_id = EMPLOYEE.employee_id
				GROUP BY employee.department_id) AS table2 
				ON table1.department_id = table2.department_id
	WHERE department.name = 'SALES'
	ORDER BY (table2.SUMma/table1.amount) DESC


/*	4)	Выбрать среднюю зарплату сотрудника компании,
		учитывая комиссионные.*/

/*SELECT TOP 1 Sal_plus_Com
	FROM (SELECT TOP 50 PERCENT (EMPLOYEE.Salary+ISNULL(EMPLOYEE.commission, 0)) AS Sal_plus_Com
	FROM EMPLOYEE
	ORDER BY Sal_plus_Com) AS least
	ORDER BY Sal_plus_Com DESC*/


select ((SUM(Salary)+SUM(commission))/COUNT(employee_id))
from EMPLOYEE

select *
from EMPLOYEE

select * from EMPLOYEE 
where commission is not null

SELECT COUNT(EMPLOYEE.employee_id)
FROM EMPLOYEE


SELECT COUNT(T1.employee_id)
FROM EMPLOYEE AS t1, EMPLOYEE AS T2
WHERE T1.employee_id = T2.manager_id

WHERE isnull(manager_id, -1) = -1

SELECT EMPLOYEE.employee_id
FROM  EMPLOYEE, (SELECT * FROM EMPLOYEE) AS T1, (SELECT * FROM EMPLOYEE) AS T2
WHERE T1.employee_id = T2.manager_id