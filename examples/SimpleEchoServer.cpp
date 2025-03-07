// SimpleEchoServer.java
// This class is the server side of a simple echo server based on
// UDP/IP. The server receives from a client a packet containing a character
// string, then echoes the string back to the client.
// Last edited January 9th, 2016


#include <chrono>
#include <thread>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>
#include "Datagram.h"

#define PORT    5000
   
class SimpleEchoServer {
public:
    SimpleEchoServer() : sendSocket(), receiveSocket(PORT) {}

private:
    // Construct a datagram socket and bind it to any available 
    // port on the local host machine. This socket will be used to
    // send UDP Datagram packets.
    DatagramSocket sendSocket;

    // Construct a datagram socket and bind it to port 5000 
    // on the local host machine. This socket will be used to
    // receive UDP Datagram packets.
    DatagramSocket receiveSocket;

public:
    void receiveAndEcho() {
	// Construct a DatagramPacket for receiving packets up 
	// to 100 bytes long (the length of the byte array).
	
	std::vector<uint8_t> data(100);
	DatagramPacket receivePacket(data, data.size());
	std::cout << "Server: Waiting for Packet." << std::endl;

	// Block until a datagram packet is received from receiveSocket.
	try {        
	    std::cout << "Waiting..." << std::endl; // so we know we're waiting
	    receiveSocket.receive(receivePacket);
	} catch (const std::runtime_error& e ) {
	    std::cout << "IO Exception: likely:"
		      << "Receive Socket Timed Out." << std::endl << e.what() << std::endl;
	    exit(1);
	}

	// Process the received datagram.
	std::cout << "Server: Packet received:" << std::endl;
	std::cout << "From host: " << receivePacket.getAddressAsString() << std::endl;
	std::cout << "Host port: " << receivePacket.getPort() << std::endl;
	int len = receivePacket.getLength();
	std::cout << "Length: " << len << std::endl
		  << "Containing: ";

	// Form a String from the byte array.
	std::string received = std::string( static_cast<const char *>(receivePacket.getData()), receivePacket.getLength() );
	std::cout << received << std::endl;
      
	// Slow things down (wait 5 seconds)
	std::this_thread::sleep_for( std::chrono::seconds( 5 ) );
 
	// Create a new datagram packet containing the string received from the client.

	// Construct a datagram packet that is to be sent to a specified port 
	// on a specified host.
	// The arguments are:
	//  data - the packet data (a byte array). This is the packet data
	//         that was received from the client.
	//  receivePacket.getLength() - the length of the packet data.
	//    Since we are echoing the received packet, this is the length 
	//    of the received packet's data. 
	//    This value is <= data.length (the length of the byte array).
	//  receivePacket.getAddress() - the Internet address of the 
	//     destination host. Since we want to send a packet back to the 
	//     client, we extract the address of the machine where the
	//     client is running from the datagram that was sent to us by 
	//     the client.
	//  receivePacket.getPort() - the destination port number on the 
	//     destination host where the client is running. The client
	//     sends and receives datagrams through the same socket/port,
	//     so we extract the port that the client used to send us the
	//     datagram, and use that as the destination port for the echoed
	//     packet.

	DatagramPacket sendPacket(data, receivePacket.getLength(),
				  receivePacket.getAddress(), receivePacket.getPort());

	std::cout <<  "Server: Sending packet:" << std::endl;
	std::cout << "To host: " << sendPacket.getAddressAsString() << std::endl;
	std::cout << "Destination host port: " << sendPacket.getPort() << std::endl;
	len = sendPacket.getLength();
	std::cout << "Length: " << len << std::endl
		  << "Containing: " << std::endl;
	std::cout << std::string(static_cast<const char *>(sendPacket.getData()), len) << std::endl; // 
	// or (as we should be sending back the same thing)
	// System.out.println(received); 
        
	// Send the datagram packet to the client via the send socket. 
	try {
	    sendSocket.send(sendPacket);
	} catch ( const std::runtime_error& e ) {
	    std::cerr << e.what() << std::endl;
	    exit(1);
	}

	std::cout << "Server: packet sent" << std::endl;

      // We're finished, so close the sockets.
      // Sockets will close with RAII
//      sendSocket.close();
//      receiveSocket.close();
      return;
   }
};
 

int main(int argc, char ** argv)
{
    SimpleEchoServer().receiveAndEcho();
}
