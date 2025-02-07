//
// Created by tats on 10/7/2024.
//

#include "PayloadTestTask.hpp"
#include "RS422/Payload_Message.hpp"

void PayloadTestTask::execute() {

    LOG_DEBUG << "Runtime init: " << this->TaskName;

    while (true) {

//        LOG_DEBUG << "Runtime entered: " << this->TaskName;
        if(sendPayloadMessage(payloadMessage, 512)){
            LOG_DEBUG<<"Sent 512 bytes payload message";
        }else{
            LOG_DEBUG<<"Unable to send payload message";
        }

        enterLowPowerModeRS422();

//        LOG_DEBUG << "Runtime exit: " << this->TaskName;
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}