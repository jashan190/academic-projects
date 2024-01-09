//FinalProject.cpp
//Jashandeep Singh, CISP 400
//12/15/2023


#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

void programGreeting();
int moveNorth(int xCoords);
int moveSouth(int xCoords);
int moveWest(int yCoords);
int moveEast(int yCoords);


class Robots {
    int sensors[16][5];
    int newTurn;
    int newHarvest;
    int xVelocity, yVelocity; // using velocity as it is the derivative of postion. meaning they are the derivatives x cords and y cords. 
    int xCoords, yCoords;
    int batteryLevel;
    int exampleAttribute;

public:
    Robots() : xVelocity(0), yVelocity(0), xCoords(0), yCoords(0), batteryLevel(5), exampleAttribute(rand() % 100) {
        for (int x = 0; x < 16; ++x) {
            for (int y = 0; y < 5; ++y) {
                sensors[x][y] = rand() % 4;
            }
        }
    }
    int getExampleAttribute() const { return exampleAttribute; }
    void setExampleAttribute(int value) { exampleAttribute = value; }
    void updateVelocityBasedOnSensors() {
        int maxBatteries = 0, direction = -1;
        for (int i = 0; i < 4; ++i) {
            if (sensors[i][0] > maxBatteries) {
                maxBatteries = sensors[i][0];
                direction = i;
            }
        }

        switch (direction) {
            case 0: yVelocity--; break;
            case 1: yVelocity++; break;
            case 2: xVelocity++; break;
            case 3: xVelocity--; break;
        }
    }

    void updatePosition() {
        xCoords += xVelocity;
        yCoords += yVelocity;
        xCoords = max(0, min(xCoords, 9));
        yCoords = max(0, min(yCoords, 9));
        newTurn++; 
    }

    void senseEnvironment(const vector<vector<int>>& grid) {
        for (auto& row : sensors) {
            fill(begin(row), end(row), 0);
        }

        if (xCoords > 0) sensors[0][0] = grid[xCoords - 1][yCoords];
        if (xCoords < grid.size() - 1) sensors[1][0] = grid[xCoords + 1][yCoords];
        if (yCoords < grid[0].size() - 1) sensors[2][0] = grid[xCoords][yCoords + 1];
        if (yCoords > 0) sensors[3][0] = grid[xCoords][yCoords - 1];
    }

void performTasks(vector<vector<int>>& grid) {
    if (grid[xCoords][yCoords] > 0) {
        batteryLevel += grid[xCoords][yCoords];
        newHarvest++; // Increment when a battery is collected
        grid[xCoords][yCoords] = 0;
        
    }
    // Additional task-related logic
}
    int getLifespan() const {
      return newTurn;
    }
    int getBatteriesCollected()const{
      return newHarvest;
    }
    int getFitness() const {
        return newHarvest;
    }
};





class Generation {
    float averageFitness;
    int totalBatteriesCollected;
    int averageLifespan;
    static float totalFitnessSum;
    static int totalBatteriesSum;
    static int totalLifespanSum;
    static int count;
public:
    Generation() : averageFitness(0), totalBatteriesCollected(0), averageLifespan(0) {}

    void calculateMetrics(const vector<Robots>& robots) {
        int totalFitness = 0, totalLifespan = 0;
        for (const auto& robot : robots) {
            totalFitness += robot.getFitness();
            totalLifespan += robot.getLifespan(); 
            totalBatteriesCollected += robot.getBatteriesCollected(); 
        }
        averageFitness = totalFitness / static_cast<float>(robots.size());
        averageLifespan = totalLifespan / robots.size();
    }

    void reportGenerationData(int generationNumber) const {   
      cout << "\n\nGeneration " << generationNumber + 1 << " - \tAverage Fitness: " << averageFitness
             << ", Total Batteries Collected:" << totalBatteriesCollected
             << ", Average Lifespan: " << averageLifespan << endl;
    }
  static void addToTotal(const Generation& gen) {
      totalFitnessSum += gen.averageFitness;
      totalBatteriesSum += gen.totalBatteriesCollected;
      totalLifespanSum += gen.averageLifespan;
      count++;
  }
  static void reportFinalAverage() {
    cout << "\n--FINAL--" << endl;
    cout << "\nFinal Average Fitness: " << (totalFitnessSum / count) << endl;
    cout << "Final Total Batteries Collected: " << totalBatteriesSum << endl;
    cout << "Final Average Lifespan: " << (totalLifespanSum / count) << endl;
  }
  static void resetTotals() {
      totalFitnessSum = 0;
      totalBatteriesSum = 0;
      totalLifespanSum = 0;
      count = 0;
  }
};
//Static members that I decided to initialize right after the generation class. 
float Generation::totalFitnessSum = 0;
int Generation::totalBatteriesSum = 0;
int Generation::totalLifespanSum = 0;
int Generation::count = 0;





// function protoypes which use the classes so their prototypes will be under the class

void setupEnvironment(vector<vector<int>>& grid, int GRID_SIZE);
void geneticAlgorithm(vector<Robots>& robots);
Robots crossover(const Robots& parent1, const Robots& parent2);
void mutate(Robots& robot);
int main() {
    srand(time(NULL));
    programGreeting(); 

    const int NUM_GENERATIONS = 200;
    const int NUM_ROBOTS = 200;
    const int SIMULATION_STEPS = 100;
    const int GRID_SIZE = 10;
    
    vector<Robots> robots(NUM_ROBOTS);
    vector<vector<int>> grid(GRID_SIZE, vector<int>(GRID_SIZE, 0));

    for (int gen = 0; gen < NUM_GENERATIONS; ++gen) {
        setupEnvironment(grid, GRID_SIZE);

        for (int step = 0; step < SIMULATION_STEPS; ++step) {
            for (auto& robot : robots) {
                robot.senseEnvironment(grid);
                robot.updateVelocityBasedOnSensors();
                robot.updatePosition();
                robot.performTasks(grid);
            }
        }

        geneticAlgorithm(robots);
        Generation generation; 
        generation.calculateMetrics(robots);
        generation.reportGenerationData(gen);
        Generation::addToTotal(generation);
    }

    Generation::reportFinalAverage();
    return 0;
}

