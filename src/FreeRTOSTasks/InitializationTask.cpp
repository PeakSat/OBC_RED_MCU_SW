#include "InitializationTask.hpp"

void InitializationTask::execute() {
    initializeTasks();
    LOG_DEBUG<<"going IDLE";
    IdleStateInit();

    vTaskDelete(nullptr);
}
