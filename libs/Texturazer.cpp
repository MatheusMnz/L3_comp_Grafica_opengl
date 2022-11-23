#include "Body.h"
#include "Texturazer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>

// It belongs to Adjailson
// By : Adjailson, the legend
int Texturazer::parse_script(const char *file_name)
{

    // Variáveis auxiliares
    std::ifstream *file = new std::ifstream();
    vec3f_t aux = {0};
    std::vector<vec3f_t> aux_cords;

    char *input_str = (char *)malloc(sizeof(char) * 50);

    int n_coordenadas,
        n_texturas;

    file->open(file_name, std::ios::in);

    // Verifica se o arquivo está aberto
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
        if (strcmp("TEXTURE_SCRIPT", input_str))
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

    // Verifica quantos modelos de textura deve carregar
    file->getline(input_str, 30);
    sscanf(input_str, "%d", &n_texturas);

    // Carrega o vetor de modelo da textura e o vetor de texturas
    for (int i = 0; i < n_texturas; i++)
    {
        // Obtem as coordenadas do modelo
        file->getline(input_str, 30, ';');
        sscanf(input_str, "%d;", &n_coordenadas);

        for (int x = 0; x < n_coordenadas; x++)
        {
            file->getline(input_str, 30, ';');
            sscanf(input_str, "%f,%f", &aux.x, &aux.y);

            // Preenche o vetor
            aux_cords.push_back(aux);
        }

        // Append na lista de vetores de coordenadas e limpa o vetor para proxima leitura
        this->texture_cords.push_back(aux_cords);
        aux_cords.clear();

        // Lê o resto da linha para ir para a próxima
        file->getline(input_str, 50);

        // Obtem o nome do arquivo de textura
        file->getline(input_str, 100);
        // printf("nome = %s\n", input_str);
        std::string input_caminho("assets/texture/");
        input_caminho.append(input_str);

        // Carrega a textura usando a soil
        GLuint idTextura = SOIL_load_OGL_texture(input_caminho.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_DDS_LOAD_DIRECT);

        // Verifica se ocorreu algum erro na SOIL
        if (idTextura == 0)
        {
            printf("Erro do SOIL: '%s'\n", SOIL_last_result());
            return 1;
        }
        else
            this->loaded_textures.push_back(idTextura);
    }

    delete input_str;
    delete file;
    return 0;
}

// construtor
Texturazer::Texturazer(const char *script_name,

                       float *matDif,
                       float *matSpec,
                       float *matShine)
{

    // Little Gambs, arrumar no projeto final

    // // Tenta carregar a textura de acordo com o arquivo de script
    // if (parse_script(script_name) == 1)
    // {
    //     printf("Arquivo de Textura [%s] Inexistente ou Inelegivel ! \n", script_name);
    // }

    // Carrega os valores do material direto
    memcpy(this->matDif, matDif, sizeof(float) * 4);
    memcpy(this->matSpec, matSpec, sizeof(float) * 4);
    memcpy(this->matShine, matShine, sizeof(float) * 4);

    // Carrega diretamente usando a soil, permite apenas um arquivo
    // Carrega a textura usando a soil/
    GLuint idTextura = SOIL_load_OGL_texture(script_name, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_DDS_LOAD_DIRECT);

    // Verifica se ocorreu algum erro na SOIL
    if (idTextura == 0)
    {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
    }
    else
        this->loaded_textures.push_back(idTextura);
}
