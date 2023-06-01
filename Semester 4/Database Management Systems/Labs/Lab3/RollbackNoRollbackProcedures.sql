use TeaShop
go

select * from Allergens
select * from Teas
select * from AllergTeas
select * from Distributors

-- validations:

--valid name Teas & Allergens
create or alter function uf_ValidateName(@name varchar(40)) returns int as
begin
	declare @return int
	set @return = 0
	if (len(@name) >= 3)
		set @return = 1
	return @return
end

DECLARE @result INT
EXEC @result = uf_ValidateName 'ange'
SELECT @result AS 'Result'

--valid quantity in Teas
create or alter function uf_ValidateQuantity(@quantity int) returns int as
begin
	declare @return int
	set @return = 0
	if (@quantity > 0 )
		set @return = 1
	return @return
end

DECLARE @result INT
EXEC @result = uf_ValidateQuantity 10
SELECT @result AS 'Result'

--valid price in Teas
create or alter function uf_ValidatePrice(@price float) returns int as
begin
	declare @return int
	set @return = 0
	if (@price > 0)
		set @return = 1
	return @return
end

DECLARE @result INT
EXEC @result = uf_ValidatePrice -2
SELECT @result AS 'Result'


--valid did in Teas, if the distributor exists
create or alter function uf_ValidateDistributor(@distributorName varchar(40)) returns int as
begin
	declare @return int
	set @return = isnull((select did from Distributors where name = @distributorName), 0)
	return @return
end

select name from Distributors

DECLARE @result INT
EXEC @result = uf_ValidateDistributor 'Native American Herbal Tea Company'
SELECT @result AS 'Result'

--valid ttid in Teas, if the tea type exists
create or alter function uf_ValidateTeaType(@teaType varchar(40)) returns int as
begin
	declare @return int
	set @return = isnull((select ttid from TeaTypes where name = @teaType), 0)
	return @return
end

select name from TeaTypes

DECLARE @result INT
EXEC @result = uf_ValidateTeaType 'focusa'
SELECT @result AS 'Result'


-- Setup a logging system to track executed actions for all scenarios
create table LogTable(
	Lid int identity primary key,
	TypeOperation varchar(50), -- insert, update, delete, select
	TableOperation varchar(50),
	LogStatus varchar(50),
	ExecutionDate datetime)

	
-- create a stored procedure that inserts data in tables that are in a m:n relationship; 
-- if one insert fails, all the operations performed by the procedure must be rolled back 
create or alter procedure AddAllergenTea 
		@allergenName varchar(40), 
		@teaType varchar(40), 
		@teaName varchar(40), 
		@quantity int, 
		@price float,  
		@distributor varchar(40) 
as
begin
	begin tran
	begin try

		-- valid allergen fields
		if(dbo.uf_ValidateName( @allergenName) <> 1)
		begin
			raiserror('The name of the allergen should be at least 3 characters long', 14, 1)
		end

		-- valid tea fields
		if(dbo.uf_ValidateName( @teaName) <> 1)
		begin
			raiserror('The name of the tea should be at least 3 characters long', 14, 1)
		end

		declare @ttid int = dbo.uf_ValidateTeaType( @teaType)
		if( @ttid = 0)
		begin
			raiserror('The given type does not exist', 14, 1)
		end

		if(dbo.uf_ValidateQuantity( @quantity) <> 1)
		begin
			raiserror('The quantity should be a strictly positive number', 14, 1)
		end

		if(dbo.uf_ValidatePrice( @price) <> 1)
		begin
			raiserror('The price should be a strictly positive floating point number', 14, 1)
		end

		declare @did int = dbo.uf_ValidateDistributor( @distributor)
		if(@did = 0)
		begin
			raiserror('The given distributor does not exist', 14, 1)
		end

		insert into Allergens(name) values (@allergenName)
		insert into Teas(ttid, name, quantity, price, did) values (@ttid, @teaName, @quantity, @price, @did)
		declare @tid int = (select max(tid) from Teas)
		declare @alid int = (select max(alid) from Allergens)
		insert into AllergTeas(tid, alid) values (@tid, @alid)

	commit tran
		insert into LogTable(TypeOperation, TableOperation, LogStatus, ExecutionDate) values('insert', 'Allergens, Teas, AllergTeas', 'committed', GETDATE())
		select 'transaction committed'
	end try	
	begin catch
		rollback tran 
		insert into LogTable(TypeOperation, TableOperation, LogStatus, ExecutionDate) values('insert', 'Allergens, Teas, AllergTeas', 'rollbacked', GETDATE())
		select 'Transaction rollbacked: ' + ERROR_MESSAGE() as ErrorMessage
	end catch
