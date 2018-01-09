# Rapi-I2C-LCD 

A C++ class for interfacing with an I2C LCD Display connected to the Raspberry Pi. 
> Note:
> The code is only being tested on one device for an 16x2 LCD Display. I also used Lewis Loflin's [code](http://www.bristolwatch.com/rpi/i2clcd.htm)

## Getting Started


### Prerequisites

You need a library called [WiringPi](http://wiringpi.com/) in order to use the code. For the installation process please refer to [this](http://wiringpi.com/download-and-install/) page.

### Usage

To initialize a new LCD named lcd:

```c++
LCD lcd;
```

To clear the display:

```cpp
// This method takes in the amount of milliseconds to pause before clearing
lcd.clear(pause);
```

To write on Line 1:

```cpp
lcd.lcdLoc(1);  //1 for Line 1, 2 for Line 2
```

To show a message on the Display:

```cpp
// You can pass a string or write directly
// l = left, m = middle, r = right alignment
// Pause defines the time before next character is being displayed
lcd.print(alignment, pause, message);
lcd.print(alignment, pause, "Hello World");
```

##### Social

You can find me at [Twitter](http://www.bristolwatch.com/rpi/i2clcd.htm).


## Acknowledgments

I would like to thank these people for sharing their code.

* Gordon Henderson - [WiringPi](http://wiringpi.com/)
* Lewis Lofin - [C code](http://www.bristolwatch.com/rpi/i2clcd.htm)

