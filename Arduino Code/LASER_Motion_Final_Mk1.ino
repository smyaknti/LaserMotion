#include<SoftwareSerial.h>

/* 
PINOUTS: 

Bluetooth RX: 11
          TX: 10
PD: PD1: A1
    PD2: A2
PD High pins: digital 3 and 5;    
*/
int bluetoothTx = 10;
int bluetoothRx = 11;

SoftwareSerial bluetooth( bluetoothTx, bluetoothRx);

void setup() {
  
  pinMode(13,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  bluetooth.begin(9600);
  Serial.begin(9600);
}

int PDtwo;
int PDone;
int flag;
int PDPower=255;
int i;
int btdata=0;

void loop() {
  digitalWrite(3,PDPower);
  digitalWrite(5,PDPower);
  flag=0;
  btdata=0;
  PDone=analogRead(1);
  PDtwo=analogRead(2);
  Serial.println(PDone); Serial.println(PDtwo);
  if((PDone>=35)&&(PDtwo>=35))
  { btdata=5;
    }
  else
  {
    if(PDone>=35)
  {
    for(i=0;i<1000;i++)
    {
      PDtwo=analogRead(2);
      if(PDtwo>=35)
      {
        flag=1;
         btdata=1; //Run 1st command here!!(swipe from 1 to 2) 
        break;
      }
      delay(1);
    }    
  if(flag==0)
  {
    btdata=2;//Run 2nd command here!!(Block 1)
  }
  }
  else if(PDtwo>=35)
  {
    
    for(i=0;i<1000;i++)
    {
      PDone=analogRead(1);
      if(PDone>=35)
      {
        flag=1;
         btdata=3;//Run 3rd command here!!(Swipe frm 2 to 1) 
        break;
      }
      delay(1);
    }    
    if(flag==0)
    {
      btdata=4;//Run 4th command here!!(block 2)
    }
  }
} 
 if(btdata!=0)
{  bluetooth.println(btdata);
    Serial.println(btdata);
   digitalWrite(13,HIGH);
   delay(500);
   digitalWrite(13,LOW);
}
delay(100);
}
