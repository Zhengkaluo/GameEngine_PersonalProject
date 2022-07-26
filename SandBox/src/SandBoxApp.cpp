
//#include "../KaluoEngine/KaluoEngine.h"
#include <KaluoEngine.h>
#include <stdio.h>
class Sandbox : public KaluoEngine::Application
{
public:
	Sandbox()
	{
		//std::("constructing sandbox...");
	}

	~Sandbox()
	{

	}
};

//int main() 
//{
//	Sandbox* NewSandBox = new Sandbox();
//	NewSandBox->Run();
//	delete NewSandBox;
//}

//return new sandbox when application is needed to be created
KaluoEngine::Application* KaluoEngine::CreateApplication()
{
	return new Sandbox();
}