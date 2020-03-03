/*               2048 GAME
*      by: Team Segmentation Fault
*
*    Clingan 10:20  |  Started 11/25/19
*/


/* Including all necessary libraries. */
#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHRandom.h>
#include <LCDColors.h>
#include <FEHBuzzer.h>

/* Here is the class creation */
class GameBoard{

/* Contains all data and variables used in multiple functions */
private:
  int board[4][4];
  int breaker;
  int currentScore, highScore;
  float xPosition, yPosition, xTrash, yTrash;

/* Declarations of all functions */
public:
  GameBoard();
  int move();
  bool checkLegal();
  void display();
  void clear();
  void generate();
  char StartMenu();
  char dispCredits();
  void GenerateBoardGUI();
  char dispRules();
  char dispStats();
  int CScore();
  int HScore();
  void changeScore();

};

int main(void)
{
  LCD.Clear();
  /* Here is the object creation for grid, which is of the class GameBoard */
  GameBoard grid;
  bool checker = true;
  char choice = 'a';
  int resetter = 0;

/* Here is the example of the while loop. */
  while (true) {

/* Here is the example of the switch-case. */
  switch (choice){
  case 'a':

/* The case that displays the start menu using the StartMenu function */
      choice = grid.StartMenu();

      break;

  case 'b':

/* The case that executes the game itself */
      LCD.Clear();
      grid.generate();
      grid.display();
      grid.GenerateBoardGUI();

      while(checker == true){ //Checks whether the user has any possible moves left.

          resetter = grid.move();
          grid.generate();
          grid.display();
          grid.GenerateBoardGUI();
          checker = grid.checkLegal();

            if(resetter == 1){

                choice = 'a';
                break;

            } else if (resetter == 2){

                grid.clear();

            }


      }

/* Checks to see if back arrow was pressed */

    if(resetter != 1){
      LCD.Clear();
      LCD.Write("\n\n\n\nGame Ended. Your score was:");
      LCD.Write(grid.CScore());

      /* Checks if the user's score beat the high score, and replaces the high score if the user's is greater */

/* Here is an example of an if statement */
/* Additionally, here is an example of a relational operator */
      if(grid.CScore() > grid.HScore()){

        grid.changeScore();
        LCD.Write("New High Score!\n");
        LCD.Write("Congrats!\n");

      }

      grid.clear(); //Resetting game
    }

      break;

  case 'c':

      choice = grid.dispRules(); //Displays rules to the user and tracks whether they pressed the back button

      break;

  case 'd':

      choice = grid.dispStats(); //Displays statistics to the user and tracks whether they pressed the back button

      break;

  case 'e':

      choice = grid.dispCredits(); //Displays credits to the user and tracks whether they pressed the back button

      break;


      }
  }
}

/* Constructor creation */
GameBoard::GameBoard() {

 /* Filling board with 0s */
 /* Here is an example of a for structure */
   for(int i = 0; i < 4; i++){

       for(int j = 0; j < 4; j++){

           board[i][j] = 0;

       }

   }

/* Setting all variables to 0 */
   xPosition = 0;
   yPosition = 0;
   xTrash = 0;
   yTrash = 0;
   breaker = 0;
   highScore = 0;
   currentScore = 0;

}

int GameBoard::CScore(){

    return currentScore;

}

int GameBoard::HScore(){

    return highScore;

}

void GameBoard::changeScore(){

    highScore = currentScore;

}

