#include <GL/glut.h>
#include <cmath>

// --- Variáveis Globais para Animação ---
float anguloDeRotacao = 0.0f; // Para a rotação do sol

// --- Função de Animação ---
void animar(int value) {
    anguloDeRotacao += 0.5f;
    if (anguloDeRotacao > 360.0f) {
        anguloDeRotacao -= 360.0f;
    }
    glutPostRedisplay();
    glutTimerFunc(16, animar, 0);
}

// --- Função dedicada para desenhar uma casa ---
void desenharCasa() {
    // Parede da Casa (Branco)
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.4f, -0.6f); glVertex2f(0.4f, -0.6f);
        glVertex2f(0.4f, 0.2f); glVertex2f(-0.4f, 0.2f);
    glEnd();

    // Telhado e Chaminé (Marrom)
    glColor3f(0.5f, 0.25f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.4f, 0.2f); glVertex2f(0.4f, 0.2f); glVertex2f(0.0f, 0.6f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(-0.3f, 0.3f); glVertex2f(-0.15f, 0.45f);
        glVertex2f(-0.15f, 0.75f); glVertex2f(-0.3f, 0.75f);
    glEnd();

    // Porta (Vermelho) - Desenhada um pouco à frente (Z=0.01)
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(-0.3f, -0.6f, 0.01f); glVertex3f(-0.1f, -0.6f, 0.01f);
        glVertex3f(-0.1f, -0.2f, 0.01f); glVertex3f(-0.3f, -0.2f, 0.01f);
    glEnd();

    // Janela (Azul) - Desenhada um pouco à frente (Z=0.01)
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex3f(0.1f, -0.1f, 0.01f); glVertex3f(0.3f, -0.1f, 0.01f);
        glVertex3f(0.3f, 0.1f, 0.01f); glVertex3f(0.1f, 0.1f, 0.01f);
    glEnd();
}

// --- Função de Inicialização ---
void inicializar() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
}

