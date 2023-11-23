#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include <stdio.h>
#include <math.h>

// gravitacia
float const g = 9.81f;

// cas
float t;
float const casKrok = 15;

// vstupne parametre
float z0, v0, alpha, phi;

// vypocitane rychlosti
float v0xz, v0x, v0z, v0y;

// vypocitane suradnice
float x, z, y;


// rychlost v case
float vx, vz, vy;

void display() {
    glClearColor(187 / 256.0f, 138 / 256.0f, 91 / 256.0f, 0.2f);
    glClearDepth(1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    glBegin(GL_LINES);
    glColor3f(0.1f, 0.0f, 0.69f);

    glVertex3f(0, 0 ,0);
    glVertex3f(GLUT_WINDOW_WIDTH, 0, 0);

    glVertex3f(0, 0, 0);
    glVertex3f(0, GLUT_WINDOW_HEIGHT, 0);

    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, GLUT_WINDOW_DEPTH_SIZE);

    glColor3f(0.99f, 0.0f, 0.55f);
    glVertex3f(0, 0 ,0);
    glVertex3f(-GLUT_WINDOW_WIDTH, 0, 0);

    glVertex3f(0, 0, 0);
    glVertex3f(0, -GLUT_WINDOW_HEIGHT, 0);

    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, -GLUT_WINDOW_DEPTH_SIZE);
    glEnd();

    glLoadIdentity();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(x, 0, z);
    GLUquadric * smth;
    smth = gluNewQuadric();
    gluSphere(smth,0.3 ,1000,200);

    glLoadIdentity();
    glColor3f(0.0f, 0.0f, 1.0f);
    glTranslatef(x, y, z);
    GLUquadric * quad;
    quad = gluNewQuadric();
    gluSphere(quad,0.5 ,1000,200);
    glEnd ();

    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height) {
    GLfloat aspect = (GLfloat) width / (GLfloat) height;
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0f, aspect, 0.1f, 100.0f);
    gluLookAt(15.0, z0 + 10.0, 15.0,0.0,0.0, 0.0, 0.0, 1.0, 0.0);
}

void posun(const int hod) {
    t += casKrok;

    x = v0x * (t / 1000);
    z = v0z * (t / 1000);
    y = z0 + v0y * (t / 1000) - (0.5f * g * (t / 1000) * (t / 1000));

    vy = v0y - g * (t / 1000);

    if (y <= 0) exit(1);

    glutPostRedisplay();
    glutTimerFunc(casKrok, posun, hod + 1); // rekurzívna funkcia
}

int main( int argc, char **argv ) {

    if (argc >= 4) {
        z0 = atof(argv[1]);
        v0 = atof(argv[2]);
        alpha = atof(argv[3]);
        phi = atof(argv[4]);

        v0xz = v0 * cosf(alpha);
        vx = v0x = v0xz * cosf(phi);
        vz = v0z = v0xz * sinf(phi);
        v0y = v0 * sinf(alpha);
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glEnable(GL_DEPTH_TEST);

    glutInitWindowSize(640, 480);
    glutInitWindowPosition(50, 50);
    glClearColor(0.05f, 0.25f, 0.01f, 0.5f);
    glClearDepth(1.0f);

    glutCreateWindow("Samuel Zaprazny - Uloha 6");
    glutDisplayFunc(display);
    glutTimerFunc(casKrok, posun, 0);

    glutReshapeFunc(reshape);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glutMainLoop();
    return 0;
}