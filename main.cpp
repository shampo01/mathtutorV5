/***************************************************************************************
Program: MathTutorV3
Programmer(s): Andrew Hogue, Shadrack Ampofo
Date: 11/3/24
github URL: https://github.com/anhogue01/Math_TutorV4
Description:
- This is a simple math tutoring program that asks the user to solve math problems.
- The user can solve addition, subtraction, multiplication, and division problems.
- The program includes multiple attempts for each problem, levels up or down depending
  on correct/incorrect answers, and allows the user to continue playing until they quit.
****************************************************************************************/

#include <iostream> // required for cin/cout
#include <cstdlib>  // required for rand() and srand()
#include <ctime>    // required for time()
#include <string>   // needed for the string userName;
#include <limits>   // for numeric_limits
#include <cctype>   // for tolower
#include <iomanip>  // for setw
#include <vector>   // for the 2d vector
using namespace std; // needed to define the namespace

// Constant - values that dont change
const int MAX_ATTEMPTS = 3; // The user gets 3 tries to answer
const int LEVEL_RANGE_CHANGE = 10; // The level range changes by 10

// Enum for Math Operations - it's a way to give names to numbers
enum MathType {ADDITION = 1, SUBTRACTION, MULTIPLICATION, DIVISION};

// Functions
void askQuestion(int level, MathType mathType, int& correct, int& incorrect, int range, string userName);
bool validateAnswer(int userAnswer, int correctAnswer);
bool getContinueResponse();
int getMathAnswer(int leftNum, int rightNum, MathType mathType);
void displaySummary( const vector<vector<int>>& questions);

int main() {
    // Varibles
    string userName = "unknown"; // stores the users name
    int correct = 0;             // counter for the number of correct answers
    int incorrect = 0;           // counter for the number of incorrect answers
    int mathLevel = 1;           // starting math level for the user
    int currentRange = LEVEL_RANGE_CHANGE; // the range of numbers (starts between 1 and 10)
    int mathType = 0;            // math operation type
    char mathSymbol = '?';       // to represent the math symbol
    vector<vector<int>> questions; // 2d vector to store question data

    // seed random number generation
    srand(time(0));

    // intro and header to the program
    cout << " __  __       _   _       _____      _             " << endl;
    cout << "|  \\/  | __ _| |_| |__   |_   _|   _| |_ ___  _ __ " << endl;
    cout << "| |\\/| |/ _` | __| '_ \\    | || | | | __/ _ \\| '__|" << endl;
    cout << "| |  | | (_| | |_| | | |   | || |_| | || (_) | |   " << endl;
    cout << "|_|  |_|\\__,_|\\__|_| |_|   |_| \\__,_|\\__\\___/|_|   " << endl;
    cout << endl;
    cout << "***************************************************" << endl;
    cout << "*    Welcome to the C++ Calcualtor!       :)      *" << endl;
    cout << "***************************************************" << endl;
    cout << endl;
    cout << "Super Funny Math Jokes:" << endl;
    cout << endl;
    cout << "     * Why was the math book sad? It had too many problems!" << endl;
    cout << "     * Parallel lines have so much in common." << endl;
    cout << "       Its a Shame they will never meet." << endl;
    cout << "     * Where do math lovers go on vacation? Times Square." << endl;
    cout << endl;
    cout << "****************************************************" << endl;
    cout << endl;


    cout << "Please enter your name: " << endl;
    cin >> userName;
    cout << "Welcome " << userName << " to the C++ Calculator!" << endl; //outputs the users name
    cout << endl;
    cout << "Complete the following math problem:" << endl;
    cout << endl;

    // Main program loop - this loop runs until the user chooses to stop
    do {
        // randomize math operation for each question
        mathType = rand() % 4 + 1;

        // asks the user a math question (with a randomly selected math type)
        switch(mathType) {
            case 1:
                askQuestion(mathLevel, ADDITION, correct, incorrect, currentRange, userName);
            break;
            case 2:
                askQuestion(mathLevel, SUBTRACTION, correct, incorrect, currentRange, userName);
            break;
            case 3:
                askQuestion(mathLevel, MULTIPLICATION, correct, incorrect, currentRange, userName);
            break;
            case 4:
                askQuestion(mathLevel, DIVISION, correct, incorrect, currentRange, userName);
            break;
            default:
                cout << "Error: Invalid Math Type!" << endl;
            cout << "Please Contact 555-555-5555 to report any bugs" << endl;
            return -1;
        }

        // check if the user should level up or down
        if (correct == 3) {
            mathLevel++;
            currentRange += LEVEL_RANGE_CHANGE; // increase range when leveling up
            cout << "Great job! You're leveling up to level " << mathLevel << endl;
            cout << "Now the numbers are between 1 and " << currentRange << endl;
            correct = 0; // reset correct/incorrect counters
            incorrect = 0;
        } else if (incorrect == 3 && mathLevel > 1) {
            mathLevel--;
            currentRange -= LEVEL_RANGE_CHANGE; // decreases range when leveling down
            cout << "OOPS! You're leveling down to level " << mathLevel << endl;
            cout << "Now the numbers are between 1 and " << currentRange << endl;
            correct = 0; //reset correct/incorrect counters
            incorrect = 0;
        }

    } while (getContinueResponse()); // continue as long as the user wants to

    // display the summary report before quitting
    displaySummary(questions);
    cout << "Nice Try! Keep practicing your math" << endl;
    return 0; // end of main function
}
// function definitions - this section defines how each function behaves

