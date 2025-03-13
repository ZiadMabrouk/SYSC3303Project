#ifndef DATAGRAM_H
#define DATAGRAM_H

/* -*- c++-mode -*-
 * Helper classes modelled on the Java versions for interfacing to the internet.
 *
 * A work in progress.
 */

#include <vector>
#include <exception>
#include <cstring>
#include <sys/errno.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>
#include <unistd.h>
#include <stdexcept>
#include <iostream>

#include "ElevatorDataTypes.h"

class InetAddress
{
public:
    static in_addr_t getLocalHost() { return inet_addr( "127.0.0.1" ); }
};


class DatagramPacket {
public:
    DatagramPacket( std::vector<uint8_t>& data, size_t length, in_addr_t address=INADDR_ANY, in_port_t port=0 ) : _data(data) {
	_address.sin_family = AF_INET; 
	_address.sin_port = port;
	_address.sin_addr.s_addr = address;
	_length = std::min( data.size(), length );	// Take smaller value.
    }

    void * getData() const { return const_cast<void *>(static_cast<const void *>(_data.data())); }
    size_t getLength() const { return _length; }
    void setLength( size_t length ) { _length = std::min( length, _data.size() ); }
    in_addr_t getAddress() { return _address.sin_addr.s_addr; }
    in_port_t getPort() { return _address.sin_port; } 	// swap to host byte order.
    std::string getAddressAsString() const { return std::string( inet_ntoa( _address.sin_addr ) ); }

    struct sockaddr* address() { return reinterpret_cast<sockaddr*>(&_address); }
    std::vector<uint8_t>::const_iterator begin() const { return _data.begin(); }
    std::vector<uint8_t>::const_iterator end() const { return _data.end(); }

private:
    std::vector<uint8_t>& _data;	/* Don't copy data passed in constructor */
    size_t _length;
    struct sockaddr_in _address;
};

// Creating socket file descriptor
class DatagramSocket {
public:
    DatagramSocket() : socket_fd(socket(AF_INET, SOCK_DGRAM, 0)) {
	if ( socket_fd < 0 ) {
	    throw std::runtime_error( std::string("socket creation failed: ") + strerror(errno) );
	}
    }

    /*
     * Open a socket and bind to a specific port.  The socket is attached to all interfaces.
     */
    
    DatagramSocket(in_port_t port) : socket_fd(socket(AF_INET, SOCK_DGRAM, 0)) {
	if ( socket_fd < 0 ) {
	    throw std::runtime_error( std::string("socket creation failed: ") + strerror(errno) );
	}

	struct sockaddr_in address;
	memset(&address, 0, sizeof(address)); 
       
	address.sin_family = AF_INET; 
	address.sin_port = port; 
	address.sin_addr.s_addr = INADDR_ANY;		/* Bind to all local interfaces */

	if ( bind(socket_fd, (const struct sockaddr *)&address, sizeof(address) ) < 0 ) {
	    throw std::runtime_error( std::string("socket bind failed") + strerror(errno) );
	}
	
    }
    
    ~DatagramSocket() {
	close( socket_fd );
    }

    ssize_t send( DatagramPacket& packet ) {
	ssize_t sent = sendto( socket_fd, packet.getData(), packet.getLength(), 0, packet.address(), sizeof(*packet.address()) );
	if ( sent == -1 ) {
	    throw std::runtime_error( std::string("sendto failed: ") + strerror(errno) );
	}
	return sent;
    }
    
    void receive( DatagramPacket& packet ) {
	socklen_t len = sizeof(*packet.address());
	int received = recvfrom(socket_fd, packet.getData(), MAXLINE, MSG_WAITALL, packet.address(), &len);
	if ( received < 0 ) {
	    throw std::runtime_error( std::string("recvfrom failed: ") + strerror(errno) );
	}
	packet.setLength(received);
    }
	int socket_fd;
private:
    static const size_t MAXLINE=1024;
};

#define TIMEOUT_SEC 5
#define MAX_RETRIES 5

void inline send_and_wait_for_ack(std::string name, e_struct sendingData, int port, DatagramSocket &iReceiveSocket, DatagramSocket &iSendSocket) {
    std::vector<uint8_t> buffer(sizeof(e_struct));  // Create a buffer for the struct
    sendingData.serialize(buffer.data());


    DatagramPacket sendPacket(buffer, buffer.size(), InetAddress::getLocalHost(), port);

    fd_set readfds;
    struct timeval timeout; // Structure to store timeout duration

    std::vector<uint8_t> ackData(sizeof(e_struct));
    DatagramPacket ackPacket(ackData, ackData.size());

    int retries = 0;  // Counter for retry attempts

    while (retries < MAX_RETRIES) {
        try {
            // Send the message to the server
            std::cout << name << "Sending message to server..." << std::endl;
            iSendSocket.send(sendPacket);
        } catch (const std::runtime_error& e) {
            std::cerr << "Send failed: " << e.what() << std::endl;
            return exit(1); // Exit on send failure
        }
        retries++;
        // Clear and set file descriptor set
        FD_ZERO(&readfds);
        FD_SET(iSendSocket.socket_fd, &readfds);

        // Set timeout duration
        timeout.tv_sec = TIMEOUT_SEC;
        timeout.tv_usec = 0;
        std::cout << name << "Waiting for acknowledgment..." << std::endl;

        int activity = select(iSendSocket.socket_fd + 1, &readfds, NULL, NULL, &timeout);

        if (activity < 0) {
            // Error in select()
            std::cerr << "Error in select()" << std::endl;
            return exit(1);
        } else if (activity == 0) {
            // Timeout expired, no ACK received
            std::cout << name << ": Timeout! No acknowledgment received." << std::endl;
            continue; // Exit loop after timeout
        }

        break;
    }
}

e_struct inline wait_and_receive_with_ack(std::string name, DatagramSocket& iReceiveSocket, DatagramSocket& iSendSocket) {
    std::vector<uint8_t> data(sizeof(e_struct));
    DatagramPacket receivePacket(data, data.size());

    std::cout << name << ": Waiting for Packet." << std::endl;

    try {
        std::cout << "Waiting..." << std::endl;
        iReceiveSocket.receive(receivePacket);
    } catch (const std::runtime_error& e) {
        std::cerr << "IO Exception: Receive Socket Timed Out.\n" << e.what() << std::endl;
        exit(1);
    }

    std::cout << name << ": Packet received:\n";
    std::cout << "From host: " << receivePacket.getAddressAsString() << std::endl;
    std::cout << "Host port: " << receivePacket.getPort() << std::endl;

    // Deserialize received struct
    e_struct receivedData = e_struct::deserialize(data.data());

    /**
     *Here you can use receivedData.(value) to access a member of the e_struct passed)
     *
     **/
    //Uncomment if there are timing issues
    //std::this_thread::sleep_for(std::chrono::seconds());

    e_struct sendStruct = receivedData;
    sendStruct.acknowledged = true;
    sendStruct.serialize(data.data()); // compress the struct to bytes

    DatagramPacket sendPacket(data, receivePacket.getLength(),
                                  receivePacket.getAddress(), receivePacket.getPort());

    std::cout << name << "Sending acknowledgement back to client...\n";
    try {
        iSendSocket.send(sendPacket);  // Send response back to client
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }




    return receivedData;

}
#endif
