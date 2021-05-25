#include<LiquidCrystal.h> // LCD ekran kütüphanesi

#define USE_ARDUINO_INTERRUPTS true // kısa süreli kesinti tanımlanır
#include <PulseSensorPlayground.h>  // Pulse Sensör kütüphanesi   

// değişkenler
const int PulseWire = 0;   // Pulse Sensörünün Mor Kablosu ANALOG PIN 0’a bağlanır.
const int LED13 = 13;      // Kırmızı LED, PIN 13’e bağlanır.
int Threshold = 510;       // Hangi sinyal seviyesinden itibaren kalp atımı olarak kabul edileceğine karar vermek için bir eşik değeri tanımlanır. 
int nabiz;                         
PulseSensorPlayground pulseSensor;   // PulseSensor kütüphanesinde bulunan fonksiyonları kullanabilmek için bir nesne oluşturulur.    

LiquidCrystal lcd (12, 11, 5, 4, 3, 2);

const int hiz=6;
const int ileri=9;
const int geri=8;

void setup() {
  pinMode(hiz,OUTPUT);
  pinMode(ileri,OUTPUT);
  pinMode(geri,OUTPUT);

  digitalWrite(ileri,HIGH);
  digitalWrite(geri,LOW);
  Serial.begin(9600);

    // PulseSensor nesnesine değerler atanır. 
  pulseSensor.analogInput(PulseWire); 
  pulseSensor.blinkOnPulse(LED13); // Kırmızı LED her kalp atımında yanıp söner.
  pulseSensor.setThreshold(Threshold); // Eşik değeri atanır. 

  // PulseSensor nesnesinin oluşturuluğunu ve değerlerin doğru şekilde atandığını kontrol etmek için LCD ekranda bilgilendirme yapılır.
  if (pulseSensor.begin()) {
    // LCD ekranda bir kere görüntülenir.
    Serial.println("Sensör basariyla çalistirildi.");      
    //lcd.setCursor(0,0);  // LCD ekranın imleç yeri tanımlanır.
    //lcd.print("NABIZ OLCULUYOR");  // Ekrana “NABIZ OLCULUYOR” yazdırılır.
  } 
  
}

void loop() {
    if (pulseSensor.sawStartOfBeat()) {
    Serial.println("Nabiz tespit edildi! "); 
    // Sensöre gelen sinyal eşik değerinin üzerinde ise ise çıktı olarak "nabiz tespit edildi" yazdırılır. 
    nabiz = pulseSensor.getBeatsPerMinute();
    lcd.setCursor(0,0); 
    lcd.print("Nabiz:");    // Ekrana “ NABIZ: “ yazdırılır." 
    lcd.print(nabiz); 
    if(nabiz<70)
    {
      Serial.println("Düşük Nabız! Motor Hızı 255");
      analogWrite(hiz,255);
    }
    else if(nabiz>=70 && nabiz<90)
    {
      Serial.println("Normal Nabız! Motor Hızı 175");
      analogWrite(hiz,175);
    }
    else
    {
      Serial.println("Yüksek Nabız! Motor Hızı 100");
      analogWrite(hiz,100);
    }
    
    //nabiz = analogRead(PulseWire);
    Serial.print("NABIZ: ");  // Output’a “NABIZ: “ yazdırılır.
    Serial.println(nabiz);    // “nabiz” değişkenindeki değer çıktıya yazdırılır.
    //lcd.clear(); 
  }
  delay(500);    // döngü yeniden çalıştırılmadan önce 20 milisaniye beklenir.
  lcd.clear();
  delay(500);
}
