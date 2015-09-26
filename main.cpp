#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::endl;

#include "ou_thread.h"
using namespace openutils;

class MyThread : public Thread
{
private:
	int m_nCount;
public:
	MyThread( int n, const char* nm )
	{
		Thread::setName( nm );
		m_nCount = n;
	}
	void run( )
	{
		wait( "MyMutex" );
		for ( int i = 0; i < m_nCount; i++ )
		{
			cout << getName( ).c_str( ) << ":" << i << endl;
		}
		release( "MyMutex" );
	}
};

int main( )
{
	Thread* t1 = new MyThread( 15, "Thread 01" );
	Thread* t2 = new MyThread( 10, "Thread 02" );
	Thread* t3 = new MyThread(   5, "Thread 03" );
	Mutex m( "MyMutex" );
	t1->start( );
	t2->start( );
	t3->start( );

	t1->stop( );
	t2->stop( );
	t3->stop( );

	delete t1;
	delete t2;
	delete t3;

	m.release( );

	return 0;
}
