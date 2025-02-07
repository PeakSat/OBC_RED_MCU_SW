#include "TaskInitialization.hpp"

void initializeTasks() {
    uartGatekeeperTask.emplace();
    timeKeepingTask.emplace();
    ambientTemperatureTask.emplace();
    watchdogTask.emplace();
    mcuTemperatureTask.emplace();
    tcHandlingTask.emplace();
    housekeepingTask.emplace();
    canGatekeeperTask.emplace();
    canTestTask.emplace();
    payloadTestTask.emplace();
//    nandTask.emplace();
//    mramTask.emplace();


    ambientTemperatureTask->createTask();
    mcuTemperatureTask->createTask();
    timeKeepingTask->createTask();
    uartGatekeeperTask->createTask();
    watchdogTask->createTask();
    tcHandlingTask->createTask();
    housekeepingTask->createTask();
    canGatekeeperTask->createTask();
    canTestTask->createTask();
    payloadTestTask->createTask();
//    nandTask->createTask();
//    mramTask->createTask();

}

void IdleStateInit(){
    vTaskSuspend(MCUTemperatureTask::mcuTempTaskHandle);
    vTaskSuspend(AmbientTemperatureTask::ambientTempTaksHandle);
    vTaskSuspend(TimeKeepingTask::timeTaskHandle);
    vTaskSuspend(TCHandlingTask::tcHandlingTaskHandle);
    vTaskSuspend(HousekeepingTask::housekeepingTaskHandle);
    vTaskSuspend(CANTestTask::canTestTaskHanle);
    vTaskSuspend(PayloadTestTask::payloadtaskHandle);
    vTaskSuspend(UARTGatekeeperTask::uartTaskHandle);
}

void REDModeInit(){
    xTaskResumeAll();
}