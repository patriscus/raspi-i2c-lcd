#include "LCD.h"
using namespace std;

int main(){
    LCD lcd {alignment::middle, 50};

    while(1){
        lcd << "This is a test, if word wrap works.":
        delay(1000);
    }
    
    return 0;
}