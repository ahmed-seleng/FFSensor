#include "FFSensor.h"
#include "FFS_MLX.h"

FFSensor::FFSensor(FFS_MLX &sensor, float const *calibrationTable) : mlx(sensor)
{
    calibration = calibrationTable;
}

uint8_t FFSensor::begin()
{
    uint8_t status = mlx.begin();
    status |= mlx.writeRegister(0x00, 0x005c);
    status |= mlx.writeRegister(0x02, 0x02b4);
    // status |= mlx.setTrigCommWocExtTcmpBurst(false, 0x00, false, false, true, 0b1111, 0x00);

    status |= mlx.requestMeasurement(FFS_MLX::X | FFS_MLX::Y | FFS_MLX::Z);
    int16_t data[3];
    delay(20);
    status |= mlx.readMeasurement(FFS_MLX::X | FFS_MLX::Y | FFS_MLX::Z, data);

    offsetX = data[0];
    offsetY = data[1];
    offsetZ = data[2];

    return status;
}

uint8_t FFSensor::begin(uint32_t intro_delay, uint16_t count)
{
    delay(intro_delay);
    uint8_t status = mlx.begin();
    status |= mlx.writeRegister(0x00, 0x005c);
    status |= mlx.writeRegister(0x02, 0x02b4);
    int16_t data[3];
    float totalX = 0;
    float totalY = 0;
    float totalZ = 0;
    for (uint16_t u; u < count; u++)
    {
        mlx.requestMeasurement(FFS_MLX::X | FFS_MLX::Y | FFS_MLX::Z);
        delay(20);
        mlx.readMeasurement(FFS_MLX::X | FFS_MLX::Y | FFS_MLX::Z, data);
        totalX += data[0];
        totalY += data[1];
        totalZ += data[2];
    }
    offsetX = totalX / count;
    offsetY = totalY / count;
    offsetZ = totalZ / count;
    return status;
}

uint8_t FFSensor::requestMeasurement()
{
    return mlx.requestMeasurement(FFS_MLX::X + FFS_MLX::Y + FFS_MLX::Z);
}

uint8_t FFSensor::readMeasurement()
{
    int16_t data[3];
    uint8_t status = mlx.readMeasurement(FFS_MLX::X + FFS_MLX::Y + FFS_MLX::Z, data);
    if (status & FFS_MLX::ERROR_BIT)
    {
        return status;
    }
    data[0] -= offsetX;
    data[1] -= offsetY;
    data[2] -= offsetZ;
    if (!(data[0] == 0 && data[1] == 0))
    {
        float radial = approximate(data[0], data[1], data[2], calibration);
        float magnitude = sqrt(float(data[0]) * float(data[0]) + float(data[1]) * float(data[1]));
        forceX = float(data[0]) / magnitude * radial;
        forceY = float(data[1]) / magnitude * radial;
    }
    forceZ = approximate(data[0], data[1], data[2], calibration + 10);
    return status;
}

uint8_t FFSensor::requestAndReadMeasurement()
{
    requestMeasurement();
    delay(10);
    return readMeasurement();
}

uint8_t FFSensor::requestAndReadMeasurement(const uint64_t &time)
{
    requestMeasurement();
    delay(time);
    return readMeasurement();
}

float FFSensor::x()
{
    return forceX;
}

float FFSensor::y()
{
    return forceY;
}

float FFSensor::z()
{
    return forceZ;
}

float FFSensor::approximate(const float &x, const float &y, const float &z, const float *c)
{
    float r = sqrt(x * x + y * y);
    return pgm_read_float(c) +
           pgm_read_float(c + 1) * r +
           pgm_read_float(c + 2) * z +
           pgm_read_float(c + 3) * r * r +
           pgm_read_float(c + 4) * r * z +
           pgm_read_float(c + 5) * z * z +
           pgm_read_float(c + 6) * r * r * r +
           pgm_read_float(c + 7) * z * r * r +
           pgm_read_float(c + 8) * z * z * r +
           pgm_read_float(c + 9) * z * z * z;
}
