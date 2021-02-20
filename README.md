# FFSensor - Flexible Force Sensor library

## Usage
The `FFSensor` instance takes the `FFS_MLX` instance and calibration data pointer.

## `FFS_MLX`
The `FFS_MLX` instance may be either `FFS_MLX_SPI` or `FFX_MLX_I2C` for SPI or I2C respectively.
`FFS_MLX_SPI` takes the `EN` pin as constructor argument while `FFS_MLX_I2C` - I2C address of mlx (usually 0x3c).

## SPI example
```.arduino
#include <FFSensor.h>
#include <FFS_MLX_SPI.h>

#include "calibration.h"

#define FFS_ENABLE_PIN  10

FFS_MLX_SPI mlx(FFS_ENABLE_PIN);
FFSensor sensor(mlx, calibration);

void setup() {
  Serial.begin(9600);
  sensor.begin();
}

void loop() {
  sensor.requestAndReadMeasurement(10);
  float forceX = sensor.x();
  float forceY = sensor.y();
  float forceZ = sensor.z();
  Serial.print(forceX);
  Serial.print(",");
  Serial.print(forceY);
  Serial.print(",");
  Serial.println(forceZ);
}
```

## I2C example
```.arduino
#include <FFSensor.h>
#include <FFS_MLX_I2C.h>

#include "calibration.h"

FFS_MLX_I2C mlx(0x3c);
FFSensor sensor(mlx, calibration);

void setup() {
  Serial.begin(9600);
  sensor.begin();
}

void loop() {
  sensor.requestAndReadMeasurement(10);
  float forceX = sensor.x();
  float forceY = sensor.y();
  float forceZ = sensor.z();
  Serial.print(forceX);
  Serial.print(",");
  Serial.print(forceY);
  Serial.print(",");
  Serial.println(forceZ);
}
```

## `FFSensor` Workflow

The `FFSensor` instance requests measurements from MLX90393 and performs calculation after the measurement is done.
