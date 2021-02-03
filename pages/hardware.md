---
layout: page
title: Hardware
permalink: /hardware/
---


## Actuation Modules

|**Module Name**|**Description**|**Downloads**|
|:-----:|:-----|:-----:|
| **Stretch Module** <br> <img src="../photos/stretch_assembly.jpg" alt="stretch_module" style="width:300px;"> | The stretch module delivers a tangential skin stretch using a servo motor actuating tangentially to the skin.The stretch module is composed of four parts: the clip, the tactor, the actuator, and the base. The twist and stretch modules feature SG90 micro servo motors commonly used in hobbyist applications as the main actuators. <br> *Dimensions*: <br>- Base(outer): 32.1mm x 25mm x 9mm <br>- Motor tab slot: 11.5mm x 3mm <br>- Motor body slot: 12.5mm x 26.5mm <br> - Clip: 18.4mm x 30.2mm x 8mm. | [3D Model Download](https://www.thingiverse.com/thing:4746724) <br><br> [Solidworks CAD Download](https://rice.box.com/v/snaptics-stretch-module)
| **Twist Module** <br> <img src="../photos/twist_assembly.jpg" alt="twist_module" style="width:300px;"> | The twist module delivers a tangential skin twist using a servo motor actuating normal to the surface of the skin. The twist module is composed of four parts: the clip, the tactor, the actuator, and the base. The twist and stretch modules feature SG90 micro servo motors commonly used in hobbyist applications as the main actuators. <br> *Dimensions*: <br>- Base(outer): 32.1mm x 25mm x 8.3mm <br>- Shaft-side slot: 15.5mm x 12.5mm <br>- Motor body slot: 22.9mm x 12.5mm | [3D Model Download](https://www.thingiverse.com/thing:4746750) <br><br> [Solidworks CAD Download](https://rice.box.com/v/snaptics-twist-module) 
| **ERM Vibration Module** <br> <img src="../photos/erm_vibration_assembly.jpg" alt="erm_vibration_module" style="width:300px;">| The ERM vibration module with its base components. The cylindrical eccentric rotating mass motor is secured to the 3d printed module frame with a light press fit. The vibration of the ERM motor is transmitted to the skin via the contact surface of the module frame. The ERM vibration module is composed of three parts: the actuator, the base, and the clip. <br> *Dimensions*: <br>- Base(outer): 32.1mm x 25mm x 6mm <br>- Slot-diameter: 6.3mm | [3D Model Download](https://www.thingiverse.com/thing:4746743) <br><br> [Solidworks CAD Download](https://rice.box.com/v/snaptics-erm-vibration-module)


## Electronics Modules

|**Module Name**|**Description**|**Downloads**|
|:-----:|:-----|:-----:|
| **Control Module** <br> <img src="../photos/control_assembly.jpg" alt="control_module" style="width:300px;"> | The control module houses the main control circuitry. The current version of the board features a frame, a custom-made printed circuit board, and a Sparkfun ESP32 Development Board. The frame uses a x-lattice structure to stabilize the base of the unit while minimizing material costs. <br> *Dimensions*: <br>- Base(outer): 78mm x 56.5mm x 5mm <br>- Frame(inner): 76mm x 40mm <br><br> Rather than having the ESP32 control board interface directly with  the  actuators, it connects to female header pins on the PCB. This PCB features a plug for an external power supply, male header pins to connect actuators to, a 5V regulator, and low-side MOSFET control for the ERM motors. The board has eight servo and ERM ports and measures 75mm x 39mm. | [3D Model Download](https://www.thingiverse.com/thing:4747935) <br><br> [Solidworks CAD Download](https://rice.box.com/v/snaptics-control-module)
| **Power Module** <br> <img src="../photos/power_assembly.jpg" alt="power_module" style="width:300px;"> | The power module features a frame that provides support for the two power sources used in this device, one battery pack for motor support and a smaller lithium ion battery pack for electronics support. <br> *Dimensions*: <br>- Base: 75mm x 69.5mm x 5mm | [3D Model Download](https://www.thingiverse.com/thing:4747915) <br><br> [Solidworks CAD Download](https://rice.box.com/v/snaptics-power-module)


## Support Modules

|**Module Name**|**Description**|**Downloads**|
|:-----:|:-----|:-----:|
| **Blank Module** <br> <img src="../photos/blank_base.jpg" alt="blank_module" style="width:300px;"/> | The blank module is a simple rectangular frame of out dimensions with a x-lattice support in the frame to provide stability. The blank module includes the same chain lock and key mechanisms on either side to interface with any other module in order to give the designer freedom to space out modules on their desired device by adding or removing blank modules between actuation modules. <br> *Dimensions*: <br>- Base(outer): 32.1mm x 25mm x 6mm | [3D Model Download](https://www.thingiverse.com/thing:4747947) <br><br> [Solidworks CAD Download](https://rice.box.com/v/snaptics-blank-module)
| **Terminal Modules** <br> <img src="../photos/terminal_bases.png" alt="terminal_modules" style="width:300px;"/> | The strap module is a converter piece between the chain style lock and key connections of the other modules to an interface that can be coupled with a simple strap or with 25mm webbing. The strap modules are adjustable and allow webbing or strapping to be tightened or loosened after attachment. <br> *Dimensions*: <br>- Base(male): 32.1mm x 16mm x 6mm <br>- Base(female): 32.1mm x 24.5mm x 6mm | [3D Model Download](https://www.thingiverse.com/thing:4747959) <br><br> [Solidworks CAD Download](https://rice.box.com/v/snaptics-terminal-module)