/**------------------------------------------
    Program 2: Great 13

    Course: CS 141, Fall 2022.
    System: Linux x86_64 and C++
    Author: Soham Kaje, starter code provided by UIC Professors George Maratos and
    David Hayes
 ---------------------------------------------**/

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>

using namespace std;

// Function that displays the instructions to the user

void display_instructions() {
  cout << "Class: CS 141" << endl
       << "Program 2: Great 13" << endl
       << endl
       << "Make a series of jumps until there is a single piece left" << endl
       << "anywhere on board. On each move you must jump an adjacent" << endl
       << "piece   into   an  empty  square,  jumping  horizontally," << endl
       << "vertically, or diagonally." << endl
       << endl
       << "Input of 'R' resets the board back to the beginning, and " << endl
       << "'X' exits the game." << endl;
}

// The internal representation of the board as an array. Do not modify directly.

char board[13]{};

/* These two functions are how you will get and set elements on the board. Only
use these two when changing, or reading the board. */

char get_element(char position) {
  if ((position < 'A') || (position > 'M')) {
    cout << "Failed to get element at position " << position << endl
         << "Make sure the given position is an uppercase letter " << endl
         << "between A-M." << endl;
    exit(1);
  }
  return board[position - 'A'];
}

void set_element(char position, char value) {
  if ((position < 'A') || (position > 'M')) {
    cout << "Failed to set element at position " << position << endl
         << "Make sure the given position is an uppercase letter " << endl
         << "between A-M." << endl;
    exit(1);
  }
  board[position - 'A'] = value;
}

// print out the board with the legend on the right

void display_board() {
  cout << endl;
  cout << setw(7) << "Board" << setw(12) << "Position" << endl;
  cout << setw(5) << board[0] << setw(11) << 'A' << endl
       << setw(3) << board[1] << ' ' << board[2] << ' ' << board[3] << setw(11)
       << "B C D" << endl
       << board[4] << ' ' << board[5] << ' ' << board[6] << ' ' << board[7]
       << ' ' << board[8] << ' ' << " E F G H I" << endl
       << setw(3) << board[9] << ' ' << board[10] << ' ' << board[11]
       << setw(11) << "J K L" << endl
       << setw(5) << board[12] << setw(11) << 'M' << endl;
  cout << endl;
}

// the functions are declared here
void make_move(string &input);
void initialize_board();
bool game_over(string input);

int main() {
  display_instructions();
  initialize_board();
  string input;

  // do-while loop to run the game while user hasn't won or exited the game
  do {
    display_board();
    // ask user for input
    cout << "Enter positions from, jump, and to (e.g. EFG): ";
    cin >> input;
    make_move(input);
  } while (!game_over(input) && !cin.eof());
  return 0;
}

// This function checks for all the rules of the game based on what the user
// inputs. Input is a pass-by-reference parameter so that it can be updated if
// necessary.
void make_move(string &input) {
  char peg_from;
  char peg_jump;
  char peg_to;

  // changes the input to all uppercase, regardless of whether its valid or
  // invalid
  for (int i = 0; i < input.length(); i++) {
    input[i] = toupper(input[i]);
  }

  // if else branch to check whether input length is 3
  if (input.length() != 3) {
    // if input isn't X or R, and it's not 3 characters long, the sequence is
    // invalid
    if (input != "X" && input != "R") {
      cout << "*** Invalid sequence. Please retry." << endl;
      return;
      ;
    }
    // if the input is R, the board is reset and user can play the game again
    else if (input == "R") {
      cout << "Restarting game." << endl;
      initialize_board();
      return;
    }
    // if the input is X, the game stops running
    else if (input == "X") {
      cout << "Exiting." << endl;
      exit(0);
    }
  }
  // checks if input length is 3 characters long
  else if (input.length() == 3) {
    // for loop to look through all the letters to make sure that all characters
    // are within the range of the letters on the legend
    for (int j = 0; j < input.length(); j++) {
      if (input[j] < 'A' || input[j] > 'M') {
        cout << "*** Given move has positions not on the board! Please retry."
             << endl;
        return;
      }
    }
    // checks if the input is a valid move or not (there are only a certain
    // number of valid moves that are all listed in this if statement)
    if ((input != "ABE") && (input != "ACG") && (input != "ADI") &&
        (input != "BCD") && (input != "BGL") && (input != "BFJ") &&
        (input != "CGK") && (input != "DCB") && (input != "DGJ") &&
        (input != "DHL") && (input != "EBA") && (input != "EFG") &&
        (input != "EJM") && (input != "FGH") && (input != "GCA") &&
        (input != "GHI") && (input != "GKM") && (input != "GFE") &&
        (input != "HGF") && (input != "IDA") && (input != "IHG") &&
        (input != "ILM") && (input != "JKL") && (input != "JGD") &&
        (input != "JFB") && (input != "KGC") && (input != "LHD") &&
        (input != "LGB") && (input != "LKJ") && (input != "MJE") &&
        (input != "MKG") && (input != "MLI")) {
      cout << "*** Move is invalid. Please retry." << endl;
      return;
    }

    // sets each character to a variable that matches its board location using
    // get_element() function
    peg_from = get_element(input.at(0));
    peg_jump = get_element(input.at(1));
    peg_to = get_element(input.at(2));

    // checks whether the starting peg has a piece
    if (peg_from == '.') {
      cout << "*** Source needs a piece. Please retry." << endl;
      return;
    }
    // checks whether the peg being jumped is a piece
    if (peg_jump == '.') {
      cout << "*** Must jump a piece. Please retry." << endl;
      return;
    }
    // checks whether the end peg/destination is empty
    if (peg_to == '#') {
      cout << "*** Destination must be empty. Please retry." << endl;
      return;
    }

    // changes the three variables to the correct values using the set_element()
    // function
    if (peg_from == '#') {
      set_element(input.at(0), '.');
    }
    if (peg_jump == '#') {
      set_element(input.at(1), '.');
    }
    if (peg_to == '.') {
      set_element(input.at(2), '#');
    }
  }
}

// This function checks whether the user has won the game or not by counting the
// number of empty spots using the input parameter. If there are 12 empty spots,
// then the user has won the game and the function returns true, otherwise the
// function returns false.
bool game_over(string input) {
  int pegCount = 0;

  // for loop to check whether each index in the board array is an empty piece
  // ('.')
  for (char i = 'A'; i <= 'M'; i++) {
    if (get_element(i) == '.') {
      pegCount += 1;
    }
  }

  // if the number of empty pegs is 12, the user wins and game_over() returns
  // true, ending the do-while loop in main
  if (pegCount == 12) {
    cout << "Congrats you win!" << endl;
    return true;
  }

  return false;
}

// This function initializes the board to have all pegs excluding the center
// hole. This function can also be used for restarting the game.
void initialize_board() {
  // for loop to correctly change the indexes in the board array using the
  // set_element() function
  for (char i = 'A'; i < 'N'; i++) {
    if (i == 'G') {
      set_element(i, '.');
    } else {
      set_element(i, '#');
    }
  }
}
