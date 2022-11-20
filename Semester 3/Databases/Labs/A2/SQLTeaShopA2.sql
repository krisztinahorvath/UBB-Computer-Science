use TeaShop
go

--insert data – for at least 4 tables; 
--at least one statement must violate referential integrity constraints;

insert into TeaTypes (
	name
) values
	('sleep'),
	('energy'),
	('focus'),
	('meditation')



insert into Allergens(
	name
) values
	('Almonds'),
	('Milk'),
	('Soy Lecithin'),
	('Coconut'),
	('Peanuts'),
	('Gluten')




insert into Distributors(
	name,
	address
) values 
	('Native American Herbal Tea Company', '102 4th Ave SE, Aberdeen, SD 57401, USA'),
	('Hugo Tea Company', '1007 Swift Ave, Kansas City, MO 64116'),
	('Cooper Tea Company', '408 S Pierce Ave, Louisville, CO 80027'),
	('New Mexico Tea Company', '1131 Mountain Rd NW Ste 2, Albuquerque'),
	('Phoenix Tea Company', '4243 W 3rd St # 9651, Battlefield'),
	('International Company', 'Fatherland Street, Nashville, TN 37206')

select * from Distributors

insert into Teas(
	ttid,
	name,
	quantity,
	price,
	did   -- here i can have error trying to insert on a did that doesn't exist

)values
	(1, 'Evergreen', 4, 2.6, 1),
	(2, 'Grand Tisane', 3, 9.3, 2),
	(3, 'Toasted Almond', 2, 7, 1),
	(3, 'Johannesburg', 5, 6.5, 6),
	(4, 'Mama Bahama', 10, 9.2, 6),
	(2, 'Mango Flip', 13, 5.5, 4),
	(4, 'Coconut Vanilla', 4, 3.2,5),
	(2, 'Organic Rooi Coconut', 5, 7, 3),
	(2, 'Sencha Tropic', 1, 12.5, 6),
	(3, 'Red Jamaica', 2, 10, 4)

--ERROR
insert into Teas(
	ttid,
	name,
	quantity,
	price,
	did   -- here i can have error trying to insert on a did that doesn't exist

)values
	(1, 'Evergreen', 4, 2.6, 10)



insert into AllergTeas(
	tid,
	alid
) values
	(1, 1),
	(2, 1),
	(3, 1),
	(4, 2),
	(5, 2),
	(6, 2),
	(7, 4),
	(8, 4),
	(10, 2),
	(5, 4),
	(6, 4),
	(4, 3),
	(9, 4),
	(10, 4)



insert into Clients(
	name, 
	email,
	address
)values
	('Sherlock Holmes', 'sherlock.holmes@email.com', '750 Bartoletti Burgs, Apt. 038, Great Britain'),
	('Nicole Willis', 'nicole.willis@email.com', 'Larsplein 6, 2 hoog, Utrecht, Netherlands'),
	('Jason Simon', 'jason.simon@email.com', '56 Schuster Plaza, Suite 269, New York, United States'),
	('Melissa Bell', 'melissa.bell@email.com', '708 Casandra Mission, Apt. 800, Great Britain'),
	('Anthony Glover', 'anthony.glover@email.com', '3341 Wolff Shoals, Suite 737, Great Britain'),
	('Donna Gonzalez', 'donna.gonzalez@email.com', '3574 Hayes Common, Kansas, United States'),
	('Barbara Brown', 'barbara.brown@email.com', '926 Kaden Mission, Apt. 921, Colorado, United States'),
	('Dorothy Lee', 'dorothy.lee@email.com', '55182 Runolfsson Mission, Apt. 843, Utah, United States')



insert into Employees(
	name,
	jobTitle
) values
	('Stephen Perry', 'manager'),
	('Bernard Scott', 'cashier'),
	('Chelsea Ashley', 'cleaning'),
	('Erika Hamilton', 'cashier'),
	('Thomas Hoffman', 'cashier'),
	('Richard Morton', 'cashier'),
	('Ana Popescu', 'cashier'),
	('Maria Andronescu', 'cashier')

	

