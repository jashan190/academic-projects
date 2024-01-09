import random
import time

def program_greeting():
    print("\nHello and welcome to my Inventory program!")
    print("Author: Jashandeep Singh")
    print("Due Date: October 22, 2023")

class Date:
    def __init__(self):
        self.year_of_manufacture = time.localtime().tm_year

    def get_current_year(self):
        return self.year_of_manufacture

    def check_year(self):
        system_date = Date()
        if system_date.get_current_year() == 2023:
            print("Date checkYear: Pass - The current year is 2023.")
        else:
            print("Date checkYear: Fail - The year is not 2023.")

class RandNo:
    has_been_seeded = False

    def __init__(self):
        if not RandNo.has_been_seeded:
            random.seed()
            RandNo.has_been_seeded = True

    def get_random(self, minimum, maximum):
        return random.uniform(minimum, maximum)

class InVal:
    @staticmethod
    def item_id_validation():
        product_id = input("Enter Product ID (5 digits only): ")
        return product_id

    @staticmethod
    def stock_amount_validation():
        stock_level = int(input("Enter Stock Level (non-negative): "))
        return stock_level

    @staticmethod
    def cost_validation():
        base_price = float(input("Enter Base Price (non-negative): "))
        return base_price

class StockItem:
    def __init__(self, product_code, stock_quantity, base_cost, sale_price, entry_date):
        self.product_code = product_code
        self.stock_quantity = stock_quantity
        self.base_cost = base_cost
        self.sale_price = sale_price
        self.entry_date = entry_date

    def __str__(self):
        return (f"Product Code: {self.product_code}\n"
                f"Stock Quantity: {self.stock_quantity}\n"
                f"Base Cost: ${self.base_cost:.2f}\n"
                f"Sale Price: ${self.sale_price:.2f}\n"
                f"Entry Date: {self.entry_date.get_current_year()}\n")

class StockControl:
    def __init__(self):
        self.stock_list = []

    def add_stock_item(self, new_item):
        self.stock_list.append(new_item)

    def remove_stock_item(self):
        if self.stock_list:
            self.stock_list.pop()

    def update_stock_item(self, code, quantity, cost):
        for item in self.stock_list:
            if item.product_code == code:
                item.stock_quantity = quantity
                item.base_cost = cost
                item.sale_price = cost * 1.25
                break

    def show_stock_items(self):
        for item in self.stock_list:
            print(item)

    def get_list_size(self):
        return len(self.stock_list)

def stock_menu(inventory_control, random_no_gen):
    while True:
        print("\nInventory Management Menu")
        print("A - Add Inventory")
        print("D - Delete Inventory")
        print("E - Edit Inventory")
        print("P - Print Inventory")
        print("Q - Quit Program")
        user_choice = input("Enter choice: ").upper()

        if user_choice == 'A':
            product_code = InVal.item_id_validation()
            stock_quantity = InVal.stock_amount_validation()
            base_cost = InVal.cost_validation()
            sale_price = random_no_gen.get_random(base_cost, base_cost * 1.5)
            entry_date = Date()
            new_item = StockItem(product_code, stock_quantity, base_cost, sale_price, entry_date)
            inventory_control.add_stock_item(new_item)
        elif user_choice == 'D':
            inventory_control.remove_stock_item()
        elif user_choice == 'E':
            if inventory_control.get_list_size() > 0:
                code_to_update = InVal.item_id_validation()
                updated_quantity = InVal.stock_amount_validation()
                updated_cost = InVal.cost_validation()
                inventory_control.update_stock_item(code_to_update, updated_quantity, updated_cost)
            else:
                print("\nNo inventory items to edit.")
        elif user_choice == 'P':
            inventory_control.show_stock_items()
        elif user_choice == 'Q':
            print("Quitting the program.")
            break
        else:
            print("Invalid selection. Please try again.")

def unit_test():
    Date().check_year()

def main():
    program_greeting()
    unit_test()
    inventory_control = StockControl()
    random_no_gen = RandNo()
    stock_menu(inventory_control, random_no_gen)

main()
