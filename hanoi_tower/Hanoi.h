#pragma once
#include <vector>
#include <string>
#include <iostream>

struct Move { char from; char to; };

void solveHanoiRecursive(int n, char from, char to, char aux, std::vector<Move>& moves);
std::vector<Move> solveHanoiRecursive(int n, char from = 'A', char to = 'C', char aux = 'B');
std::vector<Move> solveHanoiIterative(int n, char from = 'A', char to = 'C', char aux = 'B');
void printMoves(const std::vector<Move>& moves);
