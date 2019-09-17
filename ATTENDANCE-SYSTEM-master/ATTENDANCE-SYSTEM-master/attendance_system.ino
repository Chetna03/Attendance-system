#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
void setup() {
  lcd.begin(16,2);
  Serial.begin(9600);
  lcd.println("__ATTENDANCE__  ");
  lcd.setCursor(0,1);
  lcd.println(" MARKING SYSTEM ");
  delay(2000);
  lcd.clear();
  lcd.println("PLACE YOUR CARD");
}
unsigned char name1[4][12]={"19004D617C49","19004AFFA30F","000083A6B095","000083CB662E"};
unsigned char data[12];
void loop() {
  // put your main code here, to run repeatedly:
  unsigned int i;
  static int d=0;
  if (Serial.available() > 0){
      data[d++]=Serial.read();
      if(d==12)
      {
          lcd.clear();
          for(i=0;i<12;i++)
          {
            Serial.write(data[i]);
          }
          delay(2000);
          d=match();
          lcd.clear();
          if(d!=9)
          {
            print_username(d);            
          }
          else
          {
            lcd.println("NOT AUTHORISED");
            delay(500);
            Serial.println("\r\nNOT AUTHORISED\r\n");
          }
          delay(1000);
          lcd.clear();
          lcd.println("PLACE YOUR CARD");
          delay(500);
          Serial.println("PLACE YOUR CARD\r\n");
          d=0;
      }
  }
}
int match()
{
  int matched=0;
  int i,j,k=0;
  for(j=0;j<4;j++)
  {
    k=0;
    for(i=0;i<12;i++)
    {
      if(data[i]==name1[j][i])
      {
        k++;
      }
      else
      {
        break;
      }
    }
    
    if(k==12)
    {
      matched=1;
      return j;
      break;
    }
  }
  if(matched==0)
  {
    return 9;
  }
}
void print_username(unsigned int user)            //USED IN CASE OF ATTENDACE MARKING SYSTEM
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.println("AUTHORISED USER ");
  delay(500);
  lcd.setCursor(0,1);
  switch(user)
  {
    case 0: lcd.println("Madhu Chaudhry   ");break;
    case 1: lcd.println("Tanuja   ");break;
    case 2: lcd.println("Dolly Sharma   ");break;
    case 3: lcd.println("Mr. Vikash Sindhu   ");break;
  }
  delay(1000);
}

