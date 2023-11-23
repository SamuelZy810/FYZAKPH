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
const float casKrok = 25;
const float PI = 3.1415926f;
const float view = 6;
const float Lx = 2.5f;
const float Ly = 1.5f;
const float Hr = 0.35f;
const float radius = 0.075f * 2;
const float Vmax = 0.1f;

// Pomer stran
float pomStrSirka, pomStrVyska;

// Cas
float t = 0; // s - pre výpočty
time_t tt; // s - seed pre generovanie

// Suradnice guliciek
float x1 = 0, y = 0;
float x2 = 0, y2 = 0;
float x3 = 0, y3 = 0;

// Rychlosti guliciek
float v1x = 0, v1y = 0;
float v2x = 0, v2y = 0;
float v3x = 0, v3y = 0;

// Vektory
float rv12[2], rv13[2], rv23[2];

// Velkosti vektorov
float r12 = 0, r13 = 0, r23 = 0;

// Casy kolizii
float t1 = 0, t2 = 0, t3 = 0;
float t12 = 0, t13 = 0, t23 = 0;
int n12 = 0, n13 = 0, n23 = 0;

void posun(const int hod) {
    // Kód

    if (x1 >= (Lx - radius) || x1 <= (-Lx + radius)) v1x *= -1;
    if (y >= (Ly - radius) || y <= (-Ly + radius)) v1y *= -1;

    x1 = x1 + v1x;
    y = y + v1y;

    if (x2 >= (Lx - radius) || x2 <= (-Lx + radius)) v2x *= -1;
    if (y2 >= (Ly - radius) || y2 <= (-Ly + radius)) v2y *= -1;

    x2 = x2 + v2x;
    y2 = y2 + v2y;

    if (x3 >= (Lx - radius) || x3 <= (-Lx + radius)) v3x *= -1;
    if (y3 >= (Ly - radius) || y3 <= (-Ly + radius)) v3y *= -1;

    x3 = x3 + v3x;
    y3 = y3 + v3y;

    rv12[0] = x2 - x1;
    rv12[1] = y2 - y;
    r12 = sqrtf(powf(rv12[0], 2) + powf(rv12[1], 2));

    rv13[0] = x3 - x1;
    rv13[1] = y3 - y;
    r13 = sqrtf(powf(rv13[0], 2) + powf(rv13[1], 2));

    rv23[0] = x3 - x2;
    rv23[1] = y3 - y2;
    r23 = sqrtf(powf(rv23[0], 2) + powf(rv23[1], 2));

    t1 = (Lx - (x1 + radius)) / v1x;
    t2 = (Lx - (x2 + radius)) / v2x;
    t3 = (Lx - (x3 + radius)) / v2x;

    float skarv12 = rv12[0] * (v2x - v1x) + rv12[1] * (v2y - v1y);
    float skarv13 = rv13[0] * (v3x - v1x) + rv13[1] * (v3y - v1y);
    float skarv23 = rv23[0] * (v3x - v2x) + rv23[1] * (v3y - v2y);

    float velV12 = powf((sqrtf(powf((v2x - v1x), 2) + powf((v2y - v1y), 2))), 2);
    float velV13 = powf((sqrtf(powf((v3x - v1x), 2) + powf((v3y - v1y), 2))), 2);
    float velV23 = powf((sqrtf(powf((v3x - v2x), 2) + powf((v3y - v2y), 2))), 2);

    t12 = (1.0f/ velV12) * (-skarv12 - sqrtf(powf(skarv12, 2) - velV12 * (powf(r12, 2) - 4 * powf(radius, 2))));
    t13 = (1.0f/ velV13) * (-skarv13 - sqrtf(powf(skarv13, 2) - velV13 * (powf(r13, 2) - 4 * powf(radius, 2))));
    t23 = (1.0f/ velV23) * (-skarv23 - sqrtf(powf(skarv23, 2) - velV23 * (powf(r23, 2) - 4 * powf(radius, 2))));

    n12 = 1 + (int) (t12 / (casKrok / 1000.0f));
    n13 = 1 + (int) (t13 / (casKrok / 1000.0f));
    n23 = 1 + (int) (t23 / (casKrok / 1000.0f));

    if (n12 < casKrok && n12 > -casKrok) {

        float v12x = v2x - v1x, v12y = v2y - v1y;
        float zlozkaX = (rv12[0] * (rv12[0] * v12x + rv12[1] * v12y)) / (4 * powf(radius, 2));
        float zlozkaY = (rv12[1] * (rv12[0] * v12x + rv12[1] * v12y)) / (4 * powf(radius, 2));

        v1x = v1x + zlozkaX;
        v2x = v2x - zlozkaX;

        v1y = v1y + zlozkaY;
        v2y = v2y - zlozkaY;
    }

    if (n13 < casKrok && n13 > -casKrok) {
        float v13x = v3x - v1x, v13y = v3y - v1y;
        float zlozkaX = (rv13[0] * (rv13[0] * v13x + rv13[1] * v13y)) / (4 * powf(radius, 2));
        float zlozkaY = (rv13[1] * (rv13[0] * v13x + rv13[1] * v13y)) / (4 * powf(radius, 2));

        v1x = v1x + zlozkaX;
        v3x = v3x - zlozkaX;

        v1y = v1y + zlozkaY;
        v3y = v3y - zlozkaY;
    }

    if (n23 < casKrok && n23 > -casKrok) {
        float v23x = v3x - v2x, v23y = v3y - v2y;
        float zlozkaX = (rv23[0] * (rv23[0] * v23x + rv23[1] * v23y)) / (4 * powf(radius, 2));
        float zlozkaY = (rv23[1] * (rv23[0] * v23x + rv23[1] * v23y)) / (4 * powf(radius, 2));

        v2x = v2x + zlozkaX;
        v3x = v3x - zlozkaX;

        v2y = v2y + zlozkaY;
        v3y = v3y - zlozkaY;
    }

    if (v1x > Vmax) v1x = Vmax;
    else if (v1x < -Vmax) v1x = -Vmax;
    if (v1y > Vmax) v1y = Vmax;
    else if (v1y < -Vmax) v1y = -Vmax;

    if (v2x > Vmax) v2x = Vmax;
    else if (v2x < -Vmax) v2x = -Vmax;
    if (v2y > Vmax) v2y = Vmax;
    else if (v2y < -Vmax) v2y = -Vmax;

    if (v2x > Vmax) v2x = Vmax;
    else if (v2x < -Vmax) v2x = -Vmax;
    if (v2y > Vmax) v2y = Vmax;
    else if (v2y < -Vmax) v2y = -Vmax;

    t += (float) casKrok;
    glutPostRedisplay();
    glutTimerFunc(casKrok, posun, hod + 1); // rekurzívna funkcia
}

