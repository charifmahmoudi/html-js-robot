# html-js-robot
Robot Controlled using HTML5/JavaScript and BeagleBone Green

## Motivation

It is cool to be able to use the mobile devices to control the stuffs that we build. However, it may be complicated to install the application of the mobile device of a friend to let him play with the project.

## Objective

I propose here a web based interface that use HTML5 features to get the accelerometer data from all the devices that have one and use this information to remotely control a robot.

## How the Accelerometer Works in Mobile Device

The accelerometer in mobile device use an embedded sensor. The browser get this information and make it available trough the HTML5/JavaScript API.

## WebSockets are Cool

One of the main concerns for the web based IoT control is the protocol used for the communication between the GUI and the robot. HTTP is the traditional protocol used in the web browser. However, it has as very heavy communication model compared to the socket. That is because HTTP is a Layer 7 protocol that handles multiple stuffs like headers. The introduction of WebSockets in HTML5 allows the users to instantiate sockets like they can do on a native language.

## JSON is your friend

Once the connection is established using the websocket you need a representation for the data that you will exchange between the webpage and your device. JSON is a very good choice for this propose. for this project, the representation used is composed from an object containing two attribute "left" and "right" for the wheels. Each attribute is as object composed from the "pin" that represents the 3 pins used to control a DC motor using a H-Bridge in the board, "dir" the direction of the wheel, and the "value" of the speed.

## Links
[Hackster.io project](https://www.hackster.io/charifmahmoudi/robot-controlled-using-html5-javascript-and-beaglebone-green-dc779f)
