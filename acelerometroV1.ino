// Demo for getting individual unified sensor data from the MPU6050
#include <Adafruit_MPU6050.h>

float ACELERACAO_GRAVITACIONAL = 9.8;

Adafruit_MPU6050 mpu;
Adafruit_Sensor *mpu_temp, *mpu_accel, *mpu_gyro;

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); 

  Serial.println("Adafruit MPU6050 test!");

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  Serial.println("MPU6050 Found!");
  mpu_temp = mpu.getTemperatureSensor();
  mpu_temp->printSensorDetails();

  mpu_accel = mpu.getAccelerometerSensor();
  mpu_accel->printSensorDetails();

  mpu_gyro = mpu.getGyroSensor();
  mpu_gyro->printSensorDetails();
}

void loop() {
  //  /* Get a new normalized sensor event */
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;

  mpu_temp->getEvent(&temp);
  mpu_accel->getEvent(&accel);
  mpu_gyro->getEvent(&gyro);


// Calcula a magnitude total da aceleração
  float totalAccel = sqrt(pow(accel.acceleration.x, 2) + 
                          pow(accel.acceleration.y, 2) + 
                          pow(accel.acceleration.z - ACELERACAO_GRAVITACIONAL, 2));

  Serial.println("Aceleracao Total: ");
  Serial.println(totalAccel);
  Serial.print(" \t ");

// Define faixas de aceleração para determinar os modos de locomoção

  if (totalAccel < 0.5) {
    Serial.println("Modo: Parado");
  } 
  else if (totalAccel >= 0.5 && totalAccel < 1.5) {
    Serial.println("Modo: Passo Lento");
  } 
  else if (totalAccel >= 1.5 && totalAccel < 2.5) {
    Serial.println("Modo: Passo Normal");
  }
  else if (totalAccel >= 2.5 && totalAccel < 3.5) {
    Serial.println("Modo: Passo Rapido");
  }
  else if (totalAccel >= 3.5 && totalAccel < 5.0) {
    Serial.println("Modo: Trote Leve");
  }
  else if (totalAccel >= 5.0 && totalAccel < 6.5) {
    Serial.println("Modo: Trote Moderado");
  }
  else if (totalAccel >= 6.5 && totalAccel < 8.0) {
    Serial.println("Modo: Trote Forte");
  }
  else if (totalAccel >= 8.0 && totalAccel < 9.0) {
    Serial.println("Modo: Galope Lento");
  }
  else if (totalAccel >= 9.0 && totalAccel < 10.5) {
    Serial.println("Modo: Galope Moderado");
  }
  else {
    Serial.println("Modo: Galope Rapido");
  }

  delay(1000);

}