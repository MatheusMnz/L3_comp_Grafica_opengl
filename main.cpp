// STL libs
#include <bits/stdc++.h>

// OpenGL, GLUT & GLEW libs
#include <GL/glew.h>
#include <GL/freeglut.h>

// Development libs
#include "libs/callback.h"

void drawUpdate()
{
    // Limpa a cena e o buffer de profundidade
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Carrega a identidade no sistema
    glLoadIdentity();

    // Desenha todas as esferas
    // sistemaSolar.updateOnDraw();
    

    // Clean Code <3
    // Swap buffers >_<
    glutSwapBuffers();
}

void onTimeUpdate(int param)
{
    // Movimenta as esferas

    glutTimerFunc(param, onTimeUpdate, param);
}

void configGlut()
{
    // Configura a janela da GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(600, 600 * 1 / razaoAspecto);

    glutInitWindowPosition(0, 0);
    glutCreateWindow("Solar System");

    // Configura os callbacks da GLUT
    glutDisplayFunc(drawUpdate);
    glutReshapeFunc(reshapeFct);
    glutKeyboardFunc(keyboardFct);
    glutKeyboardUpFunc(keyboardFct);
    glutSpecialFunc(keyboardSpecial);
    glutSpecialUpFunc(keyboardSpecial);

    glutTimerFunc(16, onTimeUpdate, 16);

    glLineWidth(8);

    prev_wh = 600 * razaoAspecto;
    prev_ww = 600;

    // Ignora repetições de teclas e verifica apenas o pressionamento e qnd soltar
    glutIgnoreKeyRepeat(1);
}

void configOpenGl()
{
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);

    // Não mostrar faces do lado de dentro
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Esconder o ponteiro do mouse quando dentro da janela
    glutSetCursor(GLUT_CURSOR_NONE);
}

int main(int argc, char **argv)
{
    // Configura a janela da glut
    configGlut();

    // Inicializa a GLEW
    glewInit();

    // Configura o OpenGl e a Iluminacao
    configOpenGl();
    // Inicializa os planetas

    // Começa o loop principal
    glutMainLoop();
}