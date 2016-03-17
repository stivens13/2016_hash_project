//
//  main.cpp
//  22CFinal
//
//  Created by E on 3/16/16.
//  Copyright © 2016 E. All rights reserved.
//


#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

auto k = 7919;
auto a = 321;
auto b = 43112;
auto Hsize = 1009;
auto BLANK = " ";
auto MIN_TABLE_SIZE = 100;


using namespace std;

const int TABLE_SIZE = 1001;


class Student
{
private:
	string name;
	int id;
public:
	bool isEmpty = true;

	Student() {

	}

	Student( string name, int id ) {
		this->name = name;
		this->id = id;
		isEmpty = false;
	}

	string getName() {
		return name;
	}

	int getID() {
		return id;
	}
};


/*
====================================        ANNA        ===================================================
*/

class HashTable
{
private:
	vector<Student> *table;
	int m = TABLE_SIZE;
	int totalProbes;
	int numInserts;

	void tallyProbes( int p );

public:
	HashTable() {
		table = new vector<Student>( TABLE_SIZE );

	}

	void search( int id ) {
		int probe;
		int i = 0;
		probe = ( hash( id ) + i * i ) % m;

		for( int j = 0; i < table->size(); j++ ) {

			if( ( *table )[probe].isEmpty )
				return;

			else if( id == ( *table )[probe].getID() ) {
				cout << endl << " [ index : " << probe << " | " << ( *table )[probe].getName() << " , " <<
					( *table )[probe].getID() << " ] " << endl;
			}

			++i;
			probe = ( hash( id ) + i * i ) % m;
		}

	}

	void print() {
		auto i = table->size();
		for( int x = 0; x < i; x++ ) {
			if( !( *table )[x].isEmpty )
				cout << endl << " [ index : " << x << " | " << ( *table )[x].getName() << " , " << ( *table )[x].getID() <<
				" ] " << endl;
		}
	}


	int hash( int k ) {
		return k % m;
	}

	float probeRate() {
		return (float)totalProbes / (float)numInserts;
	}

	void insert( string name, int id ) {
		int i = 0, pre_inserts = numInserts;
		int probe, LIMIT = m / 2;

		do {
			probe = ( hash( id ) + i * i ) % m;
			if( ( *table )[probe].isEmpty ) {
				( *table )[probe] = Student( name, id );
				numInserts++;
				break;
			}
			else {
				totalProbes++;
				cout << " for " << name << "  i = " << ++i << " , index = " << probe << endl;
			}
			//            i++;
		} while( !( *table )[probe].isEmpty && i != m && i < LIMIT );
		if( pre_inserts == numInserts ) {
			cout << "Fail on Insertion(Maximum number of probes[" << LIMIT << "] exceeded)." << endl;
		}

	}

	void insert( Student obj ) {
		int i = 0, pre_inserts = numInserts;
		int probe, LIMIT = m / 2;

		do {
			probe = ( hash( obj.getID() ) + i * i ) % m;
			if( ( *table )[probe].isEmpty ) {
				( *table )[probe] = obj;
				numInserts++;
				break;
			}
			else {
				totalProbes++;
				cout << " for " << obj.getName() << "  i = " << ++i << " , index = " << probe << endl;
			}
			//            i++;
		} while( !( *table )[probe].isEmpty && i != m && i < LIMIT );
		if( pre_inserts == numInserts ) {
			cout << "Fail on Insertion(Maximum number of probes[" << LIMIT << "] exceeded)." << endl;
		}

	}

	void remove( int id ) {
		int probe;
		int i = 0;
		probe = ( hash( id ) + i * i ) % m;

		for( int j = 0; i < table->size(); j++ ) {

			if( ( *table )[probe].isEmpty )
				return;

			else if( id == ( *table )[probe].getID() ) {

				( *table ).erase( ( *table ).begin() + probe );
			}

			++i;
			probe = ( hash( id ) + i * i ) % m;
		}
	}

