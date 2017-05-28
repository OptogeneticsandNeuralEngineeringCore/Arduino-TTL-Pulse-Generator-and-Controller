/*
   Simple Arduino 4 Channel TTL Closed Loop Generator
   Optogenetics and Neural Engineering Core ONE Core
   University of Colorado
   10/5/16
   See optogenetic.ucdenver.edu for more information, including a detailed write up and Arduino/BNC housing 3D Model
   
   In this example, an Arduino Mega is used to sense a animal behavior in a four arm maze. Four IR beams detect presence of the animal. Based on which arm the animal is detected in, the Arduino can output TTL 
   pulses appropriate for lasers and reward. We assume only one animal per experiment and only one sensor can be activated at a time. When the animal is in Arms 1 or 3, we wish to stimulate ontogenetically
   a laser for CHR2. When the animal is in Arm 2, we wish to stimulate a laser appropriate for Jaws. When the animal is in Arm 4 we wish to open a reward port.
   
   TTL 1-4: Arduino inputs: sensors in maze arms 1-4
   TTL 5: Arduino output: continuous power for the IR Beams
   TTL 6: Arduino output: TTL signal to trigger laser for CHR2 activation
   TTL 7: Arduino output: TTL signal to trigger laser for Jaws activation

   Arduino MEGA inputs/outputs TTL (PWM) on pins 2-13 and 44-46.

   Appropriate stimulation of CHR2 is 10 ms pulses, repeated 20 times at 20 Hz.

   Appropriate stimulation of Jaws is 1 second pulse, repeated once at .1 Hz.

   The reward port is closed when the TTL pulse is set to high and opens when it goes low. The animal has 4 seconds to retrieve the reward after the beam is broken.
*/

//This section defines the pins on the Arduino. Simply define all inputs/outputs
int TTL1 = 2;       //We set this pin (the first PWM on Mega) to sense the nose poke of the first arm
int TTL2 = 3;       //We set this pin to sense the nose poke of the second arm
int TTL3 = 4;       //We set this pin to sense the nose poke of the third arm
int TTL4 = 5;       //We set this pin to sense the nose poke of the fourth arm
int TTL5 = 6;       //Power for the IR Beams so then can send IR Light

int TTL6 = 7;       //Signal to control the LED or Laser for CHR2 activation
int TTL7 = 8;       //Signal to control the LED or Laser for Jaws activation
int TTL8 = 9;       //Signal to control reward port 

//This section defines variables that the Arduino will use to define the state of the sensors. There are 4 sensors, so we need four sensor states
int sensorState1 = LOW;
int sensorState2 = LOW;
int sensorState3 = LOW;
int sensorState4 = LOW;

//Now we write the pulse train for the outputs of the system: two optogenetic stimulation and one reward port. Because we assumed that the the animal can only break one beam at a time, the
  //outputs are independent. Therefore, the conditions of each output are independent. 
//Draw out the desired waves for each output. The condition (or state) of the Arduino changes any time the channels change. See the write up for more information.
//Define the number of conditions. Define the length of time (in ms) for each condition.
//Define the number of times to repeat the pulse train
int ChR2con1 = 10;
int ChR2con2 = 40;
int ChR2numrepeat = 20;

int Jawscon1 = 1000;
int Jawscon2 = 10000-Jawscon1;
int Jawsnumrepeat =1;

int Rewardcon1 = 4000;
int Rewardnumrepeat = 1;

//Placeholder for Arduino to count with
int i = 0;

//This section sets up the Arduino to treat the pins as output or input and the initial states.
void setup() 
{
  pinMode(TTL1, INPUT);       //Arm1
  pinMode(TTL2, INPUT);       //Arm2
  pinMode(TTL3, INPUT);       //Arm3
  pinMode(TTL4, INPUT);       //Arm4
  pinMode(TTL5, OUTPUT);      //Sensor power
  pinMode(TTL6, OUTPUT);      //Laser1
  pinMode(TTL7, OUTPUT);      //Laser2
  pinMode(TTL8, OUTPUT);      //Reward
  
  digitalWrite(TTL1, HIGH);   //This defines the original state of the sensor (when it is open and detecting IR light) as high/on
  digitalWrite(TTL2, HIGH);   //This defines the original state of the sensor (when it is open and detecting IR light) as high/on
  digitalWrite(TTL3, HIGH);   //This defines the original state of the sensor (when it is open and detecting IR light) as high/on
  digitalWrite(TTL4, HIGH);   //This defines the original state of the sensor (when it is open and detecting IR light) as high/on
          
  digitalWrite(TTL5, HIGH);   //This turns on TTL5. We do not change it in the rest of the code so that we can use this to power the IR light and sensor
  digitalWrite(TTL6, LOW);    //The intial state of the laser is off
  digitalWrite(TTL7, LOW);    //The intial state of the laser is off
  digitalWrite(TTL8, HIGH);    //The intial state of the reward is closed (high)
}

