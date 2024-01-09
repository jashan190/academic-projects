//TODO.cpp
//Jashandeep Singh, CISP 400
//11/5/2023

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <iomanip> 

using namespace std; 


class TodoItem {
public:
    int id;
    string task;
    string dateAdded;

    // Specification A4 - Overloaded Constructor
    TodoItem() : id(0), task("Dummy Data"), dateAdded(getCurrentDatePST()) {}
    TodoItem(int id, const string &task) : id(id), task(task), dateAdded(getCurrentDatePST()) {}

    // Specification A1 - Overload Copy Constructor
    TodoItem(const TodoItem &other) : id(other.id), task(other.task), dateAdded(other.dateAdded) {}

    // Specification A2 - Overload Assignment Operator
    TodoItem& operator=(const TodoItem &other) {
        if (this != &other) {
            id = other.id;
            task = other.task;
            dateAdded = other.dateAdded;
        }
        return *this;
    }

    // Helper function to get current date in YYYY-MM-DD format
    static string getCurrentDatePST() {
        // Specification A3 - System Date
        time_t x = time(nullptr);
        tm *now = localtime(&x);

        now->tm_hour -= 8; // Subtract 8 hours for PST

        // Normalize the tm structure because it might be out of range after subtraction
        mktime(now);

        stringstream ss;
        ss << put_time(now, "%Y-%m-%d");
        return ss.str();
    }

    // Component testing method
    void componentTest() {
        // Specification C3 - Test TODO’s
        // Test 1: Check if the task is not empty
        if (task.empty()) {
            cout << "Component Test 1 Failed: Task is empty." << endl;
        } else {
            cout << "Component Test 1 Passed: Task is valid." << endl;
        }
        // Test 2: Check if the date format is correct
        if (dateAdded.find("-") != string::npos) {
            cout << "Component Test 2 Passed: Date format is correct." << endl;
        } else {
            cout << "Component Test 2 Failed: Date format is incorrect." << endl;
        }
    }

// Specification C1 - Overload «
  friend ostream& operator<<(ostream& os, const TodoItem& item) {
      os << "ID: " << item.id << " | Task: " << item.task << " | Date Added: " << item.dateAdded;
      return os;
  }

  // Specification C2 - Overload »
  friend istream& operator>>(istream& is, TodoItem& item) {
      getline(is, item.task, ',');
      is >> item.id;
      is.ignore(); // Ignore the comma
      getline(is, item.dateAdded);
      return is;
};

class TodoList {
private:
    TodoItem *items;
    int capacity;
    int count;
    int nextId;

    // Resize the array if needed
    void resize() {
        capacity *= 2; // Double the capacity
        TodoItem *newItems = new TodoItem[capacity];
        for (int i = 0; i < count; ++i) {
            newItems[i] = items[i];
        }
        delete[] items;
        items = newItems;
    }

public:
    // Specification C4 - TODO array
    TodoList(int initialCapacity = 5) : capacity(initialCapacity), count(0), nextId(1) {
        items = new TodoItem[capacity];
    }

    ~TodoList() {
        delete[] items;
    }

    void addItem(const string &task) {
        if (count >= capacity) {
            resize();
        }
        items[count++] = TodoItem(nextId++, task);
    }

    void displayList() const {
        for (int i = 0; i < count; ++i) {
            cout << "ID: " << items[i].id << " | Task: " << items[i].task
                      << " | Date Added: " << items[i].dateAdded << endl;
        }
    }

    void removeItem(int id) {
        for (int i = 0; i < count; ++i) {
            if (items[i].id == id) {
                // Shift all items down to fill the removed spot
                for (int j = i; j < count - 1; ++j) {
                    items[j] = items[j + 1];
                }
                --count;
                break;
            }
        }
    }

    // Specification B4 - Persistence
    void saveToFile(const string &filename) const {
        ofstream outFile(filename);
        for (int i = 0; i < count; ++i) {
            outFile << items[i].id << "," << items[i].task << "," << items[i].dateAdded << "\n";
        }
    }

    void loadFromFile(const string &filename) {
        ifstream inFile(filename);
        if (!inFile) {
            return; // File doesn't exist
        }
        string line, task, date;
        int id;
        while (getline(inFile, line)) {
            size_t firstComma = line.find(',');
            size_t lastComma = line.rfind(',');
            if (firstComma != string::npos && lastComma != string::npos && firstComma != lastComma) {
                id = stoi(line.substr(0, firstComma));
                task = line.substr(firstComma + 1, lastComma - firstComma - 1);
                date = line.substr(lastComma + 1);
                addItem(task); // sets a new date, not sure if I should change it 
            }
        }
    }
  };
};

void programGreeting() {
    cout << "Welcome to the TODO List Program.\n" << endl;
    cout << "Author: Jashandeep Singh" << endl;
    cout << "Due Date: November 5, 2023" << endl;
    cout << "Current Date: " << TodoItem::getCurrentDatePST() << endl;
}

void programMenu(TodoItem::TodoList &list) {
    cout << "Enter '+ <task>' to add a task, '? <id>' to display tasks, or '- <id>' to remove a task." << endl;
    string line, command, task;
    int id;
    while (getline(cin, line)) {
        istringstream iss(line);
        iss >> command;
      // Specification B1 - + Symbol
        if (command == "+") {
            getline(iss, task);
            if (!task.empty()) {
                list.addItem(task);
                cout << "Task added." << endl;
            }
          // Specification B2 - ? Symbol
        } else if (command == "?") {
            list.displayList();
          // Specification B3 - - symbol
        
        } else if (command == "-") {
            iss >> id;
            list.removeItem(id);
            cout << "Task removed." << endl;
        } else {
            cout << "Unknown command. Try again." << endl;
        }
    }
}

int main() {
    const string filename = "todo_list.txt";
    TodoItem::TodoList myList;

    programGreeting();
    myList.loadFromFile(filename);
    programMenu(myList);
    myList.saveToFile(filename);

    return 0;
}
/*Welcome to the TODO List Program.

Author: Jashandeep Singh
Due Date: November 5, 2023
Current Date: 2023-11-04
Enter '+ <task>' to add a task, '? <id>' to display tasks, or '- <id>' to remove a task.*/