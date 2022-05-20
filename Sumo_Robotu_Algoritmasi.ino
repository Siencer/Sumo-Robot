//MOTOR KONTROLU
int sagMotorHiz = 11; //Sağ tekerleğin hızını belirleyecek motor
int sagMotorYon = 13; //Sağ tekerleğin döneceği yönü belirleyecek motor
int solMotorHiz = 3; //Sol tekerleğin hızını belirleyecek motor
int solMotorYon = 12; //Sol tekerleğin döneceği yönü belirleyecek motor

//KOSE RENK SENSORLERI
int sagKnt = A0; //Robotunun sağ ön alt kısmında bulunan renk sensörü
int solKnt = A1; //Robotunun sol ön alt kısmında bulunan renk sensörü

//UZAKLIK SENSORLERI
int solUzaklik = A4; //Robotun solunda bulunan uzaklık algılama sensörü 
int sagUzaklik = A2; //Robotun sağında bulunan uzaklık algılama sensörü 
int ortaUzaklik = A3; //Robotun önünde bulunan uzaklık algılama sensörü 

// BUTON
int buton = 10; //Robotu başlatabilmek için kullanılan buton

//DEGISKENLER 
int hiz = 50; // Robotun hızını belirleyen değişken
int Maxhiz = 50; // Robota herhangi bir sensör bilgisi gelmediğinde gideceği sabit hız değişkeni
int donusHizi = 55; // Sağ veya sol yöne dönüş hızını belirleyen değişken
int donusSiniri = 190; // Robotun beyaz zeminde olduğunu anlaması için gereken süreyi belirleyen değişken
int sonDeger = 5; // En son görülen engelin nerede olduğunu hatırlamak için kullanılan değişken

void setup() 
{
  pinMode(solUzaklik, INPUT); 
  pinMode(sagUzaklik, INPUT); 
  pinMode(ortaUzaklik, INPUT);
  
  pinMode(buton, INPUT);

  pinMode(sagMotorHiz, OUTPUT);
  pinMode(sagMotorYon, OUTPUT);
  pinMode(solMotorHiz, OUTPUT);
  pinMode(solMotorYon, OUTPUT);

  Serial.begin(9600);
  tone(9, 480, 250); //Robot açıldıktan sonra çıkarttığı sesi belirleyen kısım
  delay(300);
  noTone(9); //Ses çıkarttıktan sonra durmasını ses çıkartmayı bırakmasını sağlayan kısım
}

//Motor Kontrol Foksiyonu
void Set_Motor(float solDeger, float sagDeger, int gecikme) 
{
    if (solDeger >= 0) 
    {
      analogWrite(solMotorHiz, solDeger);
      digitalWrite(solMotorYon, LOW);
    } 
    else {
      solDeger = abs(solDeger);
      digitalWrite(solMotorYon, HIGH);
      analogWrite(solMotorHiz, solDeger);
    }
    if (sagDeger >= 0) 
    {
      analogWrite(sagMotorHiz, sagDeger);
      digitalWrite(sagMotorYon, HIGH);
    } 
    else
    {
      sagDeger = abs(sagDeger);
      digitalWrite(sagMotorYon, LOW);
      analogWrite(sagMotorHiz, sagDeger);
    }
    delay(gecikme);

    void loop() {
      digitalWrite(sagMotorHiz, LOW);
      digitalWrite(solMotorHiz, LOW);

      Wait:
        Serial.println("Butona basilmasi bekleniyor...");
      Set_Motor(0, 0, 1);
      if (digitalRead(buton) == 1) {
        goto Start;
      }
      goto Wait;

      //Ana dongü başlangıcı
      Start:
        //Renk sensörlerinin algotirması
        //KÜÇÜK OLAN DEĞERLER BEYAZ DEMEK
        if (analogRead(solKnt) < 100 && analogRead(sagKnt) > 100) { 

          Set_Motor(100, 100, 35);
          Set_Motor(100, -100, donusSiniri); // Sağ geri , sol ileri
          sonDeger = 5;
        }
      else if (analogRead(solKnt) > 100 && analogRead(sagKnt) < 100) {

        SSet_Motor(100, 100, 35);
        Set_Motor(100, -100, donusSiniri); // Sağ ileri, sol geri
        sonDeger = 5;
      } else
        //Engel algılama algoritması
        
        if (digitalRead(ortaUzaklik) == LOW) {
          Set_Motor(100, 100, 1);
          
          sonDeger = 5;
        }

      else if (digitalRead(solUzaklik) == LOW) {
        Set_Motor(-100, 100, 1);
        
        sonDeger = 7;
      } 
      else if (digitalRead(sagUzaklik) == LOW) {
        Set_Motor(100, -100, 1);
        
        sonDeger = 3;
      } 
      else {

        if (sonDeger == 5) {
          Set_Motor(40, 40, 1);
        } 
        else if (sonDeger == 7) {
          Set_Motor(-20, 80, 2);
        } 
        else if (sonDeger == 3) {
          Set_Motor(80, -20, 2);
        }
      }
      goto Start;
    }
