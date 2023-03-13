#pragma once

// Namespace debe estar definido antes de usarse xd
namespace Powder {
	enum class Type {
		Empty,
		Ground,
		Ceiling,
		Wall,
		Sand,
		Water,
		Rock
	};
}

namespace Globals {
	extern int WindowWidth;
	extern int WindowHeight;
	extern int GroundLevel;

	extern int TickRate;
	extern int Scale;
	extern int bSize;
	extern Powder::Type SelectedMaterial;
}


