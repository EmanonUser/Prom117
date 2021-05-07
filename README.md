# Prom117

Prom117 is an Prometheus exporter for the Texas Instrument's TMP117 digital temperature sensor\
The software is written for the NodeMCUv2 based on a ESP12-E Espressif Microcontroler

Hardware Used :

  - [**NodeMCUv2**]
  - [**Sparkfun Texas Instrument TMP117 high-accuracy, low-power, i2C digital temperature sensor**]

Software Used :
    
  - [**PlatformIO CLI**]
  - [**SparkFun_TMP117**] library
  - [**ESPAsyncWebServer**] library
  - [**Prometheus TSDB**]
 
Exported Metrics: https://github.com/MoEmanon/Prom117/blob/master/pictures/exporter.png \
Schematic: https://github.com/MoEmanon/Prom117/blob/master/pictures/Sparkfun_TMP117_ESP12-E.png
  
## Usage
### Compile the sketch and flash it using platformio
First Install [**PlatformIO**] and git on your platformPlatformIO will take care of all the dependency for you

Debian/Ubuntu
```sh
$ sudo apt install git 
$ git clone https://github.com/EmanonUser/Prom117.git
$ cd Prom117/
```

Modify you WiFi logins in Prom117/lib/Secret/Secret.h

```sh
$ vim lib/Secret/Secret.h
```

If you use VScode download the PlatformIO extension, from there you will be able to compile the sketch and flash it on the NodeMCU\
Or you can do it in cli 

```sh
$ platformio run -e my_nodemcuv2 --target upload
```
Done !\
Access the metrics : http://NodeMCU_IP:9100/metrics

Monitor the serial output on your pc
```sh
$ platformio device monitor
```

[**NodeMCUv2**]: <https://www.nodemcu.com/index_en.html>
[**Sparkfun Texas Instrument TMP117 high-accuracy, low-power, i2C digital temperature sensor**]:<https://www.sparkfun.com/products/15805>
[**PlatformIO CLI**]: <https://platformio.org/>
[**PlatformIO**]: <https://docs.platformio.org/en/latest/core/installation.html>
[**SparkFun_TMP117**]: <https://github.com/sparkfun/SparkFun_TMP117_Arduino_Library>
[**ESPAsyncWebServer**]: <https://github.com/me-no-dev/ESPAsyncWebServer>
[**Prometheus TSDB**]: <https://prometheus.io/>
