# Space-Shooter-Game
Space Shooter Game Semester 1 Project 
Game Logic:
![image](https://github.com/Najeebullah3124/Space-Shooter-Game/assets/147226547/db54a2a5-e2fe-43c2-85c1-7492b3a8a296)
The game maintains a 2D grid (arr[30][50]) representing the game board.
The player (marked as ^) can move within the board boundaries and shoot (x) upwards.
Enemies (#) spawn randomly at the top and move downwards.
There's collision detection between player shots and enemies, as well as enemy shots and the player (!).

Features and Functions:
Movement: The player can move up (w), left (a), down (s), and right (d).
Firing: The player can shoot bullets (x) upwards by pressing the spacebar.
Enemy Actions: Enemies move downward, fire randomly, and disappear upon reaching the bottom.
Gifts: Randomly appearing gifts ($) grant points when collected by the player (^).
Health and Points: The player has a health bar and earns points by shooting enemies and collecting gifts.
![image](https://github.com/Najeebullah3124/Space-Shooter-Game/assets/147226547/02275e06-9b24-448c-a778-d32ee89fd234)
![image](https://github.com/Najeebullah3124/Space-Shooter-Game/assets/147226547/3386c33d-f65c-456c-b9a6-41bc4cbc13f5)
Functions Summary:
show(): Displays player points and health.
updateScreen(): Updates and prints the game board, including colors for different elements.
Boundry(): Sets up the initial game board and player position.
Functions for enemy and player bullet motions, collision detection, and enemy movement.
File I/O function to write player information (name, age, score) to a file.

![image](https://github.com/Najeebullah3124/Space-Shooter-Game/assets/147226547/763a4585-b3a2-45f9-a05d-0458872be4f2)



