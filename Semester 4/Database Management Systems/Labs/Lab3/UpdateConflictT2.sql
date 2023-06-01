use TeaShop
go

-- Update conflict T2
set transaction isolation level snapshot
begin tran
select * from Allergens where alid=6 
waitfor delay '00:00:10'
select * from Allergens where alid=4
update Allergens set name='name t2' where alid=6
commit tran