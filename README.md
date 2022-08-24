# poker-face

project developed in C++, for the discipline of data structures.

The proposed problem was to implement a system that takes care of the decision stage of the round of a poker game. In this system, for a set of players, they should be classified in relation to the cards they have, defining in a round who would be the
player with the winning hand and therefore the one who would win the bet. In case of a tie, there are criteria to resolve the issue. In addition, it is important to manage the amount of money that each player has during the game.

# Implementation

The program was developed in the C++ language, compiled by the GNU GCC compiler
Compiler Collection, on the Linux operating system.

# Data structure

The implementation of the program was based on the data structure of a list,
statically implemented, in which the player entity (who participated in the
poker game) have been entered. This preference was given due to the amount
limited number of players expected in a poker game with a limited deck
of 52 cards.

This data structure was assembled in a class called rodada. as seen in
class, the static version list was implemented in order to facilitate the implementation and
reduce the asymptotic cost of some operations.

# Classes

To modularize the implementation, 3 classes were used, the first of which was
being the carta class, containing suit and value as attributes, being the key class
for creating the cards used in the game by the players.

We have the jogador class, which contains the name and money attributes that the
player has to place bets, it also has the points and hand attributes, which
help keep track of the player's hand and the amount his score during the match, facilitating comparisons and tie-breaks.

We have the rodada class that, as commented earlier, implements
a list of players, it has been implemented to keep track of the players participating in the round, the values of their hands, how much money they are actively betting, in addition to enabling control of the final result of
plays performed and the ranking of participants.

# Classification and Tiebreaker

The hand classification system is one of the most important parts of the
implementation, especially since he is the one who manages the players who will win the
round. For the sake of code development, the players class receives a
property called points that is added every time one of the
winning hands, thus facilitating the ranking and the tiebreaker by comparison
of different scores. To classify the hands, it was initially necessary
put them in ascending order, using the quicksort algorithm during
this snippet of code, as multiple hands would be sorted during a
match.

# Instructions for compiling and running

1. get the poker-face folder. enter the folder and run the makefile using the "make" command (in the folder, there are already
   entrada.txt with a few test runs)
2. the "make" command will generate the \*.o file, and also executable in the bin folder.
3. For the "make run" command to work, the entrada.txt file must be in the root next to the makefile,
4. the command “make run” will generate the file saida.txt in the root folder of the
   makefile with results

# input example

3 1000
5 50
Giovanni 100 6O 3P 10E 11O 1O
John 200 3P 4E 3E 13C 13O
Thiago 100 12O 7P 12C 1O 13C
Gisele 300 12E 10C 11C 9C 13E
Wagner 50 5P 12P 5E 2E 1P
2 50
Wagner 200 2P 13E 9E 12C 2O
Gisele 350 11P 9P 2E 6E 4P
3 100
Thiago 250 1O 4P 1E 3O 8O
Gisele 100 9C 8C 8C 2C 6C
Giovanni 150 4P 12P 8E 12E 2P

# Example Output (referring to example input)

1 1000 S
Gisele
1 200 OP
Wagner
1 1000 F
Gisele
