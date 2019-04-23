#include <OpenThread.h>

class StringPrinter : public Print, public String
{
public:
  size_t write(uint8_t b) { return concat(static_cast<char>(b)); }
  using Print::write;
};

void setup() {
  OpenThread.begin();

  Serial.begin(115200);
  delay(3000);

  Serial.println("joiner_start");

  otError err = OpenThread.joiner_start("J01NME");

  Serial.println("end joiner_start");
  if(err) {
    Serial.println(OpenThread.otErrorToString(err));
  }

}

void loop() {
  delay(10000);
  OpenThread.dump(Serial);
  
  otActiveScanResult scantable[3] = {0};
  Serial.println("start discover");
  OpenThread.discover(scantable, 3);
  Serial.println("discover complete");
  for(int i=0; i<3; i++) {
    if(scantable[i].mChannel) {
      Serial.println();
      
      Serial.print("Found ");
      StringPrinter netname;
      netname.print(OTNetworkName(&scantable[i].mNetworkName));
      Serial.print(netname);
      Serial.print(" Ch:");
      Serial.print(scantable[i].mChannel); 
      Serial.print(" PanId:");
      Serial.print(scantable[i].mPanId, HEX); 
      Serial.print(" ExtPanId:");
      Serial.print( OTExtendedPanId(&scantable[i].mExtendedPanId) );
      
      Serial.println();
    }
  }

}
