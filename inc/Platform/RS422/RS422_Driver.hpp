//
// Created by tats on 10/7/2024.
//

#ifndef OBC_SOFTWARE_RS422_DRIVER_HPP
#define OBC_SOFTWARE_RS422_DRIVER_HPP

#include <stdlib.h>
#include <cstdint>
#include <definitions.h>
#include "peripheral/uart/plib_uart2.h"

void enterLowPowerModeRS422();

bool sendPayloadMessage(uint8_t* msg, size_t msg_size);

bool sendPayloadStatus();

#endif //OBC_SOFTWARE_RS422_DRIVER_HPP
