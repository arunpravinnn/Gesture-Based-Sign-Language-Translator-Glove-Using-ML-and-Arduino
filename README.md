It can be very difficult for people who use sign language to talk with people who don't. This communication gap can make everyday life challenging, whether at school, at work, or just during simple conversations.
While solutions like hiring a professional interpreter exist, they are expensive and not always available. Phone apps that use a camera to recognize signs can also be tricky to use, they might not work in bad lighting, and they make you focus on a screen instead of the person in front of you.
Our project aims to fix this with a different idea: a simple, low-cost glove that translates hand signs into spoken words. We designed a unique set of signs that are very easy for the glove's sensors to read accurately. By using machine learning that trains specifically on the user's hand, our goal is to create a reliable, personal translator that is easy to carry and natural to use in any conversation.

# Hardware & Software Requirements  

## Hardware Components  

| **Hardware Component** | **Quantity** | **Purpose** |
|------------------------|-------------:|-------------|
| Arduino Uno R3 (or clone) | 1 | The central microcontroller that runs the main program logic, including the machine learning model. |
| 4.5-inch Flex Sensor | 5 | Measures the degree of bend for each finger, providing the data for recognizing gestures. |
| 10kΩ Resistor | 5 | Used with each flex sensor. |
| DFPlayer Mini MP3 Module | 1 | To convert the translated audio as an electrical signal. |
| MicroSD Card | 1 | Stores the audio files for each letter and pre-programmed word. |
| Speaker (1W, 8Ω) | 1 | The output device that converts the electrical audio signal from the DFPlayer into audible sound. |
| Fabric Glove | 1 | The base of the circuit. |
| Breadboard & Wires | 1 set | For creating the prototype circuit and connecting all components. |

---

## Software / Libraries  

| **Software / Library** | **Purpose** |
|------------------------|-------------|
| Arduino IDE | The primary environment for writing, compiling, and uploading the C code to the Arduino board. |
| DFRobotDFPlayerMini.h | An Arduino library to simplify communication and control of the DFPlayer Mini module. |
| SoftwareSerial.h | A standard Arduino library used to create an additional serial communication port for the DFPlayer. |
