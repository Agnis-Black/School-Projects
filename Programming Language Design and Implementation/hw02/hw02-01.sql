.open CTA2_L_daily_ridership.db

select Station_ID,sum(Num_Riders) from Ridership
where Station_ID
group by Station_ID
order by sum(Num_Riders) desc
limit 10;
