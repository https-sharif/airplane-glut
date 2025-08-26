#ifdef _WIN32
  #include <windows.h>
  #include <GL/glut.h>
#else
  #include <GL/glut.h>
#endif

#include <math.h>

float bgOffset = 0.0f;

void drawLine(int x0, int y0, int x1, int y1, float r, float g, float b) {
    glColor3f(r, g, b);
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    glBegin(GL_POINTS);
    while (1) {
        glVertex2i(x0, y0);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx)  { err += dx; y0 += sy; }
    }
    glEnd();
}

void drawCircle(int xc, int yc, int rd, float r, float g, float b) {
   int numSegments = 50;

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(r, g, b);
    glVertex2f(xc, yc);

    for (int i = 0; i <= numSegments; i++) {
        float theta = 2.0f * 3.14159f * i / numSegments;
        float x = xc + rd * cosf(theta);
        float y = yc + rd * sinf(theta);
        glVertex2f(x, y);
    }

    glEnd();
}

void drawSky() {
    glBegin(GL_QUADS);
    
    glColor3f(0.6f, 0.85f, 1.0f);
    glVertex2f(-4.0f, 1.0f);
    
    glColor3f(0.6f, 0.85f, 1.0f);
    glVertex2f(4.0f, 1.0f);
    
    glColor3f(0.2f, 0.5f, 0.8f);
    glVertex2f(4.0f, -1.0f);
    
    glColor3f(0.85f, 0.95f, 1.0f);
    glVertex2f(-4.0f, -1.0f);
    
    glEnd();
}

void drawCloud(float x, float y, float size) {
    glColor3f(0.95f, 0.95f, 1.0f);
    
    for (int i = 0; i < 5; i++) {
        float cx = x + (i - 2) * size * 0.3f;
        float cy = y + sinf(i * 1.5f) * size * 0.1f;
        float radius = size * (0.8f + 0.4f * sinf(i * 2.0f));
        
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int j = 0; j <= 25; j++) {
            float theta = j * 2.0f * 3.14159f / 25;
            float cloudX = cx + radius * cosf(theta);
            float cloudY = cy + radius * 0.7f * sinf(theta);
            glVertex2f(cloudX, cloudY);
        }
        glEnd();
    }
}

void drawClouds() {
    float cloudOffset = bgOffset * 5.0f;

    drawCloud(-2.5f + cloudOffset,  0.70f, 0.15f);
    drawCloud( 1.2f + cloudOffset,  0.85f, 0.12f);
    drawCloud(-0.5f + cloudOffset,  0.40f, 0.18f);
    drawCloud( 2.8f + cloudOffset, -0.10f, 0.14f);
    drawCloud(-3.8f + cloudOffset, -0.25f, 0.16f);
    drawCloud( 0.0f + cloudOffset, -0.50f, 0.20f);

    float wrapOffset = cloudOffset + 8.0f;
    drawCloud(-2.5f + wrapOffset,  0.75f, 0.15f);
    drawCloud( 1.2f + wrapOffset,  0.80f, 0.12f);
    drawCloud(-0.5f + wrapOffset,  0.35f, 0.18f);
    drawCloud( 2.8f + wrapOffset, -0.15f, 0.14f);
    drawCloud(-3.8f + wrapOffset, -0.30f, 0.16f);
}

