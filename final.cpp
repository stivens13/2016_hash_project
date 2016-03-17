#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
#include <iomanip>
#include <cstdlib>
#include <list>
#include <math.h>
#include "fibonacci.cpp"

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
		unsigned int i = 0;
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
		for( unsigned int x = 0; x < i; x++ ) {
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
		unsigned int i = 0;
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
====================================        Viktoriia    ===================================================
*/

class MyHashTable
{
public:
	int key;
	string value;
	MyHashTable *next;

	MyHashTable()
	{
		key = 0;
		value = "";
		next = NULL;
	}

	int hash()
	{
		return key; //getting the hash for the current element
	}

	bool linearProbning( int key ) //cheking if the key alreadstring exists into the table
	{
		return this->search( key ) == "";
	}

	void insert( int key, string value ) //inserting new element et the end of the table via recursion
	{
		if( this->next == NULL )
		{
			this->next = new MyHashTable();
			this->key = key;
			this->value = value;
			return;
		}

		this->next->insert( key, value );
	}

	void deleteAt( int key ) //delete is a operator and can not be used as name of fucntion via recursion
	{
		if( this->next == NULL )
		{
			return;
		}

		if( this->key == key )
		{
			//getting the data from the next element in other words removing the element
			this->key = next->key;
			this->value = next->value;
			this->next = next->next;
			return;
		}

		this->next->deleteAt( key );
	}

	string search( int k ) //searching for name inside the hash table via recursion
	{
		if( this->key == k )
		{
			return this->value;
		}

		if( this->next == NULL )
		{
			return "";
		}

		return this->next->search( k );
	}

	void displayTable() //displaying the whole table via recursion
	{
		if( this->next == NULL )
		{
			return;
		}

		cout << key << '\t' << value << endl;

		next->displayTable();
	}
};

//used for splitting the string since C++ dosent support splitting

vector<string> &split( const string &s, char delim, vector<string> &elems ) {
	stringstream ss( s );
	string item;
	while( getline( ss, item, delim ) ) {
		elems.push_back( item );
	}
	return elems;
}

//used for splitting the string since C++ dosent support splitting

vector<string> split( const string &s, char delim ) {
	vector<string> elems;
	split( s, delim, elems );
	return elems;
}

//cheking if string is integer

bool isInteger( const string & s )
{
	if( s.empty() || ( ( !isdigit( s[0] ) ) && ( s[0] != '-' ) && ( s[0] != '+' ) ) ) return false;

	char * p;
	strtol( s.c_str(), &p, 10 );

	return ( *p == 0 );
}

void Viktoriia() //function Test required
{
	ifstream fin( "data_set_1.csv" );
	MyHashTable hash;

	//reading the file untill the end
	while( !fin.eof() )
	{
		string line;
		getline( fin, line );
		vector<string> parts = split( line, ',' );

		if( parts.size() == 2 )
		{
			if( isInteger( parts[0].c_str() ) )
			{
				int key = atoi( parts[0].c_str() );

				if( hash.linearProbning( key ) ) //cheking if the key alreadstring exists into the table and passing if it does
				{
					//filling the table
					hash.insert( key, parts[1] );
				}
			}
		}
	}

	int key;

	cout << "Please enter key to check - "; cin >> key; //prompting the user to enter key
	string str = hash.search( key );

	if( str == "" )
	{
		//if the key dosent exist we need proper error message
		cout << "The key does not exist in the table!" << endl;
	}
	else
	{
		cout << "The corresponding student is - " << str << endl;
	}

	cout << "Please enter key to delete - ";
	cin >> key; //prompting the user to enter key to delete

	hash.deleteAt( key ); //deleting the elemtn
	hash.displayTable(); //displaying the table
}

/*
============================================================================================================
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
	for( unsigned int i = 0; i < str.length(); i++ ) {
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
	// int i;
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

/*
=======================================================================================
*/

/*
====================================        Dharma        ===================================================
*/

/*
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
*/

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
	int size, i = 1;
	// int pos;
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

	cout << "Number of collisions: ";

	table.print_col();

	cout << table.search( 56 ) << endl;

	cout << table.search( 894 ) << endl;

	cout << table.search( 54654654654 ) << endl;
}

