# Player index correct
made player index on the correct path

Still need to do for the board
  - skip turn after reach end
  - diffrent paths diffrent tilesets

# Changes
file for player data  
tiles have effects  
need to make classes  


25% chance of random event on all tiles  
50% chance of 0 or 2 to random stat on black tile  

main path starts normal   
side path 50% easier until middle  

main path gets +10pt  
side path get -5pt and advisor  

every 10 turns damage from events goes up by 1  

events hurt points based on current stats  
  ex - main path windstorm does -5pt but for every 10 stamina does 1pt less damage
     - side path until middle windstorm does -3pt but for every 10 stamina does 1pt less damage
     - reach 0 points you get -1pt to all stats each turn
advisor can negate certain events  


Main  
tile displacement  
50 - black  
10 - yellow  
5 - purple  
10 - blue  
5 - pink  
5 - green  
10 - brown  
3 - red  
2 - cyan  

Side  
tile displacement  
50 - black  
5 - yellow  
5 - purple  
13 - blue  
7 - pinks  
7 - green  
8 - brown  
2 - red  
3 - cyan  

# Main
## Dates
Board.cpp - 4/9\
Skeleton.txt - 4/11\
Sign up - 4/25\
Final Submision - 4/30\
Project report - 5/3

## Extra Credit
We will include sorting of charcters based on Pride Points. We will also add more to riddles for a more in depth experience. 

Each turn +age\
main path +5 to age

### Extra Credit Stuff Contains:
Special tiles for each path\
Multiplayer (2-4)\
Boost based on advisor\
Same tile Constraint - if both player on same tile and not start/finish battle. flip coin winner +5 points, loser - 5 points\
Factors that alter outcome - age change loss %wise\
  wisdom + age at end
