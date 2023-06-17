#include <Servo.h>          // Inclui a Biblioteca
 
Servo Horizontal;           // Inicia o Servo da Horizontal
Servo Vertical;             // Inicia o Servo da Vertical
 
int ServoHorizontal = 90;   // Estabelece valor fixo à ServoHorizontal
int ServoVertical = 90;     // Estabelece valor fixo à ServoVertical
 
int LimiteServoHorizontalMax = 180;  // Estabele os limites de rotação
int LimiteServoHorizontalMin = 65;   // Estabele os limites de rotação
 
int LimiteServoVerticalMax = 120;    // Estabele os limites de rotação
int LimiteServoVerticalMin = 15;     // Estabele os limites de rotação
 
int LDRDC = A0;             // Inicia LDRDC no pino A0
int LDRDB = A1;             // Inicia LDRDB no pino A1
int LDREC = A2;             // Inicia LDREC no pino A2
int LDREB = A3;             // Inicia LDREB no pino A3
int LDRLed = A4;
 
void setup()  {
  Serial.begin(9600);
  Horizontal.attach(10);     // Inicia servo Horizontal na porta 10
  Vertical.attach(9);       // Inicia servo Vertical na porta 9
  pinMode(LDRLed, OUTPUT);
 
  for (int x = 45; x <= 90; x++) { // Inicia servo Horizontal na posição 90 aos poucos
   Serial.println("Posicionando Horizontal = "); 
   Serial.println(x);
   Horizontal.write(x);
   delay(300);  
  }

  for (int y = 45; y <= 90; y++) { // Inicia servo Vertical na posição 90 aos poucos
   Serial.println("Posicionando Vertical = "); 
   Serial.println(y);
   Vertical.write(y);
   delay(300);    
  }
  delay(3000);              // Aguarda 3 segundos
}
 
void loop() {
  int LDC = analogRead(LDRDC);      // Leitura Analógica do LDR Direita Cima
  int LEC = analogRead(LDREC);      // Leitura Analógica do LDR Esquerda Cima
  int LDB = analogRead(LDRDB);      // Leitura Analógica do LDR Direita Baixo
  int LEB = analogRead(LDREB);      // Leitura Analógica do LDR Esquerda Baixo
  int tol = 50;
 
  int ValorSup = (LDC + LEC) / 2;   // Média da leitura dos LDR superior
  int ValorInf = (LDB + LEB) / 2;   // Média da leitura dos LDR inferior
  int ValorDir = (LDC + LDB) / 2;   // Média da leitura dos LDR da direita
  int ValorEsq = (LEC + LEB) / 2;   // Média da leitura dos LDR da esquerda
 
  int DifSupInf = ValorSup - ValorInf;      // Diferença entre LED superior e inferior
  int DifDirEsq = ValorDir - ValorEsq;      // Diferença entre LED direita e esquerda

  // Read the light level on A4 and control the LED accordingly
  if (LDC + LEC + LDB + LEB > 2140) {
    digitalWrite(LDRLed, HIGH);  // Turn on the LED if the light level is below 512
  } else {
    digitalWrite(LDRLed, LOW);   // Turn off the LED if the light level is above 512
  }
 
  /*---------------------------------------------------*/
 
  // Realiza a leitura e executa os movimentos referente ao Servo Vertical
  if (-1 * tol > DifSupInf || DifSupInf > tol)  {
    if (ValorSup > ValorInf)  {
      ServoVertical = ++ServoVertical;
      if (ServoVertical > LimiteServoVerticalMax)  {
        ServoVertical = LimiteServoVerticalMax;
      }
    }
    else if (ValorSup < ValorInf)  {
      ServoVertical = --ServoVertical;
      if (ServoVertical < LimiteServoVerticalMin)  {
        ServoVertical = LimiteServoVerticalMin;
      }
    }
    Vertical.write(ServoVertical);
    Serial.println("ServoVertical = "); 
    Serial.println(ServoVertical);
    
  }
 
  // Realiza a leitura e executa os movimentos referente ao Servo Horizontal
  if (-1 * tol > DifDirEsq || DifDirEsq > tol) {
    if (ValorDir > ValorEsq)  {
      ServoHorizontal = --ServoHorizontal;
      if (ServoHorizontal < LimiteServoHorizontalMin)  {
        ServoHorizontal = LimiteServoHorizontalMin;
      }
    }
    else if (ValorDir < ValorEsq)  {
      ServoHorizontal = ++ServoHorizontal;
      if (ServoHorizontal > LimiteServoHorizontalMax)  {
        ServoHorizontal = LimiteServoHorizontalMax;
      }
    }
    else if (ValorDir = ValorEsq)  {
    }
    Horizontal.write(ServoHorizontal);
    Serial.println("ServoHorizontal = ");
    Serial.println(ServoHorizontal);
  }
 
  delay(100);   // Aguarda 0,1 segundo
}
