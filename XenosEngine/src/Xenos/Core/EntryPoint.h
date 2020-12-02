#pragma once

#ifdef  XENOS_PLATFORM_WINDOWS

//Create a new Application object
extern Xenos::Application* Xenos::CreateApplication();
	
int main(int args, char** argv)
{
	//Initialize the Logger
	Xenos::Log::Init();

	XS_PROFILE_BEGIN_SESSION("Startup", "XenosProfile-Startup.json");
	//Create a new Application object
	auto app = Xenos::CreateApplication();
	//Call the Run() Function on the application
	XS_PROFILE_END_SESSION();
	XS_PROFILE_BEGIN_SESSION("Startup", "XenosProfile-Runtime.json");
	app->Run();
	//Free application memory after Run() Function returns
	XS_PROFILE_END_SESSION();
	XS_PROFILE_BEGIN_SESSION("Startup", "XenosProfile-Shutdown.json");
	delete app;
	XS_PROFILE_END_SESSION();
}


#endif //  XENOS_PLATFORM_WINDOWS

