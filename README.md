# 🏠 Bethel324-control-system
벧엘관 324호 사는 두 남자👨🏻‍💻👨🏻‍💻의 웹 기반 제어 시스템 구현
    <br/>
## Introduction
저희는 한동대학교 벧엘관 324호에 살고 있습니다. 저희 기숙사는 11시마다 점호를 하는데 이때 직접 소등해야 합니다. 저희는 '더 편하게 소등을 할 수 없을까?'라고 생각했고 마침 임베디드 수업을 같이 듣고 있었기 때문에 파이널 프로젝트로 **🏠 Bethel324-control-system**을 구현하기로 했습니다.
    <br/>
## System overview
업로드 예정
    <br/>
## Features✨
로컬 네트워크 상에서 웹 브라우저를 통해 아래와 같은 기능들을 수행할 수 있습니다.
1. 💡 LED 상태 (on/off) 확인 및 제어
2. 💦 가습기 상태 (on/off) 확인 및 제어
3. 🚪 문 잠김 상태 (lock/ unlock) 확인 및 제어
4. 💧 습도 (0~100%)확인
    <br/>
## Hardware⚙️ 
1. MODBUS-RTU-Client🤖
    1. [MODBUS RTU RELAY](https://www.waveshare.com/modbus-rtu-relay.htm)
    2. [STM32 Nucleo-64 board](https://www.st.com/resource/en/user_manual/dm00105823-stm32-nucleo64-boards-mb1136-stmicroelectronics.pdf)
    3. [ESP-01](https://www.microchip.ua/wireless/esp01.pdf)
    <br/>
2. MODBUS-TCP-Client🤖
   1. [TCPPORT-40M](http://comfilewiki.co.kr/ko/doku.php?id=tcpport:index)
   2. [DMS-MG90](https://components101.com/motors/mg90s-metal-gear-servo-motor)
   3. [STM32 Nucleo-64 board](https://www.st.com/resource/en/user_manual/dm00105823-stm32-nucleo64-boards-mb1136-stmicroelectronics.pdf)
   4. [ESP-01](https://www.microchip.ua/wireless/esp01.pdf)
   5. [HTU21D](https://cdn-shop.adafruit.com/datasheets/1899_HTU21D.pdf)
    <br/>
3. Web server🤖
   1. [Raspberry Pi4 Model B](https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2711/rpi_DATA_2711_1p0_preliminary.pdf)
    <br/>
## Team composition👨🏻‍💻🧑🏻‍💻
- 채영민 : BE, HW 환경 설정 및 구성 등 [@dudals5018](https://github.com/dudals5018)
- 김석진 : FE, MODBUS-RTU-Client, MODBUS-TCP-Client 등[@SukJinKim](https://github.com/SukJinKim)
    <br/>
## Youtube
[한동대학교 21-1학기 임베디드 파이널 프로젝트 : Bethel324 control system 시현 영상](https://www.youtube.com/watch?v=UDMhM5lJeyQ)