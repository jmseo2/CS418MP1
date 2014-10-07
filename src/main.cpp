//
//  main.cpp
//  CS418MP1
//
//  Created by Seo Joon Young on 8/27/14.
//  Copyright (c) 2014 SeoJoon Young. All rights reserved.
//

#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <time.h>
#include <math.h>
#include <iostream>

using namespace std;

const int FPS = 30;
const int numVertices = 12;
const int numTriangles = 10;

int prevTime = 0, currTime = 0;
int frameCount = 0;
float theta = 0;

bool polygon = true;
bool wireframe = false;
bool border = false;

// initial vertices
GLfloat vertices[][2] = 
{
    {-0.6, 0.9},
    {0.6, 0.9},
    {-0.6, 0.6},
    {-0.2, 0.6},
    {0.2, 0.6},
    {0.6, 0.6},
    {-0.6, -0.6},
    {-0.2, -0.6},
    {0.2, -0.6},
    {0.6, -0.6},
    {-0.6, -0.9},
    {0.6, -0.9},
};

// fixed positions to translate each vertex to
GLfloat verticesTranslate[][2] = 
{
    {-0.8, 0.95},
    {0.75, 0.85},
    {-0.8, 0.69},
    {-0.3, 0.5},
    {0.2, 0.6},
    {0.7, 0.6},
    {-0.68, -0.67},
    {-0.3, -0.55},
    {0.25, -0.5},
    {0.6, -0.5},
    {-0.67, -0.8},
    {0.75, -0.95},
};

// index number of the triangle vertices
GLfloat triangleVertexIndex[][3] = 
{
    {0, 2, 3},
    {0, 1, 3},
    {1, 3, 4},
    {1, 4, 5},
    {3, 4, 8},
    {3, 7, 8},
    {6, 7, 10},
    {7, 10, 11},
    {7, 8, 11},
    {8, 9, 11},
};

// color of each vertex
GLfloat vertexColors[][3] = {
    {0.9, 0.35, 0.8},
    {0.85, 0.4, 0.45},
    {0.8, 0.45, 0.4},
    {0.75, 0.5, 0.35},
    {0.7, 0.55, 0.3},
    {0.65, 0.6, 0.2},
    {0.6, 0.65, 0.3},
    {0.55, 0.7, 0.35},
    {0.5, 0.75, 0.4},
    {0.45, 0.8, 0.45},
    {0.4, 0.85, 0.5},
    {0.35, 0.9, 0.8},
};

// This will be used to draw the border of the shape
GLfloat borderVertexIndex[] = {0, 2, 3, 7, 6, 10, 11, 9, 8, 4, 5, 1};

// draw I
void drawI() {
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    {
        for (int i = 0; i < numTriangles; i++) {
            for(int j = 0; j < 3; j++) {
                int idx = triangleVertexIndex[i][j];
                GLfloat dx = verticesTranslate[idx][0] - vertices[idx][0];
                GLfloat dy = verticesTranslate[idx][1] - vertices[idx][1];
                glColor3f(vertexColors[idx][0], vertexColors[idx][1], vertexColors[idx][2]);
                glVertex2f(vertices[idx][0] + sin(theta) * dx, vertices[idx][1] + sin(theta) * dy);
            }
        }
    }
    glEnd();
}


// draw triangle outlines
void drawITriangleOutlines() {
    glMatrixMode(GL_MODELVIEW);
    glLineWidth(5.0);
    glColor3f(0.0, 0.0, 0.0);
    for (int i = 0; i < numTriangles; i++) {
        glBegin(GL_LINE_LOOP);
        {
            for(int j = 0; j < 3; j++) {
                int idx = triangleVertexIndex[i][j];
                GLfloat dx = verticesTranslate[idx][0] - vertices[idx][0];
                GLfloat dy = verticesTranslate[idx][1] - vertices[idx][1];
                glVertex2f(vertices[idx][0] + sin(theta) * dx, vertices[idx][1] + sin(theta) * dy);
            }
        }
        glEnd();
    }
}

// draw border around I
void drawIBorder() {
    glLineWidth(20.0);
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINE_LOOP);
    {
        for (int i = 0;i < numVertices; i++) {
            int idx = borderVertexIndex[i];
            GLfloat dx = verticesTranslate[idx][0] - vertices[idx][0];
            GLfloat dy = verticesTranslate[idx][1] - vertices[idx][1];
            glVertex2f(vertices[idx][0] + sin(theta) * dx, vertices[idx][1] + sin(theta) * dy);
        }
    }
    glEnd();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void display() {
    frameCount++;
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(sin(theta) / 10.0, cos(theta) / 10.0, 0);
    glRotatef(theta * 10, 0.0, 0.0, 1.0);
    glScalef(fabs(cos(theta / 5.0)) + 0.2, fabs(cos(theta / 5.0)) + 0.2, 0);

    if (polygon) {
        drawI();
    }
    if (wireframe) {
        drawITriangleOutlines();
    }
    if (border) {
        drawIBorder();
    }
    
    glutSwapBuffers();

    currTime = glutGet(GLUT_ELAPSED_TIME);
    int elapsed = currTime - prevTime;
    if (elapsed > 1000) {
        float fps = frameCount / (elapsed / 1000.0f);
        printf("fps: %f\n", fps);
        prevTime = currTime;
        frameCount = 0;
    }
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
}

void timer(int n) {
    theta += 0.05;
    glutPostRedisplay();
    glutTimerFunc(1000.0 / FPS, timer, n);
}

void processKeys(unsigned char key, int x, int y) {
    switch(key) {
        case 'a':
            polygon = !polygon;
            break;
        case 's':
            wireframe = !wireframe;
            break;
        case 'd':
            border = !border;
            break;
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("MP1");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutTimerFunc(1000.0 / FPS, timer, FPS);
    glutKeyboardFunc(processKeys);
    
    init();
    
    glutMainLoop();
    return 0;
}