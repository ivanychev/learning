use [МояДесятаяЛаба_1]
select * 
into customers 
from northwind..customers

declare @count int
select @count = 10
while @count >= 0
  begin
    insert into customers 
		select * 
		from northwind..customers
    select @count = @count - 1
  end

select * 
into orders 
from northwind..orders

select * 
into orderdetails 
from northwind.."order details"

select * 
into products 
from northwind..products
select @count = 30
while @count >= 0
  begin
    insert into products (productname, supplierid, categoryid, quantityperunit, unitprice, unitsinstock, unitsonorder, reorderlevel, discontinued)
    select productname, supplierid, categoryid, quantityperunit, unitprice, unitsinstock, unitsonorder, reorderlevel, discontinued
    from northwind..products
    select @count = @count - 1
  end