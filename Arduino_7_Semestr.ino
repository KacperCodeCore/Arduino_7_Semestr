// int t = 10;
// int brightness = 0;
// int fadeAmount = 5; // Wartość o jaką zmienia się jasność przy każdym kroku

// void setup() {
//   pinMode(5, OUTPUT);
//   pinMode(6, OUTPUT);
//   pinMode(7, OUTPUT);
// }

// void loop() {
//   analogWrite(5, brightness);
//   analogWrite(6, brightness);
//   analogWrite(7, brightness);
//   delay(t);

//   brightness = brightness + fadeAmount;

//   if (brightness <= 0 || brightness >= 50) {
//     fadeAmount = -fadeAmount; // Zmiana kierunku zmiany jasności na przeciwny
//   }




// }



// // ##########################################################
// // Arduino Hardware Ćwiczenia
// // 1A Odczyt Adresu Sensora

// #include <OneWire.h>
// OneWire ds(9);

// void setup() {
//   Serial.begin(9600);
// }

// void loop() {
//   byte addr[8];
//   if(!ds.search(addr)){
//     Serial.println("no more adresses");
//     Serial.println();

//     ds.reset_search();
//     delay(8000);
//     return;
//   }
//   Serial.print("Adres: ");
//   for(int i = 0; i < 8; i++){
//     Serial.write(" ");
//     Serial.print(addr[i], HEX);
//   }
//   Serial.println();
// }

// // Adres:  28 99 25 8A D 0 0 C1
// // no more adresses

// // -------------------------------------------
// // Odczyt Temperatury

#include <OneWire.h>
OneWire ds(9);
byte addr[8] = {0x28, 0x99, 0x25, 0x8A, 0xD, 0x0, 0x0, 0xC1};
float celcius = 0;
float previousCelcious = 0;

int brightness = 50;


void setup() {
  pinMode(5, OUTPUT); // dioda red
  pinMode(6, OUTPUT); // dioda
  pinMode(7, OUTPUT); // dioda

  Serial.begin(9600);
}

void loop() {
  Serial.println(temperatura(addr)); // aktualna temperatura
  diodaTemperature();
  delay(1000);
  previousCelcious = celcius;
}

float temperatura(byte addr[]){
  
  byte data[9];
  ds.reset();
  ds.select(addr);
  ds.write(0x44);
  // delay(1000);
  ds.reset();
  ds.select(addr);
  ds.write(0xBE);
  for (int i = 0; i < 9; i++){
    data[i] = ds.read();
  }
  int16_t raw = (data[1] << 8) | data[0];
  celcius = (float)raw / 16.0;
  return celcius;

}

void diodaTemperature(){
  if(celcius > previousCelcious){
    digitalWrite(5, 50);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    Serial.println("Rosnie");
  }
  else if(celcius == previousCelcious){
    digitalWrite(5, LOW);
    digitalWrite(6, 50);
    digitalWrite(7, LOW);
    Serial.println("Stala");
  } else{
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, 50);
    Serial.println("Maleje");
  }
}
