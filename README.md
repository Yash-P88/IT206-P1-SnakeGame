# Snake Game

Welcome to the classic **Snake Game**! This is a fun, terminal-based game where you control a snake to eat food and grow longer. The game ends if the snake collides with itself or the boundaries of the play area.

## Table of Contents

- [Game Overview](#game-overview)
- [Installation](#installation)
- [How to Play](#how-to-play)
- [Controls](#controls)
- [Game Rules](#game-rules)
- [Game Logic](#game-logic)
- [Data Structure Analysis](#data-structure-analysis)
- [OS Compatibility](#os-compatibility)
- [Contributing](#contributing)

## Game Overview

This is a simple implementation of the classic Snake game in C++. The snake is controlled by user input and moves across the screen, collecting food that increases the snake’s length and score. The game ends if the snake collides with the walls or itself.

### Features

- *Snake Movement*: The snake can move in four directions (up, down, left, right).
- *Two Food Items*: Collect food to grow and earn points.
- *Collision Detection*: Game ends if the snake collides with the wall or its own body.
- *Score Tracking*: Tracks the current score and the highest score.
- *Speed Increasing*: The speed of the snake movement increases based on the score intervals.

## Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/Yash-P88/IT206-P1-SnakeGame.git
   ```

2. Navigate into the project folder:

   ```bash
   cd IT206-P1-SnakeGame
   ```

3. Compile the code using a C++ compiler (e.g., g++):

   ```bash
   g++ SnakeIO.cpp -o SnakeIO
   ```

4. Run the game:

   ```bash
   ./SnakeIO
   ```

## How to Play

1. Once you start the game, you'll see an introduction with instructions.
2. The snake starts at the center of the screen and can be controlled using the keyboard.
3. Your objective is to eat food (represented by `o`) that appears randomly on the board. Each piece of food increases your score and the length of the snake.
4. Avoid hitting the walls or your own tail. If you do, the game ends.

## Controls

- **W**: Move Up
- **A**: Move Left
- **S**: Move Down
- **D**: Move Right
- **R**: Restart Game (after game over)
- **Q**: Quit Game (after game over)

## Game Rules

- The game board is a grid, with walls represented by `#`.
- The snake is represented by `O` (head) and `o` (body).
- When the snake eats food, its length increases by one, and the score increases by 10 points.
- The game ends if the snake hits the wall or itself.

## Game Logic

- **Snake Class**: Manages the snake’s body, movement, and collision detection.
- **Food Class**: Spawns food items at random locations that don't overlap with the snake's body.
- **GameBoard Class**: Controls the game loop, drawing the board, and handling user input. The game state is tracked, and the snake’s movement is updated.

## Data Structure Analysis

In this game, several key data structures have been used to manage the game’s state and functionality:

### 1. **Point Class** (Coordinates of Snake and Food)

- *Purpose*: Represents the position of the snake’s body parts and the food on the game grid.
- *Data Structure*: Each `Point` object contains two integers: `x` (horizontal position) and `y` (vertical position).
- *Usage*:
  - The `Point` class is used for both the snake’s body and the food positions. Each part of the snake's body and the food is represented by a `Point` object, allowing for efficient position tracking and comparisons.
  - The position of the snake’s head is checked for collisions with food, walls, and its own body.

### 2. **Array of Points (Snake’s Body)**

- *Purpose*: Stores the positions of the snake’s body parts.
- *Data Structure*: The snake’s body is represented as an array of `Point` objects. Each element of the array corresponds to a part of the snake’s body, starting from the head to the tail.
- *Usage*:
  - The body of the snake is an array (`Point body[MaxLength]`), where each `Point` object represents a body segment of the snake.
  - The snake’s movement is handled by shifting the body segments forward, with the head taking the new position based on the direction of movement.
  - The snake’s length is tracked by an integer, and the array allows the snake to grow when it eats food.

### 3. **Food Class**

- *Purpose*: Represents the food objects on the game board.
- *Data Structure*: Each food is represented by a single `Point` object, storing its position on the board.
- *Usage*: The `Food` class contains logic to spawn food at random positions on the game board, ensuring that food doesn’t overlap with the snake’s body. It also contains logic to check for collisions with the snake's head.

### 4. **GameBoard Class**

- *Purpose*: The core of the game, managing the game loop, drawing the screen, and handling the interaction between the snake and food.
- *Data Structure*: The game board itself is logically a 2D grid (but is not explicitly implemented as a 2D array), where the `width` and `height` define the board's dimensions.
- *Usage*:
  - It holds the `Snake` and `Food` objects and coordinates the movement of the snake and spawning of food.
  - It handles input events, checks for collisions, updates the score, and determines when the game ends.

## OS Compatibility

### Windows

This game uses the `windows.h` header for some Windows-specific features such as:

- `Sleep()`
- `SetConsoleTextAttribute()` for colored output
- `system("cls")` for clearing the screen
- `_kbhit()` and `_getch()` for detecting key presses

Therefore, this solution is **Windows-dependent** by default. It works best on Windows OS with a compatible compiler like MinGW or MSVC.

### Linux/macOS

If you are running Linux or macOS, you may face issues because `windows.h` and `conio.h` are not available on these systems. Here are some recommendations to make the game work:

1. **Replace `windows.h` and `conio.h`**: You can use the `ncurses` library to handle input and output in the terminal, including key presses, clearing the screen, and text color. This would require refactoring parts of the code.
2. **Sleep Function**: You can replace `Sleep()` with `usleep()` (for microseconds) or `sleep()` (for seconds) from the `unistd.h` library.
3. **Clearing the Screen**: You can use `std::system("clear")` instead of `system("cls")` for Linux/macOS.
4. **Key Press Detection**: You may need to use `termios` and `fcntl` to handle non-blocking key input on Unix-based systems.

## Contributing  

Whether it’s fixing bugs, optimizing performance, adding new features, or making the game compatible with Linux/macOS, every contribution is welcome.  

### How to Contribute  

1. *Fork the repository* – Click the "Fork" button on GitHub to create your copy.  
2. *Create a new branch* – Name it based on your feature or fix:  

   ```bash
   git checkout -b feature-name
   ```  

3. *Make your changes* – Implement your feature while keeping the code clean and structured.  
4. *Test your changes* – Ensure everything runs smoothly before submitting.  
5. *Push your branch* – Upload your changes to GitHub:  

   ```bash
   git push origin feature-name
   ```

Enjoy the game! Let the snake grow longer, score high, and avoid the deadly walls!
