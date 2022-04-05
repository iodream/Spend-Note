/* CREATE DATABASE moved to database-setup.sh */

create table User_
(
	id bigint generated by default as identity primary key,
	login varchar(15) not null unique,
	password character(40) not null
);

create table IncomeCategory
(
   	id bigint generated by default as identity primary key,
	name varchar(30) not null,
	userId bigint not null references User_(id) on delete cascade
);

create table Income
(
	id bigint generated by default as identity primary key,
	name varchar(30) not null,
	userId bigint not null references User_(id) on delete cascade,
	amount bigint not null,
	categoryId bigint not null references IncomeCategory(id),
	addTime timestamp not null,
	expirationTime timestamp
);

create table ListState
(
	id bigint generated by default as identity primary key,
	name varchar(30) not null unique 
);

create table List
(
	id bigint generated by default as identity primary key,
	userId bigint not null references User_(id) on delete cascade,
	name varchar(30) not null,
	stateId bigint not null references ListState(id)
);

create table Coownership
(
	userId bigint references User_(id) on delete cascade,
	listId bigint references List(id) on delete cascade,
	primary key(userId, listId)
);

create table ProductCategory
(
    id bigint generated by default as identity primary key,
	userId bigint not null references User_(id) on delete cascade,
	name varchar(30) not null
);

create table Product
(
	id bigint generated by default as identity primary key,
	listId bigint not null references List(id) on delete cascade,
	categoryId bigint not null references ProductCategory(id),
	name varchar(30) not null,
	price bigint not null,
	amount bigint not null,
	productPriority integer not null,
	isBought boolean not null,
	addDate timestamp not null,
	purchaseDate timestamp,
	buyUntilDate timestamp
);

