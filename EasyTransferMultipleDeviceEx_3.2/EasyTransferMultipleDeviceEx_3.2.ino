#include <EasyTransfer.h>

/*
   Teensy 3.2
   Only connected to top Teensy 3.5
   Connected by Serial1
   Make this the second transfer structure on the 3.5
*/
#define LAPTOP Serial
#define TEENSY_35_TOP Serial1

// create easy transfer objects
EasyTransfer et1_in, et1_out;           // easy transfer objects

// create receive data structures
// NOTE: the send data structure on the paired board MUST be EXACTLY THE SAME
struct ReceiveStruct1 {
  int16_t data1;
  char string[64];
};

// create send data structures
// NOTE: the receive data structure on the paired board MUST be EXACTLY THE SAME
struct SendStruct1 {
  int16_t data1;
  char string[64];
};

// initialize data objects
ReceiveStruct1 rx1;
SendStruct1 tx1;

// init counter TESTING
int test_counter = 100;

// init testing LED
const int LED_PIN = 13;

void setup() {
  // set up serial connections
  LAPTOP.begin(9600);                 // TESTING ONLY
  TEENSY_35_TOP.begin(115200);                // corresponding to ReceiveStruct1, SendStruct1

  // set up bilateral easy transfer
  et1_in.begin(details(rx1), &TEENSY_35_TOP);
  et1_out.begin(details(tx1), &TEENSY_35_TOP);

  LAPTOP.println("I'm a Teensy 3.2");

  pinMode(LED_PIN, OUTPUT);

}

void loop() {

  // TESTING PURPOSES ONLY
  // ---------------------
  test_counter = (test_counter + 1) % 100 + 100;         // counts from 100 to 200 repeatedly
  tx1.data1 = test_counter;
  // ---------------------

  et1_out.sendData();
  digitalWrite(LED_PIN, HIGH);     // LED is on after transmit

  // receive data
  while (!et1_in.receiveData());

  digitalWrite(LED_PIN, LOW);      // LED is off after receive

  // TESTING PURPOSES ONLY
  // ---------------------
  char out_str[64];
  sprintf(out_str, "Teensy 3.2 receive val: %d", rx1.data1);
  LAPTOP.println(out_str);
  // ---------------------
  delay(50);

}
