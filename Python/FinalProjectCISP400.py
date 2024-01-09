import random

def program_greeting():
    print("Hello Everyone!")
    print("Welcome to my Final for CISP 400")
    print("My name is Jashandeep Singh and in this final we will be conducting survival of the fittest experiment using robots!")
    print("This experiment was first conducted at Harvard!")
    print("Here is some cool art!")
    print(r"""_____/\\\\\\\\\________/\\\\\\\\\\\__________/\\\\\\\\\__/\\\\\\\\\\\__/\\\\\\\\\\\_        
   ___/\\\\\\\\\\\\\____/\\\/////////\\\_____/\\\////////__\/////\\\///__\/////\\\///__       
    __/\\\/////////\\\__\//\\\______\///____/\\\/_______________\/\\\_________\/\\\_____      
     _\/\\\_______\/\\\___\////\\\__________/\\\_________________\/\\\_________\/\\\_____     
      _\/\\\\\\\\\\\\\\\______\////\\\______\/\\\_________________\/\\\_________\/\\\_____    
       _\/\\\/////////\\\_________\////\\\___\//\\\________________\/\\\_________\/\\\_____   
        _\/\\\_______\/\\\__/\\\______\//\\\___\///\\\______________\/\\\_________\/\\\_____  
        _\/\\\_______\/\\\_\///\\\\\\\\\\\/______\////\\\\\\\\\__/\\\\\\\\\\\__/\\\\\\\\\\\_ 
          _\///________\///____\///////////___________\/////////__\///////////__\///////////__""")
    print("The average lifespan will be the average amount of turns each Robot survives.")

class Robots:
    def __init__(self):
        self.sensors = [[random.randint(0, 3) for _ in range(5)] for _ in range(16)]
        self.new_turn = 0
        self.new_harvest = 0
        self.x_velocity = self.y_velocity = 0
        self.x_coords = self.y_coords = 0
        self.battery_level = 5
        self.example_attribute = random.randint(0, 99)

    def get_example_attribute(self):
        return self.example_attribute

    def set_example_attribute(self, value):
        self.example_attribute = value

    def update_velocity_based_on_sensors(self):
        max_batteries = 0
        direction = -1
        for i in range(4):
            if self.sensors[i][0] > max_batteries:
                max_batteries = self.sensors[i][0]
                direction = i

        if direction == 0:
            self.y_velocity -= 1
        elif direction == 1:
            self.y_velocity += 1
        elif direction == 2:
            self.x_velocity += 1
        elif direction == 3:
            self.x_velocity -= 1

    def update_position(self):
        self.x_coords += self.x_velocity
        self.y_coords += self.y_velocity
        self.x_coords = max(0, min(self.x_coords, 9))
        self.y_coords = max(0, min(self.y_coords, 9))
        self.new_turn += 1

    def sense_environment(self, grid):
        self.sensors = [[0 for _ in range(5)] for _ in range(16)]
        if self.x_coords > 0:
            self.sensors[0][0] = grid[self.x_coords - 1][self.y_coords]
        if self.x_coords < len(grid) - 1:
            self.sensors[1][0] = grid[self.x_coords + 1][self.y_coords]
        if self.y_coords < len(grid[0]) - 1:
            self.sensors[2][0] = grid[self.x_coords][self.y_coords + 1]
        if self.y_coords > 0:
            self.sensors[3][0] = grid[self.x_coords][self.y_coords - 1]

    def perform_tasks(self, grid):
        if grid[self.x_coords][self.y_coords] > 0:
            self.battery_level += grid[self.x_coords][self.y_coords]
            self.new_harvest += 1
            grid[self.x_coords][self.y_coords] = 0
        # Additional task-related logic

    def get_lifespan(self):
        return self.new_turn

    def get_batteries_collected(self):
        return self.new_harvest

    def get_fitness(self):
        return self.new_harvest

class Generation:
    total_fitness_sum = 0
    total_batteries_sum = 0
    total_lifespan_sum = 0
    count = 0

    def __init__(self):
        self.average_fitness = 0
        self.total_batteries_collected = 0
        self.average_lifespan = 0

    def calculate_metrics(self, robots):
        total_fitness = total_lifespan = 0
        for robot in robots:
            total_fitness += robot.get_fitness()
            total_lifespan += robot.get_lifespan()
            self.total_batteries_collected += robot.get_batteries_collected()

        self.average_fitness = total_fitness / float(len(robots))
        self.average_lifespan = total_lifespan / len(robots)

    def report_generation_data(self, generation_number):
        print(f"\n\nGeneration {generation_number + 1} - \tAverage Fitness: {self.average_fitness}, Total Batteries Collected: {self.total_batteries_collected}, Average Lifespan: {self.average_lifespan}")

    @staticmethod
    def add_to_total(gen):
        Generation.total_fitness_sum += gen.average_fitness
        Generation.total_batteries_sum += gen.total_batteries_collected
        Generation.total_lifespan_sum += gen.average_lifespan
        Generation.count += 1

    @staticmethod
    def report_final_average():
        print("\n--FINAL--")
        print("\nFinal Average Fitness:", Generation.total_fitness_sum / Generation.count)
        print("Final Total Batteries Collected:", Generation.total_batteries_sum)
        print("Final Average Lifespan:", Generation.total_lifespan_sum / Generation.count)

     
    def reset_totals():
        Generation.total_fitness_sum = 0
        Generation.total_batteries_sum = 0
        Generation.total_lifespan_sum = 0
        Generation.count = 0

def setup_environment(grid, GRID_SIZE):
    for row in grid:
        for i in range(len(row)):
            row[i] = 0
    # Randomly place batteries in the grid
    for _ in range(50):  # Place 50 batteries randomly
        x = random.randint(0, GRID_SIZE - 1)
        y = random.randint(0, GRID_SIZE - 1)
        grid[x][y] = 1  # Assuming 1 represents a battery

def genetic_algorithm(robots):
    # Sort robots based on fitness and keep the top half
    robots.sort(key=lambda robot: robot.get_fitness(), reverse=True)
    robots = robots[:len(robots) // 2]

    num_robots = len(robots)
    children = []
    for _ in range(num_robots):
        parent1 = random.choice(robots)
        parent2 = random.choice(robots)
        child = crossover(parent1, parent2)  # Implement crossover logic
        mutate(child)  # Implement mutation logic
        children.append(child)

    robots.extend(children)

def mutate(robot):
    alteration_range = 10
    alteration_offset = 5
    robot.set_example_attribute(robot.get_example_attribute() + random.randint(-alteration_offset, alteration_range - alteration_offset))

def crossover(parent1, parent2):
    child = Robots()
    child.set_example_attribute((parent1.get_example_attribute() + parent2.get_example_attribute()) // 2)
    return child

def main():
    random.seed()
    program_greeting()

    NUM_GENERATIONS = 200
    NUM_ROBOTS = 200
    SIMULATION_STEPS = 100
    GRID_SIZE = 10
    
    robots = [Robots() for _ in range(NUM_ROBOTS)]
    grid = [[0 for _ in range(GRID_SIZE)] for _ in range(GRID_SIZE)]

    for gen in range(NUM_GENERATIONS):
        setup_environment(grid, GRID_SIZE)

        for step in range(SIMULATION_STEPS):
            for robot in robots:
                robot.sense_environment(grid)
                robot.update_velocity_based_on_sensors()
                robot.update_position()
                robot.perform_tasks(grid)

        genetic_algorithm(robots)
        generation = Generation()
        generation.calculate_metrics(robots)
        generation.report_generation_data(gen)
        Generation.add_to_total(generation)

    Generation.report_final_average()

main()
