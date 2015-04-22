use ivKVN

select CURRENT_USER
select SCHEMA_NAME()

go

alter role tester
	drop member test
drop   role tester

drop   user test
drop   login test1

-- granted public by default
create login test1
	with password = 'password'
go

-- creating user "test" with "guest" schema by default
create user test
	for login test1
	with default_schema = guest

-- granting SELECT, INSERT, UPDATE  #1
grant SELECT, INSERT, UPDATE on city to test

-- granting SELECT, UPDATE to specific columns  #2
grant select(name) on university to test
grant update(name) on university to test

-- granting only SELECT to a table #3
grant select on team to test

-- granting SELECT privelege to "TEAM_INFO" view  #4
grant select on team_info to test

-- creating database-level role
create role tester

-- set the user to that role
alter role tester 
	add member test

-- granting update priveleges to "FINALISTS" view  #5
grant update on finalists(city) to tester
grant select on finalists(city) to tester

deny   select on source to test
revoke select on source to test
grant select on source to test

select * from sys.database_role_members
select * from sys.database_principals