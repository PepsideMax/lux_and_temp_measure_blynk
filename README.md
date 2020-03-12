# lux_and_temp_measure_blynk
my test for week 5 sensros and interfacing where we have to use blynk to diaspaly the amount of lux and the current temperature

as sensors I have used the BH1750 to measure the ligth ans the BMP280 to measure temperature. as controller i chose for the esp32 becous i just like it a lot and its easyer to connect to the internet becaus there is an includdes wifi module onboard.

these sensors all use I2C so the connection is almost selfexplanitory the scl of all the modules is connecten to pin D22 and the sda of all the modules is connected to the pin D21, the VCC to the 3.3V and the GND to the GND of the device. and for the BMP280 the leftover pins will have to be connected to 3.3V aswell.

