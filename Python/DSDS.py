class Node:
    def __init__(self, value):
        self.value = value
        self.next_node = None

class CustomStack:
    def __init__(self):
        self.top_node = None
        self.stack_size = 0

    def push(self, value):
        new_node = Node(value)
        new_node.next_node = self.top_node
        self.top_node = new_node
        self.stack_size += 1

    def pop(self):
        if self.top_node is None:
            raise RuntimeError("Attempt to pop from an empty stack.")
        value = self.top_node.value
        self.top_node = self.top_node.next_node
        self.stack_size -= 1
        return value

    def top(self):
        if self.top_node is None:
            raise RuntimeError("Attempt to peek on an empty stack.")
        return self.top_node.value

    def current_size(self):
        return self.stack_size

    def display(self):
        print("Stack contents (Top to Bottom): ", end='')
        current_node = self.top_node
        while current_node:
            print(current_node.value, end=' ')
            current_node = current_node.next_node
        print()

def main():
    my_stack = CustomStack()

    # Enhanced Test Rig
    print("Adding elements: 10, 20, 30")
    my_stack.push(10)
    my_stack.push(20)
    my_stack.push(30)
    my_stack.display()

    print("Current stack size: ", my_stack.current_size())

    print("Top element: ", my_stack.top())

    print("Popping elements: ", end='')
    while my_stack.current_size() > 0:
        print(my_stack.pop(), end=' ')
    print()

    print("The stack size after popping: ", my_stack.current_size())

    print("Trying to pop from an empty stack...")
    try:
        my_stack.pop()
    except RuntimeError as e:
        print("Error: ", e)


main()