/* Here is an example of a user defined function. */
char GameBoard::StartMenu(){

  /*
  What it does:
  - Draws Rectangles
  - Places Text in Rectangles
  - Takes touch input from respective box
  - Changes color of the rectangle with .Fill
  - Waits 200 ms
  - Clears screen
  - Executes what comes next
  */

      LCD.SetBackgroundColor(WHITESMOKE);

      char choice2 = 'a';
      LCD.SetFontColor(BLACK);
      LCD.Clear();
      xPosition = 0;
      yPosition = 0;
      xTrash = 0;
      yTrash = 0;

      //Title
      LCD.WriteAt("2048", 136, 2);

      //Start Game
      LCD.DrawRectangle(20, 25, 280, 50);
      LCD.WriteAt("      Start 2048 ", 30, 51);

      //Rules of Game
      LCD.DrawRectangle(20, 75, 280, 50);
      LCD.WriteAt(" Rules & Instructions", 30, 101);

      //Statistics
      LCD.DrawRectangle(20, 125, 280, 50);
      LCD.WriteAt("   View Statistics", 33, 151);

      //Credits
      LCD.DrawRectangle(20, 175, 280, 50);
      LCD.WriteAt("       Credits", 30, 201);

      Sleep(100);

      LCD.ClearBuffer();

/* Taking user input from screen */
      while(!LCD.Touch(&xPosition, &yPosition)){};

      while(LCD.Touch(&xTrash, &yTrash)){};

      //Start Game Button Press
      /* Here is an example of the logical operator (&&) */
      if((xPosition > 20 && xPosition < 300) && ((yPosition > 25) && (yPosition < 75)))
          {
              /* This section shows the button being pressed and sounds a noise */
          Buzzer.Tone(50, 200);
          LCD.SetFontColor(GRAY);
          LCD.FillRectangle(20, 25, 280, 50);
          Sleep(200);
          LCD.ClearBuffer();
          LCD.SetFontColor(BLACK);
          LCD.Clear(WHITESMOKE);
          choice2 = 'b';

          }

      //Rules of Game Button Press
      if((xPosition > 20 && xPosition < 300) && ((yPosition > 75) && (yPosition < 125)))
          {
              /* This section shows the button being pressed and sounds a noise */
          Buzzer.Tone(100, 200);
          LCD.SetFontColor(GRAY);
          LCD.FillRectangle(20, 75, 280, 50);
          Sleep(200);
          LCD.ClearBuffer();
          LCD.SetFontColor(BLACK);
          LCD.Clear(WHITESMOKE);
          choice2 = 'c';

          }

      //Statistics Button Press
      if((xPosition > 20 && xPosition < 300) && ((yPosition > 125) && (yPosition < 175)))
          {
              /* This section shows the button being pressed and sounds a noise */
          Buzzer.Tone(150, 200);
          LCD.SetFontColor(GRAY);
          LCD.FillRectangle(20, 125, 280, 50);
          Sleep(200);
          LCD.ClearBuffer();
          LCD.SetFontColor(BLACK);
          LCD.Clear(WHITESMOKE);
          choice2 = 'd';

          }

      //Credits Button Press
      if((xPosition > 20 && xPosition < 300) && ((yPosition > 175) && (yPosition < 225)))
          {
              /* This section shows the button being pressed and sounds a noise */
          Buzzer.Tone(200, 200);
          LCD.SetFontColor(GRAY);
          LCD.FillRectangle(20, 175, 280, 50);
          Sleep(200);
          LCD.ClearBuffer();
          LCD.SetFontColor(BLACK);
          LCD.Clear(WHITESMOKE);
          choice2 = 'e';

      }

      return choice2; //Used in switch-case to determine what user wants to view

}

void GameBoard::display(){

  LCD.Clear();
  int posX = 0;
  int posY = 0;

  /* Determining Y Position based off of row */
  for(int i = 0; i < 4; i++){
   posY = 8 + (i * 40);

/* Determining X position based off of column */
  for(int j = 0; j < 4; j++){
   posX = 45 + (j * 47);

/* Goes through every value in the board and prints to the position determined from its location in array */
          LCD.WriteAt(board[i][j], posX, posY);

      }

  }
}

/* Used to randomly generate a 2 in one of the empty spots on the board */
void GameBoard::generate(){

  int counter = 0;
  int empty = 0;

/* Checks if the board has an empty spot. If it doesn't, does not generate a 2*/
for (int i = 0; i < 4; i++){

    for(int j = 0; j < 4; j++){

        if(board[i][j] == 0){

            empty = 1;

        }

    }

}

/* Checks if there was a 0 on the board */
if(empty = 1) {

/* Runs until a 2 is placed */
  while(counter < 1){

      /* Randomizes where the 2 will be placed */
      int rowPos = (Random.RandInt())%4;
      int colPos = (Random.RandInt())%4;

/* Checks if the location is a 0. If it is, the 2 is placed there and the while loop ends */
  if(board[rowPos][colPos] == 0){

      board[rowPos][colPos] = 2;
      counter = counter + 1;

  }

  }
}
}

