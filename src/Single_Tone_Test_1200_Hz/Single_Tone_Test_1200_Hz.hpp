#pragma once
#include "system.hpp"
#include "uv_k5_display.hpp"

class CSingle_Tone_Test_1200_Hz
{
public:
   static constexpr auto StepSize = 0xFFFF / TUV_K5Display::SizeX;
   static constexpr auto StepSizeFreq = 10'000;
   CSingle_Tone_Test_1200_Hz()
       : DisplayBuff(gDisplayBuffer), FontSmallNr(gSmallDigs), Display(DisplayBuff), x(DisplayBuff.SizeX / 2), y(DisplayBuff.SizeY / 2)
         ,bEnabled(true){};

   void Handle()
   {
      if(!bEnabled)
      {
         return;
      }

      DisplayBuff.ClearAll();
      char C8RssiString[] = "0000000000000";

      unsigned int u32Key = PollKeyboard();
      if(u32Key == 13) // exit key
      {
         bEnabled = false;
      }

    //   C8RssiString[0] = '0' + (u32Key / 100);
    //   C8RssiString[1] = '0' + (u32Key / 10) % 10;
    //   C8RssiString[2] = '0' + u32Key % 10;

    C8RssiString[0]  = '1';
    C8RssiString[1]  = '2';
    C8RssiString[2]  = '3';
    C8RssiString[3]  = '4';
    C8RssiString[4]  = '5';
    C8RssiString[5]  = '6';
    C8RssiString[6]  = '7';
    C8RssiString[7]  = '8';
    C8RssiString[8]  = '9';
    C8RssiString[9]  = '0';
    C8RssiString[10] = '1';
    C8RssiString[11] = '2';

    //   Game.handle(u32Key);
    //   auto const BallPosition = Game.getBallPosition();
    //   auto const PlatformPosition = Game.getPlatformPosition();
      
    //   Display.DrawRectangle(BallPosition.x, BallPosition.y, 7, 7, true);
    //   Display.DrawRectangle(PlatformPosition.x, PlatformPosition.y, 6, 20, true);
      Display.SetCoursor(0, 0);
      Display.SetFont(&FontSmallNr);
    //   WriteSerialData((unsigned char *)"RX packet, hex: ", 17);
      Display.Print(C8RssiString);

    #if 0
        static unsigned int u32Cnt = 0;
        u32Cnt++;
        if((u32Cnt >> 8) % 2)
        {
            unsigned int* p32Buff = (unsigned int*)gDisplayBuffer;
            for(int i = 0; i < (DisplayBuff.SizeX * DisplayBuff.SizeY) / (8*4); i++)
            {
                *p32Buff = ~(*p32Buff);
                p32Buff++;
            }
        }

    #endif
        FlushFramebufferToScreen();
    
    }

private:
   TUV_K5Display DisplayBuff;
   const TUV_K5SmallNumbers FontSmallNr;
   CDisplay<const TUV_K5Display> Display;

   unsigned char x, y;
   bool bEnabled;
};
