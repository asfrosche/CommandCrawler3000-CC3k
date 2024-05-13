# CommandCrawler3000 (CC3K)
This game is a text-based rogue-like game where players navigate through chambers, combat enemies, collect treasure, and utilize potions, all while strategically ascending through multiple floors to reach the ultimate goal.
It was written in C++ and utilises Encapsulation, Inheritance, Abstraction and Polymorphism and makes use of the Stategy design pattern.
#### Objective:
The objective of the game is to make it through the chambers and passages and to reach the stair on the floor to make it up all the way to the fifth floor. The player wins by reaching the final stair on the fifth floor. There are enemies moving about within the chambers that will attack you if they see you and there are unknown potions that you may find and utilize.

## Usage

The game supports command-line options in the format:
Acceptable commands include:

1. `./cc3k`
2. `./cc3k filename`
3. `./cc3k seed`
4. `./cc3k filename seed`
5. `./cc3k seed filename`

## Game Functionality

### Races
- Shade: Wins with a score increased by 50%
- Drow: Potions' effects magnified by 50%
- Vampire: Gains 5HP for successful attack
- Troll: Gains 5HP per turn
- Goblin: Steals 5 gold per enemy killed
- Human: Drops 2 NormalPiles on death
- Vampire: Loses 5hp against dwarf
- Elf: Dual attack (Drow - single hit)
- Orc: Deals 50% more damage to Goblin
- Merchant Hostility (before and after)
- Halfling: Halves hit rate of PC
- Dragon: Long-range attack (guarding hoard)

### Gold
- Collecting gold by walking over it
- Enemies dropping gold piles

### Potions
- Using potions (attack and defense effects are reverted as you increase a floor level)
- HP effects remain unaffected while moving up a floor

### Commands
- Movement: `no`, `so`, `ea`, `we`, `ne`, `se`, `nw`, `sw`
- Using a potion: `u [dir]`
- Attacking: `a [dir]`
- Restart: `r`
- Freeze enemy movement: `f`
- Quit: `q`

## Extra Features

- Optional instructions page
- Colorful UI for enhanced user experience
- Implementation using RAII and smart pointers

## Tests

1. `./cc3k 2 < test1.in`: Demonstrates various game actions.
2. `./cc3k winGame.txt < winGame.txt`: Tests all basic commands and winning scenarios.

For detailed test descriptions, refer to the comments in the test files.
