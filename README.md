# ShineAndRise
A networked light switch, giving a user control over their home's lighitng with an Android applicaiton <br />
ShineRise: Folder containing the Android application <br />
The application forms a TCP connection on port 3490. The server's IP address is hard coded as my PI's IP address.  <br />
Screen shot of ShineAndRise UI.
![Alt text](https://github.com/colinsheppard10/ShineAndRise/blob/master/Images/UserInterface.png "Optional title")

TCPSelectServer: cpp code to impliment the server <br />
To run the server without connecting to MySQL database comment out the "access_database()" function calls. <br />
The server implements the Select() function to monitor multiple file descriptors without blocking.<br />
MySQLManager: cpp code to form connection to the server's database. <br />
Here is a diagram of the connections between: Android app, the server, and the light's wifi module <br />
![Alt text](https://github.com/colinsheppard10/ShineAndRise/blob/master/Images/Network.png "Optional title")
