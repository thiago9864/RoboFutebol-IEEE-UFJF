
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

int converteHex(char hexValue[]){
  byte tens = (hexValue[0] < '9') ? hexValue[0] - '0' : hexValue[0] - '7';
  byte ones = (hexValue[1] < '9') ? hexValue[1] - '0' : hexValue[1] - '7';
  int ret = (16 * tens) + ones;
  return ret;
}

bool validaComando(char c, char vetX[], char vetY[]){
  int v = 0;
  if(c >= 'a' && c <= 'z'){
    v++;
  }
  if(vetX[0] >= '0' && vetX[0] <= '9' || vetX[0] >= 'A' && vetX[0] <= 'F'){
    v++;
  }
  if(vetX[1] >= '0' && vetX[1] <= 'F' || vetX[1] >= 'A' && vetX[1] <= 'F'){
    v++;
  }
  if(vetY[0] >= '0' && vetY[0] <= 'F' || vetY[0] >= 'A' && vetY[0] <= 'F'){
    v++;
  }
  if(vetY[1] >= '0' && vetY[1] <= 'F' || vetY[1] >= 'A' && vetY[1] <= 'F'){
    v++;
  }

  if(v == 5){
    return true;
  }

  return false;
  
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
  // put your main code here, to run repeatedly:

  char controle;
  char vetX[2], vetY[2];
  bool comandoOK = false;

  if(Serial.available()){
    
    controle = (char)Serial.read();
    delay(5);
    vetX[0] = (char)Serial.read();
    delay(5);
    vetX[1] = (char)Serial.read();
    delay(5);
    vetY[0] = (char)Serial.read();
    delay(5);
    vetY[1] = (char)Serial.read();
    delay(5);
    
    if((char)Serial.read() == '|' && validaComando(controle, vetX, vetY)){
      //leu corretamente
      Serial.println("ok");
      comandoOK = true;
    } else {
      Serial.println("erro");
    }
    }

    if(comandoOK){
      Serial.println("Comando Recebido: c = " + String(controle) +", x = "+ String(converteHex(vetX)) +", y = "+ String(converteHex(vetY)));

      //decide que saidas ativar
    switch(controle){
      
      case 'e': // esquerda
        rodarMotorSentidoHorario(1);
        rodarMotorSentidoHorario(2);
      break;
      
      case 'd': //direita
        rodarMotorSentidoAntiHorario(1);
        rodarMotorSentidoAntiHorario(2);
      break;
      
      case 'f': //frente
        rodarMotorSentidoHorario(1);
        rodarMotorSentidoAntiHorario(2);
      break;
      
      case 'r': //reverso
        rodarMotorSentidoAntiHorario(1);
        rodarMotorSentidoHorario(2);
      break;
      
      case 'p': //parar
        pararMotor(0);
      break;

    }
    
    }
    
}
