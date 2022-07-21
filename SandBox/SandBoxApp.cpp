
#include "../KaluoEngine/KaluoEngine.h"
#include <KaluoEngine.h>

class Sandbox : public KaluoEngine::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

int main() 
{
	Sandbox* NewSandBox = new Sandbox();
	NewSandBox->Run();
	delete NewSandBox;
}