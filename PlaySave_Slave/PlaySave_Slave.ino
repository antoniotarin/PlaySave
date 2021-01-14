//PLAYSAVE OFFICE BUILDING MODULE
//TYPE: SLAVE
//MODEL 0001
//Antonio Tarín C.

#include <Wire.h>

//VARIABLES DE INICIALIZACIÓN
int ModuleNumber = 5;
char ModuleName[50] = "PlaySave Alpha - OFFICE BUILDING MODULE";
short ActivityLED = 2;

void setup()
{
  //PROCESO DE INICIALIZACIÓN
  pinMode(ActivityLED,OUTPUT); //DEFINIR ACTIVITY LED
  digitalWrite(ActivityLED,LOW); //RESTAURAR EL ESTADO DEL LED

  //MONITOR SERIAL PARA DEBUGGING
  Serial.begin(9600);
  //TRAS INICIALIZAR, SE MUESTRAN LOS DATOS DE LA PLACA
  Serial.print("MODEL NAME:");
  Serial.print('\n');
  for(int i=0; i<50; i++)
  {
    Serial.print(ModuleName[i]);
  }
  Serial.print('\n');
  Serial.print('\n');
  Serial.print("MODEL NUMBER:");
  Serial.print('\n');
  Serial.print(ModuleNumber);
  Serial.print('\n');
  Serial.print('\n');
  //TERMINA MONITOR SERIAL

  //TRES PARPADEOS INDICAN EXITO EN EL BOOT
  successLED();

  //INICIA SESIÓN PRINCIPAL
  Wire.begin(8);    //SE INSCRIBE A LA RED CON DIRECCIÓN 8
  //ENVIA PARAMETROS DE IDENTIFICACIÓN AL MASTER
  Wire.onRequest(sendModuleNumber);
  
}

void loop()
{
  delay(100);
}

//ENVIA EL ID DEL MODULO AL MASTER
void sendModuleNumber()
{
  Wire.write(ModuleNumber);
  Serial.write("Evento registrado: Modulo maestro conectado");
  Serial.write('\n');
  Serial.write("Enviando variables de identificación...");
  Serial.write(".");
  Serial.write('\n');
  thinkingLED(5);
  Serial.write("Se han enviado las variables de identificación");
  Serial.write('\n');

}

//3 PARPADEOS: EXITO EN LA OPERACION
void successLED()
{
  for(int i=0; i!=3; i++)
  {
    digitalWrite(ActivityLED, HIGH);
    delay(500);
    digitalWrite(ActivityLED, LOW);
    delay(500);
  }
}

//INTERMITENCIA: PROCESO EN PROGRESO
void thinkingLED(int timer)
{
  for(int i=0; i!=timer; i++)
  {
    digitalWrite(ActivityLED, HIGH);
    delay(200);
    digitalWrite(ActivityLED, LOW);
    delay(200);
  }
}

