**PROCEDURAL PROGRAMMING USING C**

**23CSE201**

**PROJECT REPORT**

**CUSTOM-GESTURE-BASED SIGN LANGUAGE TRANSLATOR GLOVE**

**USING ARDUINO**

**TEAM MEMBERS**

  -----------------------------------------------------------------------
  ARUN PRAVIN A P                     CB.SC.U4CSE24710
  ----------------------------------- -----------------------------------
  B H HARSHITH VARMA                  CB.SC.U4CSE24711

  MONISH U                            CB.SC.U4CSE24733

  TEJAS SRIVASTAVA                    CB.SC.U4CSE24754
  -----------------------------------------------------------------------

**[PROBLEM STATEMENT]{.underline}**

It can be very difficult for people who use sign language to talk with
people who don\'t. This communication gap can make everyday life
challenging, whether at school, at work, or just during simple
conversations.

While solutions like hiring a professional interpreter exist, they are
expensive and not always available. Phone apps that use a camera to
recognize signs can also be tricky to use, they might not work in bad
lighting, and they make you focus on a screen instead of the person in
front of you.

Our project aims to fix this with a different idea: a simple, low-cost
glove that translates hand signs into spoken words. We designed a unique
set of signs that are very easy for the glove\'s sensors to read
accurately. By using *machine learning* that trains specifically on the
user\'s hand, our goal is to create a reliable, personal translator that
is easy to carry and natural to use in any conversation.

![](media/image1.png){width="4.775358705161855in"
height="3.8055555555555554in"}

**[HARDWARE & SOFTWARE REQUIREMENTS]{.underline}**

  -------------------------------------------------------------------------
  Hardware          Quantity   Purpose
  Component                    
  ----------------- ---------- --------------------------------------------
  Arduino Uno R3    1          The central microcontroller that runs the
  (or clone)                   main program logic, including the machine
                               learning model.

  4.5-inch Flex     5          Measures the degree of bend for each finger,
  Sensor                       providing the data for recognizing gestures.

  10kΩ Resistor     5          Used with each flex sensor.

  DFPlayer Mini MP3 1          To convert the translated audio as an
  Module                       electrical signal

  MicroSD Card      1          Stores the audio files for each letter and
                               pre-programmed word.

  Speaker (1W, 8Ω)  1          The output device that converts the
                               electrical audio signal from the DFPlayer
                               into audible sound.

  Fabric Glove      1          The base of the circuit

  Breadboard &      1 set      For creating the prototype circuit and
  Wires                        connecting all components.
  -------------------------------------------------------------------------

  ------------------------------------------------------------------------
  Software/Library        Purpose
  ----------------------- ------------------------------------------------
  Arduino IDE             The primary environment for writing, compiling,
                          and uploading the C code to the Arduino board.

  DFRobotDFPlayerMini.h   An Arduino library to simplify communication and
                          control of the DFPlayer Mini module.

  SoftwareSerial.h        A standard Arduino library used to create an
                          additional serial communication port for the
                          DFPlayer.
  ------------------------------------------------------------------------

**[ARCHITECTURE]{.underline}**

The system\'s architecture is such that it converts physical hand
movements into spoken words through three distinct layers.

1.  **Input Layer (Data Acquisition):** This layer is the physical
    interface with the user. The five flex sensors mounted on the glove
    are the primary data sources. Each sensor\'s resistance changes as
    our finger bends. This change is captured by the Arduino\'s
    analog-to-digital converter (ADC) as a numerical value (typically
    between 0 and 1023), creating a five-dimensional data point that
    represents the state of the hand at any given moment.

2.  ![](media/image2.png){width="6.25in"
    height="3.1333333333333333in"}**Processing Layer (Logic &
    Intelligence):** This is the \"brain\" of the project, hosted on the
    Arduino Uno. It executes the main program loop, which includes the
    *k-Nearest Neighbors (k-NN)* machine learning classifier. The k-NN
    model compares the live sensor data to a pre-trained library of
    gestures to find the best match. This layer also contains the
    \"word-building\" logic that assembles recognized letters into a
    string and the \"smart dictionary\" that determines whether to play
    a full word or spell it out.

3.  **Output Layer (Audio Feedback):** Once the processing layer makes a
    decision, it sends a command to the DFPlayer Mini module. This
    dedicated audio-processing chip retrieves the specified .mp3 file
    from the microSD card, decodes it, amplifies the signal, and sends
    it to the speaker to produce clear, audible speech.

**Custom Sign Language Design:**

To maximize reliability with the flex sensor hardware, a custom sign
language was developed. Each sign is a unique combination of \"Bent\" or
\"Straight\" fingers.Since we have 5 fingers and two possible positions
per finger(B/S), total no of combinations are 2\^5 = 32.

(T,I,M,R,P = Thumb,Index,Middle,Ring,Pointing fingers)

(B=bent , S=straight)

