/**
 *  HTU21D
 *  @author Seokjin Kim
 *  @date 2021/05/16
 *
 *  @section INFORMATION
 *
 *  Datasheet :
 *  https://cdn-shop.adafruit.com/datasheets/1899_HTU21D.pdf
 *
 *  @section EXAMPLE
 *  @code
 *
 *  #include "mbed.h"
 *  #include "HTU21D.h"
 *
 *  #define MAX_BUFFER_SIZE 256
 *
 *  HTU21D htu21d(ARDUINO_UNO_D14, ARDUINO_UNO_D15);
 *  BufferedSerial pc(CONSOLE_TX, CONSOLE_RX, 115200);
 *
 *  char buffer[MAX_BUFFER_SIZE];
 *
 *  void error_handler(char *buffer, char *message);
 *
 *  int main()
 *  {
 *   float temp, humi;
 *
 *   sprintf(buffer, "\r\nHTU21D Library Example\r\n");
 *   pc.write(buffer, strlen(buffer));
 *
 *   while(true) {
 *       if((temp = htu21d.read_temp()) == -1) {
 *           error_handler(buffer, "ERROR OCCURED WHILE READING TEMPERATURE\r\n");
 *           continue;
 *       } else if(htu21d.crc_check()) {
 *           error_handler(buffer, "CRC ERROR OCCURED WHILE READING TEMPERATURE\r\n");
 *           continue;
 *       }
 *
 *       sprintf(buffer, "Temperature = %.2f [C]\r\n", htu21d.read_temp());
 *       pc.write(buffer, strlen(buffer));
 *
 *       if((humi = htu21d.read_humi()) == -1) {
 *           error_handler(buffer, "ERROR OCCURED WHILE READING HUMIDITY\r\n");
 *           continue;
 *       } else if(htu21d.crc_check()) {
 *           error_handler(buffer, "CRC ERROR OCCURED WHILE READING HUMIDITY\r\n");
 *           continue;
 *       }
 *
 *       sprintf(buffer, "Relative Humidity = %.2f [%%]\r\n", htu21d.read_humi());
 *       pc.write(buffer, strlen(buffer));
 *
 *       ThisThread::sleep_for(chrono::seconds(3));
 *   }
 *  }
 *
 *  void error_handler(char *buffer, char *message)
 *  {
 *   sprintf(buffer, message);
 *   pc.write(buffer, strlen(buffer));
 *  }
 *
 *  @endcode
 */
#ifndef _HTU21D_H_
#define _HTU21D_H_

#include <mbed.h>

#define HTU21D_ADDR             (0x40)
#define HTU21D_POLYNOMIAL       (0x131)     // x^8 + x^5 + x^4 + 1
#define HTU21D_TEMP_DELAY       (50 * 1000) // 50 ms
#define HTU21D_HUMI_DELAY       (16 * 1000) // 16 ms

// commands
#define HTU21D_TEMP_READ        (0xF3) // no hold command
#define HTU21D_HUMI_READ        (0xF5) // no hold command
#define HTU21D_TEMP_READ_HOLD   (0xE3)
#define HTU21D_HUMI_READ_HOLD   (0xE5)
#define HTU21D_USER_WRITE       (0xE6)
#define HTU21D_USER_READ        (0xE7)
#define HTU21D_SOFT_RESET       (0xFE)

class HTU21D
{
public:
    /**
     * Constructor.
     *
     * @param SDA Pin for data transfer
     * @param SCL Pin for clock signal
     */
    explicit HTU21D(PinName SDA, PinName SCL);

    /**
     * Destructor
     */
    ~HTU21D();

    /**
     * read_temp (no hold)
     * @return temperature [C] on success, -1 on failure
     */
    float read_temp(void);

    /**
     * read_humi (no hold)
     * @return relative humidity [%] on success, -1 on failure
     */
    float read_humi(void);

    /**
     * crc check
     * @return 0 on success, 1 on failure
     */
    uint32_t crc_check(void);

private:

    I2C master;
    Timer _timer;

    char command[1];
    char data[3];       // [0 - 1] : data, [2] : checksum

    void wait_us(uint32_t delay);
};

#endif