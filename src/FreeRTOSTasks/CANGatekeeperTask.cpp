#include "CAN/Driver.hpp"
#include "CAN/Frame.hpp"
#include "CANGatekeeperTask.hpp"

CANGatekeeperTask::CANGatekeeperTask() : Task("CANGatekeeperTask") {
    CAN::Driver::initialize();

    outgoingQueue = xQueueCreateStatic(CAN::FrameQueueSize, sizeof(CAN::Frame), outgoingQueueStorageArea,
                                       &outgoingQueueBuffer);
    vQueueAddToRegistry(outgoingQueue, "CAN Outgoing");
    configASSERT(outgoingQueue);

    incomingSFQueue = xQueueCreateStatic(CAN::FrameQueueSize, sizeof(CAN::Frame), incomingSFQueueStorageArea,
                                         &incomingSFQueueBuffer);
    vQueueAddToRegistry(incomingSFQueue, "CAN Incoming SF");
    configASSERT(incomingSFQueue);

    incomingMFQueue = xQueueCreateStatic(CAN::FrameQueueSize, sizeof(CAN::Frame), incomingSFQueueStorageArea,
                                         &incomingMFQueueBuffer);
    vQueueAddToRegistry(incomingSFQueue, "CAN Incoming MF");
    configASSERT(incomingMFQueue);
}

void CANGatekeeperTask::execute() {
    LOG_DEBUG << "Runtime init: " << this->TaskName;
#ifdef OBC_EQM_LCL
    LCLDefinitions::lclArray[LCLDefinitions::CAN1].enableLCL();
    LCLDefinitions::lclArray[LCLDefinitions::CAN2].enableLCL();
#endif

    PIO_PinWrite(CAN::CAN_SILENT_1, false);
    PIO_PinWrite(CAN::CAN_SILENT_2, false);

    CAN::Frame out_message = {};
    CAN::Frame in_message = {};

    uint32_t ulNotifiedValue;

    while (true) {
//        LOG_DEBUG << "Runtime entered: " << this->TaskName;
        xTaskNotifyWait(0, 0, &ulNotifiedValue, portMAX_DELAY);

        if (xTaskGetTickCount() - lastTransmissionTime > 8000) {
            LOG_ERROR << "Resetting CAN LCLs";
            LCLDefinitions::lclArray[LCLDefinitions::CAN1].enableLCL();
            LCLDefinitions::lclArray[LCLDefinitions::CAN2].enableLCL();
            MCAN0_Initialize();
            MCAN1_Initialize();
        }

        if (getIncomingSFMessagesCount()) {
            xQueueReceive(incomingSFQueue, &in_message, portMAX_DELAY);
            CAN::TPProtocol::processSingleFrame(in_message);
        }
        CAN::TPProtocol::processMultipleFrames();

        if (uxQueueMessagesWaiting(outgoingQueue)) {
            xQueueReceive(outgoingQueue, &out_message, portMAX_DELAY);
            CAN::Driver::send(out_message);
        }
//        LOG_DEBUG << "Runtime is exiting: " << this->TaskName;
    }
}
