
# General

This is a small project to be a able to "play" [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) on the Arduino UNO R4's 12x8 LED matrix.

Even if it only offers 96 pixels(cells) to work with you can still make stuff, like a glider (a small group of cells able to move diagonally on the grid), which is the default here.

## The rules:
1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
2. Any live cell with two or three live neighbours lives on to the next generation.
3. Any live cell with more than three live neighbours dies, as if by overpopulation.
4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction. 

<br>


# Settings

## Start settings

### 1. Random Start toggle

You can toggle the random start function by changin the random start variable
```
const bool randomStart = true;
```
or
```
const bool randomStart = false;
```


### 2. Define set starting board

You are able to change the first frame configuration by changing the numbers (1 = alive, 0 = dead) on line 148
```
    uint8_t frame[maxY][maxX] = {
        // define your starting board
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
```


