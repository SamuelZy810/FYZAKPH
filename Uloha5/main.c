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
const float r = 1;
const float PI = 3.1415926f;
const float num_segments = 1500;
const float view = 10;

// Pomer stran
float pomStr;

// Vektory
float v, ad, at, vc;

// Suradnice
float x, y, uh0, uh1;

// Cas
float t = 0;

// Rychlost
float uhR0 = 0, uhR1 = 0;

// Zrychlenie
float epsilon = 0;

// Subor
FILE * f = NULL;

void posun(const int hod) {
    t += casKrok;

    x = r * cosf(uh1);
    y = r * sinf(uh1);

    uh1 = uh0 + uhR0 * (t / 1000) + (0.5 * epsilon * (t / 1000) * (t / 1000));
    uhR1 = uhR0 + (epsilon * (t / 1000));

    v = r * uhR1;
    ad = r * uhR1 * uhR1;
    at = r * (epsilon * (t / 1000));
    vc = ad + at;

    glutPostRedisplay();
    glutTimerFunc(casKrok, posun, hod + 1); // rekurzívna funkcia
}

void resize (int sirka , int vyska ) {
    glViewport (0, 0, sirka, vyska);
    glMatrixMode ( GL_PROJECTION );
    glLoadIdentity();
    pomStr = sirka / vyska;

    if ( sirka == 0) sirka ++;

    gluOrtho2D ( -0.5 * view, 0.5 * view, -0.5 * view, 0.5 * view);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode ( GL_MODELVIEW );

    glLoadIdentity();
    glColor3f((float) (235.0/256.0), (float) (64.0/256.0), (float) (52.0/256.0));
    glBegin(GL_LINE_STRIP);
    for(int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * PI * (float) (ii / num_segments);

        float cx = r * cosf(theta);
        float cy = r * sinf(theta);

        glVertex2f(cx, cy);
    }
    glEnd();

    // Vektor rychlosti
    glLoadIdentity();
    glColor3f((float) (235.0/256.0), (float) (23.0/256.0), (float) (71.0/256.0));
    glTranslatef((float) x, (float) y, (float) 0.0);
    glRotatef(uh1 * (180 / PI) + 45, 0, 0, 1);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(v, v);
    glEnd();

    // Tankecionalny vektor
    glLoadIdentity();
    glColor3f((float) (135.0/256.0), (float) (210.0/256.0), (float) (71.0/256.0));
    glTranslatef((float) x, (float) y, (float) 0.0);
    glRotatef(uh1 * (180 / PI) + 45, 0, 0, 1);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(at, at);
    glEnd();

    // Vektor dostrediveho zrychlenia
    glLoadIdentity();
    glColor3f((float) (135.0/256.0), (float) (35.0/256.0), (float) (211.0/256.0));
    glTranslatef((float) x, (float) y, (float) 0.0);
    glRotatef(uh1 * (180 / PI) + 135, 0, 0, 1);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(ad, ad);
    glEnd();

    // Celkove zrychlenie
    glLoadIdentity();
    glColor3f((float) (75.0/256.0), (float) (4.0/256.0), (float) (190.0/256.0));
    glTranslatef((float) x, (float) y, (float) 0.0);
    glRotatef(uh1 * (180 / PI) + 90, 0, 0, 1);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(vc, vc);
    glEnd();

    glLoadIdentity();
    glColor3f((float) (235.0/256.0), (float) (131.0/256.0), (float) (52.0/256.0));
    glTranslatef((float) x, (float) y, (float) 0.0);
    glRotatef(uh1 * (180 / PI), 0, 0, 1);
    glBegin(GL_QUADS);
    glVertex2f(0, 1);
    glVertex2f(1, 1);
    glVertex2f(1, 0);
    glVertex2f(0, 0);
    glEnd();

    glutSwapBuffers();
}

// Ovladanie klavesnice
void keyboardNormalKey(unsigned char key, int x, int y) {
    switch (key) {
        case 49:
            // Zasztavenie
            uh0 = uh1;
            uhR0 = 0;
            epsilon = 0;
            break;
        case 27:
            // Vypnutie programu
            fclose(f);
            exit(0);
    }
}

void keyboardSpecialKey(int key , int x, int y)
{
    switch(key) {

        case GLUT_KEY_UP:
        {
            // Zrychlenie
            t = 0;
            uh0 = uh1 + uhR0 * (t / 1000) + (0.5 * epsilon * (t / 1000) * (t / 1000));
            uhR0 = uhR1;
            epsilon += 0.5f;
        }
            break;
        case GLUT_KEY_DOWN:
        {
            // Spomalenie
            t = 0;
            uh0 = uh1 + uhR0 * (t / 1000) + (0.5 * epsilon * (t / 1000) * (t / 1000));
            uhR0 = uhR1;
            epsilon -= 0.5f;
        }
            break;
    }
}

int main(int argc, char **argv) {

    if (f == NULL) {
        f = fopen("vystup.dat", "w");
    }

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

    glutKeyboardFunc(keyboardNormalKey);
    glutSpecialFunc(keyboardSpecialKey);

    glutMainLoop();
    fclose(f);
    return 0;
}