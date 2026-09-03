
-- Section1
alter table IBM_Stock add column id bigint
    primary key not null auto_increment;
-- Section2
    select count(distinct Date) as trade_days
    from IBM_Stock;
-- Section3
    select Date from IBM_Stock
    group by Date having count(*) > 1;
-- Section4
    select Date, case
                        when Close > Open then 'green'
                        when Close < Open then 'red'
                    else 'gray'
        end as color, Volume
        from IBM_Stock
    order by Date;
-- Section5
    select i1.Date, i1.Close as closing_price,
           ( select avg(i2.Close)
                from IBM_Stock i2
                    where i2.Date between i1.Date - interval 6 day and i1.Date ) as moving_avg_7
    from IBM_Stock i1
order by i1.Date;