/* This function reads user input on screen and moves values in board */
int GameBoard::move(){

   int buttonCheck = 0;
   breaker = 0;

/* Takes user input from screen */
  while(!LCD.Touch(&xPosition, &yPosition)){};

  while(LCD.Touch(&xTrash, &yTrash)){};

/* Here is an example of a do-while structure. */
      do {
      /* North Touch */
      /* Here is an example of an if-else structure */
          if((xPosition > 100 && xPosition < 215) && (yPosition < 60)){
        Buzzer.Buzz(200);
              /* This portion of the code moves all of the spaces up into the top border until there are no spaces between the top wall and each of the numbers. */
              for(int i = 0; i < 4; i++){

              for(int k = 0; k < 4; k++){
                  if(board[0][i] == 0){

                      board[0][i] = board[1][i];
                      board[1][i] = board[2][i];
                      board[2][i] = board[3][i];
                      board[3][i] = 0;
                      breaker = 1; /* Breaks waiting for a touch if north actually does something */

                  } else if(board[1][i] == 0) {

                      board[1][i] = board[2][i];
                      board[2][i] = board[3][i];
                      board[3][i] = 0;
                      breaker = 1;

                  } else if(board[2][i] == 0) {

                      board[2][i] = board[3][i];
                      board[3][i] = 0;
                      breaker = 1;

                  }
               }
       }

              /* This portion of the code adds the numbers that are the same and pushed into eachother in the north direction. */

             for(int i = 0; i < 4; i++){

             if((board[0][i] == board[1][i]) && (board[0][i] != 0)){

                 board[0][i] = board[0][i]+board[1][i];
                 board[1][i] = board[2][i];
                 board[2][i] = board[3][i];
                 board[3][i] = 0;
                 currentScore = currentScore + board[0][i];
                 breaker = 1;

             }

             if((board[1][i] == board[2][i]) && (board[1][i] != 0)){

                 board[1][i] = board[2][i]+board[1][i];
                 board[2][i] = board[3][i];
                 board[3][i] = 0;
                 currentScore = currentScore + board[1][i];
                 breaker = 1;

             }

             if((board[2][i] == board[3][i]) && (board[2][i] != 0)){

                 board[2][i] = board[3][i]+board[2][i];
                 board[3][i] = 0;
                 currentScore = currentScore + board[2][i];
                 breaker = 1;

             }

             }

              Sleep(300);
}

      /* South Touch */
          else if((xPosition > 100 && xPosition < 215) && (yPosition > 160)){
        Buzzer.Buzz(200);
              /* This portion of the code moves all of the spaces up into the bottom border until there are no spaces between the bottom wall and each of the numbers. */
              for(int i = 0; i < 4; i++){

              for(int k = 0; k < 4; k++){
                  if(board[3][i] == 0){

                      board[3][i] = board[2][i];
                      board[2][i] = board[1][i];
                      board[1][i] = board[0][i];
                      board[0][i] = 0;
                      breaker = 1;

                  } else if(board[2][i] == 0) {

                      board[2][i] = board[1][i];
                      board[1][i] = board[0][i];
                      board[0][i] = 0;
                      breaker = 1;

                  } else if(board[1][i] == 0) {

                      board[1][i] = board[0][i];
                      board[0][i] = 0;
                      breaker = 1;

                  }
               }
       }

              /* This portion of the code adds the numbers that are the same and pushed into eachother in the south direction. */

             for(int i = 0; i < 4; i++){

             if((board[3][i] == board[2][i]) && (board[3][i] != 0)){

                 board[3][i] = board[3][i]+board[2][i];
                 board[2][i] = board[1][i];
                 board[1][i] = board[0][i];
                 board[0][i] = 0;
                 currentScore = currentScore + board[3][i];
                 breaker = 1;

             }

             if((board[2][i] == board[1][i]) && (board[2][i] != 0)){

                 board[2][i] = board[2][i]+board[1][i];
                 board[1][i] = board[0][i];
                 board[0][i] = 0;
                 currentScore = currentScore + board[2][i];
                 breaker = 1;

             }

             if((board[1][i] == board[0][i]) && (board[1][i] != 0)){

                 board[1][i] = board[1][i]+board[0][i];
                 board[0][i] = 0;
                 currentScore = currentScore + board[1][i];
                 breaker = 1;

             }

             }

              Sleep(300);

  }

      /* West Touch */
          else if((xPosition < 100) && ((yPosition > 60) && (yPosition < 180))){
        Buzzer.Buzz(200);
              /* This portion of the code moves all of the spaces up into the left border until there are no spaces between the left wall and each of the numbers. */
              for(int i = 0; i < 4; i++){

              for(int k = 0; k < 4; k++){
                  if(board[i][0] == 0){

                      board[i][0] = board[i][1];
                      board[i][1] = board[i][2];
                      board[i][2] = board[i][3];
                      board[i][3] = 0;
                      breaker = 1;

                  } else if(board[i][1] == 0) {

                      board[i][1] = board[i][2];
                      board[i][2] = board[i][3];
                      board[i][3] = 0;
                      breaker = 1;

                  } else if(board[i][2] == 0) {

                      board[i][2] = board[i][3];
                      board[i][3] = 0;
                      breaker = 1;

                  }
               }
       }

              /* This portion of the code adds the numbers that are the same and pushed into eachother in the west direction. */

             for(int i = 0; i < 4; i++){

             if((board[i][0] == board[i][1]) && (board[i][0] != 0)){

                 board[i][0] = board[i][0]+board[i][1];
                 board[i][1] = board[i][2];
                 board[i][2] = board[i][3];
                 board[i][3] = 0;
                 currentScore = currentScore + board[i][0];
                 breaker = 1;

             }

             if((board[i][1] == board[i][2]) && (board[i][1] != 0)){

                 board[i][1] = board[i][2]+board[i][1];
                 board[i][2] = board[i][3];
                 board[i][3] = 0;
                 currentScore = currentScore + board[i][1];
                 breaker = 1;

             }

             if((board[i][2] == board[i][3]) && (board[i][2] != 0)){

                 board[i][2] = board[i][3]+board[i][2];
                 board[i][3] = 0;
                 currentScore = currentScore + board[i][2];
                 breaker = 1;

             }

             }

              Sleep(300);

  }
      /* East Touch */
          else if((xPosition > 260) && ((yPosition > 60) && (yPosition < 180))){
        Buzzer.Buzz(200);
              /* This portion of the code moves all of the spaces up into the right border until there are no spaces between the right wall and each of the numbers. */
              for(int i = 0; i < 4; i++){

              for(int k = 0; k < 4; k++){
                  if(board[i][3] == 0){

                      board[i][3] = board[i][2];
                      board[i][2] = board[i][1];
                      board[i][1] = board[i][0];
                      board[i][0] = 0;
                      breaker = 1;

                  } else if(board[i][2] == 0) {

                      board[i][2] = board[i][1];
                      board[i][1] = board[i][0];
                      board[i][0] = 0;
                      breaker = 1;

                  } else if(board[i][1] == 0) {

                      board[i][1] = board[i][0];
                      board[i][0] = 0;
                      breaker = 1;

                  }
               }
       }

              /* This portion of the code adds the numbers that are the same and pushed into eachother in the east direction. */

             for(int i = 0; i < 4; i++){

             if((board[i][3] == board[i][2]) && (board[i][3] != 0)){

                 board[i][3] = board[i][3]+board[i][2];
                 board[i][2] = board[i][1];
                 board[i][1] = board[i][0];
                 board[i][0] = 0;
                 currentScore = currentScore + board[i][3];
                 breaker = 1;

             }

             if((board[i][2] == board[i][1]) && (board[i][2] != 0)){

                 board[i][2] = board[i][2]+board[i][1];
                 board[i][1] = board[i][0];
                 board[i][0] = 0;
                 currentScore = currentScore + board[i][2];
                 breaker = 1;

             }

             if((board[i][1] == board[i][0]) && (board[i][1] != 0)){

                 board[i][1] = board[i][1]+board[i][0];
                 board[i][0] = 0;
                 currentScore = currentScore + board[i][1];
                 breaker = 1;

             }

             }

              Sleep(300);

      } else if((xPosition > 0) && (xPosition < 60) && (yPosition > 0) && (yPosition < 60)){

          /* This portion checks if the back button was pressed. It will break from the game and go back to the main screen. */

        LCD.SetFontColor(STEELBLUE); //Shows press
          LCD.FillRectangle(10,10,30,30);
          Buzzer.Buzz(200);
          Sleep(200);
          LCD.ClearBuffer();
          LCD.SetFontColor(BLACK);

          breaker = 1;
          buttonCheck = 1;

      } else if((xPosition > 280) && (xPosition < 320) && (yPosition > 0) && (yPosition < 60)){

          /* This portion checks if the reset button was pressed. It will reset the board and current score if it was pressed */

          LCD.SetFontColor(MAROON); //Shows press
          LCD.FillRectangle(280,10,30,30);
          Buzzer.Buzz(200);
          Sleep(200);
          LCD.ClearBuffer();
          LCD.SetFontColor(BLACK);

          breaker = 1;
          buttonCheck = 2;

      }

   } while(breaker = 0);

    return buttonCheck;

}

