#include <iostream>
#include <ctime>
#include <string>

using namespace std;

struct Room {
  string roomName;
  string roomDescription;
  int roomId;
  bool occupied;
  int exits[4];
};

void programGreeting();
string getName();

int main() {
  programGreeting();
  std::string inventory[10];
  int inventoryCount = 0; 
  //This will be the array that will spawn when a room is occupied 
  // I was thinking of doing the class but I dont really understand it all that much 
  std ::string monsters[5] = {
    "Barney",
    "Elmo",
    "Dora",
    "Squidward", 
    //Specification B3- Add more monsters (I’ll give you credit for only 1 more monster, regardless of the number you actually add).
    "Patchy"
  };
  //Specification C2- Player Name
  string playerName = getName();
  cout << playerName;

  cout << "\nWelcome " << playerName << ", you are here by entering a dungeon!" << endl;
  //Specification C1- Five Rooms
  //Specification A1-Add more Rooms
  Room rooms[6] = {
    {"First Room (The Entrance)", "The first room you encounter when entering the dungeon.", 1, false, {1, 1, 1, 1}},
    {"Second Room (The Secret Lair!)", "A secret lair belonging to the owner of the dungeon.", 2, false, {2, 0, 1, 1}},
    //Specification A3- Add treasure. This practically begs you to keep some sort of inventory as well. I suppose you’ll also need an <i>nventory command to see it.
    {"Third Room (A Secret treasure room!)", "A secret compartment of room 2.", 3, false, {-1, 1, 3, -1}},
    //Specification A2- Add trap encounters. Once revealed (visible) these are permanent. They will appear whenever you subsequently reenter that room.
    {"Fourth Room (A trap!)", "Oh No! You are stuck it is a trap!", 4, true, {-1, -1, 4, 2}},
    {"Fifth Room (The room of Natomas)", "A really boring community in the city of SAC ", 5, true, {-1, -1, -1, 3}},
    {"Sixth Room (The exit out of this dungeon!)", "The room leading to outside of the dungeon", 6, false, {-1, -1, -1, -1}}
  };
  // the way to know which room the user is in. Using the structs as well it makes it much easeier to keep track off 
  int currentRoom = 0;
  bool visit[6] = { true, true, true, true, true, true };

  string input;
  string treausure; 
  //Specification C4- Abbreviated Room Description
  do {// If you eneter the room for the first time you will be met with the room name and the room description 
    if (visit[currentRoom]) {
      cout << rooms[currentRoom].roomName << endl;
      cout << rooms[currentRoom].roomDescription << endl;
      visit[currentRoom] = false;
    } else { // if you have already been in the room you should be only met with the room name of the one you are in
      cout << rooms[currentRoom].roomName << endl;
    }
    //Specification B1-Add more command options (inventory)
    cout << "Control your action by picking either N, E, S, W, L, or I: ";
    cin >> input;
    //Specification C5 - Detailed Look 
    if (input == "L") {
      cout << rooms[currentRoom].roomName << endl;
      cout << rooms[currentRoom].roomDescription << endl;
    } else if (input == "N" || input == "E" || input == "S" || input == "W" || input =="I") {
      //SHowing what inventory you have 
      if (input == "I"){
        cout << "You currently have: " << endl;
        for (int i = 0; i < inventoryCount; i++) {
        cout << inventory[i] << endl;
      }
    }

        
      int direction;
      // The directions will be assigned to different inputs which will correlate back to 
      if (input == "N") {
        direction = 0;
      } else if (input == "E") {
        direction = 1;
      } else if (input == "S") {
        direction = 2;
      } else {
        direction = 3;
      }

      int roomAfter = rooms[currentRoom].exits[direction];

      if (roomAfter == -1) {
        cout << "No exit in that direction, so pick another one." << endl;
      } else {
        currentRoom = roomAfter;
      }//Specification C3-Input validation 
    } else {
      cout << "You did not enter a valid input." << endl;
    }
    if (rooms[currentRoom].occupied){
      int randomNumber = rand() % 5 +1; 
      string monster = monsters[randomNumber];

      cout << "Be Careful! This is room is occupied by a " << monster << "!" << endl; 
      cout << "Run Away!" << endl; 
    }
    //Specification B2 - Create a pseudodynamic array. You don’t need to grow or shrink this - easy!
    if (rooms[currentRoom].roomId == 3){
        cout << "Congrats you found treasure!" << endl; // I think this is whats meant by pseudodynamic array 
        if (inventoryCount < 10) {
      inventory[inventoryCount] = "Gold";
      inventoryCount++;
    } else {
      cout << "Your inventory is full. You cannot add more items." << endl;
    } 
        
      }// The 5th room should be the last room which is exit because 0- 
    if (currentRoom == 5) {
      cout << playerName << " you reached " << rooms[5].roomName << rooms[5].roomDescription << endl; 
      cout << playerName << ", you won!" << endl;
      break;
    }

  } while (true);

  return 0;
}


string getName() {
  string input;
  cout << "\nBefore starting this adventure, please give us your name: ";
  cin >> input;
  return input;
}

void programGreeting() {
  cout << "\nHello, welcome to my homework assignment!\n";
  cout << "\nAuthor:\tJashandeep Singh\n";
  cout << "\nDue Date:\tMay 18, 2023" << endl;
  cout << "\nBTW, are you going to accept people off the waitlist for CISP 400 in fall?" << endl;
}