#
# objecttier
#
# Builds objects from data retrieved through the data tier.
#
# Original author:
#   Prof. Joe Hummel
#   U. of Illinois, Chicago
#   CS 341, Spring 2022
#
import datatier
#
# do not import other modules
#

########################################################
#
# Station:
#
# Constructor(...)
# Properties:
#   Station_ID: int
#   Station_Name: string
#   Ridership: int
#   Percent_Ridership: float
#
class Station:

  Station_ID = 0
  Station_Name = ""
  Ridership = 0
  Percent_Ridership = 0.0

  # parameterized constructor
  def __init__(self, id, name, ridership,total_ridership):
    self.Station_ID = id
    self.Station_Name = name
    self.Ridership = ridership
    self.Percent_Ridership = (ridership/total_ridership) * 100

########################################################
#
# Stop:
#
# Constructor(...)
# Properties:
#   Stop_ID: int
#   Stop_Name: string
#   Direction: string
#   Accessible: boolean (True/False)
#   Latitude: float
#   Longitude: float
#   Lines: list of strings
#
class Stop:
  Stop_ID = 0
  Stop_Name = ""
  Direction = ""
  Accessible = False
  Latitude = 0.0
  Longitude = 0.0
  Lines = []
  
  # parameterized constructor
  def __init__(self, id, name, direction, access, lat, long, colors):
    self.Stop_ID = id
    self.Stop_Name = name
    self.Direction = direction
    self.Accessible = access
    self.Latitude = lat
    self.Longitude = long
    #print()
    #print(colors)
    #print("we start again")
    #self.Lines.clear()
    self.Lines = []
    for c in colors:
      #self.Lines.append(c)
      #print(type(c[0]))
      #print(c[0])
      self.Lines.append(c[0])

    #print("we out")
    
    
    
    


########################################################
#
# get_stations:
#
# gets and returns all stations whose name are "like"
# the pattern. Patterns are based on SQL, which allow
# the _ and % wildcards. Pass "%" to get all stations.
#
# Returns: list of stations in ascending order by name;
#          returns None if an error occurs.
#
def get_stations(dbConn, pattern):

  sql = """Select Stations.Station_ID, Station_Name, sum(Num_Riders) 
           From Stations 
           join Ridership on Stations.Station_ID = Ridership.Station_ID
           where Stations.Station_Name like ?
           group by Stations.Station_Name
           order by Stations.Station_Name asc;"""
  
  rows = datatier.select_n_rows(dbConn, sql, [pattern])
  if rows is None:
    return []

  ridership_sql = """Select sum(Num_Riders) From Ridership;"""
  riders = datatier.select_one_row(dbConn,ridership_sql)
  total_ridership = riders[0]
  
  S = []
  for row in rows:
    one = Station(row[0], row[1], row[2],total_ridership)
    S.append(one)
  
  return S;


########################################################
#
# get_stops:
#
# gets and returns all stops at a given station; the 
# given station name must match exactly (no wildcards).
# If there is no match, an empty list is returned.
#
# Returns: a list of stops in ascending order by name,
#          then in ascending order by id if two stops
#          have the same name; returns None if an error
#          occurs.
#
def get_stops(dbConn, name):


  # Stop_ID: int
#   Stop_Name: string
#   Direction: string
#   Accessible: boolean (True/False)
#   Latitude: float
#   Longitude: float
#   Lines: list of strings

  sql = """Select distinct Stops.Stop_ID, Stops.Stop_Name, 
           Stops.Direction, Stops.ADA, Stops.Latitude, Stops.Longitude             From Stations
           join Stops on Stations.Station_ID = Stops.Station_ID
           join StopDetails on Stops.Stop_ID = StopDetails.Stop_ID
           where Stations.Station_Name = ?
           group by Stops.Stop_ID
           order by Stops.Stop_Name asc;"""
  
  rows = datatier.select_n_rows(dbConn, sql, [name])
  if rows is None:
    return []

  S = []

  color_sql = """Select color from Lines
                join StopDetails on Lines.Line_ID =
                StopDetails.Line_ID
                where StopDetails.Stop_ID = ?
                group by color;"""

  for row in rows:
    color = datatier.select_n_rows(dbConn,color_sql,[row[0]])
    one = Stop(row[0], row[1], row[2], row[3], row[4], row[5], color)
    S.append(one)

  
  return S;

