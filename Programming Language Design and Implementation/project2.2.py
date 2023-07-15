#
# File: objecttier.py
#
# Builds Movie-related objects from data retrieved through 
# the data tier.
#
# Original author:
#   Prof. Joe Hummel
#   U. of Illinois, Chicago
#   CS 341, Spring 2022
#   Project #02
#
import datatier


##################################################################
#
# Movie:
#
# Constructor(...)
# Properties:
#   Movie_ID: int
#   Title: string
#   Release_Year: string
#
class Movie:
  Movie_ID = 0
  Title = ""
  Release_Year = ""

  def __init__(self, id, name, year):
    self._Movie_ID = id
    self._Title = name
    self._Release_Year = year

  @property
  def Movie_ID(self):
    return self._Movie_ID

  @property
  def Title(self):
    return self._Title

  @property
  def Release_Year(self):
    return self._Release_Year



##################################################################
#
# MovieRating:
#
# Constructor(...)
# Properties:
#   Movie_ID: int
#   Title: string
#   Release_Year: string
#   Num_Reviews: int
#   Avg_Rating: float
#
class MovieRating:
  Movie_ID = 0
  Title = ""
  Release_Year = ""
  Num_Reviews = 0
  Avg_Rating = 0.0

  def __init__(self, id, name, year, reviews, rating):
    self._Movie_ID = id
    self._Title = name
    self._Release_Year = year
    self._Num_Reviews = reviews
    self._Avg_Rating = rating

  @property
  def Movie_ID(self):
    return self._Movie_ID

  @property
  def Title(self):
    return self._Title
    
  @property
  def Release_Year(self):
    return self._Release_Year

  @property
  def Num_Reviews(self):
    return self._Num_Reviews

  @property
  def Avg_Rating(self):
    return self._Avg_Rating
  


##################################################################
#
# MovieDetails:
#
# Constructor(...)
# Properties:
#   Movie_ID: int
#   Title: string
#   Release_Date: string, date only (no time)
#   Runtime: int (minutes)
#   Original_Language: string
#   Budget: int (USD)
#   Revenue: int (USD)
#   Num_Reviews: int
#   Avg_Rating: float
#   Tagline: string
#   Genres: list of string
#   Production_Companies: list of string
#
class MovieDetails:
  Movie_ID = 0
  Title = ""
  Release_Date = ""
  Runtime = 0
  Original_Language = ""
  Budget = 0
  Revenue = 0
  Num_Reviews = 0
  Avg_Rating = 0.0
  Tagline = ""
  Genres = []
  Production_Companies = []

  def __init__(self, id, name, date, runtime, language, budget,
               revenue, reviews, rating, tag, genre_list,
               companies_list):
                 self._Movie_ID = id
                 self._Title = name
                 self._Release_Date = date
                 self._Runtime = runtime
                 self._Original_Language = language
                 self._Budget = budget
                 self._Revenue = revenue
                 self._Num_Reviews = reviews
                 self._Avg_Rating = rating
                 self._Tagline = tag
                 self._Genres = genre_list
                 self._Production_Companies = companies_list

  @property
  def Movie_ID(self):
    return self._Movie_ID

  @property
  def Title(self):
    return self._Title
    
  @property
  def Release_Date(self):
    return self._Release_Date

  @property
  def Runtime(self):
    return self._Runtime

  @property
  def Original_Language(self):
    return self._Original_Language

  @property
  def Budget(self):
    return self._Budget

  @property
  def Revenue(self):
    return self._Revenue

  @property
  def Num_Reviews(self):
    return self._Num_Reviews

  @property
  def Avg_Rating(self):
    return self._Avg_Rating

  @property
  def Tagline(self):
    return self._Tagline

  @property
  def Genres(self):
    return self._Genres

  @property
  def Production_Companies(self):
    return self._Production_Companies
    

##################################################################
# 
# num_movies:
#
# Returns: # of movies in the database; if an error returns -1
#
def num_movies(dbConn):

  sql = """Select distinct count(Movie_Id) From Movies"""
  
  row = datatier.select_one_row(dbConn, sql)
  
  if row is None:
    return -1
    
  num_movies = row[0]

  return num_movies
  
  


