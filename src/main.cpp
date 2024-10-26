#include <Arduino.h>
#include <BLE2902.h>
#include <BLEDevice.h>
#include <BLEServer.h>
// #include <BLEUtils.h>

#include <Assign.hpp>
#include <Motor/DG01D_E.hpp>
#include <System.hpp>

#include <iostream>
using namespace std;

#define BUFFER 64

BLEServer         *pServer = NULL;
BLECharacteristic *pTxCharacteristic;
bool               deviceConnected    = false;
bool               oldDeviceConnected = false;
uint8_t            txValue[BUFFER]    = "";

Motor::DG01D_E left_motor{assign::LEFT_MOTOR_PWM_PIN1,     assign::LEFT_MOTOR_PWM_PIN2, assign::LEFT_MOTOR_ENCODER_PIN1,
                          assign::LEFT_MOTOR_ENCODER_PIN2, assign::LEFT_MOTOR_PWM_CH1,  assign::LEFT_MOTOR_PWM_CH2};
Motor::DG01D_E right_motor{assign::RIGHT_MOTOR_PWM_PIN1,     assign::RIGHT_MOTOR_PWM_PIN2,
                           assign::RIGHT_MOTOR_ENCODER_PIN1, assign::RIGHT_MOTOR_ENCODER_PIN2,
                           assign::RIGHT_MOTOR_PWM_CH1,      assign::RIGHT_MOTOR_PWM_CH2};

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"  // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer *pServer) {
        deviceConnected = true;
    };

    void onDisconnect(BLEServer *pServer) {
        deviceConnected = false;
    }
};

class MyCallbacks : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
        std::string rxValue = pCharacteristic->getValue();
        if (rxValue.length() > 0) {
            Serial.println("*********");
            Serial.print("Received Value: ");
            String s = "";
            for (int i = 0; i < rxValue.length(); i++) {
                Serial.print(rxValue[i]);
                s += rxValue[i];
            }
            System::changeSpeedMotors(s.toInt(), left_motor, right_motor);
            Serial.println();
            Serial.println("*********");
        }
    }
};

void setup() {
    Serial.begin(115200);

    // Create the BLE Device
    BLEDevice::init("BLE_Control");

    // Create the BLE Server
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    // Create the BLE Service
    BLEService *pService = pServer->createService(SERVICE_UUID);

    // Create a BLE Characteristic
    pTxCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_TX, BLECharacteristic::PROPERTY_NOTIFY);

    pTxCharacteristic->addDescriptor(new BLE2902());

    BLECharacteristic *pRxCharacteristic =
        pService->createCharacteristic(CHARACTERISTIC_UUID_RX, BLECharacteristic::PROPERTY_WRITE);

    pRxCharacteristic->setCallbacks(new MyCallbacks());

    // Start the service
    pService->start();

    // Start advertising
    pServer->getAdvertising()->start();
    Serial.println("Waiting a client connection to notify...");
    BLESecurity *pSecurity = new BLESecurity();
    pSecurity->setStaticPIN(123456);
}

void loop() {

    // 以下修正箇所　COMからデータを読み取り、BLEに送信
    if (deviceConnected == true) {
        if (Serial.available() != 0) {
            size_t bufSize = Serial.read(txValue, Serial.available());
            pTxCharacteristic->setValue(txValue, bufSize);
            pTxCharacteristic->notify();
        }

        delay(10);  // bluetooth stack will go into congestion, if too many packets are sent
    }
    // ここまで

    // disconnecting
    if (!deviceConnected && oldDeviceConnected) {
        delay(500);                   // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising();  // restart advertising
        Serial.println("start advertising");
        oldDeviceConnected = deviceConnected;
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected) {
        // do stuff here on connecting
        oldDeviceConnected = deviceConnected;
    }
}