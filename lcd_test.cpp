#include "LCD.h"
using namespace std;

int main(){
    LCD lcd;
    char r = 'r';
    char l = 'l';
    char m = 'm';

    while(1){
        string hello = "Hello";

        lcd.clear(0);
        lcd.lcdLoc(1);
        lcd.print(m, 50, hello);

        string test_wrap = "A test, if word wrap works as intended";
        lcd.clear(1000);
        lcd.lcdLoc(1);
        lcd.print(l, 50, test_wrap);

        delay(1000);
    }

    return 0;
}