##################################################################
# 
# num_reviews:
#
# Returns: # of reviews in the database; if an error returns -1
#
def num_reviews(dbConn):
  
  sql = """Select count(Rating) From Ratings"""
  
  row = datatier.select_one_row(dbConn, sql)
  
  if row is None:
    return -1
    
  num_rating = row[0]

  return num_rating


##################################################################
#
# get_movies:
#
# gets and returns all movies whose name are "like"
# the pattern. Patterns are based on SQL, which allow
# the _ and % wildcards. Pass "%" to get all stations.
#
# Returns: list of movies in ascending order by name; 
#          an empty list means the query did not retrieve
#          any data (or an internal error occurred, in
#          which case an error msg is already output).
#
def get_movies(dbConn, pattern):
  
  sql = """Select Movie_ID, Title, strftime('%Y', Release_Date) as Year
           From Movies 
           where Title like ?
           order by Title asc;"""
  
  rows = datatier.select_n_rows(dbConn, sql, [pattern])

  movie_list = []
  
  for row in rows:
    
    one = Movie(row[0], row[1], row[2])
    
    movie_list.append(one)
  
  return movie_list;



##################################################################
#
# get_movie_details:
#
# gets and returns details about the given movie; you pass
# the movie id, function returns a MovieDetails object. Returns
# None if no movie was found with this id.
#
# Returns: if the search was successful, a MovieDetails obj
#          is returned. If the search did not find a matching
#          movie, None is returned; note that None is also 
#          returned if an internal error occurred (in which
#          case an error msg is already output).
#
def get_movie_details(dbConn, movie_id):
  
  sql1 = """Select Movies.Movie_ID, Title, date(Release_Date), Runtime,
           Original_Language, Budget, Revenue,
           count(Ratings.Movie_ID), avg(Ratings.Rating),
           Movie_Taglines.Tagline From Movies
           Left Join Ratings on 
           Movies.Movie_ID = Ratings.Movie_ID
           Left Join Movie_Taglines on 
           Movies.Movie_ID = Movie_Taglines.Movie_ID
           where Movies.Movie_ID = ?;"""

  sql2 = """Select Genres.Genre_Name From Movie_Genres
          Join Genres on Movie_Genres.Genre_ID = Genres.Genre_ID
          where Movie_Genres.Movie_ID = ?
          order by Genres.Genre_Name asc;"""
  
  sql3 = """Select Companies.Company_Name
          From Movie_Production_Companies
          Join Companies on 
          Movie_Production_Companies.Company_ID = Companies.Company_ID
          where Movie_Production_Companies.Movie_ID = ?
          order by Companies.Company_Name asc;"""
  
  movies_and_ratings = datatier.select_n_rows(dbConn, sql1, [movie_id])
  movie_genres = datatier.select_n_rows(dbConn, sql2, [movie_id])
  movie_companies = datatier.select_n_rows(dbConn, sql3, [movie_id])

  genres_list = []
  companies_list = []

  # list of genres
  for row in movie_genres:
    genres_list.append(row[0])

  # list of companies
  for row in movie_companies:
    companies_list.append(row[0])

  # Looping through sql1 values that returns movie ID, Name, 
  # date, minutes, language, budget, revenue, number of ratings,
  # average rating, and movie tagline
  # After these values we add our remaining 2 lists.
  for row in movies_and_ratings:
    
    # Movie ID not found
    if (row[0] == None):
      return None

    # No tagline and average rating found
    if (row[9] == None) and (row[8] == None):
      three = MovieDetails(row[0], row[1], row[2], row[3], 
                       row[4],row[5], row[6], row[7], 0.00, "",
                       genres_list, companies_list)
      return three
      
    # No average rating
    if (row[8] == None):
      one = MovieDetails(row[0], row[1], row[2], row[3], 
                       row[4],row[5], row[6], row[7], 0.00, row[9],
                       genres_list, companies_list)
      return one
      
    # No tagline found
    if (row[9] == None):
      two = MovieDetails(row[0], row[1], row[2], row[3], 
                       row[4],row[5], row[6], row[7], row[8], "",
                       genres_list, companies_list)
      return two

    # If all values accounted for return regular MovieDetails object
    four = MovieDetails(row[0], row[1], row[2], row[3], 
                       row[4],row[5], row[6], row[7], row[8], row[9],
                       genres_list, companies_list)
    return four;
         

