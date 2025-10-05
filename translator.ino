// LIBRARIES
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

// HARDWARE PIN DEFINITIONS

const int SENSOR_PINS[5] = {A0, A1, A2, A3, A4};
const int DFPLAYER_RX_PIN = 10;
const int DFPLAYER_TX_PIN = 11;

// K-NEAREST NEIGHBORS (k-NN) CLASSIFIER CONFIGURATION
const int K = 3;

// DATA STRUCTURES
struct GestureData {
  char label;
  int sensorValues[5];
};
