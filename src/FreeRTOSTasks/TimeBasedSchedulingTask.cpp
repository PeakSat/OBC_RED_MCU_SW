#include "FreeRTOSTasks/TimeBasedSchedulingTask.hpp"

void TimeBasedSchedulingTask::execute() {
    LOG_DEBUG << "Runtime init: " << this->TaskName;
    auto &timeBasedScheduling = Services.timeBasedScheduling;

    TickType_t xLastWakeTime = xTaskGetTickCount();

    while (true) {
        LOG_DEBUG << "Runtime entered: " << this->TaskName;
        Time::DefaultCUC now = TimeGetter::getCurrentTimeDefaultCUC();
        auto nextActivityExecutionCUCTime = timeBasedScheduling.executeScheduledActivity(now);
        if (nextActivityExecutionCUCTime == Time::DefaultCUC::max()) {
            LOG_DEBUG << "Runtime exiting: " << this->TaskName;
            xTaskNotifyWait(0, 0, nullptr, portMAX_DELAY);
        } else {
            TickType_t nextActivityExecutionTime = std::chrono::duration_cast<std::chrono::milliseconds>(nextActivityExecutionCUCTime - now).count();
            LOG_DEBUG << "Runtime exiting: " << this->TaskName;
            vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(nextActivityExecutionTime));
        }
    }
}
