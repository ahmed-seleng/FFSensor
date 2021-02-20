#ifndef FFS_MLX_SPI_H
#define FFS_MLX_SPI_H

#include "FFS_MLX.h"

class FFS_MLX_SPI : public FFS_MLX
{
public:
    FFS_MLX_SPI(const uint8_t &cs);
    uint8_t reset();
    uint8_t begin();
    uint8_t sendCommand(const uint8_t &cmd);
    uint8_t writeRegister(const uint8_t &addr, const int16_t &data);
    uint8_t readRegister(const uint8_t &addr, int16_t *data);
    uint8_t requestMeasurement(uint8_t xyzt);
    uint8_t readMeasurement(uint8_t xyzt, int16_t out[]);
    uint8_t startBurstMode(uint8_t xyzt);
protected:
    uint8_t cs;
    void beginTransmission();
    void endTransmission();
};

#endif