insert into EmployeeDetails(
	eid,
	email,
	salary,
	address,
	hiringDate
)values
	(1, 'stephen.perry@email.com', 7000, '5 Daron Alley, Suite 1, Ohio, United States', '2015-02-15'),
	(2, 'bernard.scott@email.com', 4500, 'Suite 022, Boyerside, Massachusetts, United States', '2012-03-08'),
	(3, 'chelsea.ashley@email.com', 2000, 'Wilderman Rest, Suite 010, California, United States', '2020-09-01'),
	(4, 'erika.hamilton@email.com', 3500, '2134 Abel Orchard, Apt.21, Wisconsin, United States', '2018-12-21'),
	(5, 'thomas.hoffman@email.com', 3400, '0248 Inlet, Suite 203, Montana, United States', '2019-12-16'),
	(6, 'richard.morton@email.com', 4000, '5299 Pagac Port, Texas, United States', '2014-05-27'),
	(7, 'ana.popescu@email.com', 3900 , null, '2022-10-24'),
	(8, 'maria.andronescu@email.co', 4000, 'Wilderman Rest, Apt.21, Wisconsin, United States','2022-10-23')



insert into Orders(
	eid,
	cid
) values
	(2, 1),
	(4, 2),
	(4, 2),
	(5, 6),
	(6, 3), 
	(2, 7),
	(6, 5)



insert into TeaOrders(
	tid,
	oid,
	price,
	quantity,
	orderingDate
) values
	(1, 1, 2.6, 1, '2022-02-14'),
	(3, 2, 18.6, 2, '2022-04-17'),
	(3, 3, 9.3, 1, '2022-04-17'),
	(6, 4, 11, 2, '2022-06-19'),
	(8, 4, 7, 1, '2022-06-19'),
	(10, 5, 20, 2, '2022-09-15'),
	(5, 6, 27.6, 3, '2019-01-01'),
	(2, 7, 9.3, 1,'2020-07-28'),
	(9, 6, 12.5,1, '2019-01-01')



--update data – for at least 3 tables;


--increases the salary with 100 of all employees that have a salary >=4500
update EmployeeDetails
set salary=salary + 100
where salary >= 4500
select * from EmployeeDetails


--decreases the price by 2 euros of all the teas that have at least 10 pieces and at most 15
select * from Teas
update Teas
set price=price-2
where quantity between 10 and 15
select * from Teas

--update TeaOrders
--set price=20
--where tid=10 and oid=5

--gives a 10% discount for all orders placed in june and september of 2022.
select * from TeaOrders
update TeaOrders
set  price=price-0.1*price
where  Month(orderingDate) in (6, 9)
select * from TeaOrders



--delete data – for at least 2 tables

--delete all the orders that are older than a year and have the total greater than 10
select * from TeaOrders
delete from TeaOrders
where (YEAR(orderingDate) < 2022 and MONTH(orderingDate) <= 10 and DAY(orderingDate) <= 24) and price > 10
select * from TeaOrders



