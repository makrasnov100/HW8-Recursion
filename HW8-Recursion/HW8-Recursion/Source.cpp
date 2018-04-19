//Author: Kostiantyn Makrasnov
//HW-08 Recursion Gateway
#include <iostream>
#include "BinarySearch.cpp"
#include "EightQueensOne.cpp"
#include "EightQueensAll.cpp"


int main() {
	//Problem 1: Binary Search
	testBinarySearch();
	//Problem 2: Eight Queens One Solution
	testEightQueensOne();
	//Problem 3: Eight Queens All Solutions
	testEightQueensAll();
	//Problem 4: Binary Search
	//testSolvingMaze();
	return 0;
}