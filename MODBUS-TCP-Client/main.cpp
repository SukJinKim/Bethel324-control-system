#include "mbed.h"
#include "HTU21D.h"

// IP and PORT# of MODBUS TCPPORT-30M
#define SERVER_IP "MODBUS_TCPPORT_30M_IP"
#define SERVER_PORT modbus_tcpport_30m_port
#define MAX_BUF_SIZE 1024

HTU21D htu21d(ARDUINO_UNO_D14, ARDUINO_UNO_D15);
UnbufferedSerial pc(CONSOLE_TX, CONSOLE_RX, 115200);

WiFiInterface *wifi;
TCPSocket socket;

char txBuf_pc[MAX_BUF_SIZE];
char txBuf_server[MAX_BUF_SIZE];
char rxBuf_server[MAX_BUF_SIZE];

char write_humi[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x01, 0x0F, 0x00, 0x10, 0x00, 0x08, 0x01, 0x00};
             
int main()
{
    SocketAddress sockAddr;
    SocketAddress serverAddr(SERVER_IP, SERVER_PORT);
    nsapi_error_t err;
    
    float humi;
    int i_humi, len;
    
    /* Connect to wifi */
    wifi = WiFiInterface::get_default_instance();
    if(!wifi)
    {
        sprintf(txBuf_pc, "ERROR: No WiFiInterface found.\r\n");
        pc.write(txBuf_pc, strlen(txBuf_pc));
        while(1){};
    }
    
    sprintf(txBuf_pc, "Connecting to %s...\r\n", MBED_CONF_APP_WIFI_SSID);
    pc.write(txBuf_pc, strlen(txBuf_pc));

    err = wifi->connect(MBED_CONF_APP_WIFI_SSID,
                        MBED_CONF_APP_WIFI_PASSWORD, NSAPI_SECURITY_WPA_WPA2);
                            
    if(err != NSAPI_ERROR_OK)
    {
        sprintf(txBuf_pc, "Connection error!!\r\n");
        pc.write(txBuf_pc, strlen(txBuf_pc));
        return -1;
    }
    
    sprintf(txBuf_pc, "Success!!\r\n");
    pc.write(txBuf_pc, strlen(txBuf_pc));
    
    wifi->get_ip_address(&sockAddr);
    sprintf(txBuf_pc, "IP : %s\r\n", sockAddr.get_ip_address());
    pc.write(txBuf_pc, strlen(txBuf_pc));
    
    socket.set_timeout(10 *1000);   // Time out : 10s
    while(true)
    {
        //  Open a TCP socket on the network interface
        socket.open(wifi);
        
        err = socket.connect(serverAddr);
        if(err != NSAPI_ERROR_OK)
        {
            sprintf(txBuf_pc, "Error connecting : %d\r\n", err);
            pc.write(txBuf_pc, strlen(txBuf_pc));
            
            socket.close();
            ThisThread::sleep_for(chrono::seconds(2));
            continue;
        }
        
        // read humidity
        if((humi = htu21d.read_humi()) == -1) 
        {
            sprintf(txBuf_pc, "ERROR OCCURED WHILE READING HUMIDITY\r\n");
            pc.write(txBuf_pc, strlen(txBuf_pc));
            
            socket.close();
            ThisThread::sleep_for(chrono::seconds(2));
            continue;
        } 
        else if(htu21d.crc_check()) 
        {
            sprintf(txBuf_pc, "CRC ERROR OCCURED WHILE READING HUMIDITY\r\n");
            pc.write(txBuf_pc, strlen(txBuf_pc));
            
            socket.close();
            ThisThread::sleep_for(chrono::seconds(2));
            continue;
        }
        
        i_humi = (int) humi;
        sprintf(txBuf_pc, "Relative Humidity = %d [%%]\r\n", i_humi);
        pc.write(txBuf_pc, strlen(txBuf_pc));
        
        // send write_humi
        len = sizeof(write_humi)/sizeof(write_humi[0]);
        write_humi[len - 1] = (i_humi & 0xff);
        
        socket.send((const char*)write_humi, 14);
        sprintf(txBuf_pc, "Send : %d %d %d %d %d %d %d %d %d %d %d %d %d %d\r\n"
                        , write_humi[0], write_humi[1], write_humi[2], write_humi[3]
                        , write_humi[4], write_humi[5], write_humi[6], write_humi[7]
                        , write_humi[8], write_humi[9], write_humi[10], write_humi[11]
                        , write_humi[12], write_humi[13]);
        pc.write(txBuf_pc, strlen(txBuf_pc));
        
        // recv from the server
        nsapi_size_or_error_t size = socket.recv(rxBuf_server, 1024);
        
        if(size <= 0)
        {   
            if(size == NSAPI_ERROR_WOULD_BLOCK) 
            {
                socket.close();
                ThisThread::sleep_for(chrono::seconds(2));
                continue;
            }
            
            sprintf(txBuf_pc, "Error while receiving data from TCP socket(%d)\r\n", size);
            pc.write(txBuf_pc, strlen(txBuf_pc));
            
            socket.close();
            ThisThread::sleep_for(chrono::seconds(2));
            continue;
        }
        rxBuf_server[size] = '\0';
        
        sprintf(txBuf_pc, "Recv : %d %d %d %d %d %d %d %d %d %d %d %d\r\n"
                        , rxBuf_server[0], rxBuf_server[1], rxBuf_server[2], rxBuf_server[3]
                        , rxBuf_server[4], rxBuf_server[5], rxBuf_server[6], rxBuf_server[7]
                        , rxBuf_server[8], rxBuf_server[9], rxBuf_server[10], rxBuf_server[11]
                        );
         pc.write(txBuf_pc, strlen(txBuf_pc));
        
        // close socket
        socket.close();
        
        ThisThread::sleep_for(chrono::seconds(10));
    }
    
    wifi->disconnect();
    
    while(true){};
}