/*
  UDP Echo client

  A simple UDP communication demo.
  The program send simple message to 'udp-echo-server-rpl' node,
  the server node send echo on the message received.
  The received echo message shows on serial port.

  Even if RPL is enabled or disabled works.
  Use same settings to compile server side programs.
  This programs behavior is based on contiki os's
  example(examples/udp-ipv6/udp-client.c).

  created 24 Jan 2016
  modified 29 May 2018
  by Tokita Hiroshi
*/

#include <NetworkInterface.h>
#include <UdpSocket.h>
#include <IPAddress.h>

const size_t MAX_PAYLOAD_LEN = 40;
const unsigned short LOCAL_PORT = 7;
const unsigned short DEST_PORT  = 7;
const int INTERVAL = 15;

UDPSocket Udp;
IPAddress server(0xfe80, 0, 0, 0, 0, 0, 0, 1); // Configure server manually.

String message;
char recvBuffer[MAX_PAYLOAD_LEN];
long lastsend;
uint16_t seq_id;

void setup() {
  Serial.begin(115200);
  Serial.println("Start udp-echo-cleint");
  NetIf.begin();

  Serial.print("Server is [");
  Serial.print(server);
  Serial.println("]");

  Serial.print("Client is [");
  Serial.print(NetIf.globalAddress());
  Serial.println("]");

  Udp.begin(LOCAL_PORT);
  Serial.print("Start listen port:");
  Serial.println(LOCAL_PORT);
}

void loop() {

  long now = millis();

  // Periodically send.
  if ((now - lastsend) > (INTERVAL * 1000)) {
    // format message
    message = "Hello ";
    message.concat(++seq_id);

    Serial.print("Send to [");
    Serial.print(server);
    Serial.print("]: '");
    Serial.print(message);
    Serial.println("'");

    // send packet
    Udp.beginPacket(server, DEST_PORT);
    Udp.write(message.c_str(), message.length() );
    Udp.endPacket();

    lastsend = now;
  }

  while (int packetSize = Udp.parsePacket()) {
    // read the packet into packetBufffer
    Udp.read(recvBuffer, packetSize);
    Serial.print("Response from [");
    Serial.print(Udp.remoteIP());
    Serial.print("]: '");
    Serial.print(recvBuffer);
    Serial.println("'");
  }

}