void drawAirplane() {
    // Airplane body (fuselage) - filled rectangle
    glColor3f(0.7f, 0.7f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2f(-0.8f, -0.08f);
    glVertex2f(0.8f, -0.08f);
    glVertex2f(0.8f, 0.08f);
    glVertex2f(-0.8f, 0.08f);
    glEnd();

    // Main wings (filled)
    glColor3f(0.6f, 0.6f, 0.7f);
    glBegin(GL_QUADS);
    // Left wing
    glVertex2f(-0.2f, 0.08f);
    glVertex2f(0.2f, 0.08f);
    glVertex2f(0.15f, 0.5f);
    glVertex2f(-0.15f, 0.5f);
    
    // Right wing
    glVertex2f(-0.2f, -0.08f);
    glVertex2f(0.2f, -0.08f);
    glVertex2f(0.15f, -0.5f);
    glVertex2f(-0.15f, -0.5f);
    glEnd();

    // Main wings outline
    glColor3f(0.2f, 0.2f, 0.3f);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    // Left wing outline
    glVertex2f(-0.2f, 0.08f);
    glVertex2f(0.2f, 0.08f);
    glVertex2f(0.15f, 0.5f);
    glVertex2f(-0.15f, 0.5f);
    glEnd();
    glBegin(GL_LINE_LOOP);
    // Right wing outline
    glVertex2f(-0.2f, -0.08f);
    glVertex2f(0.2f, -0.08f);
    glVertex2f(0.15f, -0.5f);
    glVertex2f(-0.15f, -0.5f);
    glEnd();

    // Tail wings (filled, smaller)
    glColor3f(0.5f, 0.5f, 0.6f);
    glBegin(GL_QUADS);
    // Left tail wing
    glVertex2f(-0.7f, 0.08f);
    glVertex2f(-0.4f, 0.08f);
    glVertex2f(-0.45f, 0.25f);
    glVertex2f(-0.65f, 0.25f);
    
    // Right tail wing
    glVertex2f(-0.7f, -0.08f);
    glVertex2f(-0.4f, -0.08f);
    glVertex2f(-0.45f, -0.25f);
    glVertex2f(-0.65f, -0.25f);
    glEnd();

    // Tail wings outline
    glColor3f(0.2f, 0.2f, 0.3f);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    // Left tail wing outline
    glVertex2f(-0.7f, 0.08f);
    glVertex2f(-0.4f, 0.08f);
    glVertex2f(-0.45f, 0.25f);
    glVertex2f(-0.65f, 0.25f);
    glEnd();
    glBegin(GL_LINE_LOOP);
    // Right tail wing outline
    glVertex2f(-0.7f, -0.08f);
    glVertex2f(-0.4f, -0.08f);
    glVertex2f(-0.45f, -0.25f);
    glVertex2f(-0.65f, -0.25f);
    glEnd();

    // Cockpit area (slightly darker)
    glColor3f(0.3f, 0.3f, 0.4f);
    glBegin(GL_QUADS);
    glVertex2f(0.3f, -0.06f);
    glVertex2f(0.7f, -0.06f);
    glVertex2f(0.7f, 0.06f);
    glVertex2f(0.3f, 0.06f);
    glEnd();

    // Nose (filled triangle, same width as body)
    glColor3f(0.8f, 0.8f, 0.9f);
    glBegin(GL_TRIANGLES);
    glVertex2f(1.1f, 0.0f);
    glVertex2f(0.8f, 0.08f);
    glVertex2f(0.8f, -0.08f);
    glEnd();
    
    // Nose outline
    glColor3f(0.2f, 0.2f, 0.3f);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glVertex2f(1.1f, 0.0f);
    glVertex2f(0.8f, 0.08f);
    glVertex2f(0.8f, -0.08f);
    glEnd();

    // Engine details (small rectangles on wings)
    glColor3f(0.4f, 0.4f, 0.5f);
    glBegin(GL_QUADS);
    // Left engine
    glVertex2f(-0.05f, 0.2f);
    glVertex2f(0.05f, 0.2f);
    glVertex2f(0.05f, 0.35f);
    glVertex2f(-0.05f, 0.35f);
    
    // Right engine
    glVertex2f(-0.05f, -0.2f);
    glVertex2f(0.05f, -0.2f);
    glVertex2f(0.05f, -0.35f);
    glVertex2f(-0.05f, -0.35f);
    glEnd();

    // Outline for definition
    glColor3f(0.2f, 0.2f, 0.3f);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.8f, -0.08f);
    glVertex2f(0.8f, -0.08f);
    glVertex2f(0.8f, 0.08f);
    glVertex2f(-0.8f, 0.08f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    drawSky();

    drawClouds();

    drawAirplane();
    glutSwapBuffers();
}

void timer(int v) {
    bgOffset -= 0.007f;
    if (bgOffset < -1.5f) bgOffset += 1.5f;

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void init() {
    glClearColor(0, 0, 0, 1);
    glLineWidth(3);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-4, 4, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 500);
    glutCreateWindow("Flying Airplane");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}