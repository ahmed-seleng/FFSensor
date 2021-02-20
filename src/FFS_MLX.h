#ifndef FFS_MLX_H
#define FFS_MLX_H

#include <Arduino.h>

class FFS_MLX
{
protected:
    /**
     * Start Burst Mode command.
     */
    static const uint8_t CMD_SB;

    /**
     * Start Wake-up on Change Mode command.
     */
    static const uint8_t CMD_SW;

    /**
     * Start Single Measurement Mode command.
     */
    static const uint8_t CMD_SM;

    /**
     * Read Measurement command.
     */
    static const uint8_t CMD_RM;

    /**
     * Read Register command.
     */
    static const uint8_t CMD_RR;

    /**
     * Write Register command.
     */
    static const uint8_t CMD_WR;

    /**
     * Exit Mode command.
     */
    static const uint8_t CMD_EX;

    /**
     * Memory Recall command.
     */
    static const uint8_t CMD_HR;

    /**
     * Memory Store command.
     */
    static const uint8_t CMD_HS;

    /**
     * Reset command.
     */
    static const uint8_t CMD_RT;
public:

    /**
     * The error flag in mlx answer.
     */
    static const uint8_t ERROR_BIT;

    /**
     * The X bit for requestMeasurement and readMeasurement commands.
     */
    static const uint8_t X;

    /**
     * The Y bit for requestMeasurement and readMeasurement commands.
     */
    static const uint8_t Y;

    /**
     * The Z bit for requestMeasurement and readMeasurement commands.
     */
    static const uint8_t Z;

    /**
     * The T bit for requestMeasurement and readMeasurement commands.
     */
    static const uint8_t T;

    /**
     * Initialize the FFS_MLX.
     *
     * Should be called once.
     * @return the mlx status
     */
    virtual uint8_t begin() = 0;

    /**
     * Send the Reset command to MLX90393.
     *
     * @return the mlx status
     */
    virtual uint8_t reset() = 0;

    /**
     * Send command to MLX90393.
     *
     * @return the mlx status
     */
    virtual uint8_t sendCommand(const uint8_t &cmd) = 0;

    /**
     * Write data to MLX90393 register.
     *
     * @return the mlx status
     */
    virtual uint8_t writeRegister(const uint8_t &addr, const int16_t &data) = 0;

    /**
     * Read MLX90393 register.
     *
     * @return the mlx status
     */
    virtual uint8_t readRegister(const uint8_t &addr, int16_t *data) = 0;

    /**
     * Request the measurement to be performed by the MLX90393.
     *
     * @return the mlx status
     */
    virtual uint8_t requestMeasurement(uint8_t xyzt) = 0;

    /**
     * Read the measurement performed by the MLX90393.
     *
     * @return the mlx status
     */
    virtual uint8_t readMeasurement(uint8_t xyzt, int16_t out[]) = 0;

    /**
     * Start burst measurement mode.
     *
     * @return the mlx status
     */
    virtual uint8_t startBurstMode(uint8_t xyzt) = 0;

    uint8_t setZSeriesGainHallconf(bool zSeries, uint8_t gain, uint8_t hallconf);
    uint8_t setTrigCommWocExtTcmpBurst(bool trig, uint8_t commMode, bool wakeOnChange, bool externalTrig, bool temperatureCompensation, uint8_t burstData, uint8_t burstRate);
    uint8_t setOversampleTempResolutionFilterOversampleXyz(uint8_t osrT, uint8_t resolution, uint8_t filter, uint8_t osrXyz);
    uint8_t setSensetivityDriftCompensation(uint8_t highTemperature, uint8_t lowTemperature);
    uint8_t setOffsetX(int16_t offsetX);
    uint8_t setOffsetY(int16_t offsetY);
    uint8_t setOffsetZ(int16_t offsetZ);
    uint8_t setWakeXY(int16_t threshold);
    uint8_t setWakeZ(int16_t threshold);
    uint8_t setWakeT(int16_t threshold);
};

#endif