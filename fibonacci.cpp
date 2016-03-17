#include <iostream>
#include <string>
#include <memory>
#include <math.h>
#include <iomanip>
#include <cstdlib>
#include <list>
#include <vector>
#include <fstream>

using namespace std;

const int DEFAULT_SIZE = 1000;

const double W = pow( 2, 64 );


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
	HashEntry<Key, Value>* next;

public:

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
	}  //
	HashEntry<Key, Value>* HashEntry<Key, Value>::getNext() const
	{
		return next;
	}   

};

template<typename Key, typename Value>
class FibonacciTable

{
	HashEntry<Key, Value>** fibonacci_table;

	int size;

	double A;

	int item_count;

	int col;

public:

	FibonacciTable()
		
		/*size( DEFAULT_SIZE / 0.5 ),
		A( get_golden_ratio() ),
		col(0)
		*/

	{
		size = (int) DEFAULT_SIZE * 2;
		A = get_golden_ratio();
		col = 0;
		fibonacci_table = new HashEntry<Key, Value>*[size];
		for( int c = 0; c < size; c++ )
			fibonacci_table[c] = nullptr;

		cout << "Size: " << size << endl;
	}

	void insert( Key& a_key, Value& object )

	{

		HashEntry<Key, Value>* nu = new HashEntry<Key, Value>( a_key, object );

		int hashed_key = hash( a_key );

		if( fibonacci_table[hashed_key] == nullptr )
			fibonacci_table[hashed_key] = nu;

		else

		{
			fibonacci_table[hashed_key]->setNext( nu );
			cout << "collision " << a_key << endl;
			col++;
		}
	}

	void print_col() { cout << col << endl; }

	bool is_empty() { return item_count == 0; }

	double get_golden_ratio() { return ( sqrt( 5 ) - 1 ) / 2; }

	int hash( Key& key )

	{
		key = (int) floor( size * ( key * A - floor( key * A ) ) );

		//key = floor( size * ( key * A % 1 ) );

		return key;
	}

	string search( Key key )

	{
		int hash_key = hash( key );

		return fibonacci_table[hash_key]->getItem();
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

/*
int main()

{
	DataReader<int, string> reader;

	FibonacciTable<int, string> table;

	reader.getData( table );

	cout << "Number of collisions: ";
	
	table.print_col();

	cout << table.search( 56 ) << endl;

	cout << table.search( 894 ) << endl;

	system( "pause" );

	return 0;
}
*/