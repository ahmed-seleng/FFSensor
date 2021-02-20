#include "FFS_MLX.h"

const uint8_t FFS_MLX::CMD_SB = 0x10;
const uint8_t FFS_MLX::CMD_SW = 0x20;
const uint8_t FFS_MLX::CMD_SM = 0x30;
const uint8_t FFS_MLX::CMD_RM = 0x40;
const uint8_t FFS_MLX::CMD_RR = 0x50;
const uint8_t FFS_MLX::CMD_WR = 0x60;
const uint8_t FFS_MLX::CMD_EX = 0x80;
const uint8_t FFS_MLX::CMD_HR = 0xd0;
const uint8_t FFS_MLX::CMD_HS = 0xe0;
const uint8_t FFS_MLX::CMD_RT = 0xf0;
const uint8_t FFS_MLX::ERROR_BIT = 0x10;
const uint8_t FFS_MLX::X = 0x08;
const uint8_t FFS_MLX::Y = 0x04;
const uint8_t FFS_MLX::Z = 0x02;
const uint8_t FFS_MLX::T = 0x01;

uint8_t FFS_MLX::setZSeriesGainHallconf(bool zSeries, uint8_t gain, uint8_t hallconf)
{
    int16_t data = (zSeries << 7) + ((gain & 0x05) << 4) + (hallconf & 0x07);
    return writeRegister(0x00, data);
}

uint8_t FFS_MLX::setTrigCommWocExtTcmpBurst(bool trig, uint8_t commMode, bool wakeOnChange, bool externalTrig, bool temperatureCompensation, uint8_t burstData, uint8_t burstRate)
{
    int16_t data = (trig << 15) + ((commMode & 0x03) << 13) + (wakeOnChange << 12) + (externalTrig << 11) + (temperatureCompensation << 10) + ((burstData & 0x07) << 6) + (burstRate & 0x3f);
    return writeRegister(0x01, data);
}

uint8_t FFS_MLX::setOversampleTempResolutionFilterOversampleXyz(uint8_t osrT, uint8_t resolution, uint8_t filter, uint8_t osrXyz)
{
    int16_t data = ((osrT & 0x03) << 11) + ((resolution & 0x3f) << 5) + ((filter & 0x05) << 2) + (osrXyz & 0x3);
    return writeRegister(0x02, data);
}

uint8_t FFS_MLX::setSensetivityDriftCompensation(uint8_t highTemperature, uint8_t lowTemperature)
{
    int16_t data = (highTemperature << 8) + lowTemperature;
    return writeRegister(0x03, data);
}

uint8_t FFS_MLX::setOffsetX(int16_t offsetX)
{
    return writeRegister(0x04, offsetX);
}

uint8_t FFS_MLX::setOffsetY(int16_t offsetY)
{
    return writeRegister(0x05, offsetY);
}

uint8_t FFS_MLX::setOffsetZ(int16_t offsetZ)
{
    return writeRegister(0x06, offsetZ);
}

uint8_t FFS_MLX::setWakeXY(int16_t threshold)
{
    return writeRegister(0x07, threshold);
}

uint8_t FFS_MLX::setWakeZ(int16_t threshold)
{
    return writeRegister(0x08, threshold);
}

uint8_t FFS_MLX::setWakeT(int16_t threshold)
{
    return writeRegister(0x09, threshold);
}