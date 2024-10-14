/* ============================ */
/* */
/* Michele Cristina Otta */
/* Tarso Bertolini Rodrigues */
/* Yejin Chung */
/* */
/* Ci ncia da Computa o - 4B */ � ��
/* */
/* ============================ */
#include "FreeRTOS.h"
#include "task.h"
#include "basic_io.h"
#include <stdlib.h>
#define qtd 4
#define inicial 1000
void guinada(void* pvParameters);
void arfagem(void* pvParameters);
void rolagem(void* pvParameters);
// Vetor com as vari veis das velocidades de cada motor do quadric ptero � �
long motor0 = inicial, motor1 = inicial, motor2 = inicial, motor3 = inicial;
long* motores[qtd] = {&motor0, &motor1, &motor2, &motor3};
// Definindo as poss veis manobras �
char* sentido[2] = {"Horario", "Anti horario"}; // Manobras da guinada
char* mover[2] = { "Para frente", "Para tras"}; // Manobras da arfagem
char* virar[2] = { "Para direita", "Para esquerda" }; // Manobras da rolagem
// Fun o para imprimir na tela a velocidade dos motores ��
void imprime_velocidade() {
vPrintString("\nVelocidade dos motores = ");
for (int i = 0; i < qtd; i++) {
printf("%d ", *motores[i]);
}
}
/* Fun o para guinada */ ��
void guinada(void* pvParameters) {
// Mensagem passada por par metro �
char* msg = (char*)pvParameters;
// Valor definido para quanto se deve incrementar ou decrementar
int valor = 100;
for (;; ) {
if (msg == sentido[0]) {
// Se for manobra hor ria = �
// aumentar a velocidade dos motores 0 e 2
*motores[0] += valor;
*motores[2] += valor;
// diminuir a velocidade dos motores 1 e 3;
*motores[1] -= valor;
*motores[3] -= valor;
}
else if (msg == sentido[1]) {
// Se for manobra anti hor ria = �
// diminuir a velocidade dos motores 0 e 2
*motores[0] -= valor;
*motores[2] -= valor;
// aumentar a velocidade dos motores 1 e 3
*motores[1] += valor;
*motores[3] += valor;
}
// Imprime manobra que est sendo realizada, a o que foi � ��
// passada por par metro para fun o e a velocidade dos motores � ��
vPrintString("\n\n-- Guinada --");
vPrintString("\nManobra = ");
vPrintString(msg);
imprime_velocidade();
// Tempo de 10 ms
vTaskDelay(10);
}
// Exclus o expl cita � �
vTaskDelete(NULL);
}
/* Fun o para arfagem */ ��
void arfagem(void* pvParameters) {
// Mensagem passada por par metro �
char* msg = (char*)pvParameters;
// Valor definido para quanto se deve incrementar ou decrementar
int valor = 25;
for (;; ) {
if (msg == mover[0]) {
// Se for manobra para frente =
// aumentar a velocidade dos motores 2 e 3
*motores[2] += valor;
*motores[3] += valor;
// diminuir a velocidade dos motores 0 e 1
*motores[0] -= valor;
*motores[1] -= valor;
}
else if (msg == mover[1]) {
// Se for manobra para tr s = �
// diminuir a velocidade dos motores 2 e 3
*motores[2] -= valor;
*motores[3] -= valor;
// aumentar a velocidade dos motores 0 e 1
*motores[0] += valor;
*motores[1] += valor;
}
// Imprime manobra que est sendo realizada, a o que foi � ��
// passada por par metro para fun o e a velocidade dos motores � ��
vPrintString("\n\n-- Arfagem --");
vPrintString("\nManobra = ");
vPrintString(msg);
imprime_velocidade();
// Tempo de 40 ms
vTaskDelay(40);
}
// Exclus o expl cita � �
vTaskDelete(NULL);
}
/* Fun o para rolagem */ ��
void rolagem(void* pvParameters) {
// Mensagem passada por par metro �
char* msg = (char*)pvParameters;
// Valor definido para quanto se deve incrementar ou decrementar
int valor = 50;
for (;; ) {
if (msg == virar[0]) {
// Se for manobra para direita =
// aumentar a velocidade dos motores 0 e 3
*motores[0] += valor;
*motores[3] += valor;
// diminuir a velocidade dos motores 1 e 2
*motores[1] -= valor;
*motores[2] -= valor;
}
else if (msg == virar[1]) {
// Se for manobra para esquerda =
// diminuir a velocidade dos motores 0 e 3
*motores[0] -= valor;
*motores[3] -= valor;
// aumentar a velocidade dos motores 1 e 2
*motores[1] += valor;
*motores[2] += valor;
}
// Imprime a manobra que est sendo realizada, a o que foi � ��
// passada por par metro para fun o e a velocidade dos motores � ��
vPrintString("\n\n-- Rolagem --");
vPrintString("\nManobra = ");
vPrintString(msg);
imprime_velocidade();
// Tempo de 20 ms
vTaskDelay(20);
}
// Exclus o expl cita � �
vTaskDelete(NULL);
}
int main_(void)
{
// Para ser aleat ria a passagem de manobra por par metro das tarefas � �
int a1 = rand() % 2;
int a2 = rand() % 2;
int a3 = rand() % 2;
// Criar as tarefas
xTaskCreate(guinada, "Task Guinada", 1000, sentido[a1], 1, NULL);
xTaskCreate(arfagem, "Task Arfagem", 1000, mover[a2], 1, NULL);
xTaskCreate(rolagem, "Task Rolagem", 1000, virar[a3], 1, NULL);
// Iniciar as tarefas
vTaskStartScheduler();
for (;; );
return 0;
}