/* Checks whether there are no more possible moves */
bool GameBoard::checkLegal(){

  bool checker = false;

/* Checking for spaces */
for(int i = 0; i < 4; i++){

  for(int j = 0; j < 4; j++){

      if(board[i][j] == 0){

          checker = true;

      }

  }

}

/* Checking Rows */
for (int i = 0; i < 4; i++){

  if((board[i][0] == board[i][1]) || (board[i][1] == board[i][2]) || (board[i][2] == board[i][3])){

      checker = true;

  }

}

/* Checking columns */

for (int j = 0; j < 4; j++){

  if((board[0][j] == board[1][j]) || (board[1][j] == board[2][j]) || (board[2][j] == board[3][j])){

      checker = true;

  }

}

/* Returns true if there is a possible move, false if no moves are possible */
return checker;

}

/* Clears the board and score */
void GameBoard::clear(){

/* Setting the board values to 0 */

for(int i = 0; i < 4; i++){

    for(int j = 0; j < 4; j++){

        board[i][j] = 0;

    }

}

/* Sets new high score */
if(currentScore > highScore){

    highScore = currentScore;

}

/* Resetting current score */
currentScore = 0;

}

/* Displays rules to the user */
char GameBoard::dispRules()
{

  char choice3;
  LCD.SetFontColor(PALETURQUOISE); //Back Button
  LCD.FillRectangle(10,10,30,30);
  LCD.SetFontColor(BLACK);

/* Writes the rules for the user to view */
  LCD.WriteAt("How to Play & Help", 50, 30);
  LCD.Write("\n\n\n\nTouch N, S, E, \nor W to move.\nEqual tiles will be\ncombined into a double\nA new '2' will appear\nWhen no moves available,\n you lose.\nRed button to clear.\nRestart if glitch occurs.");

  Sleep(100);
  LCD.ClearBuffer();

/* Waits for user to press back button */
  while(!LCD.Touch(&xPosition, &yPosition)){};
  while(LCD.Touch(&xTrash, &yTrash)){};

  if ((xPosition > 10 && xPosition < 60) && (yPosition > 10 && yPosition < 60)){
  LCD.SetFontColor(STEELBLUE); //Shows pressed button
  LCD.FillRectangle(10,10,30,30);
  Buzzer.Buzz(200);
  Sleep(200);
  LCD.ClearBuffer();
  LCD.SetFontColor(BLACK);

      choice3 = 'a';

  }

  return choice3;

}

