-- Section1
    with international_departures as (
        select f.source_id as airport_id, count(*) as international_connections
        from flight f
        join airport src on src.airport_id = f.source_id
        join airport dst on dst.airport_id = f.dest_id
        where src.country <> dst.country
        group by f.source_id
    )
    select ap.airport_id, ap.name as airport_name, ap.country, idp.international_connections
    from international_departures idp
    join airport ap on ap.airport_id = idp.airport_id
    order by idp.international_connections desc limit 1;
-- Section2
    select
    a.name as airline_name, count(distinct s.country) as total_countries
    from Flight f
    join Airline a on f.airline_id = a.airline_id
    join Airport s on f.source_id = s.airport_id
    group by a.name
    having count(distinct s.country) > 22
    order by total_countries desc, a.name;
-- Section3
    with delayedflights as (
    select f.airline_id, timestampdiff(minute, f.scheduled_departure, f.actual_departure) as delay_minutes
    from flight f
    where f.actual_departure is not null
            and f.actual_departure > f.scheduled_departure
    )
    select a.airline_id, a.name as airline_name, round(avg(df.delay_minutes), 2) as avg_delay_minutes
    from delayedflights df
    join airline a on df.airline_id = a.airline_id
    group by a.airline_id, a.name
    order by avg_delay_minutes limit 3;
-- Section4
    with departures as (
        select source_id as airport_id, count(*) as total_departures
        from flight
        group by source_id
    ), arrivals as (
        select dest_id as airport_id, count(*) as total_arrivals
        from flight
        group by dest_id
    )
    select ap.airport_id, ap.name as airport_name, d.total_departures, a.total_arrivals
    from departures d
    join arrivals a on d.airport_id = a.airport_id
    join airport ap on ap.airport_id = d.airport_id
    order by (d.total_departures + a.total_arrivals) desc, ap.name;
