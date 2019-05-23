#include <SoftwareSerial.h>                                               // Incluimos la librería  SoftwareSerial  
SoftwareSerial BT(10,11);                                                 // Definimos los pines RX y TX del Arduino conectados al Bluetooth

int msg[6];                                                               //Definimos msg como un array de seis
int krn[6] = {10, 10, 10, 10, 10, 10};                                    //Definimos krn como un array de seis iniciando todos a con 10
boolean DatosChange = false;                                              //Definimos DatosChange como un boolean falso

int Pulgar;                                                               //Definimos Pulgar como un int
int Indice;                                                               //Definimos Inice como un int
int Anular;                                                               //Definimos Anular como un int
int Corazon;                                                              //Definimos Corazon como un int
int Menique;                                                              //Definimos Menique como un int
int Muneca = 10;                                                          //Definimos Muneca como 10 con un int

void setup()
{
  BT.begin(9600);                                                         //Inicializamos el puerto serie BT (Para Modo AT 2)
  Serial.begin(9600);                                                     //Inicializamos  el puerto serie  
}
 
void loop()
{
  mapFlex();                                                              //Función del mapeado de son Sensres Flex
  ComparacionDatos();                                                     //Función de la comparación de datos
  if(DatosChange==true)                                                   //Condición para mover los datos
  {
     envioDatos();                                                        //Función para mandar los datos
     DatosChange = false;                                                 //Cambiamos DatosChange a falso
  }   
  delay(500);                                                             //Retraso de medio segundo
}
void mapFlex()
{
   Menique = analogRead(A5);                                              //Declaramos Pulgar para que lea el A5
   Menique = map (Pulgar, 570, 785, 10, 90);                              //Mapeo del Menique
   if(Pulgar>90)Pulgar=90;                                                //Condición para que no de datos más de 90
   else if(Pulgar<10)Pulgar=10;                                           //Condición para que no de datos menos de 10
   
   Anular = analogRead(A4);                                               //Declaramos Indice para que lea el A4
   Anular = map (Indice, 583, 885, 10, 90);                               //Mapeo del Anular
   if(Indice>90)Indice=90;                                                //Condición para que no de datos más de 90
   else if(Indice<10)Indice=10;                                           //Condición para que no de datos menos de 10
   
   Corazon = analogRead(A3);                                              //Declaramos Corazon para que lea el A3
   Corazon = map (Corazon, 565, 837, 10, 90);                             //Mapeo del Corazon
   if(Corazon>90)Corazon=90;                                              //Condición para que no de datos más de 90
   else if(Corazon<10)Corazon=10;                                         //Condición para que no de datos menos de 10
   
   Indice = analogRead(A2);                                               //Declaramos Anular para que lea el A2
   Indice = map (Anular, 630, 870, 10, 90);                               //Mapeo del Indice
   if(Anular>90)Anular=90;                                                //Condición para que no de datos más de 90
   else if(Anular<10)Anular=10;                                           //Condición para que no de datos menos de 10
   
   Pulgar = analogRead(A1);                                               //Declaramos Menique para que lea el A1
   Pulgar = map (Menique, 580, 835, 10, 90);                              //Mapeo del Pulgar
   if(Menique>90)Menique=90;                                              //Condición para que no de datos más de 90
   else if(Menique<10)Menique=10;                                         //Condición para que no de datos menos de 10
} 

void ComparacionDatos()                                                   //Función de comparación de datos
{
   msg[0] = Pulgar;                                                       //Declaramos msg[0] como Pulgar
   msg[1] = Indice;                                                       //Declaramos msg[1] como Indice
   msg[2] = Corazon;                                                      //Declaramos msg[2] como Corazon
   msg[3] = Anular;                                                       //Declaramos msg[3] como Anular
   msg[4] = Menique;                                                      //Declaramos msg[4] como Menique
   msg[5] = Muneca;                                                       //Declaramos msg[5] como Muneca
   
   if((krn[0] > (msg[0]+10))||(krn[0] < (msg[0]-10)))                     //Condicion para lectura de cambio de datos
     {
      krn[0] = Pulgar;                                                    //Declaramos krn[0] como Pulgar
      DatosChange = true;                                                 //Cambiamos DatosChange a verdadero
     }
   if((krn[1] > (msg[1]+10))||(krn[1] < (msg[1]-10)))                     //Condicion para lectura de cambio de datos
     {
      krn[1] = Indice;                                                    //Declaramos krn[1] como Pulgar
      DatosChange = true;                                                 //Cambiamos DatosChange a verdadero
     }
   if((krn[2] > (msg[2]+10))||(krn[2] < (msg[2]-10)))                     //Condicion para lectura de cambio de datos
     {
      krn[2] = Corazon;                                                   //Declaramos krn[2] como Pulgar
      DatosChange = true;                                                 //Cambiamos DatosChange a verdadero
     }
   if((krn[3] > (msg[3]+10))||(krn[3] < (msg[3]-10)))                     //Condicion para lectura de cambio de datos
     {
      krn[3] = Anular;                                                    //Declaramos krn[3] como Pulgar
      DatosChange = true;                                                 //Cambiamos DatosChange a verdadero
     }
   if((krn[4] > (msg[4]+10))||(krn[4] < (msg[4]-10)))                     //Condicion para lectura de cambio de datos
     {
      krn[4] = Menique;                                                   //Declaramos krn[4] como Pulgar
      DatosChange = true;                                                 //Cambiamos DatosChange a verdadero
     }
}

void envioDatos()                                                         //Función de envio de datos
{
  for (int i=0; i<6;i++)                                                  //Un for para enviar todos los datos a la vez
  {
    BT.print(krn[i]);                                                     //Imprimimos por el BT los datos krn
    BT.print(',');                                                        //Imprimimos por el BT un ',' despues de cada dato
  }
}


