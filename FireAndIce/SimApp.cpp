#include "SimApp.h"
#include "Splendido.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

long t = 0;
SimApp * win = NULL;

int handleTime(void *)
{
	t++;
	win->tick(t);
	return TRUE;
}

double SimApp::s_secPerTick = 0.1;
double SimApp::s_metersPerPixel = 1.0;

SimApp::SimApp(int argc, char *argv[], string title, int w, int h) 
	: m_playground(), m_window(), m_app()
{
	srand(time(NULL));

  	m_app = Gtk::Application::create(argc, argv,
      "SimPack");

 	m_window.set_default_size(w, h);
 	m_window.set_title(title.c_str());
 
	cout << "Sim Window Created" << endl;

	m_window.add(m_playground);

	// units for x,y,w,h are in meters...
	for (int i = 0; i < 20; i++)//change i to 100
	{
		int x = rand() % w;
		int y = rand() % h;
		int vx = (rand() % 40) - 20;
		int vy = (rand() % 40) - 20;
		if (i > 10)//change to 50
		{
			m_playground.add(new Splendido(x, y, 30, 30, vx, vy, 
			true, m_playground));
		}
		else
		{
			m_playground.add(new Splendido(x, y, 30, 30, vx, vy, 
			false, m_playground));			
		}
	}
   	m_playground.show();
 	
 	win = this;
 	g_timeout_add(s_secPerTick*1000,handleTime,NULL);
 	
 	m_app->run(m_window);
}



