import random

class Creature:
    def __init__(self, name="Unnamed"):
        self.hunger = random.randint(0, 5)
        self.boredom = random.randint(0, 5)
        self.name = name

    def pass_time(self):
        self.hunger += 1
        self.boredom += 1

    def play(self):
        raise NotImplementedError

    def feed(self):
        raise NotImplementedError

    def test(self):
        raise NotImplementedError

    def __str__(self):
        return f"Hunger: {self.hunger}, Boredom: {self.boredom}"

class AquaticHokeemon(Creature):
    def __init__(self, name):
        super().__init__(name)

    def play(self):
        play_value = random.randint(6, 10)
        self.boredom -= play_value
        if self.boredom < 0:
            self.boredom = 0
        print(f"Splashing around with {self.name}. Boredom reduced by {play_value}.")
        self.pass_time()

    def feed(self):
        feed_value = random.randint(2, 5)
        self.hunger -= feed_value
        if self.hunger < 0:
            self.hunger = 0
        print(f"Feeding fish to {self.name}. Hunger reduced by {feed_value}.")
        self.pass_time()

    def test(self):
        print(f"{self.name} (AquaticHokeemon) is being tested.")

class MagicalHokeemon(Creature):
    def __init__(self, name):
        super().__init__(name)

    def play(self):
        play_value = random.randint(4, 8)
        self.boredom -= play_value
        if self.boredom < 0:
            self.boredom = 0
        print(f"Playing a magical game with {self.name}. Boredom reduced by {play_value}.")
        self.pass_time()

    def feed(self):
        feed_value = random.randint(3, 6)
        self.hunger -= feed_value
        if self.hunger < 0:
            self.hunger = 0
        print(f"Feeding magical berries to {self.name}. Hunger reduced by {feed_value}.")
        self.pass_time()

    def test(self):
        print(f"{self.name} (MagicalHokeemon) is being tested.")

    @staticmethod
    def merge(a, b):
        merged_name = a.name + "-" + b.name
        merged_hunger = (a.hunger + b.hunger) // 2
        merged_boredom = (a.boredom + b.boredom) // 2
        merged_hokeemon = MagicalHokeemon(merged_name)
        merged_hokeemon.hunger = merged_hunger
        merged_hokeemon.boredom = merged_boredom
        return merged_hokeemon

def program_greeting():
    print("Welcome to the Hokeemon Program.\n")
    print("Author: Jashandeep Singh")
    print("Due Date: November 26, 2023\n")

    def lambda_function():
        print("This is a Lambda function in the Hokeemon game!\n")

    lambda_function()

def main():
    program_greeting()
    random.seed()

    my_hokeemon = MagicalHokeemon("JigglyPuff")
    my_hokeemon.test()

    hokeemon1_name = input("Enter a name for your first Hokeemon: ")
    hokeemon1 = MagicalHokeemon(hokeemon1_name)

    hokeemon2_name = input("Enter a name for your second Hokeemon: ")
    hokeemon2 = MagicalHokeemon(hokeemon2_name)

    hokeemon1.test()
    hokeemon2.test()

    while True:
        choice = input("Choose an action (P: Play, F: Feed, L: Listen, M: Merge, Q: Quit): ").lower()

        if choice == 'p':
            my_hokeemon.play()
        elif choice == 'f':
            my_hokeemon.feed()
        elif choice == 'l':
            print(my_hokeemon)
        elif choice == 'm':
            print("Merging Hokeemon1 and Hokeemon2.")
            merged_hokeemon = MagicalHokeemon.merge(hokeemon1, hokeemon2)
            print(f"Merged Hokeemon created: {merged_hokeemon.name}")
            print(merged_hokeemon)
        elif choice == 'q':
            print("Thank you for playing!")
            break
        else:
            print("Invalid choice. Please try again.")

        my_hokeemon.pass_time()
        hokeemon1.pass_time()
        hokeemon2.pass_time()

        display_status = lambda creature: (
            f"{creature.name}'s Status: {'Hungry' if creature.hunger > 10 else 'Not Hungry'}, "
            f"{'Bored' if creature.boredom > 10 else 'Entertained'}"
        )

        print(display_status(my_hokeemon))
        print(display_status(hokeemon1))
        print(display_status(hokeemon2))

main()
