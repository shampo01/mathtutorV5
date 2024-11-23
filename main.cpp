/***************************************************************************
Course Section: Section 3 - 12:00 p.m.
Program: MathTutorV5
Programmers: Shadrack Ampofo
Date: 11/23/2024
GitHub URL: https://github.com/shampo01/mathtutorV5.git
This is a simple math tutoring program that asks the user to solve math problems.
- The user can solve addition, subtraction, multiplication, and division problems.
- The program includes multiple attempts for each problem, levels up or down depending
  on correct/incorrect answers, and allows the user to continue playing until they quit.
****************************************************************************************/


#include "MathTutor.h"
#include <iostream> // Needed for cin/cout, /t for tab spacing, and left and right alignment
#include <string> // Needed for string variables - date types
#include <cstdlib> // Needed for random numbers
#include <limits> // Used for limits library
#include <vector> // used so we can make our 2D Vector
#include <iomanip> //for the setw
using namespace std;

int main() {
    int totalCorrect = 0; // Used to calculate the total correct questions a user has gotten
    int totalIncorrect = 0; // Used to calculate the total incorrect questions a user has gotten
    int mathLevel = 1; // Used for the math level
    int currentRange = 10; // Initial range of random numbers
    vector<vector<int> > questions; //stores every question the suer answers
    string userName, userInput; // Gets the user answer
    bool playAgain = true;

    // Seed the random number generator
    srand(time(0));

    // Displays the game's intro and gets the user's name
    DisplayGameIntro();
    userName = GetUserName();

    // Shows if the user wants to play again
    while (playAgain) {
        // Generate a random math question
        vector<int> question = GenerateRandomQuestion(mathLevel, currentRange);

        // Allow the user to attempt the question
        GiveThreeAttempts(userName, question, totalCorrect, totalIncorrect);

        // Record the question for the summary
        questions.push_back(question);

        // Check for level changes
        CheckForLevelChange(totalCorrect, totalIncorrect, mathLevel, currentRange);

        // Ask the user if they want to play again
        userInput = AskToPlayAgain(userName);
        playAgain = (userInput == "y" || userInput == "yes");
    }

    // Shows the summary of the questions in a proper display
    DisplaySummaryReport(questions);

    // Displaying to the User that the Program is Finished and that it will be back.
    cout << endl << "\tCheck back soon for the next version. Goodbye!" << endl;
    return 0;
}