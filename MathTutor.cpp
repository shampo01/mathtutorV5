#include <iostream> // Needed for cin/cout, /t for tab spacing, and left and right alignment
#include <string> // Needed for string variables - date types
#include <cstdlib> // Needed for random numbers
#include <limits> // Used for limits library
#include <vector> // used so we can make our 2D Vector
#include <iomanip> //for the setw

using namespace std; // used to not put "std" in cin/cout


const int LEVEL_RANGE_CHANGE = 10; // Changes the range of questions
const int MAX_ATTEMPTS = 3; // Giving the user the amount of max attempts

//Defining the functions and
void DisplayGameIntro() {

    // Displaying the Program Intro/Presentation.
    cout << " ______________________________________________________________ " << endl;
    cout << "                                                                " << endl;
    cout << "    __  __         _    _       _______      _                  " << endl;
    cout << "   |  ||  |       | |  | |     |__   __|    | |                 " << endl;
    cout << "   |      |  __ _ | |_ | |__      | | _   _ | |_  ___   _ __    " << endl;
    cout << "   | |||| | / _` || __|| '_ |     | || | | || __|/ _ | | '__|   " << endl;
    cout << "   | |  | || (_| || |_ | | | |    | || |_| || |_| (_) || |      " << endl;
    cout << "   |_|  |_| |__,_| |__||_| |_|    |_| |__,_| |__||___/ |_|      " << endl;
    cout << "                                                                " << endl;
    cout << " ______________________________________________________________ " << endl;
    cout << endl;
    cout << "|           Welcome to the Craziest Math Tutor Game!           |" << endl;
    cout << " ______________________________________________________________ " << endl;
    cout << endl;

    // Displaying for the User Fun Facts about Math that are Interesting.
    cout << "-\tFun Math Facts! " << endl;
    cout << endl;
    cout << "\t    * The most used number in math is 3." << endl;
    cout << "\t    * Every odd number has an (e) in it." << endl;
    cout << "\t    * -40 Celcius is -40 Fahrenheit." << endl;
    cout << "\t    * Zero is not represented in Roman numerals." << endl;
    cout << endl;
    cout << " ______________________________________________________________ " << endl;

    return;
}; //

// The function below gets the users name ans returns it so it can be passed in other functions
string GetUserName() {
    string userName;
    cout << "*\tPlease enter your name: ";
    getline(cin, userName);
    cout << endl << "*\tWelcome " << userName << " to the Math Tutor!" << endl;
    return userName;
}

// Get the input from the user and makes sure it's a number and not any other character
int GetNumericValue() {
    int userAns;
    while (!(cin >> userAns)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\tInvalid input! Please enter a number: ";
    }
    return userAns;
}

// The function that asks the user whether they would like to play again and returns yes or no which are the user's input
string AskToPlayAgain(string userName) {
    string userInput;
    while (true) {
        cout << "*\tDo you want to continue, " << userName << "? (y=yes | n=no): ";
        cin >> userInput;
        for (auto &c: userInput) c = tolower(c); // Gets the user input for if they want to continue
        if (userInput == "y" || userInput == "yes" || userInput == "n" || userInput == "no") {
            break;
        } else {
            cout << "*\tInvalid input, please try again..." << endl;
        }
    }
    return userInput; // returns a string
}


// It is the vector function that generates a random question and uses an "enum" and returns the
vector<int> GenerateRandomQuestion(int mathLevel, int currentRange) {
    enum MathType { MT_ADD = 1, MT_SUB, MT_MUL, MT_DIV };
    MathType questionType = static_cast<MathType>(rand() % 4 + 1);
    int leftNum = rand() % currentRange + 1;
    int rightNum = rand() % currentRange + 1;
    char symbol = '?';
    int correctAnswer = 0;

    // Switches the question type
    switch (questionType) {
        case MT_ADD: // used for addition
            symbol = '+';
            correctAnswer = leftNum + rightNum;
            break;
        case MT_SUB: // used for subtraction
            symbol = '-';
            if (leftNum < rightNum) swap(leftNum, rightNum);
            correctAnswer = leftNum - rightNum;
            break;
        case MT_MUL: // used for multiplication
            symbol = '*';
            correctAnswer = leftNum * rightNum;
            break;
        case MT_DIV: // used for division
            symbol = '/';
            correctAnswer = leftNum;
            leftNum *= rightNum;
            break;  // This shows that the code is broken, it displays a message.
        default:
            break;
    }
    return {mathLevel, leftNum, static_cast<int>(symbol), rightNum, correctAnswer, 0};
}

