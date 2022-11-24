// STL libs
#include <bits/stdc++.h>

// OpenGL, GLUT & GLEW libs
#include <GL/glew.h>
#include <GL/freeglut.h>

// Development libs
#include "libs/SolarSystem.h"
#include "libs/callback.h"

SolarSystem *sistemaSolar;

void drawUpdate()
{
    // Limpa a cena e o buffer de profundidade
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Carrega a identidade no sistema
    glLoadIdentity();

    // Utiliza de coordenadas cilindricas para movimentar a camera
    // x = origin.x + p*sin(θ)*cos(Φ)
    // y = origin.y + p
    // z = origin.z +p*cos(θ)*cos(Φ)

    gluLookAt(0, 400, 1,
              0, 0, 0,
              0, 1, 0);
    // Desenha todas as esferas
    sistemaSolar->updateOnDraw();

    // Clean Code <3
    // Swap buffers >_<
    glutSwapBuffers();
}

void onTimeUpdate(int param)
{
    // Movimenta as esferas
    sistemaSolar->updateOnTime();
    glutPostRedisplay();
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
    glDisable(GL_CULL_FACE);

        // Esconder o ponteiro do mouse quando dentro da janela
    // glutSetCursor(GLUT_CURSOR_NONE);

    float globAmb[] = {0.15, 0.15, 0.15, 1.0};

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, false); // habilita local view
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb);   // Luz ambiente global

    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_LIGHT0);
}

void initGame()
{
    sistemaSolar = new SolarSystem("solarsystem.sscp");
}

int main(int argc, char **argv)
{
    // Inicializa a glut
    glutInit(&argc, argv);

    // Configura a janela da glut
    configGlut();

    // Inicializa a GLEW
    glewInit();

    // Configura o OpenGl e a Iluminacao
    configOpenGl();

    // Inicializa os planetas
    initGame();

    // Começa o loop principal
    glutMainLoop();
}