#pragma once

#ifdef KALUO_PLATFORM_WINDOWS

//create engine application 

extern KaluoEngine::Application* KaluoEngine::CreateApplication();

int main(int argc, char** argv)
{
	//create application by calling application's create application and it defined by the client
	printf("Kaluo Engine constructing...\n");
	auto App = KaluoEngine::CreateApplication();
	App->Run();
	delete App;
}

#endif