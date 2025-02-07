#include "CANTestTask.hpp"
#include "CANGatekeeperTask.hpp"

void CANTestTask::execute() {

    LOG_DEBUG << "Runtime init: " << this->TaskName;
    CAN::Frame frame = {CAN::NodeID};
    for (auto i = 0; i < CAN::Frame::MaxDataLength; i++) {
        frame.data.at(i) = i;
    }

    String<ECSSMaxMessageSize> testPayload1("WHO LIVES IN A PINEAPPLE UNDER THE SEA?");

    String<ECSSMaxMessageSize> testPayload2("Giati?");

    while (true) {

//        LOG_DEBUG << "Runtime entered: " << this->TaskName;
        if(AcubeSATParameters::obcCANBUSActive.getValue() == CAN::Driver::ActiveBus::Redundant) {
            AcubeSATParameters::obcCANBUSActive.setValue(CAN::Driver::ActiveBus::Main);
            CAN::Application::createLogMessage(CAN::NodeIDs::COMMS, false, testPayload1.data(), false);
            LOG_DEBUG << "Sent CAN message to main CAN bus";
        } else {
            AcubeSATParameters::obcCANBUSActive.setValue(CAN::Driver::ActiveBus::Redundant);
            CAN::Application::createLogMessage(CAN::NodeIDs::COMMS, false, testPayload2.data(), false);
            LOG_DEBUG << "Sent CAN message to redundant CAN bus";
        }


//        xTaskNotify(canGatekeeperTask->taskHandle, 0, eNoAction);

//        LOG_DEBUG << "Runtime exit: " << this->TaskName;
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}