void programGreeting() {
    cout << "Hello Everyone!" << endl;
    cout << "Welcome to my Final for CISP 400" << endl;
    cout << "My name is Jashandeep Singh and in this final we will be conducting survival of the fittest experiment using robots!" << endl;
    cout << "This experiment was first conducted at Harvard!" << endl;
    cout << "Here is some cool art" << endl;
    cout << R"(
  _____/\\\\\\\\\________/\\\\\\\\\\\__________/\\\\\\\\\__/\\\\\\\\\\\__/\\\\\\\\\\\_        
   ___/\\\\\\\\\\\\\____/\\\/////////\\\_____/\\\////////__\/////\\\///__\/////\\\///__       
    __/\\\/////////\\\__\//\\\______\///____/\\\/_______________\/\\\_________\/\\\_____      
     _\/\\\_______\/\\\___\////\\\__________/\\\_________________\/\\\_________\/\\\_____     
      _\/\\\\\\\\\\\\\\\______\////\\\______\/\\\_________________\/\\\_________\/\\\_____    
       _\/\\\/////////\\\_________\////\\\___\//\\\________________\/\\\_________\/\\\_____   
        _\/\\\_______\/\\\__/\\\______\//\\\___\///\\\______________\/\\\_________\/\\\_____  
        _\/\\\_______\/\\\_\///\\\\\\\\\\\/______\////\\\\\\\\\__/\\\\\\\\\\\__/\\\\\\\\\\\_ 
          _\///________\///____\///////////___________\/////////__\///////////__\///////////__        
  )" << '\n';
    cout << "The average lifespan will be the average amount of turns each Robot survives." << endl;
}

// Implement crossover and mutate functions here
void setupEnvironment(vector<vector<int>>& grid, int GRID_SIZE) {
    for (auto& row : grid) fill(row.begin(), row.end(), 0);
    // Randomly place batteries in the grid
    for (int i = 0; i < 50; ++i) {  // Place 50 batteries randomly
        int x = rand() % GRID_SIZE;
        int y = rand() % GRID_SIZE;
        grid[x][y] = 1; // Assuming 1 represents a battery
    }
}

void geneticAlgorithm(vector<Robots>& robots) {
    sort(robots.begin(), robots.end(), [](const Robots& a, const Robots& b) {
        return a.getFitness() > b.getFitness();
    });

    robots.resize(robots.size() / 2);

    int numRobots = robots.size();
    for (int i = 0; i < numRobots; ++i) {
        Robots parent1 = robots[rand() % numRobots];
        Robots parent2 = robots[rand() % numRobots];
        Robots child = crossover(parent1, parent2); // Implement crossover logic
        mutate(child); // Implement mutation logic
        robots.push_back(child);
    }
}
// The implementation of the mutate function
  void mutate(Robots& robot) {
    const int alterationRange = 10;
    const int alterationOffset = 5;
    robot.setExampleAttribute(robot.getExampleAttribute() + (rand() % alterationRange - alterationOffset));
}

// The implementation of the crossover function
Robots crossover(const Robots& parent1, const Robots& parent2) {
    Robots child;
  child.setExampleAttribute((parent1.getExampleAttribute() + parent2.getExampleAttribute()) / 2);
  return child;
}

