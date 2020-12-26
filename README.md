# Prom117

Prom117 is an NodeMCU arduino-like sketch, the goal is to export Texas Instrument's TMP117 digital temperature sensor data into Prometheus a time series database

Hardware Used :

  - [**NodeMCUv2 (ESP12-E)**]
  - [**Sparkfun Texas Instrument TMP117 high-accuracy, low-power, i2C digital temperature sensor**]

Software Used :
    
  - [**PlatformIO CLI**]
  - [**SparkFun_TMP117**] library
  - [**ESPAsyncWebServer**] library
  - [**Prometheus TSDB**]
  

### Compile using platformio CLI
PlatformIO will take care of all the dependency for you

Install [**PlatformIO**] on your platform

Debian/Ubuntu
```sh
$ sudo apt install platformio
```


Compile then flash automatically via esptools
```sh
$ git clone https://github.com/MoEmanon/Prom117.git
$ cd Prom117/
```

Modify you WiFi logins in Prom117/lib/Secret/Secret.h

```sh
$ vim lib/Secret/Secret.h
$ platformio run -e my_nodemcuv2 --target upload
```
Done !

Serial monitoring
```sh
$ platformio device monitor
```


[**NodeMCUv2 (ESP12-E)**]: <https://www.nodemcu.com/index_en.html>
[**Sparkfun Texas Instrument TMP117 high-accuracy, low-power, i2C digital temperature sensor**]:<https://www.sparkfun.com/products/15805>

[**PlatformIO CLI**]: <https://platformio.org/>
[**PlatformIO**]: <https://platformio.org/>
[**SparkFun_TMP117**]: <https://github.com/sparkfun/SparkFun_TMP117_Arduino_Library>
[**ESPAsyncWebServer**]: <https://github.com/me-no-dev/ESPAsyncWebServer>
[**Prometheus TSDB**]: <https://prometheus.io/>
