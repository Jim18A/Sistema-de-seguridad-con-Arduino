//LIBRERIAS
#include <Wire.h> //display
#include <LiquidCrystal_I2C.h> //display
#include <Keypad.h> //teclado

LiquidCrystal_I2C lcd(0x27, 16, 2); //diplay

//--teclado--
const byte ROWS = 4; //n filas
const byte COLS = 4; //n columnas

char keys[ROWS][COLS] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; //pines de filas
byte colPins[COLS] = {5, 4, 3, 2}; //pines de columnas

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//ASIGNACION DE PINES
const int Buzzer = 10; //buzzer
const int Laser = 11; //laser
const int Ldr = 12; //fotoresistor

//Variable para la comunicacion
char dato;

//-----------//-----------//
void setup(){

  //PUERTO SERIAL
  Serial.begin(9600);

  //DISPLAY
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("WELCOME!");
  lcd.setCursor(0, 1);
  lcd.print("Pass:");
  delay(2000);
  
  //BUZZER
  pinMode(Buzzer, OUTPUT);
  digitalWrite(Buzzer, HIGH);

  //LASER
  pinMode(Laser, OUTPUT);
  digitalWrite(Laser, HIGH);
 
  //FOTORESITOR
  pinMode(Ldr, INPUT);
  digitalWrite(Ldr, HIGH);
}
//-----------//-----------//

const char* Pass = "1234"; //la contraseña se almacena en una variable
int npass;
bool verifyPass(char* entrada) {
   return (strcmp(entrada, Pass) == 0);
}
//al ingresar una contraña cualquiera, se compara con la que ya esta definida


char entrada[5];  // Arreglo para almacenar la entrada de la contraseña
  static int i = 0;

//-----------//-----------//
void loop(){

  // COMUNICACION CON LA INTERFAZ
  if (Serial.available()){
    dato=Serial.read();
    Serial.println(dato);
    delay(500);
    
    //-----------//-----------//
    //test de laser
    if(dato== 'l'){
      digitalWrite(Laser, HIGH);
    }
    if(dato == 'j'){
      digitalWrite(Laser, LOW);
    }
    //-----------//-----------//
    //test de alarma
    if(dato== 'p'){
      digitalWrite(Buzzer, LOW);
    }
    if(dato == 'o'){
      digitalWrite(Buzzer, HIGH);
    }
    //-----------//-----------//
    // display  ON/OFF
    if (dato == 'x'){
      lcd.display();
      lcd.backlight();
    }
    if (dato == 'y'){
      lcd.noDisplay();
      lcd.noBacklight();
    }
    //-----------//-----------//
    //CAMBIAR CONTRASEÑA
    if(dato == 'z'){
      Serial.write(Pass);
    }

    if(dato == 'e'){
      npass = Serial.parseInt();
      sprintf(Pass,"%d",npass);
    } 
 }
 //-----------//-----------//
  //Barrera laser
  if(digitalRead(Ldr) == 0 && digitalRead(Laser) == 1 ){
    digitalWrite(Buzzer, LOW);
  } 
  else {
    if(digitalRead(Laser) == 1 && dato != 'p')
      digitalWrite(Buzzer, HIGH);
  }
  //-----------//-----------//
  // CONTROL DE ACCESO
  char key = keypad.getKey();

  if (key) {

    if (key != '#') {
      lcd.display();
      lcd.backlight();
      entrada[i++] = key;
      lcd.print('*');
      digitalWrite(Buzzer, LOW);
      delay(200);
      digitalWrite(Buzzer, HIGH);

    } else {

       entrada[i] = '\0';  
       i= 0;

       if (verifyPass(entrada)) {

         lcd.clear();
         lcd.print("CORRECT");
         digitalWrite(Buzzer, LOW);
         delay(100);
         digitalWrite(Buzzer, HIGH);
         delay(150);
         digitalWrite(Buzzer, LOW);
         delay(100);
         digitalWrite(Buzzer, HIGH);
         digitalWrite(Laser, LOW);
        
        } else {
         lcd.clear();
         lcd.print("INCORRECT");
         digitalWrite(Buzzer, LOW);
         delay(500);
         digitalWrite(Buzzer, HIGH);

         lcd.clear();
         lcd.setCursor(4, 0);
         lcd.print("REPIT PLS");
         digitalWrite(Laser, HIGH);
        }
       delay(2000);  
       lcd.clear();
       lcd.setCursor(4, 0);
       lcd.print("WELCOME!");
       lcd.setCursor(0, 1);
       lcd.print("Pass:");
       i = 0; 
     }
   }
}