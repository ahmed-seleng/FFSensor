#ifndef FFSENSOR_H
#define FFSENSOR_H

#include "FFS_MLX.h"

/**
 * Namespace to store FFS-related constants.
 */
namespace FFS {
    static const uint8_t calibrationSize = 20;
}

/**
 * Class for communicating with FFS sensor via provided FFS_MLX instance.
 *
 * Several FFSensors can use single FFS_MLX instance if communicate through demux.
 */
class FFSensor {
public:
    /**
     * Create FFSensor instance from FFS_MLX data provider and calibration table.
     */
    FFSensor(FFS_MLX &sensor, float const *calibrationTable);

    /**
     * Initialize the FFSensor.
     * This method should be called once.
     *
     * @return mlx status
     */
    uint8_t begin();

    /**
     * Initialize the FFSensor.
     * This methos should be called once.
     * 
     * @param intro_delay the delay in ms to wait before starting the zeroing process
     * @param count the count of measurement iterations for median counting
     * @return mlx status
     */
    uint8_t begin(uint32_t intro_delay, uint16_t count);

    /**
     * Request single measurement.
     * The measurement may take up to 10ms in default configuration to complete.
     *
     * @return mlx status
     */
    uint8_t requestMeasurement();

    /**
     * Read the measurement and calculate internal values.
     *
     * @return mlx status
     */
    uint8_t readMeasurement();

    /**
     * Request and read single measurement.
     * This is blocking method, it will take at least 10ms to complete.
     *
     * @return mlx status
     */
    uint8_t requestAndReadMeasurement();

    /**
     * Request and read single measurement with given delay between request and read.
     * This is blocking method, it will take at least `time` ms to complete.
     *
     * @param time a time to wait between request and read operation in ms
     * @return mlx status
     */
    uint8_t requestAndReadMeasurement(const uint64_t &time);

    /**
     * Get the x component of measured force.
     *
     * @return force in N
     */
    float x();

    /**
     * Get the y component of measured force.
     *
     * @return force in N
     */
    float y();

    /**
     * Get the z component of measured force.
     *
     * @return force in N
     */
    float z();
protected:
    /**
     * Reference to mlx sensor communication implementation.
     */
    FFS_MLX &mlx;

    /**
     * The pointer to calibration table.
     */
    float const *calibration;

    /**
     * Approximate the force using measured data and calibration table.
     *
     * @return approximation result
     */
    float approximate(const float &x, const float &y, const float &z, const float* c);
private:
    float forceX;
    float forceY;
    float forceZ;
    int16_t offsetX;
    int16_t offsetY;
    int16_t offsetZ;
};

#endif
