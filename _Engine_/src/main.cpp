//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Game.h"
#include "google\protobuf\message_lite.h"

Game* pGame = nullptr;

int CALLBACK WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	// Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	Test::RunTests();

	pGame = new Game("GAM 576 - MS1", 1200, 900);
	assert(pGame);

	pGame->Run();
	delete pGame;

	google::protobuf::ShutdownProtobufLibrary();


	return 0;
}

// ---  End of File ---
