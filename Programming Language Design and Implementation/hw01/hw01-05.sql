.open CTA_L_daily_ridership.db
select sum(Num_Riders) from Ridership
where Station_ID = (select Station_ID from Stations where Station_Name = 'UIC-Halsted'and date(Ride_Date) between '2019' and '2020')

--select sum(Num_Riders) from Ridership
--where Station_ID = (select Station_ID from Stations where Station_Name = 'UIC-Halsted'and date(Ride_Date) between '2020' and '2021')