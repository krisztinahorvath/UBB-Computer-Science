use TeaShop
go

create table FidelityCard (
	fid int primary key,
	cardNo int unique,
	points int
)

create table CreditCard(
	cid int primary key,
	cardNo int
)

create table Wallet (
	wid int primary key,
	fid int foreign key references FidelityCard(fid),
	cid int foreign key references CreditCard(cid)
)

create or alter procedure insertFidelityCard(@rows int) 
as
begin
	declare @max int
	set @max = @rows * 2 + 100

	while @rows > 0
	begin
		insert into FidelityCard values (@rows, @max, @max % 210)
		set @rows = @rows - 1
		set @max = @max -2 
	end
end
go

create or alter procedure insertCreditCard(@rows int) as
begin
	while @rows > 0 
	begin
		insert into CreditCard values(@rows, @rows%542)
		set @rows = @rows - 1
	end
end
go

create or alter procedure insertWallet(@rows int) as
begin
	declare @fid int 
	declare @cid int
	while @rows > 0
	begin
		set @fid = (SELECT TOP 1 fid FROM FidelityCard ORDER BY NEWID())
		set @cid = (SELECT TOP 1 cid FROM CreditCard ORDER BY NEWID())
		insert into Wallet values(@rows, @fid, @cid)
		set @rows = @rows - 1
	end
end
go

exec insertFidelityCard 5000
exec insertCreditCard 5000
exec insertWallet 5000

-- a. Write queries on Ta such that their execution plans contain the following operators:

-- clustered index scan - entire table
select * from FidelityCard

-- clustered index seek - return a specific subset of rows from a clustered index
select * 
from FidelityCard
where fid > 500

-- nonclustered index scan - scan the entire nonclustered index
select cardNo
from FidelityCard
order by cardNo

-- nonclustered index seek - return a specific subset of rows from a nonclustered index
select cardNo
from FidelityCard
where cardNo between 1000 and 5000

-- key lookup - nonclustered index seek + key lookup - the data is found in a nonclustered index, but additional data is needed
select points, cardNo
from FidelityCard
where cardNo = 1000


-- b. Write a query on table Tb with a WHERE clause of the form WHERE b2 = value and analyze its execution plan. 
-- Create a nonclustered index that can speed up the query. Examine the execution plan again.

select * 
from CreditCard
where cardNo = 538

create nonclustered index CreditCard_index on CreditCard(cardNo)
drop index CreditCard_index on CreditCard

-- c. Create a view that joins at least 2 tables. Check whether existing indexes are helpful; 
-- if not, reassess existing indexes / examine the cardinality of the tables.

create or alter view myView 
as 
	select FidelityCard.fid, CreditCard.cid, Wallet.wid
	from Wallet
	inner join FidelityCard on FidelityCard.fid = Wallet.wid
	inner join CreditCard on CreditCard.cid = Wallet.wid
	where CreditCard.cardNo > 100 and FidelityCard.points < 3000
go

select * from myView

create nonclustered index FidelityCard_index on FidelityCard(points)
drop index FidelityCard_index on FidelityCard

create nonclustered index Wallet_index on Wallet(fid, cid)
drop index Wallet_index on Wallet