	~HashTable() {
		for( int i = 0; i < TABLE_SIZE; i++ )
			if( !( *table )[i].isEmpty )
				table->pop_back();
		delete table;
	}
};

/*
=======================================================================================
*/


/*
====================================        Jimmy        ===================================================
*/


enum EntryType
{
	Legitimate, Empty, Deleted
};


struct HashNode
{
	string element;
	int studentId;
	enum EntryType info;
};

struct JHashTable
{
	int size;
	HashNode *table;
};

// Universal Hash Function
int HashFunc1( string text, int size ) {
	int i;
	long long res = 0;
	long long M = ( size * k );
	int s = text.size();
	for( i = s - 1; i >= 0; i-- ) {
		res = a * ( res * 256 + (int)text[i] );
		//cout<<"res before modulo = "<<res<<endl;
		res = res % M;
		//cout<<"res after modulo = "<<res<<endl;
	}
	long long res1 = ( res + b ) / k;
	return res1;
}

// Regular Prime Hash Function
int HashFunc2( string str, int size ) {
	unsigned int hash = 0;
	unsigned int prime_one = 10103;
	unsigned int prime_two = 49921;
	for( int i = 0; i < str.length(); i++ ) {
		hash = hash * prime_one + str[i];
		prime_one = prime_one * prime_two;
	}
	hash = hash % size;
	return hash;
}

/*
* Function to Initialize Table
*/
JHashTable *initializeTable( int size ) {
	JHashTable *htable;
	if( size < MIN_TABLE_SIZE ) {
		cout << "Table Size Too Small" << endl;
		return NULL;
	}
	htable = new JHashTable;
	if( htable == NULL ) {
		cout << "Out of Space" << endl;
		return NULL;
	}
	htable->size = size;
	htable->table = new HashNode[htable->size];
	if( htable->table == NULL ) {
		cout << "Table Size Too Small" << endl;
		return NULL;
	}
	for( int i = 0; i < htable->size; i++ ) {
		htable->table[i].info = Empty;
		htable->table[i].element = "NULL";
	}
	return htable;
}

/*
* Function to Find Element from the table
*/
int Find( string key, JHashTable *htable ) {
	int hashVal = HashFunc1( key, htable->size );
	int stepSize = HashFunc2( key, htable->size );
	while( htable->table[hashVal].info != Empty && htable->table[hashVal].element != key ) {
		hashVal = hashVal + stepSize;
		hashVal = hashVal % htable->size;
	}
	return hashVal;
}

/*
* Function to Insert Element into the table
*/
void Insert( string key, int ID, JHashTable *htable ) {
	int pos = Find( key, htable );
	if( htable->table[pos].info != Legitimate ) {
		htable->table[pos].info = Legitimate;
		htable->table[pos].element = key;
		htable->table[pos].studentId = ID;
	}
}

/*
* Function to Rehash the table
*/
JHashTable *Rehash( JHashTable *htable ) {
	int size = htable->size;
	HashNode *table = htable->table;
	htable = initializeTable( 2 * size );
	for( int i = 0; i < size; i++ ) {
		if( table[i].info == Legitimate )
			Insert( table[i].element, table[i].studentId, htable );
	}
	//delete(table);
	return htable;
}

/*
* Function to Retrieve the table
*/
void Retrieve( JHashTable *htable ) {
	for( int i = 0; i < htable->size; i++ ) {
		string value = htable->table[i].element;
		int studentId = htable->table[i].studentId;
		if( value == "NULL" )
			cout << "Position: " << i + 1 << " Element: Null" << endl;
		else {
			cout << "Position: " << i + 1 << " Name: " << value << " " << "ID: " << studentId << endl;
		}
	}

}

HashNode *getItem( string key, JHashTable *htable ) {
	int pos = Find( key, htable );
	if( htable->table[pos].info == Legitimate ) {
		return &htable->table[pos];
	}
	return nullptr;
}


