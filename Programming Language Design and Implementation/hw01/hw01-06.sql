.open CTA_L_daily_ridership.db
select date(Ride_Date), sum(Num_Riders) from Ridership
where Ride_Date like '20%%-07-04%' and Ride_Date between '2016' and '2022'
group by Ride_Date
order by Ride_Date desc