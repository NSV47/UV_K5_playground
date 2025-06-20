#include "system.hpp"
#include "hardware/hardware.hpp"
#include "registers.hpp"
// #include "uv_k5_display.hpp"
// #include "rssi_sbar.hpp"
// #include <string.h>
#include "Single_Tone_Test_1200_Hz.hpp"

CSingle_Tone_Test_1200_Hz Single_Tone_Test_1200_Hz;

int main()
{
   // WriteSerialData((unsigned char *)"RX packet, hex: ", 17);
   IRQ_RESET();
   return 0;
}

extern "C" void Reset_Handler()
{
   IRQ_RESET();
}

extern "C" void SysTick_Handler()
{
   static bool bFirstInit = false;
   if(!bFirstInit)
   {
      System::CopyDataSection();
      __libc_init_array();
      bFirstInit = true;
   }
   
   static unsigned int u32StupidCounter = 1;
   if((!(u32StupidCounter++ % 2) && u32StupidCounter > 200))
   {
    //   Pong.Handle();
      Single_Tone_Test_1200_Hz.Handle();
   }

   static unsigned int u32MyStupidCounter = 1;
   if((!(u32MyStupidCounter++ % 20) && u32MyStupidCounter > 2000))
   {
    //   Pong.Handle();
      // Single_Tone_Test_1200_Hz.Handle();
      WriteSerialData((unsigned char *)"RX packet, hex: ", 17);
   }
   IRQ_SYSTICK();
}