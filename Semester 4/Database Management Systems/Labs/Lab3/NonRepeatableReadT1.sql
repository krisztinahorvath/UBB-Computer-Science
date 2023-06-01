use TeaShop
go

--non-repeatable read T1
insert into Teas(ttid, name,price, did) values (1, 'non-repeat', 10000, 1)
begin tran
waitfor delay '00:00:07'
update Teas set name='updated' where price = 10000
commit tran

delete from Teas where tid > 10