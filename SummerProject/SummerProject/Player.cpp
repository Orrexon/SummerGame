//PLayer.cpp

#include <iostream>
#include "GameObject.h"
#include "Player.h"
#include "BoxCollider.h"
#include "CircleCollider.h"


Player::Player(Collider* collider, sf::Vector2f position, InputManager* input,
	CollisionManager* collisionmgr, GameObjectManager* gameobjmgr)
: m_animatedSprite(nullptr)
{
	m_boxCollider = dynamic_cast<BoxCollider*>(collider);
	m_boxCollider->setParent(this);
	m_position = position;
	m_inputMgr = input;
	m_collMgr = collisionmgr;
	m_gameObjMgr = gameobjmgr;
	m_type = "Player";
	m_velocity = { 0.f, 0.f };
	onGround = false;
	m_dead = false;
	bLeft = false;
	bRight = false;
}
Player::~Player()
{
	if (m_animatedSprite != nullptr)
	{
		delete m_animatedSprite;
		m_animatedSprite = nullptr;
	}
	std::map<std::string, Animation*>::iterator it = m_animations.begin();
	while (it != m_animations.end())
	{
		if (it->second != nullptr)
		{
			delete it->second;
			it->second = nullptr;
		}
		it++;
	}
	m_animations.clear();
}

void Player::initTestbody()
{
	TestBodyRect.setSize(m_boxCollider->GetExtention());
	TestBodyRect.setFillColor(sf::Color::Blue);
	TestBodyRect.setPosition(m_position);
	TestBodyRect.setOrigin(m_boxCollider->GetExtention() / 2.f);
}

void Player::initAnimation()
{
	m_spriteSheet = new sf::Texture;
	if(!m_spriteSheet->loadFromFile("../data/sprites/hero_spritesheet.png")) printf("Player::initAnimation() somethings wrong\n");
	//Idle animation
	Animation* m_animator_idle = new Animation;
	m_animator_idle->setSpriteSheet(*m_spriteSheet);
	m_animator_idle->addFrame(sf::IntRect(0, 18, 80, 66));
	m_animator_idle->addFrame(sf::IntRect(80, 18, 80, 66));
	m_animator_idle->addFrame(sf::IntRect(160, 18, 80, 66));
	m_animator_idle->addFrame(sf::IntRect(240, 18, 80, 66));
	m_animator_idle->addFrame(sf::IntRect(320, 18, 80, 66));
	m_animator_idle->addFrame(sf::IntRect(400, 18, 80, 66));
	m_animator_idle->addFrame(sf::IntRect(480, 18, 80, 66));
	insertAnimation("idle", m_animator_idle);
	//walking animation
	Animation* m_animation_walking = new Animation;
	m_animation_walking->setSpriteSheet(*m_spriteSheet);
	m_animation_walking->addFrame(sf::IntRect(0, 115, 80, 66));
	m_animation_walking->addFrame(sf::IntRect(80, 115, 80, 66));
	m_animation_walking->addFrame(sf::IntRect(160, 115, 80, 66));
	m_animation_walking->addFrame(sf::IntRect(240, 115, 80, 66));
	m_animation_walking->addFrame(sf::IntRect(320, 115, 80, 66));
	m_animation_walking->addFrame(sf::IntRect(400, 115, 80, 66));
	insertAnimation("walking", m_animation_walking);
	//shoot/aim
	Animation* m_animation_shooting = new Animation;
	m_animation_shooting->addFrame(sf::IntRect(0, 210, 80, 66));
	m_animation_shooting->addFrame(sf::IntRect(80, 210, 80, 66));
	m_animation_shooting->addFrame(sf::IntRect(160, 210, 80, 66));
	m_animation_shooting->addFrame(sf::IntRect(240, 210, 80, 66));
	m_animation_shooting->addFrame(sf::IntRect(320, 210, 80, 66));
	m_animation_shooting->addFrame(sf::IntRect(400, 210, 80, 66));
	insertAnimation("shooting", m_animation_shooting);
	//jump
	Animation* m_animation_jump = new Animation;
	m_animation_jump->addFrame(sf::IntRect(0, 298, 80, 66));
	m_animation_jump->addFrame(sf::IntRect(80, 298, 80, 66));
	m_animation_jump->addFrame(sf::IntRect(160, 298, 80, 66));
	m_animation_jump->addFrame(sf::IntRect(80, 298, 80, 66));
	insertAnimation("jump", m_animation_jump);
	//die need to check coordinates
	Animation* m_animation_die = new Animation;
	m_animation_die->addFrame(sf::IntRect(240, 298, 80, 66));
	m_animation_die->addFrame(sf::IntRect(320, 298, 80, 66));
	m_animation_die->addFrame(sf::IntRect(400, 298, 80, 66));
	m_animation_die->addFrame(sf::IntRect(500, 298, 80, 66));
	insertAnimation("die", m_animation_die);
	//Duck (not the animal)
	Animation* m_animation_duck = new Animation;
	m_animation_duck->addFrame(sf::IntRect(0, 396, 80, 56));
	m_animation_duck->addFrame(sf::IntRect(80, 396, 80, 56));
	m_animation_duck->addFrame(sf::IntRect(160, 396, 80, 56));
	insertAnimation("duck", m_animation_duck);

	m_animatedSprite = (new AnimatedSprite(sf::seconds(0.2), true, true));
	m_animatedSprite->setPosition(400, 400);
	m_animatedSprite->setAnimation(*getAnimation("idle"));
}