end

select * from Allergens
select * from Teas
select * from AllergTeas


-- commit
select * from LogTable
exec AddAllergenTea @allergenName='testing', @teaType='sleep', @teaName='testing', @quantity=10, @price=10, @distributor='Hugo Tea Company'
select * from LogTable

--rollback
--negative quantity
select * from LogTable
exec AddAllergenTea @allergenName='testing', @teaType='sleep', @teaName='testing', @quantity=-10, @price=10, @distributor='Hugo Tea Company'
select * from LogTable

-- create a stored procedure that inserts data in tables that are in a m:n relationship; 
-- if an insert fails, try to recover as much as possible from the entire operation: for example, 
-- if the user wants to add a book and its authors, succeeds creating the authors, but fails with the book, 
-- the authors should remain in the database (grade 5);

create or alter procedure AddAllergenTeaRecovery 
		@allergenName varchar(40), 
		@teaType varchar(40), 
		@teaName varchar(40), 
		@quantity int, 
		@price float,  
		@distributor varchar(40) 
as
begin
	declare @alid int = -1
	declare @tid int = -1

	-- allergens
	begin try
		begin tran
		
		if(dbo.uf_ValidateName( @allergenName) <> 1)
		begin
			raiserror('The name of the allergen should be at least 3 characters long', 14, 1)
		end
		insert into Allergens(name) values (@allergenName)

		commit tran 
		set @alid = (select max(alid) from Allergens)
		insert into LogTable(TypeOperation, TableOperation, LogStatus, ExecutionDate) values('insert', 'Allergens', 'committed', GETDATE())
	end try
	begin catch
		if @@TRANCOUNT > 0  rollback tran 
		insert into LogTable(TypeOperation, TableOperation, LogStatus, ExecutionDate) values('insert', 'Allergens', 'error', GETDATE())
	end catch

	--teas
	begin try
		begin tran 

		if(dbo.uf_ValidateName( @teaName) <> 1)
		begin
			raiserror('The name of the tea should be at least 3 characters long', 14, 1)
		end

		declare @ttid int = dbo.uf_ValidateTeaType( @teaType)
		if( @ttid = 0)
		begin
			raiserror('The given type does not exist', 14, 1)
		end

		if(dbo.uf_ValidateQuantity( @quantity) <> 1)
		begin
			raiserror('The quantity should be a strictly positive number', 14, 1)
		end

		if(dbo.uf_ValidatePrice( @price) <> 1)
		begin
			raiserror('The price should be a strictly positive floating point number', 14, 1)
		end

		declare @did int = dbo.uf_ValidateDistributor( @distributor)
		if(@did = 0)
		begin
			raiserror('The given distributor does not exist', 14, 1)
		end

		insert into Teas(ttid, name, quantity, price, did) values (@ttid, @teaName, @quantity, @price, @did)
		
		commit tran 
		set @tid = (select max(tid) from Teas)
		insert into LogTable(TypeOperation, TableOperation, LogStatus, ExecutionDate) values('insert', 'Teas', 'committed', GETDATE())
		
	end try
	begin catch
		if @@TRANCOUNT > 0  rollback tran 
		insert into LogTable(TypeOperation, TableOperation, LogStatus, ExecutionDate) values('insert', 'Teas', 'error', GETDATE())
	end catch

	if(@alid <> -1 and @tid <> -1)
	begin
		begin tran 
			insert into AllergTeas(tid, alid) values (@tid, @alid)
		commit tran
		insert into LogTable(TypeOperation, TableOperation, LogStatus, ExecutionDate) values('insert', 'AllergTeas', 'committed', GETDATE())
	end
	else
	begin
		insert into LogTable(TypeOperation, TableOperation, LogStatus, ExecutionDate) values('insert', 'AllergTeas', 'error', GETDATE())
		select 'the insert into AllergTeas table could not be made'
	end
end


select * from Allergens
select * from Teas
select * from AllergTeas


-- commit
select * from LogTable
exec AddAllergenTeaRecovery @allergenName='testing', @teaType='sleep', @teaName='testing', @quantity=10, @price=10, @distributor='Hugo Tea Company'
select * from LogTable

-- rollback
-- allergen name doesn't have at least 3 characters
select * from LogTable
exec AddAllergenTeaRecovery @allergenName='t3', @teaType='sleep', @teaName='test100', @quantity=10, @price=10, @distributor='Hugo Tea Company'
select * from LogTable