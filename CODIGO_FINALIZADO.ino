#include <PubSubClient.h>

#include <UIPEthernet.h>
#include <utility/logging.h>

#include <SPI.h>

//Variável utilizada para enviar as mensagens utilizando o cliente MQTT
bool mensagem; 

//Define o endereço MAC que será utilizado
byte mac[] = { 0xDC, 0x4E, 0x49, 0xCB, 0xB0, 0x18 };

int pino2 = 2; //Cria uma variável para o Pino 2
bool estado_sensor;  //Cria uma variável para armazenar o estado do sensor 

//Inicia o cliente Ethernet
EthernetClient client;



//Inicia o client MQTT
PubSubClient mqttClient(client);

void setup() {
   
    pinMode (pino2,INPUT_PULLUP);  //Coloca o Pino 2 como Entrada 
 Serial.begin(9600); //Inicia o Monitor Serial

    //Inicia o controlador Ethernet e solicita um IP para o servidor de DHCP
    Ethernet.begin(mac);

    //Inicia o monitor Serial
    Serial.begin(9600);

    mqttClient.setServer("54.174.235.157",1883);

    //Exibe no Monitor Serial as informações sobre o IP do Arduino
    Serial.print("O IP do Arduino e: ");
    Serial.println(Ethernet.localIP());

    //Exibe no Monitor Serial as informações sobre a Máscara de Rede do Arduino
    Serial.print("A Mascara de Rede do Arduino e: ");
    Serial.println(Ethernet.subnetMask());

    //Exibe no Monitor Serial as informações sobre o Gateway do Arduino
    Serial.print("O Gateway do Arduino e: ");
    Serial.println(Ethernet.gatewayIP());

    //Exibe uma linha em branco 
    Serial.println("");

     
}

void loop() {
estado_sensor = digitalRead(pino2); //Efetua a leitura do Pino 2 e armazena o valor obtido na variável  
   
   mqttClient.connect("giovannaaraujo");
   
  if (estado_sensor==0){
    Serial.println("O rack esta fechado");
    mensagem = mqttClient.publish("giovannaaraujo-t", "FECHADO");

  }
  else {
    Serial.println("O rack esta aberto");
    mensagem = mqttClient.publish("giovannaaraujo-t", "ABERTO");

  }
  
  Serial.println(estado_sensor); //Exibe no Monitor Serial o Estado do Sensor 

Serial.println(mensagem);

   //Função que verifica a conexão entre o Cliente e o Broker e evita a queda de conexão entre eles.
    mqttClient.loop();

   
} 
