#include "Cell.h"

Cell::Cell(int value) {
	Value = value;
	hasMerged = false;
}

Cell::~Cell()
{}

bool Cell::operator+(Cell& cellToMerge)
{
	if (Value != cellToMerge.Value) return false;
	if (hasMerged || cellToMerge.hasMerged) return false;

	Value *= 2;
	cellToMerge.Value = 0;
	return true;
}