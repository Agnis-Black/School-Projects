.open CTA2_L_daily_ridership.db

select Station_Name,sum(Num_Riders) from Ridership
join Stations on Ridership.Station_ID = Stations.Station_ID
where Stations.Station_ID
group by Stations.Station_ID
order by sum(Num_Riders) desc
limit 10;