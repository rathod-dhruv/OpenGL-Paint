#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <functional>

bool isDrawing, isErasing, isLineDrawing = false;
bool pencilTool, eraserTool, lineTool, rectangleTool, paintTool = false;


//Store the points where the user clicked
std::vector<std::pair<float, float>> points;
std::vector<std::function<void()>> drawFunctions;
std::vector<std::pair<float, float>> eraserCurves;
std::vector<std::pair<float, float>> lineCurves(2);
std::vector<std::pair<float, float>> lineCurves1(2);

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

void drawLine(std::vector<std::pair<float, float>> linePoints, const float* colorArray, float lineWidth)
{
    glColor3f(colorArray[0], colorArray[1], colorArray[2]);
    glLineWidth(lineWidth);

    glBegin(GL_LINE_STRIP);

    for (const auto& point : linePoints)
    {
        glVertex2f(point.first, point.second);
    }

    glEnd();
}

void eraseLineRealTime()
{

    glColor3f(1.0f, 1.0f, 1.0f); // Set color to white for erasing
    glPointSize(20.0f); // Use fixed point size for erasing

    glBegin(GL_POINTS);
    for (const auto& era : eraserCurves)
    {
        glVertex2f(era.first, era.second);
    }
    glEnd();

}

void drawStraightLineRealtime()
{
    glColor3f(currColorArray[0], currColorArray[1], currColorArray[2]);
    glLineWidth(currLineWidth);

    glBegin(GL_LINES);

    glVertex2f(lineCurves[0].first, lineCurves[0].second);
    glVertex2f(lineCurves[1].first, lineCurves[1].second);

    glEnd();
}


void DrawStraightLine(std::vector<std::pair<float, float>> linePoints, const float* colorArray, float lineWidth)
{
    glColor3f(colorArray[0], colorArray[1], colorArray[2]);
    glLineWidth(lineWidth);

    glBegin(GL_LINES);

    glVertex2f(linePoints[0].first, linePoints[0].second);
    glVertex2f(linePoints[1].first, linePoints[1].second);

    glEnd();
}

void EraserTool(std::vector<std::pair<float, float>> erasePoints)
{
    glColor3f(1.0f, 1.0f, 1.0f); // Set color to white for erasing
    glPointSize(20.0f); // Use fixed point size for erasing

    glBegin(GL_POINTS);
    for (const auto& era : erasePoints)
    {
        glVertex2f(era.first, era.second);
    }
    glEnd();
}


void setBool(bool eraser, bool pencil, bool line, bool rectangle, bool paint)
{
    eraserTool = eraser;
    pencilTool = pencil;
    lineTool = line;
    rectangleTool = rectangle;
    paintTool = paint;
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'e':
    case 'E':
        setBool(true, false, false, false, false);
        break;
    case 'p':
    case 'P':
        setBool(false, true, false, false, false);
        break;
    case 'l':
    case 'L':
        setBool(false, false, true, false, false);
        break;
    case 's':
    case 'S':
        setBool(false, false, false, true, false);
        break;
    case 'a':
    case 'A':
        setBool(false, false, false, false, true);
        glutPostRedisplay(); // Request a redraw
        break;


    case 'g':
    case 'G':
        currColorArray[0] = 0.0f; // Green
        currColorArray[1] = 1.0f;
        currColorArray[2] = 0.0f;
        break;
    case 'b':
    case 'B':
        currColorArray[0] = 0.0f; // black
        currColorArray[1] = 0.0f;
        currColorArray[2] = 0.0f;
        break;
    case 'r':
    case 'R':
        currColorArray[0] = 1.0f; // Red
        currColorArray[1] = 0.0f;
        currColorArray[2] = 0.0f;
        break;

    case 'y':
    case 'Y':
        currColorArray[0] = 1.0f; // Yellow
        currColorArray[1] = 1.0f;
        currColorArray[2] = 0.0f;
        break;
    case 'z':
    case 'Z':
        if (!drawFunctions.empty())
        {
            drawFunctions.pop_back();
            glutPostRedisplay(); // Request a redraw
        }
        break;
    default:
        break;
    }

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

            if (eraserTool)
            {
                eraserCurves.emplace_back(posX, posY);
                isErasing = true;
            }

            if (lineTool)
            {
                lineCurves.clear();
                lineCurves.resize(2);
                lineCurves[0] = std::make_pair(posX, posY);
                isLineDrawing = true;
            }

        }
        else if (state == GLUT_UP)
        {
            if (pencilTool)
            {
                isDrawing = false;
                std::vector<std::pair<float, float>> tempPoints = points; // Capture current points
                float tempColorArray[3] = { currColorArray[0], currColorArray[1], currColorArray[2] }; // Capture current color
                float tempLineWidth = currLineWidth; // Capture current line width  

                drawFunctions.push_back([tempPoints, tempColorArray, tempLineWidth]() {
                    float colorArr[3] = { tempColorArray[0], tempColorArray[1], tempColorArray[2] };
                    drawLine(tempPoints, colorArr, tempLineWidth);
                    });

                points.clear();

            }

            if (eraserTool)
            {
                isErasing = false;
                std::vector<std::pair<float, float>> tempErasePoints = eraserCurves; // Capture current points

                drawFunctions.push_back([tempErasePoints]() {
                    EraserTool(tempErasePoints);
                    });

                eraserCurves.clear();

            }

            if (lineTool)
            {
                isLineDrawing = false;
                std::vector<std::pair<float, float>> tempLinePoints = lineCurves;
                float tempColorArray[3] = { currColorArray[0], currColorArray[1], currColorArray[2] }; // Capture current color
                float tempLineWidth = currLineWidth; // Capture current line width

                drawFunctions.push_back([tempLinePoints, tempColorArray, tempLineWidth]() {
                    float colorArr[3] = { tempColorArray[0], tempColorArray[1], tempColorArray[2] };
                    drawLine(tempLinePoints, colorArr, tempLineWidth);
                    });

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

    if (isErasing && eraserTool)
    {
        eraserCurves.emplace_back(curX, curY);
    }
    if (isLineDrawing && lineTool)
    {
        lineCurves[1] = std::make_pair(curX, curY);
    }

    glutPostRedisplay(); // Request a redraw

}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    for (const auto& func : drawFunctions)
    {
        func(); // Call each stored drawing function
    }

    drawLineRealTime();
    eraseLineRealTime();
    drawStraightLineRealtime();

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
    glutKeyboardFunc(keyboard);
    glutMotionFunc(handleMouseMotion);

    glutDisplayFunc(display);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glutMainLoop();
    return 0;

}