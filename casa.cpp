#include <GL/glut.h> 


void inicializar() {

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}


void desenhar() {

    glClear(GL_COLOR_BUFFER_BIT);

    // ---- 1. Corpo da Casa (Retângulo Preto) ----
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.4f, -0.6f); // Vértice inferior esquerdo
        glVertex2f(0.4f, -0.6f);  // Vértice inferior direito
        glVertex2f(0.4f, 0.2f);   // Vértice superior direito
        glVertex2f(-0.4f, 0.2f);  // Vértice superior esquerdo
    glEnd();

    // ---- 2. Telhado (Triângulo Preto) ----
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.4f, 0.2f);  // Base esquerda
        glVertex2f(0.4f, 0.2f);   // Base direita
        glVertex2f(0.0f, 0.6f);   // Ponta do telhado
    glEnd();

// ---- 3. Chaminé (Trapézio Retângulo) ----
	
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.3f, 0.3f);    // Vértice inferior esquerdo (sobre o telhado)
        glVertex2f(-0.15f, 0.45f);  // Vértice inferior direito (sobre o telhado)
        glVertex2f(-0.15f, 0.75f);  // Vértice superior direito
        glVertex2f(-0.3f, 0.75f);   // Vértice superior esquerdo
    glEnd();

    // ---- 4. Porta (Retângulo Vermelho) ----
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.3f, -0.6f);
        glVertex2f(-0.1f, -0.6f);
        glVertex2f(-0.1f, -0.2f);
        glVertex2f(-0.3f, -0.2f);
    glEnd();

    // ---- 5. Janela (Quadrado Azul) ----
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(0.1f, -0.1f);
        glVertex2f(0.3f, -0.1f);
        glVertex2f(0.3f, 0.1f);
        glVertex2f(0.1f, 0.1f);
    glEnd();

    glFlush();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Casa Simples"); 
    inicializar(); 
    glutDisplayFunc(desenhar); 
    glutMainLoop(); 
    return 0;
}

