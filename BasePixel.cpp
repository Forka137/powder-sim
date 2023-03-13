#include "BasePixel.h"

BasePixel::~BasePixel() {
	// Debe tener un destructor virtual
	// O sino unique_ptr no podrá llamar al destructor de SandPixel y la memoria no se liberará
};

Vector2 BasePixel::GetPosition() {
	return _position;
}

Powder::Type BasePixel::GetType() {
	return _type;
}