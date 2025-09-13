#include <GL/glut.h>
#include <cmath>

float anguloDeRotacao = 0.0f;

void animar() {
    anguloDeRotacao += 0.5f;
    if (anguloDeRotacao > 360.0f) {
        anguloDeRotacao -= 360.0f;
    }
    glutPostRedisplay();
}

void desenhar() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

// ---- 1. Artefato Estático (Quadrado) ----

    glBegin(GL_QUADS);
        glColor3f(0.8f, 0.8f, 0.8f);
        glVertex2f(-0.15f, 0.15f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-0.15f, -0.15f);
        glColor3f(0.8f, 0.8f, 0.8f);
        glVertex2f(0.15f, -0.15f);
        glColor3f(0.5f, 0.5f, 0.5f);
        glVertex2f(0.15f, 0.15f);
    glEnd();

    // ---- 2. Artefato Dinâmico (Sol Detalhado) ----
    glPushMatrix();
	glTranslatef(0.4f, 0.6f, 0.0f); 
    glRotatef(anguloDeRotacao, 0.0f, 0.0f, 1.0f);

    const float PI = 3.1415926535;
    const int NUM_RAIOS = 16;
    
    // Definindo os raios (tamanhos) para facilitar o ajuste
    const float raio_base_fundo = 0.13f;
    const float raio_ponta_fundo = 0.25f;
    const float raio_base_frente = 0.12f;
    const float raio_ponta_frente = 0.22f;
    const float raio_nucleo = 0.15f;
    
    // Camada 1: Raios de Fundo (Laranja Escuro)
    glColor3f(1.0f, 0.5f, 0.0f); // Laranja mais escuro
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < NUM_RAIOS; ++i) {
        float angulo_central = (2.0f * PI * i) / NUM_RAIOS;
        // Ponta do raio
        glVertex2f(cos(angulo_central) * raio_ponta_fundo, sin(angulo_central) * raio_ponta_fundo);
        // Vértices da base do raio
        float angulo_base1 = angulo_central - (PI / NUM_RAIOS / 1.5f);
        float angulo_base2 = angulo_central + (PI / NUM_RAIOS / 1.5f);
        glVertex2f(cos(angulo_base1) * raio_base_fundo, sin(angulo_base1) * raio_base_fundo);
        glVertex2f(cos(angulo_base2) * raio_base_fundo, sin(angulo_base2) * raio_base_fundo);
    }
    glEnd();

    // Camada 2: Raios da Frente (Laranja Claro)
    glColor3f(1.0f, 0.7f, 0.0f); // Laranja mais claro
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < NUM_RAIOS; ++i) {
        float angulo_central = (2.0f * PI * i) / NUM_RAIOS;
        // Ponta do raio
        glVertex2f(cos(angulo_central) * raio_ponta_frente, sin(angulo_central) * raio_ponta_frente);
        // Vértices da base do raio
        float angulo_base1 = angulo_central - (PI / NUM_RAIOS / 1.8f);
        float angulo_base2 = angulo_central + (PI / NUM_RAIOS / 1.8f);
        glVertex2f(cos(angulo_base1) * raio_base_frente, sin(angulo_base1) * raio_base_frente);
        glVertex2f(cos(angulo_base2) * raio_base_frente, sin(angulo_base2) * raio_base_frente);
    }
    glEnd();

    // Camada 3: Núcleo do Sol (desenhado por último para ficar na frente)
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0f, 1.0f, 0.5f); // Amarelo bem claro no centro
        glVertex2f(0.0f, 0.0f);
        glColor3f(1.0f, 0.8f, 0.0f); // Laranja na borda
        for (int i = 0; i <= NUM_RAIOS * 2; ++i) { // O dobro de lados para ficar bem redondo
            float angulo = (2.0f * PI * i) / (NUM_RAIOS * 2);
            glVertex2f(cos(angulo) * raio_nucleo, sin(angulo) * raio_nucleo);
        }
    glEnd();

    glPopMatrix();
    glutSwapBuffers();
}

void inicializar() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Artefato Estático & Artefato Dinâmico");
    inicializar();
    glutDisplayFunc(desenhar);
    glutIdleFunc(animar);
    glutMainLoop();
    return 0;
}

