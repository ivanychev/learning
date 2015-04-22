-- seeing database principals
select * from sys.database_principals

-- seeing server principals
Select * from sys.server_principals

-- Listing the fixed server roles
EXEC sp_helpsrvrole ;

-- Listing fixed and user-defined server roles
SELECT * FROM sys.server_principals WHERE type = 'R' ;

-- Returning a description of a fixed server role
EXEC sp_helpsrvrole 'diskadmin' ;
