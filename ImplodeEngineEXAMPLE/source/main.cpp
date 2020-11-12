#include "pch.h"
#include "ImplodeEngine.h"
using namespace std;

int main()
{
	ImplodeEngine::Initialise();
	ImplodeEngine::GameLoop();
	ImplodeEngine::Exit();
	return 0;
}