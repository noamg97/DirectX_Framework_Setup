#include "Game.h"
#include "Framework.h"

//--------------------app instance handle code------------------not used any more-------------------cmd args-----------unnecessary---
int WINAPI WinMain(__in HINSTANCE instanceHandle, __in_opt HINSTANCE previousInstanceHandle, __in LPSTR lpCmdLine, __in int nShowCmd)
{
	// create an instace of our game object and pass it to the framework
	Framework frameWork(instanceHandle, new Game());


	// initialize, and exit if fails to initialize
	if(!frameWork.Initialize())
		return 1;

	// runs the program. Run() only ends when a Quit Message is sent, and returns the (quit) message.
	return frameWork.Run().wParam;
}