//function to ask a math question
void askQuestion(int level, MathType mathType, int& correct, int& incorrect, int range, string userName) {
    // integers for the left and right numbers in the math question
    int leftNum = rand() % range + 1;
    int rightNum = rand() % range + 1;

    // to make sure leftNum is divisible nby right
    if(mathType == DIVISION) {
        // ensure that the two numbers can divide evenly (whole number answer)
        while (rightNum == 0 || leftNum % rightNum != 0) {
            leftNum = rand() % range + 1;
            rightNum = rand() % range + 1;
        }
    }

    // the correct answer, based on math type (addition, subtraction, etc...)
    int correctAnswer = getMathAnswer(leftNum, rightNum, mathType);
    int userAnswer; // stores the user's answer
    char mathSymbol = '?'; //  math symbol based on operation

    // assign the math symbol based on the operation
    switch (mathType) {
        case ADDITION:
            mathSymbol = '+';
        break;
        case SUBTRACTION:
            mathSymbol = '-';
        break;
        case MULTIPLICATION:
            mathSymbol = '*';
        break;
        case DIVISION:
            mathSymbol = '/';
        break;
    }

    // the user has 3 attempts to answer the question
    for (int i = 1; i <= MAX_ATTEMPTS; i++) {
        cout << "[Level #" << level << "] " << userName << ", What is " << leftNum << " "<< mathSymbol << " " << rightNum << "? ";
        cin >> userAnswer;

        // check if the user's input is valid (must be a number)
        while (!cin) {
            cin.clear(); // clear the input error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard bad input
            cout << "Invalid input. Please enter a number: ";
            cin >> userAnswer;
        }

        // check if the answer is correct
        if (validateAnswer(userAnswer, correctAnswer)) {
            cout << "Correct! Well done.\n";
            correct++; // increase the correct answer count
            return; // exit the function because the answer was correct
        } else {
            cout << "Incorrect.\n";
            if (i < MAX_ATTEMPTS) {
                cout << "You have " << (MAX_ATTEMPTS - i) << " attempt(s) left.\n";
            } else {
                cout << "No more tries. The correct answer was " << correctAnswer << endl;
                incorrect++; // increase the incorrect answer count
            }
        }
    }
}

// function to check if the user's answer is correct
bool validateAnswer(int userAnswer, int correctAnswer) {
    return userAnswer == correctAnswer; // returns true if answers match
}

// function to ask if the user wants to continue
bool getContinueResponse() {
    char choice; // store the user's choice (y/n)
    cout << "Do you want to continue? (y/n) ";
    cin >> choice;
    return choice == 'y' || choice == 'Y'; // return true is the user says yes
}

// function to get the correct answer based on the math operation
int getMathAnswer(int leftNum, int rightNum, MathType mathType) {
    // return the correct answer based on the math type
    switch (mathType) {
        case ADDITION:
            return leftNum + rightNum;
        case SUBTRACTION:
            return leftNum - rightNum;
        case MULTIPLICATION:
            return leftNum * rightNum;
        case DIVISION:
            if (rightNum != 0)
                return leftNum / rightNum;
            else
                return 0; // return 0 if rightNum is 0 to avoid crash
        default:
            return 0;
    }
    void displaySummary(const vector<vector<int>>& questions) {
        cout <<"\nSummary of Your Math Questions: \n"
        cout << setw(10) << "level" <<setw(15) <<" Question" << setw(10) << "Answer" << setw(15) << "Attempts" << endl;
        cout << string(50, '-') <<endl;

        for (const auto& q : questions)
            char mathSymbol =q[2];
            cout << setw(10) << q[0]
                 << setw(15) << q[1] << ' '<< mathSymbol << ' ' << q[3]
                 << setw(10) << q[4]
                  << setw(15) << q[5] >0 ? to_string(q[5]) : "Incorrect") << endl;


        }

    }

}