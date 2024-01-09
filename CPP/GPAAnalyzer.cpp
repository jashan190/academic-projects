// GPA Analyzer.cpp
// Jashandeep Singh, CISP 400
// 9/24/2023

#include <iostream>
#include <ctime> // for system date
#include <sstream>
using namespace std;

// Function Prototypes
void ProgramGreeting();
void addGrade(int &count, int grades[], int &sum);
void displayGrades(int count, int grades[]);
void processGrades(int count, int sum);
char getLetterGrade(double grade);
char Grade2Lttr(int grade);
void usingheap(int*& grade, int& capcacity);
int getmenuChoice();
void displayDate();
void unitTest();

class FancyText {
public:
  static void print (const string& text, const string& color){
    cout << color << text << "\033[0m"; 
  }
};
//Specification A1 - Date Class
class Date {
public:
  Date();//Specification A2- External Date Initialization
  void SetDate(int newMonth, int newDay, int newYear);
  void displayDate() const;
  //Specification A3- Componet Test Method in Date
  static void CompTest();
private:
  int month, day, year;
  bool isDateValid(int newMonth, int newDay, int newYear) const;
};

int main() {
    unitTest();
    ProgramGreeting();
    Date::CompTest();
    displayDate();
    
    //Specification B1 - Dynamic Array 
    //Specification B2 - Add elements
    int* grades = new int[1];
    int count = 0;               // Counter for the number of grades
    int sum = 0;                 // Sum of grades

    int choice;
    do {

        choice = getmenuChoice();
      

        switch (choice) {
            case 1:
                usingheap(grades,count); 
                addGrade(count, grades, sum);
                break;
            case 2:
                cout << "The scores entered so far are: " << endl; 
                displayGrades(count, grades);
                break;
            case 3:
                processGrades(count, sum);
                break;
            case 4:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

    } while (choice != 4);
  
    delete[] grades; 
    
    return 0;
}
//Specification A4-Unit
void unitTest() {
    cout << "Running Component Test for Date class..." << endl;
    Date::CompTest();
    
    cout << "Running score to letter grade conversion tests..." << endl;
    struct GradeTest {
        int score;
        char expectedLetter;
    };
    
    GradeTest gradeTests[] = {
        {95, 'A'},
        {85, 'B'},
        {75, 'C'},
        {65, 'D'},
        {55, 'F'},
        {105, 'F'},  // score too high
        {-5, 'F'}    // score too low
    };
    
    for (const auto& test : gradeTests) {
        char letter = getLetterGrade(test.score);
        if (letter == test.expectedLetter) {
            cout << "Test PASSED for score " << test.score << ". Expected: " << test.expectedLetter << ", Got: " << letter << endl;
        } else {
            cout << "Test FAILED for score " << test.score << ". Expected: " << test.expectedLetter << ", Got: " << letter << endl;
        }
    }
    
    cout << "Unit tests completed." << endl;
}
// Specification C1-Program Greeting
void ProgramGreeting(){
    cout << "\nHello and welcome to my GPA Analyzer program!" << endl;
    cout << "Author: Jashandeep Singh" << endl;
    cout << "Due Date: September 24, 2023" << endl;
}
// functions for date
void displayDate(){
  Date currentDate;
  currentDate.displayDate();
}
Date::Date(){
  time_t now = time(0);
  tm *ltm = localtime(&now);
  year = 1900 + ltm->tm_year;
  month = 1 + ltm->tm_mon;
  day = ltm->tm_mday;
}

void Date::SetDate(int newMonth, int newDay, int newYear) {
    if(isDateValid(newMonth, newDay, newYear)) {
        month = newMonth;
        day = newDay;
        year = newYear;
    } else {
        cout << "Invalid date. No changes made." << endl;
    }
}
void Date::displayDate() const {
    cout << month << '/' << day << '/' << year << endl;
}
void Date::CompTest() {
    Date testDate;
    testDate.SetDate(9, 24, 2023);  // Assuming 9/24/2023 is a valid date.

    // Capture the standard output.
    std::stringstream buffer;
    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf(buffer.rdbuf());

    testDate.displayDate();  // Now the output goes to the buffer.

    // Restore original buffer before checking.
    std::cout.rdbuf(oldCoutStreamBuf);

    string dateOutput = buffer.str();
    string expectedOutput = "9/24/2023\n";

    if (dateOutput == expectedOutput) {
        cout << "CompTest PASSED." << endl;
    } else {
        cout << "CompTest FAILED. Expected: " << expectedOutput << " Got: " << dateOutput << endl;
    }
}

bool Date::isDateValid(int newMonth, int newDay, int newYear) const {
    // Check the validity of the month
    if (newMonth < 1 || newMonth > 12) return false;
    
    // Check the validity of the day, based on the month
    if (newDay < 1) return false;
    if (newMonth == 4 || newMonth == 6 || newMonth == 9 || newMonth == 11) {
        if (newDay > 30) return false;
    } else if (newMonth == 2) {
        // For simplicity, not considering leap years
        if (newDay > 28) return false;
    } else {
        if (newDay > 31) return false;
    }
    
    // Check the validity of the year
    if (newYear < 0) return false;  // or any other constraint you have on the year
    
    return true;
}


// the different functions to manipulate the gradebook

void addGrade(int &count, int grades[], int &sum) {
    if (count >= 1000) {
        cout << "Maximum number of grades reached. Cannot add more grades." << endl;
        return;
    }

    int grade;
    cout << "Enter grade (0-100): ";
    cin >> grade;

    if (grade >= 0 && grade <= 100) {
        grades[count] = grade;
        sum += grade;
        count++;
    } else {
        cout << "Invalid grade. Please enter a grade between 0 and 100." << endl;
    }
}
void usingheap(int*& grades, int& count) {
    int newarraySize = count + 1;
    int* pTmp = new int[newarraySize]; // new array on heap

    for (int i = 0; i < count; i++){ // copy thge already on grades to the new array
      pTmp[i] = grades[i];
    }

    delete[] grades;
    grades = pTmp; // deallocate old array while updating new pointers 
}

//Specification B4 - Highlight Failing Grades
void displayGrades(int count, int* grades) {
    for (int i = 0; i < count; i++) {
        int grade = grades[i];
        char letterGrade = Grade2Lttr(grade);
        if (letterGrade == 'F') {
            FancyText::print(to_string(grade) + " (F)\n", "\033[31m");  // red color for failing grades
        } else {
            cout << grade << " (" << letterGrade << ")" << endl;
        }
    }
}

//Specification C4- Compute GPA
void processGrades(int count, int sum) {
    if (count == 0) {
        cout << "No grades to process." << endl;
        return;
    }

    double average = static_cast<double>(sum) / count;
    char letterGrade = getLetterGrade(average);

    cout << "Average score: " << average << endl;
    cout << "Letter Grade: " << letterGrade << endl;
}

char getLetterGrade(double grade) {
    if (grade > 100 || grade < 0) return 'F';
    else if (grade >= 90) return 'A';
    else if (grade >= 80) return 'B';
    else if (grade >= 70) return 'C';
    else if (grade >= 60) return 'D';
    else return 'F';
}
char Grade2Lttr(int grade) {
    if (grade >= 90) return 'A';
    else if (grade >= 80) return 'B';
    else if (grade >= 70) return 'C';
    else if (grade >= 60) return 'D';
    else return 'F';
}
//Specification B3- Menu Input Validation
int getmenuChoice() {
    int choice;
    do {
        cout << "\n1. Add grade" << endl;
        cout << "2. Print Scores" << endl;
        cout << "3. Process all grades" << endl;
        cout << "4. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice < 1 || choice > 4)  {
            cout << "Invalid input. Please enter a number between 1 and 4." << endl;
        }
    } while (choice < 1 || choice > 4);
    return choice;
}