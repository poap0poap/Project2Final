Board.cpp - Due 4/9
Skeleton.txt - Due 4/11
Sign up - 4/25
Final Submision - 4/30
Project report - 5/3

We will include sorting of charcters based on Pride Points. We will also add more to riddles for a more in depth experience. 

Contains:
Special tiles for each path
Multiplayer (2-4)
Boost based on advisor
Same tile Constraint - if both player on same tile and not start/finish battle. flip coin winner +5 points, loser - 5 points\
Factors that alter outcome - age change loss %wise
  wisdom + age at end

Tile Information and Effects:
Green - Grassland/Regular Tiles
  - Must have 20 at least on each path.
  - A random event from "random_events.txt" occurs that can help/hurt the player. 
  - There is a 50% chance for the random event to occur.
  - Make sure to make it so that the player's advisor can protect against the random event if it harms the player.
Special Tiles:
        Blue - Oasis Tile
          - This gives the player an extra turn to keep moving forward
          - Add 200 points each to the Stamina, Strength, and Wisdom Stat.
        Pink - Counseling Tile
          - Add 300 points each to the Stamina, Strength, and Wisdom Stat.
          - Choose an advisor from the following advisors.
          - If you already have and advisor, you can change to a different one from the list or keep the same one.
          - Friendly Reminder that the Advisor can protect the player against the random events.
        Red - Graveyard Tile
          - Player goes back 10 Tiles
          - Subtract 100 points each from the Stamina, Strength, and Wisdom Stat.
        Brown - Hyena Tile
          - Hyenas drag you back to where you came from.
          - Subtract 300 points from the Stamina Stat
        Purple - Challenge Tile
          - Answer a question from "riddles.txt". If you answer correctly, add 500 points to the Wisdom Stat.
          - Note: Riddles are supposed to be c++ related.


NOTE: These odds are from the workbook and that we can change them if we want.
Tile Odds for Both Paths:
  Straight to the Pridelands:
    - 52 Total Tiles: 20 Grasslands, 30 Special, 1 Start and 1 End
        - 20% Chance to find an Advisor
        - 25% Chance for a Challenge Tile to appear.
        - First Half
            - 25% Chance for a Special Tile to be a Graveyard Tile
            - 25% Chance for a Special Tile to be a Hyena Tile
            - 5% Chance for a Special Tile to be an Oasis Tile
        - Second Half
            - 15% Chance for a Special Tile to be a Graveyard Tile
            - 15% Chance for a Special Tile to be a Hyena Tile
            - 25% Chnace for a Special Tile to be an Oasis Tile

Cub Training:
    - 52 Total Tiles: 20 Grasslands, 30 Special, 1 Start and 1 End
        - 20% Chance for a Graveyard Tile
        - 20% Chance for a Hyena Tile
        - 15% Chance to find an Advisor (since they already have one)
        - First Half
            - 25% Chance for a Special Tile to be an Oasis Tile
            - 20% Chance for a Challenge Tile to appear
        - Second Half
            - 15% Chance for a Special Tile to be an Oasis Tile
            - 30% Chance for a Challenge Tile to appear

Final Evaluation of Pride Points by the end.
For every 100 points in the Stamina, Strenght, or Wisdom Stat, add 1000 Pride Points to the total.
Whoever has the greatest ammount of Pride Points by the end will be declared the winner. 
Make sure to display the name of the lion with the highest Pride Points as the winner, along with each player’s final stats.
