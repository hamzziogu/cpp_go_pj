#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <cmath>

float windowwidth = 800;
float windowheight = 800;
float x_width = windowwidth / 2;
float y_height = windowheight / 2;

float brownR = (float)152/255;
float brownG = (float)102/255;
float brownB = (float)52/255;

bool init = 1, restart = 1;
static float mat[15][15][3];
static char Turn = 0;
static int widthWeight = 1.2;

float origin_point_x = 0.065f;
float origin_potin_y = 0.065f;

float Distance = 0, minDistance = 3.f,
minDistanceX = 0, minDistanceY = 0;
int position_x, position_y;

float scale_x = 2.0;
float scale_y = 2.0;
float transf_x = -0.47;
float transf_y = -0.47;

float radius = 0.03f;

void draw_line() 
{

    glClearColor(brownR, brownG, brownB, 1.0f);
    glLoadIdentity();
    glScalef(scale_x, scale_y, 0);
    glTranslatef(transf_x, transf_y, 0);
    glColor3f(0.0f, 0.0f, 1.0f);
    glLineWidth(2.0);

    for (int i = 0; i < 15; i++)
    {
        glBegin(GL_LINES);
        glVertex2f(0.f, (float)i / 15);
        //glVertex2f(1.f - origin_point_x  , (float)i/15);
        glVertex2f(1.f - origin_point_x, (float)i / 15);
        glEnd();
    }

    for (int i = 0; i < 15; i++)
    {
        glBegin(GL_LINES);
        glVertex2f((float)i / 15.f, 0.f);
        //glVertex2f((float)i / 15.f, 1.0f - origin_potin_y);
        glVertex2f((float)i / 15.f, 1.0f - origin_potin_y);
        glEnd();
    }

    glFlush();
}
void draw_circle()
{
    for (int y = 0; y < 15; y++)
        for (int x = 0; x < 15; x++)
        {
            if(mat[y][x][2] != 0)
                if (mat[y][x][2] == 1)
                {
                    glMatrixMode(GL_MODELVIEW);
                    glLoadIdentity();
                    glScalef(scale_x, scale_y, 0);
                    glTranslatef(transf_x, transf_y, 0);
                    glTranslatef(mat[y][x][0], mat[y][x][1], 0);
                    glColor3f(0.0f, 0.0f, 0.0f);
                    glBegin(GL_POLYGON);
                    for (float fAngle = 0.f; fAngle < 360.f; fAngle += 1.0f) {
                        glVertex2f(cos(fAngle) * radius, sin(fAngle) * radius);

                    }
                    glEnd();
                    glPopMatrix();
                }
                else
                {   
                    glMatrixMode(GL_MODELVIEW);
                    glLoadIdentity();
                    glScalef(scale_x, scale_y, 0);
                    glTranslatef(transf_x, transf_y, 0);
                    glTranslatef(mat[y][x][0], mat[y][x][1], 0);
                    glColor3f(1.0f, 1.0f, 1.0f);
                    glBegin(GL_POLYGON);
                    for (float fAngle = 0.f; fAngle < 360.f; fAngle += 1.0f) {
                        glVertex2f(cos(fAngle) * radius, sin(fAngle) * radius);

                    }
                    glEnd();
                    glPopMatrix();
                }
        }
}
void initialization(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(windowwidth, windowheight);
    glutCreateWindow("OpenGL");
    glClearColor(brownR, brownG, brownB, 1.0f);
    glFlush();
    //gluOrtho2D(-0.09f, 1.f, -0.09f, 1.f);

    for (int y = 1; y <= 15; y++)
        for (int x = 0; x < 15; x++)
        {
            mat[y-1][x][0] = ((float)x / 15 );
            mat[y-1][x][1] = 1.f - ((float)y / 15 );
        }

    init = 0;
}
void game_initialization()
{
    for (int y = 0; y < 15; y++)
        for (int x = 0; x < 15; x++)
        {
            mat[y][x][2] = 0;
        }
    //glClear(GL_COLOR_BUFFER_BIT);
    draw_line();
    restart = 0;
}

void mouse_move(int pointX, int pointY)
{
        
        //std::cout << pointX << " " << pointY << "\n" << std::endl;
        float XX = (float)(pointX-20) / 800;
        float YY = 0.97f - (float)(pointY) / 800;

        for (int y = 0; y < 15; y++)
            for (int x = 0; x < 15; x++)
            {
                Distance = pow(mat[y][x][0] - XX, 2) + pow(mat[y][x][1] - YY, 2);
                if (minDistance > Distance)
                {
                    minDistance = Distance;
                    minDistanceX = mat[y][x][0];
                    minDistanceY = mat[y][x][1];
                    position_x = x;
                    position_y = y;
                }
            }
        
        minDistance = 3.0f;

        glClear(GL_COLOR_BUFFER_BIT);
        glPushMatrix();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glScalef(scale_x, scale_y, 0);
        glTranslatef(transf_x, transf_y, 0);

        draw_line();

        glColor3f(0.9f, 0.0f, 0.0f);
        glPointSize(10.0);
        glBegin(GL_POINTS);
        glVertex2f(minDistanceX, minDistanceY);
        glEnd();

        glPopMatrix();
        draw_circle();

        glFinish();
}
void click(int A, int B, int px, int py)
{
    
    if (B == GLUT_DOWN)
        if (mat[position_y][position_x][2] == 0)
        {
            /*for (int y = 0; y < 15; y++) {
                for (int x = 0; x < 15; x++)
                {
                    std::cout << mat[y][x][2] << ", " << std::endl;
                }
                printf("\n");
            }*/
            
            if (Turn == 0) {
                mat[position_y][position_x][2] = 1;
                Turn = 1;
            }
            else {
                mat[position_y][position_x][2] = 2;
                Turn = 0;
            }
        }
    
}
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'q':
    case 'Q':
        exit(0);
        break;
    case 's':
    case 'S':
    {
        restart = 1;
        //glutMainLoop();
        break;
    }
    default:
        break;
    }
}
void display() {


    //glViewport(0, 0, 800, 800);

    


    glutPassiveMotionFunc(mouse_move);
    glutMouseFunc(click);
    glutKeyboardFunc(keyboard);
}



int main(int argc, char** argv)

{
    if(init)
        initialization(argc, argv);
    if(restart)
        game_initialization();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;

}