.open CTA2_L_daily_ridership.db


select distinct Color from Lines
join StopDetails on Lines.Line_ID = StopDetails.Line_ID
join Stops on StopDetails.Stop_ID = Stops.Stop_ID  
join Stations on Stops.Station_ID = Stations.Station_ID
where Station_Name = 'Belmont-North Main'
group by Color
order by Color asc
