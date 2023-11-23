#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <windows.h>

const int casKrok = 20;
const float Lmax = 20.0;

float pTroj = 0.0, pStvor = 0.0, pKruhX = 0.0, pKruhY = 0.0;
float krok1 = 0.05, krok2 = 0.025, krok3 = 0.0, krok4 = 0.0;
int casStv = 0, casKruh = 0, count = 1;

void posun (const int hod) {
    casStv += casKrok;
    casKruh += casKrok;

    if (casStv > 3000) {
        krok2 *= -1;
        casStv = 0;
    }

    if (casKruh < 4000) {
        if (casKruh < 2000) {
            krok3 = 0.0;
            krok4 = count * 0.025;
        } else if (casKruh >= 2000) {
            if (casKruh == 2000) count = count * (-1);
            krok3 = count * 0.025;
            krok4 = 0.0;
        }
    } else {
        casKruh = 0;
    }

    pTroj += krok1;
    pStvor += krok2;

    pKruhX += krok3;
    pKruhY += krok4;

    glutPostRedisplay();
    glutTimerFunc(casKrok, posun, hod + 1);
}

void obsluhaResize (int sirka , int vyska )
{

    glViewport (0, 0, sirka , vyska );
    glMatrixMode ( GL_PROJECTION );
    glLoadIdentity();

    if ( sirka == 0) sirka ++;

    const float pomstr = ((float) vyska )/ sirka ;

    gluOrtho2D ( -0.5 * Lmax, 0.5 * Lmax * pomstr, -0.5 * Lmax, 0.5 * Lmax * pomstr);

}

void callBackFunc(void) {

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.316, 0.707, 0.094);
    glBegin(GL_TRIANGLES);
    glVertex2f(0 + pTroj, 0 + pTroj);
    glVertex2f(3.5 + pTroj, 3.5 + pTroj);
    glVertex2f(3.5 + pTroj, 0 + pTroj);
    glEnd();

    glColor3f(0.707, 0.667, 0.093);
    glBegin(GL_QUADS);
    glVertex2f(0 + pStvor, 2.4);
    glVertex2f(2.4 + pStvor, 2.4);
    glVertex2f(2.4 + pStvor, 0);
    glVertex2f(0 + pStvor, 0);
    glEnd();

    glColor3f(0.656, 0.195, 0.25);
    glBegin(GL_QUADS);
    glVertex2f(1 + pKruhX, 1 + pKruhY);
    glVertex2f(2 + pKruhX, 1 + pKruhY);
    glVertex2f(2 + pKruhX, 0 + pKruhY);
    glVertex2f(1 + pKruhX, 0 + pKruhY);
    glEnd();

    /** Medzi toto sa pise kod */
    glutSwapBuffers();
}

int main (int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);

    glutInitWindowSize(700, 700);
    glutInitWindowPosition(450, 50);
    glutCreateWindow("Uloha cislo 1 - Zaprazny");

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.9, 0.25, 0.2, 0.0);

    glutDisplayFunc(callBackFunc);
    glutReshapeFunc(obsluhaResize);
    glutTimerFunc(casKrok, posun, 0);

    glutMainLoop();
    return 0;
}
