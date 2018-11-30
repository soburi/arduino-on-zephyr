#include "Uart.h"

class UartACM : public Uart
{
  public:
    UartACM(struct device* dev) : Uart(dev) { }
  protected:
    void begin_impl(unsigned long baudrate, uint16_t config);
};
