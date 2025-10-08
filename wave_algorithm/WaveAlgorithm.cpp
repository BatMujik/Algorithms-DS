#include "WaveAlgorithm.h"
#include <algorithm>
#include <stack>
#include <random>
#include <chrono>

// Direction vectors (right, down, left, up)
const Point Direction::DIRECTIONS[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
const std::string Direction::DIRECTION_NAMES[4] = {"RIGHT", "DOWN", "LEFT", "UP"};
const char Direction::DIRECTION_CHARS[4] = {'→', '↓', '←', '↑'};

// Constructors
WaveAlgorithm::WaveAlgorithm() : rows(0), cols(0), pathFound(false) {
    std::cout << "WaveAlgorithm default constructor called" << std::endl;
}

WaveAlgorithm::WaveAlgorithm(int rows, int cols) 
    : rows(rows), cols(cols), pathFound(false), start(-1, -1), target(-1, -1) {
    grid.resize(rows, std::vector<int>(cols, 0));
    originalGrid.resize(rows, std::vector<CellType>(cols, CellType::EMPTY));
    std::cout << "WaveAlgorithm constructor called with size " << rows << "x" << cols << std::endl;
}

WaveAlgorithm::WaveAlgorithm(const std::vector<std::vector<CellType>>& initialGrid) 
    : pathFound(false), start(-1, -1), target(-1, -1) {
    rows = static_cast<int>(initialGrid.size());
    cols = (rows > 0) ? static_cast<int>(initialGrid[0].size()) : 0;
    
    grid.resize(rows, std::vector<int>(cols, 0));
    originalGrid = initialGrid;
    
    // Find start and target points
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (originalGrid[i][j] == CellType::START) {
                start = Point(i, j);
            } else if (originalGrid[i][j] == CellType::TARGET) {
                target = Point(i, j);
            }
        }
    }
    
    std::cout << "WaveAlgorithm constructor called with initial grid" << std::endl;
}

// Copy constructor
WaveAlgorithm::WaveAlgorithm(const WaveAlgorithm& other) 
    : grid(other.grid), originalGrid(other.originalGrid), rows(other.rows), cols(other.cols),
      start(other.start), target(other.target), pathFound(other.pathFound), 
      shortestPath(other.shortestPath) {
    std::cout << "WaveAlgorithm copy constructor called" << std::endl;
}

// Move constructor
WaveAlgorithm::WaveAlgorithm(WaveAlgorithm&& other) noexcept
    : grid(std::move(other.grid)), originalGrid(std::move(other.originalGrid)),
      rows(other.rows), cols(other.cols), start(other.start), target(other.target),
      pathFound(other.pathFound), shortestPath(std::move(other.shortestPath)) {
    other.rows = 0;
    other.cols = 0;
    other.pathFound = false;
    std::cout << "WaveAlgorithm move constructor called" << std::endl;
}

// Copy assignment
WaveAlgorithm& WaveAlgorithm::operator=(const WaveAlgorithm& other) {
    if (this != &other) {
        grid = other.grid;
        originalGrid = other.originalGrid;
        rows = other.rows;
        cols = other.cols;
        start = other.start;
        target = other.target;
        pathFound = other.pathFound;
        shortestPath = other.shortestPath;
        std::cout << "WaveAlgorithm copy assignment called" << std::endl;
    }
    return *this;
}

// Move assignment
WaveAlgorithm& WaveAlgorithm::operator=(WaveAlgorithm&& other) noexcept {
    if (this != &other) {
        grid = std::move(other.grid);
        originalGrid = std::move(other.originalGrid);
        rows = other.rows;
        cols = other.cols;
        start = other.start;
        target = other.target;
        pathFound = other.pathFound;
        shortestPath = std::move(other.shortestPath);
        
        other.rows = 0;
        other.cols = 0;
        other.pathFound = false;
        std::cout << "WaveAlgorithm move assignment called" << std::endl;
    }
    return *this;
}

// Helper methods
bool WaveAlgorithm::isValid(int x, int y) const {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

bool WaveAlgorithm::isPassable(int x, int y) const {
    if (!isValid(x, y)) return false;
    return originalGrid[x][y] != CellType::OBSTACLE;
}

void WaveAlgorithm::resetGrid() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = (originalGrid[i][j] == CellType::OBSTACLE) ? -1 : 0;
        }
    }
    pathFound = false;
    shortestPath.clear();
}

