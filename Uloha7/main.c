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
const float g = 9.81f;
const float PI = 3.1415926f;
const float view = 12;
const float L = 4;

// Pomer stran
float pomStr;

// Cas
float t = 0;

// Uhol dosky
float alpha = 0;

// Nulove parametre
float x0 = 0, v0 = 0;

// Nenulove parametre
float x = 0, v = 0;

// Koeficienty trenia
float mis = 0.5f, mid = 0.1f;

// Zrachlenia
float a;

float sgn(float num){
    if(num>=0){
        return 1;
    }else{
        return -1;
    }
}

void posun(const int hod) {
    t += casKrok;

    if (mis < fabsf(atanf(alpha * (PI / 180)))) {
        if (alpha == 0 && v > -0.02 && v < 0.02) {a = 0; v0 = 0;}
        else a = -1 * (g * sinf(alpha * (PI / 180)) - sgn(mid * g * cosf(alpha * (PI / 180))));

        if (x > L && (a > 0 || v > 0) || x < -L && (a < 0 || v < 0)) {
            a = 0;
            v0 = 0;
            v = 0;
        } else {
            x = x0 + (v0 * (t / 1000)) + (0.5f * a * (t / 1000) * (t / 1000));
            v = v0 + (a * (t / 1000));
        }
    } else if (v != 0) {
        if (alpha == 0 && v > -0.02 && v < 0.02) {a = 0; v0 = 0;}
        else a = -1 * (g * sinf(alpha * (PI / 180)) - sgn(mid * g * cosf(alpha * (PI / 180))));

        if (x > L && (a > 0 || v > 0) || x < -L && (a < 0 || v < 0)) {
            a = 0;
            v0 = 0;
            v = 0;
        } else {
            x = x0 + (v0 * (t / 1000)) + (0.5f * a * (t / 1000) * (t / 1000));
            v = v0 + (a * (t / 1000));
        }
    }

    glutPostRedisplay();
    glutTimerFunc(casKrok, posun, hod + 1); // rekurzívna funkcia
}

void resize (int sirka , int vyska ) {
    glViewport (0, 0, sirka, vyska);
    glMatrixMode ( GL_PROJECTION );
    glLoadIdentity();
    pomStr = (float) sirka / (float) vyska;

    if ( sirka == 0) sirka ++;

    gluOrtho2D ( (-0.5 * view), (0.5 * view), (-0.5 * view), (0.5 * view));
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode ( GL_MODELVIEW );

    glLoadIdentity();
    glColor3f(0,0.5f,0.4f);
    glBegin(GL_LINES);
    glVertex2f(-0.5f * GLUT_WINDOW_WIDTH, 0);
    glVertex2f(0.5f * GLUT_WINDOW_WIDTH, 0);
    glEnd();

    glLoadIdentity();
    glRotatef(alpha, 0, 0, 1);
    glColor3f(0.35f,0.27f,0.1f);
    glBegin(GL_QUADS);
    glVertex2f(0,0.15f);
    glVertex2f(-L, 0.15f);
    glVertex2f(-L, 0);
    glVertex2f(0, 0);

    glVertex2f(L, 0.15f);
    glVertex2f(0, 0.15f);
    glVertex2f(0, 0);
    glVertex2f(L, 0);

    glVertex2f(L + 0.05f, 0.3f);
    glVertex2f(L, 0.3f);
    glVertex2f(L, -0.15f);
    glVertex2f(L + 0.05f, -0.15f);

    glVertex2f(0,-0.15f);
    glVertex2f(-L, -0.15f);
    glVertex2f(-L, 0);
    glVertex2f(0, 0);

    glVertex2f(L, -0.15f);
    glVertex2f(0, -0.15f);
    glVertex2f(0, 0);
    glVertex2f(L, 0);

    glVertex2f(-L - 0.05f, 0.3f);
    glVertex2f(-L, 0.3f);
    glVertex2f(-L, -0.15f);
    glVertex2f(-L - 0.05f, -0.15f);
    glEnd();

    glLoadIdentity();
    glColor3f(0, 0, 0);
    glRotatef(alpha, 0, 0, 1);
    glTranslatef(x, 0, 0);
    glBegin(GL_QUADS);
    glVertex2f(0, 0.5f + 0.15f);
    glVertex2f(0.5f, 0.5f + 0.15f);
    glVertex2f(0.5f, 0 + 0.15f);
    glVertex2f(0, 0 + 0.15f);
    glEnd();

    glutSwapBuffers();
}

void keyboardSpecialKey(int key , int vx, int vy)
{
    switch(key) {

        case GLUT_KEY_RIGHT:
        {
            // Naklonenie dolava
            if (alpha >= -30) {
                alpha -= 2;
                t = 0;
                x0 = x + (v0 * (t / 1000)) + (0.5f * a * (t / 1000) * (t / 1000));
                v0 = v + (a * (t / 1000));
                v = v0;
//                a = -1 * (g * sinf(alpha * (PI / 180)) - sgn(mid * g * cosf(alpha * (PI / 180))));
            }
        }
            break;
        case GLUT_KEY_LEFT:
        {
            // Naklonenie dolava
            if (alpha <= 30) {
                alpha += 2;
                t = 0;
                x0 = x + (v0 * (t / 1000)) + (0.5f * a * (t / 1000) * (t / 1000));
                v0 = v + (a * (t / 1000));
//                a = -1 * (g * sinf(alpha * (PI / 180)) + sgn(mid * g * cosf(alpha * (PI / 180))));
            }
        }
            break;
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);

    glutInitWindowSize(700, 700);
    glutInitWindowPosition(170, 50);
    glutCreateWindow("Uloha cislo 7 - Zaprazny");

    glClearColor(0.9, 0.9, 0.9, 0.5);

    glutSpecialFunc(keyboardSpecialKey);

    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutTimerFunc(casKrok, posun, 0);

//    printf("Sin 30 %4.3f cos 30 %4.3f\nSin 30 %4.3f cos 30 %4.3f\n\n", sinf(30), cosf(30), sinf(-30), cosf(-30));
//    printf("a -30 +%4.3f\n", -1 * (g * sinf(-30 * (PI / 180)) - mid * g * cosf(-30 * (PI / 180))));
//    printf("a +30 %4.3f", -1 * (g * sinf(30 * (PI / 180)) + mid * g * cosf(30 * (PI / 180))));

    glutMainLoop();
    return 0;
}
