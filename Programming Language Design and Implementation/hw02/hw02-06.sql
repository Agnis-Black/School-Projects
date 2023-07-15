.open CTA2_L_daily_ridership.db

select Station_Name, count(Stops.Station_ID) from Stations
inner join Stops on Stations.Station_ID = Stops.Station_ID
group by Station_Name