void resize (int sirka , int vyska ) {

    glViewport (0, 0, sirka, vyska);
    glMatrixMode ( GL_PROJECTION );

    glLoadIdentity();

    if (vyska == 0) vyska ++;

    pomStrVyska = (float) sirka / (float) vyska;

    gluOrtho2D ( (-0.5 * view) * pomStrVyska, (0.5 * view) * pomStrVyska, (-0.5 * view), (0.5 * view));

}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode ( GL_MODELVIEW );

    // Biliardový stôl
    glLoadIdentity();
    // Farba stola 62, 163, 84 rgb
    glColor3f((float) (62 / 256.0f), (float) (163 / 256.0f), (float) (84 / 256.0f));
    glBegin(GL_QUADS);
    glVertex2f(Lx, Ly);
    glVertex2f(-Lx, Ly);
    glVertex2f(-Lx, -Ly);
    glVertex2f(Lx, -Ly);
    glEnd();

    // Farba dreva okolo 125, 72, 12 rgb
    glColor3f((float) (125 / 256.0f), (float) (72 / 256.0f), (float) (12 / 256.0f));
    glBegin(GL_QUADS);
    glVertex2f(Lx + Hr, Ly + Hr);
    glVertex2f(-Lx - Hr, Ly + Hr);
    glVertex2f(-Lx - Hr, Ly);
    glVertex2f(Lx + Hr, Ly);

    glVertex2f(Lx + Hr, -Ly - Hr);
    glVertex2f(-Lx - Hr, -Ly - Hr);
    glVertex2f(-Lx - Hr, -Ly);
    glVertex2f(Lx + Hr, -Ly);

    glVertex2f(-Lx, Ly);
    glVertex2f(-Lx - Hr, Ly);
    glVertex2f(-Lx - Hr, -Ly);
    glVertex2f(-Lx, -Ly);

    glVertex2f(Lx, Ly);
    glVertex2f(Lx + Hr, Ly);
    glVertex2f(Lx + Hr, -Ly);
    glVertex2f(Lx, -Ly);
    glEnd();

    // Vykreslovanie guliciek
    // Gula č.1
    glLoadIdentity();
    glColor3f((float) (256 / 256.0f), (float) (256 / 256.0f), (float) (256 / 256.0f));
    glTranslatef(x1, y, 0);
    GLUquadric * quad;
    quad = gluNewQuadric();
    gluSphere(quad, radius, 100, 20);
    glEnd ();

    // Gula č.2
    glLoadIdentity();
    glColor3f((float) (0 / 256.0f), (float) (0 / 256.0f), (float) (0 / 256.0f));
    glTranslatef(x2, y2, 0);
    GLUquadric * quad2;
    quad2 = gluNewQuadric();
    gluSphere(quad2, radius, 100, 20);
    glEnd ();

    // Gula č.3
    glLoadIdentity();
    glColor3f((float) (256 / 256.0f), (float) (0 / 256.0f), (float) (0 / 256.0f));
    glTranslatef(x3, y3, 0);
    GLUquadric * quad3;
    quad3 = gluNewQuadric();
    gluSphere(quad3, radius, 100, 20);
    glEnd ();

    glutSwapBuffers();
}

