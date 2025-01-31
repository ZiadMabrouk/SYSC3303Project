/**
 * The basic Box class to show mutual exclusion and 
 * condition synchronization using Resource Acquisition
 * Is Initialization (RAII) idiom.
 * 
 * @author Lynn Marshall 
 * @version 1.00
 */

#include <chrono>
#include <thread>
#include <iostream>
#include <random>
#include <mutex>
#include <condition_variable>

template <typename Type> class Box
{
private:
    Type contents;	// The "Type" stored in the box
    bool empty = true;	// The state of the box.
    std::mutex mtx;
    std::condition_variable cv;
public:
    Box() : contents(Type()), empty(true), mtx(), cv() {}	// Constructor

    void put( Type item ) {
	std::unique_lock<std::mutex> lock(mtx);	// releases when lock goes out of scope.
	while ( !empty ) cv.wait(lock);
	contents = item;
	empty = false;
	cv.notify_all();
    }

    Type get() {
	std::unique_lock<std::mutex> lock(mtx);	// releases when lock goes out of scope.
	while ( empty ) cv.wait(lock);
	Type item = contents;
	empty = true;
	cv.notify_all();
	return item;
    }
};

const int count = 10;

template <typename Type> class Producer
{
private:
    std::string name;
    Box<Type>& box;

public:
    Producer( Box<Type>& a_box ) : name(), box(a_box) {}
    
    void operator()( const std::string& name ) {
        for(int i = 0; i < 10; i++) {
	    std::cout << name << "(" << std::this_thread::get_id() << ") produced " << i << std::endl;
	    box.put( i );
	    std::cout << name << "(" << std::this_thread::get_id() << ") put in box " << i << std::endl;
	    std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
	}
    }
};

template <typename Type> class Consumer
{
private:
    std::string name;
    Box<Type>& box;

public:
    Consumer( Box<Type>& a_box ) : name(), box(a_box) {}
    void operator()( const std::string& name ) {
        for(int i = 0; i < 10; i++) {
	    std::cout << name << "(" << std::this_thread::get_id() << ") ready to consume " << i << std::endl;
	    Type item = box.get();
	    std::cout << name << "(" << std::this_thread::get_id() << ") consumed " << item << std::endl;
	    std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
	}
    }
};

int main( int argc, char ** argv )
{
    Box<int> box;
    Producer<int> producer( box );
    Consumer<int> consumer( box );
    
    std::thread producer_thread( producer, "producer" );	// Pass by value.
    std::thread consumer_thread( consumer, "consumer" );	// Pass by value.
    producer_thread.join();
    consumer_thread.join();
    return 0;
}

