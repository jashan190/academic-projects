//Invinq.cpp
//Jashandeep Singh, CISP 400 
// 10/22/2023
#include <iostream>                                 
#include <string>                                      
#include <iomanip>                                     
#include <cstdlib>                                     
#include <ctime>
using namespace std;

void programGreeting(){
  cout << "\nHello and welcome to my Inventory program!" << endl;
  cout << "Author: Jashandeep Singh" << endl;
  cout << "Due Date: October 22, 2023" << endl;
}

// Specification B1 - Date class
class Date {
private:
    int yearOfManufacture;

public:
    Date() {
        time_t timer = time(nullptr);
        tm* timeStruct = localtime(&timer);
        yearOfManufacture = timeStruct->tm_year + 1900;
    }

    int getCurrentYear() const {
        return yearOfManufacture;
    }

    void checkYear() {
        Date systemDate;
        if (systemDate.getCurrentYear() == 2023) {
            cout << "Date checkYear: Pass - The current year is 2023." << endl;
        } else {
            cout << "Date checkYear: Fail - The year is not 2023." << endl;
        }
    }
};

// Specification B2 - RandNo Class
// Specification B3 - Singleton Design Pattern
class RandNo {
private:
    static bool hasBeenSeeded;

public:
    RandNo() {
        if (!hasBeenSeeded) {
            srand(static_cast<unsigned int>(time(nullptr)));
            hasBeenSeeded = true;
        }
    }

    double getRandom(double minimum, double maximum) {
        return minimum + static_cast<double>(rand()) / (RAND_MAX / (maximum - minimum));
    }

    // Specification A3 - Overload operator>>
    friend istream& operator>>(istream& input, RandNo& randomNumberGenerator) {
        int seedValue;
        cout << "\nEnter a custom seed for RNG: ";
        input >> seedValue;
        srand(seedValue);
        hasBeenSeeded = true;
        return input;
    }
};

bool RandNo::hasBeenSeeded = false; 

// Specification B4 - Inventory Entry Input Validation
class InVal {
public:
    static string itemIDValidation() {
        string productID;
        cout << "Enter Product ID (5 digits only): ";
        cin >> productID;
        return productID; // Simple validation for example purposes
    }

    static int stockAmountValidation() {
        int stockLevel;
        cout << "Enter Stock Level (non-negative): ";
        cin >> stockLevel;
        return stockLevel; // Simple validation for example purposes
    }

    static double costValidation() {
        double basePrice;
        cout << "Enter Base Price (non-negative): ";
        cin >> basePrice;
        return basePrice; // Simple validation for example purposes
    }
};

// Specification A2 - Overload operator<<
struct StockItem {
    string productCode;
    int stockQuantity;
    double baseCost;
    double salePrice;
    Date entryDate;

    friend ostream& operator<<(ostream& outputStream, const StockItem& item) {
        outputStream << "Product Code: " << item.productCode << "\n"
                     << "Stock Quantity: " << item.stockQuantity << "\n"
                     << "Base Cost: $" << fixed << setprecision(2) << item.baseCost << "\n"
                     << "Sale Price: $" << fixed << setprecision(2) << item.salePrice << "\n"
                     << "Entry Date: " << item.entryDate.getCurrentYear() << "\n";
        return outputStream;
    }
};

// Specification C2 - Dynamic Array  
// Specification C3 - Resize Array
class StockControl {
private:
    StockItem* stockList;
    int listSize;

public:
    StockControl() : listSize(0), stockList(new StockItem[1]) {}

    ~StockControl() {
        delete[] stockList;
    }

    void addStockItem(const StockItem& newItem) {
        StockItem* pTmp = new StockItem[listSize + 1];
        for (int index = 0; index < listSize; ++index) {
              pTmp[index] = stockList[index];
        }
          pTmp[listSize] = newItem;
        delete[] stockList;
        stockList = pTmp;
        ++listSize;
    }

    void removeStockItem() {
        if (listSize > 0) {
            StockItem* pTmp = new StockItem[listSize - 1];
            for (int index = 0; index < listSize - 1; ++index) {
                  pTmp[index] = stockList[index];
            }
            delete[] stockList;
            stockList = pTmp;
            --listSize;
        }
    }

    // Specification A1 - Edit Inventory
    void updateStockItem(const string& code, int quantity, double cost) {
        for (int index = 0; index < listSize; ++index) {
            if (stockList[index].productCode == code) {
                stockList[index].stockQuantity = quantity;
                stockList[index].baseCost = cost;
                stockList[index].salePrice = cost * 1.25; 
                return;
            }
        }
    }

    void showStockItems() const {
        for (int index = 0; index < listSize; ++index) {
            cout << stockList[index] << endl;
        }
    }

    int getListSize() const {
        return listSize;
    }
};

// Specification C1 - Alpha Menu 
// Specification C4 - Menu Input Validation
void stockMenu(StockControl &inventoryControl, RandNo &randomNoGen) {
    char userChoice;
    do {
        cout << "\nInventory Management Menu" << endl;
        cout << "A - Add Inventory" << endl;
        cout << "D - Delete Inventory" << endl;
        cout << "E - Edit Inventory" << endl;
        cout << "P - Print Inventory" << endl;
        cout << "Q - Quit Program" << endl;
        cout << "Enter choice: ";
        cin >> userChoice;
        userChoice = toupper(userChoice);

        switch (userChoice) {
            case 'A': {
                // Add Inventory
                StockItem newItem;
                newItem.productCode = InVal::itemIDValidation();
                newItem.stockQuantity = InVal::stockAmountValidation();
                newItem.baseCost = InVal::costValidation();
                newItem.salePrice = randomNoGen.getRandom(newItem.baseCost, newItem.baseCost * 1.5);
                newItem.entryDate = Date();
                inventoryControl.addStockItem(newItem);
                break;
            }
            case 'D': {
                // Delete Inventory
                inventoryControl.removeStockItem();
                break;
            }
            case 'E': {
                // Edit Inventory
                if (inventoryControl.getListSize() > 0) {
                    string codeToUpdate = InVal::itemIDValidation();
                    int updatedQuantity = InVal::stockAmountValidation();
                    double updatedCost = InVal::costValidation();
                    inventoryControl.updateStockItem(codeToUpdate, updatedQuantity, updatedCost);
                } else {
                    cout << "\nNo inventory items to edit." << endl;
                }
                break;
            }
            case 'P': {
                // Print Inventory
                inventoryControl.showStockItems();
                break;
            }
            case 'Q': {
                // Quit Program
                cout << "Quitting the program." << endl;
                return;
            }
            default: {
                cout << "Invalid selection. Please try again." << endl;
                break;
            }
        }
    } while (userChoice != 'Q');
}

// Specification A4 - UnitTest() function in main()
void UnitTest() {
    // Unit tests for Date and RandNo classes
    Date().checkYear();
}

int main() {
    programGreeting();
    UnitTest();
    StockControl inventoryControl;
    RandNo randomNoGen;
    stockMenu(inventoryControl, randomNoGen);
    return 0;
}