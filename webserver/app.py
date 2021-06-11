
from flask import Flask, render_template
import socket

app = Flask(__name__)
led = False 
humidifier = False
humidity = 0
door = False


def modbus_send(cmd):
	modbus_sock = socket.socket()
	modbus_sock.settimeout(3)
	tcpport_ip = "TCPPORT_IP"
	tcpport_port = 502

	if modbus_sock.fileno() == -1:
		modbus_sock.close()
		return -1
	try:
		modbus_sock.connect((tcpport_ip, tcpport_port))
	except:
		modbus_sock.close()
		return -1

	modbus_sock.send(cmd)

	
	msg = modbus_sock.recv(1000)
	print(msg)
	modbus_sock.close()

	return msg	
	

def init():
	door_off = b"\x00\x00\x00\x00\x00\x06\x01\x06\x00\x04\x00\x02"

	modbus_send(door_off)
	

def toggle_door():
	door_on = b"\x00\x00\x00\x00\x00\x06\x01\x06\x00\x04\x00\x01"
	door_off = b"\x00\x00\x00\x00\x00\x06\x01\x06\x00\x04\x00\x02"


	global door
	door = not door
	if door:
		modbus_send(door_on)
	else:
		modbus_send(door_off)

def update_humidity():
	global humidity
	humidity_read = b"\x00\x00\x00\x00\x00\x06\x01\x01\x00\x10\x00\x07"
	response = modbus_send(humidity_read)
	if response is not -1:
		humidity = response[-1]	
	
	


@app.route('/')
def index():
	global led, humidifier, humidity, door
	return render_template('index.html', led= str(led), humidifier= str(humidifier), humidity=str(humidity), door= str(door))




@app.route('/status')
def status():
	global led, humidifier
	ret = 0
	if led:
		ret += 2 
	if humidifier:
		ret += 1 
	return str(ret)


@app.route('/door', methods=['GET'])
def door_url():
	global door
	toggle_door()
	if door:
		return "1"
	else:
		return "0"

@app.route('/led')
def led_url():
	global led
	led = not led
	if led:
		return "1"
	else:
		return "0"

@app.route('/humidity')
def humidity_url():
	global humidity
	update_humidity()
	return str(humidity)

@app.route('/humidifier')
def humidifier_url():
	global humidifier
	humidifier = not humidifier
	if humidifier:
		return "1"
	else:
		return "0"



if __name__ == '__main__':
	

	app.run(host = "0.0.0.0", port=5000, debug=True)
	 



