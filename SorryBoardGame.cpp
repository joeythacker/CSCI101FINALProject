//
//
//  SorryBoardGame.cpp
//
//  Created by Josiah Thacker on 5/3/23.
//
#include<iostream>
#include<string>
#include<ctime>
using namespace std;

// global variables
/* Create an Array to be used to track the player’s positions on the playing board.
   The playing board has 50 spaces (with 50 being the winning space). */
int playingBoard[50] = { 0 };
int positions[5];
int totalPlayers;
int currentPlayer;
int d1, d2;
int winner = 0;
bool startPlayer1;
bool startPlayer2;
bool startPlayer3;
bool startPlayer4;

// function prototypes
int getPosition(int p);
void displayBoard();
void rollDice();
bool isOtherPlayer(int m);
void movePlayer(int m);
void validateDice();

// start main function
int main()
{
    srand(time_t(NULL));
    char res = 'N';
    do
    {
        // initialize the variables and arrays
        totalPlayers = 0;
        currentPlayer = 0;
        d1 = 0; d2 = 0;
        winner = 0;
        startPlayer1 = false;
        startPlayer2 = false;
        startPlayer3 = true;
        startPlayer4 = true;
        
        for (int i = 0; i < 50; i++) {
            playingBoard[i] = 0;
        }
        
        // Prompt the user for the number of players(2 - 4).
        cout << "Enter the number of players: ";
        cin >> totalPlayers;
        cin.get();
        while (totalPlayers < 2 || totalPlayers > 4)
        {
            cout << "The number of players is not in the range (2-4)." << endl;
            cout << "Enter the number of players: ";
            cin >> totalPlayers;
            cin.get();
        }
        for (int i = 1; i <= totalPlayers; i++){
            positions[i] = 0;
        }
        
        if (totalPlayers >= 3)
            startPlayer3 = false;
        
        if (totalPlayers == 4)
            startPlayer4 = false;
        
        // repeat the loop to find the winner
        while (!winner)
        {
            // call the displayBoard function
            displayBoard();
            currentPlayer = currentPlayer % totalPlayers;
            cout << "Player #" << currentPlayer + 1 << " will roll the dice. [Press Enter]";
            cin.get();
            
            // call the rollDice function
            rollDice();
            
            // call the validateDice function
            validateDice();
            currentPlayer++;
        }
        
        // call the displayBoard function
        displayBoard();
        
        /* Once a player finishes, create a winning message announcing the winner. */
        cout << "Congratulations! Player #" << winner << " is the Winner." << endl << endl;
        
        /* Then ask the user if they would like to play again. */
        cout << "Do you want to play again? [Type 'y'/'Y' for Yes]:" << endl;
        cin >> res;
        cin.get();
    } while (res == 'y' || res == 'Y');
    return 0;
}
int getPosition(int p)
{
    for (int i = 0; i < 50; i++) {
        if (playingBoard[i] == p)
            return i;
    }

    return 0;
} // end of getPosition function

// displayBoard function implementation
void displayBoard()
{
    /* Depict a Playing Board on the screen and display the Players’ position on the board. */
    cout << "Playing board:" << endl;
    for (int i = 0; i < 50; i++) {
        cout << playingBoard[i] << " ";
    }
    cout << endl << "Players positions:" << endl;
    for (int i = 1; i <= totalPlayers; i++) {
        cout << "Position of Player #" << i << ": " << getPosition(i) << endl;
    }
} // end of displayBoard function

// rollDice function implementation
void rollDice()
{
    /* Use a random Generator to “roll” the dice, the user must press enter to roll. */
    /* A player must roll an EXACT number to enter the winning space. */
    // Create two die for the players to roll.
    // A player must roll a double to start.
    if (currentPlayer == 0 && startPlayer1 == false) {
        do {
            d1 = 1 + (rand() % 6);
            d2 = 1 + (rand() % 6);
        }while (d1 != d2);

        startPlayer1 = true;
    }
    else if (currentPlayer == 1 && startPlayer2 == false) {
        do {
            d1 = 1 + (rand() % 6);
            d2 = 1 + (rand() % 6);
        } while (d1 != d2);

        startPlayer2 = true;
    }
    else if (currentPlayer == 2 && startPlayer3 == false) {
        do {
            d1 = 1 + (rand() % 6);
            d2 = 1 + (rand() % 6);
        } while (d1 != d2);

        startPlayer3 = true;
    }
    else if (currentPlayer == 3 && startPlayer4 == false) {
        do {
            d1 = 1 + (rand() % 6);
            d2 = 1 + (rand() % 6);
        } while (d1 != d2);

        startPlayer4 = true;
    }
    else {
        d1 = 1 + (rand() % 6);
        d2 = 1 + (rand() % 6);
    }
    cout << d1 << " " << d2 << endl;
} // end of rollDice function

