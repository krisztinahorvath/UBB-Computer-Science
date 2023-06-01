--alter database TeaShop set allow_snapshot_isolation on

use TeaShop
go

-- Update conflict T1
waitfor delay '00:00:10'
begin tran
update Allergens set name='update conflict' where alid=6
waitfor delay '00:00:10'
commit tran

select * from Allergens


--alter database TeaShop set allow_snapshot_isolation off

