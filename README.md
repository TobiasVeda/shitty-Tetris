# Tetris
Exam project for "IKT103-G 24V Videregående softwareutvikling"

## Requirements
- C++ 17
- Simple Fast Multimedial Library (SFML)

- Or just run the exe in the zip folder, totally safe

## How to play

### Setting keybinds
- Input desired keybinds one by one for custom keybinds
- Press "enter" for deafult keybinds
- Controller does not support custom controls. Press any controller key to register a controller
  - Note: One controller can be assigned to differnt player
  - Xbox button prompts will be shown, regardless of controller type
- Pressing "enter", or any controller button will overwrite already assigned custom keybinds with the deafult set
- In Singleplayer
  - When all actions have an assigned key, press any key to start.
- In Multiplayer
  - When all of player 1's actions are assigned, the next keypress will be assigned to player 2
  - When both players actions have assigned keybinds, press any button to start
  - Mix of controller and keyboard allowed

 ### Game Over
 - When a newly spawned block immedialtly collides with another block, the player dies
 - In Singleplayer
   - The game ends in a game over screen
   - The scoreboard is shown
 - In Multiplayer
   - Each player dies seperatly and is shown the scoreboard
   - When both players die, the player with the highest score is announced the winner
 - Close and reopen the game to play again

### Default Keybinds
- Minimize/Maximize Window: F11

- Singleplayer Keyboard
  - Move Down: *Down Arrow*
  - Move Right: *Right Arrow*
  - Move Left: *Left Arrow*
  - Rotate Clockwise: *Up Arrow*
  - Rotate Counter-Clock: *Z*
  - Drop Block: *Space*
  - Hold Block: *C*

- Multiplayer Keyboard PLayer 1
  - Move Down: *S*
  - Move Right: *D*
  - Move Left: *A*
  - Rotate Clockwise: *W*
  - Rotate Counter-Clock: *Q*
  - Drop Block: *Tab*
  - Hold Block: *E*

- Multiplayer Keyboard PLayer 2
  - Move Down: *Down Arrow*
  - Move Right: *Right Arrow*
  - Move Left: *Left Arrow*
  - Rotate Clockwise: *Up Arrow*
  - Rotate Counter-Clock: *Right Shift*
  - Drop Block: *Enter*
  - Hold Block: *-*

- Controller (Xbox)
  - Move Down: *Stick Down*
  - Move Right: *Stick Arrow*
  - Move Left: *Stick Arrow*
  - Rotate Clockwise: *B*
  - Rotate Counter-Clock: *Y*
  - Drop Block: *A*
  - Hold Block: *X*
