//
// Created by tats on 10/7/2024.
//

#include "RS422/RS422_Driver.hpp"


/*
 * ADM3491 module
 * RO -> Receiver Output -> Connected to UART2_RX
 * DI -> Driver Input -> Connected to UART2_TX
 * RE -> Receiver Output Enable, Active Low -> Connected to PD30 (Chip pad 34)
 * DE -> Driver Output Enable, Active High -> Connected to PD16 (Chip pad 78)
 *
 * ! If RE is High and DE is Low, the device enters a low power
 * shutdown mode
 *
 */

void enterLowPowerModeRS422(){
    PIO_PinWrite(PAYLOAD_RX_ENABLE_PIN, true);
    PIO_PinWrite(PAYLOAD_TX_ENABLE_PIN, true);
}

bool sendPayloadStatus(){
    return UART2_TransmitComplete();
}

bool sendPayloadMessage(uint8_t* msg, size_t msg_size){
    bool status = false;

    if(sendPayloadStatus()){
        PIO_PinWrite(PAYLOAD_TX_ENABLE_PIN, true);
        status = UART2_Write(msg, msg_size);
        //PIO_PinWrite(PAYLOAD_TX_ENABLE_PIN, false);
    }
    return status;
}

