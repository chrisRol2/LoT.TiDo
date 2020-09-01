# esp8266-SerialOTA
Current version of ArduinoOTA for esp8266 does not allow to get serial messages when the modules is not connected physically.
The class SerialOTA accepts telnet connection (port 23) and broadcast any message to connected clients when the function serialOTA.println() is called.
Code is inspired bu the Seria2Telnet shetch from the example library.
So far function only println(const char*) is implemented - in future versions all println accepted by Serial should be replicated
A elegant way to replace Serial by SerialOTA and make the operation transparent to user is to be found: so far I use a #define to replace at compliation Serial by SerialOTA....maybe not that great ?

How to use it:
-replace proper ssiid and password in the script and upload the example
-open a telnet session (telnet open xx.xx.xx.xx) - you should receive "Hello!"


