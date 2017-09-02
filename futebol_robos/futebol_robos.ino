
//portas do Arduino ligadas na ponte H
int D2 =  2;
int D3 =  3;
int D4 =  4;
int D5 =  5;

/**
 * Configuracao
 */
void setup() {
	// put your setup code here, to run once:
	
	Serial.begin(9600);
	
	pinMode ( D2, OUTPUT);//Pino 2 da ponte H, fio vermelho do motor 1
	pinMode ( D3, OUTPUT);//Pino 7 da ponte H, fio preto do motor 1
	pinMode ( D5, OUTPUT);//Pino 10 da ponte H, fio azul claro do motor 2
	pinMode ( D4, OUTPUT);//Pino 15 da ponte H; fio azul escuro motor 2
	
}

/**
 * Controle dos motores
 */

void rodarMotorSentidoHorario(int motor){
	if(motor==1)
	{
		digitalWrite(D3,HIGH);
		digitalWrite(D2,LOW);
	}
	else
	{
		digitalWrite(D4,LOW);
		digitalWrite(D5,HIGH);
	}
}

void rodarMotorSentidoAntiHorario(int motor){
	if(motor==1)
	{
		digitalWrite(D3,LOW);
		digitalWrite(D2,HIGH);
	}
	else
	{
		digitalWrite(D4,HIGH);
		digitalWrite(D5,LOW);
	}
}

void pararMotor(int motor){
	if(motor==1)
	{
		//para o motor 1
		digitalWrite(D3,LOW);
		digitalWrite(D2,LOW);
	}
	else if(motor == 2)
	{
		//para o motor 2
		digitalWrite(D4,LOW);
		digitalWrite(D5,LOW);
	} else {
		//para os dois motores
		digitalWrite(D3,LOW);
		digitalWrite(D2,LOW);
		digitalWrite(D4,LOW);
		digitalWrite(D5,LOW);
	}
}

/**
 * Programa principal
 */

void loop() {
	
	char caracter = 'X';

  if(Serial.available() > 0){

    //le do stream se estiver disponivel
    caracter = Serial.read();

    //debug
    Serial.println(caracter);

    //decide que saidas ativar
    switch(caracter){
      
      case 'E': // esquerda
        rodarMotorSentidoHorario(1);
        rodarMotorSentidoHorario(2);
      break;
      
      case 'D': //direita
        rodarMotorSentidoAntiHorario(1);
        rodarMotorSentidoAntiHorario(2);
      break;
      
      case 'F': //frente
        rodarMotorSentidoHorario(1);
        rodarMotorSentidoAntiHorario(2);
      break;
      
      case 'R': //reverso
        rodarMotorSentidoAntiHorario(1);
        rodarMotorSentidoHorario(2);
      break;
      
      case 'P': //parar
        pararMotor(0);
      break;

    }
    
  }
	
	delay(10);
}

