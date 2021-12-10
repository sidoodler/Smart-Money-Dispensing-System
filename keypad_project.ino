 #include <Keypad.h>
 #include <LiquidCrystal.h>
 #include <Servo.h>

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns

char keys[ROWS][COLS] = { // Define the Keymap
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = { 22, 24, 26, 28 };// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.

byte colPins[COLS] = { 30, 32, 34 ,36}; // Connect keypad COL0, COL1, COL2 and COL3 to these Arduino pins.

//const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
const int rs = 42, en = 40, d4 = 44, d5 = 46, d6 = 48, d7 = 50;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );// Create the Keypad
Servo servo10;
int ar[4],br[4],aval,bval;

#define led10 13
#define led20 12
#define led50 11
#define led100 10
#define k0 23
#define k1 25
#define k2 27
#define k3 29
#define rst 38
#define a0 31
#define a1 33
#define a2 35
#define a3 37
#define b0 39
#define b1 41
#define b2 43
#define b3 45
#define note10 8
#define note20 9
#define trigger 7

void setup() {
  // put your setup code here, to run once:
  pinMode(led10,OUTPUT);
  pinMode(led20,OUTPUT);
  pinMode(led50,OUTPUT);
  pinMode(led100,OUTPUT);
  pinMode(k0,OUTPUT);
  pinMode(k1,OUTPUT);
  pinMode(k2,OUTPUT);
  pinMode(k3,OUTPUT);
  digitalWrite(k0,LOW);
  digitalWrite(k1,LOW);
  digitalWrite(k2,LOW);
  digitalWrite(k3,LOW);
  pinMode(trigger,OUTPUT);
  digitalWrite(trigger,LOW);
  pinMode(rst,OUTPUT);
  pinMode(a0,INPUT);
  pinMode(a1,INPUT);
  pinMode(a2,INPUT);
  pinMode(a3,INPUT);
  pinMode(b0,INPUT);
  pinMode(b1,INPUT);
  pinMode(b2,INPUT);
  pinMode(b3,INPUT);
  pinMode(note10,OUTPUT);
  pinMode(note20,OUTPUT);
  digitalWrite(rst,LOW);
  lcd.begin(16,2);
  lcd.print("Enter A");
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  char key = kpd.getKey();
  lcd.setCursor(0,0);
  lcd.print("Enter A");
  digitalWrite(rst,LOW);
  digitalWrite(k0,LOW);
  digitalWrite(k1,LOW);
  digitalWrite(k2,LOW);
  digitalWrite(k3,LOW);
  if(trigger==HIGH)
    digitalWrite(trigger,LOW);
  else
    digitalWrite(trigger,HIGH);
  if(key)  // Check for a valid key.
  {
    Serial.println("Before 1 key");
    switch(key)
    {
      case 'A': 
        digitalWrite(k0,LOW);
        digitalWrite(k1,HIGH);
        digitalWrite(k2,LOW);
        digitalWrite(k3,HIGH);
        if(trigger==HIGH)
          digitalWrite(trigger,LOW);
        else
          digitalWrite(trigger,HIGH);
        lcd.clear();
        lcd.setCursor(0,0);
        Serial.println("Entered A");
        lcd.print("Enter Denom.");
        delay(200);
        char key2;
        int b=0;
        do
        {

          key2=kpd.getKey();
          Serial.println("to enter key2");
          if(key2)
          {
            Serial.println("Entered inside A");
            switch(key2)
            {
              case '2': digitalWrite(led10,LOW);
                        digitalWrite(led20,HIGH);
                        digitalWrite(led50,LOW);
                        digitalWrite(led100,LOW);
                        digitalWrite(k0,LOW);
                        digitalWrite(k1,HIGH);
                        digitalWrite(k2,LOW);
                        digitalWrite(k3,LOW);
                        if(trigger==HIGH)
                          digitalWrite(trigger,LOW);
                        else
                          digitalWrite(trigger,HIGH);
                        lcd.clear();
                        lcd.setCursor(0,0);
                        lcd.print("Enter B");
                        Serial.println("2 of A");
                        b=1;
                        break;
              case '3': digitalWrite(led10,LOW);
                        digitalWrite(led20,LOW);
                        digitalWrite(led50,HIGH);
                        digitalWrite(led100,LOW);
                        digitalWrite(k0,HIGH);
                        digitalWrite(k1,HIGH);
                        digitalWrite(k2,LOW);
                        digitalWrite(k3,LOW);
                        if(trigger==HIGH)
                          digitalWrite(trigger,LOW);
                        else
                          digitalWrite(trigger,HIGH);
                        lcd.clear();
                        lcd.setCursor(0,0);
                        lcd.print("Enter B");
                        b=1;
                        break;
              case 'B': lcd.clear();
                        lcd.setCursor(0,0);
                        lcd.print("Which Note?");
                        digitalWrite(led10,LOW);
                        digitalWrite(led20,LOW);
                        digitalWrite(led50,LOW);
                        digitalWrite(led100,LOW);
                        digitalWrite(k0,HIGH);
                        digitalWrite(k1,HIGH);
                        digitalWrite(k2,LOW);
                        digitalWrite(k3,HIGH);
                        if(trigger==HIGH)
                          digitalWrite(trigger,LOW);
                        else
                          digitalWrite(trigger,HIGH);
                        delay(500);
                        break;
              default: lcd.clear();
                      lcd.setCursor(0,0);
                      Serial.println("Entered A invalid");
                      lcd.print("Invalid Input!");
                      if(b==0)
                      {
                        lcd.setCursor(0,1);
                        lcd.print("Enter Denom.");
                      }
                      else
                      {
                        lcd.setCursor(0,1);
                        lcd.print("Enter B");
                      }
                      break;                  
            }
          }
        }while(key2!='B');

        
        char key3;
        do
        {
          int c=0;
          do
          {
            
            if(trigger==HIGH)
              digitalWrite(trigger,LOW);
            else
              digitalWrite(trigger,HIGH);
            key3=kpd.getKey();
            Serial.println("to enter key3");
            if(key3)
            {
              switch(key3)
              {
                case '1': digitalWrite(led10,HIGH);
                          digitalWrite(led20,LOW);
                          digitalWrite(led50,LOW);
                          digitalWrite(led100,LOW);
                          digitalWrite(k0,HIGH);
                          digitalWrite(k1,LOW);
                          digitalWrite(k2,LOW);
                          digitalWrite(k3,LOW);
                          if(trigger==HIGH)
                            digitalWrite(trigger,LOW);
                          else
                            digitalWrite(trigger,HIGH);
                          delay(500);
                          lcd.clear();
                          lcd.setCursor(0,0);
                          lcd.print("Enter C OR");
                          lcd.setCursor(0,1);
                          lcd.print("Update Denom.");
                          c=1;
                          break;
                case '2': digitalWrite(led10,LOW);
                          digitalWrite(led20,HIGH);
                          digitalWrite(led50,LOW);
                          digitalWrite(led100,LOW);
                          digitalWrite(k0,LOW);
                          digitalWrite(k1,HIGH);
                          digitalWrite(k2,LOW);
                          digitalWrite(k3,LOW);
                          if(trigger==HIGH)
                            digitalWrite(trigger,LOW);
                          else
                            digitalWrite(trigger,HIGH);
                          delay(500);
                          lcd.clear();
                          lcd.setCursor(0,0);
                          lcd.print("Enter C or");
                          lcd.setCursor(0,1);
                          lcd.print("Update Denom.");
                          c=1;
                          break;
                case 'C': lcd.clear();
                          lcd.setCursor(0,0);
                          lcd.print("No. of notes?");
                          Serial.println("Entered before C");
                          digitalWrite(led10,LOW);
                          digitalWrite(led20,LOW);
                          digitalWrite(led50,LOW);
                          digitalWrite(led100,LOW);
                          digitalWrite(k0,LOW);
                          digitalWrite(k1,LOW);
                          digitalWrite(k2,HIGH);
                          digitalWrite(k3,HIGH);
                          if(trigger==HIGH)
                            digitalWrite(trigger,LOW);
                          else
                            digitalWrite(trigger,HIGH);
                          delay(500);
                          break;
                default: lcd.clear();
                          lcd.setCursor(0,0);
                          lcd.print("Invalid Input!");
                          if(c==0)
                          {
                            lcd.setCursor(0,1);
                            lcd.print("Which note?");
                          }
                          else
                          {
                            lcd.setCursor(0,1);
                            lcd.print("Enter C");
                          }
                          break;                  
              }
            }
          }while(key3!='C');
  
          char key4;
          do
          {
            key4=kpd.getKey();
            Serial.println("Entered after C");
            if(key4)
            {
              if(key4=='0' || key4=='1' || key4=='2' || key4=='3' || key4=='4' || key4=='5' || key4=='6' || key4=='7' || key4=='8' || key4=='9')
              {
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("B other,D cnfirm");
                lcd.setCursor(0,1);
                lcd.print("or Update notes");
                Serial.println("Entered after C part1");
                if(key4=='0')
                {
                  digitalWrite(k0,HIGH);
                  digitalWrite(k1,HIGH);
                  digitalWrite(k2,HIGH);
                  digitalWrite(k3,HIGH);
                  if(trigger==HIGH)
                    digitalWrite(trigger,LOW);
                  else
                    digitalWrite(trigger,HIGH);
                }
                if(key4=='1')
                {
                  digitalWrite(k0,HIGH);
                  digitalWrite(k1,LOW);
                  digitalWrite(k2,LOW);
                  digitalWrite(k3,LOW);
                  if(trigger==HIGH)
                    digitalWrite(trigger,LOW);
                  else
                    digitalWrite(trigger,HIGH);
                }
                if(key4=='2')
                {
                  digitalWrite(k0,LOW);
                  digitalWrite(k1,HIGH);
                  digitalWrite(k2,LOW);
                  digitalWrite(k3,LOW);
                  if(trigger==HIGH)
                    digitalWrite(trigger,LOW);
                  else
                    digitalWrite(trigger,HIGH);
                }
                if(key4=='3')
                {
                  digitalWrite(k0,HIGH);
                  digitalWrite(k1,HIGH);
                  digitalWrite(k2,LOW);
                  digitalWrite(k3,LOW);
                  if(trigger==HIGH)
                    digitalWrite(trigger,LOW);
                  else
                    digitalWrite(trigger,HIGH);
                }
                if(key4=='4')
                {
                  digitalWrite(k0,LOW);
                  digitalWrite(k1,LOW);
                  digitalWrite(k2,HIGH);
                  digitalWrite(k3,LOW);
                  if(trigger==HIGH)
                    digitalWrite(trigger,LOW);
                  else
                    digitalWrite(trigger,HIGH);
                }
                if(key4=='5')
                {
                  digitalWrite(k0,HIGH);
                  digitalWrite(k1,LOW);
                  digitalWrite(k2,HIGH);
                  digitalWrite(k3,LOW);
                  if(trigger==HIGH)
                    digitalWrite(trigger,LOW);
                  else
                    digitalWrite(trigger,HIGH);
                }
                if(key4=='6')
                {
                  digitalWrite(k0,LOW);
                  digitalWrite(k1,HIGH);
                  digitalWrite(k2,HIGH);
                  digitalWrite(k3,LOW);
                  if(trigger==HIGH)
                    digitalWrite(trigger,LOW);
                  else
                    digitalWrite(trigger,HIGH);
                }
                if(key4=='7')
                {
                  digitalWrite(k0,HIGH);
                  digitalWrite(k1,HIGH);
                  digitalWrite(k2,HIGH);
                  digitalWrite(k3,LOW);
                  if(trigger==HIGH)
                    digitalWrite(trigger,LOW);
                  else
                    digitalWrite(trigger,HIGH);
                }
                if(key4=='8')
                {
                  digitalWrite(k0,LOW);
                  digitalWrite(k1,LOW);
                  digitalWrite(k2,LOW);
                  digitalWrite(k3,HIGH);
                  if(trigger==HIGH)
                    digitalWrite(trigger,LOW);
                  else
                    digitalWrite(trigger,HIGH);
                }
                if(key4=='9')
                {
                  digitalWrite(k0,HIGH);
                  digitalWrite(k1,LOW);
                  digitalWrite(k2,LOW);
                  digitalWrite(k3,HIGH);
                  if(trigger==HIGH)
                    digitalWrite(trigger,LOW);
                  else
                    digitalWrite(trigger,HIGH);
                }
              }
              else if(key4=='D')
              { 
                aval=0;
                bval=0;
                digitalWrite(k0,HIGH);
                digitalWrite(k1,LOW);
                digitalWrite(k2,HIGH);
                digitalWrite(k3,HIGH);
                if(trigger==HIGH)
                    digitalWrite(trigger,LOW);
                else
                    digitalWrite(trigger,HIGH);
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Thank you!");
                delay(1000);
                digitalWrite(k0,LOW);
                digitalWrite(k1,LOW);
                digitalWrite(k2,LOW);
                digitalWrite(k3,LOW);
                if(trigger==HIGH)
                    digitalWrite(trigger,LOW);
                else
                    digitalWrite(trigger,HIGH);
                delay(200);
                /*
                ar[0]=digitalRead(a0);
                Serial.println(ar[0]);
                ar[1]=digitalRead(a1);
                Serial.println(ar[1]);
                ar[2]=digitalRead(a2);
                Serial.println(ar[2]);
                ar[3]=digitalRead(a3);
                Serial.println(ar[3]);
                br[0]=digitalRead(b0);
                Serial.println(br[0]);
                br[1]=digitalRead(b1);
                Serial.println(br[1]);
                br[2]=digitalRead(b2);
                Serial.println(br[2]);
                br[3]=digitalRead(b3);
                Serial.println(br[3]);
                for(int l=0;l<4;l++)
                {
                  if(ar[l]==HIGH)
                  {
                    aval+=pow(2,l);
                  }
                  if(br[l]==HIGH)
                  {
                    bval+=pow(2,l);
                  }
                }
                for(int z=0;z<aval;z++)
                {
                  digitalWrite(note10,HIGH);
                  delay(500);
                  digitalWrite(note10,LOW);
                  delay(500);
                }
                for(int z=0;z<bval;z++)
                {
                  digitalWrite(note20,HIGH);
                  delay(500);
                  digitalWrite(note20,LOW);
                  delay(500);
                } */
                
                delay(4000);
                digitalWrite(rst,HIGH);
                delay(1000);
                lcd.clear();
                Serial.println("Entered after C part2");
              }
              else if(key4=='B')
              {
                digitalWrite(k0,HIGH);
                digitalWrite(k1,HIGH);
                digitalWrite(k2,LOW);
                digitalWrite(k3,HIGH);
                if(trigger==HIGH)
                    digitalWrite(trigger,LOW);
                else
                    digitalWrite(trigger,HIGH);
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Which note?");
                Serial.println("Entered after C part3");
              }
              else 
              {
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Invalid Input!");
                lcd.setCursor(0,1);
                lcd.print("No. of notes?");
              }
            }
          }while(key4!='D' && key4!='B');
          key3=key4;
        }while(key3=='B');

        break;
        
      default: lcd.clear();
        Serial.println("Entered default of A");
        lcd.setCursor(0,0);
        lcd.print("Invalid input!");
        lcd.setCursor(0,1);
        lcd.print("Enter A");
        break;
    }
  }
}
