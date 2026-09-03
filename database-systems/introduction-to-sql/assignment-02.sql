-- Section1
select case
               when Total_Spent > 15 then 'high'
               when Total_Spent between 5 and 15 then 'medium'
               when Total_Spent < 5 then 'low'
        end as category,
        count(*) as num_tx
        from cafe_sales
        where Total_Spent is not null
    group by
        case
               when Total_Spent > 15 then 'high'
               when Total_Spent between 5 and 15 then 'medium'
               when Total_Spent < 5 then 'low'
       end;
-- Section2
with avg_item as (
    select
        Item, avg(Quantity) over (partition by Item) as avg_quantity, Quantity, Total_Spent, Payment_Method
    from cafe_sales
    )
    select Item, sum(Total_Spent) as Total_Spent_Cash
        from avg_item
            where Payment_Method = 'Cash'
            and Quantity > avg_quantity
        group by Item order by Total_Spent_Cash desc limit 5;
-- Section3
select Payment_Method, count(*) as num_tx, sum(Total_Spent) as total_sales
    from cafe_sales
    where Payment_Method is not null and Total_Spent is not null
        group by Payment_Method
        having  num_tx > 2000;
-- Section4
select Transaction_ID, Item, Total_Spent
    from cafe_sales
    where Total_Spent > (select avg(Total_Spent) from cafe_sales);
-- Section5
select Transaction_ID, Item, Total_Spent
    from cafe_sales
    where (Item like '%Cake%' or Item like '%Cookie%')
    and Transaction_Date between '2023-06-01' and '2023-06-30';
-- Section6
select Item, sum(Total_spent) as total_revenue
    from cafe_sales
    group by Item order by total_revenue desc limit 3;