//This is the code that the Arduino loops through. It reads each sensor in series. If a sensor changes state (the beam is broken), it then outputs TTLs. 
void loop() 
{
  
  ///////////////////////////Read the IR sensor1
  sensorState1 = digitalRead (TTL1);

  //Check to see if the beam is broken.
  if (sensorState1 == LOW) 
  {
    //If sensor1 (Arm1) is broken (LOW), 
    for (int i = 0; i < ChR2numrepeat; i++) 
    {
      //Condition 1
      digitalWrite(TTL6, HIGH);
      delay(ChR2con1);

      //Condition 2
      digitalWrite(TTL6, LOW);
      delay(ChR2con2);

      //This states that when the optogenetic stimulation loop is completed, then set the read pin back to high, just as was done in the initialization.
      //You need not worry too much about this, but if you would like more information, SparkFun has a pretty good tutorial on 'floating' and 'pull up resistors'
      if (i == ChR2numrepeat - 1) 
      {
      digitalWrite(TTL1, HIGH);
      }
    }
  }
  
  //Without this section, optogenetic stimulation would be provided if the beam was continuously broken. We want only one stimulation pattern for a given nose poke.
  //Reread the IR sensor. We want to check that the mouse has left the nose poke before we deliver another stimulation.
  while (sensorState1 == LOW) 
  {
    delay(500);
    sensorState1 = digitalRead (TTL1);
  }

 
  ///////////////////////////Read the IR sensor2
  sensorState2 = digitalRead (TTL2);

  //Check to see if the beam is broken.
  if (sensorState2 == LOW) 
  {
    //If sensor2 (Arm2) is broken (LOW), 
    for (int i = 0; i < Jawsnumrepeat; i++) 
    {
      //Condition 1
      digitalWrite(TTL7, HIGH);
      delay(Jawscon1);

      //Condition 2
      digitalWrite(TTL7, LOW);
      delay(Jawscon2);

      //This states that when the optogenetic stimulation loop is completed, then set the read pin back to high, just as was done in the initialization.
      //You need not worry too much about this, but if you would like more information, SparkFun has a pretty good tutorial on 'floating' and 'pull up resistors'
      if (i == Jawsnumrepeat - 1) 
      {
      digitalWrite(TTL2, HIGH);
      }
    }
  }
  
  //Without this section, optogenetic stimulation would be provided if the beam was continuously broken. We want only one stimulation pattern for a given nose poke.
  //Reread the IR sensor. We want to check that the mouse has left the nose poke before we deliver another stimulation.
  while (sensorState2 == LOW) 
  {
    delay(500);
    sensorState2 = digitalRead (TTL2);
  }

  ///////////////////////////Read the IR sensor3
  sensorState3 = digitalRead (TTL3);

  //Check to see if the beam is broken.
  if (sensorState3 == LOW) 
  {
    //If sensor3 (Arm3) is broken (LOW), 
    for (int i = 0; i < ChR2numrepeat; i++) 
    {
      //Condition 1
      digitalWrite(TTL6, HIGH);
      delay(ChR2con1);

      //Condition 2
      digitalWrite(TTL6, LOW);
      delay(ChR2con2);

      //This states that when the optogenetic stimulation loop is completed, then set the read pin back to high, just as was done in the initialization.
      //You need not worry too much about this, but if you would like more information, SparkFun has a pretty good tutorial on 'floating' and 'pull up resistors'
      if (i == ChR2numrepeat - 1) 
      {
      digitalWrite(TTL3, HIGH);
      }
    }
  }
  
  //Without this section, optogenetic stimulation would be provided if the beam was continuously broken. We want only one stimulation pattern for a given nose poke.
  //Reread the IR sensor. We want to check that the mouse has left the nose poke before we deliver another stimulation.
  while (sensorState3 == LOW) 
  {
    delay(500);
    sensorState3 = digitalRead (TTL3);
  }


///////////////////////////Read the IR sensor4
  sensorState4 = digitalRead (TTL4);

  //Check to see if the beam is broken.
  if (sensorState4 == LOW) 
  {
    //If sensor4 (Arm4) is broken (LOW), 
    for (int i = 0; i < Rewardnumrepeat; i++) 
    {
      //Condition 1
      digitalWrite(TTL8, LOW);
      delay(Rewardcon1);

      //This states that when the reward loop is completed, then set the read pin back to high, just as was done in the initialization.
      //You need not worry too much about this, but if you would like more information, SparkFun has a pretty good tutorial on 'floating' and 'pull up resistors'
      if (i == Rewardnumrepeat - 1) 
      {
      digitalWrite(TTL4, HIGH);
      digitalWrite(TTL8, HIGH);
      }
    }
  }
  
  //Without this section, reward would be provided if the beam was continuously broken. We want only one stimulation pattern for a given nose poke.
  //Reread the IR sensor. We want to check that the mouse has left the nose poke before we deliver another stimulation.
  while (sensorState4 == LOW) 
  {
    delay(500);
    sensorState4 = digitalRead (TTL4);
  }

}