/*
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
*/
void fibonacci_tester()

{

}

int main( int argc, const char *argv[] )
{
	// insert code here...

	/*
	int choice1;
	int choice2;
	while( 1 ) {
	cout << "\n----------------------" << endl;
	cout << "       The Hashers!" << endl;
	cout << "\n----------------------" << endl;
	cout << "1.Build the database!" << endl;
	cout << "2.Insert a new student" << endl;
	cout << "3.Display students" << endl;
	cout << "4.Search for a student" << endl;
	cout << "5.Exit" << endl;
	cout << "Enter your choice: " << endl;
	cin >> choice1;
	switch( choice1 )
	{
	case 1:
	cout << "\n----------------------" << endl;
	cout << "  The Hashers are building tables!" << endl;
	cout << "\n----------------------" << endl;
	cout << "1.Build using Direct Address" << endl;
	cout << "2.Build using Division" << endl;
	cout << "3.Build using Fibonacci" << endl;
	cout << "4.Build using Perfect" << endl;
	cout << "5.Build using Double Hashing" << endl;
	cout << "6.Build using Universal" << endl;
	cout << "7.Return " << endl;
	cout << "Enter your choice: " << endl;
	cin >> choice2;
	switch( choice2 )
	{
	case 1:
	break;
	case 2:
	break;
	case 3:
	break;
	case 4:
	break;
	case 5:
	break;
	case 6:
	break;
	case 7:
	break;
	default:
	break;

	}
	break;
	case 2:
	cout << "\n----------------------" << endl;
	cout << "  INSERT: " << endl;
	cout << "\n----------------------" << endl;
	cout << "1.Insert using Direct Address" << endl;
	cout << "2.Insert using Division" << endl;
	cout << "3.Insert using Fibonacci" << endl;
	cout << "4.Insert using Perfect" << endl;
	cout << "5.Insert using Double Hashing" << endl;
	cout << "6.Insert using Universal" << endl;
	cout << "7.Return " << endl;
	cout << "Enter your choice: " << endl;
	cin >> choice2;
	switch( choice2 )
	{
	case 1:
	break;
	case 2:
	break;
	case 3:
	break;
	case 4:
	break;
	case 5:
	break;
	case 6:
	break;
	case 7:
	break;
	default:
	break;

	}

	case 3:
	cout << "\n----------------------" << endl;
	cout << "  PRINT : " << endl;
	cout << "\n----------------------" << endl;
	cout << "1.Print using Direct Address" << endl;
	cout << "2.Print using Division" << endl;
	cout << "3.Print using Fibonacci" << endl;
	cout << "4.Print using Perfect" << endl;
	cout << "5.Print using Double Hashing" << endl;
	cout << "6.Print using Universal" << endl;
	cout << "7.Return " << endl;
	cout << "Enter your choice: " << endl;
	cin >> choice2;
	switch( choice2 )
	{
	case 1:
	break;
	case 2:
	break;
	case 3:
	break;
	case 4:
	break;
	case 5:
	break;
	case 6:
	break;
	case 7:
	break;
	default:
	break;

	}
	case 4:
	cout << "\n----------------------" << endl;
	cout << "  SEARCH: " << endl;
	cout << "\n----------------------" << endl;
	cout << "1.Search using Direct Address" << endl;
	cout << "2.Search using Division" << endl;
	cout << "3.Search using Fibonacci" << endl;
	cout << "4.Search using Perfect" << endl;
	cout << "5.Search using Double Hashing" << endl;
	cout << "6.Search using Universal" << endl;
	cout << "7.Return " << endl;
	cout << "Enter your choice: " << endl;
	cin >> choice2;
	switch( choice2 )
	{
	case 1:
	break;
	case 2:
	break;
	case 3:
	break;
	case 4:
	break;
	case 5:
	break;
	case 6:
	break;
	case 7:
	break;
	default:
	break;

	}
	case 5:
	exit( 1 );
	default:
	cout << "\nEnter correct option\n";
	}
	}
	*/

	// Anna();
	//    Jimmy();
	Nikita();
	//Dharma();
	//Viktoriia();

	system( "pause" );

	return 0;
};