/*
* Node Declaration
*/
struct JHashNode
{
	int element;
	enum EntryType info;
};
/*
* Table Declaration
*/
struct J2HashTable
{
	int size;
	JHashNode *table;
};
/*
* Function to Genereate First Hash
*/
int HashFunc1( int key, int size )
{
	// to be implemented
	return 0;
}
/*
* Function to Genereate Second Hash
*/
int HashFunc2( int key, int size )
{
	// to be implemented
	return 0;
}
/*
* Function to Initialize Table
*/

void Retrieve( J2HashTable *htable )
{
	for( int i = 0; i < htable->size; i++ )
	{
		int value = htable->table[i].element;
		if( !value )
			cout << "Position: " << i + 1 << " Element: Null" << endl;
		else
			cout << "Position: " << i + 1 << " Element: " << value << endl;
	}

}

long UniversalFunction( string text )
{
	int i;
	long  res = 0;
	long M = ( Hsize * k );
	int s = text.size();
	for( int i = s - 1; i >= 0; i-- ) {
		res = a * ( res * 256 + (int)text[i] );
		res = res % M;
	}
	long res1 = ( res + b ) / k;
	return res1;
}

/*
=======================================================================================
*/

/*
====================================        Nikita        ===================================================
*/



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
class FibonacciTable

{
	HashEntry<Key, Value>** fibonacci_table;

	int current_size;

	double A;

	int item_count;

public:

	FibonacciTable(): current_size( 0 ), A( get_golden_ratio() ) {}

	void insert( Key& a_key, Value& object )

	{
		HashEntry<Key, Value>* nu = new HashEntry<Key, Value>( a_key, object );

		a_key = hash( a_key );


		if( fibonacci_table[a_key] == nullptr )
			fibonacci_table[a_key] = nu;

		else
			
		{
			fibonacci_table[hashed_key]->setNext( nu );
			cout << "collision " << a_key << endl;
			col++;
		}
	}

	bool is_empty() { return item_count == 0; }

	double get_golden_ratio() { return ( sqrt( 5 ) - 1 ) / 2; }

	int hash( Key& key )

