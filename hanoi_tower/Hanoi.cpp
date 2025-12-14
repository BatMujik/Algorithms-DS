#include "Hanoi.h"
#include <utility>

void solveHanoiRecursive(int n, char from, char to, char aux, std::vector<Move>& moves) {
	if (n <= 0) return;
	solveHanoiRecursive(n - 1, from, aux, to, moves);
	moves.push_back({from, to});
	solveHanoiRecursive(n - 1, aux, to, from, moves);
}

std::vector<Move> solveHanoiRecursive(int n, char from, char to, char aux) {
	std::vector<Move> moves;
	solveHanoiRecursive(n, from, to, aux, moves);
	return moves;
}

std::vector<Move> solveHanoiIterative(int n, char from, char to, char aux) {
	std::vector<Move> moves;
	if (n <= 0) return moves;

	std::vector<char> pegs = {from, aux, to};
	auto indexOf = [&](char p){ for (int i=0;i<3;++i) if (pegs[i]==p) return i; return 0; };
	int src = indexOf(from), dst = indexOf(to), spare = indexOf(aux);
	auto pegName = [&](int i){ return pegs[i]; };

	int totalMoves = (1 << n) - 1;
	bool even = (n % 2 == 0);
	int a = src, b = even ? spare : dst, c = even ? dst : spare;

	for (int m = 1; m <= totalMoves; ++m) {
		if (m % 3 == 1) {
			moves.push_back({pegName(a), pegName(b)});
			std::swap(a,b);
		} else if (m % 3 == 2) {
			moves.push_back({pegName(a), pegName(c)});
			std::swap(a,c);
		} else {
			moves.push_back({pegName(b), pegName(c)});
			std::swap(b,c);
		}
	}
	return moves;
}

void printMoves(const std::vector<Move>& moves) {
	for (const auto& mv : moves) {
		std::cout << mv.from << " -> " << mv.to << '\n';
	}
	std::cout << "Total moves: " << moves.size() << '\n';
}
