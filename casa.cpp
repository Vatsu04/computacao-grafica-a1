#include <GL/glut.h> 


void inicializar() {

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}


void desenhar() {

    glClear(GL_COLOR_BUFFER_BIT);

    // ---- 1. Corpo da Casa (Ret�ngulo Preto) ----
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.4f, -0.6f); // V�rtice inferior esquerdo
        glVertex2f(0.4f, -0.6f);  // V�rtice inferior direito
        glVertex2f(0.4f, 0.2f);   // V�rtice superior direito
        glVertex2f(-0.4f, 0.2f);  // V�rtice superior esquerdo
    glEnd();

    // ---- 2. Telhado (Tri�ngulo Preto) ----
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.4f, 0.2f);  // Base esquerda
        glVertex2f(0.4f, 0.2f);   // Base direita
        glVertex2f(0.0f, 0.6f);   // Ponta do telhado
    glEnd();

// ---- 3. Chamin� (Trap�zio Ret�ngulo) ----
	
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.3f, 0.3f);    // V�rtice inferior esquerdo (sobre o telhado)
        glVertex2f(-0.15f, 0.45f);  // V�rtice inferior direito (sobre o telhado)
        glVertex2f(-0.15f, 0.75f);  // V�rtice superior direito
        glVertex2f(-0.3f, 0.75f);   // V�rtice superior esquerdo
    glEnd();

    // ---- 4. Porta (Ret�ngulo Vermelho) ----
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

