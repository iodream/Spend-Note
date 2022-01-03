CREATE DATABASE SpendAndNote
USE SpendAndNote

CREATE TABLE IncomeCategory
(
	id bigint primary key,
	name character(30) not null unique
)

CREATE TABLE User_
(
	id bigint primary key,
	login character(15) not null unique,
	password character(40) not null
)

CREATE TABLE Income
(
	id bigint primary key,
	name character not null,
	userId bigint not null references User_(id),
	amount money not null,
	categoryId bigint not null references IncomeCategory(id),
	addTime timestamp not null,
	expirationTime timestamp
)

CREATE TABLE ListState
(
	id bigint primary key,
	name character(30) not null unique 
)

CREATE TABLE List
(
	id bigint primary key,
	userId bigint not null references User_(id),
	name character(30) not null,
	stateId bigint not null references ListState(id)
)

CREATE TABLE Coownership
(
	userId bigint not null unique references User_(id),
	listId bigint not null unique references List(id)
)

CREATE TABLE ProductCategory
(
	id bigint primary key,
	name haracter(30) not null unique 
)

CREATE TABLE Product
(
	id bigint primary key,
	listId bigint not null unique references List(id),
	categoryId bigint not null unique references ProductCategory(id),
	name haracter(30) not null,
	price money not null,
	amount bigint not null,
	productPriority integer not null,
	isBought boolean not null,
	addDate timestamp not null,
	purchaseDate timestamp,
	buyUntilDate timestamp
)