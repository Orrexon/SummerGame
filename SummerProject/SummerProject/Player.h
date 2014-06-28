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

enum ANIMATION_TYPE
{
	IDLE,
	WALKING,
	SHOOTING,
	JUMPING,
	DUCKING,
	DYING
};
class Player : public GameObject
{
public:
	Player(Collider* collider, sf::Vector2f position, InputManager* input,
		CollisionManager* collisionmgr, GameObjectManager* gameobjmgr);
	~Player();
	
	void update(float deltatime);

	void handleInput(float deltatime, sf::Vector2f gravity);

	void scaleSprite(const sf::Vector2f, const sf::Vector2f);

	void initTestbody();

	void initAnimation();

	void onCollision(GameObject* other);

	void shoot();

	Collider* getCollider() { return m_boxCollider; }
	sf::RectangleShape& GetRect() { return TestBodyRect; }
	bool isDead() { return m_dead; }
	Animation* getAnimation(std::string);
	void insertAnimation(std::string name, Animation* animation);
	AnimatedSprite* getAnimatedSprite() { return m_animatedSprite; }
private:
	InputManager* m_inputMgr;
	CollisionManager* m_collMgr;
	GameObjectManager* m_gameObjMgr;
	bool onGround;
	sf::Vector2f m_velocity;
	BoxCollider* m_boxCollider;
	Bullet* m_bullet;
	std::map<std::string, Animation*> m_animations;
	AnimatedSprite* m_animatedSprite;
	sf::Texture* m_spriteSheet;
	bool bLeft, bRight;
	ANIMATION_TYPE m_eAnimationType;
	sf::CircleShape TestBodyCircle;
	sf::RectangleShape TestBodyRect;
};