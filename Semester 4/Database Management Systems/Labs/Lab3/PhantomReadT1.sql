use TeaShop
go
-- Phantom Read T1
begin tran
waitfor delay '00:00:07'
insert into Allergens(name) values ('phantom read')
commit tran