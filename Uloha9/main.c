// Standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include <time.h>

// GL libraries
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdbool.h>

// Konštanty
const int casKrok = 16;
const float g = 9.81f;
const float PI = 3.1415926f;
const float view = 12;
const float k = 1.0f;

// Pomer stran
float pomStrSirka, pomStrVyska;

// Cas
float t = 0; // s - pre výpočty
time_t tt; // s - seed pre generovanie

// Hmotnosti
float m1 = 1.0f, m2 = 1.0f, m3 = 1.0f; // kg

// Vektory medzi bodmi, suradnice (x, y, z)
float rv12[3], rv13[3], rv23[3];

// Velkost vektorov
float r12 = 0, r13 = 0, r23 = 0;

// Vektory sily medzi bodmi, suradnice (x, y, z)
float f12[3], f13[3], f23[3];

// Vektor sily bodu
float f1[3], f2[3], f3[3];

// Suradnice bodov
float x10 = 0, y10 = 0, z10 = 0, x11 = 0, y11 = 0, z11 = 0; // Bod 1 -> r1
float x20 = 0, y20 = 0, z20 = 0, x21 = 0, y21 = 0, z21 = 0; // Bod 2 -> r2
float x30 = 0, y30 = 0, z30 = 0, x31 = 0, y31 = 0, z31 = 0; // Bod 3 -> r3

// Rychlost bodu
float v1x = 0.5f, v1y = 0.5f, v1z = 0;
float v2x = -0.5f, v2y = -0.5f, v2z = 0;
float v3x = 0, v3y = 0, v3z = 0;

// Tazisko
float xT = 0, yT= 0, zT = 0; // Suradnice
float pv[3]; // Vektor celkocej hybnosti

// Súradnice trajektórie
float trX1[10000000], trY1[10000000]; // Trajektória telesa 1
float trX2[10000000], trY2[10000000]; // Trajektória telesa 2
float trX3[10000000], trY3[10000000]; // Trajektória telesa 3
int cast = 0;

void posun(const int hod) {
    // Kód
    // Teleso 1
    v1x = v1x + f1[0] * ((float) casKrok / 1000.0f);
    x11 = x11 + v1x * ((float) casKrok / 1000.0f);

    v1y = v1y + f1[1] * ((float) casKrok / 1000.0f);
    y11 = y11 + v1y * ((float) casKrok / 1000.0f);

    v1z = v1z + f1[2] * ((float) casKrok / 1000.0f);
    z11 = z11 + v1z * ((float) casKrok / 1000.0f);

    // Teleso 2
    v2x = v2x + f2[0] * ((float) casKrok / 1000.0f);
    x21 = x21 + v2x * ((float) casKrok / 1000.0f);

    v2y = v2y + f2[1] * ((float) casKrok / 1000.0f);
    y21 = y21 + v2y * ((float) casKrok / 1000.0f);

    v2z = v2z + f2[2] * ((float) casKrok / 1000.0f);
    z21 = z21 + v1z * ((float) casKrok / 1000.0f);

    // Teleso 3
    x31 = -x11 - x21;
    y31 = -y11 - y21;
    z31 = -z11 - z21;

    trX1[cast] = x11;
    trX2[cast] = x21;
    trX3[cast] = x31;

    trY1[cast] = y11;
    trY2[cast] = y21;
    trY3[cast] = y31;

    cast++;

    r12 = sqrtf(powf((x21 - x11), 2) + powf((y21 - y11), 2) + powf((z21 - z11), 2));
    r13 = sqrtf(powf((x31 - x11), 2) + powf((y31 - y11), 2) + powf((z31 - z11), 2));
    r23 = sqrtf(powf((x31 - x21), 2) + powf((y31 - y21), 2) + powf((z31 - z21), 2));

    rv12[0] = x21 - x11;
    rv12[1] = y21 - y11;
    rv12[2] = z21 - z11;

    rv13[0] = x31 - x11;
    rv13[1] = y31 - y11;
    rv13[2] = z31 - z11;

    rv23[0] = x31 - x21;
    rv23[1] = y31 - y21;
    rv23[2] = z31 - z21;

    f12[0] = k * ((m1 * m2) / r12) * (rv12[0]/r12);
    f12[1] = k * ((m1 * m2) / r12) * (rv12[1]/r12);
    f12[2] = k * ((m1 * m2) / r12) * (rv12[2]/r12);

    f13[0] = k * ((m1 * m3) / r13) * (rv13[0]/r13);
    f13[1] = k * ((m1 * m3) / r13) * (rv13[1]/r13);
    f13[2] = k * ((m1 * m3) / r13) * (rv13[2]/r13);

    f23[0] = k * ((m2 * m3) / r23) * (rv23[0]/r23);
    f23[1] = k * ((m2 * m3) / r23) * (rv23[1]/r23);
    f23[2] = k * ((m2 * m3) / r23) * (rv23[2]/r23);

    f1[0] = f12[0] + f13[0]; // x
    f1[1] = f12[1] + f13[1]; // y
    f1[2] = f12[2] + f13[2]; // z

    f2[0] = -1 * f12[0] + f23[0];
    f2[1] = -1 * f12[1] + f23[1];
    f2[2] = -1 * f12[2] + f23[2];

    f3[0] = -1 * f13[0] + -1 * f13[0];
    f3[0] = -1 * f13[0] + -1 * f13[0];
    f3[0] = -1 * f13[0] + -1 * f13[0];

    // Vypocet taziska
    // Súradnice
    xT = ((x11 * m1) + (x21 * m2) + (x31 * m3)) / (m1 + m2 + m3);
    yT = ((y11 * m1) + (y21 * m2) + (y31 * m3)) / (m1 + m2 + m3);
    zT = ((z11 * m1) + (z21 * m2) + (z31 * m3)) / (m1 + m2 + m3);

    // Vektor hybnosti
    pv[0] = m1 * v1x + m2 * v2x + m3 * v3x;
    pv[1] = m1 * v1y + m2 * v2y + m3 * v3y;
    pv[2] = m1 * v1z + m2 * v2z + m3 * v3z;

    // Vypis na overenie - súradnice taziska aj vektor celkovej hybnosti
    // by mali byt 0 - kvôli chybe vypoctov, zaokruhlovanie a pod to nikdy nebude uplna 0
    printf("Suradnice T: x = %.2f, y = %.2f, z = %.2f; Vektor p: (x, y, z) = (%.2f, %.2f, %.2f)\n", xT, yT, zT, pv[0], pv[1], pv[2]);

    t += (float) casKrok;
    glutPostRedisplay();
    glutTimerFunc(casKrok, posun, hod + 1); // rekurzívna funkcia
}

