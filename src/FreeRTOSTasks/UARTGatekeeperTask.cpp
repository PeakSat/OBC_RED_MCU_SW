#include "UARTGatekeeperTask.hpp"

UARTGatekeeperTask::UARTGatekeeperTask() : Task("UARTGatekeeperTask") {
    xUartQueue = xQueueCreateStatic(UARTQueueSize, sizeof(etl::string<LOGGER_MAX_MESSAGE_SIZE>), ucQueueStorageArea,
                                    &xStaticQueue);
}

void UARTGatekeeperTask::execute() {
    LOG_DEBUG << "Runtime init: " << this->TaskName;
    etl::string<LoggerMaxMessageSize> output;
    const void *txRegisterAddress = const_cast<void *>(reinterpret_cast<volatile void *>(&UART_PERIPHERAL_REGISTER));
    while (true) {
//        LOG_DEBUG << "Runtime entered: " << this->TaskName;
        xQueueReceive(xUartQueue, &output, portMAX_DELAY);
        output.repair();

        if constexpr (LogsAreCOBSEncoded) {
            auto cobsEncoded = COBSencode<LoggerMaxMessageSize>(output);
            XDMAC_ChannelTransfer(XDMAC_CHANNEL_0, cobsEncoded.data(), txRegisterAddress, cobsEncoded.size());
        } else {
            XDMAC_ChannelTransfer(XDMAC_CHANNEL_0, output.data(), txRegisterAddress, output.size());
        }
//        LOG_DEBUG << "Runtime exiting: " << this->TaskName;
        vTaskDelay(100);
    }
}
