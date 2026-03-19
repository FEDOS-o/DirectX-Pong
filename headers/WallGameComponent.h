#include "Rect.h"
#include "GameComponent.h"

class WallComponent : public GameComponent {
private: 
	Rect bounds;

public:
	WallComponent(Game* game, Vector2 startPos) : GameComponent(game), bounds{ startPos, Vector2(900, 20) } {}
};