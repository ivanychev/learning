use ivKVN
go

drop view media_info;
go

create view media_info(url, type, Id1, Id2)
as 
	select  record.url url, record_type.description type, record.type_id, record_type.type_id
	from	record,
			record_type
	where record.type_id = record_type.type_id
go


insert into media_info(url, Id1)
values('http://google.com', 6)


set identity_insert record_type on
insert into media_info(type, Id2)
values('Notes', 6)
set identity_insert record_type off


select *
from media_info

select *
from record

select *
from record_type






select *
from media_info