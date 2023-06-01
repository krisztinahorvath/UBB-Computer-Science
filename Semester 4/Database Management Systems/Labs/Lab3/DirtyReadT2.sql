use TeaShop 
go

--Dirty Read T2
set transaction isolation level read uncommitted
begin tran
select * from Allergens
waitfor delay '00:00:15'
select * from Allergens
commit tran

--solution
set transaction isolation level read committed
begin tran
select * from Allergens
waitfor delay '00:00:15'
select * from Allergens
commit tran
