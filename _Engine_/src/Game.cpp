//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "sb7.h"
#include "MathEngine.h"
#include "Game.h"
#include "Manager_Wrapper.h"

#include "Scene_MS3.h"
#include "Scene_Concert.h"

using namespace Uncertain;

//-----------------------------------------------------------------------------
//  Game::Game()
//		Game Engine Constructor
//-----------------------------------------------------------------------------
Game::Game(const char* const windowName, const int Width, const int Height)
	:Engine(windowName, Width, Height), poActiveScene(nullptr)
{
	assert(windowName);

}

//-----------------------------------------------------------------------------
//  Game::~Game()
//		Game Engine destructor
//-----------------------------------------------------------------------------
Game::~Game()
{
}

//-----------------------------------------------------------------------------
// Game::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void Game::Initialize()
{

}


//-----------------------------------------------------------------------------
// Game::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
void Game::LoadContent()
{
	ManagerWrapper::InitManagers(this);

	//this->LoadScene(new Scene_MS3());
	this->LoadScene(new Scene_Concert());
}

//-----------------------------------------------------------------------------
// Game::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------
_Time placeholderTime;


void Game::Update(float )
{
	this->poActiveScene->Update();

	InputManager::Update();
	CameraManager::Update();
	AnimManager::Update();
	ArmatureManager::Update();
	UIManager::Update();

	GameObjectManager::Update(placeholderTime);
}


//-----------------------------------------------------------------------------
// Game::Draw()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void Game::Draw()
{
	GameObjectManager::Draw();
}


//-----------------------------------------------------------------------------
// Game::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void Game::UnLoadContent()
{
	ManagerWrapper::DestroyManagers();
	UnloadScene();
}


//-----------------------------------------------------------------------------
// Game::ScreenResize()
//-----------------------------------------------------------------------------
void Game::onResize(int w, int h)
{
	Engine::onResize(w, h);
}


//------------------------------------------------------------------
// Game::ClearBufferFunc()
// Allows user to change the way the clear buffer function works
//------------------------------------------------------------------
void Game::ClearBufferFunc()
{
#ifdef _DEBUG
	const GLfloat color[] = { 0.428f, 0.416f, 0.650f, 1.0f };
#else
	const GLfloat color[] = { 0.95f, 0.7f, 0.7f, 1.0f };
#endif
	const GLfloat one = 1.0f;

	glViewport(0, 0, info.windowWidth, info.windowHeight);
	glClearBufferfv(GL_COLOR, 0, color);
	glClearBufferfv(GL_DEPTH, 0, &one);
}

void Game::LoadScene(Scene* pScene)
{
	if (this->poActiveScene)
	{
		poActiveScene->Unload();
		delete poActiveScene;
	}

	poActiveScene = pScene;
	poActiveScene->Load();
}

void Game::UnloadScene()
{
	if (this->poActiveScene)
	{
		poActiveScene->Unload();
		delete poActiveScene;
	}
}


// --- End of File ---
