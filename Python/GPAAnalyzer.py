import datetime

# Program greeting
def program_greeting():
    print("\nHello and welcome to my GPA Analyzer program!")
    print("Author: Jashandeep Singh")
    print("Due Date: September 24, 2023")

# Date class
class Date:
    def __init__(self, year=0, month=0, day=0):
        if year == 0 and month == 0 and day == 0:
            now = datetime.datetime.now()
            self.year = now.year
            self.month = now.month
            self.day = now.day
        else:
            self.year = year
            self.month = month
            self.day = day

    def display_date(self):
        print(f"{self.month}/{self.day}/{self.year}")

    def is_date_valid(self):
        try:
            datetime.datetime(self.year, self.month, self.day)
            return True
        except ValueError:
            return False

    @staticmethod
    def comp_test():
        test_date = Date(2023, 9, 24)
        if test_date.is_date_valid():
            print("CompTest PASSED.")
        else:
            print("CompTest FAILED.")

# Adding a grade
def add_grade(grades):
    grade = int(input("Enter grade (0-100): "))
    if 0 <= grade <= 100:
        grades.append(grade)
    else:
        print("Invalid grade. Please enter a grade between 0 and 100.")

# Displaying grades
def display_grades(grades):
    for grade in grades:
        letter_grade = grade_to_letter(grade)
        if letter_grade == 'F':
            print(f"\033[31m{grade} (F)\033[0m")  # red color for failing grades
        else:
            print(f"{grade} ({letter_grade})")

# Process grades
def process_grades(grades):
    if not grades:
        print("No grades to process.")
        return
    average = sum(grades) / len(grades)
    letter_grade = grade_to_letter(average)
    print(f"Average score: {average}")
    print(f"Letter Grade: {letter_grade}")

# Convert grade to letter
def grade_to_letter(grade):
    if grade >= 90:
        return 'A'
    elif grade >= 80:
        return 'B'
    elif grade >= 70:
        return 'C'
    elif grade >= 60:
        return 'D'
    else:
        return 'F'

# Menu choice
def get_menu_choice():
    while True:
        print("\n1. Add grade")
        print("2. Print Scores")
        print("3. Process all grades")
        print("4. Quit")
        try:
            choice = input("Enter your choice: ")
            if not choice:  # Checks if the input is empty
                raise ValueError("Empty input")
            choice = int(choice)
            if 1 <= choice <= 4:
                return choice
            else:
                print("Invalid input. Please enter a number between 1 and 4.")
        except ValueError as e:
            print(f"Invalid input: {e}. Please enter a valid number.")

# Unit test
def unit_test():
    print("Running Component Test for Date class...")
    Date.comp_test()

    print("Running score to letter grade conversion tests...")
    grade_tests = [
        (95, 'A'),
        (85, 'B'),
        (75, 'C'),
        (65, 'D'),
        (55, 'F'),
        (105, 'F'),  # score too high
        (-5, 'F')    # score too low
    ]

    for score, expected_letter in grade_tests:
        letter = grade_to_letter(score)
        if letter == expected_letter:
            print(f"Test PASSED for score {score}. Expected: {expected_letter}, Got: {letter}")
        else:
            print(f"Test FAILED for score {score}. Expected: {expected_letter}, Got: {letter}")

    print("Unit tests completed.")

def main():
    unit_test()
    program_greeting()
    Date.comp_test()

    # Initialize grades list
    grades = []

    # Menu loop
    while True:
        choice = get_menu_choice()
        if choice == 1:
            add_grade(grades)
        elif choice == 2:
            display_grades(grades)
        elif choice == 3:
            process_grades(grades)
        elif choice == 4:
            print("Exiting program.")
            break

main()