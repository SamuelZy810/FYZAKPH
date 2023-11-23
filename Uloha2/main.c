// Standard libraries
#include <stdio.h>
#include <stdlib.h>

// GL libraries
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

// Konštanty
const int casKrok = 15;
const float Lmax = 700;

// Vstupne hodnoty
float x0, v01, v02, a1, a2;

// Suradnice
float x1 = 0, x2 = 0;

// Cas
float t = 0;

// Rychlost
float v1, v2;

// Subor
FILE * f = '\0';

void posun(const int hod) {
    t += 15;

    x1 = (v01 * (t/1000)) + ((a1 * (t/1000) * (t/1000)) * 1/2);
    x2 = x0 + (v02 * (t/1000)) + ((a2 * (t/1000) * (t/1000)) * 1/2);

    v1 = v01 + a1 * t/1000;
    v2 = v02 + a2 * t/1000;

//    printf("Hodnota x1: %.3f v case %.2f sekund || Rychlost = %.2f\n", x1, t/1000, v1);
//    printf("Hodnota x2: %.3f v case %.2f sekund || Rychlost = %.2f\n\n", x2, t/1000, v2);

    if (t > 30000) {
        fclose(f);
        exit(0);
    }

    if (x1 > x2) {
        fclose(f);
        exit(2);
    }

    fprintf(f, "%.2f %.2f %.2f %.2f %.2f\n", t/1000, x1, v1, x2, v2);

    glutPostRedisplay();
    glutTimerFunc(casKrok, posun, hod + 1); // rekurzívna funkcia
}

void resize (int sirka , int vyska )
{

    glViewport (0, 0, sirka, vyska);
    glMatrixMode ( GL_PROJECTION );
    glLoadIdentity();

    if ( sirka == 0) sirka ++;

    const float pomstr = ((float) vyska )/ sirka ;

    gluOrtho2D ( 0, 300 * pomstr, 0, 175 * pomstr);

}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode ( GL_MODELVIEW );

    glLoadIdentity();
    glColor3f(0.707, 0.667, 0.093);
    glTranslatef(x1, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(0, 5);
    glVertex2f(5, 5);
    glVertex2f(5, 0);
    glVertex2f(0, 0);
    glEnd();

    glLoadIdentity();
    glColor3f(0.656, 0.195, 0.25);
    glTranslatef(x2, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(0, 5);
    glVertex2f(5, 5);
    glVertex2f(5, 0);
    glVertex2f(0, 0);
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char **argv) {
    x0 = atof(argv[1]); v01 = atof(argv[2]); a1 = atof(argv[3]); v02 = atof(argv[4]); a2 = atof(argv[5]);

    if (f == '\0') {
        f = fopen("vystup.dat", "w");
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);

    glutInitWindowSize(1200, 700);
    glutInitWindowPosition(170, 50);
    glutCreateWindow("Uloha cislo 2 - Zaprazny");

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.9, 0.9, 0.9, 0.5);

    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutTimerFunc(casKrok, posun, 0);

    glutMainLoop();
    fclose(f);
    return 0;
}
