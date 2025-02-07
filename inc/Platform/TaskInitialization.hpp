#pragma once

#include "FreeRTOS.h"
#include "SEGGER_RTT.h"
#include "TimeKeepingTask.hpp"
#include "MCUTemperatureTask.hpp"
#include "AmbientTemperatureTask.hpp"
#include "UARTGatekeeperTask.hpp"
#include "WatchdogTask.hpp"
#include "CANGatekeeperTask.hpp"
#include "CANTestTask.hpp"
#include "HousekeepingTask.hpp"
#include "TimeBasedSchedulingTask.hpp"
#include "StatisticsReportingTask.hpp"
#include "TCHandlingTask.hpp"
#include "PayloadTestTask.hpp"

void initializeTasks();

void IdleStateInit();

void REDModeInit();