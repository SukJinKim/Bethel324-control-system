#include "mbed.h"

#define SERVER_IP "SERVER_IP"
#define SERVER_PORT server_port
#define SERVER_RES_SIZE 153

UnbufferedSerial modbus(PC_6, PC_7, 9600);
DigitalOut enable(ARDUINO_UNO_D4);

UnbufferedSerial pc(CONSOLE_TX, CONSOLE_RX, 115200);

WiFiInterface *wifi;
TCPSocket socket;

char txBuf_pc[1024];
char txBuf_server[] = "GET /status HTTP/1.1\r\n\r\n";
char rxBuf_server[1024];

char LED_on[] = {0x01, 0x05, 0x00, 0x00, 0xFF, 0x00, 0x8C, 0x3A};
char LED_off[] = {0x01, 0x05, 0x00, 0x00, 0x00, 0x00, 0xCD, 0xCA};
char HUM_on[] = {0x01, 0x05, 0x00, 0x01, 0xFF, 0x00, 0xDD, 0xFA};
char HUM_off[] = {0x01, 0x05, 0x00, 0x01, 0x00, 0x00, 0x9C, 0x0A};

int main()
{
    SocketAddress sockAddr;
    SocketAddress serverAddr(SERVER_IP, SERVER_PORT);
    nsapi_error_t err;
    char last_command = 0xff;

    /* Connect to wifi */
    wifi = WiFiInterface::get_default_instance();
    if (!wifi)
    {
        sprintf(txBuf_pc, "ERROR: No WiFiInterface found.\r\n");
        pc.write(txBuf_pc, strlen(txBuf_pc));
        while (1)
        {
        };
    }

    sprintf(txBuf_pc, "Connecting to %s...\r\n", MBED_CONF_APP_WIFI_SSID);
    pc.write(txBuf_pc, strlen(txBuf_pc));

    err = wifi->connect(MBED_CONF_APP_WIFI_SSID,
                        MBED_CONF_APP_WIFI_PASSWORD, NSAPI_SECURITY_WPA_WPA2);

    if (err != NSAPI_ERROR_OK)
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

    enable = 1;
    while (true)
    {
        //  Open a TCP socket on the network interface
        socket.open(wifi);

        err = socket.connect(serverAddr);
        if (err != NSAPI_ERROR_OK)
        {
            sprintf(txBuf_pc, "Error connecting : %d\r\n", err);
            pc.write(txBuf_pc, strlen(txBuf_pc));
            socket.close();
            return -1;
        }

        // send GET message to server
        socket.send((const char *)txBuf_server, strlen(txBuf_server));
        sprintf(txBuf_pc, "Send : %s\r\n", txBuf_server);
        pc.write(txBuf_pc, strlen(txBuf_pc));

        // recv from the server
        nsapi_size_or_error_t size = socket.recv(rxBuf_server, 1024);

        if (size <= 0)
        {
            if (size == NSAPI_ERROR_WOULD_BLOCK)
                continue;

            sprintf(txBuf_pc, "Error while receiving data from TCP socket(%d)\r\n", size);
            pc.write(txBuf_pc, strlen(txBuf_pc));
            return -1;
        }
        rxBuf_server[size] = '\0';

        sprintf(txBuf_pc, "\r\nRX data : (%d)%s\r\n", size, rxBuf_server);
        pc.write(txBuf_pc, strlen(txBuf_pc));

        // close socket
        socket.close();

        // trouble-shooting
        if (size < SERVER_RES_SIZE)
        {
            ThisThread::sleep_for(chrono::seconds(2));
            continue;
        }

        // parse the command
        char command = rxBuf_server[size - 1] - '0';
        sprintf(txBuf_pc, "command : %c\r\n", command);
        pc.write(txBuf_pc, strlen(txBuf_pc));

        if (last_command != command)
        {

            if (command & 0x02)
                modbus.write(LED_on, 8);
            else
                modbus.write(LED_off, 8);

            ThisThread::sleep_for(chrono::milliseconds(100));

            if (command & 0x01)
                modbus.write(HUM_on, 8);
            else
                modbus.write(HUM_off, 8);
        }
        last_command = command;

        ThisThread::sleep_for(chrono::seconds(2));
    }
}