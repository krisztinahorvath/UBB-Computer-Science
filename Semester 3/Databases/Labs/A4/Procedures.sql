use TeaShop
go

create or alter procedure addTeaTypes
@n int 
as
begin
	declare @i int=0
	while @i < @n 
	begin 
		insert into TeaTypes values (concat ('Type ', @i))
		set @i = @i + 1
	end
end
go

create or alter procedure deleteTeaTypes
as
begin
	delete from TeaTypes where name like 'Type %'
end
go


create or alter procedure addTeas
@n int 
as
begin
	declare @type int  = (select top 1 ttid from TeaTypes where name like 'Type %') 

	declare @i int=0

	while @i < @n 
	begin 
		--(ttid, name, quantity, price, did)
		insert into Teas values (@type, concat ('Tea ', @i), 10, 2.5, 1)
		set @i = @i + 1
	end
end
go

create or alter procedure deleteTeas
as
begin
	delete from Teas where name like 'Tea %'
end 
go


create or alter procedure addTeaOrders
@n int 
as
begin
	declare @tid int
	declare @oid int
	declare curs cursor
		for
		select t.tid, o.oid from (select tid from Teas where name like 'Tea %')t cross join Orders o
	open curs
	declare @i int=0
	while @i < @n
	begin
		fetch next from curs into @tid, @oid
		insert into TeaOrders(tid, oid, price, quantity, orderingDate) values (@tid, @oid, 10, -100 * @i, '2022-02-14')
		set @i=@i+1
	end 
	close curs 
	deallocate curs
end
go

create or alter procedure deleteTeaOrders
as
begin
	delete from TeaOrders where quantity <= 0
end
go 


create or alter view viewTeaTypes
as
	select name
	from TeaTypes
go
--select * from viewTeaTypes

create or alter view viewTeas
as
	select Teas.tid, Teas.ttid
	from Teas inner join TeaTypes on Teas.ttid = TeaTypes.ttid
go

create or alter view viewTeaOrders
as
	select Teas.name, sum(TeaOrders.quantity) as nrOfTeas
	from TeaOrders inner join Teas on TeaOrders.tid = Teas.tid
	group by Teas.name
go
--select * from viewTeaOrders

create or alter procedure selectView
(@name varchar(100))
as
begin
	declare @sql varchar(250) = 'select * from ' + @name
	exec(@sql)
end
go


insert into Tests(Name) values ('addTeaTypes'), ('deleteTeaTypes'), ('addTeas'), ('deleteTeas'), ('addTeaOrders'), ('deleteTeaOrders'), ('selectView')
insert into Tables(Name) values ('TeaTypes'), ('Teas'), ('TeaOrders')
insert into Views(name) values ('viewTeaTypes'), ('viewTeas'), ('viewTeaOrders')

select * from Tests
select * from Tables
select * from Views

insert into TestViews(TestID, ViewID) values (7, 1), (7, 2), (7, 3)

insert into TestTables(TestID, TableID, NoOfRows, Position) 
values 
	(6, 3, 70, 1), --deleteTeaOrders
	(4, 2, 30, 2),
	(2, 1, 100, 3),
	(1, 1, 50, 1),  --insertTeaTypes
	(3, 2, 150, 2),
	(5, 3, 200, 3)

select * from TestTables
select * from TestViews


create or alter procedure mainTest
as
begin
	insert into TestRuns values ('', '2000', '2000')

	declare @testRunID int
	set @testRunID = (select max(TestRunID) from TestRuns)

	print 'running test with id ' + convert(varchar, @testRunID)
	update TestRuns
	set Description = 'test' + convert(varchar, @testRunID)
	where TestRunID = @testRunID 

	declare @noOfRows int
	declare @tableID int
	declare @tableName varchar(100)
	declare @startAt datetime
	declare @endAt datetime
	declare @viewID int
	declare @viewName varchar(100)
	declare @name varchar(100)

	declare testDeleteCursor cursor
	for
	select TableID, Name, NoOfRows
	from Tests inner join TestTables on Tests.TestID = TestTables.TestID
	where Name like 'delete%' 
	order by Position 

	open testDeleteCursor
	
	fetch next
	from testDeleteCursor
	into @tableID, @name, @noOfRows

	set @startAt = getdate()

	update TestRuns
	set StartAt = @startAt
	where TestRunID = @testRunID and year(StartAt) = 2000


	while @@FETCH_STATUS = 0
	begin
		print 'running  ' + @name

		exec(@name) 

		fetch next
		from testDeleteCursor
		into @tableID,@name,  @noOfRows
	end

	close testDeleteCursor
	deallocate testDeleteCursor

	-- insert tests

	declare testInsertCursor cursor
	for
	select TableID, Name, NoOfRows
	from Tests inner join TestTables on Tests.TestID = TestTables.TestID
	where Name like 'add%' 
	order by Position 

	open testInsertCursor

	fetch next
	from testInsertCursor
	into @tableID, @name, @noOfRows

	while @@FETCH_STATUS = 0
	begin

		set @startAt = getdate()

		print 'running ' + @name

		exec @name @noOfRows
		
		set @endAt = getdate()

		insert into TestRunTables values (@testRunID, @tableID, @startAt, @endAt)

		fetch next
		from testInsertCursor
		into @tableID, @name, @noOfRows
	end

	close testInsertCursor
	deallocate testInsertCursor


	-- view tests

	declare testViewCursor cursor
	for 
	select ViewID
	from TestViews

	open testViewCursor

	fetch next
	from testViewCursor
	into @viewID

	while @@FETCH_STATUS = 0
	begin
		set @viewName = (select Name from Views where ViewID = @viewID)

		set @startAt = getdate()
		print 'view name ' + @viewName
		exec selectView @viewName
		set @endAt = getdate()

		insert into TestRunViews values (@testRunID, @viewID, @startAt, @endAt)

		fetch next
		from testViewCursor
		into @viewID
	end

	update TestRuns
	set EndAt = @endAt
	where TestRunID = @testRunID

	close testViewCursor
	deallocate testViewCursor
end
go

exec mainTest

select * from TestRunTables
select * from TestRunViews
select * from TestRuns 