/*Hello Everyone!
Welcome to my Final for CISP 400
My name is Jashandeep Singh and in this final we will be conducting survival of the fittest experiment using robots!
This experiment was first conducted at Harvard!
Here is some cool art

  _____/\\\\\\\\\________/\\\\\\\\\\\__________/\\\\\\\\\__/\\\\\\\\\\\__/\\\\\\\\\\\_        
   ___/\\\\\\\\\\\\\____/\\\/////////\\\_____/\\\////////__\/////\\\///__\/////\\\///__       
    __/\\\/////////\\\__\//\\\______\///____/\\\/_______________\/\\\_________\/\\\_____      
     _\/\\\_______\/\\\___\////\\\__________/\\\_________________\/\\\_________\/\\\_____     
      _\/\\\\\\\\\\\\\\\______\////\\\______\/\\\_________________\/\\\_________\/\\\_____    
       _\/\\\/////////\\\_________\////\\\___\//\\\________________\/\\\_________\/\\\_____   
        _\/\\\_______\/\\\__/\\\______\//\\\___\///\\\______________\/\\\_________\/\\\_____  
        _\/\\\_______\/\\\_\///\\\\\\\\\\\/______\////\\\\\\\\\__/\\\\\\\\\\\__/\\\\\\\\\\\_ 
          _\///________\///____\///////////___________\/////////__\///////////__\///////////__        
  
The average lifespan will be the average amount of turns each Robot survives.
Generation 1 - Average Fitness: 0.505, Total Batteries Collected: 101, Average Lifespan: 100
The average lifespan will be the average amount of turns each Robot survives.
Generation 2 - Average Fitness: 1.505, Total Batteries Collected: 301, Average Lifespan: 200
The average lifespan will be the average amount of turns each Robot survives.
Generation 3 - Average Fitness: 1, Total Batteries Collected: 200, Average Lifespan: 300
The average lifespan will be the average amount of turns each Robot survives.
Generation 4 - Average Fitness: 5.03, Total Batteries Collected: 1006, Average Lifespan: 400
The average lifespan will be the average amount of turns each Robot survives.
Generation 5 - Average Fitness: 4.01, Total Batteries Collected: 802, Average Lifespan: 500
The average lifespan will be the average amount of turns each Robot survives.
Generation 6 - Average Fitness: 4.01, Total Batteries Collected: 802, Average Lifespan: 600
The average lifespan will be the average amount of turns each Robot survives.
Generation 7 - Average Fitness: 8.51, Total Batteries Collected: 1702, Average Lifespan: 700
The average lifespan will be the average amount of turns each Robot survives.
Generation 8 - Average Fitness: 4.5, Total Batteries Collected: 900, Average Lifespan: 800
The average lifespan will be the average amount of turns each Robot survives.
Generation 9 - Average Fitness: 10.01, Total Batteries Collected: 2002, Average Lifespan: 900
The average lifespan will be the average amount of turns each Robot survives.
Generation 10 - Average Fitness: 12.01, Total Batteries Collected: 2402, Average Lifespan: 1000
The average lifespan will be the average amount of turns each Robot survives.
Generation 11 - Average Fitness: 6.5, Total Batteries Collected: 1300, Average Lifespan: 1100
The average lifespan will be the average amount of turns each Robot survives.
Generation 12 - Average Fitness: 15.525, Total Batteries Collected: 3105, Average Lifespan: 1200
The average lifespan will be the average amount of turns each Robot survives.
Generation 13 - Average Fitness: 19.01, Total Batteries Collected: 3802, Average Lifespan: 1300
The average lifespan will be the average amount of turns each Robot survives.
Generation 14 - Average Fitness: 21.01, Total Batteries Collected: 4202, Average Lifespan: 1400
The average lifespan will be the average amount of turns each Robot survives.
Generation 15 - Average Fitness: 23.515, Total Batteries Collected: 4703, Average Lifespan: 1500
The average lifespan will be the average amount of turns each Robot survives.
Generation 16 - Average Fitness: 26.515, Total Batteries Collected: 5303, Average Lifespan: 1600
The average lifespan will be the average amount of turns each Robot survives.
Generation 17 - Average Fitness: 30.02, Total Batteries Collected: 6004, Average Lifespan: 1700
The average lifespan will be the average amount of turns each Robot survives.
Generation 18 - Average Fitness: 34.525, Total Batteries Collected: 6905, Average Lifespan: 1800
The average lifespan will be the average amount of turns each Robot survives.
Generation 19 - Average Fitness: 18.5, Total Batteries Collected: 3700, Average Lifespan: 1900
The average lifespan will be the average amount of turns each Robot survives.
Generation 20 - Average Fitness: 37.505, Total Batteries Collected: 7501, Average Lifespan: 2000
The average lifespan will be the average amount of turns each Robot survives.
Generation 21 - Average Fitness: 39.01, Total Batteries Collected: 7802, Average Lifespan: 2100
The average lifespan will be the average amount of turns each Robot survives.
Generation 22 - Average Fitness: 41.015, Total Batteries Collected: 8203, Average Lifespan: 2200
The average lifespan will be the average amount of turns each Robot survives.
Generation 23 - Average Fitness: 43.01, Total Batteries Collected: 8602, Average Lifespan: 2300
The average lifespan will be the average amount of turns each Robot survives.
Generation 24 - Average Fitness: 44.505, Total Batteries Collected: 8901, Average Lifespan: 2400
The average lifespan will be the average amount of turns each Robot survives.
Generation 25 - Average Fitness: 45.505, Total Batteries Collected: 9101, Average Lifespan: 2500
The average lifespan will be the average amount of turns each Robot survives.
Generation 26 - Average Fitness: 46.505, Total Batteries Collected: 9301, Average Lifespan: 2600
The average lifespan will be the average amount of turns each Robot survives.
Generation 27 - Average Fitness: 23.5, Total Batteries Collected: 4700, Average Lifespan: 2700
The average lifespan will be the average amount of turns each Robot survives.
Generation 28 - Average Fitness: 48.01, Total Batteries Collected: 9602, Average Lifespan: 2800
The average lifespan will be the average amount of turns each Robot survives.
Generation 29 - Average Fitness: 52.535, Total Batteries Collected: 10507, Average Lifespan: 2900
The average lifespan will be the average amount of turns each Robot survives.
Generation 30 - Average Fitness: 56.505, Total Batteries Collected: 11301, Average Lifespan: 3000
The average lifespan will be the average amount of turns each Robot survives.
Generation 31 - Average Fitness: 57.505, Total Batteries Collected: 11501, Average Lifespan: 3100
The average lifespan will be the average amount of turns each Robot survives.
Generation 32 - Average Fitness: 29, Total Batteries Collected: 5800, Average Lifespan: 3200
The average lifespan will be the average amount of turns each Robot survives.
Generation 33 - Average Fitness: 29, Total Batteries Collected: 5800, Average Lifespan: 3300
The average lifespan will be the average amount of turns each Robot survives.
Generation 34 - Average Fitness: 29, Total Batteries Collected: 5800, Average Lifespan: 3400
The average lifespan will be the average amount of turns each Robot survives.
Generation 35 - Average Fitness: 29, Total Batteries Collected: 5800, Average Lifespan: 3500
The average lifespan will be the average amount of turns each Robot survives.
Generation 36 - Average Fitness: 29, Total Batteries Collected: 5800, Average Lifespan: 3600
The average lifespan will be the average amount of turns each Robot survives.
Generation 37 - Average Fitness: 29, Total Batteries Collected: 5800, Average Lifespan: 3700
The average lifespan will be the average amount of turns each Robot survives.
Generation 38 - Average Fitness: 29, Total Batteries Collected: 5800, Average Lifespan: 3800
The average lifespan will be the average amount of turns each Robot survives.
Generation 39 - Average Fitness: 58.505, Total Batteries Collected: 11701, Average Lifespan: 3900
The average lifespan will be the average amount of turns each Robot survives.
Generation 40 - Average Fitness: 61.55, Total Batteries Collected: 12310, Average Lifespan: 4000
The average lifespan will be the average amount of turns each Robot survives.
Generation 41 - Average Fitness: 65.02, Total Batteries Collected: 13004, Average Lifespan: 4100
The average lifespan will be the average amount of turns each Robot survives.
Generation 42 - Average Fitness: 33, Total Batteries Collected: 6600, Average Lifespan: 4200
The average lifespan will be the average amount of turns each Robot survives.
Generation 43 - Average Fitness: 33, Total Batteries Collected: 6600, Average Lifespan: 4300
The average lifespan will be the average amount of turns each Robot survives.
Generation 44 - Average Fitness: 66.505, Total Batteries Collected: 13301, Average Lifespan: 4400
The average lifespan will be the average amount of turns each Robot survives.
Generation 45 - Average Fitness: 33.5, Total Batteries Collected: 6700, Average Lifespan: 4500
The average lifespan will be the average amount of turns each Robot survives.
Generation 46 - Average Fitness: 33.5, Total Batteries Collected: 6700, Average Lifespan: 4600
The average lifespan will be the average amount of turns each Robot survives.
Generation 47 - Average Fitness: 33.5, Total Batteries Collected: 6700, Average Lifespan: 4700
The average lifespan will be the average amount of turns each Robot survives.
Generation 48 - Average Fitness: 68.01, Total Batteries Collected: 13602, Average Lifespan: 4800
The average lifespan will be the average amount of turns each Robot survives.
Generation 49 - Average Fitness: 70.52, Total Batteries Collected: 14104, Average Lifespan: 4900
The average lifespan will be the average amount of turns each Robot survives.
Generation 50 - Average Fitness: 73.515, Total Batteries Collected: 14703, Average Lifespan: 5000
The average lifespan will be the average amount of turns each Robot survives.
Generation 51 - Average Fitness: 75.505, Total Batteries Collected: 15101, Average Lifespan: 5100
The average lifespan will be the average amount of turns each Robot survives.
Generation 52 - Average Fitness: 38, Total Batteries Collected: 7600, Average Lifespan: 5200
The average lifespan will be the average amount of turns each Robot survives.
Generation 53 - Average Fitness: 76.505, Total Batteries Collected: 15301, Average Lifespan: 5300
The average lifespan will be the average amount of turns each Robot survives.
Generation 54 - Average Fitness: 38.5, Total Batteries Collected: 7700, Average Lifespan: 5400
The average lifespan will be the average amount of turns each Robot survives.
Generation 55 - Average Fitness: 38.5, Total Batteries Collected: 7700, Average Lifespan: 5500
The average lifespan will be the average amount of turns each Robot survives.
Generation 56 - Average Fitness: 80.03, Total Batteries Collected: 16006, Average Lifespan: 5600
The average lifespan will be the average amount of turns each Robot survives.
Generation 57 - Average Fitness: 85.535, Total Batteries Collected: 17107, Average Lifespan: 5700
The average lifespan will be the average amount of turns each Robot survives.
Generation 58 - Average Fitness: 44, Total Batteries Collected: 8800, Average Lifespan: 5800
The average lifespan will be the average amount of turns each Robot survives.
Generation 59 - Average Fitness: 44, Total Batteries Collected: 8800, Average Lifespan: 5900
The average lifespan will be the average amount of turns each Robot survives.
Generation 60 - Average Fitness: 89.515, Total Batteries Collected: 17903, Average Lifespan: 6000
The average lifespan will be the average amount of turns each Robot survives.
Generation 61 - Average Fitness: 93.53, Total Batteries Collected: 18706, Average Lifespan: 6100
The average lifespan will be the average amount of turns each Robot survives.
Generation 62 - Average Fitness: 97.015, Total Batteries Collected: 19403, Average Lifespan: 6200
The average lifespan will be the average amount of turns each Robot survives.
Generation 63 - Average Fitness: 49.01, Total Batteries Collected: 9802, Average Lifespan: 6300
The average lifespan will be the average amount of turns each Robot survives.
Generation 64 - Average Fitness: 49.01, Total Batteries Collected: 9802, Average Lifespan: 6400
The average lifespan will be the average amount of turns each Robot survives.
Generation 65 - Average Fitness: 99.015, Total Batteries Collected: 19803, Average Lifespan: 6500
The average lifespan will be the average amount of turns each Robot survives.
Generation 66 - Average Fitness: 100.505, Total Batteries Collected: 20101, Average Lifespan: 6600
The average lifespan will be the average amount of turns each Robot survives.
Generation 67 - Average Fitness: 50.5, Total Batteries Collected: 10100, Average Lifespan: 6700
The average lifespan will be the average amount of turns each Robot survives.
Generation 68 - Average Fitness: 50.5, Total Batteries Collected: 10100, Average Lifespan: 6800
The average lifespan will be the average amount of turns each Robot survives.
Generation 69 - Average Fitness: 102.01, Total Batteries Collected: 20402, Average Lifespan: 6900
The average lifespan will be the average amount of turns each Robot survives.
Generation 70 - Average Fitness: 103.505, Total Batteries Collected: 20701, Average Lifespan: 7000
The average lifespan will be the average amount of turns each Robot survives.
Generation 71 - Average Fitness: 105.01, Total Batteries Collected: 21002, Average Lifespan: 7100
The average lifespan will be the average amount of turns each Robot survives.
Generation 72 - Average Fitness: 107.52, Total Batteries Collected: 21504, Average Lifespan: 7200
The average lifespan will be the average amount of turns each Robot survives.
Generation 73 - Average Fitness: 109.505, Total Batteries Collected: 21901, Average Lifespan: 7300
The average lifespan will be the average amount of turns each Robot survives.
Generation 74 - Average Fitness: 55, Total Batteries Collected: 11000, Average Lifespan: 7400
The average lifespan will be the average amount of turns each Robot survives.
Generation 75 - Average Fitness: 110.505, Total Batteries Collected: 22101, Average Lifespan: 7500
The average lifespan will be the average amount of turns each Robot survives.
Generation 76 - Average Fitness: 112.01, Total Batteries Collected: 22402, Average Lifespan: 7600
The average lifespan will be the average amount of turns each Robot survives.
Generation 77 - Average Fitness: 56.53, Total Batteries Collected: 11306, Average Lifespan: 7700
The average lifespan will be the average amount of turns each Robot survives.
Generation 78 - Average Fitness: 115.545, Total Batteries Collected: 23109, Average Lifespan: 7800
The average lifespan will be the average amount of turns each Robot survives.
Generation 79 - Average Fitness: 120.03, Total Batteries Collected: 24006, Average Lifespan: 7900
The average lifespan will be the average amount of turns each Robot survives.
Generation 80 - Average Fitness: 61.01, Total Batteries Collected: 12202, Average Lifespan: 8000
The average lifespan will be the average amount of turns each Robot survives.
Generation 81 - Average Fitness: 122.51, Total Batteries Collected: 24502, Average Lifespan: 8100
The average lifespan will be the average amount of turns each Robot survives.
Generation 82 - Average Fitness: 61.5, Total Batteries Collected: 12300, Average Lifespan: 8200
The average lifespan will be the average amount of turns each Robot survives.
Generation 83 - Average Fitness: 123.505, Total Batteries Collected: 24701, Average Lifespan: 8300
The average lifespan will be the average amount of turns each Robot survives.
Generation 84 - Average Fitness: 62, Total Batteries Collected: 12400, Average Lifespan: 8400
The average lifespan will be the average amount of turns each Robot survives.
Generation 85 - Average Fitness: 127.03, Total Batteries Collected: 25406, Average Lifespan: 8500
The average lifespan will be the average amount of turns each Robot survives.
Generation 86 - Average Fitness: 132.025, Total Batteries Collected: 26405, Average Lifespan: 8600
The average lifespan will be the average amount of turns each Robot survives.
Generation 87 - Average Fitness: 67, Total Batteries Collected: 13400, Average Lifespan: 8700
The average lifespan will be the average amount of turns each Robot survives.
Generation 88 - Average Fitness: 134.505, Total Batteries Collected: 26901, Average Lifespan: 8800
The average lifespan will be the average amount of turns each Robot survives.
Generation 89 - Average Fitness: 137.025, Total Batteries Collected: 27405, Average Lifespan: 8900
The average lifespan will be the average amount of turns each Robot survives.
Generation 90 - Average Fitness: 69.5, Total Batteries Collected: 13900, Average Lifespan: 9000
The average lifespan will be the average amount of turns each Robot survives.
Generation 91 - Average Fitness: 140.01, Total Batteries Collected: 28002, Average Lifespan: 9100
The average lifespan will be the average amount of turns each Robot survives.
Generation 92 - Average Fitness: 142.01, Total Batteries Collected: 28402, Average Lifespan: 9200
The average lifespan will be the average amount of turns each Robot survives.
Generation 93 - Average Fitness: 144.515, Total Batteries Collected: 28903, Average Lifespan: 9300
The average lifespan will be the average amount of turns each Robot survives.
Generation 94 - Average Fitness: 73, Total Batteries Collected: 14600, Average Lifespan: 9400
The average lifespan will be the average amount of turns each Robot survives.
Generation 95 - Average Fitness: 148.02, Total Batteries Collected: 29604, Average Lifespan: 9500
The average lifespan will be the average amount of turns each Robot survives.
Generation 96 - Average Fitness: 151.015, Total Batteries Collected: 30203, Average Lifespan: 9600
The average lifespan will be the average amount of turns each Robot survives.
Generation 97 - Average Fitness: 153.515, Total Batteries Collected: 30703, Average Lifespan: 9700
The average lifespan will be the average amount of turns each Robot survives.
Generation 98 - Average Fitness: 77.5, Total Batteries Collected: 15500, Average Lifespan: 9800
The average lifespan will be the average amount of turns each Robot survives.
Generation 99 - Average Fitness: 77.5, Total Batteries Collected: 15500, Average Lifespan: 9900
The average lifespan will be the average amount of turns each Robot survives.
Generation 100 - Average Fitness: 77.5, Total Batteries Collected: 15500, Average Lifespan: 10000
The average lifespan will be the average amount of turns each Robot survives.
Generation 101 - Average Fitness: 77.5, Total Batteries Collected: 15500, Average Lifespan: 10100
The average lifespan will be the average amount of turns each Robot survives.
Generation 102 - Average Fitness: 77.5, Total Batteries Collected: 15500, Average Lifespan: 10200
The average lifespan will be the average amount of turns each Robot survives.
Generation 103 - Average Fitness: 155.505, Total Batteries Collected: 31101, Average Lifespan: 10300
The average lifespan will be the average amount of turns each Robot survives.
Generation 104 - Average Fitness: 156.505, Total Batteries Collected: 31301, Average Lifespan: 10400
The average lifespan will be the average amount of turns each Robot survives.
Generation 105 - Average Fitness: 159.525, Total Batteries Collected: 31905, Average Lifespan: 10500
The average lifespan will be the average amount of turns each Robot survives.
Generation 106 - Average Fitness: 162.505, Total Batteries Collected: 32501, Average Lifespan: 10600
The average lifespan will be the average amount of turns each Robot survives.
Generation 107 - Average Fitness: 163.505, Total Batteries Collected: 32701, Average Lifespan: 10700
The average lifespan will be the average amount of turns each Robot survives.
Generation 108 - Average Fitness: 165.01, Total Batteries Collected: 33002, Average Lifespan: 10800
The average lifespan will be the average amount of turns each Robot survives.
Generation 109 - Average Fitness: 166.51, Total Batteries Collected: 33302, Average Lifespan: 10900
The average lifespan will be the average amount of turns each Robot survives.
Generation 110 - Average Fitness: 167.505, Total Batteries Collected: 33501, Average Lifespan: 11000
The average lifespan will be the average amount of turns each Robot survives.
Generation 111 - Average Fitness: 168.505, Total Batteries Collected: 33701, Average Lifespan: 11100
The average lifespan will be the average amount of turns each Robot survives.
Generation 112 - Average Fitness: 171.02, Total Batteries Collected: 34204, Average Lifespan: 11200
The average lifespan will be the average amount of turns each Robot survives.
Generation 113 - Average Fitness: 173.505, Total Batteries Collected: 34701, Average Lifespan: 11300
The average lifespan will be the average amount of turns each Robot survives.
Generation 114 - Average Fitness: 175.01, Total Batteries Collected: 35002, Average Lifespan: 11400
The average lifespan will be the average amount of turns each Robot survives.
Generation 115 - Average Fitness: 178.53, Total Batteries Collected: 35706, Average Lifespan: 11500
The average lifespan will be the average amount of turns each Robot survives.
Generation 116 - Average Fitness: 90.51, Total Batteries Collected: 18102, Average Lifespan: 11600
The average lifespan will be the average amount of turns each Robot survives.
Generation 117 - Average Fitness: 182.015, Total Batteries Collected: 36403, Average Lifespan: 11700
The average lifespan will be the average amount of turns each Robot survives.
Generation 118 - Average Fitness: 184.515, Total Batteries Collected: 36903, Average Lifespan: 11800
The average lifespan will be the average amount of turns each Robot survives.
Generation 119 - Average Fitness: 93, Total Batteries Collected: 18600, Average Lifespan: 11900
The average lifespan will be the average amount of turns each Robot survives.
Generation 120 - Average Fitness: 93, Total Batteries Collected: 18600, Average Lifespan: 12000
The average lifespan will be the average amount of turns each Robot survives.
Generation 121 - Average Fitness: 188.545, Total Batteries Collected: 37709, Average Lifespan: 12100
The average lifespan will be the average amount of turns each Robot survives.
Generation 122 - Average Fitness: 195.545, Total Batteries Collected: 39109, Average Lifespan: 12200
The average lifespan will be the average amount of turns each Robot survives.
Generation 123 - Average Fitness: 200.505, Total Batteries Collected: 40101, Average Lifespan: 12300
The average lifespan will be the average amount of turns each Robot survives.
Generation 124 - Average Fitness: 204.035, Total Batteries Collected: 40807, Average Lifespan: 12400
The average lifespan will be the average amount of turns each Robot survives.
Generation 125 - Average Fitness: 208.515, Total Batteries Collected: 41703, Average Lifespan: 12500
The average lifespan will be the average amount of turns each Robot survives.
Generation 126 - Average Fitness: 212.035, Total Batteries Collected: 42407, Average Lifespan: 12600
The average lifespan will be the average amount of turns each Robot survives.
Generation 127 - Average Fitness: 215.01, Total Batteries Collected: 43002, Average Lifespan: 12700
The average lifespan will be the average amount of turns each Robot survives.
Generation 128 - Average Fitness: 218.025, Total Batteries Collected: 43605, Average Lifespan: 12800
The average lifespan will be the average amount of turns each Robot survives.
Generation 129 - Average Fitness: 222.035, Total Batteries Collected: 44407, Average Lifespan: 12900
The average lifespan will be the average amount of turns each Robot survives.
Generation 130 - Average Fitness: 226.02, Total Batteries Collected: 45204, Average Lifespan: 13000
The average lifespan will be the average amount of turns each Robot survives.
Generation 131 - Average Fitness: 228.505, Total Batteries Collected: 45701, Average Lifespan: 13100
The average lifespan will be the average amount of turns each Robot survives.
Generation 132 - Average Fitness: 230.515, Total Batteries Collected: 46103, Average Lifespan: 13200
The average lifespan will be the average amount of turns each Robot survives.
Generation 133 - Average Fitness: 234.525, Total Batteries Collected: 46905, Average Lifespan: 13300
The average lifespan will be the average amount of turns each Robot survives.
Generation 134 - Average Fitness: 237.505, Total Batteries Collected: 47501, Average Lifespan: 13400
The average lifespan will be the average amount of turns each Robot survives.
Generation 135 - Average Fitness: 238.505, Total Batteries Collected: 47701, Average Lifespan: 13500
The average lifespan will be the average amount of turns each Robot survives.
Generation 136 - Average Fitness: 240.515, Total Batteries Collected: 48103, Average Lifespan: 13600
The average lifespan will be the average amount of turns each Robot survives.
Generation 137 - Average Fitness: 242.505, Total Batteries Collected: 48501, Average Lifespan: 13700
The average lifespan will be the average amount of turns each Robot survives.
Generation 138 - Average Fitness: 244.015, Total Batteries Collected: 48803, Average Lifespan: 13800
The average lifespan will be the average amount of turns each Robot survives.
Generation 139 - Average Fitness: 247.545, Total Batteries Collected: 49509, Average Lifespan: 13900
The average lifespan will be the average amount of turns each Robot survives.
Generation 140 - Average Fitness: 251.515, Total Batteries Collected: 50303, Average Lifespan: 14000
The average lifespan will be the average amount of turns each Robot survives.
Generation 141 - Average Fitness: 126.5, Total Batteries Collected: 25300, Average Lifespan: 14100
The average lifespan will be the average amount of turns each Robot survives.
Generation 142 - Average Fitness: 126.5, Total Batteries Collected: 25300, Average Lifespan: 14200
The average lifespan will be the average amount of turns each Robot survives.
Generation 143 - Average Fitness: 126.5, Total Batteries Collected: 25300, Average Lifespan: 14300
The average lifespan will be the average amount of turns each Robot survives.
Generation 144 - Average Fitness: 253.505, Total Batteries Collected: 50701, Average Lifespan: 14400
The average lifespan will be the average amount of turns each Robot survives.
Generation 145 - Average Fitness: 127, Total Batteries Collected: 25400, Average Lifespan: 14500
The average lifespan will be the average amount of turns each Robot survives.
Generation 146 - Average Fitness: 127, Total Batteries Collected: 25400, Average Lifespan: 14600
The average lifespan will be the average amount of turns each Robot survives.
Generation 147 - Average Fitness: 258.04, Total Batteries Collected: 51608, Average Lifespan: 14700
The average lifespan will be the average amount of turns each Robot survives.
Generation 148 - Average Fitness: 131.01, Total Batteries Collected: 26202, Average Lifespan: 14800
The average lifespan will be the average amount of turns each Robot survives.
Generation 149 - Average Fitness: 263.015, Total Batteries Collected: 52603, Average Lifespan: 14900
The average lifespan will be the average amount of turns each Robot survives.
Generation 150 - Average Fitness: 266.02, Total Batteries Collected: 53204, Average Lifespan: 15000
The average lifespan will be the average amount of turns each Robot survives.
Generation 151 - Average Fitness: 134.02, Total Batteries Collected: 26804, Average Lifespan: 15100
The average lifespan will be the average amount of turns each Robot survives.
Generation 152 - Average Fitness: 269.525, Total Batteries Collected: 53905, Average Lifespan: 15200
The average lifespan will be the average amount of turns each Robot survives.
Generation 153 - Average Fitness: 135.5, Total Batteries Collected: 27100, Average Lifespan: 15300
The average lifespan will be the average amount of turns each Robot survives.
Generation 154 - Average Fitness: 135.5, Total Batteries Collected: 27100, Average Lifespan: 15400
The average lifespan will be the average amount of turns each Robot survives.
Generation 155 - Average Fitness: 272.515, Total Batteries Collected: 54503, Average Lifespan: 15500
The average lifespan will be the average amount of turns each Robot survives.
Generation 156 - Average Fitness: 274.505, Total Batteries Collected: 54901, Average Lifespan: 15600
The average lifespan will be the average amount of turns each Robot survives.
Generation 157 - Average Fitness: 137.5, Total Batteries Collected: 27500, Average Lifespan: 15700
The average lifespan will be the average amount of turns each Robot survives.
Generation 158 - Average Fitness: 275.505, Total Batteries Collected: 55101, Average Lifespan: 15800
The average lifespan will be the average amount of turns each Robot survives.
Generation 159 - Average Fitness: 138.01, Total Batteries Collected: 27602, Average Lifespan: 15900
The average lifespan will be the average amount of turns each Robot survives.
Generation 160 - Average Fitness: 280.555, Total Batteries Collected: 56111, Average Lifespan: 16000
The average lifespan will be the average amount of turns each Robot survives.
Generation 161 - Average Fitness: 286.52, Total Batteries Collected: 57304, Average Lifespan: 16100
The average lifespan will be the average amount of turns each Robot survives.
Generation 162 - Average Fitness: 288.505, Total Batteries Collected: 57701, Average Lifespan: 16200
The average lifespan will be the average amount of turns each Robot survives.
Generation 163 - Average Fitness: 289.505, Total Batteries Collected: 57901, Average Lifespan: 16300
The average lifespan will be the average amount of turns each Robot survives.
Generation 164 - Average Fitness: 145, Total Batteries Collected: 29000, Average Lifespan: 16400
The average lifespan will be the average amount of turns each Robot survives.
Generation 165 - Average Fitness: 292.525, Total Batteries Collected: 58505, Average Lifespan: 16500
The average lifespan will be the average amount of turns each Robot survives.
Generation 166 - Average Fitness: 296.015, Total Batteries Collected: 59203, Average Lifespan: 16600
The average lifespan will be the average amount of turns each Robot survives.
Generation 167 - Average Fitness: 299.02, Total Batteries Collected: 59804, Average Lifespan: 16700
The average lifespan will be the average amount of turns each Robot survives.
Generation 168 - Average Fitness: 302.01, Total Batteries Collected: 60402, Average Lifespan: 16800
The average lifespan will be the average amount of turns each Robot survives.
Generation 169 - Average Fitness: 304.01, Total Batteries Collected: 60802, Average Lifespan: 16900
The average lifespan will be the average amount of turns each Robot survives.
Generation 170 - Average Fitness: 152.51, Total Batteries Collected: 30502, Average Lifespan: 17000
The average lifespan will be the average amount of turns each Robot survives.
Generation 171 - Average Fitness: 307.535, Total Batteries Collected: 61507, Average Lifespan: 17100
The average lifespan will be the average amount of turns each Robot survives.
Generation 172 - Average Fitness: 155, Total Batteries Collected: 31000, Average Lifespan: 17200
The average lifespan will be the average amount of turns each Robot survives.
Generation 173 - Average Fitness: 155, Total Batteries Collected: 31000, Average Lifespan: 17300
The average lifespan will be the average amount of turns each Robot survives.
Generation 174 - Average Fitness: 315.05, Total Batteries Collected: 63010, Average Lifespan: 17400
The average lifespan will be the average amount of turns each Robot survives.
Generation 175 - Average Fitness: 322.03, Total Batteries Collected: 64406, Average Lifespan: 17500
The average lifespan will be the average amount of turns each Robot survives.
Generation 176 - Average Fitness: 324.505, Total Batteries Collected: 64901, Average Lifespan: 17600
The average lifespan will be the average amount of turns each Robot survives.
Generation 177 - Average Fitness: 325.505, Total Batteries Collected: 65101, Average Lifespan: 17700
The average lifespan will be the average amount of turns each Robot survives.
Generation 178 - Average Fitness: 163, Total Batteries Collected: 32600, Average Lifespan: 17800
The average lifespan will be the average amount of turns each Robot survives.
Generation 179 - Average Fitness: 327.01, Total Batteries Collected: 65402, Average Lifespan: 17900
The average lifespan will be the average amount of turns each Robot survives.
Generation 180 - Average Fitness: 164, Total Batteries Collected: 32800, Average Lifespan: 18000
The average lifespan will be the average amount of turns each Robot survives.
Generation 181 - Average Fitness: 330.025, Total Batteries Collected: 66005, Average Lifespan: 18100
The average lifespan will be the average amount of turns each Robot survives.
Generation 182 - Average Fitness: 334.025, Total Batteries Collected: 66805, Average Lifespan: 18200
The average lifespan will be the average amount of turns each Robot survives.
Generation 183 - Average Fitness: 336.505, Total Batteries Collected: 67301, Average Lifespan: 18300
The average lifespan will be the average amount of turns each Robot survives.
Generation 184 - Average Fitness: 168.51, Total Batteries Collected: 33702, Average Lifespan: 18400
The average lifespan will be the average amount of turns each Robot survives.
Generation 185 - Average Fitness: 338.015, Total Batteries Collected: 67603, Average Lifespan: 18500
The average lifespan will be the average amount of turns each Robot survives.
Generation 186 - Average Fitness: 169.5, Total Batteries Collected: 33900, Average Lifespan: 18600
The average lifespan will be the average amount of turns each Robot survives.
Generation 187 - Average Fitness: 169.5, Total Batteries Collected: 33900, Average Lifespan: 18700
The average lifespan will be the average amount of turns each Robot survives.
Generation 188 - Average Fitness: 339.505, Total Batteries Collected: 67901, Average Lifespan: 18800
The average lifespan will be the average amount of turns each Robot survives.
Generation 189 - Average Fitness: 340.51, Total Batteries Collected: 68102, Average Lifespan: 18900
The average lifespan will be the average amount of turns each Robot survives.
Generation 190 - Average Fitness: 344.535, Total Batteries Collected: 68907, Average Lifespan: 19000
The average lifespan will be the average amount of turns each Robot survives.
Generation 191 - Average Fitness: 350.025, Total Batteries Collected: 70005, Average Lifespan: 19100
The average lifespan will be the average amount of turns each Robot survives.
Generation 192 - Average Fitness: 354.02, Total Batteries Collected: 70804, Average Lifespan: 19200
The average lifespan will be the average amount of turns each Robot survives.
Generation 193 - Average Fitness: 357.02, Total Batteries Collected: 71404, Average Lifespan: 19300
The average lifespan will be the average amount of turns each Robot survives.
Generation 194 - Average Fitness: 179.01, Total Batteries Collected: 35802, Average Lifespan: 19400
The average lifespan will be the average amount of turns each Robot survives.
Generation 195 - Average Fitness: 359.525, Total Batteries Collected: 71905, Average Lifespan: 19500
The average lifespan will be the average amount of turns each Robot survives.
Generation 196 - Average Fitness: 180.51, Total Batteries Collected: 36102, Average Lifespan: 19600
The average lifespan will be the average amount of turns each Robot survives.
Generation 197 - Average Fitness: 363.025, Total Batteries Collected: 72605, Average Lifespan: 19700
The average lifespan will be the average amount of turns each Robot survives.
Generation 198 - Average Fitness: 182.51, Total Batteries Collected: 36502, Average Lifespan: 19800
The average lifespan will be the average amount of turns each Robot survives.
Generation 199 - Average Fitness: 366.52, Total Batteries Collected: 73304, Average Lifespan: 19900
The average lifespan will be the average amount of turns each Robot survives.
Generation 200 - Average Fitness: 369.525, Total Batteries Collected: 73905, Average Lifespan: 20000
Final Average Fitness: 143.224
Final Total Batteries Collected: 5728977
Final Average Lifespan: 10050 */
