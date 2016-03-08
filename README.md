# ShineAndRise
ShineRise: folder containing the Android application <br />
![Alt text](https://github.com/colinsheppard10/ShineAndRise/blob/master/Images/UserInterface.png "Optional title")

The application forms a TCP connection on port 3490. The server's IP address is hard coded for my PI's LAN IP address.  <br />
Here are screenshots of the apps UI. 
TCPSelectServer: cpp code to impliment the server. To run the server without connecting to MySQL database comment out the "access_database()" function calls <br />
The server implements the Select() function to monitor multiple file descriptors without blocking.<br />
