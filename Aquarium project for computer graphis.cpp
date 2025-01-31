#include <GL/glut.h>
#include <cmath>
#include <cstdlib> // For random number generation

// Function to draw a single algae (wavy plant)
void drawAlgae(float x, float y) {
    glColor3f(0.0f, 0.5f, 0.0f); // Dark green for algae
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
        glVertex2f(x + 0.1f * cos(angle), y + 0.05f * sin(angle)); // Ellipse shape
    }
    glEnd();

    // Tail of the fish (triangle)
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 0.1f, y);          // Tip of the tail
    glVertex2f(x - 0.15f, y - 0.05f); // Bottom of the tail
    glVertex2f(x - 0.15f, y + 0.05f); // Top of the tail
    glEnd();

    // Top fin of the fish (small triangle)
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 0.05f, y + 0.05f); // Base center of the body
    glVertex2f(x + 0.02f, y + 0.1f);  // Tip of the top fin
    glVertex2f(x - 0.1f, y + 0.1f);   // Base left
    glEnd();

    // Bottom fin of the fish (small triangle)
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 0.05f, y - 0.05f); // Base center of the body
    glVertex2f(x + 0.02f, y - 0.1f);  // Tip of the bottom fin
    glVertex2f(x - 0.1f, y - 0.1f);   // Base left
    glEnd();

    // Eye of the fish (small circle)
    glColor3f(0.0f, 0.0f, 0.0f); // Black for the eye
    glBegin(GL_POLYGON);
    for (float angle = 0; angle <= 2 * M_PI; angle += 0.1) {
        glVertex2f(x + 0.05f + 0.01f * cos(angle), y + 0.01f * sin(angle));
    }
    glEnd();
}

// Function to draw the sea floor (grass, rocks, and algae)
void drawSeaFloor() {
    // Grass (plants at the bottom)
    glColor3f(0.0f, 0.8f, 0.0f); // Green for grass
    for (float x = -1.0f; x <= 1.0f; x += 0.1f) {
        glBegin(GL_TRIANGLES);
        glVertex2f(x, -0.8f);       // Bottom of grass
        glVertex2f(x - 0.03f, -0.7f); // Left tip of grass blade
        glVertex2f(x + 0.03f, -0.7f); // Right tip of grass blade
        glEnd();
    }

    // Rocks at the bottom
    glColor3f(0.5f, 0.35f, 0.05f); // Brown for rocks
    for (float x = -0.9f; x <= 0.9f; x += 0.3f) {
        glBegin(GL_POLYGON);
        glVertex2f(x, -0.85f);
        glVertex2f(x + 0.05f, -0.85f);
        glVertex2f(x + 0.03f, -0.8f);
        glVertex2f(x - 0.03f, -0.8f);
        glEnd();
    }

    // Algae at the bottom
    for (float x = -1.0f; x <= 1.0f; x += 0.2f) {
        drawAlgae(x, -0.8f);
    }
}

// Function to draw bubbles
void drawBubble(float x, float y) {
    glColor3f(0.8f, 0.8f, 1.0f); // Light blue for bubbles
    glBegin(GL_POLYGON);
    for (float angle = 0; angle <= 2 * M_PI; angle += 0.1) {
        glVertex2f(x + 0.02f * cos(angle), y + 0.02f * sin(angle)); // Circle shape
    }
    glEnd();
}

// Bubble positions
float bubbleX[5] = { -0.5f, -0.2f, 0.0f, 0.4f, 0.7f };
float bubbleY[5] = { -0.7f, -0.8f, -0.75f, -0.8f, -0.85f };

// Fish position and direction
float fishX = -1.0f; // Initial X position
float fishY = 0.0f;  // Initial Y position
float speed = 0.005f; // Speed of fish movement

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

    // Draw the sea floor
    drawSeaFloor();

    // Draw bubbles
    for (int i = 0; i < 5; i++) {
        drawBubble(bubbleX[i], bubbleY[i]);
    }

    // Draw moving fish
    drawFish(fishX, fishY, 1.0f, 0.0f, 0.0f);        // Red fish
    drawFish(fishX - 0.3f, fishY + 0.2f, 0.0f, 1.0f, 0.0f); // Green fish
    drawFish(fishX - 0.6f, fishY - 0.2f, 0.0f, 0.0f, 1.0f); // Blue fish

    glutSwapBuffers(); // Swap buffers for smooth animation
}

// Timer function to update animation
void update(int value) {
    // Update fish position
    fishX += speed;
    if (fishX > 1.2f) { // Reset position when fish moves out of view
        fishX = -1.2f;
    }

    // Update bubbles
    for (int i = 0; i < 5; i++) {
        bubbleY[i] += 0.01f; // Move bubbles upwards
        if (bubbleY[i] > 1.0f) { // Reset bubble position when it moves out of view
            bubbleY[i] = -0.8f;
        }
    }

    glutPostRedisplay();          // Redraw the scene
    glutTimerFunc(16, update, 0); // Call update after 16ms (~60FPS)
}

// Initialization function
void init() {
    glClearColor(0.0f, 0.0f, 0.2f, 1.0f); // Set background color (dark blue)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Set up 2D orthographic view
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);              // Window size
    glutCreateWindow("2D Fish Animation with Algae and Bubbles");     // Window title

    init();                                    // Initialize OpenGL
    glutDisplayFunc(display);                  // Set display function
    glutTimerFunc(16, update, 0);              // Set timer for animation
    glutMainLoop();                            // Enter the event loop

    return 0;
}