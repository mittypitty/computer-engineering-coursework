-- Section1
    select Orders.order_id, Orders.customer_id, Orders.order_date
    from Orders
    where not exists(
        select 1
        from OrderItem
        where OrderItem.order_id = Orders.order_id
    )
    order by Orders.order_id;
-- Section2
    select Orders.order_id, coalesce(sum(OrderItem.quantity * OrderItem.order_item_unit_price), 0) as total_revenue
    from Orders
        left join OrderItem on Orders.order_id = OrderItem.order_id
    group by Orders.order_id order by total_revenue desc;
-- Section3
    select c.customer_id, c.name, c.email
    from Customer c
    where not exists(
        select p.product_id
        from Product p
        join Category on p.category_id = Category.category_id
        where Category.name = 'English Books' and p.product_id not in (
            select OrderItem.product_id
            from Orders
            join OrderItem on Orders.order_id = OrderItem.order_id
            where Orders.customer_id = c.customer_id
            )
    );
-- Section4
    with recursive hierarchy as (
    select c1.category_id, c1.parent_id, c1.name, c1.name as full_path
    from Category c1
    where c1.parent_id is null
    union all
    select c2.category_id, c2.parent_id, c2.name, concat(parent.full_path,' > ',c2.name) as full_path
    from Category c2
    join hierarchy parent on c2.parent_id = parent.category_id
    )
    select category_id, parent_id, name, full_path
    from hierarchy;
-- Section5
select extract(year from Orders.order_date) as order_year,
       extract(month from Orders.order_date) as order_month,
       sum(OrderItem.quantity * OrderItem.order_item_unit_price) as monthly_revenue
from Orders
    join OrderItem on Orders.order_id = OrderItem.order_id
group by extract(year from Orders.order_date), extract(month from Orders.order_date)
order by monthly_revenue desc limit 10;



