#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

DFRobotDFPlayerMini mp3;

// Define los pines del sensor de ultrasonido
const int trigPin1 = 3; // (Frente)
const int echoPin1 = 2; // (Frente)

// const int trigPin2 = 7; // (Derecha)
// const int echoPin2 = 6; // (Derecha)

// const int trigPin3 = 13; // (Izquierda)
// const int echoPin3 = 12; // (Izquierda)

// Define el pin del buzzer
const int buzzerPin = 4;
int frequency1 = 1000; // Frecuencia del tono en Hz
// int frequency2 = 300; // Frecuencia del tono en Hz

// const int vibracionPin = 7; // Elige el pin digital que usarás para controlar la vibración

SoftwareSerial mySerial(10, 11); // Configura los pines RX y TX para la comunicación serial con el módulo
bool isPlaying = false;     // Variable para rastrear el estado de reproducción actual

void setup() {
  // Inicializa el puerto serie para imprimir los resultados en la consola
  Serial.begin(9600);
  mySerial.begin(9600);

  // Configura los pines del sensor de ultrasonido
  pinMode(trigPin1, OUTPUT); // (Frente)
  pinMode(echoPin1, INPUT);  // (Frente)

  // pinMode(trigPin2, OUTPUT); // (Derecha)
  // pinMode(echoPin2, INPUT);  // (Derecha)

  // pinMode(trigPin3, OUTPUT); // (Izquierda)
  // pinMode(echoPin3, INPUT);  // (Izquierda)

  // Configura el pin del buzzer
  pinMode(buzzerPin, OUTPUT);

  // // Configura el pin de vibración como una salida
  // pinMode(vibracionPin, OUTPUT);

  mp3.begin(mySerial);    // Inicializa la comunicación con el módulo DFPlayer Mini
  mp3.volume(30);         // Ajusta el volumen del módulo (valores entre 0 y 30)
}

void loop() {
  
  
  sensor1();

  // Lee la duración del eco
  long duration1 = pulseIn(echoPin1, HIGH);
  
  // Calcula la distancia en cm dividiendo la duración del eco por la velocidad del sonido en el aire y dividiendo por dos
  int distance1 = duration1 / 58;
  
  // Si el objeto está a 10 cm o menos de distancia del sensor, muestra un mensaje en la consola
  if (distance1 <= 40 && !isPlaying) {
    Serial.println("INICIO REPRODUCCION");
    playAudio();
  } else if (distance1 <= 40) {
    Serial.println("ALTO");
    buzzerFrente();
  } else {
    Serial.println("TRANQUILO");
    digitalWrite(buzzerPin, LOW);
  }

  // if (distance1 <= 5) {
  //   Serial.println("ALTO");
  //   buzzerFrente();
  //   playAudio();
  // } else {
  //   digitalWrite(buzzerPin, LOW);
  // }

  // sensor2();

  // // Lee la duración del eco
  // long duration2 = pulseIn(echoPin2, HIGH);
  
  // // Calcula la distancia en cm dividiendo la duración del eco por la velocidad del sonido en el aire y dividiendo por dos
  // int distance2 = duration2 / 58;
  
  // // Si el objeto está a 10 cm o menos de distancia del sensor, muestra un mensaje en la consola
  // if (distance2 <= 10) {
  //   Serial.println("DERECHA");
  //   buzzerLados();
  // } else {
  //   digitalWrite(buzzerPin, LOW);
  // }

  // sensor3();

  // // Lee la duración del eco
  // long duration3 = pulseIn(echoPin3, HIGH);
  
  // // Calcula la distancia en cm dividiendo la duración del eco por la velocidad del sonido en el aire y dividiendo por dos
  // int distance3 = duration3 / 58;
  
  // // Si el objeto está a 10 cm o menos de distancia del sensor, muestra un mensaje en la consola
  // if (distance3 <= 10) {
  //   Serial.println("IZQUIERDA");
  //   buzzerLados();
  // } else {
  //   digitalWrite(buzzerPin, LOW);
  // }

  // Esperar un momento antes de volver a medir la distancia
  delay(100);
}

void sensor1() {
  // Establece el pin trigger en bajo durante 2 microsegundos para indicar que se enviará una señal
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);

  // Establece el pin trigger en alto durante 10 microsegundos para enviar una señal de ultrasonido
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
}

// void sensor2() {
//   // Establece el pin trigger en bajo durante 2 microsegundos para indicar que se enviará una señal
//   digitalWrite(trigPin2, LOW);
//   delayMicroseconds(2);

//   // Establece el pin trigger en alto durante 10 microsegundos para enviar una señal de ultrasonido
//   digitalWrite(trigPin2, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(trigPin2, LOW);
// }

// void sensor3() {
//   // Establece el pin trigger en bajo durante 2 microsegundos para indicar que se enviará una señal
//   digitalWrite(trigPin3, LOW);
//   delayMicroseconds(2);

//   // Establece el pin trigger en alto durante 10 microsegundos para enviar una señal de ultrasonido
//   digitalWrite(trigPin3, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(trigPin3, LOW);
// }

void buzzerFrente() {
  digitalWrite(buzzerPin, HIGH);
  // delay(500);
  // noTone(buzzerPin);
  // delay(500);
}

// void buzzerLados() {
//   digitalWrite(buzzerPin, frequency2);
// }

void playAudio() {
  mp3.play(1);    // Reproduce la pista número 1
  isPlaying = true;
}

void stopAudio() {
  mp3.stop();     // Detiene la reproducción
  isPlaying = false;
}


// void vibracion() {
//   digitalWrite(vibracionPin, 255); // enciende el motor
//   delay(1000); // espera un segundo
//   digitalWrite(vibracionPin, LOW); // apaga el motor
//   // delay(1000);
// }

// const int vibracionPin = 7; // Elige el pin digital que usarás para controlar la vibración

// void setup() {
//   // Configura el pin de vibración como una salida
//   pinMode(vibracionPin, OUTPUT);
// }

// void loop() {
//   digitalWrite(vibracionPin, HIGH); // enciende el motor
//   delay(1000); // espera un segundo
//   digitalWrite(vibracionPin, LOW); // apaga el motor
//   delay(1000);
// }