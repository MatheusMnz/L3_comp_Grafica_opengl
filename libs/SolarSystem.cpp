#include "SolarSystem.h"
#include <vector>
#include "Body.h"
#include <iostream>

SolarSystem::SolarSystem(const char * texture_name)
{
    if(this->parseScript(texture_name))
    {
        printf("Deu ruim no parser do sistema solar >_< \n");
    }
}

void SolarSystem::updateOnTime()
{
    for (int i = 0; i < astros.size(); i++)
    {
        astros[i].move();
    }
}

void SolarSystem::updateOnDraw()
{
    // Limpa o vetor de objetos que nao reagem a luz
    nonReacting.clear();

    // Desenha todos os objetos que reagem a luz
    glEnable(GL_LIGHTING);
    for (int i = 0; i < astros.size(); i++)
    {
        // Verifica se o corpo interage com a luz
        if (astros[i].isLight())
        {
            astros[i].draw();
        }
        else
            nonReacting.push_back(&astros[i]);
    }
    glDisable(GL_LIGHTING);

    // Desenha os objetos que nao reagem a luz
    for (int i = 0; i < nonReacting.size(); i++)
    {
        nonReacting[i]->draw();
    }
}