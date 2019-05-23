#include <Servo.h>                                    //Esta es la libreria que nos ayuda a controlar los servo-motores
#include <SoftwareSerial.h>                           //Esta es la libreria que nos ayuda a hacer la comunicación con el Bluetooth
SoftwareSerial BT(10,11);                             //Declaramos el Pin 10 como Rx y el Pin 11 como Tx

Servo Pulgar;                                         //Declaramos el servo-motor con el nombre Pulgar
Servo Indice;                                         //Declaramos el servo-motor con el nombre Indice
Servo Corazon;                                        //Declaramos el servo-motor con el nombre Corazon
Servo Anular;                                         //Declaramos el servo-motor con el nombre Anular
Servo Menique;                                        //Declaramos el servo-motor con el nombre Menique
Servo Muneca;                                         //Declaramos el servo-motor con el nombre Muneca

int msg[6];                                           //Creamos un array para recibir los datos de los sensores flex
float temp = 0;                                       //Creamos un float para poder calcular el tiempo
boolean bloqueado = false;                            //Creamos un boolean para poder desbloquear el Bt.avaiable en caso que se bloquee
boolean datosMotor = false;                           //Creamos un boolean para mover los motores cuando lleguen datos

void setup()
{
  BT.begin(9600);                                     //Iniciamos el bluetooth
  
  Muneca.attach(A5);                                  //Declaramos el servo-motor Muneca en el Pin A5
  Menique.attach(A4);                                 //Declaramos el servo-motor Menique en el Pin A4
  Anular.attach(A3);                                  //Declaramos el servo-motor Anular en el Pin A3      
  Corazon.attach(A2);                                 //Declaramos el servo-motor Corazon en el Pin A2    
  Indice.attach(A1);                                  //Declaramos el servo-motor Indice en el Pin A1
  Pulgar.attach(A0);                                  //Declaramos el servo-motor Pulgar en el Pin A0
  Muneca.write(180);                                  //Iniciamos el servo-motor en la posición de 180 grados
  Menique.writeMicroseconds(1000);                    //Iniciamos el servo-motor en la posición de 0 grados
  Anular.writeMicroseconds(1000);                     //Iniciamos el servo-motor en la posición de 0 grados
  Corazon.writeMicroseconds(1000);                    //Iniciamos el servo-motor en la posición de 0 grados
  Pulgar.writeMicroseconds(1000);                     //Iniciamos el servo-motor en la posición de 0 grados
  Indice.writeMicroseconds(1000);                     //Iniciamos el servo-motor en la posición de 0 grados
  }
 
void loop()
{
  temp = millis();                                    //Declaramos temp como millis para iniciar un temporizador
  while ((BT.available()<18) && (bloqueado == false)) //Mientras que BT.available tenga menos de 18 bites y bloqueado sea falso entra en esta condición
    {
     float currentTime = millis();                    //Creamos un float para terminar el temporizador
     if (currentTime > (temp + 2000))                 //Si currentTime llega a dos segundos entra en esta condición
        { 
        BT.flush();                                   //Al entrar en la condicion limpia la memoria de BT para poder salir del bloqueado
        bloqueado = true;                             //Ponemos bloqueado igual a true para salir de la condición
        }
    }
  bloqueado = false;                                  //Bloqueado volvemos a poner a false para podar volver a entrar
  while (BT.available()>0)                            //Cuando el BT.available sea mayor a cero bites entra en esta condición
   {    
      int num = BT.available();                       //Creamos un int para contar los nueros de bytes que hay en el BT.available
      char buffer[3];                                 //Creamos un buffer cuatro datos tipo char 
      BT.readBytesUntil(',', buffer, 7);              //Esta funcion es para leer los datos hasta cada "," del buffer y tiene un maximo de 7 bloques
      msg[(num/3)-1] = atoi(buffer);                  //Esta función es para decir qeu cada bloque que hemos hecho con la función anterior las enumere
      datosMotor = true;                              //Activamos datosMotor para asi mover los datos
   } 

 if (datosMotor == true)                              //Una condición para evitar movimiento no necesario
   {
     motores();                                       //Función para mover motores
     datosMotor = false;                              //Apagamos datosMotor para que no pueda entrar denuevo sin pasar por a condición anterior
   }                                                               
}                                                                     

void motores()                                                        
{
 int pulgar = map (msg[5], 10, 90, 1000, 2000);       //Es un mapeo para poder mover los motores correctamente
 Pulgar.writeMicroseconds(pulgar);                    //Función para mover los motores  
 int indice = map (msg[4], 10, 90, 1000, 2000);       //Es un mapeo para poder mover los motores correctamente
 Indice.writeMicroseconds(indice);                    //Función para mover los motores
 int corazon = map (msg[3], 10, 90, 1000, 2000);      //Es un mapeo para poder mover los motores correctamente
 Corazon.writeMicroseconds(corazon);                  //Función para mover los motores
 int anular = map (msg[2], 10, 90, 1000, 2000);       //Es un mapeo para poder mover los motores correctamente
 Anular.writeMicroseconds(anular);                    //Función para mover los motores
 int menique = map (msg[1], 10, 90, 1000, 2000);      //Es un mapeo para poder mover los motores correctamente
 Menique.writeMicroseconds(menique);                  //Función para mover los motores
 int muneca = map (msg[0], 10, 90, 2000, 1000);       //Es un mapeo para poder mover los motores correctamente
 Muneca .writeMicroseconds(muneca);                   //Función para mover los motores
}