##################################################################
#
# get_top_N_movies:
#
# gets and returns the top N movies based on their average 
# rating, where each movie has at least the specified # of
# reviews. Example: pass (10, 100) to get the top 10 movies
# with at least 100 reviews.
#
# Returns: returns a list of 0 or more MovieRating objects;
#          the list could be empty if the min # of reviews
#          is too high. An empty list is also returned if
#          an internal error occurs (in which case an error 
#          msg is already output).
#
def get_top_N_movies(dbConn, N, min_num_reviews):
  
  sql = """Select Movies.Movie_ID, Title, 
           strftime('%Y', Release_Date) as Year, 
           avg(Ratings.Rating) as average, 
           count(Ratings.Movie_ID) as number 
           From Movies
           Left Join Ratings on Movies.Movie_ID = Ratings.Movie_ID
           group by Movies.Movie_ID
           having number >= ?
           order by average desc
           limit ?; """

  top_n = datatier.select_n_rows(dbConn, sql, [min_num_reviews, N])

  top_n_list = []

  # Returns a list of MovieRating object which contains:
  # movie ID, Name, year of the movie, average rating, 
  # and number of ratings
  for row in top_n:
    
    one = MovieRating(row[0],row[1],row[2],row[4],row[3])
    
    top_n_list.append(one)

  return top_n_list
  

  


##################################################################
#
# add_review:
#
# Inserts the given review --- a rating value 0..10 --- into
# the database for the given movie. It is considered an error
# if the movie does not exist (see below), and the review is
# not inserted.
#
# Returns: 1 if the review was successfully added, returns
#          0 if not (e.g. if the movie does not exist, or if
#          an internal error occurred).
#
def add_review(dbConn, movie_id, rating):

  sql1 = """Select count(Movie_ID) From Movies
           Where Movie_ID = ?;"""
  
  sql2 = """Insert Into Ratings(Movie_ID, Rating)
           Values(?, ?);"""

  movie_exist = datatier.select_one_row(dbConn, sql1, [movie_id])

  # Check if movie exists in Movies table
  for unit in movie_exist:
    
    if(unit == 0):
      
      return 0
    
  edit = datatier.perform_action(dbConn, sql2, [movie_id, rating])
  
  return edit;

##################################################################
#
# set_tagline:
#
# Sets the tagline --- summary --- for the given movie. If
# the movie already has a tagline, it will be replaced by
# this new value. Passing a tagline of "" effectively 
# deletes the existing tagline. It is considered an error
# if the movie does not exist (see below), and the tagline
# is not set.
#
# Returns: 1 if the tagline was successfully set, returns
#          0 if not (e.g. if the movie does not exist, or if
#          an internal error occurred).
#
def set_tagline(dbConn, movie_id, tagline):
  
  sql1 = """Select count(Movie_ID) From Movies
           Where Movie_ID = ?;"""
  
  sql2 = """Insert Into Movie_Taglines(Movie_ID, Tagline)
           Values(?, ?);"""

  sql4 = """Update Movie_Taglines
            Set Tagline = ?
            Where Movie_ID = ?;"""

  sql5 = """Select count(Tagline) From Movie_Taglines 
            Where Movie_ID = ?;"""

  movie_exist = datatier.select_one_row(dbConn, sql1, [movie_id])
  
  for unit in movie_exist:
    # Check if movie exists
    if(unit == 0):
      
      return 0

  tag_exist = datatier.select_one_row(dbConn, sql5, [movie_id])
  
  for tag in tag_exist:

    # If there is no tag and movie exists, create a tag
    if(tag == 0):
      
      edit = datatier.perform_action(dbConn, sql2, [movie_id,tagline])
      
      return edit

  # Movie exists and there is an existing tag
  # Update it with new tag
  edit = datatier.perform_action(dbConn, sql4, [tagline, movie_id])
  
  return edit;
