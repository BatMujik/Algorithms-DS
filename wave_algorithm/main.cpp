#include "WaveAlgorithm.h"
#include <iostream>
#include <string>

// Function declarations
void testBasicWaveAlgorithm();
void testAdvancedFeatures();
void testFileIO();
void testGridGeneration();
void performanceBenchmarks();
void interactiveMode();
void demonstrateAlgorithm();

int main() {
    std::cout << "=== WAVE ALGORITHM PATHFINDING IMPLEMENTATION ===" << std::endl;
    std::cout << "Features:" << std::endl;
    std::cout << "- Grid-based pathfinding with obstacle avoidance" << std::endl;
    std::cout << "- Shortest path calculation using BFS wave propagation" << std::endl;
    std::cout << "- 4-directional and 8-directional movement" << std::endl;
    std::cout << "- Distance mapping and path reconstruction" << std::endl;
    std::cout << "- Grid visualization and file I/O" << std::endl;
    std::cout << "- Random obstacle generation and maze support" << std::endl;
    std::cout << "- Copy/Move semantics (Rule of 5)" << std::endl;
    
    while (true) {
        std::cout << "\n========= WAVE ALGORITHM MENU =========" << std::endl;
        std::cout << "1. Test Basic Wave Algorithm" << std::endl;
        std::cout << "2. Test Advanced Features" << std::endl;
        std::cout << "3. Test File I/O" << std::endl;
        std::cout << "4. Test Grid Generation" << std::endl;
        std::cout << "5. Performance Benchmarks" << std::endl;
        std::cout << "6. Interactive Mode" << std::endl;
        std::cout << "7. Algorithm Demonstration" << std::endl;
        std::cout << "8. Run All Tests" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choose an option: ";
        
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a number." << std::endl;
            continue;
        }
        
        std::cin.ignore(); // Clear the newline
        
        try {
            switch (choice) {
                case 1:
                    testBasicWaveAlgorithm();
                    break;
                case 2:
                    testAdvancedFeatures();
                    break;
                case 3:
                    testFileIO();
                    break;
                case 4:
                    testGridGeneration();
                    break;
                case 5:
                    performanceBenchmarks();
                    break;
                case 6:
                    interactiveMode();
                    break;
                case 7:
                    demonstrateAlgorithm();
                    break;
                case 8:
                    testBasicWaveAlgorithm();
                    testAdvancedFeatures();
                    testGridGeneration();
                    performanceBenchmarks();
                    break;
                case 0:
                    std::cout << "Goodbye!" << std::endl;
                    return 0;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
        
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }
    
    return 0;
}

void testBasicWaveAlgorithm() {
    std::cout << "\n========= BASIC WAVE ALGORITHM TESTS =========" << std::endl;
    
    // Test 1: Simple pathfinding
    std::cout << "\n--- Test 1: Simple Grid Pathfinding ---" << std::endl;
    WaveAlgorithm wave = WaveUtils::createSimpleGrid();
    wave.displayGrid();
    
    if (wave.findPath()) {
        std::cout << "Path found!" << std::endl;
        wave.displayPath();
        wave.displayGridWithPath();
        wave.displayDistances();
    } else {
        std::cout << "No path found!" << std::endl;
    }
    
    // Test 2: Copy semantics
    std::cout << "\n--- Test 2: Copy Semantics ---" << std::endl;
    WaveAlgorithm copied_wave = wave;
    copied_wave.displayGridWithPath();
    
    // Test 3: Move semantics
    std::cout << "\n--- Test 3: Move Semantics ---" << std::endl;
    WaveAlgorithm moved_wave = std::move(copied_wave);
    moved_wave.displayGridWithPath();
    
    // Test 4: Maze pathfinding
    std::cout << "\n--- Test 4: Maze Pathfinding ---" << std::endl;
    WaveAlgorithm maze = WaveUtils::createMazeGrid();
    maze.displayGrid();
    
    if (maze.findPath()) {
        std::cout << "Maze path found!" << std::endl;
        maze.displayGridWithPath();
    } else {
        std::cout << "No path through maze!" << std::endl;
    }
    
    // Test 5: No path scenario
    std::cout << "\n--- Test 5: Blocked Path Scenario ---" << std::endl;
    WaveAlgorithm blocked(3, 3);
    blocked.setStart(0, 0);
    blocked.setTarget(2, 2);
    // Create a wall that blocks the path
    blocked.setObstacle(1, 0);
    blocked.setObstacle(1, 1);
    blocked.setObstacle(1, 2);
    blocked.setObstacle(0, 1);
    blocked.setObstacle(2, 1);
    
    blocked.displayGrid();
    
    if (blocked.findPath()) {
        std::cout << "Path found!" << std::endl;
        blocked.displayGridWithPath();
    } else {
        std::cout << "No path available (as expected)." << std::endl;
    }
}

void testAdvancedFeatures() {
    std::cout << "\n========= ADVANCED FEATURES TESTS =========" << std::endl;
    
    // Test 1: Diagonal movement
    std::cout << "\n--- Test 1: Diagonal Movement ---" << std::endl;
    WaveAlgorithm wave(5, 5);
    wave.setStart(0, 0);
    wave.setTarget(4, 4);
    wave.setObstacle(1, 1);
    wave.setObstacle(2, 1);
    wave.setObstacle(3, 1);
    
    wave.displayGrid();
    
    // Compare 4-directional vs 8-directional
    std::cout << "\n4-directional pathfinding:" << std::endl;
    if (wave.findPath()) {
        wave.displayGridWithPath();
        std::cout << "Distance: " << wave.getDistance() << std::endl;
    }
    
    std::cout << "\n8-directional pathfinding:" << std::endl;
    if (wave.findPathWithDiagonal()) {
        wave.displayGridWithPath();
        std::cout << "Distance: " << wave.getDistance() << std::endl;
    }
    
    // Test 2: Reachable cells
    std::cout << "\n--- Test 2: Reachable Cells Analysis ---" << std::endl;
    WaveAlgorithm reachable(6, 6);
    reachable.setStart(3, 3);
    reachable.setTarget(0, 0); // Dummy target
    reachable.setObstacle(2, 3);
    reachable.setObstacle(3, 2);
    
    if (reachable.findPath()) {
        std::vector<Point> cells = reachable.getReachableCells(3);
        std::cout << "Cells reachable within distance 3: " << cells.size() << std::endl;
        for (const Point& cell : cells) {
            std::cout << "(" << cell.x << "," << cell.y << ") ";
        }
        std::cout << std::endl;
        
        reachable.displayDistances();
    }
    
    // Test 3: Multiple start-target combinations
    std::cout << "\n--- Test 3: Dynamic Start-Target Pathfinding ---" << std::endl;
    WaveAlgorithm dynamic(4, 4);
    dynamic.setObstacle(1, 1);
    dynamic.setObstacle(2, 2);
    
    std::vector<Point> starts = {{0, 0}, {0, 3}, {3, 0}};
    std::vector<Point> targets = {{3, 3}, {3, 0}, {0, 3}};
    
    for (size_t i = 0; i < starts.size(); ++i) {
        std::cout << "\nPath from (" << starts[i].x << "," << starts[i].y 
                  << ") to (" << targets[i].x << "," << targets[i].y << "):" << std::endl;
        
        if (dynamic.findPath(starts[i], targets[i])) {
            std::cout << "Distance: " << dynamic.getDistance() << std::endl;
            auto path = dynamic.getPath();
            for (size_t j = 0; j < path.size(); ++j) {
                std::cout << "(" << path[j].x << "," << path[j].y << ")";
                if (j < path.size() - 1) std::cout << " -> ";
            }
            std::cout << std::endl;
        } else {
            std::cout << "No path found." << std::endl;
        }
    }
}

void testFileIO() {
    std::cout << "\n========= FILE I/O TESTS =========" << std::endl;
    
    // Create a test grid
    WaveAlgorithm wave(4, 5);
    wave.setStart(0, 0);
    wave.setTarget(3, 4);
    wave.setObstacle(1, 1);
    wave.setObstacle(1, 2);
    wave.setObstacle(2, 1);
    
    std::cout << "Original grid:" << std::endl;
    wave.displayGrid();
    
    // Save to file
    if (wave.saveToFile("test_grid.txt")) {
        std::cout << "\nGrid saved to test_grid.txt" << std::endl;
    } else {
        std::cout << "\nFailed to save grid" << std::endl;
        return;
    }
    
    // Load from file
    WaveAlgorithm loaded;
    if (loaded.loadFromFile("test_grid.txt")) {
        std::cout << "\nGrid loaded from test_grid.txt:" << std::endl;
        loaded.displayGrid();
        
        if (loaded.findPath()) {
            loaded.displayGridWithPath();
        }
    } else {
        std::cout << "\nFailed to load grid" << std::endl;
    }
}

void testGridGeneration() {
    std::cout << "\n========= GRID GENERATION TESTS =========" << std::endl;
    
    // Test 1: Random obstacles
    std::cout << "\n--- Test 1: Random Obstacle Generation ---" << std::endl;
    WaveAlgorithm random(8, 8);
    random.setStart(0, 0);
    random.setTarget(7, 7);
    
    std::cout << "Grid with 30% random obstacles:" << std::endl;
    random.generateRandomObstacles(0.3);
    random.displayGrid();
    
    if (random.findPath()) {
        std::cout << "\nPath found through random obstacles:" << std::endl;
        random.displayGridWithPath();
        std::cout << "Path length: " << random.getPath().size() << " steps" << std::endl;
        std::cout << "Distance: " << random.getDistance() << std::endl;
    } else {
        std::cout << "\nNo path found through obstacles." << std::endl;
    }
    
    // Test 2: Clear and regenerate
    std::cout << "\n--- Test 2: Grid Clearing and Regeneration ---" << std::endl;
    random.clearGrid();
    std::cout << "Grid after clearing:" << std::endl;
    random.displayGrid();
    
    random.generateRandomObstacles(0.15);
    std::cout << "\nGrid with 15% random obstacles:" << std::endl;
    random.displayGrid();
    
    if (random.findPath()) {
        random.displayGridWithPath();
    }
}

void performanceBenchmarks() {
    std::cout << "\n========= PERFORMANCE BENCHMARKS =========" << std::endl;
    WaveUtils::performanceBenchmark();
}

void demonstrateAlgorithm() {
    std::cout << "\n========= WAVE ALGORITHM DEMONSTRATION =========" << std::endl;
    std::cout << "This demonstrates how the wave algorithm works step by step." << std::endl;
    
    WaveAlgorithm demo(6, 6);
    demo.setStart(1, 1);
    demo.setTarget(4, 4);
    demo.setObstacle(2, 2);
    demo.setObstacle(2, 3);
    demo.setObstacle(3, 2);
    
    std::cout << "\nInitial grid:" << std::endl;
    demo.displayGrid();
    
    std::cout << "\nRunning wave algorithm..." << std::endl;
    if (demo.findPath()) {
        std::cout << "\nDistance map (shows wave propagation):" << std::endl;
        demo.displayDistances();
        
        std::cout << "\nShortest path found:" << std::endl;
        demo.displayPath();
        
        std::cout << "\nGrid with path marked:" << std::endl;
        demo.displayGridWithPath();
        
        std::cout << "\nAlgorithm explanation:" << std::endl;
        std::cout << "1. Start from the source cell with distance 0" << std::endl;
        std::cout << "2. Mark all reachable neighbors with distance 1" << std::endl;
        std::cout << "3. Continue propagating wave until target is reached" << std::endl;
        std::cout << "4. Reconstruct path by following decreasing distances" << std::endl;
        std::cout << "5. The algorithm guarantees the shortest path in unweighted grids" << std::endl;
    } else {
        std::cout << "No path exists!" << std::endl;
    }
}

void interactiveMode() {
    std::cout << "\n========= INTERACTIVE WAVE ALGORITHM MODE =========" << std::endl;
    
    int rows, cols;
    std::cout << "Enter grid size (rows cols): ";
    std::cin >> rows >> cols;
    std::cin.ignore();
    
    if (rows <= 0 || cols <= 0 || rows > 20 || cols > 20) {
        std::cout << "Invalid grid size. Using 5x5 default." << std::endl;
        rows = cols = 5;
    }
    
    WaveAlgorithm wave(rows, cols);
    
    while (true) {
        std::cout << "\n--- Current Grid ---" << std::endl;
        wave.displayGrid();
        
        std::cout << "\n--- Interactive Menu ---" << std::endl;
        std::cout << "1. Set Start Point" << std::endl;
        std::cout << "2. Set Target Point" << std::endl;
        std::cout << "3. Add Obstacle" << std::endl;
        std::cout << "4. Remove Obstacle" << std::endl;
        std::cout << "5. Find Path" << std::endl;
        std::cout << "6. Generate Random Obstacles" << std::endl;
        std::cout << "7. Clear Grid" << std::endl;
        std::cout << "8. Show Distance Map" << std::endl;
        std::cout << "9. Find Path with Diagonal Movement" << std::endl;
        std::cout << "0. Back to main menu" << std::endl;
        std::cout << "Choice: ";
        
        int choice;
        std::cin >> choice;
        std::cin.ignore();
        
        try {
            switch (choice) {
                case 1: {
                    int x, y;
                    std::cout << "Enter start position (x y): ";
                    std::cin >> x >> y;
                    std::cin.ignore();
                    wave.setStart(x, y);
                    std::cout << "Start set at (" << x << "," << y << ")" << std::endl;
                    break;
                }
                case 2: {
                    int x, y;
                    std::cout << "Enter target position (x y): ";
                    std::cin >> x >> y;
                    std::cin.ignore();
                    wave.setTarget(x, y);
                    std::cout << "Target set at (" << x << "," << y << ")" << std::endl;
                    break;
                }
                case 3: {
                    int x, y;
                    std::cout << "Enter obstacle position (x y): ";
                    std::cin >> x >> y;
                    std::cin.ignore();
                    wave.setObstacle(x, y);
                    std::cout << "Obstacle added at (" << x << "," << y << ")" << std::endl;
                    break;
                }
                case 4: {
                    int x, y;
                    std::cout << "Enter position to clear (x y): ";
                    std::cin >> x >> y;
                    std::cin.ignore();
                    wave.clearObstacle(x, y);
                    std::cout << "Obstacle removed from (" << x << "," << y << ")" << std::endl;
                    break;
                }
                case 5:
                    if (wave.findPath()) {
                        std::cout << "Path found!" << std::endl;
                        wave.displayPath();
                        wave.displayGridWithPath();
                    } else {
                        std::cout << "No path found!" << std::endl;
                    }
                    break;
                case 6: {
                    double ratio;
                    std::cout << "Enter obstacle ratio (0.0-1.0): ";
                    std::cin >> ratio;
                    std::cin.ignore();
                    wave.generateRandomObstacles(ratio);
                    std::cout << "Random obstacles generated." << std::endl;
                    break;
                }
                case 7:
                    wave.clearGrid();
                    std::cout << "Grid cleared." << std::endl;
                    break;
                case 8:
                    if (wave.hasPath()) {
                        wave.displayDistances();
                    } else {
                        std::cout << "No path calculated yet. Run 'Find Path' first." << std::endl;
                    }
                    break;
                case 9:
                    if (wave.findPathWithDiagonal()) {
                        std::cout << "Path found with diagonal movement!" << std::endl;
                        wave.displayPath();
                        wave.displayGridWithPath();
                    } else {
                        std::cout << "No path found!" << std::endl;
                    }
                    break;
                case 0:
                    return;
                default:
                    std::cout << "Invalid choice." << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
}