#include "LCD.h"

using namespace std;

LCD::LCD() {

    if (wiringPiSetup () == -1) 
        throw runtime_error("WiringPiSetup failed.");

    this->set_variables();

    this->lcd_init();
} 

void LCD::set_variables(){
    I2C_ADDR = 0x27;
    LCD_CHR = 1;
    LCD_CMD = 0;
    Line1 = 0x80;
    Line2 = 0xC0;
    currentln = 1;
    LCD_Backlight = 0x08;
    ENABLE = 0b00000100;

    fd = wiringPiI2CSetup(I2C_ADDR);
}

void LCD::lcd_init(){
    lcd_byte(0x33, LCD_CMD); // Initialise
    lcd_byte(0x32, LCD_CMD); // Initialise
    lcd_byte(0x06, LCD_CMD); // Cursor move direction
    lcd_byte(0x0C, LCD_CMD); // 0x0F On, Blink Off
    lcd_byte(0x28, LCD_CMD); // Data length, number of lines, font size
    lcd_byte(0x01, LCD_CMD); // Clear display
    delayMicroseconds(500);
}

void LCD::lcd_byte(int bits, int mode)   {

    //Send byte to data pins
    // bits = the data
    // mode = 1 for data, 0 for command
    int bits_high;
    int bits_low;
    // uses the two half byte writes to LCD
    bits_high = mode | (bits & 0xF0) | LCD_Backlight ;
    bits_low = mode | ((bits << 4) & 0xF0) | LCD_Backlight ;

    // High bits
    wiringPiI2CReadReg8(fd, bits_high);
    lcd_toggle_enable(bits_high);

    // Low bits
    wiringPiI2CReadReg8(fd, bits_low);
    lcd_toggle_enable(bits_low);
}

void LCD::lcd_toggle_enable(int bits)   {
    // Toggle enable pin on LCD display
    delayMicroseconds(500);
    wiringPiI2CReadReg8(fd, (bits | ENABLE));
    delayMicroseconds(500);
    wiringPiI2CReadReg8(fd, (bits & ~ENABLE));
    delayMicroseconds(500);
}

void LCD::lcdLoc(int line){
    if(line == 1){
        lcd_byte(Line1, LCD_CMD);
        currentln = 1;
    } else {
        lcd_byte(Line2, LCD_CMD);
        currentln = 2;
    }
}

void LCD::clear(int pause){

    if(pause > 0)
        delay(pause);

    lcd_byte(0x01, LCD_CMD);
    lcd_byte(0x02, LCD_CMD);
}

void LCD::printNum(int pause, int number){
    string temp = to_string(number);

    for(char c: temp){
        lcd_byte(c, LCD_CHR);
        if(pause > 0)
            delay(pause);
    }
}

void LCD::printNum(int pause, float number){
    string temp = to_string(number);

    for(char c: temp){
        lcd_byte(c, LCD_CHR);
        if(pause > 0)
            delay(pause);
    }
}

void LCD::print(char alignment, int pause, string message){
    
    //Word-wrap
    if(message.length() > 15){
        string temp_m = message;

        for(int i{0}; i < 16; ++i){
                lcd_byte(temp_m.at(i), LCD_CHR);
                delay(pause);
        }

        temp_m = "";

        for(int i{16}; i < message.length(); ++i) 
            temp_m += message.at(i);
          

        if(currentln == 1)
            lcdLoc(2);

        else {
            lcdLoc(1);
            clear(0);
        }               

        print(alignment, pause, temp_m);
    }

    else{
        if(alignment == 'l'){ 
            for(int i{0}; i < message.length(); ++i){
                lcd_byte(message.at(i), LCD_CHR);
                delay(pause);
            }
        }

        else if(alignment == 'm'){

            string temp;
            int getspaces{0};
        
            getspaces = (16 - message.length()) / 2 - 1;

            for(int i{0}; i <= getspaces; ++i)
                temp += " ";
            

            temp += message;
            for(int i{0}; i < temp.length(); ++i){
                lcd_byte(temp.at(i), LCD_CHR);
                if(i > getspaces)
                    delay(pause);
            }    
        }

         if(alignment == 'r'){

            string temp;
            int getspaces{0};

            getspaces = (16 - message.length());

            for(int i{0}; i < getspaces; ++i)
                temp += " "; 
            

            temp += message;
            for(int i{0}; i < temp.length(); ++i){
                lcd_byte(temp.at(i), LCD_CHR);
                if(i > getspaces)
                    delay(pause);
            }   
        }

    }

}

void LCD::print(char alignment, const char *s){
    string message;

    while ( *s ) message += *(s++);
    print(alignment, message;)
}

void LCD::printChar(char c){

}