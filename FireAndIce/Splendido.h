#ifndef SPLENDIDO_PARTICLE_H
#define SPLENDIDO_PARTICLE_H

#include "ParticleBase.h"
#include "ParticlePlayground.h"
#include <gtkmm/drawingarea.h>

class Splendido : public ParticleBase
{
public:
    Splendido(double x, double y, double w, double h, 
        double vX, double vY, bool fire, ParticlePlayground& playground);
    virtual void draw(int win_height, int win_width, 
  	const Cairo::RefPtr<Cairo::Context>& cr);
    virtual ~Splendido() {};
    virtual void tick(long t);

   	double getVX() const { return m_vX; }
   	double getVY() const { return m_vY; }
   	void setVX(double vx) { m_vX = vx; }
   	void setVY(double vy) { m_vY = vy; }
    

private:
  bool m_fire;
  double m_red;
  double m_green;
  double m_blue;
  int m_win_w;
  int m_win_h;
	double m_vX;
	double m_vY;
  Glib::RefPtr<Gdk::Pixbuf> fireImage = 
        Gdk::Pixbuf::create_from_file("fire.png");
    Glib::RefPtr<Gdk::Pixbuf> iceImage = 
        Gdk::Pixbuf::create_from_file("ice.png");
  ParticlePlayground& m_playground;
  ParticleBase * findClosest() ;
  bool isAboveMe(ParticleBase* particle) const;
  bool isToMyRight(ParticleBase* particle) const;
};

#endif