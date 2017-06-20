
#include <DHT.h>      //Inclui a biblioteca do sensor DHT22
#include "Timer.h"    //Inclui a biblioteca do Timer para controle do tempo

DHT dht(5, DHT22);   //Define o pino 5 para o sensor DHT22 
int pin = 3;        //Define o pino 3 para o Rele
Timer t;          // Define t para controle do tempo
int pin_buzzer = 9;

void setup() {
  Serial.begin(9600); // Começa o display
  dht.begin(); // Começa o sensor DHT
  pinMode (pin, OUTPUT); // Define a saída do pin 3 (Rele)
  pinMode (pin_buzzer, OUTPUT); // Define a saída do pin 9 para o buzzer
  digitalWrite (pin, HIGH); // definir off o umidificador
  t.every(20000, continuarLeitura); // Chama a função de leitura, ou seja, uma nova execução do sistema
}

void loop() {
  t.update(); // Atualiza a variavel T (Contagem do tempo)
}

float medirUmidade() {  // Função que realiza a média da leitura de 3 umidades do tempo
  float soma = 0;
  soma+= dht.readHumidity();
  soma+= dht.readHumidity();
  soma+= dht.readHumidity();  
  return soma/3;
} 

void ligarUmidificador (int pin){

  digitalWrite (pin, LOW);

}

void desligarUmidificador (int pin) {

  digitalWrite (pin, HIGH); 

}

void ativa_buzzer(){
  int frequencia=440; // frequência correspondente a notá Lá
  tone(pin_buzzer,frequencia);
}

void desativa_buzzer(){
  noTone(pin_buzzer);
}

void continuarLeitura(){
  
  float umidade = medirUmidade(); // Busca a umidade
  Serial.print(umidade); // Mostra a umidade em %
  Serial.print(";");
  if (isnan(umidade)) {
    desligarUmidificador(pin);
    ativa_buzzer(); // ativa o alerta
    Serial.print(00.0);
    Serial.print(";");
    Serial.print(3);
    Serial.println(";");
  } else {
      desativa_buzzer(); // desativa o alerta
     if  (umidade < 65){
        ligarUmidificador(pin);
        Serial.print(1);
        Serial.println(";");
    } else {    
        desligarUmidificador(pin);
        Serial.print(0);
        Serial.println(";");
    }
  }

}