void resize (int sirka , int vyska ) {

    glViewport (0, 0, sirka, vyska);
    glMatrixMode ( GL_PROJECTION );

    glLoadIdentity();

    if (sirka == 0) sirka ++;
    if (vyska == 0) vyska ++;

    pomStrVyska = (float) sirka / (float) vyska;
    pomStrSirka = (float) vyska / (float) sirka;

    gluOrtho2D ( (-0.5 * view), (0.5 * view), (-0.5 * view), (0.5 * view));

}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode ( GL_MODELVIEW );

    /// Tri kocky

    // Kocka 1
    glLoadIdentity();
    // 66, 135, 245 rgb
    glColor3f((66 / 256.0f), (135 / 256.0f), (245 / 256.0f));
    glTranslatef(x11, y11, z11);

    glBegin(GL_QUADS);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.5f, 0.0f);
    glEnd();

    // Kocka 2
    glLoadIdentity();
    // 235, 64, 52 rgb
    glColor3f((235 / 256.0f), (64 / 256.0f), (52 / 256.0f));
    glTranslatef(x21, y21, z21);

    glBegin(GL_QUADS);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.5f, 0.0f);
    glEnd();

    // Kocka 3
    glLoadIdentity();
    // 252, 186, 3 rgb
    glColor3f((252 / 256.0f), (186 / 256.0f), (3 / 256.0f));
    glTranslatef(x31, y31, z31);

    glBegin(GL_QUADS);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.5f, 0.0f);
    glEnd();

    if (cast > 0) {
        glLoadIdentity();
        // 152, 175, 212 rgb
        glColor3f((152 / 256.0f), (175 / 256.0f), (212 / 256.0f));
        glBegin(GL_LINES);
        for (int i = 0; i < (cast - 1); ++i) {
            glVertex2f(trX1[i], trY1[i]);
            glVertex2f(trX1[i + 1], trY1[i + 1]);
        }
        glEnd();

        glLoadIdentity();
        // 152, 175, 212 rgb
        glColor3f((152 / 256.0f), (175 / 256.0f), (212 / 256.0f));
        glBegin(GL_LINES);
        for (int i = 0; i < (cast - 1); ++i) {
            glVertex2f(trX2[i], trY2[i]);
            glVertex2f(trX2[i + 1], trY2[i + 1]);
        }
        glEnd();

        glLoadIdentity();
        // 152, 175, 212 rgb
        glColor3f((152 / 256.0f), (175 / 256.0f), (212 / 256.0f));
        glBegin(GL_LINES);
        for (int i = 0; i < (cast - 1); ++i) {
            glVertex2f(trX3[i], trY3[i]);
            glVertex2f(trX3[i + 1], trY3[i + 1]);
        }
        glEnd();
    }

    glutSwapBuffers();
}

int main(int argc, char **argv) {
    // Náhodné generovanie
    tt = time(0);
    srand((unsigned) time((time_t *) &tt));

    x10 = (float) (rand() % 12) - 6;
    y10 = (float) (rand() % 12) - 6;
    z10 = 0;

    x20 = (float) (rand() % 12) - 6;
    y20 = (float) (rand() % 12) - 6;
    z20 = 0;

    // Žltý bod
    x30 = (float) (-x11 - x21);
    y30 = (float) (-y11 - y21);
    z30 = (float) (-z11 - z21);

    x11 = x10;
    y11 = y10;
    z11 = z10;

    x21 = x20;
    y21 = y20;
    z21 = z20;

    x31 = x30;
    y31 = y30;
    z31 = z30;

    v1x = ((float)rand()/RAND_MAX)*(float)(0.5);
    v2x = ((float)rand()/RAND_MAX)*(float)(0.5);

    bool randbool1 = rand() & 1;
    bool randbool2 = rand() & 1;

    if(randbool1 == 0){
        v1x = v1x * (-1);
    }
    if(randbool2 == 0){
        v2x = v2x * (-1);
    }

    v3x = -v1x - v2x;

    v1y = ((float)rand()/RAND_MAX)*(float)(0.5);
    v2y = ((float)rand()/RAND_MAX)*(float)(0.5);

    bool randbool1y = rand() & 1;
    bool randbool2y = rand() & 1;

    if(randbool1y == 0){
        v1y = v1y * (-1);
    }
    if(randbool2y == 0){
        v2y = v2y * (-1);
    }

    v3y = -v1y - v2y;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);

    glutInitWindowSize(700, 700);
    glutInitWindowPosition(170, 50);
    glutCreateWindow("Uloha cislo 9 - Zaprazny");

    glClearColor(0.9f, 0.9f, 0.9f, 0.5f);

    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutTimerFunc(casKrok, posun, 0);

    glutMainLoop();
    return 0;
}
