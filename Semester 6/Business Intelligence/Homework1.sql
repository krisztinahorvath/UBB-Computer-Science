create database OrganizationsCountries
go

use OrganizationsCountries
go


create table Organizations(
	organizationCode int primary key,
	organizationName varchar(30),
	headquarter varchar(30),
	foundedDate date
)

create table Countries(
	countryCode int primary key,
	countryName varchar(30),
	capital varchar(30),
	area int,
	countryPopulation decimal,
	continent varchar(30),
)

create table OrganizationsCountries(
	countryCode int foreign key references Countries(countryCode) not null,
	organizationCode int foreign key references Organizations(organizationCode) not null,
)


insert into Organizations(organizationCode, organizationName, headquarter, foundedDate) 
	values (111, 'NATO', 'Washington', '1980-04-22'),
	(222, 'CIA', 'New York', '1967-04-22'),
	(333, 'SRI', 'Bucuresti', '1980-04-22')


insert into Countries(countryCode, countryName, capital, area, countryPopulation, continent) values
	(1111, 'Romania', 'Bucuresti', 15000, 15000000, 'Europe'),
	(2222, 'USA', 'Washington', 200000, 20000000, 'North America'),
	(3333, 'UK', 'London', 20000, 1800000, 'Europe')


insert into Countries(countryCode, countryName, capital, area, countryPopulation, continent) values (444, 'Hungary', 'Budapest', 2000, 123321, 'Europe')


insert into OrganizationsCountries(countryCode, organizationCode) values 
	(1111, 111), (1111, 333), (2222, 111), (2222, 222), (3333, 111)

-- 1. List all the countries which are members of NATO.
select c.*
from Countries c
join OrganizationsCountries oc on c.countryCode = oc.countryCode
join Organizations o on oc.organizationCode = o.organizationCode
where o.organizationName = 'NATO';


--2. List all the countries which are members of organizations founded before 1980
select c.*
from Countries c
join OrganizationsCountries oc on c.countryCode = oc.countryCode
join Organizations o on oc.organizationCode = o.organizationCode
where o.foundedDate < '1980-01-01'; ;

--3. List all the countries which are members of only one organization
select c.countryName
from Countries c
join OrganizationsCountries oc on c.countryCode = oc.countryCode
group by c.countryName
having count(oc.organizationCode) = 1;


--4. List all the capitals which are headquarter of no organization
select capital
from Countries
where capital not in (select headquarter from Organizations);


--5. List the population of each continent
select continent, sum(countryPopulation) as populationNr
from Countries
group by continent;


--6. Count the countries of each continent
select continent, count(*) as countryCount
from Countries
group by continent;
