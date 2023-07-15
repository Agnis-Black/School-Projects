.open CTA2_L_daily_ridership.db

select strftime('%Y', Ride_Date) as year,sum(Num_Riders) from Ridership
where year between '2011' and '2020'
group by year
order by year desc