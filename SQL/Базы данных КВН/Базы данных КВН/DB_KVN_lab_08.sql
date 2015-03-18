SELECT *
	FROM sysobjects
	ORDER BY XTYPE;

SELECT *
	FROM SYSCOLUMNS;
SELECT *
	FROM SYSUSERS;
SELECT * 
	FROM sys.all_objects;
SELECT *
	FROM sysreferences;
SELECT *
	FROM INFORMATION_SCHEMA.TABLES;

SELECT TABLE_NAME
	FROM information_schema.tables
	WHERE TABLE_TYPE= 'BASE TABLE';


SELECT sysobjects.name
	FROM sysobjects, sysusers
	WHERE xtype = 'U'
		AND	sysusers.uid = sysobjects.UiD
		AND	sysusers.name = USER_NAME();


SELECT sysobjects.name
	FROM SYSOBJECTS, SYSUSERS
	WHERE XTYPE='U'
	AND sysobjects.uid = SYSUSERS.uid
	AND  SYSUSERS.NAME = USER_NAME()
	AND sysobjects.ID NOT IN (SELECT major_id
									FROM SYS.extended_properties);
/*
select *
from fn_listextendedproperty ('microsoft_database_tools_support', 'schema', 'dbo', 'table', 'sysdiagrams', null, null)


select *
from fn_listextendedproperty ('microsoft_database_tools_support', 'schema', 'dbo', 'table', null, null, null)
*/


SELECT sysobjects.name, syscolumns.name, syscolumns.isnullable, systypes.name, syscolumns.length
	FROM sysobjects, sysusers, syscolumns, systypes
	WHERE sysobjects.xtype = 'U'
	AND	sysusers.uid = sysobjects.uid
	AND	sysusers.name = user_name()
	AND	syscolumns.id = sysobjects.id
	AND	systypes.xtype = syscolumns.xtype
	AND sysobjects.ID NOT IN (SELECT major_id
									FROM SYS.extended_properties);



SELECT T1.name, T2.name, T1.xtype
	FROM sysobjects T1, sysobjects T2, sysusers
	WHERE sysusers.uid = T1.uid
	AND	sysusers.name = USER_NAME()
	AND T2.id = T1.parent_obj
	AND	(T1.xtype = 'PK' OR T1.xtype = 'F')
	AND T2.ID NOT IN (SELECT major_id
									FROM SYS.extended_properties);



SELECT T1.name, T2.name, T3.name
	FROM sysreferences, sysobjects T1, sysobjects T2, sysobjects T3, sysusers
	WHERE sysreferences.constid = T1.id
	AND	sysusers.uid = T1.uid
	AND sysusers.name = USER_NAME()
	AND	sysreferences.fkeyid = T2.id
	AND	sysreferences.rkeyid = T3.id;



SELECT sysobjects.name, syscomments.text
	FROM sysobjects, syscomments, sysusers
	WHERE sysobjects.xtype = 'V'
	AND sysobjects.uid = sysusers.uid
	AND	sysusers.name = USER_NAME()
	AND sysobjects.id = syscomments.id;


SELECT T1.name, T2.name
	FROM sysobjects T1, sysobjects T2, sysusers
	WHERE T1.xtype = 'TR'
	AND	T1.parent_obj=t2.id
	AND T1.uid = sysusers.uid
	AND sysusers.name = USER_NAME();

SELECT *
	FROM SYS.stats
db.size

SELECT SUM(syscolumns.length)
	FROM sysobjects, syscolumns
	WHERE syscolumns.id = sysobjects.id;


SELECT *
	FROM db_cache

sp_spaceused

USE [25];
GO
EXEC sp_spaceused N'rchasing.Vendor';
GO