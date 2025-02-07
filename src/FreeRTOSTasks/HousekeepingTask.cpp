#include "FreeRTOSTasks/HousekeepingTask.hpp"

void HousekeepingTask::execute() {

    LOG_DEBUG << "Runtime init: " << this->TaskName;
    auto &housekeeping = Services.housekeeping;
    uint32_t nextCollection = 0;
    uint32_t timeBeforeDelay = 0;
    TickType_t xLastWakeTime = xTaskGetTickCount();

    while (true) {
//        LOG_DEBUG << "Runtime entered: " << this->TaskName;
        nextCollection = housekeeping.reportPendingStructures(xTaskGetTickCount(), timeBeforeDelay, nextCollection);
        timeBeforeDelay = xTaskGetTickCount();
//        LOG_DEBUG << "Runtime exit: " << this->TaskName;
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(nextCollection));
    }
}
