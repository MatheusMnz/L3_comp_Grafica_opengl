#ifndef __SOLARSYSTEM__
#define __SOLARSYSTEM__

#include <vector>
#include "Body.h"
#include <iostream>

class SolarSystem
{
private:
    // Vetores de Corpos no Sistema
    std::vector<Body> astros;

    // Vetores de corpos que nao precisam de iteracao com a luz
    std::vector<Body *> nonReacting;

public:
    SolarSystem(const char *script_name);

    // Parser para o script de sistema solar
    int parseScript(const char *script_name);

    // Funcao para atualizar o movimento dos astros
    void updateOnTime();

    // Funcao para desenhar os astros
    void updateOnDraw();
};

#endif