#include "SolarSystem.h"

SolarSystem::SolarSystem(const char *script)
{
    if (this->parseScript(script))
    {
        printf("Deu ruim no parser do sistema solar >_< \n");
    }
}

int SolarSystem::parseScript(const char *file_name)
{
    // Referência para o arquivo
    std::ifstream *file = new std::ifstream();

    // Definindo varáveis
    vec3f_t mov_origem = {0};

    GLint lightEmissor = 0,
          n_luas = 0,
          n_astros = 0,
          elipse_a, elipse_b;

    GLfloat vel_rot = 0,
            vel_trans = 0;

    char *input_str = (char *)malloc(sizeof(char) * 50);

    float lightDif[4] = {0};
    float lightSpec[4] = {0};
    float lightShine[4] = {0};

    // Abro o arquivo
    file->open(file_name, std::ios::in);

    // Verifica se o arquivo foi aberto
    if (!file->is_open())
    {
        printf("COULDNT_OPEN_FILE \n");
        delete input_str;
        delete file;
        return 1;
    }

    // Verifica se o arquivo está vazio
    if (!file->eof())
    {
        file->getline(input_str, 30);

        // Verifica a formatacao
        if (strcmp("SISTEMA", input_str))
        {
            printf("FORMAT_ERROR_ON_FILE \n");
            delete input_str;
            delete file;
            return 1;
        }
    }
    else
    {
        delete input_str;
        delete file;
        return 1;
    }

    // Verifica quantos astros teremos
    file->getline(input_str, 30);
    sscanf(input_str, "%d", &n_astros);

    for (int i = 0; i < n_astros; i++)
    {
        lightEmissor = 0;
        if (n_luas)
        {
            // Obter o centro de movimento (x, y, z)
            file->getline(input_str, 30, ';');
            sscanf(input_str, "%f,%f,%f", &mov_origem.x, &mov_origem.y, &mov_origem.z);
            n_luas--;
        }
        // Obter os coeficientes "a" e "b" das elipses
        file->getline(input_str, 10, ';');
        sscanf(input_str, "%d", &elipse_a);
        file->getline(input_str, 10, ';');
        sscanf(input_str, "%d", &elipse_b);

        // Obter velocidade de rotação
        file->getline(input_str, 10, ';');
        sscanf(input_str, "%f", &vel_rot);

        // Obter velocidade de translação
        file->getline(input_str, 10, ';');
        sscanf(input_str, "%f", &vel_trans);

        // Obter propriedade de emissor de luz
        file->getline(input_str, 10, ';');
        sscanf(input_str, "%d", &lightEmissor);

        // Verifica se é um emissor de Luz
        if (lightEmissor)
        {
            // Carrega as propriedades da luz
            file->getline(input_str, 100);
            sscanf(input_str, "%f;%f;%f", &lightDif[0], &lightDif[1], &lightDif[2]);
            file->getline(input_str, 100);
            sscanf(input_str, "%f;%f;%f", &lightSpec[0], &lightSpec[1], &lightSpec[2]);
            file->getline(input_str, 100);
            sscanf(input_str, "%f;%f;%f", &lightShine[0], &lightShine[1], &lightShine[2]);
        }

        // Obter o número de luas
        file->getline(input_str, 10, ';');
        sscanf(input_str, "%d", &n_luas);

        if(n_luas)
        {
            
        }
    }

    return 0;
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