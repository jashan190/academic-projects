import datetime
import os

class TodoItem:
    def __init__(self, id=0, task="Dummy Data"):
        self.id = id
        self.task = task
        self.date_added = TodoItem.get_current_date_pst()

    @staticmethod
    def get_current_date_pst():
        current_time = datetime.datetime.now() - datetime.timedelta(hours=8)
        return current_time.strftime("%Y-%m-%d")

    def __str__(self):
        return f"ID: {self.id} | Task: {self.task} | Date Added: {self.date_added}"

class TodoList:
    def __init__(self):
        self.items = []
        self.next_id = 1

    def add_item(self, task):
        self.items.append(TodoItem(self.next_id, task))
        self.next_id += 1

    def display_list(self):
        for item in self.items:
            print(item)

    def remove_item(self, id):
        self.items = [item for item in self.items if item.id != id]

    def save_to_file(self, filename):
        with open(filename, "w") as file:
            for item in self.items:
                file.write(f"{item.id},{item.task},{item.date_added}\n")

    def load_from_file(self, filename):
        if not os.path.exists(filename):
            return
        with open(filename, "r") as file:
            for line in file:
                id_str, task, date_added = line.strip().split(",")
                self.items.append(TodoItem(int(id_str), task))

def program_greeting():
    print("Welcome to the TODO List Program.\n")
    print("Author: Jashandeep Singh")
    print("Due Date: November 5, 2023")
    print("Current Date:", TodoItem.get_current_date_pst())

def program_menu(todo_list):
    print("Enter '+ <task>' to add a task, '? <id>' to display tasks, or '- <id>' to remove a task.")
    while True:
        line = input()
        if not line:
            break
        command, *args = line.split(maxsplit=1)
        if command == "+":
            task = args[0] if args else ""
            if task:
                todo_list.add_item(task)
                print("Task added.")
        elif command == "?":
            todo_list.display_list()
        elif command == "-":
            id = int(args[0]) if args else -1
            todo_list.remove_item(id)
            print("Task removed.")
        else:
            print("Unknown command. Try again.")

def main():
    filename = "todo_list.txt"
    my_list = TodoList()

    program_greeting()
    my_list.load_from_file(filename)
    program_menu(my_list)
    my_list.save_to_file(filename)

main()