// --- Função para cuidar da Projeção de Perspectiva ---
void redimensionar(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// --- Função Principal de Desenho ---
void desenhar() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // --- Céu ---
    glBegin(GL_QUADS);
        glColor3f(0.1f, 0.1f, 0.4f);
        glVertex3f(-15.0f, 8.0f, -15.0f); glVertex3f(15.0f, 8.0f, -15.0f);
        glColor3f(1.0f, 0.5f, 0.2f);
        glVertex3f(15.0f, -1.0f, -15.0f); glVertex3f(-15.0f, -1.0f, -15.0f);
    glEnd();

    // --- Sol ---
    glPushMatrix();
    glTranslatef(-2.5f, 2.0f, -1.0f);
    glRotatef(anguloDeRotacao, 0.0f, 0.0f, 1.0f);
        const float PI = 3.1415926535; const int NUM_RAIOS = 16;
        const float rbf = 0.13f, rpf = 0.25f, rbf2 = 0.12f, rpf2 = 0.22f, rn = 0.15f;
        glColor3f(1.0f, 0.5f, 0.0f); glBegin(GL_TRIANGLES);
        for (int i = 0; i < NUM_RAIOS; ++i) {
            float ac = (2.0f * PI * i) / NUM_RAIOS; glVertex2f(cos(ac)*rpf, sin(ac)*rpf);
            float ab1 = ac - (PI/NUM_RAIOS/1.5f); float ab2 = ac + (PI/NUM_RAIOS/1.5f);
            glVertex2f(cos(ab1)*rbf, sin(ab1)*rbf); glVertex2f(cos(ab2)*rbf, sin(ab2)*rbf);
        } glEnd();
        glColor3f(1.0f, 0.7f, 0.0f); glBegin(GL_TRIANGLES);
        for (int i = 0; i < NUM_RAIOS; ++i) {
            float ac = (2.0f * PI * i) / NUM_RAIOS; glVertex2f(cos(ac)*rpf2, sin(ac)*rpf2);
            float ab1 = ac - (PI/NUM_RAIOS/1.8f); float ab2 = ac + (PI/NUM_RAIOS/1.8f);
            glVertex2f(cos(ab1)*rbf2, sin(ab1)*rbf2); glVertex2f(cos(ab2)*rbf2, sin(ab2)*rbf2);
        } glEnd();
        glBegin(GL_TRIANGLE_FAN);
            glColor3f(1.0f,1.0f,0.5f); glVertex2f(0.0f,0.0f); glColor3f(1.0f,0.8f,0.0f);
            for(int i=0; i<=NUM_RAIOS*2;++i){ float a=(2.0f*PI*i)/(NUM_RAIOS*2); glVertex2f(cos(a)*rn,sin(a)*rn); }
        glEnd();
    glPopMatrix();

    // --- Montanhas ---
    glColor3f(0.2f, 0.15f, 0.3f);
    glBegin(GL_TRIANGLES);
        glVertex3f(-6.0f, -1.0f, -10.0f); glVertex3f(-2.0f, 2.5f, -10.0f); glVertex3f(2.0f, -1.0f, -10.0f);
        glVertex3f(0.0f, -1.0f, -10.0f); glVertex3f(4.0f, 3.0f, -10.0f); glVertex3f(8.0f, -1.0f, -10.0f);
    glEnd();
    glColor3f(0.3f, 0.25f, 0.4f);
    glBegin(GL_TRIANGLES);
        glVertex3f(-4.0f, -1.0f, -8.0f); glVertex3f(1.0f, 4.0f, -8.0f); glVertex3f(6.0f, -1.0f, -8.0f);
    glEnd();

    // --- Chão ---
    glBegin(GL_QUADS);
        glColor3f(0.1f, 0.4f, 0.1f);
        glVertex3f(-15.0f, -1.0f, 5.0f); glVertex3f(15.0f, -1.0f, 5.0f);
        glColor3f(0.4f, 0.6f, 0.2f);
        glVertex3f(15.0f, -1.0f, -15.0f); glVertex3f(-15.0f, -1.0f, -15.0f);
    glEnd();
    
    // --- NOVO: Estrada em Perspectiva ---
    // Superfície da estrada (asfalto)
    glColor3f(0.3f, 0.3f, 0.3f); // Cor de asfalto
    glBegin(GL_QUAD_STRIP);
        // Os vértices são definidos em pares (esquerdo, direito)
        // A estrada começa larga e perto, e vai se estreitando para longe
        glVertex3f(-2.5f, -0.99f, 4.0f);   // Ponto 1 - Esquerda
        glVertex3f(-1.5f, -0.99f, 4.0f);   // Ponto 1 - Direita
        
        glVertex3f(-1.4f, -0.99f, 2.0f);   // Ponto 2 - Esquerda
        glVertex3f(-0.6f, -0.99f, 2.0f);   // Ponto 2 - Direita
        
        glVertex3f(0.2f, -0.99f, 0.0f);    // Ponto 3 - Esquerda
        glVertex3f(0.8f, -0.99f, 0.0f);    // Ponto 3 - Direita
        
        glVertex3f(1.8f, -0.99f, -3.0f);   // Ponto 4 - Esquerda
        glVertex3f(2.2f, -0.99f, -3.0f);   // Ponto 4 - Direita

        glVertex3f(3.5f, -0.99f, -6.0f);   // Ponto 5 - Esquerda
        glVertex3f(3.8f, -0.99f, -6.0f);   // Ponto 5 - Direita
    glEnd();
    
    // Linha central da estrada
    glColor3f(0.9f, 0.8f, 0.0f); // Amarelo
    glBegin(GL_LINE_STRIP);
        // Os vértices são os pontos centrais da estrada
        glVertex3f(-2.0f, -0.98f, 4.0f);
        glVertex3f(-1.0f, -0.98f, 2.0f);
        glVertex3f(0.5f, -0.98f, 0.0f);
        glVertex3f(2.0f, -0.98f, -3.0f);
        glVertex3f(3.65f, -0.98f, -6.0f);
    glEnd();

    // --- Casas em Perspectiva ---
    // Casa 1: Primeiro plano, à esquerda
    glPushMatrix();
        glTranslatef(-1.5f, -0.7f, 0.0f);
        glScalef(0.6f, 0.6f, 0.6f);
        desenharCasa();
    glPopMatrix();

    // Casa 2: Plano médio, à direita
    glPushMatrix();
        glTranslatef(1.0f, -0.6f, -3.0f);
        glScalef(0.5f, 0.5f, 0.5f);
        desenharCasa();
    glPopMatrix();

    // Casa 3: Plano de fundo, bem à direita
    glPushMatrix();
        glTranslatef(4.5f, -0.7f, -6.0f);
        glScalef(0.4f, 0.4f, 0.4f);
        desenharCasa();
    glPopMatrix();
    
    glutSwapBuffers();
}

// --- Função Principal ---
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cena com Perspectiva");
    
    inicializar();
    glutDisplayFunc(desenhar);
    glutReshapeFunc(redimensionar);
    glutTimerFunc(0, animar, 0);
    
    glutMainLoop();
    return 0;
}
