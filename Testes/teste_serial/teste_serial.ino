void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
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
    }
    
}
