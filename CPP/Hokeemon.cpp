//Hokeemon.cpp
//Jashandeep Singh
//11/26/2022

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>



using namespace std;

// Specification C2 - Creature Class
class Creature {
protected:
    int hunger;
    int boredom;
    string name; 

public:
// Specification A1 - Critter Name
    Creature(const string& name = "Unnamed") : hunger(rand() % 6), boredom(rand() % 6), name(name) {}

    // Specification A2 - Copy Constructor
    Creature(const Creature& other) : hunger(other.hunger), boredom(other.boredom), name(other.name) {}

    //Specification B2 - Virtual Class Creature
    virtual void play() = 0;
    virtual void feed() = 0;

    // Specification C1 - PassTime
    virtual void passTime() {
        hunger++;
        boredom++;
    }

    // Specification C4 - Overload «
    friend ostream& operator<<(ostream& os, const Creature& creature) {
        os << "Hunger: " << creature.hunger << ", Boredom: " << creature.boredom;
        return os;
    }

    // Specification B3 - Overload Assignment Operator
    Creature& operator=(const Creature& other) {
        if (this != &other) {
            hunger = other.hunger;
            boredom = other.boredom;
            name = other.name;
        }
        return *this;
    }

    // Getters for Lambda function 
    int getHunger() const { return hunger; }
    int getBoredom() const { return boredom; }
    string getName() const { return name; }

    // Component testing method
    virtual void test() = 0;
};

// Specification A3 - Second Child Class
class AquaticHokeemon : public Creature {
public:
    AquaticHokeemon(const string& name) : Creature(name) {}

    void play() override {
        int playValue = rand() % 5 + 6;
        boredom -= playValue;
        if (boredom < 0) {
            boredom = 0;
        }
        cout << "Splashing around with " << name << ". Boredom reduced by " << playValue << "." << endl;
        passTime();
    }

    void feed() override {
        int feedValue = rand() % 4 + 2;
        hunger -= feedValue;
        if (hunger < 0) {
            hunger = 0;
        }
        cout << "Feeding fish to " << name << ". Hunger reduced by " << feedValue << "." << endl;
        passTime();
    }

    void test() override {
        cout << name << " (AquaticHokeemon) is being tested." << endl;
    }
};

// Specification B1 - Child Class
class MagicalHokeemon : public Creature {
public:
    MagicalHokeemon(const string& name) : Creature(name) {}

    void play() override {
        int playValue = rand() % 5 + 4;
        boredom -= playValue;
        if (boredom < 0) {
            boredom = 0;
        }
        cout << "Playing a magical game with " << name << ". Boredom reduced by " << playValue << "." << endl;
        passTime();
    }

    void feed() override {
        int feedValue = rand() % 4 + 3;
        hunger -= feedValue;
        if (hunger < 0) {
            hunger = 0;
        }
        cout << "Feeding magical berries to " << name << ". Hunger reduced by " << feedValue << "." << endl;
        passTime();
    }

    void test() override {
        cout << name << " (MagicalHokeemon) is being tested." << endl;
    }
    friend MagicalHokeemon operator+(const MagicalHokeemon& a, const MagicalHokeemon& b) {
        string mergedName = a.getName() + "-" + b.getName();
        int mergedHunger = (a.getHunger() + b.getHunger()) / 2;
        int mergedBoredom = (a.getBoredom() + b.getBoredom()) / 2;
        MagicalHokeemon mergedHokeemon(mergedName);
        mergedHokeemon.hunger = mergedHunger;
        mergedHokeemon.boredom = mergedBoredom;
        return mergedHokeemon;
    }
};

void programGreeting();

int main() {
    programGreeting();
    srand(time(nullptr));  // Initialize random number generator

    MagicalHokeemon myHokeemon("JigglyPuff");   // Create a MagicalHokeemon object
    myHokeemon.test();                           // Run diagnostic tests


  string hokeemon1Name, hokeemon2Name;
  cout << "Enter a name for your first Hokeemon: ";
  getline(cin, hokeemon1Name);
  MagicalHokeemon hokeemon1(hokeemon1Name);

  cout << "Enter a name for your second Hokeemon: ";
  getline(cin, hokeemon2Name);
  MagicalHokeemon hokeemon2(hokeemon2Name);

  hokeemon1.test();  // Run diagnostic tests on the first Hokeemon
  hokeemon2.test();  // Run diagnostic tests on the second Hokeemon
    // Specification C3 - Validate Input
    char choice;
    do {
        cout << "Choose an action (P: Play, F: Feed, L: Listen, M: Merge, Q: Quit): ";
        cin >> choice;

        switch (choice) {
            case 'P':
            case 'p':
                myHokeemon.play();
                break;
            case 'F':
            case 'f':
                myHokeemon.feed();
                break;
            case 'L':
            case 'l':
                cout << myHokeemon;  // Using overloaded « operator
                break;
            case 'Q':
            case 'q':
                cout << "Thank you for playing!" << endl;
                return 0;
          //Specification B4- Overload + Operator
          case 'M':
          case 'm': {
              cout << "Merging Hokeemon1 and Hokeemon2." << endl;
              MagicalHokeemon mergedHokeemon = hokeemon1 + hokeemon2;
              cout << "Merged Hokeemon created: " << mergedHokeemon.getName() << endl;
              // Display merged Hokeemon details
              cout << mergedHokeemon;
              break;
          }
            default:
                cout << "Invalid choice. Please try again.\n";
        }

        myHokeemon.passTime();
        hokeemon1.passTime();
        hokeemon2.passTime();
        // Specification A4 - Lambda Function Usage
        auto displayStatus = [](const Creature& creature) {
            cout << creature.getName() << "'s Status: ";
            if (creature.getHunger() > 10) {
                cout << "Hungry, ";
            } else {
                cout << "Not Hungry, ";
            }
            if (creature.getBoredom() > 10) {
                cout << "Bored";
            } else {
                cout << "Entertained";
            }
            cout << endl;
        };

        displayStatus(myHokeemon);
        displayStatus(hokeemon1);
        displayStatus(hokeemon2);


    } while (choice != 'Q' && choice != 'q');

    return 0;
}


void programGreeting() {
    cout << "Welcome to the Hokeemon Program.\n" << endl;
    cout << "Author: Jashandeep Singh" << endl;
    cout << "Due Date: November 26, 2023" << endl;

    auto lambdaFunction = []() {
        cout << "This is a Lambda function in the Hokeemon game!\n" << endl;
    };

    lambdaFunction();
}