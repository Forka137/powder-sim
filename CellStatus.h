#pragma once
#include "globals.h"

struct CellStatus {
	// Structs have constructors
	CellStatus() {}

	bool free = true;
	Powder::Type type = Powder::Type::Empty;
};

// Me acabo de dar cuenta que no necesito el bool free xd