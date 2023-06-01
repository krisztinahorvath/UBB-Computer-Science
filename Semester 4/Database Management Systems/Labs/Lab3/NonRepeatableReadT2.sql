use TeaShop
go


--non-repeatable read T2
set transaction isolation level read committed
begin tran
select * from Teas
waitfor delay '00:00:07'
select * from Teas
commit tran

--solution:
set transaction isolation level repeatable read
begin tran
select * from Teas
waitfor delay '00:00:07'
select * from Teas
commit tran