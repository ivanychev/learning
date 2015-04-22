use ivKVN


-- #1 check
select * from city
insert into city
	values('Portland')
update city
	set name = 'Montreal'
	where name = 'Portland'

-- #2 check
select * from university -- error occur if executed
select name from university
update university
	set name = 'HSE'
	where name like '%VSE%'

-- #3 check
select * from team
update team				-- error occur if executed
	set name = 'CHP'
	where name = 'ChP'

-- #4 check
select * from team_info

-- #5 check
select city from finalists

update finalists
set city = 'London'
where city = 'Moscow'

select * from source 