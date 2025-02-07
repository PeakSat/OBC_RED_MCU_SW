#include "FreeRTOSTasks/StatisticsReportingTask.hpp"

void StatisticsReportingTask::execute() {
    LOG_DEBUG << "Runtime init: " << this->TaskName;
    auto &parameterStatistics = Services.parameterStatistics;
    TickType_t xLastWakeTime = xTaskGetTickCount();

    while (true) {
        LOG_DEBUG << "Runtime entered: " << this->TaskName;
        if (parameterStatistics.getPeriodicReportingStatus()) {
            parameterStatistics.reportParameterStatistics(false);
        }
        LOG_DEBUG << "Runtime exiting: " << this->TaskName;
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(parameterStatistics.getReportingIntervalMs()));
    }
}
