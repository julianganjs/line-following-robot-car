# Line Following Robot Car
This repository contains the source code for an advanced robot car equipped with line following, distance measurement, obstacle avoidance, Bluetooth control and two special features. The robot operates on an Arduino Uno microcontroller and is programmed using C++ language in Arduino IDE.
## Prerequisites
- Arduino IDE
> The software is required to upload the code to the Arduino UNO board.
## Features
- ### Line Following
  The line following functionality utilizes a sensor array made up of two infrared light detecting sensors. One of the sensors is self-made IR Sensor Module. The circuit schematic is as follows.
  <br><br><img src="https://github.com/julianganjs/line-following-robot-car/assets/127673790/9b11aa12-8c0a-420b-838f-621eb3569b2c" width="300vw"><br>
  The needed components are soldered onto a veroboard until the sensor is fully constructed.
  <br><br><img src="https://github.com/julianganjs/line-following-robot-car/assets/127673790/97e7a216-7181-49b0-9c4f-099ea2a875e2" width="230vw"><br>
  The DIY and ready-made sensors are then attached to the front of the robot car.
  <br><br><img src="https://github.com/julianganjs/line-following-robot-car/assets/127673790/9bf2f4a3-3cc1-4bda-8ebe-5c34e6694523" width="250vw"><br>
  When the black line is detected, no IR light will be received by the photodiode and a “LOW” digital signal from the DIY IR Sensor and a “HIGH” signal from the ready-made IR Sensor will be sent to the Arduino.   These signals will allow the microcontroller to determine the next direction of the car.
- ### Distance Measurement
  This feature uses an encoder sensor to determine the distance travelled by the robot car. The number of rotations of the wheel is multiplied by the circumference of the wheel to find out the total distance.
- ### Obstacle Avoidance
  An Ultrasonic Ranging Module is placed at the front of the robot car and is used to detect obstacles in front of the car. It will then send a signal to the Arduino UNO module to determine the adaptive measures to avoid the obstacle.
  <br><br><img src="https://github.com/julianganjs/line-following-robot-car/assets/127673790/dff6b199-4554-45f1-be25-118ba71215f0" width="250vw"><br>
- ### Bluetooth Control
  To allow the robot car to be controlled via Bluetooth on a smartphone app, a Bluetooth Serial Transceiver module is connected to the Arduino Uno microcontroller on the robot car. Each direction has a button and is assigned to a serial character, and when that character is read by the code, the robot car would then move in the following direction.
- ### In the Box Game (Special Feature 1)
  The In the Box Game utilizes the Ultrasonic Ranging Module to establish an up to 4 player game. This game uses the same principles in terms of obstacle detection. The goal of the game is to keep the robot car within a box while it is constantly being deflected. Each deflection turns the robot car to a random direction, with each player taking turns to keep it in the box. However, the car can only be reflected if a bat is detected within 4-10cm from the Ultrasonic sensor. Any less and the current player loses. 
- ### Dog Mode (Special Feature 2)
  This feature enables the robot car to behave like a dog. For example: follow the owner, wag its tail, turn around when someone taps its tail and perform tricks when voice commands are given. Complicated coding has been implemented to allow the “dog” to be as lifelike as possible.
  <br><br>When a person is detected within 30cm in front of the Ultrasonic sensor, the robot car will approach the person slowly till a distance of 15cm between it and the person. When a hand is detected within 2cm of the Ultrasonic sensor, this signals that the person wants to pat the “dog”, thus it will allow the person to do so and wag its tail.
  <br><br>A ready-made IR sensor is attached to the back of the robot car and represents a “tail”. When an person’s hand reflects the infrared light while tapping the tail, the “dog” will turn around and “look” for the person.
  <br><br><img src="https://github.com/julianganjs/line-following-robot-car/assets/127673790/12cc8be8-8c27-4366-a403-afe85f06a9a3" width="230vw"><br>
  For voice commands, it follows the same principles as the bluetooth control function, except each voice command is assigned to a serial character on the smartphone app instead of a button. The Arduino UNO then determines the next action based on the given code.
## Code Structure
- LineFollowingCode.ino: This code allows the robot car to detect and follow track lines.
- EncoderSensorCode.ino: This code allows the robot car to measure and calculate the total distance it has travelled.
- ObstacleAvoidingCode.ino: This code allows the robot car to avoid obstacles in its path.
- BluetoothControlCode.ino: This code allows the robot car to be controlled via Bluetooth on a smartphone app.
- SpecialFeature1.ino: This code enables the In the Box game on the robot car.
- SpecialFeature2.ino: This code enables dog mode on the robot car.
## License
This project is licensed under the MIT License.
