// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <vector>

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>

class State;
class GameStateManager;
class CollisionManager;
class InputManager;
class SpriteManager;
class GameObjectManager;
class Level;
class View;
class Player;
class CircleCollider;
class Collider;

#include "GameStateManager.h"
#include "Core.h"
#include "CollisionManager.h"
#include "InputManager.h"
#include "GameObjectManager.h"
#include "SpriteManager.h"
#include "Level.h"
#include "View.h"
#include "State.h"
#include "StartState.h"
#include "GameState.h"
#include "State.h"


#include "Animation.h"
#include "AnimatedSprite.h"

#include "CircleCollider.h"
#include "Collider.h"
#include "BoxCollider.h"

#include "Bullet.h"
#include "Player.h"
#include "PlatformObject.h"
#include "SalesMan.h"
#include "GameObject.h"
#include "GraphFunctions.h"
#include "GraphAlgorithms.h"
#include "SparseGraph.h"
#include "NavGraphEdge.h"
#include "NavGraphNode.h"
#include "MathNerd.h"

// TODO: reference additional headers your program requires here
