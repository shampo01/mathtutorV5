// This is the header file for the Math Tutor version 5 project
#ifndef MATHTUTOR_H
#define MATHTUTOR_H

#include <iostream>
#include <vector>
#include <string>
#include <ctime> // Needed for system time



using namespace std;



// Function Prototypes
void DisplayGameIntro();
string GetUserName();
int GetNumericValue();
string AskToPlayAgain(string userName);
void DisplaySummaryReport(const vector<vector<int>> &allQuestions);
vector<int> GenerateRandomQuestion(int mathLevel, int currentRange);
bool GiveThreeAttempts(string userName, vector<int> &currentQuestion, int &totalCorrect, int &totalIncorrect);
void CheckForLevelChange(int &totalCorrect, int &totalIncorrect, int &mathLevel, int &currentRange);

#include "MathTutor.cpp"
#endif //MATHTUTOR_H