bool isOtherPlayer(int m)
{
    if(playingBoard[m] > 0)
        return true;
    else
        return false;
} // end of isOtherPlayer function

// movePlayer function implementation
void movePlayer(int m)
{
    int move;
    if (m == 2 || m == 3 || m == 4 || m == 5 || m == 6 || m == 8 || m == 9 || m == 10)
    {
        if (m == 4) {
            // Move back one space.
            move = positions[currentPlayer + 1] - 1;
        }
        else {
            // Move forward the space(s).
            move = positions[currentPlayer + 1] + m;
        }

        if (move < 0) {
            cout << "You cannot move back to one space." << endl;
        }
        else if (move > 49) {
            cout << "You cannot move " << m << " spaces." << endl;
        }
        else if (move == 49)
        {
            winner = currentPlayer + 1;
            playingBoard[move] = currentPlayer + 1;
            playingBoard[positions[currentPlayer + 1]] = 0;
            positions[currentPlayer + 1] = move;
        }
        else if (isOtherPlayer(move))
        {
            /* If a player lands on the same space as another, the other player must return to the beginning. */
            cout << "Player #" << playingBoard[move] << " is on this position, you sent that player to the start." << endl;
            positions[playingBoard[move]] = 0;
            playingBoard[move] = currentPlayer + 1;
            playingBoard[positions[currentPlayer + 1]] = 0;
            positions[currentPlayer + 1] = move;
        }
        else
        {
            if (m == 4) {
                cout << "You are backwarded one space in the board" << endl;
            }
            else {
                cout << "You are forwarded " << move << " spaces in the board" << endl;
            }

            // Move forward/backward the space(s).
            playingBoard[move] = currentPlayer + 1;
            playingBoard[positions[currentPlayer + 1]] = 0;
            positions[currentPlayer + 1] = move;
        }
    }
    else if (m == 7)
    {
        /* Swap spots with the leading layer / or nothing if player is in lead. */
        int lead = 0;
        int maximum = INT_MIN;
        for (int i = 1; i <= totalPlayers; i++)
        {
            if (maximum < positions[i]) {
                maximum = positions[i];
                lead = i;
            }
        }
        if (lead != currentPlayer + 1)
        {
            /* Swap spots with the leading layer / or nothing if player is in lead. */
            cout << "Swapping your position with lead player #" << lead << "." << endl;
            std::swap(positions[currentPlayer + 1], positions[lead]);
            playingBoard[positions[currentPlayer + 1]] = currentPlayer + 1;
            playingBoard[positions[lead]] = lead;
        }
        else {
            cout << "You are already in lead position." << endl;
        }
    }
    else if (m == 11)
    {
        /* Swap spots with the last player / or do nothing if player is last. */
        int last = 0;
        int minimum = INT_MAX;
        for (int i = 1; i <= totalPlayers; i++) {
            if (minimum > positions[i]) {
                minimum = positions[i];
                last = i;
            }
        }

        if (last != currentPlayer + 1)
        {
            /* Swap spots with the last player / or do nothing if player is last. */
            cout << "Swapping your position with last player #" << last << "." << endl;
            std::swap(positions[currentPlayer + 1], positions[last]);
            playingBoard[positions[currentPlayer + 1]] = currentPlayer + 1;
            playingBoard[positions[last]] = last;
        }
        else {
            cout << "You are already in last position." << endl;
        }
    }
    else if (m == 12)
    {
        // Start Over
        cout << "You are going to starting position of the board." << endl;
        playingBoard[positions[currentPlayer + 1]] = 0;
        positions[currentPlayer + 1] = 0;
    }
    cout << "Player #" << currentPlayer + 1 << " current position is: " << positions[currentPlayer + 1] << endl;
} // end of movePlayer function
void validateDice()
{
    if (d1 == d2)
    {
        // call the displayBoard function
        movePlayer(d1 + d2);

        // call the displayBoard function
        displayBoard();

        /* If a player rolls a double, they’ll get another roll */
        cout << "You scored a double! Roll again. [Press Enter]";
        cin.get();

        // call the rollDice function
        rollDice();

        if (d1 == d2) {
            /* If a player rolls two doubles in a row, they Start Over */
            cout << "Oh! You scored double two times!" << endl;

            // call the movePlayer function
            movePlayer(12);
        }
        else {
            // call the movePlayer function
            movePlayer(d1 + d2);
        }
    }
    else {
        // call the movePlayer function
        movePlayer(d1 + d2);
    }
} // end of validateDice function


