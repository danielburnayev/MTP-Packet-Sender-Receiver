Before trying to run the code below, execute the two commands below in your command line to compile all of the provided code.

gcc mtpsender.c mtppacket.c -o mtpsender
gcc mtpreceiver.c mtppacket.c -o mtpreceiver

Once compiled, one will have to run the mtpreceiver first as that will give the sender a server to send their data to. mtpreceiver follows the format below:
./mtpreceiver <receiver-port> <output-file> <receiver-log-file>

After that, the mtpsender can be run, which follows the format below:
./mtpsender <receiver-IP> <receiver-port> <window-size>	<input-file> <sender-log-file>