// Grid manipulation
void WaveAlgorithm::setGridSize(int newRows, int newCols) {
    rows = newRows;
    cols = newCols;
    grid.assign(rows, std::vector<int>(cols, 0));
    originalGrid.assign(rows, std::vector<CellType>(cols, CellType::EMPTY));
    pathFound = false;
    shortestPath.clear();
}

void WaveAlgorithm::setCell(int x, int y, CellType cellType) {
    if (!isValid(x, y)) return;
    
    originalGrid[x][y] = cellType;
    
    if (cellType == CellType::START) {
        start = Point(x, y);
    } else if (cellType == CellType::TARGET) {
        target = Point(x, y);
    }
}

CellType WaveAlgorithm::getCell(int x, int y) const {
    if (!isValid(x, y)) return CellType::OBSTACLE;
    return originalGrid[x][y];
}

void WaveAlgorithm::setObstacle(int x, int y) {
    setCell(x, y, CellType::OBSTACLE);
}

void WaveAlgorithm::clearObstacle(int x, int y) {
    setCell(x, y, CellType::EMPTY);
}

void WaveAlgorithm::setStart(int x, int y) {
    setCell(x, y, CellType::START);
}

void WaveAlgorithm::setTarget(int x, int y) {
    setCell(x, y, CellType::TARGET);
}

// Wave algorithm implementation
bool WaveAlgorithm::findPath() {
    if (start.x == -1 || target.x == -1) {
        std::cout << "Start or target not set!" << std::endl;
        return false;
    }
    
    return findPath(start, target);
}

bool WaveAlgorithm::findPath(const Point& startPoint, const Point& targetPoint) {
    if (!isValid(startPoint.x, startPoint.y) || !isValid(targetPoint.x, targetPoint.y)) {
        return false;
    }
    
    if (!isPassable(startPoint.x, startPoint.y) || !isPassable(targetPoint.x, targetPoint.y)) {
        return false;
    }
    
    resetGrid();
    
    std::queue<Point> queue;
    queue.push(startPoint);
    grid[startPoint.x][startPoint.y] = 1;
    
    while (!queue.empty()) {
        Point current = queue.front();
        queue.pop();
        
        // Check if we reached the target
        if (current == targetPoint) {
            pathFound = true;
            reconstructPath();
            return true;
        }
        
        // Explore all 4 directions
        for (const Point& dir : Direction::DIRECTIONS) {
            int newX = current.x + dir.x;
            int newY = current.y + dir.y;
            
            if (isPassable(newX, newY) && grid[newX][newY] == 0) {
                grid[newX][newY] = grid[current.x][current.y] + 1;
                queue.push(Point(newX, newY));
            }
        }
    }
    
    pathFound = false;
    return false;
}

void WaveAlgorithm::reconstructPath() {
    shortestPath.clear();
    
    if (!pathFound) return;
    
    Point current = target;
    shortestPath.push_back(current);
    
    while (!(current == start)) {
        int currentDistance = grid[current.x][current.y];
        bool found = false;
        
        // Look for a neighbor with distance currentDistance - 1
        for (const Point& dir : Direction::DIRECTIONS) {
            int newX = current.x + dir.x;
            int newY = current.y + dir.y;
            
            if (isValid(newX, newY) && grid[newX][newY] == currentDistance - 1) {
                current = Point(newX, newY);
                shortestPath.push_back(current);
                found = true;
                break;
            }
        }
        
        if (!found) {
            std::cout << "Error: Could not reconstruct path!" << std::endl;
            shortestPath.clear();
            return;
        }
    }
    
    // Reverse to get path from start to target
    std::reverse(shortestPath.begin(), shortestPath.end());
}

// Path and distance queries
std::vector<Point> WaveAlgorithm::getPath() const {
    return shortestPath;
}

int WaveAlgorithm::getDistance() const {
    if (!pathFound || target.x == -1) return -1;
    return grid[target.x][target.y] - 1; // Subtract 1 because we start counting from 1
}

int WaveAlgorithm::getDistance(int x, int y) const {
    if (!isValid(x, y) || grid[x][y] <= 0) return -1;
    return grid[x][y] - 1;
}

bool WaveAlgorithm::hasPath() const {
    return pathFound;
}

