#pragma once

#include "TaskInitialization.hpp"
#include "TCHandlingTask.hpp"
#include "Task.hpp"

/**
 * The first task to run after starting the scheduler used to spawn the rest of the tasks.
 */
class InitializationTask: public Task {
public:
    const static inline uint16_t TaskStackDepth = 8300;

    StackType_t taskStack[TaskStackDepth];

    InitializationTask() : Task("InitializationTask") {}

    void execute();

    void createTask() {
        xTaskCreateStatic(vClassTask<InitializationTask>, this->TaskName, InitializationTask::TaskStackDepth,
                          this, configMAX_PRIORITIES - 1, this->taskStack,
                          &(this->taskBuffer));
    }
};

inline std::optional<InitializationTask> initializationTask;

