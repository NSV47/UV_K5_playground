#include "system.hpp"
#include "hardware/hardware.hpp"
#include "registers.hpp"
// #include "uv_k5_display.hpp"
// #include "rssi_sbar.hpp"
// #include <string.h>
#include "Single_Tone_Test_1200_Hz.hpp"
#include <stdint.h>

#define UART_BASE 0x4006B800

const char *a = "test";

typedef volatile struct {
   uint32_t DR;    // Data Register
   uint32_t SR;    // Status Register
   uint32_t BRR;   // Baud Rate Register
   uint32_t CR1;   // Control Register 1
   uint32_t CR2;   // Control Register 2
} UART_TypeDef;

static UART_TypeDef *const uart = (UART_TypeDef *)UART_BASE;

void uart_send_char(char c) {
    while (!(uart->SR & (1 << 7))) {}  // Ждём флаг TXE (Transmit Empty)
    uart->DR = c;
}

void uart_send_str(const char *s) {
    while (*s) {
        uart_send_char(*s++);
    }
}

CSingle_Tone_Test_1200_Hz Single_Tone_Test_1200_Hz;

int main()
{
   uart_send_str(a);
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
   IRQ_SYSTICK();
}