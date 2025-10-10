
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>


const int SENSOR_PINS[5] = {A0, A1, A2, A3, A4};
const int DFPLAYER_RX_PIN = 10;
const int DFPLAYER_TX_PIN = 11;

const int K = 3;

struct GestureData {
  char label;
  int sensorValues[5];
};

const GestureData trainingData[] = {
  
  { 'A', {645, 355, 350, 348, 352}}, { 'A', {650, 348, 355, 351, 349}}, { 'A', {655, 352, 347, 353, 350}},
  { 'B', {352, 648, 652, 351, 649}}, { 'B', {348, 652, 648, 349, 651}}, { 'B', {350, 650, 650, 350, 650}},
  { 'C', {349, 351, 648, 652, 350}}, { 'C', {351, 349, 652, 648, 348}}, { 'C', {350, 350, 650, 650, 352}},
  { 'D', {355, 645, 350, 655, 350}}, { 'D', {350, 650, 348, 650, 351}}, { 'D', {348, 655, 352, 645, 349}},
  { 'E', {351, 648, 352, 349, 350}}, { 'E', {349, 652, 348, 351, 348}}, { 'E', {350, 650, 350, 350, 352}},
  { 'F', {352, 350, 648, 652, 649}}, { 'F', {348, 348, 652, 648, 651}}, { 'F', {350, 352, 650, 650, 650}},
  { 'G', {349, 651, 649, 651, 350}}, { 'G', {351, 649, 651, 649, 348}}, { 'G', {350, 650, 650, 650, 352}},
  { 'H', {648, 352, 349, 351, 650}}, { 'H', {652, 348, 351, 349, 648}}, { 'H', {650, 350, 350, 350, 652}},
  { 'I', {355, 350, 645, 350, 350}}, { 'I', {350, 348, 650, 352, 348}}, { 'I', {348, 352, 655, 348, 352}},
  { 'K', {652, 350, 348, 649, 651}}, { 'K', {648, 348, 352, 651, 649}}, { 'K', {650, 352, 350, 650, 650}},
  { 'L', {350, 649, 351, 349, 651}}, { 'L', {348, 651, 349, 351, 649}}, { 'L', {352, 650, 350, 350, 650}},
  { 'M', {351, 349, 651, 351, 649}}, { 'M', {349, 351, 649, 349, 651}}, { 'M', {350, 350, 650, 350, 650}},
  { 'N', {649, 351, 649, 351, 350}}, { 'N', {651, 349, 651, 349, 348}}, { 'N', {650, 350, 650, 350, 352}},
  { 'O', {352, 350, 348, 648, 350}}, { 'O', {348, 348, 352, 652, 348}}, { 'O', {350, 352, 350, 650, 352}},
  { 'P', {350, 351, 349, 649, 651}}, { 'P', {348, 349, 351, 651, 649}}, { 'P', {352, 350, 350, 650, 650}},
  { 'R', {351, 649, 651, 350, 350}}, { 'R', {349, 651, 649, 348, 348}}, { 'R', {350, 650, 650, 352, 352}},
  { 'S', {648, 352, 350, 648, 350}}, { 'S', {652, 348, 348, 652, 348}}, { 'S', {650, 350, 352, 650, 352}},
  { 'T', {651, 649, 351, 349, 350}}, { 'T', {649, 651, 349, 351, 348}}, { 'T', {650, 650, 350, 350, 352}},
  { 'U', {350, 350, 350, 348, 648}}, { 'U', {348, 348, 352, 352, 652}}, { 'U', {352, 352, 348, 350, 650}},
  { 'V', {649, 351, 649, 651, 350}}, { 'V', {651, 349, 651, 649, 348}}, { 'V', {650, 350, 650, 650, 352}},
  { 'W', {648, 652, 650, 352, 350}}, { 'W', {652, 648, 648, 348, 348}}, { 'W', {650, 650, 652, 350, 352}},
  { 'Y', {349, 651, 649, 651, 350}}, { 'Y', {351, 649, 651, 649, 348}}, { 'Y', {350, 650, 650, 650, 352}},

  // --- COMMANDS AND CUSTOM WORDS SAMPLES (3 per command) ---
  { ' ', {348, 352, 350, 349, 351}}, { ' ', {352, 348, 351, 350, 349}}, { ' ', {350, 350, 348, 352, 350}},
  { '<', {648, 652, 650, 649, 651}}, { '<', {652, 648, 651, 650, 649}}, { '<', {650, 650, 648, 652, 650}},
  { '1', {649, 651, 650, 648, 352}}, { '1', {651, 649, 648, 652, 348}}, { '1', {650, 650, 652, 650, 350}}, // HELLO
  { '2', {352, 648, 652, 650, 649}}, { '2', {348, 652, 648, 648, 651}}, { '2', {350, 650, 650, 652, 650}}, // THANK YOU
  { '3', {648, 352, 648, 352, 648}}, { '3', {652, 348, 652, 348, 652}}, { '3', {650, 350, 650, 350, 650}}, // NAMASTE
  { '4', {652, 648, 352, 648, 352}}, { '4', {648, 652, 348, 652, 348}}, { '4', {650, 650, 350, 650, 350}}, // PRAGNA
  { '5', {352, 648, 652, 351, 649}}, { '5', {348, 652, 648, 349, 651}}, { '5', {350, 650, 650, 350, 650}}, // DORA
  { '6', {649, 351, 649, 651, 350}}, { '6', {651, 349, 651, 649, 348}}, { '6', {650, 350, 650, 650, 352}}, // MAM
  { '7', {650, 651, 349, 651, 649}}, { '7', {648, 649, 351, 649, 651}}, { '7', {652, 650, 350, 650, 650}}, // AMRITA
  { '8', {351, 649, 351, 649, 651}}, { '8', {349, 651, 349, 651, 649}}, { '8', {350, 650, 350, 650, 650}}, // HELP
};

