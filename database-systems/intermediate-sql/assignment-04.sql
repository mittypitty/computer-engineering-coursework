-- Section1
    with lasttransaction as (
    select u.user_id, u.name, a.balance as current_balance,
        case
            when t.to_account_id = a.account_id then t.amount
            when t.from_account_id = a.account_id then -t.amount
        end as transaction_impact,
        row_number() over (
            partition by u.user_id
            order by t.created_at desc, t.transaction_id desc
        ) as rn
    from users u
    join accounts a on u.user_id = a.user_id
    join transactions t on a.account_id = t.from_account_id
                         or a.account_id = t.to_account_id
    where t.status = 'success'
)
select u.user_id, u.name,
    coalesce(lt.current_balance - lt.transaction_impact, a.balance) as old_balance,
    coalesce(lt.current_balance, a.balance) as new_balance,
    round(coalesce((lt.transaction_impact / nullif(lt.current_balance - lt.transaction_impact, 0)) * 100, 0), 2) as change_percent
from users u
join accounts a on u.user_id = a.user_id
left join lasttransaction lt on u.user_id = lt.user_id and lt.rn = 1
order by u.user_id;
-- Section2
    select type, count(*) as transaction_count
    from transactions
    group by type
    order by transaction_count desc;
-- Section3
    with user_avgs as (
      select u.user_id, u.name, round(avg(t.amount), 2) as avg_user_amount
      from users u
      join accounts a on a.user_id = u.user_id
      join transactions t on (t.from_account_id = a.account_id
                                or t.to_account_id = a.account_id)
      where t.status = 'success'
      group by u.user_id, u.name
    ),
    all_avg as (
      select AVG(avg_user_amount) as avg_all
      from user_avgs
    )
    select u.user_id, u.name, u.avg_user_amount
    from user_avgs u, all_avg a
    where u.avg_user_amount > a.avg_all
    order by u.avg_user_amount desc;
-- Section4
    select provider, users.user_id
    from payment_methods
    join users on payment_methods.user_id = users.user_id
    order by provider;