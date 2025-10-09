#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>



void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    //Color which take 3 arguments 
    //between 0.0 and 1.0, , its float because its 3"f"
    glColor3f(1.0f, 0, 0.0f);

    glLineWidth(2.0f); //Define the width of the line, need only for Line Loop drawing


    //Define the size of the point
    glPointSize(8.0f);

    //Between glBegin and glEnd we define what we want to draw
    //glBegin(GL_POINTS); // If we want to draw points

    glBegin(GL_POLYGON); // If we want to draw lines

    //Define the point position, location
    //One vertex is enough for point drawing
    glVertex2f(0.5f, 0.5f);


    glVertex2f(-0.5f, -0.5f);

    glVertex2f(-0.5f, 0.5f);
    glVertex2f(0.5f, -0.5f);


    glEnd();

    glutSwapBuffers();

}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Paint");
    glutPositionWindow(100, 50);

    glutMouseFunc(handleMouseClick);

    glutDisplayFunc(display);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glutMainLoop();
    return 0;

}