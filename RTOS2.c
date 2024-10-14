/* ============================ */
/* */
/* Michele Cristina Otta */
/* Tarso Bertolini Rodrigues */
/* Yejin Chung */
/* */
/* Ci ncia da Computa o - 4B */� ��
/* Projeto fase 2 */
/* */
/* ============================ */
#include "FreeRTOS.h"
#include "task.h"
#include "basic_io.h"
#include <stdlib.h>
#include "semphr.h"
#define qtd 4
#define inicial 1000
#define tamanho 10
SemaphoreHandle_t xSemaphore;
void guinada(void* pvParameters);
void arfagem(void* pvParameters);
void rolagem(void* pvParameters);
void radio_frequencia(void* pvParameters);
// Vetor para armazenar as vari veis das velocidades de cada motor do quadric ptero� �
volatile long motor0 = inicial, motor1 = inicial, motor2 = inicial, motor3 =
inicial;
volatile long* motores[qtd] = {&motor0, &motor1, &motor2, &motor3};
// Definindo as poss veis manobras�
char* sentidos[2] = {"horario", "antihorario"}; // Manobras da guinada
char* mover[2] = { "frente", "tras"}; // Manobras da arfagem
char* virar[2] = { "direita", "esquerda" }; // Manobras da rolagem
// Vari veis globais�
volatile char sentido[tamanho], direcao[tamanho], orientacao[tamanho];
// Fun o para imprimir na tela a velocidade dos motores��
void imprime_velocidade() {
vPrintString("\nVelocidade dos motores = ");
for (int i = 0; i < qtd; i++) {
printf("%d ", *motores[i]);
}
}
/* Fun o para guinada */��
void guinada(void* pvParameters) {
// Valor inicial passado por par metro�
sprintf(sentido, (char*)pvParameters);
// Valor definido para quanto se deve incrementar ou decrementar
int valor = 100;
for (;; ) {
// Checar se o sem foro foi criado�
if (xSemaphore != NULL) {
// Checar se o sem foro pode ser obtido�
// Caso n o possa, aguarda a quantidade passada por par metro� �
para verificar novamente
if (xSemaphoreTake(xSemaphore, 10) == pdTRUE) {
if (strcmp(sentido, sentidos[0]) == 0) {
// Se for manobra hor ria =�
// aumentar a velocidade dos motores 0 e 2
*motores[0] += valor;
*motores[2] += valor;
// diminuir a velocidade dos motores 1 e 3;
*motores[1] -= valor;
*motores[3] -= valor;
}
else if (strcmp(sentido, sentidos[1]) == 0) {
// Se for manobra anti hor ria =�
// diminuir a velocidade dos motores 0 e 2
*motores[0] -= valor;
*motores[2] -= valor;
// aumentar a velocidade dos motores 1 e 3
*motores[1] += valor;
*motores[3] += valor;
}
// Imprime manobra que est sendo realizada e a velocidade�
dos motores
vPrintString("\n\n-- Guinada --");
vPrintString("\nManobra = ");
vPrintString(sentido);
imprime_velocidade();
// Liberar o sem foro�
xSemaphoreGive(xSemaphore);
// Tempo de 10 ms
vTaskDelay(portTICK_RATE_MS * 10);
}
}
}
// Exclus o expl cita� �
vTaskDelete(NULL);
}
/* Fun o para arfagem */��
void arfagem(void* pvParameters) {
// Valor inicial passado por par metro�
sprintf(direcao, (char*)pvParameters);
// Valor definido para quanto se deve incrementar ou decrementar
int valor = 25;
for (;; ) {
// Checar se o sem foro foi criado�
if (xSemaphore != NULL) {
// Checar se o sem foro pode ser obtido�
// Caso n o possa, aguarda a quantidade passada por par metro� �
para verificar novamente
if (xSemaphoreTake(xSemaphore, 10) == pdTRUE) {
if (strcmp(direcao, mover[0]) == 0) {
// Se for manobra para frente =
// aumentar a velocidade dos motores 2 e 3
*motores[2] += valor;
*motores[3] += valor;
// diminuir a velocidade dos motores 0 e 1
*motores[0] -= valor;
*motores[1] -= valor;
}
else if (strcmp(direcao, mover[1]) == 0) {
// Se for manobra para tr s =�
// diminuir a velocidade dos motores 2 e 3
*motores[2] -= valor;
*motores[3] -= valor;
// aumentar a velocidade dos motores 0 e 1
*motores[0] += valor;
*motores[1] += valor;
}
// Imprime manobra que est sendo realizada e a velocidade�
dos motores
vPrintString("\n\n-- Arfagem --");
vPrintString("\nManobra = ");
vPrintString(direcao);
imprime_velocidade();
// Liberar o sem foro�
xSemaphoreGive(xSemaphore);
// Tempo de 40 ms
vTaskDelay(portTICK_RATE_MS * 40);
}
}
}
// Exclus o expl cita� �
vTaskDelete(NULL);
}
/* Fun o para rolagem */��
void rolagem(void* pvParameters) {
// Valor inicial passado por par metro�
sprintf(orientacao, (char*)pvParameters);
// Valor definido para quanto se deve incrementar ou decrementar
int valor = 50;
for (;; ) {
// Checar se o sem foro foi criado�
if (xSemaphore != NULL) {
// Checar se o sem foro pode ser obtido�
// Caso n o possa, aguarda a quantidade passada por par metro� �
para verificar novamente
if (xSemaphoreTake(xSemaphore, 10) == pdTRUE) {
if (strcmp(orientacao, virar[0]) == 0) {
// Se for manobra para direita =
// aumentar a velocidade dos motores 0 e 3
*motores[0] += valor;
*motores[3] += valor;
// diminuir a velocidade dos motores 1 e 2
*motores[1] -= valor;
*motores[2] -= valor;
}
else if (strcmp(orientacao, virar[1]) == 0) {
// Se for manobra para esquerda =
// diminuir a velocidade dos motores 0 e 3
*motores[0] -= valor;
*motores[3] -= valor;
// aumentar a velocidade dos motores 1 e 2
*motores[1] += valor;
*motores[2] += valor;
}
// Imprime a manobra que est sendo realizada e a�
velocidade dos motores
vPrintString("\n\n-- Rolagem --");
vPrintString("\nManobra = ");
vPrintString(orientacao);
imprime_velocidade();
// Liberar o sem foro�
xSemaphoreGive(xSemaphore);
// Tempo de 20 ms
vTaskDelay(portTICK_RATE_MS * 20);
}
}
}
// Exclus o expl cita� �
vTaskDelete(NULL);
}
/* Fun o para alterar manobras */��
void radio_frequencia(void* pvParameters) {
int x, y, z;
for (;;) {
// Checar se o sem foro foi criado�
if (xSemaphore != NULL) {
// Checar se o sem foro pode ser obtido�
// Caso n o possa, aguarda a quantidade passada por par metro� �
para verificar novamente
if (xSemaphoreTake(xSemaphore, 10) == pdTRUE) {
// Manobras alteradas aletoriamente
x = rand() % 100;
y = rand() % 100;
z = rand() % 100;
if (x % 2 == 0) {
sprintf(sentido, sentidos[0]); // se par, sentido
hor rio�
}
else {
sprintf(sentido, sentidos[1]); // se mpar, anti�
hor rio�
}
if (y % 2 == 0) {
sprintf(direcao, mover[0]); // se par, dire o��
para frente
}
else {
sprintf(direcao, mover[1]); // se mpar, dire o� ��
para tr s�
}
if (z % 2 == 0) {
sprintf(orientacao, virar[0]); // se par, orienta o��
para a direita
}
else {
sprintf(orientacao, virar[1]); // se mpar,�
orienta o para a esquerda��
}
// Liberar o sem foro�
xSemaphoreGive(xSemaphore);
// Tempo de 100 ms
vTaskDelay(portTICK_RATE_MS * 100);
}
}
}
// Exclus o expl cita� �
vTaskDelete(NULL);
}
int main_(void)
{
// Criar o sem foro bin rio� �
vSemaphoreCreateBinary(xSemaphore);
// Verifica se o sem foro foi criado�
if (xSemaphore != NULL) {
// Criar as tarefas
xTaskCreate(guinada, "Task Guinada", 1000, (void*)sentidos[0], 2,
NULL);
xTaskCreate(arfagem, "Task Arfagem", 1000, (void*)mover[0], 2, NULL);
xTaskCreate(rolagem, "Task Rolagem", 1000, (void*)virar[0], 2, NULL);
xTaskCreate(radio_frequencia, "Task Radio Frequencia", 1000, NULL, 1,
NULL);
// Iniciar a execu o das tarefas��
vTaskStartScheduler();
for (;; );
// Deleta o sem foro�
vSemaphoreDelete(xSemaphore);
}
return 0;
}