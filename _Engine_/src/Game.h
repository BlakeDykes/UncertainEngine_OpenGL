//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef GAME_H
#define GAME_H

#include <math.h>
#include <vmath.h>   // ToDo get rid of the projection, move to the camera

#include "sb7.h"
#include "Engine.h"
#include "MathEngine.h"
#include "Scene.h"

class Game : public Engine
{
public:
	// constructor
	Game(const char* const windowName, const int Width, const int Height);
	Game(const Game &) = delete;
	Game &operator = (const Game &) = delete;
	Game(Game &&) = delete;
	Game &operator = (Game &&) = delete;
	~Game();

	void LoadScene(Uncertain::Scene* pScene);
	void UnloadScene();

private:
	virtual void Initialize() override;
	virtual void LoadContent() override;
	virtual void Update(float currentTime) override;
	virtual void Draw() override;
	virtual void UnLoadContent() override;
	virtual void ClearBufferFunc() override;

	virtual void onResize(int w, int h) override;

	Uncertain::Scene* poActiveScene;
};

#endif

// --- End of File ---

