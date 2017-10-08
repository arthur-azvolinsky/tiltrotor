#include <Servo.h> 

Servo esc1, esc2, esc3, esc4;
int throttle = 0;

void setup() {
  
  Serial.begin(9600);
  Serial.setTimeout(500);
  
  ESCinit();

}

void loop() {
  if(Serial.available()) throttle = Serial.parseInt();
  Serial.println(throttle);
  esc1.write(throttle);
  esc2.write(throttle);
  esc3.write(throttle*.64 + 692); //51 - 135 1062 - 1931 869
  esc4.write(throttle); //4-136 579-1937 1358
}

void ESCinit(){
  esc1.attach(3);
  esc2.attach(2);
  esc3.attach(5);
  esc4.attach(4);
  
  esc1.write(2000);
  esc2.write(2000);
  esc3.write(2000);
  esc4.write(2000);
  
  esc1.write(0);
  esc2.write(0);
  esc3.write(0);
  esc4.write(0);//esc attachment and low signal, may need more depending on stubbornness of esc calibrations
  
  return 0;
}

//escVal is the esc number, myThrot is the convenient throttle value
//myThrot ranges from 0 to 100
int tConvert (int escVal, int myThrot) {
  int esc1min = 10, esc1max = 150;
  int esc2min = 10, esc2max = 150;
  int esc3min = 10, esc3max = 150;
  int esc4min = 10, esc4max = 150;

  int arr[8] = {esc1min, esc1max, esc2min, esc2max, \
                esc3min, esc3max, esc4min, esc4max}; 
  
  if ((escVal < 1) || (escVal > 4)) {
    Serial.println("Error: Invalid Esc Value\n");
    return -1;
  }

  if ((myThrot < 0) || (myThrot > 100)) {
    Serial.println("Error: Invalid Throttle Value\n");
    return -1;
  }

  double Min = (double) (arr[2*(escVal - 1)]);
  double Max = (double) (arr[2*escVal - 1]);

  double frac = ((double) myThrot)/100.0;
  double ret = Min + (Max - Min)*frac;
  return ((int) ret);
}

  

