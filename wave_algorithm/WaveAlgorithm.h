#pragma once
#include <vector>
#include <queue>
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <fstream>

// Point structure for coordinates
struct Point {
    int x, y;
    
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
    
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
    
    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
};

// Cell types for the grid
enum class CellType {
    EMPTY = 0,      // Passable cell
    OBSTACLE = -1,  // Blocked cell
    START = -2,     // Starting point
    TARGET = -3     // Target point
};

// Direction vectors for 4-directional movement
struct Direction {
    static const Point DIRECTIONS[4];
    static const std::string DIRECTION_NAMES[4];
    static const char DIRECTION_CHARS[4];
};

// Wave algorithm implementation
class WaveAlgorithm {
private:
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<CellType>> originalGrid;
    int rows, cols;
    Point start, target;
    bool pathFound;
    std::vector<Point> shortestPath;
    
    // Internal helper methods
    bool isValid(int x, int y) const;
    bool isPassable(int x, int y) const;
    void resetGrid();
    void reconstructPath();
    
public:
    // Constructors
    WaveAlgorithm();
    WaveAlgorithm(int rows, int cols);
    WaveAlgorithm(const std::vector<std::vector<CellType>>& initialGrid);
    
    // Copy constructor
    WaveAlgorithm(const WaveAlgorithm& other);
    
    // Move constructor
    WaveAlgorithm(WaveAlgorithm&& other) noexcept;
    
    // Copy assignment
    WaveAlgorithm& operator=(const WaveAlgorithm& other);
    
    // Move assignment
    WaveAlgorithm& operator=(WaveAlgorithm&& other) noexcept;
    
    // Destructor
    ~WaveAlgorithm() = default;
    
    // Grid manipulation
    void setGridSize(int rows, int cols);
    void setCell(int x, int y, CellType cellType);
    CellType getCell(int x, int y) const;
    void setObstacle(int x, int y);
    void clearObstacle(int x, int y);
    void setStart(int x, int y);
    void setTarget(int x, int y);
    
    // Wave algorithm execution
    bool findPath();
    bool findPath(const Point& start, const Point& target);
    
    // Path and distance queries
    std::vector<Point> getPath() const;
    int getDistance() const;
    int getDistance(int x, int y) const;
    bool hasPath() const;
    
    // Grid access
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    Point getStart() const { return start; }
    Point getTarget() const { return target; }
    
    // Visualization
    void displayGrid() const;
    void displayDistances() const;
    void displayPath() const;
    void displayGridWithPath() const;
    
    // File I/O
    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename) const;
    
    // Grid generation
    void generateRandomObstacles(double obstacleRatio);
    void generateMaze();
    void clearGrid();
    
    // Multiple path algorithms
    std::vector<std::vector<Point>> findAllPaths();
    std::vector<Point> findPathDFS();
    
    // Advanced features
    bool findPathWithDiagonal();  // 8-directional movement
    std::vector<Point> getReachableCells(int maxDistance) const;
    void floodFill(const Point& start, int maxDistance);
};

// Utility functions for wave algorithm
namespace WaveUtils {
    // Create predefined grids
    WaveAlgorithm createSimpleGrid();
    WaveAlgorithm createMazeGrid();
    WaveAlgorithm createLargeGrid();
    
    // Grid analysis
    double calculatePathEfficiency(const WaveAlgorithm& wave);
    std::vector<Point> getBottleneckPoints(const WaveAlgorithm& wave);
    
    // Path optimization
    std::vector<Point> smoothPath(const std::vector<Point>& path);
    
    // Visualization helpers
    void printGridWithColors(const WaveAlgorithm& wave);
    std::string gridToString(const WaveAlgorithm& wave);
    
    // Performance testing
    void performanceBenchmark();
}