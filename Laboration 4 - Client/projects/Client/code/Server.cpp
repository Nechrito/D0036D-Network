#include "config.h"
#include "Application.h"
#include "WinsockClient.h"

int main()
{
	Application app;
	WinsockClient client;

	if (app.Open())
	{
		app.Run();
		app.Close();
	}
	app.Exit();
}
