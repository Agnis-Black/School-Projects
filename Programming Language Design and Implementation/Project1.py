# Name: Aqsa Arif
# Class: cs341
# UIN: 677417264
# UIC email: aarif20@uic.edu
#
# Project 1 : Analyzing CTA2 L data in Python
#

import sqlite3
import matplotlib.pyplot as plt


##################################################################  


# print_stats
# Given a connection to the CTA database, executes various
# SQL queries to retrieve and output basic stats.
def print_stats(dbConn):
  
    dbCursor = dbConn.cursor()
    
    print("General stats:")

  # Retrieve number of Stations
    dbCursor.execute("Select count(*) From Stations;")
    row = dbCursor.fetchone();
    print("  # of stations:", f"{row[0]:,}")

  # Retrieve number of Stops
    dbCursor.execute("Select count(*) From Stops;")
    row = dbCursor.fetchone();
    print("  # of stops:", f"{row[0]:,}")

  # Retrieve number of Ride entries
    dbCursor.execute("Select count(*) From Ridership;")
    row = dbCursor.fetchone();
    print("  # of ride entries:", f"{row[0]:,}")

  # Retrieve date range from ridership (2 parts)
  ################################################
  # retrieve starting date (part 1)
    sql = """Select date(Ride_Date) From Ridership 
             where Ride_Date like '20%%-%%-%%' 
             group by Ride_Date 
             order by Ride_Date asc;"""
    dbCursor.execute(sql)
    first = dbCursor.fetchone();
    print("  date range:", f"{first[0]:}", "- ", end="")

  # retieve last date (part 2)
    sql = """Select date(Ride_Date) From Ridership
              where Ride_Date like '20%%-%%-%%'
              group by Ride_Date
              order by Ride_Date desc;"""
    dbCursor.execute(sql)
    last = dbCursor.fetchone();
    print(f"{last[0]:}")
  ###################################################
  
  # Retrieve Total Ridership
    dbCursor.execute("Select sum(Num_Riders) From Ridership;")
    row = dbCursor.fetchone();
    print("  Total ridership:", f"{row[0]:,}")
    Total_Ridership = row[0]

  # Retrieve Weekday Ridership
    sql = """Select sum(Num_Riders) From Ridership
             where Type_of_Day = 'W';"""
    dbCursor.execute(sql)
    row = dbCursor.fetchone();
  # Evaluate percentage against total ridership and 
  # format to 2 decimal places
    percentage = (row[0]/Total_Ridership) * 100
    print("  Weekday ridership:", f"{row[0]:,}", 
          "(" + "{:.2f}".format(percentage) + "%)")

  # Retrieve Saturday Ridership
    sql = """Select sum(Num_Riders) From Ridership
             where Type_of_Day = 'A';"""
    dbCursor.execute(sql)
    row = dbCursor.fetchone();
  # Evaluate percentage against total ridership and 
  # format to 2 decimal places
    percentage = (row[0]/Total_Ridership) * 100
    print("  Saturday ridership:", f"{row[0]:,}", 
          "(" + "{:.2f}".format(percentage) + "%)")

  # Retrieve Sunday/holiday Ridership
    sql = """Select sum(Num_Riders) From Ridership
             where Type_of_Day = 'U';"""
    dbCursor.execute(sql)
    row = dbCursor.fetchone();
  # Evaluate percentage against total ridership and 
  # format to 2 decimal places
    percentage = (row[0]/Total_Ridership) * 100 
    print("  Sunday/holiday ridership:", f"{row[0]:,}", 
          "(" + "{:.2f}".format(percentage) + "%)")


def command_one(): # function for command 1
  
  dbCursor = dbConn.cursor()
  
  # Take input from user
  print("\n")
  name = input("Enter partial station name (wildcards _ and %): " )
  
  # Compare user input name against SQL table
  # get Station ID and Station Name as tuple
  sql = """Select Station_ID, Station_Name 
             From Stations 
             where Station_Name like ? 
             group by Station_Name 
             order by Station_Name asc;"""
  
  # Match on SQL table and fetch all matching
  dbCursor.execute(sql, [name])
  row = dbCursor.fetchall()

  # determine any matching results and print accordingly
  # Error print when no matching station
  if len(row) == 0:
    
    print("**No stations found...")
    
  else:
    
    for data in row:
      # tuple formated as Station ID and Station name
      print(data[0], ":" , data[1])