// Visualization
void WaveAlgorithm::displayGrid() const {
    std::cout << "\n=== Original Grid ===" << std::endl;
    std::cout << "Legend: . = Empty, # = Obstacle, S = Start, T = Target" << std::endl;
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            switch (originalGrid[i][j]) {
                case CellType::EMPTY: std::cout << ". "; break;
                case CellType::OBSTACLE: std::cout << "# "; break;
                case CellType::START: std::cout << "S "; break;
                case CellType::TARGET: std::cout << "T "; break;
            }
        }
        std::cout << std::endl;
    }
}

void WaveAlgorithm::displayDistances() const {
    std::cout << "\n=== Distance Grid ===" << std::endl;
    std::cout << "Numbers show distance from start, -1 = obstacle, 0 = unreachable" << std::endl;
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (originalGrid[i][j] == CellType::OBSTACLE) {
                std::cout << std::setw(3) << "#";
            } else if (grid[i][j] == 0) {
                std::cout << std::setw(3) << ".";
            } else {
                std::cout << std::setw(3) << (grid[i][j] - 1);
            }
        }
        std::cout << std::endl;
    }
}

void WaveAlgorithm::displayPath() const {
    if (!pathFound) {
        std::cout << "No path found!" << std::endl;
        return;
    }
    
    std::cout << "\n=== Shortest Path ===" << std::endl;
    std::cout << "Path length: " << shortestPath.size() << " steps" << std::endl;
    std::cout << "Distance: " << getDistance() << std::endl;
    
    for (size_t i = 0; i < shortestPath.size(); ++i) {
        std::cout << "(" << shortestPath[i].x << "," << shortestPath[i].y << ")";
        if (i < shortestPath.size() - 1) std::cout << " -> ";
    }
    std::cout << std::endl;
}

void WaveAlgorithm::displayGridWithPath() const {
    std::cout << "\n=== Grid with Path ===" << std::endl;
    std::cout << "Legend: . = Empty, # = Obstacle, S = Start, T = Target, * = Path" << std::endl;
    
    // Create a copy of the original grid to mark the path
    std::vector<std::vector<char>> display(rows, std::vector<char>(cols));
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            switch (originalGrid[i][j]) {
                case CellType::EMPTY: display[i][j] = '.'; break;
                case CellType::OBSTACLE: display[i][j] = '#'; break;
                case CellType::START: display[i][j] = 'S'; break;
                case CellType::TARGET: display[i][j] = 'T'; break;
            }
        }
    }
    
    // Mark the path (excluding start and target)
    if (pathFound) {
        for (size_t i = 1; i < shortestPath.size() - 1; ++i) {
            display[shortestPath[i].x][shortestPath[i].y] = '*';
        }
    }
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << display[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// File I/O
bool WaveAlgorithm::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file " << filename << std::endl;
        return false;
    }
    
    file >> rows >> cols;
    if (rows <= 0 || cols <= 0) {
        std::cout << "Error: Invalid grid dimensions" << std::endl;
        return false;
    }
    
    grid.assign(rows, std::vector<int>(cols, 0));
    originalGrid.assign(rows, std::vector<CellType>(cols, CellType::EMPTY));
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int cellValue;
            file >> cellValue;
            
            switch (cellValue) {
                case 0: originalGrid[i][j] = CellType::EMPTY; break;
                case -1: originalGrid[i][j] = CellType::OBSTACLE; break;
                case -2: 
                    originalGrid[i][j] = CellType::START;
                    start = Point(i, j);
                    break;
                case -3:
                    originalGrid[i][j] = CellType::TARGET;
                    target = Point(i, j);
                    break;
                default:
                    originalGrid[i][j] = CellType::EMPTY;
            }
        }
    }
    
    file.close();
    pathFound = false;
    shortestPath.clear();
    return true;
}

bool WaveAlgorithm::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not create file " << filename << std::endl;
        return false;
    }
    
    file << rows << " " << cols << std::endl;
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file << static_cast<int>(originalGrid[i][j]) << " ";
        }
        file << std::endl;
    }
    
    file.close();
    return true;
}

