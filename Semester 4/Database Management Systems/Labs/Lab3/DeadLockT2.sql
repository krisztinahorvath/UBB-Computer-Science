use TeaShop
go

--Deadlock T2
set deadlock_priority low
begin tran 
update Allergens set name = 'allergen t2' where alid = 5
waitfor delay '00:00:10'
update Teas set name = 'tea t2' where tid = 2
commit tran

--solution:
set deadlock_priority high
begin tran 
update Allergens set name = 'allergen t2' where alid = 5
waitfor delay '00:00:10'
update Teas set name = 'tea t2' where tid = 2
commit tran