-- select names of tables created by @user

declare @user nvarchar(50)
use ivKVN
set @user = 'dbo'


-- Selecting names of personal tables of @user 
select obj.name as table_name
from sys.sysobjects as obj, sys.sysusers as usr
where obj.uid = usr.uid
and   usr.name = @user
and   obj.type = 'U'

-- table, column, is nullable, data type, data type size
select	obj.name as 'table', 
		col.name as 'column', 
		case when col.isnullable = 0 then 'no' when col.isnullable = 1 then 'yes' end,
		typez.name,
		typez.length		 
from sys.sysobjects as obj, sys.syscolumns as col, sys.systypes as typez, sys.sysusers as usr
where	obj.type = 'U'
and		obj.id   = col.id
and     col.xtype=typez.xtype
and		obj.uid = usr.uid
and		usr.name = @user;

-- references 1
with temp(ref, forgn, parent)
as (
select obj1.name, obj2.name, obj3.name
from 
(sys.sysreferences as ref1
inner join
sys.sysobjects as obj1
on (ref1.constid = obj1.id)
inner join 
sys.sysobjects as obj2
on (ref1.fkeyid = obj2.id)
inner join
sys.sysobjects as obj3
on (ref1.rkeyid = obj3.id)), sys.sysusers as usr
where obj1.uid = usr.uid
and   usr.name = @user)

select distinct temp.ref, temp.forgn, 'PK'
from temp

union

select distinct temp.ref, temp.parent, 'F'
from temp;


-- references 2
with temp2(uid, ref, forgn, parent)
as (
select obj1.uid, obj1.name, obj2.name, obj3.name
from 
sys.sysreferences as ref1
inner join
sys.sysobjects as obj1
on (ref1.constid = obj1.id)
inner join 
sys.sysobjects as obj2
on (ref1.fkeyid = obj2.id)
inner join
sys.sysobjects as obj3
on (ref1.rkeyid = obj3.id)
)

select temp2.ref, temp2.forgn, temp2.parent
from temp2, sys.sysusers as usr
where temp2.uid = usr.uid
and   usr.name = @user



-- views
select obj.name, comm.text
from sys.sysobjects as obj , sys.syscomments as comm, sys.sysusers as usr
where obj.xtype = 'V'
and   obj.id = comm.id
and   obj.uid = usr.uid
and   usr.name = @user;



-- trigger
with temp3(name, tabl)
as (
select obj.name, obj.parent_obj
from sys.sysobjects as obj, sys.sysusers as usr
where obj.uid  = usr.uid
and   usr.name = @user
)

select temp3.name, obj1.name
from temp3
inner join
sys.sysobjects as obj1
on temp3.tabl = obj1.id