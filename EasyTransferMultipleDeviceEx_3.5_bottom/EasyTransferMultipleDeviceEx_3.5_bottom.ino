#include <EasyTransfer.h>

/*
   Teensy 3.5 Bottom
   Connected to Teensy 3.5 Top (Serial1)
   Teensy 3.5 Top -- corresponds to first ET structure
*/

#define LAPTOP Serial
#define TEENSY_35_TOP Serial1

// create easy transfer objects
EasyTransfer et1_in, et1_out;            // first easy transfer objects

// create receive data structures
// NOTE: the send data structure on the paired board MUST be EXACTLY THE SAME
// corresponds to SendStruct1 on Teensy3.5 top
struct ReceiveStruct1 {
  char string[64];
  int16_t data1;
};

// create send data structures
// NOTE: the receive data structure on the paired board MUST be EXACTLY THE SAME
// corresponds to ReceiveStruct1 on Teensy3.5 top
struct SendStruct1 {
  char string[64];
  int32_t data1;
  int16_t data2;
};


// initialize data objects
ReceiveStruct1 rx1;
SendStruct1 tx1;

// init testing led
const int LED_PIN = 13;

// init counter TESTING
int test_counter = 0;

void setup() {
  // set up serial connections
  LAPTOP.begin(9600);                 // TESTING ONLY
  TEENSY_35_TOP.begin(115200);                // corresponding to ReceiveStruct1, SendStruct1

  // set bilateral up easy transfer for each connection
  et1_in.begin(details(rx1), &TEENSY_35_TOP);
  et1_out.begin(details(tx1), &TEENSY_35_TOP);

  pinMode(LED_PIN, OUTPUT);

}

void loop() {

  // TESTING PURPOSES ONLY
  // ---------------------
  test_counter = (test_counter + 1) % 100;         // counts from 0 to 100 repeatedly
  tx1.data2 = test_counter;
  // ---------------------

  et1_out.sendData();
  digitalWrite(LED_PIN, HIGH);     // LED is on after transmit

  // receive data
  while(!et1_in.receiveData());

  digitalWrite(LED_PIN, LOW);      // LED is off after receive

  // TESTING PURPOSES ONLY
  // ---------------------
  char out_str[64];
  sprintf(out_str, "Teensy 3.5 Bottom receive val: %d", rx1.data1);
  LAPTOP.println(out_str);
  // ---------------------
  delay(50);

}
