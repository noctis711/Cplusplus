#include "ParticlePlayground.h"
#include <cairomm/context.h>
#include <iostream>

using namespace std;

ParticlePlayground::ParticlePlayground()
  : m_particles()
{ }

ParticlePlayground::~ParticlePlayground()
{
    for (vector<ParticleBase*>::const_iterator it = m_particles.begin(); 
        it!=m_particles.end(); it++) 
    {
        delete (*it);
    }    
}

void ParticlePlayground::add(ParticleBase* p)
{
    m_particles.push_back(p);
}

bool ParticlePlayground::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    cr->save();

    Gtk::Allocation allocation = get_allocation();
    const int win_width = allocation.get_width();
    const int win_height = allocation.get_height();
    
    for (vector<ParticleBase*>::const_iterator it = m_particles.begin(); 
        it!=m_particles.end(); it++) 
    {
        (*it)->draw(win_height, win_width, cr);
    }

    cr->restore();

    return true;
}


void ParticlePlayground::tick(long t)
{//loop checks for collisions and add particles that haven't collided
    for(auto it = m_particles.begin(); it!=m_particles.end(); it++){
        if((*it)->getCollision()==false){
            m_goodParticles.push_back(*it);
        }
        else{
            //cout << "collision" << endl;
        }
    }
    m_particles = m_goodParticles;
    m_goodParticles.clear();
    for (vector<ParticleBase*>::const_iterator it = m_particles.begin(); 
        it!=m_particles.end(); it++) 
    {
            (*it)->tick(t);
    }    
    queue_draw();
}