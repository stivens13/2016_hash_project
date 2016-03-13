// Jimmy Liu
// CIS 22C
// Final Project
// 13 March 2016

#include <iostream>
#include <cstdlib>
#include <string>
#include <iostream>
#include <array>

#define MIN_TABLE_SIZE 10
#define k 7919 
#define a 321
#define b 43112
using namespace std;

enum EntryType {Legitimate, Empty, Deleted};

struct Student {
    string name;
    int studentId;
};

struct HashNode
{
    string element;
    enum EntryType info;
};

struct HashTable
{
    int size;
    HashNode *table;
};

// Universal Hash Function
int HashFunc1(string text, int size) {
  int i;
  long long  res = 0;
  long long M = (size * k);
  int s=text.size();
  for(i = s-1; i >= 0; i--)
  {
    res = a * (res * 256 + (int)text[i]);
    //cout<<"res before modulo = "<<res<<endl;
    res=res % M;
    //cout<<"res after modulo = "<<res<<endl;
  }
    long long res1 = (res + b) / k;
    return res1;
}

// Regular Prime Hash Function
int HashFunc2(string str, int size) {
    unsigned int hash = 0;
    unsigned int prime_one   = 10103;
    unsigned int prime_two    = 49921;
    for (int i = 0; i < str.length(); i++) {
        hash = hash * prime_one + str[i];
        prime_one = prime_one * prime_two;
    }
    hash = hash % size;
    return hash;
}

/*
 * Function to Initialize Table
 */
HashTable *initializeTable(int size)
{
    HashTable *htable;
    if (size < MIN_TABLE_SIZE)
    {
        cout<<"Table Size Too Small"<<endl;
        return NULL;
    }
    htable = new HashTable;
    if (htable == NULL)
    {
        cout<<"Out of Space"<<endl;
        return NULL;
    }
    htable->size = size;
    htable->table = new HashNode [htable->size];
    if (htable->table == NULL)
    {
        cout<<"Table Size Too Small"<<endl;
        return NULL;
    }
    for (int i = 0; i < htable->size; i++)
    {
        htable->table[i].info = Empty;
        htable->table[i].element = "NULL";
    }
    return htable;
}
/*
 * Function to Find Element from the table
 */
int Find(string key, HashTable *htable)
{
    int hashVal= HashFunc1(key, htable->size);
    int stepSize= HashFunc2(key, htable->size);
    while (htable->table[hashVal].info != Empty && htable->table[hashVal].element != key) {
        hashVal = hashVal + stepSize;
        hashVal = hashVal % htable->size;
    }
    return hashVal;
}
/*
 * Function to Insert Element into the table
 */
void Insert(string key, HashTable *htable)
{
    int pos = Find(key, htable);
    if (htable->table[pos].info != Legitimate )
    {
        htable->table[pos].info = Legitimate;
        htable->table[pos].element = key;
    }
}
/*
 * Function to Rehash the table
 */
HashTable *Rehash(HashTable *htable)
{
    int size = htable->size;
    HashNode *table = htable->table;
    htable = initializeTable(2 * size);
    for (int i = 0; i < size; i++)
    {
        if (table[i].info == Legitimate)
            Insert(table[i].element, htable);
    }
    //delete(table);
    return htable;
}
/*
 * Function to Retrieve the table
 */
void Retrieve(HashTable *htable)
{
    for (int i = 0; i < htable->size; i++)
    {
        string value = htable->table[i].element;
        if (value == "NULL")
            cout<<"Position: "<<i + 1<<" Element: Null"<<endl;
        else
            cout<<"Position: "<<i + 1<<" Element: "<<value<<endl;
    }
 
}
/*
 * Main Contains Menu
 */
int main()
{
    string value;
    int size, pos, i = 1;
    int choice;
    HashTable *htable;
    while(1)
    {
        cout<<"\n----------------------"<<endl;
        cout<<"Operations on Double Hashing"<<endl;
        cout<<"\n----------------------"<<endl;
        cout<<"1.Initialize size of the table"<<endl;
        cout<<"2.Insert element into the table"<<endl;
        cout<<"3.Display Hash Table"<<endl;
        cout<<"4.Rehash The Table"<<endl;
        cout<<"5.Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<"Enter size of the Hash Table: ";
            cin>>size;
            htable = initializeTable(size);
            break;
        case 2:
            if (i > htable->size)
            {
                cout<<"Table is Full, Rehash the table"<<endl;
                continue;
            }
        	cout<<"Enter element to be inserted: ";
        	cin>>value;
            Insert(value, htable);
            i++;
            break;
        case 3:
            Retrieve(htable);
            break;
        case 4:
            htable = Rehash(htable);
            break;
        case 5:
            exit(1);
        default:
           cout<<"\nEnter correct option\n";
       }
    }
    return 0;
}