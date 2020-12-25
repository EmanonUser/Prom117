# Prom117

Prom117 is an NodeMCU arduino-like sketch, the goal is to export Texas Instrument's TMP117 digital temperature sensor data into Prometheus a time series database

Hardware Used :

  - NodeMCUv2 (ESP12-E)
  - Texas Instrument TMP117 high-accuracy, low-power, i2C digital temperature sensor

Software Used :
    
  - [**PlatformIO CLI**]
  - [**SparkFun_TMP117**] library
  - [**ESPAsyncWebServer**]: library
  - [**Prometheus TSDB**]
  

[**PlatformIO CLI**]: <https://platformio.org/>
[**SparkFun_TMP117**]: <https://github.com/sparkfun/SparkFun_TMP117_Arduino_Library>
[**ESPAsyncWebServer**]: <https://github.com/me-no-dev/ESPAsyncWebServer>
[**Prometheus TSDB**]: <https://prometheus.io/>
