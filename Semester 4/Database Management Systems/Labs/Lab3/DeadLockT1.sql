use TeaShop
go

--Deadlock T1
begin tran 
update Teas set name = 'tea t1' where tid = 2
waitfor delay '00:00:10'
update Allergens set name = 'allergen t1' where alid = 5
commit tran

select * from Allergens
select * from Teas