void Player::update(float deltatime)
{
	const sf::Vector2f gravity = { 0.f, 9.8f };
	const sf::Vector2f vRight= { 1.f, 1.f };
	const sf::Vector2f vLeft = { -1.f, 1.f };
	handleInput(deltatime, gravity);
	scaleSprite(vLeft, vRight);
	if (m_eAnimationType == WALKING)
	{
		m_animatedSprite->play(*getAnimation("walking"));
	}
	if (!onGround)
	{
		m_velocity.y += deltatime * gravity.y;
	}
	m_position += m_velocity;
	m_boxCollider->SetPosition(m_position);
	TestBodyRect.setPosition(m_position);
	m_animatedSprite->setPosition(m_position);
	m_animatedSprite->setOrigin(m_animatedSprite->getLocalBounds().width / 2, m_animatedSprite->getLocalBounds().height / 2);
	
	m_eAnimationType = IDLE;
	m_velocity *= 0.9f;
	onGround = false;
	bRight = false;
	bLeft = false;
}

void Player::handleInput(float deltatime, sf::Vector2f gravity)
{
	if (m_inputMgr->IsDown(sf::Keyboard::D))
	{
		m_velocity.x = deltatime*200.f;
		if (m_eAnimationType != WALKING)m_eAnimationType = WALKING;
		bRight = true;
	}
	if (m_inputMgr->IsReleased(sf::Keyboard::D))
	{
		m_animatedSprite->pause();
		m_animatedSprite->setAnimation(*getAnimation("idle"));
		m_animatedSprite->play();
	}
	if (m_inputMgr->IsDown(sf::Keyboard::A))
	{
		m_velocity.x = deltatime*-200.f;
		if (m_eAnimationType != WALKING)m_eAnimationType = WALKING;
		bLeft = true;
	}
	if (m_inputMgr->IsReleased(sf::Keyboard::A))
	{
		m_animatedSprite->pause();
		m_animatedSprite->setAnimation(*getAnimation("idle"));
		m_animatedSprite->play();
	}
	if (m_inputMgr->IsDown(sf::Keyboard::W))
	{
		m_velocity.y = deltatime*-200.f;
	}
	if (m_inputMgr->IsDown(sf::Keyboard::S))
	{
		m_velocity.y = deltatime*200.f;
	}
	if (m_inputMgr->IsDownOnce(sf::Keyboard::Space) && onGround)
	{
		m_velocity.y = -gravity.y;
		onGround = false;
	}
	if (m_inputMgr->IsDownOnce(sf::Keyboard::F))
	{
		shoot();
	}
}

void Player::scaleSprite(const sf::Vector2f vLeft, const sf::Vector2f vRight)
{
	if (bLeft)
	{
		if (m_animatedSprite->getScale().x > 0)
		{
			m_animatedSprite->setScale(vLeft);
		}
		bRight = false;
	}
	else if (bRight)
	{
		if (m_animatedSprite->getScale().x < 0)
		{
			m_animatedSprite->setScale(vRight);
		}
		bLeft = false;
	}
	
}

void Player::onCollision(GameObject* other)
{
	PlatformObject* platform = dynamic_cast<PlatformObject*>(other);
	if (platform != nullptr)
	{
		if (m_position.y  <= platform->getPosition().y )
		{
  			onGround = true;
		}
		m_position += m_boxCollider->getOffset();
	}
	
	//m_velocity *= 0.9f;
	//printf("Player::onCollision()\n")
}

void Player::shoot()
{
	sf::Vector2f bVel = { 3.f, 0.f };
	if (m_velocity.x < 0.f) bVel *= -1.f;
	CircleCollider* collider = new CircleCollider(m_position, 10.f);
	m_bullet = new Bullet(collider, m_position);
	m_bullet->setId(PLAYER_BULLET);
	m_bullet->setVelocity(bVel);
	m_bullet->InitTestBody();
	m_gameObjMgr->attach(m_bullet);
	m_collMgr->Attach(m_bullet->getCollider());
	
	//avoiding danglers,
	//actual objects are deleted elswhere from the std::vectors of the managers
	collider = nullptr;
	m_bullet = nullptr;
}

Animation* Player::getAnimation(std::string name)
{
	std::map<std::string, Animation*>::iterator it = m_animations.find(name);
	if (it == m_animations.end())
	{
		std::cout << "No such animation as: " << name << " available.\n Returning nullptr" << std::endl;
		return nullptr;
	}
	return it->second;
}

void Player::insertAnimation(std::string name, Animation* animation)
{
	std::pair<std::string, Animation*> Pair(name, animation);
	m_animations.insert(Pair);
}