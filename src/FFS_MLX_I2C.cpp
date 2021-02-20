#include "FFS_MLX_I2C.h"
#include <Wire.h>
#include <Arduino.h>

FFS_MLX_I2C::FFS_MLX_I2C(const uint8_t &addr)
{
    mlxAddr = addr;
}

uint8_t FFS_MLX_I2C::begin()
{
    Wire.begin();
    uint8_t status;
    status = reset();
    return status;
}

uint8_t FFS_MLX_I2C::reset()
{
    uint8_t status;
    status = sendCommand(CMD_RT);
    delay(10);
    status = sendCommand(CMD_RT);
    delay(10);
    return status;
}

uint8_t FFS_MLX_I2C::sendCommand(const uint8_t &cmd)
{
    Wire.beginTransmission(mlxAddr);
    Wire.write(cmd);
    Wire.endTransmission();
    Wire.requestFrom(mlxAddr, uint8_t(1));
    uint8_t status = Wire.read();
    return status;
}

uint8_t FFS_MLX_I2C::writeRegister(const uint8_t &addr, const int16_t &data)
{
    if (addr >= 0x20){ return 0xff; }
    Wire.beginTransmission(mlxAddr);
    Wire.write(CMD_WR);
    Wire.write((data & 0xff00) >> 8);
    Wire.write(data & 0x00ff);
    Wire.write((addr & 0x3f) << 2);
    Wire.endTransmission();
    Wire.requestFrom(mlxAddr, uint8_t(1));
    uint8_t status = Wire.read();
    return status;
}

uint8_t FFS_MLX_I2C::readRegister(const uint8_t &addr, int16_t *data)
{
    if (addr >= 0x20){ return 0xff; }
    Wire.beginTransmission(mlxAddr);
    Wire.write(CMD_RR);
    Wire.write((addr & 0x3f) << 2);
    Wire.endTransmission();
    Wire.requestFrom(mlxAddr, uint8_t(3));
    uint8_t status = Wire.read();
    *data = Wire.read();
    *data = (*data << 8) + Wire.read();
    return status;
}

uint8_t FFS_MLX_I2C::requestMeasurement(uint8_t xyzt)
{
    uint8_t command = CMD_SM | (xyzt & 0x0f);
    uint8_t status = sendCommand(command);
    return status;
}

uint8_t FFS_MLX_I2C::readMeasurement(uint8_t xyzt, int16_t out[])
{
    xyzt &= 0x0f;
    uint8_t measurementSize = __builtin_popcount(xyzt);
    uint8_t command = CMD_RM | (xyzt & 0x0f);
    Wire.beginTransmission(mlxAddr);
    Wire.write(command);
    Wire.endTransmission();
    Wire.requestFrom(mlxAddr, uint8_t(measurementSize * 2 + 1));
    uint8_t status = Wire.read();
    for (uint8_t index = 0; index < measurementSize; index ++) {
        out[index] = Wire.read();
        out[index] = (out[index] << 8) + Wire.read();
    }
    return status;
}

uint8_t FFS_MLX_I2C::startBurstMode(uint8_t xyzt)
{
    uint8_t command = CMD_SB | (xyzt & 0x0f);
    uint8_t status = sendCommand(command);
    return status;
}
