#include <GL/glut.h>
#include <cmath>

// --- Variáveis Globais para Animação ---
float anguloDeRotacao = 0.0f; // Para a rotação do sol

// --- Função de Animação ---
void animar(int value) {
    // Atualiza o ângulo de rotação do sol
    anguloDeRotacao += 0.5f;
    if (anguloDeRotacao > 360.0f) {
        anguloDeRotacao -= 360.0f;
    }
    
    glutPostRedisplay(); // Pede para redesenhar a tela
    glutTimerFunc(16, animar, 0); // Chama a si mesma a cada ~16ms (~60 FPS)
}

// --- Função de Inicialização ---
void inicializar() {
    // Habilita o teste de profundidade, essencial para 3D
    glEnable(GL_DEPTH_TEST);
    // Define a cor de fundo como um azul claro (céu)
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
    // Limpa os buffers de cor e de profundidade
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Define a Posição da Câmera
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // --- 1. Céu (Gradiente do Pôr do Sol) ---
    glBegin(GL_QUADS);
        glColor3f(0.1f, 0.1f, 0.4f);
        glVertex3f(-15.0f, 8.0f, -15.0f);
        glVertex3f(15.0f, 8.0f, -15.0f);
        glColor3f(1.0f, 0.5f, 0.2f);
        glVertex3f(15.0f, -1.0f, -15.0f);
        glVertex3f(-15.0f, -1.0f, -15.0f);
    glEnd();

    // --- 2. Sol Detalhado e Giratório ---
    glPushMatrix();
    glTranslatef(-2.5f, 2.0f, -14.0f);
    glRotatef(anguloDeRotacao, 0.0f, 0.0f, 1.0f);

        const float PI = 3.1415926535;
        const int NUM_RAIOS = 16;
        const float raio_base_fundo = 0.13f, raio_ponta_fundo = 0.25f;
        const float raio_base_frente = 0.12f, raio_ponta_frente = 0.22f;
        const float raio_nucleo = 0.15f;
        
        glColor3f(1.0f, 0.5f, 0.0f);
        glBegin(GL_TRIANGLES);
        for (int i = 0; i < NUM_RAIOS; ++i) {
            float angulo_central = (2.0f * PI * i) / NUM_RAIOS;
            glVertex2f(cos(angulo_central) * raio_ponta_fundo, sin(angulo_central) * raio_ponta_fundo);
            float angulo_base1 = angulo_central - (PI / NUM_RAIOS / 1.5f);
            float angulo_base2 = angulo_central + (PI / NUM_RAIOS / 1.5f);
            glVertex2f(cos(angulo_base1) * raio_base_fundo, sin(angulo_base1) * raio_base_fundo);
            glVertex2f(cos(angulo_base2) * raio_base_fundo, sin(angulo_base2) * raio_base_fundo);
        }
        glEnd();

        glColor3f(1.0f, 0.7f, 0.0f);
        glBegin(GL_TRIANGLES);
        for (int i = 0; i < NUM_RAIOS; ++i) {
            float angulo_central = (2.0f * PI * i) / NUM_RAIOS;
            glVertex2f(cos(angulo_central) * raio_ponta_frente, sin(angulo_central) * raio_ponta_frente);
            float angulo_base1 = angulo_central - (PI / NUM_RAIOS / 1.8f);
            float angulo_base2 = angulo_central + (PI / NUM_RAIOS / 1.8f);
            glVertex2f(cos(angulo_base1) * raio_base_frente, sin(angulo_base1) * raio_base_frente);
            glVertex2f(cos(angulo_base2) * raio_base_frente, sin(angulo_base2) * raio_base_frente);
        }
        glEnd();

        glBegin(GL_TRIANGLE_FAN);
            glColor3f(1.0f, 1.0f, 0.5f);
            glVertex2f(0.0f, 0.0f);
            glColor3f(1.0f, 0.8f, 0.0f);
            for (int i = 0; i <= NUM_RAIOS * 2; ++i) {
                float angulo = (2.0f * PI * i) / (NUM_RAIOS * 2);
                glVertex2f(cos(angulo) * raio_nucleo, sin(angulo) * raio_nucleo);
            }
        glEnd();
    glPopMatrix();

    // --- 3. Montanhas ---
    glColor3f(0.2f, 0.15f, 0.3f);
    glBegin(GL_TRIANGLES);
        glVertex3f(-6.0f, -1.0f, -10.0f); glVertex3f(-2.0f, 2.5f, -10.0f); glVertex3f(2.0f, -1.0f, -10.0f);
        glVertex3f(0.0f, -1.0f, -10.0f); glVertex3f(4.0f, 3.0f, -10.0f); glVertex3f(8.0f, -1.0f, -10.0f);
    glEnd();
    glColor3f(0.3f, 0.25f, 0.4f);
    glBegin(GL_TRIANGLES);
        glVertex3f(-4.0f, -1.0f, -8.0f); glVertex3f(1.0f, 4.0f, -8.0f); glVertex3f(6.0f, -1.0f, -8.0f);
    glEnd();

    // --- 4. Chão ---
    glBegin(GL_QUADS);
        glColor3f(0.1f, 0.4f, 0.1f);
        glVertex3f(-15.0f, -1.0f, 5.0f);
        glVertex3f(15.0f, -1.0f, 5.0f);
        glColor3f(0.4f, 0.6f, 0.2f);
        glVertex3f(15.0f, -1.0f, -15.0f);
        glVertex3f(-15.0f, -1.0f, -15.0f);
    glEnd();

    // --- 5. Casa (Objeto em Primeiro Plano) ---
    glPushMatrix();
    glTranslatef(-1.5f, -0.7f, 0.0f);
    glScalef(0.6f, 0.6f, 0.6f);
    
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
    glPopMatrix();
    
    glutSwapBuffers();
}

// --- Função Principal ---
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cena Cinematográfica Final");
    
    inicializar();
    glutDisplayFunc(desenhar);
    glutReshapeFunc(redimensionar);
    glutTimerFunc(0, animar, 0);
    
    glutMainLoop();
    return 0;
}
