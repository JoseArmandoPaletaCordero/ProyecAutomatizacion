#include <SPI.h>  //Importamos librería comunicación SPI
#include <Ethernet.h>  //Importamos librería Ethernet

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };//Ponemos la dirección MAC de la Ethernet Shield que está con una etiqueta debajo la placa
IPAddress ip(192,168,1,177);
EthernetServer server(80);//Creamos un servidor Web con el puerto 80 que es el puerto HTTP por defecto
String HTTP_req;          // Para guardar la peticion del cliente
boolean LED_status = 0;
int led1=2;
int led2=3;
int led3=4;
int led4=5;
int led5=6;
int led6=7;
int led7=8;
int led8=9;
int led9=10;
String estado1="OFF"; //Estado de la Lampara inicialmente en "OFF"
String estado2="OFF"; //Estado del ventilador inicialmente en "OFF"

void setup()
{
 Serial.begin(9600);

 // Inicializamos la comunicación Ethernet y el servidor
 Ethernet.begin(mac, ip);
 server.begin();
 Serial.print("server is at ");
 Serial.println(Ethernet.localIP());

for(int i=2;i<11;i++)
  pinMode(i,OUTPUT);
  
}

void loop()
{
 EthernetClient client = server.available(); //Creamos un cliente Web
 //Cuando detecte un cliente a través de una petición HTTP
 if (client) {
   Serial.println("new client");
   boolean currentLineIsBlank = true; //Una petición HTTP acaba con una línea en blanco
   String cadena=""; //Creamos una cadena de caracteres vacía
   while (client.connected()) {
     if (client.available()) {
       char c = client.read();//Leemos la petición HTTP carácter por carácter
       Serial.write(c);//Visualizamos la petición HTTP por el Monitor Serial
       cadena.concat(c);//Unimos el String 'cadena' con la petición HTTP (c). De esta manera convertimos la petición HTTP a un String

        //Ya que hemos convertido la petición HTTP a una cadena de caracteres, ahora podremos buscar partes del texto.
        int posicion1=cadena.indexOf("LED="); //Guardamos la posición de la instancia "LED=" a la variable 'posicion1'

         if(cadena.substring(posicion1)=="LED=ON")//Si a la posición 'posicion1' hay "LED=ON"
         {
           digitalWrite(led1,HIGH);
    digitalWrite(led7,HIGH);
    digitalWrite(led6,HIGH);
    delay(8000);
    digitalWrite(led1,LOW);
    digitalWrite(led7,LOW);
    delay(1000);
    digitalWrite(led1,HIGH);
    digitalWrite(led7,HIGH);
    delay(1000);
    digitalWrite(led1,LOW);
    digitalWrite(led7,LOW);
    delay(1000);
    digitalWrite(led1,HIGH);
    digitalWrite(led7,HIGH);
    delay (1000);
    digitalWrite(led1,LOW);
    digitalWrite(led7,LOW);
    digitalWrite(led8,HIGH);
    digitalWrite(led2,HIGH);
    delay(2000);
    digitalWrite(led8,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led6,LOW);
    digitalWrite(led4,HIGH);
    digitalWrite(led3,HIGH);
    digitalWrite(led9,HIGH);
    delay(2000);
    digitalWrite(led4,LOW);
    delay(1000);
    digitalWrite(led4,HIGH);
    delay(1000);
    digitalWrite(led4,LOW);
    delay(1000);
    digitalWrite(led5,HIGH);
    delay(1000);
    digitalWrite(led5,LOW);
    digitalWrite(led3,LOW);
    digitalWrite(led9,LOW);
    estado1="ON";
         }
         if(cadena.substring(posicion1)=="LED=OFF")//Si a la posición 'posicion1' hay "LAMPARA=OFF"
         {
           digitalWrite(led1,LOW);
    digitalWrite(led7,LOW);
    digitalWrite(led6,LOW);
    delay(2000);
    digitalWrite(led1,LOW);
    digitalWrite(led7,LOW);
    delay(1000);
    digitalWrite(led1,LOW);
    digitalWrite(led7,LOW);
    delay(1000);
    digitalWrite(led1,LOW);
    digitalWrite(led7,LOW);
    delay(1000);
    digitalWrite(led1,LOW);
    digitalWrite(led7,LOW);
    delay(1000);
    digitalWrite(led1,LOW);
    digitalWrite(led7,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led8,LOW);
    delay(2000);
    digitalWrite(led2,LOW);
    digitalWrite(led8,LOW);
    digitalWrite(led6,LOW);
    digitalWrite(led3,LOW); 
    digitalWrite(led4,LOW);
    digitalWrite(led9,LOW);
    delay(6000);
    digitalWrite(led4,LOW);
    delay(1000);
    digitalWrite(led4,LOW);
    delay(1000);
    digitalWrite(led4,LOW);
    delay(1000);
    digitalWrite(led4,LOW);
    delay(1000);
    digitalWrite(led4,LOW); 
    digitalWrite(led5,LOW);
    delay(2000);
    digitalWrite(led3,LOW);
    digitalWrite(led5,LOW);
    digitalWrite(led9,LOW);
    estado1="OFF";
         }

      
        

 
       //Cuando reciba una línea en blanco, quiere decir que la petición HTTP ha acabado y el servidor Web está listo para enviar una respuesta
       if (c == 'n' && currentLineIsBlank) {

           // Enviamos al cliente una respuesta HTTP
           client.println("HTTP/1.1 200 OK");
           client.println("Content-Type: text/html");
           client.println();

           //Página web en formato HTML
           client.println("<html>");
           client.println("<head>");
           client.println("</head>");
           client.println("<body>");
           client.println("<h1 align='center'>Secuencia de LEDS </h1><h4 align='center'>Creado por Equipo 1 M</h4><h2 align='center'>Control de led</h2>");
           //Creamos los botones. Para enviar parametros a través de HTML se utiliza el metodo URL encode. Los parámetros se envian a través del símbolo '?'
           client.println("<div style='text-align:center;'>");
           client.println("<button onClick=location.href='./?LED=ON' style='margin:auto;background-color: #84B1FF;color: snow;padding: 10px;border: 1px solid #3F7CFF;width:65px;'>");
           client.println("ON");
           client.println("</button>");
           client.println("<button onClick=location.href='./?LED=OFF' style='margin:auto;background-color: #84B1FF;color: snow;padding: 10px;border: 1px solid #3F7CFF;width:65px;'>");
           client.println("OFF");
           client.println("</button>");
           client.println("<br /><br />");
           client.println("<b>LED = ");
           
           client.print(estado2);
           client.println("</b><br />");
           client.println("</b></body>");
           client.println("</html>");
           break;
       }
       if (c == 'n') {
         currentLineIsBlank = true;
       }
       else if (c != 'r') {
         currentLineIsBlank = false;
       }
     }
   }
   //Dar tiempo al navegador para recibir los datos
   delay(1);
   client.stop();// Cierra la conexión
 }
}
