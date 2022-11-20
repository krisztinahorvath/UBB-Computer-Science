create database TeaShop
go

use TeaShop
go

create table TeaTypes (
	ttid int primary key identity,
	name varchar(40) not null
)

create table Allergens(
	alid int primary key identity,
	name varchar(40) not null
)

create table Distributors (
	did int primary key identity,
	name varchar(40) not null,
	address varchar(60)
)

create table Teas (
	tid int primary key identity,
	ttid int foreign key references TeaTypes(ttid) not null,
	name varchar(40) not null,
	quantity int default 1,
	price float not null,
	did int foreign key references Distributors(did) not null
)

create table AllergTeas (
	tid int foreign key references Teas(tid) not null,
	alid int foreign key references Allergens(alid) not null,
	constraint pf_AllergTeas primary key(tid,alid)
)

create table Clients (
	cid int primary key identity,
	name varchar(40) not null,
	email varchar(40) not null,
	address varchar(60) not null
)

create table Employees (
	eid int primary key identity,
	name varchar(40) not null,
	jobTitle varchar(40) not null
)

create table EmployeeDetails (
	eid int foreign key references Employees(eid) not null,
	email varchar(40) not null,
	salary float not null,
	address varchar(60),
	hiringDate date not null,
	constraint pk_EmployeeDetails primary key(eid)
)

create table Orders (
	oid int primary key identity,
	eid int foreign key references Employees(eid) not null,
	cid int foreign key references Clients(cid) not null
)

create table TeaOrders (
	tid int foreign key references Teas(tid) not null,
	oid int foreign key references Orders(oid) not null,
	constraint pk_TeaOrders primary key(oid, tid),
	price float not null,  
	quantity int default 1,
	orderingDate date not null
)


--
--use master
--go
--drop database TeaShop