// function assigned to give 3 attempts to the user and return whether he or she got it true or not
bool GiveThreeAttempts(string userName, vector<int> &currentQuestion, int &totalCorrect, int &totalIncorrect) {
    int userAns = 0;
    bool isCorrect = false;
    for (int i = 1; i <= MAX_ATTEMPTS; ++i) {  // Shows what level the user is on
        cout << "[Level #" << currentQuestion[0] << "] " << userName
             << ", what is " << currentQuestion[1] << " "
             << char(currentQuestion[2]) << " " << currentQuestion[3] << "? ";
        userAns = GetNumericValue();

        // Check if the answer is correct
        if (userAns == currentQuestion[4]) {
            cout << "\tCorrect! Well done!" << endl;
            currentQuestion[5] = i;
            totalCorrect++;
            isCorrect = true;
            break;
        } else {
            cout << "\tIncorrect. ";
            if (i < MAX_ATTEMPTS) cout << "Try again." << endl; // Shows how many attempts they have left
        }
    }

    if (!isCorrect) {
        currentQuestion[5] = 0;
        totalIncorrect++;
        cout << "\tOut of attempts. The correct answer was: " << currentQuestion[4] << endl;
    }

    return isCorrect;
}


// The function below checks if the user gets 3 correct and levels them up and if they get 3 incorrect and they are in
// (follow up) a level higher than 1 and reduces it by one and also alongside the level of the questions asked
void CheckForLevelChange(int &totalCorrect, int &totalIncorrect, int &mathLevel, int &currentRange) {
    if (totalCorrect >= 3) {
        mathLevel++; // Increases the math level
        currentRange += LEVEL_RANGE_CHANGE; // Increase range to have harder questions
        totalCorrect = 0; // Shows the user how many answers they got correct
        totalIncorrect = 0; // Shows the user how many answers they got incorrect
        cout << "*\tLeveling up to Level " << mathLevel << ". Range: 1-" << currentRange << endl;
    } else if (totalIncorrect >= 3 && mathLevel > 1) {
        mathLevel--; // Decreases the math level
        currentRange -= LEVEL_RANGE_CHANGE; // Decrease range for easier questions
        totalCorrect = 0; // Shows the user how many answers they got correct
        totalIncorrect = 0; // Shows the user how many answers they got incorrect
        cout << "*\tLeveling down to Level " << mathLevel << ". Range: 1-" << currentRange << endl;
    } else if (totalIncorrect >= 3) {
        mathLevel--; // If all the questions are wrong then you failed because the level cannot decrease anymore
        totalCorrect = 0; // Shows the user how many answers they got correct
        totalIncorrect = 0; // Shows the user how many answers they got incorrect
    }
    return;
}
// The function below displays the final report of the user
void DisplaySummaryReport(const vector<vector<int>> &allQuestions) {
    int totalCorrect = 0;
    int totalIncorrect = 0;

    cout << "=======================================" << endl;
    cout << "              Summary Report           " << endl;
    cout << "========================================" << endl;
    cout << setw(10) << left << "Level"
         << setw(15) << left << " Question"
         << setw(10) << left << "  Attempts" << endl;
    cout << "------  ----------------  -----------" << endl;

    for (const auto &q : allQuestions) {
        int questionLevel = q[0]; // Used for the level of Questions
        int qLeftNum = q[1]; // Generate random numbers between 1 and 10
        char qMathSymbol = static_cast<char>(q[2]); // Gets characters
        int qRightNum = q[3]; // Generate random numbers between 1 and 10
        int qCorrectAns = q[4]; // Used for the correct answer
        int qAttempts = q[5]; // Includes Initial Attempts

        // displays question details mathlevel, leftNum, symbol, rightNum, =, correctAnswer, then attempts per question
        cout << setw(10) << left << questionLevel
             << setw(2) << left << qLeftNum << " " << qMathSymbol << " " <<setw(2)<< left << qRightNum<< setw(2)<<right<<" = "<<  qCorrectAns;

        // Displays the number of attempts or Incorrect
        if (qAttempts == 0) {
            cout << setw(15) << "Incorrect" << endl;
            totalIncorrect++;
        } else {
            cout << setw(11) << qAttempts << endl;
            totalCorrect++;
        }
    }

    // Displays the Summary Totals
    cout << endl;
    cout << "* Total Questions: " << setw(3) << allQuestions.size() << endl;
    cout << "* Total Correct..: " << setw(3) << totalCorrect << endl;
    cout << "* Total Incorrect: " << setw(3) << totalIncorrect << endl;
    cout << "* Average correct : " << setw(3) << (static_cast<double>(totalCorrect)/static_cast<double>(allQuestions.size()))*100 << "%"<< endl;
    cout << "___________________________________ " << endl;
}