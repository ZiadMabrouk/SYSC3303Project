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
    
private:
    int socket_fd;
    static const size_t MAXLINE=1024;
};
