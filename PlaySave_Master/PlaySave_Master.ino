//PLAYSAVE MASTER MODULE
//TYPE: MASTER
//MODEL 0000
//Antonio Tarín C.

#include <Wire.h>

//VARIABLES DE INICIALIZACIÓN
int ModuleNumber = 0;
char ModuleName[50] = "PlaySave Alpha - MASTER PIGGYBANK MODULE";
short ActivityLED = 2;
int slaveModuleNumber = -1;

void setup()
{
  //INICIALIZACIÓN DE WIRE Y SERIAL
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output

  //INICIALIZACIÓN DE LED DE ACTIVITY
  pinMode(ActivityLED,OUTPUT); //DEFINIR ACTIVITY LED
  digitalWrite(ActivityLED,LOW); //RESTAURAR EL ESTADO DEL LED

  //MONITOR SERIAL PARA DEBUGGING
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
  
  //LEE EL MODELO DEL MODULO
  slaveModuleNumber = -1;
  do
  {
    Wire.requestFrom(8, 1);
    slaveModuleNumber = Wire.read();
    Serial.print("Connected module number: ");
    if(slaveModuleNumber > 0)
    {
      Serial.print(slaveModuleNumber);
      Serial.print('\n');
      successLED();
    }
    else if(slaveModuleNumber < 0)
    {
      Serial.print('\n');
      Serial.print("No module detected, probing again in 5 seconds");
      Serial.print('\n');
    }

    //ENVIA A LA CONSOLA EL MODELO DEL MODULO
    Serial.print("Connected module name: ");
    switch(slaveModuleNumber)
    {
      case 5:
      Serial.print("PlaySave Alpha - OFFICE BUILDING MODULE");
    }
    Serial.print('\n');
    Serial.print('\n');
    delay(5000);
  } while (slaveModuleNumber < 0);

  Wire.requestFrom(8, 1);
  if(slaveModuleNumber < 0);
  Serial.print("Module has been disconnected.");
  successLED();
  Serial.print('\n');
  
}

void loop()
{
  delay(500);
}

//RUTINA DE PARPADEO DE LED
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

