#include <EasyTransfer.h>

/*
   Teensy 3.5 Top
   Connected to both Teensy 3.5 Bottom (Serial1) and Teensy3.2 (Serial2)
   Teensy 3.5 bottom -- corresponds to first ET structure
   Teensy 3.2 -- corresponds to second ET structure
*/

#define LAPTOP Serial
#define TEENSY_32 Serial2
#define TEENSY_35_BOTTOM Serial1

// create easy transfer objects
EasyTransfer et1_in, et1_out;           // first easy transfer objects
EasyTransfer et2_in, et2_out;            // second easy transfer objects

// create receive data structures
// NOTE: the send data structure on the paired board MUST be EXACTLY THE SAME
// corresponds to SendStruct1 on Teensy3.5 bottom
struct ReceiveStruct1 {
  char string[64];
  int32_t data1;
  int16_t data2;
};

// same as SendStruct1 on Teensy3.2
struct ReceiveStruct2 {
  int16_t data1;
  char string[64];
};

// create send data structures
// NOTE: the receive data structure on the paired board MUST be EXACTLY THE SAME
// corresponds to ReceiveStruct1 on Teensy3.5 bottom
struct SendStruct1 {
  char string[64];
  int16_t data1;
};

// same as ReceiveStruct1 on Teensy3.2
struct SendStruct2 {
  int16_t data1;
  char string[64];
};

// initialize data objects
ReceiveStruct1 rx1;
SendStruct1 tx1;

ReceiveStruct2 rx2;
SendStruct2 tx2;

// init testing led
const int LED_PIN = 13;

// init counter TESTING
int test_counter = 0;

// channel switch
bool channel_switch = true;

void setup() {
  // set up serial connections
//  LAPTOP.begin(9600);                 // TESTING ONLY
  TEENSY_35_BOTTOM.begin(115200);                // corresponding to ReceiveStruct1, SendStruct1
  TEENSY_32.begin(115200);                // corresponding to ReceiveStruct2, SendStruct2

  // set bilateral up easy transfer for each connection
  et1_in.begin(details(rx1), &TEENSY_35_BOTTOM);
  et1_out.begin(details(tx1), &TEENSY_35_BOTTOM);

  et2_in.begin(details(rx2), &TEENSY_32);
  et2_out.begin(details(tx2), &TEENSY_32);

  pinMode(LED_PIN, OUTPUT);

}

void loop() {

  // TESTING PURPOSES ONLY
  // ---------------------
  test_counter = (test_counter + 1) % 100;         // counts from 0 to 100 repeatedly
  tx1.data1 = test_counter;
  tx2.data1 = test_counter;
  // ---------------------

  digitalWrite(LED_PIN, HIGH);     // LED is on after transmit

  // receive data
  if (channel_switch) {
    et1_out.sendData();
    while(!(et1_in.receiveData()));
  }
  else {
    et2_out.sendData();
    while(!(et2_in.receiveData()));
  }

  channel_switch = !channel_switch;
  
  digitalWrite(LED_PIN, LOW);      // LED is off after receive

  // TESTING PURPOSES ONLY
  // ---------------------
  char out_str[64];
  sprintf(out_str, "Teensy 3.5 Top receive vals: %d, %d", rx1.data2, rx2.data1);
  LAPTOP.println(out_str);
  // ---------------------
  delay(25);


}
