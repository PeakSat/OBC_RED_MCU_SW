#include "WatchdogTask.hpp"

void WatchdogTask::execute() {
    while (true) {

//        LOG_DEBUG << "Runtime entered: " << this->TaskName;
        WDT_Clear();
        LOG_DEBUG << "Watchdog reset";

//        LOG_DEBUG << "Runtime exit: " << this->TaskName;
        vTaskDelay(pdMS_TO_TICKS(WatchdogWindow));
    }
}
