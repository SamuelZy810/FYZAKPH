// Standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>

// GL libraries
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

// Konštanty
const int casKrok = 16;
const float g = (float) 9.81;

// Vstupne hodnoty
float v0, a, h0;

// Primerany obraz
float HH, LL;

// Suradnice
float x, y;
float surX[10000000], surY[10000000];
int iterator = 0;

// Cas
float t = 0;

// Rychlost
float vx, vy;

// Subor
FILE * f = NULL;

void posun(const int hod) {
    t += casKrok;

    x = v0 * cosf(a) * (t / 1000);
    y = h0 + v0 * sinf(a) * (t / 1000) - (0.5 * g * powf((t / 1000), 2));

    vx = v0 * cosf(a);
    vy = v0 * sinf(a) - g * (t / 1000);

    if (y <= 0) {
        fclose(f);
        exit(1);
    }

    surX[iterator] = x;
    surY[iterator] = y;
    iterator++;

    glutPostRedisplay();
    glutTimerFunc(casKrok, posun, hod + 1); // rekurzívna funkcia
}

void resize (int sirka , int vyska ) {
    glViewport (0, 0, sirka, vyska);
    glMatrixMode ( GL_PROJECTION );
    glLoadIdentity();

    if ( sirka == 0) sirka ++;

    gluOrtho2D ( 0, 10 * LL, 0, 10 * HH);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode ( GL_MODELVIEW );

    if (iterator > 0) {
        glLoadIdentity();
        glColor3f((float) (235.0/256.0), (float) (131.0/256.0), (float) (52.0/256.0));
        glBegin(GL_LINES);
        for (int i = 1; i < iterator; ++i) {
            glVertex2f(surX[i], surY[i]);
            glVertex2f(surX[i - 1], surY[i - 1]);
        }
        glEnd();
    }

    glLoadIdentity();
    glColor3f((float) (100.0/256.0), (float) (70.0/256.0), (float) (145.0/256.0));
    glBegin(GL_LINES);
    glVertex2f(vx + x, vy + y);
    glVertex2f(x, y);
    glEnd();


    glLoadIdentity();
    glColor3f((float) (235.0/256.0), (float) (131.0/256.0), (float) (52.0/256.0));
    glTranslatef((float) x, (float) y, (float) 0.0);
    glBegin(GL_QUADS);
    glVertex2f(0, 0.1 * HH);
    glVertex2f(0.1 * LL, 0.1 * HH);
    glVertex2f(0.1 * LL, 0);
    glVertex2f(0, 0);
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char **argv) {
    if (argc > 3) {
        printf("Inicializujem!\n");
        v0 = atof(argv[1]); a = atof(argv[2]); h0 = atof(argv[3]);
    }

    if (f == NULL) {
        f = fopen("vystup.dat", "w");
    }

    float v0y = v0 * sinf(a);
    float v0x = v0 * cosf(a);

//    HH = h0 + (powf(v0y, 2) / (2 * g));
//    LL = v0x * ((v0y + sqrtf(powf(v0y, 2) + 2 * h0 * g)) / g);

    HH = 1;
    LL = 1;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);

    glutInitWindowSize(700, 700);
    glutInitWindowPosition(170, 50);
    glutCreateWindow("Uloha cislo 4 - Zaprazny");

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.9, 0.9, 0.9, 0.5);

    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutTimerFunc(casKrok, posun, 0);

    glutMainLoop();
    fclose(f);
    return 0;
}