#include "config.h"
#include "Application.h"

int main()
{
	Application app;
	
	if (app.Open())
	{
		app.Run();
		app.Close();
	}
	app.Exit();
}
