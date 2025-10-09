#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <functional>

bool isDrawing = false;
bool pencilTool = true;
//Store the points where the user clicked
std::vector<std::pair<float, float>> points;
std::vector<std::function<void()>> drawFunctions;

GLfloat currColorArray[3] = { 0.0f, 0.0f, 0.0f }; // Default color is black
GLfloat currLineWidth = 2.0f; // Default line width

void drawLineRealTime() {
    glColor3f(currColorArray[0], currColorArray[1], currColorArray[2]);
    glLineWidth(currLineWidth);

    glBegin(GL_LINE_STRIP);

    for (const auto& point : points)
    {
        glVertex2f(point.first, point.second);
    }

    glEnd();
}

void handleMouseClick(int button, int state, int x, int y)
{
    //x and y are in openGL coordinates
    //We need to convert them to our normalized device coordinates which are between -1 and 1

    float posX = (2.0f * static_cast<float>(x) / glutGet(GLUT_WINDOW_WIDTH)) - 1.0f;
    float posY = 1.0f - (2.0f * static_cast<float>(y) / glutGet(GLUT_WINDOW_HEIGHT));

    //std::cout << "Mouse Clicked at: (" << posX << ", " << posY << ")\n";
    //std::cout << "Mouse Clicked at: (" << x << ", " << y << ")\n";


    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            if (pencilTool)
            {
                points.emplace_back(posX, posY);
                isDrawing = true;
            }


        }
        else if (state == GLUT_UP)
        {
            if (pencilTool)
            {
                isDrawing = false;
                points.clear();
            }

            glutPostRedisplay(); // Request a redraw
        }
    }

}

void handleMouseMotion(int x, int y)
{
    float curX = (2.0f * static_cast<float>(x) / glutGet(GLUT_WINDOW_WIDTH)) - 1.0f;
    float curY = 1.0f - (2.0f * static_cast<float>(y) / glutGet(GLUT_WINDOW_HEIGHT));
    if (isDrawing && pencilTool)
    {
        points.emplace_back(curX, curY);
    }
    glutPostRedisplay(); // Request a redraw

}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // //Color which take 3 arguments 
    // //between 0.0 and 1.0, , its float because its 3"f"
    // glColor3f(1.0f, 0, 0.0f);

    // glLineWidth(2.0f); //Define the width of the line, need only for Line Loop drawing


    // //Define the size of the point
    // glPointSize(8.0f);

    // //Between glBegin and glEnd we define what we want to draw
    // //glBegin(GL_POINTS); // If we want to draw points

    // glBegin(GL_POLYGON); // If we want to draw lines

    // //Define the point position, location
    // //One vertex is enough for point drawing
    // glVertex2f(0.5f, 0.5f);


    // glVertex2f(-0.5f, -0.5f);

    // glVertex2f(-0.5f, 0.5f);
    // glVertex2f(0.5f, -0.5f);


    // glEnd();


    drawLineRealTime();
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

    glutMotionFunc(handleMouseMotion);

    glutDisplayFunc(display);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glutMainLoop();
    return 0;

}