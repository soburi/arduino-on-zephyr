#include "ZLogger.h"
#include <zephyr.h>

LOG_MODULE_REGISTER(foo, LOG_LEVEL_DBG);

size_t ZLoggerClass::write(uint8_t b) {
	size_t sz = concat(static_cast<char>(b));
	if(b == '\n') {
		const char* ptr = c_str();
		if(ptr[length()-2] == '\r') {
			setCharAt(length()-2, 0);
			Z_LOG(loglevel, "%s", c_str() );
			invalidate();
		}
	}

	return sz;
}

ZLoggerClass ZLogger;
