#include <iostream>
#include <string>
#include <memory>
#include <math.h>
#include <iomanip>
#include <cstdlib>
#include <list>
#include <vector>
#include <fstream>
#include "fibo_header.h"

using namespace std;

template <typename Key, typename Value>
class Entry
{
private:

	Key key;
	Value item;
	
public:
	Entry() {}
	Entry( Value new_entry, Key item_key ): item( new_entry ), key( item_key ) {}

	Value getItem() const { return item; }

	Key getKey() const { return key; }

	void setItem( const Value& new_entry ) { item = new_entry; }

	void setKey( const Key& item_key ) { key = item_key; }

	bool operator==( const Entry<Key, Value>& rightHandItem ) const { return ( key == rightHandItem.getKey() ); }

	bool operator>( const Entry<Key, Value>& rightHandItem ) const { return ( key > rightHandItem.getKey() ); }

}; 


template<typename Key, typename Value>
class HashEntry: public Entry<Key, Value>

{
private:

	Entry<Key, Value> entry;
	HashEntry<Key, Value>* next;
	
public:

	//HashEntry(): next(nullptr) {}

	HashEntry()
	{
		Entry<Key, Value>();
		next = nullptr;
	}  // end 
	HashEntry( Key itemKey, Value newEntry )
	{
		Entry<Key, Value>::setItem( newEntry );
		Entry<Key, Value>::setKey( itemKey );
		next = nullptr;
	}  // end 
	HashEntry( HashEntry<Key, Value>* nextEntryPtr )
	{
		Entry<Key, Value>::setItem( newEntry );
		Entry<Key, Value>::setKey( itemKey );
		next = nextEntryPtr;
	}  // end 

	void setNext( HashEntry<Key, Value>* nextEntryPtr )
	{
		next = nextEntryPtr;
	}  // end 
	HashEntry<Key, Value>* HashEntry<Key, Value>::getNext() const
	{
		return next;
	}  // end 

};

template<typename Key, typename Value>
class FibonacciTable// : public FibonacciTableInterface<T,R>

{	
	HashEntry<Key, Value>** fibonacci_table;

	int current_size;

	double golden_middle;

	int item_count;

	//void rehash() {};

public:

	FibonacciTable(): current_size( 0 ), golden_middle( get_golden_ratio() ) {}

	void insert( Key& a_key, Value& object )

	{
		HashEntry<Key, Value>* nu = new HashEntry<Key, Value>( a_key, object );

		a_key = hash( a_key );

		
		if( fibonacci_table[a_key] == nullptr )
			fibonacci_table[a_key] = nu;

		else
			fibonacci_table[a_key]->setNext( nu );
			

		//shared_ptr

	}

	bool is_empty() { return item_count == 0; }

	double get_golden_ratio() { return ( sqrt( 5 ) - 1 ) / 2; }

	int hash( Key& key )

	{
		int c2 = 0x27d4eb2d; 

		key = ( key ^ 61 ) ^ ( key >> 16 );
		key = key + ( key << 3 );
		key = key ^ ( key >> 4 );
		key = key * c2;
		key = key ^ ( key >> 15 );

		key %= 1000;

		cout << key << endl;

		return key;
	}

};

template<typename Key, typename Value>
class DataReader

{
private:

	fstream data;

public:

	DataReader()
	{

		data.open( "data_set_1.csv" );

		if( !data )
		{
			cout << "The file was not found" << endl;

			exit( EXIT_FAILURE );
		}
	}

	~DataReader() { close_file(); };

	void close_file()

	{
		if( data ) data.close();
	}

	void getData( FibonacciTable<Key, Value> & D )
	{
		string buffer;
		Key id;
		Value name;

		while( getline( data, buffer ) )
		{
			if( buffer == "" )
				continue;

			int k = buffer.find( "," );

			id = atoi( buffer.substr( 0, k ).data() );

			name = buffer.substr( k + 1, buffer.length() );

			//pair<string, double> an_item;

			//an_item.first = name;
			//an_item.second = price;

			D.insert( id, name );
		}

		cout << "Done" << endl;

	}
};


int main()

{
	DataReader<int, string> reader;

	FibonacciTable<int, string> table;

	reader.getData( table );

	system( "pause" );

	return 0;
}