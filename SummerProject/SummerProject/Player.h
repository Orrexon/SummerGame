//Player.h

#pragma once
#include "GameObject.h"
#include "PlatformObject.h"
#include "Bullet.h"
#include "InputManager.h"
#include "GameObjectManager.h"
#include "CollisionManager.h"
#include "Animation.h"
#include "AnimatedSprite.h"
class Player : public GameObject
{
public:
	Player(Collider* collider, sf::Vector2f position, InputManager* input);
	~Player();
	
	void update(float deltatime);

	void initTestbody();

	void initAnimation();

	void onCollision(GameObject* other);

	void shoot(GameObjectManager* gameObjMgr, CollisionManager* collMgr);

	Collider* getCollider() { return m_boxCollider; }
	sf::RectangleShape& GetRect() { return TestBodyRect; }
	bool isDead() { return m_dead; }
	Animation* getAnimator() { return m_animator; }
	AnimatedSprite* getAnimatedSprite() { return m_animatedSprite; }
private:
	InputManager* m_inputMgr;
	bool onGround;
	sf::Vector2f m_velocity;
	BoxCollider* m_boxCollider;
	Bullet* m_bullet;
	Animation* m_animator;
	AnimatedSprite* m_animatedSprite;
	sf::Texture* m_spriteSheet;
	sf::CircleShape TestBodyCircle;
	sf::RectangleShape TestBodyRect;
};