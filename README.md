# ๐  Bethel324-control-system
๋ฒง์๊ด 324ํธ ์ฌ๋ ๋ ๋จ์๐จ๐ปโ๐ป๐จ๐ปโ๐ป์ ์น ๊ธฐ๋ฐ ์ ์ด ์์คํ ๊ตฌํ
    <br/>
## Introduction ๐ฅ
์ ํฌ๋ ๋ฒง์๊ด 324ํธ์ ์ด๊ณ  ์์ต๋๋ค. ๊ธฐ์์ฌ ์ํ์๋ ๊ณ ์ ์ ์ผ๋ก ๋ฐ๋ณต๋๋ ๋ช ๊ฐ์ง ์ผ๋ค์ด ์๊ณ , ์ด๋ฌํ ์ผ๋ค์ด ์ ํฌ๋ฅผ ํผ๊ณคํ๊ฒ ๋ง๋ญ๋๋ค. ๋ฐฉ์ ๋น์ธ ๋๋ ๋ฐฉ๋ฌธ์ ์ ๊ทธ๊ณ , ๋ฐค 11์๊ฐ ๋๋ฉด ์๋ฑํ๊ณ , ์๊ธฐ ์ ์ ํธ์ํ ์ ์ ์ํด ๊ฐ์ต๊ธฐ๋ฅผ ํ๋๋ค. ์ด๋ฌํ ์ผ๋ค์ ์๋์ผ๋ก ํน์ ์ค๋งํธํฐ ํฐ์น ํ๋๋ก ํ  ์ ์๋ค๋ฉด ์ผ๋ง๋ ํธํ ์ง ๊ธฐ๋ํ๋ ๋ง์์ผ๋ก **๐  Bethel324-control-system**์ ๊ตฌํํ๊ธฐ๋ก ํ์ต๋๋ค.
    <br/>
## System overview ๐ฎ
![system-overview](system-overview.jpeg)
    <br/>
## Features โจ
๋ก์ปฌ ๋คํธ์ํฌ ์์์ ์น ๋ธ๋ผ์ฐ์ ๋ฅผ ํตํด ์๋์ ๊ฐ์ ๊ธฐ๋ฅ๋ค์ ์ํํ  ์ ์์ต๋๋ค.
1. ๐ก LED ์ํ (on/off) ํ์ธ ๋ฐ ์ ์ด
2. ๐ฆ ๊ฐ์ต๊ธฐ ์ํ (on/off) ํ์ธ ๋ฐ ์ ์ด
3. ๐ช ๋ฌธ ์ ๊น ์ํ (lock/ unlock) ํ์ธ ๋ฐ ์ ์ด
4. ๐ง ์ต๋ (0~100%)ํ์ธ
   <br/>
## SW configuration ๐ป
1. Modbus-RTU-Client
   - mbed-os-6.11.0
    <br/>
2. Modbus-TCP-Client
   - mbed-os-6.11.0
    <br/>
3. Web server
   - Linux raspberrypi 5.4.72-v7l+
   - Flask 1.0.2
   - Python 3.7.3
    <br/>
## HW configuration โ๏ธ
1. MODBUS-RTU-Client ๐ค
    1. [MODBUS RTU RELAY](https://www.waveshare.com/modbus-rtu-relay.htm)
    2. [MAX485 Module](http://www.openimpulse.com/blog/wp-content/uploads/wpsc/downloadables/MAX485-Datasheet.pdf)
    3. [STM32 Nucleo-64 board](https://www.st.com/resource/en/user_manual/dm00105823-stm32-nucleo64-boards-mb1136-stmicroelectronics.pdf)
    4. [ESP-01](https://www.microchip.ua/wireless/esp01.pdf)
    <br/>
2. MODBUS-TCP-Client ๐ค
   1. [TCPPORT-30M](http://comfilewiki.co.kr/ko/doku.php?id=tcpport:index)
   2. [DMS-MG90](https://components101.com/motors/mg90s-metal-gear-servo-motor)
   3. [STM32 Nucleo-64 board](https://www.st.com/resource/en/user_manual/dm00105823-stm32-nucleo64-boards-mb1136-stmicroelectronics.pdf)
   4. [ESP-01](https://www.microchip.ua/wireless/esp01.pdf)
   5. [HTU21D](https://cdn-shop.adafruit.com/datasheets/1899_HTU21D.pdf)
    <br/>
3. Web server ๐ค
   1. [Raspberry Pi4 Model B](https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2711/rpi_DATA_2711_1p0_preliminary.pdf)
    <br/>
## Team composition ๐จ๐ปโ๐ป๐ง๐ปโ๐ป
- ์ฑ์๋ฏผ : BE, HW ํ๊ฒฝ ์ค์  ๋ฐ ๊ตฌ์ฑ ๋ฑ [@dudals5018](https://github.com/dudals5018)
- ๊น์์ง : FE, MODBUS-RTU-Client, MODBUS-TCP-Client ๋ฑ[@SukJinKim](https://github.com/SukJinKim)
  <br/>
## Links ๐
Youtube : [ํ๋๋ํ๊ต 21-1ํ๊ธฐ ์๋ฒ ๋๋ ํ์ด๋ ํ๋ก์ ํธ : Bethel324 control system ์ํ ์์](https://www.youtube.com/watch?v=UDMhM5lJeyQ)
<br/>
Blog : [๐ Bethel324-control-system์ ๋ํ์ฌ](https://alinew.tistory.com/92), [๐ Bethel324-control-system์ ๊ตฌํํ๋ฉด์ ๋ฐฐ์ฐ๊ณ  ์ฑ์ฅํ ์ ๋ค](https://alinew.tistory.com/93)