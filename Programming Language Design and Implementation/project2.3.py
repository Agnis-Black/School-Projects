# 
#   Name: Aqsa Arif
#   NetID: aarif20
#   Date: 10/07/2022
#   Class: CS 341, Fall 2022
#   Project 02-03
#
# References: 
#  learning python: https://www.w3schools.com/python/
#  sqlite programming: https://docs.python.org/3/library/sqlite3.html
#
import sqlite3
import objecttier


##################################################################  
# 
# retrieve_movies : total number of movies and reviews
#
def retrieve_movies(dbConn):
  
  movies = objecttier.num_movies(dbConn)  
  
  reviews = objecttier.num_reviews(dbConn)
  
  print("  # of movies:", f"{movies:,}")
  
  print("  # of reviews:", f"{reviews:,}")
  
  print()

##################################################################  
# 
# command 1 : print less than 100 movies with wildcards search
#
def command_one(dbConn):
  
  print()
  
  name = input("Enter movie name (wildcards _ and % supported): ")
  
  movie = objecttier.get_movies(dbConn,name)
  
  print()
  
  print("# of movies found:", len(movie))
  
  print()
  
  if (len(movie) > 100):
    
    print("There are too many movies to display, please narrow your search and try again...")
    
  else:
    
    for mov in movie:
      
      print(mov.Movie_ID, ":", mov.Title, "(" + mov.Release_Year + ")")

##################################################################  
# 
# command 2 : get movie details from a valid movie ID number
#
def command_two(dbConn):
  
  id = int(input("\nEnter movie id: "))
  
  movie = objecttier.get_movie_details(dbConn, id)
  
  if(movie == None):
    
    print("\nNo such movie...")
    
  else:
    
    print()
    
    print(movie.Movie_ID, ":", movie.Title)
    
    print("  Release Date:", movie.Release_Date)
    
    print("  Runtime:", movie.Runtime, "(mins)")
    
    print("  Orig language:", movie.Original_Language)
    
    print("  Budget:", "$" + str(f"{movie.Budget:,}"), "(USD)")
    
    print("  Revenue:", "$" + str(f"{movie.Revenue:,}"), "(USD)")
    
    print("  Num reviews:", movie.Num_Reviews)
    
    print("  Avg rating:", f"{movie.Avg_Rating:.2f}", "(0..10)")
    
    print("  Genres: ", end = "")

    # Loop through list of genres
    for genre in movie.Genres:
      
      print(genre, end = ", ")
      
    print("\n  Production companies: ", end = "")

    # Loop through list of companies
    for company in movie.Production_Companies:
      
      print(company, end = ", ")
      
    print("\n  Tagline:", movie.Tagline)

##################################################################  
# 
# command 3 : look up top N movies with a minimum number of reviews
#
def command_three(dbConn):
  
  print()
  
  N = int(input("N?"))
  
  if (N <= 0):
    
    print(" Please enter a positive value for N...")
    
  else:
    
    min_reviews = int(input(" min number of reviews? "))
    
    if (min_reviews <= 0):
      
      print(" Please enter a positive value for min number of reviews...")
      
    else:
      
      movies = objecttier.get_top_N_movies(dbConn, N, min_reviews)
      
      print()

      # Loop through list of movies and format for print
      for mov in movies:
        
        print(mov.Movie_ID, ":", mov.Title, 
              "(" + mov.Release_Year + "),",
              "avg rating =", f"{mov.Avg_Rating:.2f}", 
              "(" + str(mov.Num_Reviews) + " reviews)")

##################################################################  
# 
# command 4 : allow user to insert their own rating for a valid movie
#
def command_four(dbConn):
  
  print()
  
  rating = int(input("Enter rating (0..10): "))
  
  if (rating < 0) or (rating > 10):
    
    print("Invalid rating...")
    
  else:
    
    id = int(input("Enter movie id: "))
    
    insert = objecttier.add_review(dbConn, id, rating)
    
    if(insert == 0):
      
      print("\nNo such movie...")
      
    else:
      
      print("\nReview successfully inserted")
    
##################################################################  
# 
# command 5 : Allow user to add their own tagline for a valid movie
#
def command_five(dbConn):
  
  print()
  
  tag = input("tagline? ")
  
  id = int(input("movie id?"))
  
  apply_tag = objecttier.set_tagline(dbConn, id, tag)
  
  if (apply_tag == 0):
  
    print("\nNo such movie...")
  
  else:
  
    print("\nTagline successfully set")

##################################################################  
#
# main
#
print('** Welcome to the MovieLens app **')

dbConn = sqlite3.connect('MovieLens.db')

print()

print("General stats:")

# Function to print genral stats
retrieve_movies(dbConn)

cmd = input("Please enter a command (1-5, x to exit): ")

while cmd != "x":
  
    if cmd == "1":
      
      command_one(dbConn)
      
    elif cmd == "2":
      
      command_two(dbConn)
      
    elif cmd == "3":
      
      command_three(dbConn)
      
    elif cmd == "4":
      
      command_four(dbConn)
      
    elif cmd == "5":
      
      command_five(dbConn)
      
    else:
      
        print("**Error, unknown command, try again...")

    print()

    # Keep looping until x is pressed
    cmd = input("Please enter a command (1-5, x to exit): ")

#
# done
#
