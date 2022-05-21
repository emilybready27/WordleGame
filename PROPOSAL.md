For my final project, my idea is to recreate the Wordle game that became popular over the past few months. I became very invested in playing this game every day, and I thought it was interesting how such a simple concept could really attract a lot of people. The only thing that I didn’t like about the application was that you could only play one game each day. I wanted to see if I could recreate this game to work as cleanly as the original and also make the change so that you’re not limited to just one word a day. Then hopefully I can play my own game instead of theirs (which also has ads, so that would be an added bonus).

## Week 1: Wordle Structure

*Create an instance of Wordle for a given word*

- Set up directories and files so they link and compile without error
- Decompose Wordle concept into classes:
  - Game: represents a Board and a correct answer
  - Board: represents the grid of words
  - Word: consists of five Letters and a string representation
  - Letter: each has its own associated color
- Implement functionality to construct a single game given a single word
- PrintLn state of the game to the console

## Week 2: Console User Inputs

*Play the game with input from the console*

- Decompose into more classes:
  - Dictionary: stores list of words from which to generate new games, check user guesses
  - UI: handles user commands and prints messages to console
  - Statistics: quantitative information about the games played
- Use this https://github.com/exciteabletom/wordle-API/blob/master/word_list.txt list of 5-letter English words to construct the Dictionary
- Implement Dictionary selection of new words and validation of user-input words
- Implement commands in UI 
  - sequence of letters: word guess
  - 1: show instructions
  - 2: start a new game
  - 3: play an existing game
- Change color of console text to match corresponding Letter color

## Week 3: Cinder Visualization

*Play the game using Cinder visualization*

- Decompose WordleApp into classes:
  - Tile: represents a single letter with a color for correctness
  - Layout: grid of 30 Tiles
- Implement overridden methods:
  - setup: display layout of empty Tiles
  - draw: display Tiles based on their color and letter, according to Wordle state
  - keyDown: accept characters for word guesses from keyboard
- Add buttons to Layout for inputting word guesses via mouse clicks
- Override mouseDown

## Week 4: Added Cinder Visualization

*Look at past games and overall statistics*

- Accept commands 1, 2, and 3 via keyboard inputs
- Accept commands 1, 2, and 3 via mouse clicks
- Create home page display to add to Layout with different options
  - Look at past games or generate new one
  - View game instructions
  - View game Statistics
- Write README.md of instructions

## Stretch Goals

- Implement points system so you can buy an extra guess
- Implement boards of different sizes for different lengths of words
- Display definition of a word after a game is completed
