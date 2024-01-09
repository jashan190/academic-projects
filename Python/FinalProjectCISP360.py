import random

class Room:
    def __init__(self, name, description, room_id, occupied, exits):
        self.name = name
        self.description = description
        self.room_id = room_id
        self.occupied = occupied
        self.exits = exits

def program_greeting():
    print("\nHello, welcome to my homework assignment!\n")
    print("Author: Jashandeep Singh")
    print("Due Date: May 18, 2023")
    print("BTW, are you going to accept people off the waitlist for CISP 400 in fall?")

def get_name():
    return input("\nBefore starting this adventure, please give us your name: ")

def main():
    program_greeting()
    inventory = []
    monsters = ["Barney", "Elmo", "Dora", "Squidward", "Patchy"]
    player_name = get_name()

    print(f"\nWelcome {player_name}, you are here by entering a dungeon!")

    rooms = [
        Room("First Room (The Entrance)", "The first room you encounter when entering the dungeon.", 1, False, [1, 1, 1, 1]),
        Room("Second Room (The Secret Lair!)", "A secret lair belonging to the owner of the dungeon.", 2, False, [2, 0, 1, 1]),
        Room("Third Room (A Secret treasure room!)", "A secret compartment of room 2.", 3, False, [-1, 1, 3, -1]),
        Room("Fourth Room (A trap!)", "Oh No! You are stuck it is a trap!", 4, True, [-1, -1, 4, 2]),
        Room("Fifth Room (The room of Natomas)", "A really boring community in the city of SAC ", 5, True, [-1, -1, -1, 3]),
        Room("Sixth Room (The exit out of this dungeon!)", "The room leading to outside of the dungeon", 6, False, [-1, -1, -1, -1])
    ]

    current_room = 0
    visited = [True] * len(rooms)
    direction_mapping = {'N': 0, 'E': 1, 'S': 2, 'W': 3}

    while True:
        room = rooms[current_room]

        if visited[current_room]:
            print(room.name)
            print(room.description)
            visited[current_room] = False
        else:
            print(room.name)

        action = input("Control your action by picking either N, E, S, W, L, or I: ").upper()

        if action in direction_mapping:
            next_room = room.exits[direction_mapping[action]]
            if next_room != -1:
                current_room = next_room
            else:
                print("No exit in that direction, so pick another one.")
        elif action == 'L':
            print(room.name)
            print(room.description)
        elif action == 'I':
            print("You currently have: ")
            for item in inventory:
                print(item)
        else:
            print("You did not enter a valid input.")

        if room.occupied:
            monster = random.choice(monsters)
            print(f"Be careful! This room is occupied by {monster}! Run away!")

        if room.room_id == 3 and "Gold" not in inventory:
            print("Congrats, you found treasure!")
            if len(inventory) < 10:
                inventory.append("Gold")
            else:
                print("Your inventory is full. You cannot add more items.")

        if current_room == 5:
            print(f"{player_name}, you reached {room.name} {room.description}")
            print(f"{player_name}, you won!")
            break

main()
