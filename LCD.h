#ifndef LCD_H
#define LCD_H

#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class LCD {
    int I2C_ADDR;

    int LCD_CHR;
    int LCD_CMD;

    int Line1;
    int Line2;
    int currentln;

    int LCD_Backlight = 0x08;

    int ENABLE = 0b00000100;

    void set_variables();
    void lcd_init();
    void lcd_byte(int bits, int mode);
    void lcd_toggle_enable(int bits);

    int fd;

    public:
        LCD();
        void clear(int pause);
        //Note: this changes currentln value
        void lcdLoc(int line);
        void printNum(int pause, int number);
        void printNum(int pause, float number);
        void print(char alignment, int pause, string message);
        void print(char alignment, const char *s);
        void printChar(char val);
};

#endif