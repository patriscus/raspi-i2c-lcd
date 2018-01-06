# I2C 16x2 LCD "Library" for the Raspberry Pi

I searched for an I2C LCD library for the Raspberry Pi that was not written in Python, but in C++ instead. What I found was [Lewis Loflin's](http://www.bristolwatch.com/rpi/i2clcd.htm) code which was written in C. I adopted this code and edit it since then. 
**Note** - I just started programming few months ago and the code is only being tested on one device. I do not take responsibility for any damage resulted from executing this code.

## Getting Started

You only need to download the files and include the LCD.h file into your main cpp file.

### Prerequisites

You need a library called [WiringPi](http://wiringpi.com/) in order to use the code. For the installation process please refer to [this](http://wiringpi.com/download-and-install/) page.


## Authors

* **Patrick Ahmetovic** - *rewriting the code*

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.


## Acknowledgments

I would like to thank these people for sharing their code.

* Gordon Henderson - [WiringPi](http://wiringpi.com/)
* Lewis Lofin - [link](http://www.bristolwatch.com/rpi/i2clcd.htm)