const int NUM_GESTURES = sizeof(trainingData) / sizeof(GestureData);

String dictionaryWords[] = {
  "HELLO", "THANK YOU", "NAMASTE", "PRAGNA", "DORA", "MAM", "AMRITA", "HELP"
};
const int NUM_DICTIONARY_WORDS = sizeof(dictionaryWords) / sizeof(String);


SoftwareSerial mySoftwareSerial(DFPLAYER_RX_PIN, DFPLAYER_TX_PIN);
DFRobotDFPlayerMini myDFPlayer;

String currentWord = "";
char lastPredictedChar = 0;
char currentPredictedChar = 0;
unsigned long lastGestureTime = 0;
const int GESTURE_HOLD_TIME = 500;


void setup() {
  Serial.begin(9600);
  mySoftwareSerial.begin(9600);
  Serial.println(F(""));

  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println(F("DFPlayer Mini not found."));
    while (true);
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.volume(24);
}

void loop() {
  int currentSensorReadings[5];
  for (int i = 0; i < 5; i++) {
    currentSensorReadings[i] = analogRead(SENSOR_PINS[i]);
  }

  char predictedChar = classify(currentSensorReadings);

  if (predictedChar != lastPredictedChar) {
    lastPredictedChar = predictedChar;
    lastGestureTime = millis();
  }

  if (millis() - lastGestureTime > GESTURE_HOLD_TIME && predictedChar != currentPredictedChar) {
    currentPredictedChar = predictedChar;
    processCharacter(currentPredictedChar);
  }
}

void processCharacter(char ch) {
  if (ch == '<') {
    if (currentWord.length() > 0) {
      currentWord.remove(currentWord.length() - 1);
      Serial.print("Word: ");
      Serial.println(currentWord);
    }
    return;
  }

  if (ch == ' ') {
    if (currentWord.length() > 0) {
      Serial.print("Final Word: ");
      Serial.println(currentWord);
      playWord(currentWord);
      currentWord = "";
    }
    return;
  }

  if (ch >= '1' && ch <= '8') {
    int wordIndex = ch - '1';
    if (wordIndex < NUM_DICTIONARY_WORDS) {
      String wordToPlay = dictionaryWords[wordIndex];
      Serial.print("Direct Command Word: ");
      Serial.println(wordToPlay);
      playWord(wordToPlay);
    }
    return;
  }

  currentWord += ch;
  Serial.print("Word: ");
  Serial.println(currentWord);
}

void playWord(String word) {
  for (int i = 0; i < NUM_DICTIONARY_WORDS; i++) {
    if (word.equalsIgnoreCase(dictionaryWords[i])) {
      int fileNumber = 22 + i + 1;
      Serial.print("Playing dictionary word '");
      Serial.print(word);
      Serial.print("' (File ");
      Serial.print(fileNumber);
      Serial.println(")");
      myDFPlayer.play(fileNumber);
      return;
    }
  }

  Serial.print("Spelling word: ");
  Serial.println(word);
  for (int i = 0; i < word.length(); i++) {
    char letter = word.charAt(i);
    int fileNumber = letter - 'A' + 1;
    myDFPlayer.play(fileNumber);
    delay(500);
  }
}

// K-NEAREST NEIGHBORS (k-NN) IMPLEMENTATION
char classify(int readings[5]) {
  long distances[NUM_GESTURES];
  
  for (int i = 0; i < NUM_GESTURES; i++) {
    distances[i] = calculateDistance(readings, trainingData[i].sensorValues);
  }

  char neighbors[K];
  for (int i = 0; i < K; i++) {
    long minDistance = -1;
    int minIndex = -1;
    for (int j = 0; j < NUM_GESTURES; j++) {
      if ((distances[j] < minDistance || minDistance == -1) && distances[j] != -1) {
        minDistance = distances[j];
        minIndex = j;
      }
    }
    neighbors[i] = trainingData[minIndex].label;
    distances[minIndex] = -1;
  }

  return majorityVote(neighbors);
}

long calculateDistance(int p1[5], int p2[5]) {
  long sum = 0;
  for (int i = 0; i < 5; i++) {
    long diff = p1[i] - p2[i];
    sum += diff * diff;
  }
  return sum;
}

char majorityVote(char neighbors[K]) {
  int counts[K] = {0};
  
  for (int i = 0; i < K; i++) {
    for (int j = 0; j < K; j++) {
      if (neighbors[j] == neighbors[i]) {
        counts[i]++;
      }
    }
  }

  int maxCount = 0;
  char mostFrequentChar = 0;
  for (int i = 0; i < K; i++) {
    if (counts[i] > maxCount) {
      maxCount = counts[i];
      mostFrequentChar = neighbors[i];
    }
  }
  return mostFrequentChar;
}
