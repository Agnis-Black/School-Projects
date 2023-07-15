.open CTA2_L_daily_ridership.db

select Stop_ID, Stop_Name from Stops
join Stations on Stops.Station_ID = Stations.Station_ID
where Station_Name = 'Belmont-North Main'
group by Stop_Name
order by Stop_Name asc
