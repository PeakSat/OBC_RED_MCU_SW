#ifndef OBC_SOFTWARE_HOUSEKEEPINGTASK_HPP
#define OBC_SOFTWARE_HOUSEKEEPINGTASK_HPP

#include "Task.hpp"

/**
 * FreeRTOS task implementing the ST[03] Housekeeping Service.
 */
class HousekeepingTask : public Task {
public:
    const static inline uint16_t TaskStackDepth = 2000;

    StackType_t taskStack[TaskStackDepth];

    /**
      * @see HousekeepingService
      */
    void execute();

    HousekeepingTask() : Task("Housekeeping") {}

    static inline TaskHandle_t housekeepingTaskHandle;

    /**
     * Create freeRTOS Task
     */
    void createTask() {
        housekeepingTaskHandle = xTaskCreateStatic(vClassTask<HousekeepingTask>, this->TaskName, HousekeepingTask::TaskStackDepth,
                          this, configMAX_PRIORITIES - 1, this->taskStack,
                          &(this->taskBuffer));
    }

};

inline std::optional<HousekeepingTask> housekeepingTask;

#endif