	{
		key = (int)floor( size * ( key * A - floor( key * A ) ) );

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

/*
=======================================================================================
*/

/*
====================================        Dahram        ===================================================
*/

template <typename T>
class DHashTable
{
	T* hashTable;
	int size;
	int collisions;
	int values[256];
	int valuesCount[256];
	vector<Student> collided;

public:
	DHashTable( int size1 )
	{
		size = size1;
		hashTable = new T[size + 1];
		for( int i = 0; i < 256; i++ )
		{
			values[i] = 1;
		}
	}
	~DHashTable() { delete[] hashTable; }
	void GetData( vector<T>& vdata, bool easy )
	{
		InitializeHashTable( vdata, easy );
		CheckCollisions();
	}

	// If "easy" = true, this uses the hardcoded perfect hashing function
	int InitializeHashTable( vector<T>& vdata, bool easy )
	{
		for( int index = 0; index < size; index++ )
		{
			hashTable[index] = { "NULL", NULL };
		}

		if( !easy )
		{
			setValues( vdata );
			return -1;
		}
		for( T data : vdata )
		{
			int index = easyHashGenerator( data.name );
			//cout << "INDEX " << index << " item " << hashTable[index] << endl;
			if( hashTable[index].name.compare( "NULL" ) != 0 )
			{
				collisions++;
				collided.push_back( hashTable[index] );
			}
			hashTable[index] = data;
		}
		return collisions;
	}
	double CheckCollisions()
	{
		double percent = double( collisions ) / double( size ) * 100;
		cout << "Percentage of collisions " << percent << "%" << endl;
		return percent;
	}

	//The "easy" hash generator
	int easyHashGenerator( string str )
	{
		if( str == "Jimmy" )
			return 4;
		else if( str == "Dharma" )
			return 3;
		else if( str == "Anna" )
			return 2;
		else if( str == "Nikita" )
			return 1;
		else if( str == "Viktoria" )
			return 0;
		return 5;
	}

	//This is the "smarter" perfect hashing function/searching function I wrote
	Student cichelliSearch( string name )
	{
		return hashTable[calculateKey( name )];
	}

	//This is for the "dumber"" one
	Student easySearch( string name )
	{
		return hashTable[easyHashGenerator( name )];
	}
	void Traverse( string str, int index )
	{
		if( index < size )
		{
			index++;
			if( str.compare( "NULL" ) != 0 )
				cout << str << endl;
			Traverse( hashTable[index], index );
		}
	}
	string operator[] ( int index )
	{
		return hashTable[index];
	}
	int hashInsert( string str )
	{
		int i = 0;
		do
		{
			if( hashTable[key].compare( "NULL" ) == 0 )
			{
				hashTable[i] = str;
				return i;
			}
			else
				i++;
		} while( i < size );
		return -1;
	}
	bool hashRemove( string str )
	{
		int i = 0;
		do
		{
			if( hashTable[i].compare( str ) == 0 )
			{
				hashTable[i] = "NULL";
				return true;
			}
			else
				i++;
		} while( i < size );
		return false;
	}
	void printCollisions()
	{
		for( int i = 0; i < collided.size(); i++ )
		{
			cout << collided[i] << "  ";
		}
		cout << endl;
	}
	void print()
	{
		for( int i = 0; i < size; i++ )
		{
			cout << hashTable[i].name << "   " << hashTable[i].studentId << endl;
		}
	}

	int calculateKey( string str )
	{
		int key = 0;
		for( char c : str )
		{
			key += values[c];
		}
		return key % size;
	}
	void setValues( vector<T> vec )
	{
		for( T data : vec )
		{
			for( char c : data.name )
			{
				valuesCount[c] ++;
			}
		}

		for( T data : vec )
		{
			int key = calculateKey( data.name );
			//cout << "HEREH " << key << endl;

			if( hashTable[key].name == "NULL" )
			{
				hashTable[key] = data;
			}
			else
			{
				int i;
				while( hashTable[key].name != "NULL" )
				{
					i = 0;
					//check the letter does not affect any other words
					while( valuesCount[data.name.at( i )] != 1 )
					{
						i++;
					}
					values[data.name.at( i )] ++;
					key = calculateKey( data.name );
				}
				hashTable[key] = data;
			}

		}

	}
};

template <typename T>
class D2HashTable
{
private:

	Node** hashTable;
	int values[256];
	int size;
public:
	D2HashTable( int size1 ) {
		size = size1;
		hashTable = new Node *[size + 1];
	}

	~D2HashTable() { delete[] hashTable; }

	void GetData( vector<T> &vdata, bool easy ) {
		InitializeD2HashTable( vdata, easy );
		CheckCollisions();
	}

	void InitializeD2HashTable( vector<T> &vdata ) {
		for( int index = 0; index < size; index++ ) {
			Node *n = new Node( { "NULL", NULL }, NULL );
			hashTable[index] = n;
		}
		for( T data : vdata ) {
			int index = badGenerator( data.name );
			Node *n = new Node( data, NULL );
			if( hashTable[index]->kid.name.compare( "NULL" ) != 0 ) {
				Node *roamer;
				roamer = hashTable[index];
				while( roamer->next != NULL ) {
					roamer = roamer->next;
				}
				roamer->next = n;
			}
			else
				hashTable[index] = n;
		}
	}

	int badGenerator( string str ) {
		return str.length() % size;
	}

	void Traverse( string str, int index ) {
		if( index < size ) {
			index++;
			if( str.compare( "NULL" ) != 0 )
				cout << str << endl;
			Traverse( hashTable[index], index );
		}
	}

	Student search( string name ) {
		int i = badGenerator( name );
		if( hashTable[i]->next == NULL )
			return hashTable[i]->kid;
		Node *roamer;
		roamer = hashTable[i];
		while( roamer->next != NULL ) {
			roamer = roamer->next;
		}
		return roamer->kid;

	}

	void print() {
		for( int i = 0; i < size; i++ ) {
			Node *n = hashTable[i];
			cout << n->kid.name << "    " << n->kid.studentId << ", ";
			while( n->next != NULL ) {
				n = n->next;
				cout << n->kid.name << "    " << n->kid.studentId << ", ";

			}
			cout << endl;
		}
	}
};


	/*
	=======================================================================================
	*/

	void readData( HashTable &a, string filename ) {
		string line;
		ifstream myfile( filename + ".csv" );
		if( myfile.is_open() ) {
			while( getline( myfile, line ) ) {
				string temp[2];
				istringstream ss( line );
				getline( ss, temp[0], ',' ); //student id temp[0]
				getline( ss, temp[1], ',' ); //student name temp[1]
				Student tempo( temp[1], atoi( temp[0].c_str() ) );
				a.insert( tempo );
			}
		}
		else {
			cout << "ERROR!" << endl;
			system( "Pause" );
		}
		myfile.close();
	}

	void Anna()
	{
		HashTable a;

		readData( a, "MOCK_DATA" );

		a.print();
		a.remove( 1 );
		a.print();
	}

	void Jimmy()
	{
		string value;
		int size, pos, i = 1;
		int choice;
		JHashTable *htable;
		while( 1 )
		{
			cout << "\n----------------------" << endl;
			cout << "Operations on Double Hashing" << endl;
			cout << "\n----------------------" << endl;
			cout << "1.Initialize size of the table" << endl;
			cout << "2.Insert element into the table" << endl;
			cout << "3.Display Hash Table" << endl;
			cout << "4.Rehash The Table" << endl;
			cout << "5.Find Item" << endl;
			cout << "6.Exit" << endl;
			cout << "Enter your choice: ";
			cin >> choice;
			switch( choice )
			{
			case 1:
				cout << "Enter size of the Hash Table: ";
				cin >> size;
				htable = initializeTable( size );
				break;
			case 2:
				if( i > htable->size )
				{
					cout << "Table is Full, Rehash the table" << endl;
					continue;
				}
				cout << "Enter element to be inserted: ";
				cin >> value;
				Insert( value, 12512, htable );
				i++;
				break;
			case 3:
				Retrieve( htable );
				break;
			case 4:
				htable = Rehash( htable );
				break;
			case 5: {
				cout << "Enter element to search: ";
				cin >> value;
				HashNode *hold = getItem( value, htable );
				if( hold != nullptr ) {
					cout << "Name: " << hold->element << " Student Id: " << hold->studentId << endl;
				}}
					break;
			case 6:
				exit( 1 );
			default:
				cout << "\nEnter correct option\n";
			}
		}

	}


	void Nikita()
	{
		DataReader<int, string> reader;

		FibonacciTable<int, string> table;

		reader.getData( table );

		system( "pause" );
	}


	void Dharma() {
		DHashTable<Student> h( 5 );
		//vector<Student> vec = {{ "Jimmy", 4 } };
		vector<Student> vec = { { "Jimmy",    4 },
		{ "Dharma",   3 },
		{ "Anna",     2 },
		{ "Nikita",   1 },
		{ "Viktoria", 0 } };
		h.InitializeHashTable( vec, false );
		h.print();
		//cout << h.cichelliSearch("Jimmy").studentId;
		cin.get();


		D2HashTable<Student> hh( 3 );
		//vector<Student> vec = {{ "Jimmy", 4 } };
		vector<Student> vecc = { { "ab", 4 },{ "cd", 2 },{ "sd", 2 } };
		hh.InitializeD2HashTable( vecc );
		hh.print();
		cout << "Find Student : " << hh.search( "cd" ).getName() << hh.search( "cd" ).getID();
		cin.get();
	}

	void fibonacci_tester()

	{

	}

	int main( int argc, const char *argv[] ) 
	
	{
		// insert code here...
		// Anna();
		//    Jimmy();
		//Nikita();
		//Dharma();

		return 0;
	}