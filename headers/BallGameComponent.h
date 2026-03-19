#include "Rect.h"
#include "GameComponent.h"
#include "PaddleGameComponent.h"


class BallGameComponent : public GameComponent {
private:
	Rect bounds;
	Vector2 velocity;
	float speed;

	PaddleGameComponent* leftPaddle;
	PaddleGameComponent* rightPaddle;

	void PaddleCollision(PaddleGameComponent* paddle, int direction) {
		if (!paddle || !bounds.Intersects(paddle->GetBounds())) {
			return;
		}
		//!!!!
		velocity.x = direction * abs(velocity.x);  

		float hitPos = (bounds.position.y - paddle->GetBounds().position.y) /
			(paddle->GetBounds().size.y / 2);
		velocity.y = hitPos * 300.0f;
		
	}

public:
	BallGameComponent(Game* game, Vector2 startPos, PaddleGameComponent* leftPaddle, PaddleGameComponent* rightPaddle) :
		GameComponent(game),
		bounds{ startPos, Vector2(20.0f, 20.0f) },
		velocity(300.0f, 200.0f),
		speed(400.0f),
		leftPaddle(leftPaddle),
		rightPaddle(rightPaddle) {}

	void Update(float deltaTime) override {
		bounds.position.x += velocity.x * deltaTime;
		bounds.position.y += velocity.y * deltaTime;

		if (bounds.Top() < -400.0f || bounds.Bottom() > 400.0f) {
			velocity.y *= -1;
		}

		PaddleCollision(leftPaddle, 1);
		PaddleCollision(rightPaddle, -1);


		if (bounds.Right() > 450.0f) {
			std::cout << "Ãîë ëåâîìó!\n" << std::endl;
			ResetBall(1);  // ëåòèò âëåâî
		}
		if (bounds.Left() < -450.0f) {
			std::cout << "Ãîë ïðàâîìó!\n" << std::endl;
			ResetBall(-1);  // ëåòèò âïðàâî
		}
	}

	void ResetBall(int direction) {
		bounds.position = Vector2(0, 0);
		velocity = Vector2(direction * speed, (rand() % 400 - 200.0f));
	}

	Rect GetBounds() const { return bounds; }
};