-   **The Final Custom Alphabet (22 Letters)**

  -----------------------------------------------------------------------
  Char    Description                        Finger State (T,I,M,R,P)
  ------- ---------------------------------- ----------------------------
  A       Only Thumb bent                    (B, S, S, S, S)

  B       Index, Middle, Pinky bent          (S, B, B, S, B)

  C       Middle and Ring bent               (S, S, B, B, S)

  D       Index and Ring bent                (S, B, S, B, S)

  E       Only Index finger bent             (S, B, S, S, S)

  F       Three outer fingers bent           (S, S, B, B, B)

  G       Three middle fingers bent          (S, B, B, B, S)

  H       Thumb and Pinky bent               (B, S, S, S, B)

  I       Only Middle finger bent            (S, S, B, S, S)

  K       Thumb, Ring, and Pinky bent        (B, S, S, B, B)

  L       Index and Pinky bent               (S, B, S, S, B)

  M       Middle and Pinky bent              (S, S, B, S, B)

  N       Thumb and Middle bent              (B, S, B, S, S)

  O       Only Ring finger bent              (S, S, S, B, S)

  P       Ring and Pinky bent                (S, S, S, B, B)

  R       Index and Middle bent              (S, B, B, S, S)

  S       Thumb and Ring bent                (B, S, S, B, S)

  T       Thumb and Index bent               (B, B, S, S, S)

  U       Only Pinky finger bent             (S, S, S, S, B)

  V       Thumb, Middle, and Ring bent       (B, S, B, B, S)

  W       Thumb, Index, and Middle bent      (B, B, B, S, S)

  Y       Thumb and Pinky straight           (S, B, B, B, S)
  -----------------------------------------------------------------------

-   **Commands and Custom Words (10 Slots)**

  ------------------------------------------------------------------------
  Word/Command     Description                      Finger State
                                                    (T,I,M,R,P)
  ---------------- -------------------------------- ----------------------
  SPACE            All fingers straight (flat hand) (S, S, S, S, S)

  DELETE           All fingers bent (fist)          (B, B, B, B, B)

  HELLO            Fist with thumb sticking out     (B, B, B, B, S)

  THANK YOU        Pointing hand                    (S, B, B, B, B)

  VANAKKAM         Thumb, Middle, Pinky bent        (B, S, B, S, B)

  WE               Thumb, Index, Ring bent          (B, B, S, B, S)

  ARE              Index, Middle, Pinky bent        (S, B, B, S, B)

  THE              Thumb, Middle, Ring bent         (B, S, B, B, S)

  AMRITA           Middle finger straight, others   (B, B, S, B, B)
                   bent                             

  HELP             Thumb & Middle straight, others  (S, B, S, B, B)
                   bent                             
  ------------------------------------------------------------------------

**[PROGRAM FLOW]{.underline}**

The program\'s logic operates in a continuous loop, translating a
user\'s gestures into words.

-   First, the Arduino reads the values from the five flex sensors.
    These readings are stored in an array and sent to the k-NN
    classifier. The classifier then compares the new readings with all
    the data it already has, calculating how close each one is. It picks
    the k closest matches, takes a majority vote, and predicts the sign
    being made, returning it as a single character.

-   The main loop then checks if this character is new. If yes, it
    processes it. If the character is a standard letter, it is appended
    to the *currentWord* string. If the character is the \'DELETE\'
    command, the last letter of the string is removed.

-   The most important part happens when the program sees the "SPACE"
    command. First, it looks in its word list to check if the word we
    typed is already saved. If it is, it plays the whole word's sound at
    once. If it is not, it goes letter by letter and plays each letter's
    sound. When it finishes, it erases the word and gets ready for the
    next one.

**[FLOW DIAGRAM]{.underline}**

![](media/image3.png){width="6.268055555555556in"
height="6.356944444444444in"}

**C CONCEPTS USED**

-   **Data Structures (struct):** A custom struct was created to
    organize our training data. This allowed us to bundle a character
    label with its corresponding array of five sensor values, creating a
    clean database.

-   **Arrays:** Arrays are the backbone of our project\'s data
    management. They are used for storing sensor pin configurations,
    holding real-time sensor readings, containing the entire k-NN
    training dataset, and defining the list of words for our dictionary.

-   **Functions:** The code is broken down into functions. For example,
    classify() encapsulates the entire machine learning prediction
    process, while calculateDistance() handles a specific tasks in our
    k-nn algorithm.

-   **Control Structures (if, for):** for loops are essential for
    iterating through sensor readings and searching the dataset. Complex
    if-else logic forms the core of the word-building system, directing
    program flow based on whether a recognized character is a letter, a
    command, or a space.

-   **Libraries (#include):** The project demonstrates the use of
    external libraries to interface with hardware modules. Including
    *SoftwareSerial.h* and *DFRobotDFPlayerMini.h* allowed us to easily
    communicate with the MP3 player.

**EXPECTED OUTPUT**

The final output of the project is a fully functional, wearable
communication device. A user wearing the glove can spell any word using
the custom sign language. Upon gesturing the \'SPACE\' command, the
device will respond with clear, audible speech from its speaker. The
output is intelligent: if the user spells \"HELLO,\" the device will
play a single, fluid audio clip of \"hello.\" If the user spells an
un-programmed word like \"JADEJA\" the device will audibly spell it out:
\"J..A..D..E..J..A" . This provides a seamless, flexible, and powerful
user experience.
