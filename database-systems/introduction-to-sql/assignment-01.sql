
-- Section1
create table customers
(
    id       bigint unsigned auto_increment
        primary key,
    name     varchar(255) not null,
    family   varchar(255) not null,
    email    varchar(50) not null,
    password varchar(255) not null
)ENGINE=InnoDB;

create table items
(
    id                 bigint unsigned auto_increment
        primary key,
    name               varchar(255)   not null,
    type               varchar(255)   not null,
    price              decimal(10, 2) not null,
    available_quantity int            not null
) ENGINE=InnoDB;

-- Section2

create table sales
(
    customer_id bigint unsigned not null,
    item_id     bigint unsigned not null,
    datetime    timestamp not null default now(),
    foreign key (customer_id) references customers (id),
    foreign key (item_id) references items (id)
)ENGINE=InnoDB;

-- Section3
delete from customers
where id not in (
    select distinct sales.customer_id
    from sales
    where datetime >= CURDATE() - INTERVAL 365 DAY
    );

-- Section4
alter table sales add column items varchar(255);
update sales set items = item_id;

alter table sales drop foreign key sales_ibfk_2;
alter table sales drop column item_id;