double findMod(double a, double b)
{
    double mod;
    // Handling negative values
    if (a < 0)
        mod = -a;
    else
        mod =  a;
    if (b < 0)
        b = -b;

    // Finding mod by repeated subtraction

    while (mod >= b)
        mod = mod - b;

    // Sign of result typically depends
    // on sign of a.
    if (a < 0)
        return -mod;

    return mod;
}

int main(int argc, char **argv) {
    // Náhodné generovanie
    tt = time(0);
    srand((unsigned) time((time_t *) &tt));

    x1 = (float) (findMod((double) rand(), Lx) - radius);
    y = (float) (findMod((double) rand(), Ly) - radius);
    v1x = ((float) rand() / RAND_MAX) * (float) (0.05);
    v1y = ((float) rand() / RAND_MAX) * (float) (0.05);

    bool randbool1 = rand() & 1;
    bool randbool2 = rand() & 1;
    bool randbool3 = rand() & 1;
    bool randbool4 = rand() & 1;

    if(randbool1 == 0){
        x1 = x1 * (-1);
    }
    if(randbool2 == 0){
        y = y * (-1);
    }
    if(randbool3 == 0){
        v1x = v1x * (-1);
    }
    if(randbool4 == 0){
        v1y = v1y * (-1);
    }

    x2 = (float) (findMod((double) rand(), Lx) - radius);
    y2 = (float) (findMod((double) rand(), Ly) - radius);
    v2x = ((float) rand() / RAND_MAX) * (float) (0.05);
    v2y = ((float) rand() / RAND_MAX) * (float) (0.05);

    randbool1 = rand() & 1;
    randbool2 = rand() & 1;
    randbool3 = rand() & 1;
    randbool4 = rand() & 1;

    if(randbool1 == 0){
        x2 = x2 * (-1);
    }
    if(randbool2 == 0){
        y2 = y2 * (-1);
    }
    if(randbool3 == 0){
        v2x = v2x * (-1);
    }
    if(randbool4 == 0){
        v2y = v2y * (-1);
    }

    x3 = (float) (findMod((double) rand(), Lx) - radius);
    y3 = (float) (findMod((double) rand(), Ly) - radius);
    v3x = ((float) rand() / RAND_MAX) * (float) (0.05);
    v3y = ((float) rand() / RAND_MAX) * (float) (0.05);

    randbool1 = rand() & 1;
    randbool2 = rand() & 1;
    randbool3 = rand() & 1;
    randbool4 = rand() & 1;

    if(randbool1 == 0){
        x3 = x3 * (-1);
    }
    if(randbool2 == 0){
        y3 = y3 * (-1);
    }
    if(randbool3 == 0){
        v3x = v3x * (-1);
    }
    if(randbool4 == 0){
        v3y = v3y * (-1);
    }

   // printf("V1 (x = %.2f, y = %.2f), V2 (x = %.2f, y = %.2f), V3 (x = %.2f, y = %.2f)", v1x, v1y, v2x, v2y, v3x, v3y);

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