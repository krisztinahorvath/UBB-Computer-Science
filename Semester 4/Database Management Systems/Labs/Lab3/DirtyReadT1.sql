use TeaShop
go

--Dirty Read T1
begin transaction
update Allergens set name = 'Almond milk'
where alid = 6
waitfor delay '00:00:10'
rollback transaction 