// Grid generation
void WaveAlgorithm::generateRandomObstacles(double obstacleRatio) {
    if (obstacleRatio < 0.0 || obstacleRatio > 1.0) {
        std::cout << "Error: Obstacle ratio must be between 0.0 and 1.0" << std::endl;
        return;
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (originalGrid[i][j] != CellType::START && originalGrid[i][j] != CellType::TARGET) {
                if (dis(gen) < obstacleRatio) {
                    originalGrid[i][j] = CellType::OBSTACLE;
                } else {
                    originalGrid[i][j] = CellType::EMPTY;
                }
            }
        }
    }
    
    pathFound = false;
    shortestPath.clear();
}

void WaveAlgorithm::clearGrid() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (originalGrid[i][j] != CellType::START && originalGrid[i][j] != CellType::TARGET) {
                originalGrid[i][j] = CellType::EMPTY;
            }
        }
    }
    pathFound = false;
    shortestPath.clear();
}

// Advanced pathfinding with diagonal movement
bool WaveAlgorithm::findPathWithDiagonal() {
    if (start.x == -1 || target.x == -1) {
        std::cout << "Start or target not set!" << std::endl;
        return false;
    }
    
    resetGrid();
    
    // 8-directional movement (including diagonals)
    const Point directions[8] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},           {0, 1},
        {1, -1},  {1, 0},  {1, 1}
    };
    
    std::queue<Point> queue;
    queue.push(start);
    grid[start.x][start.y] = 1;
    
    while (!queue.empty()) {
        Point current = queue.front();
        queue.pop();
        
        if (current == target) {
            pathFound = true;
            reconstructPath();
            return true;
        }
        
        for (const Point& dir : directions) {
            int newX = current.x + dir.x;
            int newY = current.y + dir.y;
            
            if (isPassable(newX, newY) && grid[newX][newY] == 0) {
                grid[newX][newY] = grid[current.x][current.y] + 1;
                queue.push(Point(newX, newY));
            }
        }
    }
    
    pathFound = false;
    return false;
}

// Get all reachable cells within a distance
std::vector<Point> WaveAlgorithm::getReachableCells(int maxDistance) const {
    std::vector<Point> reachable;
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int distance = getDistance(i, j);
            if (distance >= 0 && distance <= maxDistance) {
                reachable.emplace_back(i, j);
            }
        }
    }
    
    return reachable;
}

// Utility functions
namespace WaveUtils {
    WaveAlgorithm createSimpleGrid() {
        WaveAlgorithm wave(5, 5);
        wave.setStart(0, 0);
        wave.setTarget(4, 4);
        wave.setObstacle(2, 2);
        wave.setObstacle(2, 3);
        return wave;
    }
    
    WaveAlgorithm createMazeGrid() {
        std::vector<std::vector<CellType>> maze = {
            {CellType::START, CellType::OBSTACLE, CellType::EMPTY, CellType::EMPTY, CellType::EMPTY},
            {CellType::EMPTY, CellType::OBSTACLE, CellType::EMPTY, CellType::OBSTACLE, CellType::EMPTY},
            {CellType::EMPTY, CellType::EMPTY, CellType::EMPTY, CellType::OBSTACLE, CellType::EMPTY},
            {CellType::OBSTACLE, CellType::OBSTACLE, CellType::EMPTY, CellType::EMPTY, CellType::EMPTY},
            {CellType::EMPTY, CellType::EMPTY, CellType::EMPTY, CellType::OBSTACLE, CellType::TARGET}
        };
        return WaveAlgorithm(maze);
    }
    
    void performanceBenchmark() {
        std::cout << "\n=== WAVE ALGORITHM PERFORMANCE BENCHMARK ===" << std::endl;
        
        std::vector<int> sizes = {10, 20, 50, 100};
        
        for (int size : sizes) {
            WaveAlgorithm wave(size, size);
            wave.setStart(0, 0);
            wave.setTarget(size - 1, size - 1);
            wave.generateRandomObstacles(0.3);
            
            auto start = std::chrono::high_resolution_clock::now();
            bool found = wave.findPath();
            auto end = std::chrono::high_resolution_clock::now();
            
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            
            std::cout << "Grid " << size << "x" << size << ": ";
            std::cout << duration.count() << " μs, ";
            std::cout << "Path " << (found ? "found" : "not found");
            if (found) {
                std::cout << " (distance: " << wave.getDistance() << ")";
            }
            std::cout << std::endl;
        }
    }
}