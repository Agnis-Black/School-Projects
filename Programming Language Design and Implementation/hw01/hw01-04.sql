.open CTA_L_daily_ridership.db
select sum(Num_Riders) from Ridership
where Station_ID = 40190 and date(Ride_Date) between '2005-01-01' and '2005-12-31'