/* Displays stats to the user */
char GameBoard::dispStats(){

  char choice4;
  LCD.SetFontColor(PALETURQUOISE); //Back Button
  LCD.FillRectangle(10,10,30,30);
  LCD.SetFontColor(BLACK);

/* Shows current score and highest score */
  LCD.Write("\n\n\n\nCurrent Score: ");
  LCD.Write(currentScore);
  LCD.Write("\n\nHighest Score: ");
  LCD.Write(highScore);

  Sleep(100);
  LCD.ClearBuffer();

/* Waits for button press to go back */
  while(!LCD.Touch(&xPosition, &yPosition)){};
  while(LCD.Touch(&xTrash, &yTrash)){};

  if ((xPosition > 10 && xPosition < 60) && (yPosition > 10 && yPosition < 60)){
    LCD.SetFontColor(STEELBLUE); //Shows press
    LCD.FillRectangle(10,10,30,30);
    Buzzer.Buzz(200);
    Sleep(200);
    LCD.ClearBuffer();
    LCD.SetFontColor(BLACK);

  choice4 = 'a';
  }
return choice4;

}

/* Displays the credits to the user */
char GameBoard::dispCredits(){

  char choice5;
  LCD.SetFontColor(PALETURQUOISE); //Back Button
  LCD.FillRectangle(10,10,30,30);
  LCD.SetFontColor(BLACK);

/* Writes the credits to the screen */
LCD.Write("\n\n\n\nGame Credits \n2048 for PROTEUS \nWritten by: \nJames Kolimago \n& Michael Sidenstick \nFEH 2019 Ohio State \n");

Sleep(100);
LCD.ClearBuffer();

/* Waits for user to press screen */
while(!LCD.Touch(&xPosition, &yPosition)){};
while(LCD.Touch(&xTrash, &yTrash)){};

if ((xPosition > 10 && xPosition < 60) && (yPosition > 10 && yPosition < 60)){
  LCD.SetFontColor(STEELBLUE); //Shows press
  LCD.FillRectangle(10,10,30,30);
  Buzzer.Buzz(200);
  Sleep(200);
  LCD.ClearBuffer();
  LCD.SetFontColor(BLACK);

  choice5 = 'a';

}

return choice5;

}


