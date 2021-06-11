/**
 *  HTU21D
 *  @author Seokjin Kim
 *  @date 2021/05/16
 *
 *  @section INFORMATION
 *
 *  Datasheet :
 *  https://cdn-shop.adafruit.com/datasheets/1899_HTU21D.pdf
 */
#include "HTU21D.h"

/**
 * Constructor.
 *
 * @param SDA Pin for data transfer
 * @param SCL Pin for clock signal
 */
HTU21D::HTU21D(PinName SDA, PinName SCL) : master(SDA, SCL)
{
    master.frequency(400 * 1000);       // 400KHz
}

/**
 * Destructor
 */
HTU21D::~HTU21D()
{
}

/**
 * read_temp (no hold)
 *
 * @return temperature [C] on success, -1 on failure
 */
float HTU21D::read_temp(void)
{
    command[0] = HTU21D_TEMP_READ;
    if(master.write((HTU21D_ADDR) << 1, command, 1))
        return -1.0;
    
    wait_us(HTU21D_TEMP_DELAY);
    
    if(master.read((HTU21D_ADDR) << 1, data, 3))
        return -1.0;
    
    uint32_t signal_temp = (data[0] << 8) | (data[1] >> 4);
    
    return -46.85 + 175.72 * (float(signal_temp) / pow(2.0, 16.0));
}

/**
 * read_humi (no hold)
 *
 * @return relative humidity [%] on success, -1 on failure
 */
float HTU21D::read_humi(void)
{
    command[0] = HTU21D_HUMI_READ;
    if(master.write((HTU21D_ADDR) << 1, command, 1))
        return -1.0;
    
    wait_us(HTU21D_HUMI_DELAY);
    
    if(master.read((HTU21D_ADDR) << 1, data, 3))
        return -1.0;
    
    uint32_t signal_humi = (data[0] << 8) | (data[1] >> 4);
    
    return -6 + 125 * (float(signal_humi) / pow(2.0, 16.0));
}

/**
 * crc_check
 * 
 * @return 0 on success, non-zero on failure
 */
uint32_t HTU21D::crc_check(void)
{
    uint32_t remainder = (data[0] << 16 | data[1] << 8 | data[2]);
    uint32_t divisor = (HTU21D_POLYNOMIAL << 23);
    
    for(uint32_t bit = 32; bit > 0; --bit)
    {
        if(remainder & 0x80000000)
        {
            remainder ^= divisor;
        }
        
        remainder = (remainder << 1);
    }
    
    return remainder;
}

/**
 * wait_us
 *
 * @param delay [us]
 */
void HTU21D::wait_us(uint32_t delay)
{
    _timer.reset();
    _timer.start();
    while(_timer.elapsed_time().count() < delay) {}
    _timer.stop();
    _timer.reset();
}