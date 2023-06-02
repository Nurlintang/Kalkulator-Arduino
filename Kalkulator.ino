//c++ code

/* Menyambungkan Arduino dengan hardware lainnya */

#include <Keypad.h> //Library keypad
const byte ROWS = 4; 
const byte COLS = 4; 


char hexakeys[ROWS][COLS] = { 
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowpins[ROWS] = {A0, A1, A2, A3}; 
byte colpins[COLS] = {11, 10, 9, 8}; 


Keypad customKeypad = Keypad(makeKeymap(hexakeys),
                              rowpins, colpins, ROWS, COLS);

#include <LiquidCrystal.h> //Library LCD
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); 


char operasi;
char step;
enum {inAngkaPertama, inAngkaKedua, outhasil};
String strAngkaPertama = " ", strAngkaKedua = " ";
float AngkaPertama, AngkaKedua;
float hasil; 

void setup() { 
  lcd.begin(16,2); 
  lcd.print("TEST KALKULATOR"); 
  delay (1000); 
  lcd.clear(); 
  Serial.begin(9600); 
}

void loop(){ 
 char customKey = customKeypad.getKey(); 
    switch (step){   
      case inAngkaPertama:
        if(customKey){
        
           if(customKey == 'A'){
             lcd.setCursor(15,0);
             lcd.print("+");

             operasi = '+';  
             step = inAngkaKedua;
           }
        
           else if(customKey == 'B'){
             lcd.setCursor(15,0);
             lcd.print('-');

             operasi = '-';
             step = inAngkaKedua;
           }
        
           else if(customKey == 'C'){
             lcd.setCursor(15,0);
             lcd.print('x');

             operasi = 'x';
             step = inAngkaKedua;
           }

           else if(customKey == 'D'){
             lcd.setCursor(15,0);
             lcd.print('/');

             operasi = '/';
             step = inAngkaKedua;
           }

           else{
               strAngkaPertama += customKey;
               lcd.setCursor(0,0);
               lcd.print(strAngkaPertama);
           }
         }
  	break; 
    
    case inAngkaKedua:
          if(customKey){

              if(customKey == '#'){
                step = outhasil;
              }

              else{
                strAngkaKedua += customKey;
                lcd.setCursor(0,1);
                lcd.print(strAngkaKedua);
              }
            }
    break; 
    
    case outhasil:
      
          AngkaPertama = strAngkaPertama.toInt();
          AngkaKedua = strAngkaKedua.toInt();
    
         
           if(operasi == '+'){
             hasil = AngkaPertama + AngkaKedua;
             }
         
           else if(operasi == '-'){
             hasil = AngkaPertama - AngkaKedua;
             }

           else if(operasi == 'x'){
             hasil = AngkaPertama * AngkaKedua;
             }

           else if(operasi == '/'){
             hasil = AngkaPertama / AngkaKedua;
             }

              lcd.setCursor(9,1);
              lcd.print(hasil);
    
    if(customKey){
      
        if(customKey == '*'){
          strAngkaPertama = " ";
          strAngkaKedua = " ";
          lcd.clear();
          step = inAngkaPertama;
        }
    }
    break; 
  }        
} 