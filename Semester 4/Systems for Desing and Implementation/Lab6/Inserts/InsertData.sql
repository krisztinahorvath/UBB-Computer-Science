use booksDB

--Authors
SET IDENTITY_INSERT Authors ON;

BULK INSERT Authors
FROM 'C:\Facultate\Semestrul 4\MPP\Labs\Lab6Faker\authors.csv'
WITH
(
    FIELDTERMINATOR = ',',
    ROWTERMINATOR = '\n',
    FIRSTROW = 1,
    BATCHSIZE = 1000,
	KEEPIDENTITY
);

SET IDENTITY_INSERT Authors OFF;

-- Genres
SET IDENTITY_INSERT Genres ON;

BULK INSERT Genres
FROM 'C:\Facultate\Semestrul 4\MPP\Labs\Lab6Faker\genres.csv'
WITH
(
    FIELDTERMINATOR = ',',
    ROWTERMINATOR = '\n',
    FIRSTROW = 1,
    BATCHSIZE = 1000, 
	KEEPIDENTITY
);

SET IDENTITY_INSERT Genres OFF;



-- Books
SET IDENTITY_INSERT Books ON;

BULK INSERT Books
FROM 'C:\Facultate\Semestrul 4\MPP\Labs\Lab6Faker\booksWDescription.csv'
WITH
(
    FIELDTERMINATOR = ',',
    ROWTERMINATOR = '\n',
    FIRSTROW = 1,
    BATCHSIZE = 1000, 
	KEEPIDENTITY
);

SET IDENTITY_INSERT Books OFF;


-- BookAuthors
BULK INSERT BookAuthors
FROM 'C:\Facultate\Semestrul 4\MPP\Labs\Lab6Faker\bookauthors.csv'
WITH
(
    FIELDTERMINATOR = ',',
    ROWTERMINATOR = '\n',
    FIRSTROW = 1,
    BATCHSIZE = 1000, 
	KEEPIDENTITY
);


select count(*) as NoOfGenres from Genres
select count(*) as NoOfBooks from Books
select count(*) as NoOfAuthors from Authors
select count(*) as NoOfBookAuthors from BookAuthors

select * from Genres
select * from Authors
select * from Books
select * from BookAuthors

select max(Id) from Authors

delete from  Books