#pragma once

#ifdef KALUO_PLATFORM_WINDOWS

//create engine application 

extern KaluoEngine::Application* KaluoEngine::CreateApplication();

int main(int argc, char** argv)
{
	KaluoEngine::Log::Init();
	KALUO_CORE_WARN("Enigne Log Initialized!");
	//KaluoEngine::Log::GetCoreLogger()->warn("Initialized Engine Log!");
	int a = 5;
	KALUO_INFO("Client Log Initialized! Test Var = {0}", a);
	//KaluoEngine::Log::GetClientLogger()->info("Initialized Client Log!");

	//create application by calling application's create application and it defined by the client
	printf("Kaluo Engine constructing...\n");
	auto App = KaluoEngine::CreateApplication();
	App->Run();
	delete App;
}

#endif