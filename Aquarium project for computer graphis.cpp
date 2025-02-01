#include <GL/glut.h>
#include <cmath>
#include <cstdlib> // For random number generation

// Function to draw a single algae (wavy plant)
void drawAlgae(float x, float y) {
    glColor3f(0.0f, 0.5f, 0.0f); 
    glBegin(GL_LINE_STRIP);
    for (float i = 0; i <= 1.0f; i += 0.1f) {
        glVertex2f(x + 0.02f * sin(i * 10), y + i * 0.2f); // Wavy effect
    }
    glEnd();
}

// Function to draw a full fish with body, tail, fins, and eye
void drawFish(float x, float y, float r, float g, float b) {
    // Body of the fish (ellipse)
    glColor3f(r, g, b); // Fish color
    glBegin(GL_POLYGON);
    for (float angle = 0; angle <= 2 * M_PI; angle += 0.1) {
        glVertex2f(x + 0.1f * cos(angle), y + 0.05f * sin(angle)); 
    }
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(x - 0.1f, y);          
    glVertex2f(x - 0.15f, y - 0.05f);
    glVertex2f(x - 0.15f, y + 0.05f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(x - 0.05f, y + 0.05f); // Base center of the body
    glVertex2f(x + 0.02f, y + 0.1f);  // Tip of the top fin
    glVertex2f(x - 0.1f, y + 0.1f);   // Base left
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(x - 0.05f, y - 0.05f); // Base center of the body
    glVertex2f(x + 0.02f, y - 0.1f);  // Tip of the bottom fin
    glVertex2f(x - 0.1f, y - 0.1f);   // Base left
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Black for the eye
    glBegin(GL_POLYGON);
    for (float angle = 0; angle <= 2 * M_PI; angle += 0.1) {
        glVertex2f(x + 0.05f + 0.01f * cos(angle), y + 0.01f * sin(angle));
    }
    glEnd();
}

void drawSeaFloor() {
    glColor3f(0.0f, 0.8f, 0.0f); 
    for (float x = -1.0f; x <= 1.0f; x += 0.1f) {
        glBegin(GL_TRIANGLES);
        glVertex2f(x, -0.8f);       
        glVertex2f(x - 0.03f, -0.7f);
        glVertex2f(x + 0.03f, -0.7f);
        glEnd();
    }

    glColor3f(0.5f, 0.35f, 0.05f);
    for (float x = -0.9f; x <= 0.9f; x += 0.3f) {
        glBegin(GL_POLYGON);
        glVertex2f(x, -0.85f);
        glVertex2f(x + 0.05f, -0.85f);
        glVertex2f(x + 0.03f, -0.8f);
        glVertex2f(x - 0.03f, -0.8f);
        glEnd();
    }

    for (float x = -1.0f; x <= 1.0f; x += 0.2f) {
        drawAlgae(x, -0.8f);
    }
}

void drawBubble(float x, float y) {
    glColor3f(0.8f, 0.8f, 1.0f); 
    glBegin(GL_POLYGON);
    for (float angle = 0; angle <= 2 * M_PI; angle += 0.1) {
        glVertex2f(x + 0.02f * cos(angle), y + 0.02f * sin(angle));
    }
    glEnd();
}

float bubbleX[5] = { -0.5f, -0.2f, 0.0f, 0.4f, 0.7f };
float bubbleY[5] = { -0.7f, -0.8f, -0.75f, -0.8f, -0.85f };

float fishX = -1.0f; 
float fishY = 0.0f; 
float speed = 0.005f; 

void display() {
    glClear(GL_COLOR_BUFFER_BIT); 
    drawSeaFloor();

    for (int i = 0; i < 5; i++) {
        drawBubble(bubbleX[i], bubbleY[i]);
    }
    drawFish(fishX, fishY, 1.0f, 0.0f, 0.0f);       
    drawFish(fishX - 0.3f, fishY + 0.2f, 0.0f, 1.0f, 0.0f); 
    drawFish(fishX - 0.6f, fishY - 0.2f, 0.0f, 0.0f, 1.0f); 

    glutSwapBuffers();
}

void update(int value) {
    fishX += speed;
    if (fishX > 1.2f) { 
        fishX = -1.2f;
    }

    for (int i = 0; i < 5; i++) {
        bubbleY[i] += 0.01f; 
        if (bubbleY[i] > 1.0f) {
            bubbleY[i] = -0.8f;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void init() {
    glClearColor(0.0f, 0.0f, 0.2f, 1.0f); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); 
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);              
    glutCreateWindow("2D Fish Animation with Algae and Bubbles");

    init();                                    
    glutDisplayFunc(display);                  
    glutTimerFunc(16, update, 0);              
    glutMainLoop();                           
    return 0;
}
