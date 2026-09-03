
-- Section1
select t1.name, t1.yearID, round((t1.W * 1.0 / (t1.W + t1.L)) -(t2.W * 1.0 / (t2.W + t2.L)), 3) as improvement
from Teams t1
    join Teams t2 on t1.name = t2.name and t1.yearID = t2.yearID + 1
    having improvement > 0.05
    order by improvement desc, t1.name asc;
-- Section2
select yearID
from Teams
group by yearID
    having sum(
           case
               when W > L then 1
               else 0
           end
           )  > count(*) / 2
order by yearID;
-- Section3
select t2.name, t2.yearID, t2.R, round((t2.R - (select avg(t.R)
                              from Teams t
                              where t.yearID = t2.yearID)), 1) as diff_from_year_avg
from Teams t2
order by diff_from_year_avg desc limit 10;
-- Section4
select name, yearID, (R - RA) as run_diff
from Teams
group by name, yearID, R, RA
    having run_diff > (select avg(R - RA)
                       from Teams t
                       where t.yearID = Teams.yearID)
order by run_diff desc, name desc, yearID desc;