def command_two(): # function for command 2
  
  dbCursor = dbConn.cursor()

  # Retrieve Total Ridership
  dbCursor.execute("Select sum(Num_Riders) From Ridership;")
  ridership = dbCursor.fetchone();
  Total_Ridership = ridership[0]
  
  print("** ridership all stations **")
  
  # Retrieve Station name and ridership at that Station
  # from database
  sql = """Select Station_Name, sum(Num_Riders) from Ridership
        join Stations on Ridership.Station_ID = Stations.Station_ID
        group by Stations.Station_Name
        order by Stations.Station_Name asc;"""
  
  # Find on SQL table and fetch all matching
  dbCursor.execute(sql)
  row = dbCursor.fetchall()

  # Evaluate percentage per station
  for data in row:
  # tuple row contains station name and ridership at that station
    percentage = (data[1]/Total_Ridership) * 100 
    print(data[0], ":" , f"{data[1]:,}", 
          "(" + "{:.2f}".format(percentage) + "%)")  
    

def command_three(): # function for command 3
  
  dbCursor = dbConn.cursor()

  # Retrieve Total Ridership
  dbCursor.execute("Select sum(Num_Riders) From Ridership;")
  ridership = dbCursor.fetchone();
  Total_Ridership = ridership[0]
  
  print("** top-10 stations **")
  
  # Retieve station name and ridership of that station 
  # from database
  sql = """Select Station_Name,sum(Num_Riders) from Ridership
        join Stations on Ridership.Station_ID = Stations.Station_ID
        group by Station_Name
        order by sum(Num_riders) desc
        limit 10;"""

  # Find on SQL table and fetch all matching
  dbCursor.execute(sql)
  row = dbCursor.fetchall()

  # Evaluate percentage of total ridership per station
  for data in row:
  # tuple row contains station name and ridership of that station
    percentage = (data[1]/Total_Ridership) * 100 
    print(data[0], ":" , f"{data[1]:,}", 
          "(" + "{:.2f}".format(percentage) + "%)")  
    
def command_four(): # function for command 4

  dbCursor = dbConn.cursor()

  # Retrieve Total Ridership
  dbCursor.execute("Select sum(Num_Riders) From Ridership;")
  ridership = dbCursor.fetchone();
  Total_Ridership = ridership[0]
  
  print("** least-10 stations **")
  
  # Retrieve station name and ridership of that station
  # from database
  sql = """Select Station_Name,sum(Num_Riders) from Ridership
        join Stations on Ridership.Station_ID = Stations.Station_ID
        group by Station_Name
        order by sum(Num_riders) asc
        limit 10;"""

  # Find on SQL table and fetch all matching
  dbCursor.execute(sql)
  row = dbCursor.fetchall()

  # Evaluate percentage per station
  for data in row:
  # tuple row contains station name and ridership
    percentage = (data[1]/Total_Ridership) * 100 
    print(data[0], ":" , f"{data[1]:,}", 
          "(" + "{:.2f}".format(percentage) + "%)")

def command_five(): # function for command 5
  
  dbCursor = dbConn.cursor()
  
  # Get color input from user to use in query
  color = input("\nEnter a line color (e.g. Red or Yellow): " )
  
  # Retieve stop name, directions it travels, and whether
  # the station is disability accessible
  sql = """Select distinct Stop_Name, Direction, ADA from Stops
           join StopDetails on Stops.Stop_ID = StopDetails.Stop_ID
           join Lines on StopDetails.Line_ID = Lines.Line_ID 
           where Lines.Color like ?
           group by Stop_Name
           order by Stop_Name asc;"""

  # Find on SQL table and fetch all matching
  dbCursor.execute(sql,[color])
  row = dbCursor.fetchall()
  
  # Format Stop station, direction, and disability access
  if len(row) == 0:
    
    # initial error check if color inputed exists
    print("**No such line...")
    
  else:
    
    for data in row:

      # tuple row contains stop name, direction it travels, and 
      # disability accessibility in that order
      if (data[2] == 1):
        
        print(data[0], ": direction =" , 
              data[1], "(accessible? yes)")
        
      elif (data[2] == 0):
        
        print(data[0], ": direction =" , 
              data[1], "(accessible? no)")

