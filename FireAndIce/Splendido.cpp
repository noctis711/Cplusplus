#include "Splendido.h"
#include "SimApp.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>

using namespace std;

Splendido::Splendido(double x, double y, double w, double h, 
    double vX, double vY, bool fire, ParticlePlayground& playground)
      : ParticleBase(x, y, w, h, fire), m_vX(vX), m_vY(vY), 
        m_win_w (0), m_win_h(0), m_red(0.8), m_green(0.0), m_blue(0.0),
         m_playground(playground) 
{
    m_fire=fire;
    
}

void Splendido::draw(int win_height, int win_width, 
  const Cairo::RefPtr<Cairo::Context>& cr)
{
    m_win_w = win_width;
    m_win_h = win_height;

    srand(time(NULL));

    double xpix = getX() / SimApp::getMetersPerPixel();
    double ypix = getY() / SimApp::getMetersPerPixel();
    double wpix = getW() / SimApp::getMetersPerPixel();
    double hpix = getH() / SimApp::getMetersPerPixel();

    cr->save();

    cr->set_line_width(1.0);
    /*cr->set_source_rgba(m_red, m_green, m_blue, 0.6);
    cr->arc(xpix, ypix, wpix / 2.0, 0.0, 2.0 * M_PI);
    cr->fill_preserve();*/
    if(m_fire){
        Gdk::Cairo::set_source_pixbuf(cr,fireImage,xpix,ypix);
        cr->rectangle(xpix,ypix,fireImage->get_width(),fireImage->get_height());    
    }
    else{
        Gdk::Cairo::set_source_pixbuf(cr,iceImage,xpix,ypix);
        cr->rectangle(xpix,ypix,iceImage->get_width(),iceImage->get_height());
    }
    
    cr->fill();
    cr->stroke();

    cr->restore();
}

void Splendido::tick(long t)
{
    ParticleBase * closest = findClosest();
    if (closest != NULL && getCollision()==true)
    {

        //cout << "collision " << t << endl;
    }

	double deltaX = ((getVX() / SimApp::getMetersPerPixel()) * SimApp::getSecPerTick());
	double deltaY = ((getVY() / SimApp::getMetersPerPixel()) * SimApp::getSecPerTick());

    int r = rand() % 10;
    if( r == 5){
        double angle = atan(getY()/getX());
        double incX = (((getVX() / SimApp::getMetersPerPixel()) * SimApp::getSecPerTick())+1)*cos(angle);
        double incY = (((getVY() / SimApp::getMetersPerPixel()) * SimApp::getSecPerTick())+1)*sin(angle);
        setX(getX() + deltaX + incX);
        setY(getY() + deltaY + incY);
    }
    else{
    setX(getX() + deltaX);
	setY(getY() + deltaY);
    }

    if (m_win_w > 0 && m_win_h)
    {
        double xpix = getX() / SimApp::getMetersPerPixel();
        double ypix = getY() / SimApp::getMetersPerPixel();
        double wpix = getW() / SimApp::getMetersPerPixel();
        double hpix = getH() / SimApp::getMetersPerPixel();        

        if (xpix > m_win_w)
            xpix = wpix/2.0;
        else if (xpix < 0)
            xpix = m_win_w-(wpix/2.0);

        if (ypix > m_win_h)
            ypix = (hpix/2.0);
        else if (ypix < 0)
            ypix = m_win_h-(hpix/2.0);
        
        setX(xpix * SimApp::getMetersPerPixel());
        setY(ypix * SimApp::getMetersPerPixel());
    }
}

ParticleBase * Splendido::findClosest() 
{
    ParticleBase * smallest = NULL;
    double mindist = 100000;
    for (vector<ParticleBase*>::const_iterator it = m_playground.getParticles().begin(); 
        it!=m_playground.getParticles().end(); it++) 
    {
        if (*it != this)
        {
            double dist = sqrt(pow(getX() - (*it)->getX(), 2) + 
                pow(getY() - (*it)->getY(), 2));

            if (dist < mindist)
            {//checks for collision and if both particles are ice it does nothing, else collison true
                mindist = dist;
                smallest = *it;
            }
        }
    }
    if(mindist < 30){
        if(!(this)->getPower() && !(smallest)->getPower()){
            
        }
        else if((this)->getPower() && (smallest)->getPower()){
            (smallest)->setCollision(true);
            (this)->setCollision(true);
        }
        else if((this)->getPower() && !(smallest)->getPower()){
            (smallest)->setCollision(true);
        }
        else if((smallest)->getPower() && !(this)->getPower()){
            (this)->setCollision(true);
        }
    }
    return smallest;
}

bool Splendido::isAboveMe(ParticleBase* particle) const
{
    return particle->getY() < getY();
}

bool Splendido::isToMyRight(ParticleBase * particle) const
{
    return particle->getX() > getX();
}
