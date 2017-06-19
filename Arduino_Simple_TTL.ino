/*
 * Simple Arduino 4 Channel TTL Pulse Generator
 * Optogenetics and Neural Engineering Core ONE Core
 * University of Colorado
 * 10/5/16
 * See optogenetic.ucdenver.edu for more information, including a detailed write up and Arduino/BNC housing 3D Model
 * 
 * In this example, (4) unique TTL signals are sent out from the Arduino. Any time one signal changes, the condition of the Arduino changes.
 * The duration of each condition is set as well as the state of each channel.
 */

//This section defines the pins on the Arduino. We specify the intigers (int) TTL1 through TTL4.
//If you expanding this to require 6 channels, uncomment the last two lines here and add additional code below where needed.
int TTL1 = 2;
int TTL2 = 4;
int TTL3 = 7;
int TTL4 = 8;
//int TTL5 = 12;
//int TTL6 = 13; //Though, not recommend, as there are slight differences in this pin. If you must use pin 13 as a digital input, set its pinMode() to INPUT and use an external pull down resistor.

//This tells the Arduino to treat the pins as output. In this example, all channels are output. For an example with input (closed loop), see the Arduino-Simple_Closed_Loop.ino file section.
void setup() {
pinMode(TTL1, OUTPUT);
pinMode(TTL2, OUTPUT);
pinMode(TTL3, OUTPUT);
pinMode(TTL4, OUTPUT);
}

//Draw out the desired waves for each channel on paper, on the same timeline, such that channel 1 appears over channel 2, etc. The condition (or state) of the Arduino changes any time any of the channels change. See the write up for more information.
//Define the number of conditions. Define the length of time (in ms) for each condition. 
int con1 = 25;
int con2 = 25;
int con3 = 25;
int con4 = 25;
int con5 = 0;  //May be tempting to do, but it is recommended that the end of a pulse train NOT be considered as a condition.

//This is the code that the Arduino loops through. It will start on condition 1 and then move through the rest of the conditions and then auto restart back at condition 1.
//It writes each pin as High/ON or Low/Off for each condition, and the waits for the duration of condition (set above). 
void loop() {
    //Condition 1
  digitalWrite(TTL1,HIGH);
  digitalWrite(TTL2,HIGH);
  digitalWrite(TTL3,HIGH);
  digitalWrite(TTL4,LOW);
  delay(con1);
  
    //Condition 2
  digitalWrite(TTL1,HIGH);
  digitalWrite(TTL2,LOW);
  digitalWrite(TTL3,HIGH);
  digitalWrite(TTL4,LOW);
  delay(con2);

    //Condition 3
  digitalWrite(TTL1,LOW);
  digitalWrite(TTL2,HIGH);
  digitalWrite(TTL3,LOW);
  digitalWrite(TTL4,LOW);
  delay(con3);

    //Condition 4
  digitalWrite(TTL1,LOW);
  digitalWrite(TTL2,LOW);
  digitalWrite(TTL3,HIGH);
  digitalWrite(TTL4,LOW);
  delay(con4);

    //Condition 5    //May be tempting to do, but it is recommended that the end of a pulse train NOT be considered as a condition. Doing this may present problems as outlined in the write up (Channel 3).
  digitalWrite(TTL1,LOW);
  digitalWrite(TTL2,LOW);
  digitalWrite(TTL3,LOW);
  digitalWrite(TTL4,LOW);
  delay(con5);  
}

