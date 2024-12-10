#include <stc15.h>
#include "IO_Init.h"
#include "LCD1602.H"
#include "Init_config.h"
//#include "Delay.h"
//#include "Button.h"
//#include "SMG.h"
//#include "EEPROM.h"
//#include "HC06_BT.h"
//#include "Built_In_ADC.h"
#include "key.h"
#include "Clock.h"

void main(void)
 {  
    uint i=0;
    GPIO_Init();
//	LcdInit();
//    Key_Init();
    Clock_Init(); 
    while (1)
    {
        Key_Scan();
        MainSystem();

        
    }
}

