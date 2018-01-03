#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

#define I2C_ADDR   0x27


#define LCD_CHR  1 // Mode - Sending data
#define LCD_CMD  0 // Mode - Sending command

#define LINE1  0x80 // 1st line
#define LINE2  0xC0 // 2nd line

#define LCD_BACKLIGHT   0x08  // On
// LCD_BACKLIGHT = 0x00  # Off

#define ENABLE  0b00000100 // Enable bit

void lcd_init(void);
void lcd_byte(int bits, int mode);
void lcd_toggle_enable(int bits);

// added by Lewis
void typeInt(int i);
void typeFloat(float myFloat);
void lcdLoc(int line); //move cursor
void ClrLcd(void); // clr LCD return home
void typeln(char &alignment, int pause, string message);
void typeln(char &alignment, const char *s);
void typeChar(char val);
int fd;  // seen by all subroutines

int currentln{0};
char r = 'r';
char l = 'l';
char m = 'm';

int main()   {

    if (wiringPiSetup () == -1) exit (1);

    fd = wiringPiI2CSetup(I2C_ADDR);

    char r = 'r';
    char l = 'l';
    char m = 'm';
    

    lcd_init(); // setup LCD

    while (1)   {

        ClrLcd();

        string small = "small";
        string myname = "insert random quote here";
        lcdLoc(LINE1);
        typeln(m, 100, myname);


        delay(1000);
        ClrLcd();
        string what = "Test";
        typeln(r, 200, what);
        delay(1000);
    }

    return 0;

}


/* float to string
void typeFloat(float myFloat)   {
    char buffer[20];
    sprintf(buffer, "%4.2f",  myFloat);
    typeln(buffer);
}

// int to string
void typeInt(int i)   {
    char array1[20];
    sprintf(array1, "%d",  i);
    typeln(array1);
}*/

// clr lcd go home loc 0x80
void ClrLcd(void)   {
    lcd_byte(0x01, LCD_CMD);
    lcd_byte(0x02, LCD_CMD);
}

// go to location on LCD
void lcdLoc(int line)   {
    lcd_byte(line, LCD_CMD);
    (line == 0x80) ? currentln = 1 : currentln = 2;
}


void typeChar(char val)   {

    lcd_byte(val, LCD_CHR);
}



void typeln(const char &alignment, const char *s){

    while ( *s ) lcd_byte(*(s++), LCD_CHR);

}

void typeln(char &alignment, int pause, string message){
    string m = message;

    if(message.length() > 15){
        alignment = 'l';
        for(int i{0}; i < 16; ++i){
                lcd_byte(m.at(i), LCD_CHR);
                delay(pause);
        }

        m = "";
        for(int i{16}; i < message.length(); ++i){
            m += message.at(i);
        }        

        

        if(currentln == 1){
            lcdLoc(LINE2);
        } 

        else{
            lcdLoc(LINE1);
            ClrLcd();
           
        }
        typeln(l, pause, m);
            
    }       

    else{
        if(alignment == 'l'){ 
            for(int i{0}; i < message.length(); ++i){
                lcd_byte(message.at(i), LCD_CHR);
                delay(pause);
            }
        
        }
            
        if(alignment == 'm'){

            string temp;
            int getspaces{0};
        
            getspaces = (16 - message.length()) / 2;

            for(int i{0}; i <= getspaces; ++i){
                temp += " ";
            } 

            temp += message;
            for(int i{0}; i < temp.length(); ++i){
                lcd_byte(temp.at(i), LCD_CHR);
               if( i > getspaces ) delay(pause);
            }

                
        }

        if(alignment == 'r'){

            string temp;
            int getspaces{0};

            getspaces = (16 - message.length());

            for(int i{0}; i < getspaces; ++i){
                temp += " "; 
            }

            temp += message;
            for(int i{0}; i < temp.length(); ++i){
                lcd_byte(temp.at(i), LCD_CHR);
                if( i > getspaces )delay(pause);
            }   
            

        }

    }
    
}

void lcd_byte(int bits, int mode)   {

    //Send byte to data pins
    // bits = the data
    // mode = 1 for data, 0 for command
    int bits_high;
    int bits_low;
    // uses the two half byte writes to LCD
    bits_high = mode | (bits & 0xF0) | LCD_BACKLIGHT ;
    bits_low = mode | ((bits << 4) & 0xF0) | LCD_BACKLIGHT ;

    // High bits
    wiringPiI2CReadReg8(fd, bits_high);
    lcd_toggle_enable(bits_high);

    // Low bits
    wiringPiI2CReadReg8(fd, bits_low);
    lcd_toggle_enable(bits_low);
}

void lcd_toggle_enable(int bits)   {
    // Toggle enable pin on LCD display
    delayMicroseconds(500);
    wiringPiI2CReadReg8(fd, (bits | ENABLE));
    delayMicroseconds(500);
    wiringPiI2CReadReg8(fd, (bits & ~ENABLE));
    delayMicroseconds(500);
}


void lcd_init()   {
    // Initialise display
    lcd_byte(0x33, LCD_CMD); // Initialise
    lcd_byte(0x32, LCD_CMD); // Initialise
    lcd_byte(0x06, LCD_CMD); // Cursor move direction
    lcd_byte(0x0C, LCD_CMD); // 0x0F On, Blink Off
    lcd_byte(0x28, LCD_CMD); // Data length, number of lines, font size
    lcd_byte(0x01, LCD_CMD); // Clear display
    delayMicroseconds(500);
}
