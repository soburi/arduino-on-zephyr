#ifndef ZLOGGER_H
#define ZLOGGER_H

#include "Arduino.h"
#include <logging/log.h>

class ZLoggerClass : public Print, private String
{
private:
  uint16_t loglevel;
public:
  size_t write(uint8_t b);

  inline void begin(uint16_t lv) { loglevel = lv; }

  using Print::write;
};

extern ZLoggerClass ZLogger;
#endif
