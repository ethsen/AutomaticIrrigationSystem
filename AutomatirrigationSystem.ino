
int moistureSensor1 = A0;
int moistureSensor2 = A1;
int moistureSensor3 = A3;

int moistureLevel1 = 0;
int moistureLevel2 = 0;
int moistureLevel3 = 0;

int averageMoisture = 0;
int checkMoisture = 0;

bool isSoilDry;

int pump1 = 7;
int pump2 = 6;

void setup() {
  pinMode(moistureSensor1, INPUT);
  pinMode(moistureSensor2, INPUT);
  pinMode(moistureSensor3, INPUT);
  
  pinMode(pump1, OUTPUT);
  pinMode(pump2, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  moistureSensorAverage(); 
  Serial.println(averageMoisture);
  
  if (averageMoisture > 400){
    isSoilDry = doubleCheckSoil();
    if(isSoilDry){
      waterPlant();
    }
    
  }
}



void moistureSensorAverage(){
  moistureLevel1 = analogRead(moistureSensor1);
  moistureLevel2 = analogRead(moistureSensor2);
  moistureLevel3 = analogRead(moistureSensor3);
 
  averageMoisture = (moistureLevel1 + moistureLevel2 + moistureLevel3)/3;

}

bool doubleCheckSoil(){
  
  moistureLevel1 = analogRead(moistureSensor1);
  moistureLevel2 = analogRead(moistureSensor2);
  moistureLevel3 = analogRead(moistureSensor3);

  checkMoisture = (moistureLevel1 + moistureLevel2 + moistureLevel3)/3;

  if(checkMoisture > 400){
    return true;
  }
  else{
    return false;
  }
  
}

void waterPlant(){
  while(averageMoisture > 400){
    moistureSensorAverage();
    digitalWrite(pump1, LOW);
    digitalWrite(pump2, LOW);
    Serial.println("on");
  }

  digitalWrite(pump1, HIGH);
  digitalWrite(pump2, HIGH);
}
 