def command_six(): # function for command 6
  
  dbCursor = dbConn.cursor()
  
  print("** ridership by month **")
  
  # Retrieve ridership by month
  sql = """Select strftime('%m', Ride_Date) as month, 
        sum(Num_Riders) from Ridership
        group by month
        order by month asc;"""
  
  # Find on SQL table and fetch all matching
  dbCursor.execute(sql)
  row = dbCursor.fetchall()

  # tuple row contains month and ridership within that month
  for data in row:
    print(data[0], ":" , f"{data[1]:,}")

  # ask user if they wish to plot information
  # if user inputs anything besides 'y' just skip 
  plot = input("Plot? (y/n)")
  if (plot == "y"):
    x = []
    y = []
    # x-axis will be a list containing months
    # y-axis will be a list containing riderships
    for data in row: 
      x.append(data[0])
      y.append(data[1])

    # formatting graph for desired output
    plt.xlabel("month")
    plt.ylabel("number of riders (x *10^8)")
    plt.title("monthly ridership")
    plt.plot(x, y)
    plt.show()
    
def command_seven(): # function for command 7
  
  dbCursor = dbConn.cursor()
  
  print("** ridership by year **")
  
  # retrieve year and ridership within that year from database
  sql = """Select strftime('%Y', Ride_Date) as year, 
        sum(Num_Riders) from Ridership
        group by year
        order by year asc;"""
  
  # Find on SQL table and fetch all matching
  dbCursor.execute(sql)
  row = dbCursor.fetchall()

  # tuple row contains year and ridership respectively
  for data in row:
    print(data[0], ":" , f"{data[1]:,}")

  # ask user if they wish to plot information
  # if user inputs anything besides 'y' just skip 
  plot = input("Plot? (y/n)")
  if (plot == "y"):
    x = []
    y = []

    # x-axis conatins last two digits of year, the year is sliced
    # to obtain desired string
    # y-axis contains total ridership in that year
    for data in row: 
      slice = data[0]
      x.append(slice[2:4])
      y.append(data[1])

    # format graph for desired result
    plt.xlabel("year")
    plt.ylabel("number of riders (x *10^8)")
    plt.title("yearly ridership")
    plt.plot(x, y)
    plt.show()

def command_eight(): # function for command 8
  
  dbCursor = dbConn.cursor()

  # ask user for year and the first station they want to 
  # look up
  year = input("\nYear to compare against? ")
  station_one = input("\nEnter station 1 (wildcards _ and %): ")
  
  # retrieve the date, the number of riders on that day,
  # the station's ID, and the station's name from database
  sql = """Select date(Ride_Date), Num_Riders,     
        Stations.Station_ID, Stations.Station_Name from Ridership
        join Stations on Ridership.Station_ID = Stations.Station_ID
        where Stations.Station_Name like ? and 
        strftime('%Y', Ride_Date) like ?
        order by date(Ride_Date) asc;"""

  dbCursor.execute(sql,[station_one, year])
  row = dbCursor.fetchall()

  # this initial check is for the first station input by user
  if len(row) == 0:
    
    print("**No station found...")

  # if there are too many matching stations error check
  elif len(row) > 366:
    
    print("**Multiple stations found...")
    
  else:

    # if station one checks out same process is repeated
    # with station two
    station_two = input("\nEnter station 2 (wildcards _ and %): ")
    
    # retrieve the date, the number of riders on that day,
    # the station's ID, and the station's name from database
    sql2 = """Select date(Ride_Date), Num_Riders,     
          Stations.Station_ID, Stations.Station_Name from Ridership
          join Stations on Ridership.Station_ID =   
          Stations.Station_ID
          where Stations.Station_Name like ? and 
          strftime('%Y', Ride_Date) = ? 
          order by date(Ride_Date) asc;"""
    
    dbCursor.execute(sql2,[station_two, year])
    row2 = dbCursor.fetchall()

    # this is the secondary check for the 2nd station input by user
    if len(row2) == 0:
      
      print("**No station found...")

    elif len(row2) > 366:
      
      print("**Multiple stations found...")
    
    else: 
      
      # if both station names pass all checks 
      # proceed to process tuple information
      
      # These two strings serve as string containers to pass 
      # formating errors
      station_one_name = ""
      station_two_name = ""

      # Station 1 printing
      ########################################################
      for data in row[0:1]:
        # tuple contains station ID and station name
        station_one_name = data[3]
        print("Station 1:", data[2], data[3])
    
      for data in row[0:5]:
        # tuple contains first 5 rows of dates and riderships
        print(data[0] , data[1])
    
      for data in row[-5:]:
        # tuple contains last 5 rows of dates and riderships
        print(data[0] , data[1])
      ###########################################################

      # Station 2 printing
      ###########################################################
      for data in row2[0:1]:
        # tuple contains station ID and station name
        station_two_name = data[3]
        print("Station 2:", data[2], data[3])
        
      for data in row2[0:5]:
        # tuple contains first 5 rows of dates and riderships
        print(data[0] , data[1])
        
      for data in row2[-5:]:
        # tuple contains last 5 rows of dates and riderships
        print(data[0] , data[1])
      ############################################################

      # ask user if they wish to plot information
      # if user inputs anything besides 'y' just skip 
      plot = input("\nPlot? (y/n)")
      if (plot == "y"):
        x = []
        y = []
        y2 = []
        day = 1

        # for loop transfers data for ridership into a list for y-axis
        # from first station
        for data in row:
          x.append(day)
          y.append(data[1])
          day = day + 1

        # for loop transfers data for ridership into a list for y-axis
        # from second station
        for data in row2:
          y2.append(data[1])

        # format graph for desired result
        plt.xlabel("day")
        plt.ylabel("number of riders")
        # specify title to desired year
        plt.title("riders each day of " + year)
        # plot 2 graph lines to compare ridership between
        # stations
        plt.plot(x, y)
        plt.plot(x, y2)
        plt.legend([station_one_name, station_two_name])
        plt.show()
      

