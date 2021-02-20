#include "FFS_MLX_SPI.h"
#include <SPI.h>
#include <Arduino.h>

FFS_MLX_SPI::FFS_MLX_SPI(const uint8_t &cs_pin)
{
    cs = cs_pin;
}

uint8_t FFS_MLX_SPI::begin()
{
    SPI.begin();
    pinMode(cs, OUTPUT);
    uint8_t status;
    status = reset();
    return status;
}

uint8_t FFS_MLX_SPI::reset()
{
    uint8_t status;
    status = sendCommand(CMD_RT);
    delay(10);
    status = sendCommand(CMD_RT);
    delay(10);
    return status;
}

uint8_t FFS_MLX_SPI::sendCommand(const uint8_t &cmd)
{
    beginTransmission();
    SPI.transfer(cmd);
    uint8_t status = SPI.transfer(0x00);
    endTransmission();
    return status;
}

uint8_t FFS_MLX_SPI::writeRegister(const uint8_t &addr, const int16_t &data)
{
    if (addr >= 0x20){ return 0xff; }
    beginTransmission();
    SPI.transfer(CMD_WR);
    SPI.transfer((data & 0xff00) >> 8);
    SPI.transfer(data & 0x00ff);
    SPI.transfer((addr & 0x3f) << 2);
    uint8_t status = SPI.transfer(0x00);
    endTransmission();
    return status;
}

uint8_t FFS_MLX_SPI::readRegister(const uint8_t &addr, int16_t *data)
{
    if (addr >= 0x20){ return 0xff; }
    beginTransmission();
    SPI.transfer(CMD_RR);
    SPI.transfer((addr & 0x3f) << 2);
    uint8_t status = SPI.transfer(0x00);
    *data = SPI.transfer(0x00);
    *data = (*data << 8) + SPI.transfer(0x00);
    endTransmission();
    return status;
}

uint8_t FFS_MLX_SPI::requestMeasurement(uint8_t xyzt)
{
    uint8_t command = CMD_SM | (xyzt & 0x0f);
    uint8_t status = sendCommand(command);
    return status;
}

uint8_t FFS_MLX_SPI::readMeasurement(uint8_t xyzt, int16_t out[])
{
    xyzt &= 0x0f;
    uint8_t measurementSize = __builtin_popcount(xyzt);
    uint8_t command = CMD_RM | (xyzt & 0x0f);
    beginTransmission();
    SPI.transfer(command);
    uint8_t status = SPI.transfer(0x00);
    for (uint8_t index = 0; index < measurementSize; index ++) {
        out[index] = SPI.transfer(0x00);
        out[index] = (out[index] << 8) + SPI.transfer(0x00);
    }
    endTransmission();
    return status;
}

uint8_t FFS_MLX_SPI::startBurstMode(uint8_t xyzt)
{
    uint8_t command = CMD_SB | (xyzt & 0x0f);
    uint8_t status = sendCommand(command);
    return status;
}


void FFS_MLX_SPI::beginTransmission()
{
    digitalWrite(cs, LOW);
    SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE3));
}

void FFS_MLX_SPI::endTransmission()
{
    SPI.endTransaction();
    digitalWrite(cs, HIGH);
}
