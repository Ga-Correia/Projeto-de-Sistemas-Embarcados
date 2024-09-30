/*
Gabriel Correia Granja  RA: 148521
Jo�o Vitor Terra    RA: 148118
Matheus Ossis de Lima  RA:148677

Trabalho Final de Sistemas Embarcados 2024/1 semestre
*/

void main() {
  unsigned int cont = 0;
  unsigned int resto= 0;
  unsigned char resultado;
  unsigned char ucStatus_inc;
  unsigned int pot1 = 0;
  unsigned char pot1_pwm = 0;
  PORTA = 255;
  TRISA = 255;
  //ADCON1 = 0x0D;
  ADCON1 = 0b11001110;
  TRISB.RB0 = 1;
  I2C1_Init(80000);               // Inicializa I2C com clock de 80KHz
  PWM1_Init(5000);      // Inicializa m�dulo PWM com 5Khz
  PWM1_Start();         // Start PWM
  while(1) {
     pot1 = ADC_Read(0);     // L� o valor anal�gico do potenci�metro (AN0)
     pot1_pwm =  (unsigned char)(pot1*0.25);

     // Verifica o estado do bot�o (RB0)
     if ((PORTB.RB0 == 0) && (ucStatus_inc == 0)) { // Incrementa apenas uma vez quando o bot�o � pressionado
         ucStatus_inc = 1;
         cont++;

     }
     if ((PORTB.RB0 == 1) && (ucStatus_inc == 1)) { // Libera a op��o de incremento quando o bot�o � solto
         ucStatus_inc = 0;

     }

     // Se o bot�o estiver desligado (Valor = 0), for�a o potenci�metro a ser 0
     resto =  cont%2;
     if (resto ==0) {
         pot1_pwm = 0;  // For�a o valor do potenci�metro para 0
     }

     // Envia os dados para o Arduino via I2C
     I2C1_Start();               // Inicia a comunica��o I2C
     I2C1_Wr(0x58);              // Envia o endere�o do Arduino (0x58)
     I2C1_Wr(resto);             // Envia a vari�vel "Valor" (0 = DESLIGADO, 1 = LIGADO)
     I2C1_Wr(pot1_pwm);          // Envia o valor do potenci�metro convertido (0-255, ou 0 se Valor for 0)
     I2C1_Stop();                // Finaliza a comunica��o I2C

     Delay_ms(100);              // Pequeno atraso para n�o saturar a comunica��o
  }
}
