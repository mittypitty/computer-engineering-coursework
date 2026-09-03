-- Section1
select s.student_id, s.name as student_name, round(avg(e.grade), 2) as gpa
from student s
join enrollment e on s.student_id = e.student_id
group by s.student_id, s.name
order by gpa desc limit 5;
-- Section2
select prof_id, name, total_students
from (
  select p.prof_id, p.name, count(e.student_id) as total_students,
    row_number() over (order by count(e.student_id) desc) as rn
  from professor p
  join course c on p.prof_id = c.prof_id
  join enrollment e on c.course_id = e.course_id
  group by p.prof_id, p.name
) ranked
where rn between 4 and 6;

-- Section3
select c.course_id, c.title, d.dept_name, avg(case when e.grade >= 10 then e.grade end) as average_grade
from course c
join department d on c.dept_id = d.dept_id
join enrollment e on c.course_id = e.course_id
where e.grade >= 10
group by c.course_id, c.title, d.dept_name
having avg(case when e.grade >= 10 then e.grade end) >= 14.5
order by average_grade desc;

-- Section4
select s.student_id, c.title as course_title, s.name, e.grade as current_score, least(e.grade + 1, 20) as new_score
from enrollment e
join student s on e.student_id = s.student_id
join course c on e.course_id = c.course_id
join professor p on c.prof_id = p.prof_id
join department d_p on p.dept_id = d_p.dept_id
join department d_s on s.dept_id = d_s.dept_id
where lower(trim(d_p.dept_name)) = 'computer science'
order by new_score desc, current_score desc, s.name, c.title;