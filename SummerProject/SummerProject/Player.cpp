//PLayer.cpp

#include "GameObject.h"
#include "Player.h"
#include "BoxCollider.h"
#include "CircleCollider.h"


Player::Player(Collider* collider, sf::Vector2f position, InputManager* input) : m_animatedSprite(nullptr)
{
	m_boxCollider = dynamic_cast<BoxCollider*>(collider);
	m_boxCollider->setParent(this);
	m_position = position;
	m_inputMgr = input;
	m_type = "Player";
	m_velocity = { 0.f, 0.f };
	onGround = false;
	m_dead = false;
	m_animator = new Animation;
}
Player::~Player()
{
	if (m_animatedSprite != nullptr)
	{
		delete m_animatedSprite;
		m_animatedSprite = nullptr;
	}
	if (m_animator != nullptr)
	{
		delete m_animator;
		m_animator = nullptr;
	}
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
	m_animator->setSpriteSheet(*m_spriteSheet);
	m_animator->addFrame(sf::IntRect(0, 18, 80, 66));
	m_animator->addFrame(sf::IntRect(80, 18, 80, 66));
	m_animator->addFrame(sf::IntRect(160, 18, 80, 66));
	m_animator->addFrame(sf::IntRect(240, 18, 80, 66));
	m_animator->addFrame(sf::IntRect(320, 18, 80, 66));
	m_animator->addFrame(sf::IntRect(400, 18, 80, 66));
	m_animator->addFrame(sf::IntRect(480, 18, 80, 66));
	m_animatedSprite = (new AnimatedSprite(sf::seconds(0.2), true, true));
	m_animatedSprite->setPosition(400, 400);
	m_animatedSprite->setAnimation(*m_animator);
}

void Player::update(float deltatime)
{
	const sf::Vector2f gravity = { 0.f, 9.8f };
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_velocity.x = deltatime*200.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_velocity.x = deltatime*-200.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_velocity.y = deltatime*-200.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_velocity.y = deltatime*200.f;
	}
	if (m_inputMgr->IsDownOnce(sf::Keyboard::Space) && onGround)
	{
		m_velocity.y = -gravity.y;
		onGround = false;
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
	m_velocity *= 0.9f;
	onGround = false;
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

void Player::shoot(GameObjectManager* gameObjMgr, CollisionManager* collMgr)
{
	sf::Vector2f bVel = { 3.f, 0.f };
	if (m_velocity.x < 0.f) bVel *= -1.f;
	CircleCollider* collider = new CircleCollider(m_position, 10.f);
	m_bullet = new Bullet(collider, m_position);
	m_bullet->setId(PLAYER_BULLET);
	m_bullet->setVelocity(bVel);
	m_bullet->InitTestBody();
	gameObjMgr->attach(m_bullet);
	collMgr->Attach(m_bullet->getCollider());
	
	//avoiding danglers,
	//actual objects are deleted elswhere from the std::vectors of the managers
	collider = nullptr;
	m_bullet = nullptr;
}