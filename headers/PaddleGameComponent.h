#include "Rect.h"
#include "GameComponent.h"

class PaddleGameComponent : public GameComponent {

private:
	Rect bounds;
	float speed;
	Keys upKey;
	Keys downKey;
	float minY;
	float maxY;

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;

public:
	PaddleGameComponent(Game* game, Vector2 startPos, Keys upKey, Keys downKey, float minY = -350.0f, float maxY = -350.0f) :
		GameComponent(game),
		bounds{ startPos, Vector2(20.0f, 100.0f) },
		speed(500.0f),
		upKey(upKey),
		downKey(downKey),
		minY(minY),
		maxY(maxY) {}

	void Update(float deltaTime) override {
		if (game->Input->IsKeyDown(upKey)) {
			bounds.position.y -= speed * deltaTime;
		}

		if (game->Input->IsKeyDown(downKey)) {
			bounds.position.y += speed * deltaTime;
		}


		float halfHeight = bounds.size.y / 2;
		if (bounds.position.y - halfHeight < minY) {
			bounds.position.y = minY + halfHeight;
		}
		if (bounds.position.y + halfHeight > maxY) {
			bounds.position.y = maxY - halfHeight;
		}
	}

	Rect GetBounds() const {
		return bounds;
	}
};