void GameBoard::GenerateBoardGUI()
{
//Generates 5 vertical and 5 horizontal lines.
//Will produce a 4x4 grid with dimensions of 50 x 50
//Initial position is (75,45)
//Also creates rectangles for where the score and return to start boxes will be

//Defines for loop variables and variable for x and y position
int rowGrid;
int colmGrid;
int currentRowY, currentColmX;
char choice6;
//This should fix the grid
//Draws 5 Horizontal Lines,
for (rowGrid = 0; rowGrid < 5; rowGrid++)
{
   //Cumulatively changes row initial position
   currentRowY = 5 + (40 * rowGrid);

   LCD.DrawHorizontalLine(currentRowY, 43, 231); //Draws line

}
//Draws 5 vertical lines
for (colmGrid = 0; colmGrid < 5; colmGrid++)
{
   //Cumulatively changes column initial position
   currentColmX = 43 + (47 * colmGrid);

   LCD.DrawVerticalLine(currentColmX, 5, 165); //Draws line

}

//Sets Rectangles for score and return
//Makes a box and displays a button for BACK. Still needs a way to return to start. Maybe make function char or put a new function in
LCD.SetFontColor(PALETURQUOISE); //Back Button
LCD.FillRectangle(10,10,30,30);

//Sets Rectangle for Resetting
LCD.SetFontColor(SCARLET); //Reset Button
LCD.FillRectangle(280,10,30,30);

//Reinitialize background and font
LCD.SetFontColor(BLACK); //Font and lines set BLACK
LCD.SetBackgroundColor(WHITESMOKE);

//Places score on board
LCD.WriteAt("Current Score:", 25, 210);
LCD.WriteAt(currentScore, 225, 210);

}


