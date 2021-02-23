# Audio Recorder/Player

# INTRO
In this project, we have aimed to create a digital voice recorder which can record voice that will be taken from microphone.
We have used various types of modules such as Timers, PWM, ADC, External Interrupts and I2C.
We have used two EEPROMs that have 64K bytes size in order to store our voice samples.
A keypad used to get input from user in order to be selected operation that user wants.
A speaker circuit built to play audio from EEPROMs by using PWM.
ADC sampling frequency has been arranged by calculating each track that will be stored in EEPROMs size.
Playing sound by using PWM has been done in two times of sampling frequency in order to obtain proper audio from speaker.
EEPROMs used same I2C bus but we have communicated them with different device addresses.
Lastly, in our speaker circuit, we have used a band pass and high pass filter to get less noisy audio from EEPROMs.

# FEATURES
- Audio Recording
- Audio Pausing/Playing
- Audio Deleting
- Track Selection
 
# DOCS

## Project Setup
![project setup](https://github.com/aykutshahin/AudioRecorderPlayer/blob/main/docs/project_setup.jpg)

## Block Diagram
![block diagram](https://github.com/aykutshahin/AudioRecorderPlayer/blob/main/docs/block_diagram.jpg)

## State Machine Diagram
![state machine](https://github.com/aykutshahin/AudioRecorderPlayer/blob/main/docs/state_machine_diagram.jpg)