def command_nine(): # function for command 9
  
  dbCursor = dbConn.cursor()

  # get line color from user
  color = input("\nEnter a line color (e.g. Red or Yellow): " )
  
  # retrieve station name, latitude, and longitude from database
  sql = """Select distinct Stations.Station_Name, Latitude, 
           Longitude from Stops
           join Stations on Stops.Station_ID = Stations.Station_ID
           join StopDetails on Stops.Stop_ID = StopDetails.Stop_ID
           join Lines on StopDetails.Line_ID = Lines.Line_ID 
           where Lines.Color like ?
           group by Stations.Station_Name
           order by Stations.Station_Name asc;"""

  # Find on SQL table and fetch all matching
  dbCursor.execute(sql,[color])
  row = dbCursor.fetchall()
  
  # Error check to see if color exists
  if len(row) == 0:
    
    print("**No such line...")
    
  else:

    # if line color exists the print station name and it's 
    # geographical location
    for data in row:
      
      print(data[0]+ " : " + 
            "(" + str(data[1]) + ", " + str(data[2]) + ")" )

    # ask user if they wish to plot information
    # if user inputs anything besides 'y' just skip 
    plot = input("\nPlot? (y/n)")
    if (plot == "y"):
      x = []
      y = []
      
      for data in row: 
        x.append(data[2])
        y.append(data[1])
        
      image = plt.imread("chicago.png")
      
      # area covered by the map:
      xydims = [-87.9277, -87.5569, 41.7012, 42.0868] 
      plt.imshow(image, extent=xydims)
      
      # formating title for specifc color line
      plt.title(color + " line")

      # specifying purple line
      if (color.lower() == "purple-express"):
       color="Purple" # color="#800080"
        
      plt.plot(x, y, "o", c=color)
      
      for data in row:
        # tuple contains station name with geographical coordinates
        plt.annotate(data[0], (data[2],data[1]) )
        
      plt.xlim([-87.9277, -87.5569])
      plt.ylim([41.7012, 42.0868])
      plt.show()
  
def switch(case): 
# function that acts as switch case between inputs 1-9
  if case == "1":
    command_one()

  elif case == "2":
    command_two()

  elif case == "3":
    command_three()

  elif case == "4":
    command_four()

  elif case == "5":
    command_five()

  elif case == "6":
    command_six()

  elif case == "7":
    command_seven()

  elif case == "8":
    command_eight()

  elif case == "9":
    command_nine()
    
  else:
    print("**Error, unknown command, try again...")




##############################################################
# main
print('** Welcome to CTA L analysis app **')
print()

dbConn = sqlite3.connect('CTA2_L_daily_ridership.db')

print_stats(dbConn)

# Take input from user and switch cases accordingly
# loop cases until exit button x

case = input("\nPlease enter a command (1-9, x to exit): ")

while(case != "x"):
  switch(case)
  case = input("\nPlease enter a command (1-9, x to exit): ")

#
# done
#