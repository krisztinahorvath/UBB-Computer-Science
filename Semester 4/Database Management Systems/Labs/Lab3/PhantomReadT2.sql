use TeaShop
go

-- Phantom Read T2
set transaction isolation level repeatable read
begin tran
select * from Allergens
waitfor delay '00:00:07'
select * from Allergens
commit tran

--solution:
set transaction isolation level serializable
begin tran
select * from Allergens
waitfor delay '00:00:07'
select * from Allergens
commit tran