--delete the employees who don't have an adress or have an invalid email
--(doesn't end with '@email.com') 

delete from EmployeeDetails
where email not like '%email.com' or address is null

select * from EmployeeDetails

select * from Employees



--a. 2 queries with the union operation; use UNION [ALL] and OR;

--UNION
--show all the emails of the clients and employees in the database to send them a happy holiday email
select email
from Clients
where Clients.name like '%a' or Clients.name like '%b'
union 
select email
from EmployeeDetails
order by email

--UNION ALL
--show the employees that have packaged an order (in the future we can count all the distinct columns to see how many orders each employee had)
select E.name, E.eid
from Employees E
union all
select E.name , O.eid
from Orders O, Employees E
where O.eid=E.eid


--b. 2 queries with the intersection operation; use INTERSECT and IN;

--INTERSECT
--show the allergens found in the teas that have more than one pieces but less than 5, or it has exactly 6
select A.alid, A.name
from Allergens A
intersect
select AlT.alid, A.name
from AllergTeas AlT, Allergens A, Teas
where AlT.tid = Teas.tid and AlT.alid=A.alid and ((Teas.quantity > 1 and Teas.quantity < 5) or Teas.quantity=6)



--IN
--show all the teas that have allergens peanuts, almonds, and milk
select T.tid, T.name, A.name
from Teas T, AllergTeas AlT, Allergens A
where T.tid=AlT.tid and AlT.alid=A.alid and A.name in ('Peanuts', 'Almonds', 'Milk')



--c. 2 queries with the difference operation; use EXCEPT and NOT IN;

--EXCEPT
--find the clients that have a saved account but haven't ordered anything yet
select C.cid, C.name
from Clients C
except
select C.cid, C.name
from Orders O, Clients C
where O.cid=C.cid 



--NOT IN
--find the top 3 employees that haven't been hired in 2012, 2019, 2021 order them descending by their salary
select top 3 t.eid, t.name, t.salary, t.hiringDate
from 
	(select E.eid, E.name, EmployeeDetails.hiringDate,EmployeeDetails.salary
	from Employees E, EmployeeDetails
	where E.eid=EmployeeDetails.eid and year(EmployeeDetails.hiringDate) not in (2012,2019,2021)
	) t --ERROR if we use order by in the select in from
order by t.salary desc



--d. 4 queries with INNER JOIN, LEFT JOIN, RIGHT JOIN, and FULL JOIN (one query per operator); 
-- one query will join at least 3 tables, while another one will join at least two many-to-many relationships;

--INNER JOIN
--show all the different teas that have been ordered and the clients that have ordered them
--one query will join at least 3 tables
select TeaOrders.oid, Teas.name, Clients.cid
from Teas 
inner join TeaOrders on TeaOrders.tid=Teas.tid
inner join Orders on TeaOrders.oid=Orders.oid
inner join Clients on Clients.cid=Orders.cid


--LEFT JOIN
--show all cashiers that have packed an order of a tea with the allergen milk
--will join at least two many-to-many relationships;
select Employees.name, Teas.name as tea_name, Orders.oid
from Employees
left join Orders on Orders.eid=Employees.eid
left join TeaOrders on TeaOrders.oid=Orders.oid
left join Teas on Teas.tid=TeaOrders.tid
left join AllergTeas on AllergTeas.tid=Teas.tid
left join Allergens on Allergens.alid=AllergTeas.alid
where Employees.jobTitle='cashier' and Allergens.name='milk'


--RIGHT JOIN
--show all the different types that the teas in the current stock have and the maximum price of the teas that have it
select distinct TeaTypes.name, Teas.price
from Teas
right join TeaTypes on Teas.ttid=TeaTypes.ttid
where Teas.price=(select max(price) 
					from Teas
					where Teas.ttid=TeaTypes.ttid)

--FULL JOIN
--show 3 clients with the most expensive orders and their price
select top 3 Clients.name, TeaOrders.price 
from Clients
full join Orders on Clients.cid=Orders.cid
full join TeaOrders on TeaOrders.oid=Orders.oid
order by TeaOrders.price desc


--e. 2 queries with the IN operator and a subquery in the WHERE clause; 
--in at least one case, the subquery must include a subquery in its own WHERE clause;


--IN operator and a subquery in the WHERE clause; 
--show the employees that have been hired in 2019 and 2021(2020 no hiring-pandemic)
--and have the maximum salary of that year
select Employees.name, ED.salary, year(ED.hiringDate) as hiringYear
from Employees
full join EmployeeDetails ED on ED.eid=Employees.eid
where year(ED.hiringDate) in (2019, 2021) and ED.salary = (select max(EmployeeDetails.salary)
															from EmployeeDetails
														    where year(EmployeeDetails.hiringDate)=year(ED.hiringDate))



--IN operator and a subquery in the WHERE clause; 
--in at least one case, the subquery must include a subquery in its own WHERE clause;
--show all the employees that have packed for at least 2 clients and at least one of those clients ordered in 2022
--and show their salary with a 10% raise because of that 
select distinct Employees.eid,  Employees.name, ED.salary + ED.salary*0.1 as newSalary
from Employees
full join EmployeeDetails ED on ED.eid=Employees.eid
full join Orders O on O.eid=ED.eid
where ED.eid in (select Orders.eid
				from Orders
				where (select count(O.eid)
			    		from Orders O
						full join TeaOrders on TeaOrders.oid=O.oid
						full join Clients on O.cid=Clients.cid
						where year(TeaOrders.orderingDate)=2022 and O.eid=Orders.eid) >= 1
				group by Orders.eid
				having count(Orders.cid)=2 ) 


--f. 2 queries with the EXISTS operator and a subquery in the WHERE clause;

--show the teas that are in stock but haven't been ordered yet by anyone 
--and show their price with a 20% discount because of the lack of buyers
select Teas.name, Teas.price - Teas.price*0.2 as discountPrice
from Teas
where not exists (select * 
				 from TeaOrders
				 where Teas.tid = TeaOrders.tid) 


--show all the distributors that have distributed teas ordered this year
select D.did, D.name
from Distributors D
where exists(select *
			 from Teas
			 full join TeaOrders on TeaOrders.tid=Teas.tid
			 where Teas.did=D.did and year(TeaOrders.orderingDate)=2022)


--g. 2 queries with a subquery in the FROM clause; 

--show the top 3 most ordered teas so far 
select top 3 t.nrOfOrders, t.name
from (select count(TeaOrders.tid) as nrOfOrders, Teas.name
      from Teas
	  full join TeaOrders on TeaOrders.tid=Teas.tid
	  
	  group by Teas.name
	  having count(TeaOrders.tid) > 0)t
order by t.nrOfOrders desc

--show the client ids that have ordered this year and the number of orders they had
select count(t.cid) as nrOfOrders, t.cid
from (select distinct TeaOrders.oid, Clients.cid
      from Teas, TeaOrders
      full join Orders on Orders.oid=TeaOrders.oid
      full join Clients on Orders.cid=Clients.cid
      where Teas.tid=TeaOrders.tid and year(TeaOrders.orderingDate)=2022)t
group by T.cid
having count(t.cid)>0


--h. 4 queries with the GROUP BY clause, 3 of which also contain the HAVING clause; 
--2 of the latter will also have a subquery in the HAVING clause; 
--use the aggregation operators: COUNT, SUM, AVG, MIN, MAX;

--compute the average price of an order(make sure that orders with multiple items are 
--seen as one single order when computing the average)
select avg(t.total_price) as average_price
from (select O.oid, sum(TeaOrders.price) as total_price
	  from Orders O, TeaOrders
      where O.oid = TeaOrders.oid
      group by O.oid)t

--show the clients that have placed at least two different orders and the number of orders they placed
select Clients.cid, count(Orders.oid) as nr_of_orders
from Orders, Clients
where Clients.cid = Orders.cid
group by Clients.cid
having count(Orders.oid) >= 2

--show the maximum price of the orders in each year
select max(T.price) as maximum_order, year(T.orderingDate) as year_
from TeaOrders T
group by year(T.orderingDate)
having max(T.price) = (select max(t.total_price) as mx_ord
				from (select O.oid, sum(TeaOrders.price) as total_price
					 from Orders O, TeaOrders
					where O.oid = TeaOrders.oid and year(TeaOrders.orderingDate) = year(T.orderingDate)
					group by O.oid)t)

--show the job titles of the employees and the minimum salary of an employee from there
--and display the monthly pay for each department
select E.jobTitle, min(ED.salary) as min_sal, sum(ED.salary) as total_sal_dep
from EmployeeDetails ED, Employees E
where ED.eid = E.eid
group by E.jobTitle
having min(ED.salary) > 0 and sum(ED.salary) = (select sum(t.sal)
										from (select sum(EmployeeDetails.salary) as sal, Employees.jobTitle
										      from EmployeeDetails, Employees
										      where EmployeeDetails.eid=Employees.eid and Employees.jobTitle = E.jobTitle
											  group by Employees.jobTitle)t) 


--i. 4 queries using ANY and ALL to introduce a subquery in the WHERE clause (2 queries per operator); 
--rewrite 2 of them with aggregation operators, and the other 2 with IN / [NOT] IN.


--show the top 3 cheapest teas that have been ordered before and increase their price by 10% due to their popularity
select top 3 T.name, T.price + T.price*0.1 as new_price
from Teas T
where T.tid = ANY (select TeaOrders.tid
				   from TeaOrders)
order by T.price

--rewritten with IN
select top 3 T.name, T.price + T.price*0.1 as new_price
from Teas T
where T.tid in (select TeaOrders.tid
		        from TeaOrders, Teas )
order by T.price


--show the the top 5 orders that are more expensive than the cheapest order
select top 5 TeaOrders.*
from TeaOrders
where TeaOrders.price > ANY (select T.price
							 from TeaOrders T)
order by TeaOrders.price desc

--rewritten with MIN
select top 5 TeaOrders.*
from TeaOrders
where TeaOrders.price > (select min(T.price)
							 from TeaOrders T)
order by TeaOrders.price desc


--show the cashier with the smallest salary and increase it by 15%
select E.name, ED.salary as old_salary, ED.salary + ED.salary*0.15 new_salary
from Employees E, EmployeeDetails ED
where E.jobTitle='cashier' and E.eid=ED.eid and ED.salary <= ALL (select EmployeeDetails.salary
					   from EmployeeDetails, Employees
					   where EmployeeDetails.eid=Employees.eid and Employees.jobTitle='cashier')
					   
--rewritten with min
select E.name, ED.salary as old_salary, ED.salary + ED.salary*0.15 new_salary
from Employees E, EmployeeDetails ED
where E.jobTitle='cashier' and E.eid=ED.eid and ED.salary <= (select min(EmployeeDetails.salary)
					   from EmployeeDetails, Employees
					   where EmployeeDetails.eid=Employees.eid and Employees.jobTitle='cashier')


--show the teas that have a limited stock(<5) so that when we place our next orders at the distributors
select T.tid, T.name, T.quantity
from Teas T
where T.tid<>ALL(select distinct Teas.tid
					 from Teas, TeaOrders
					 where Teas.quantity >= 5)

--rewritten with NOT IN
select T.tid, T.name, T.quantity
from Teas T
where T.tid not in (select distinct Teas.tid
					 from Teas, TeaOrders
					 where Teas.quantity >= 5)