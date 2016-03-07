#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;

#define k 7919 
#define Hsize 1009   
#define a 321
#define b 43112
#define BLANK " "
#define MIN_TABLE_SIZE 100

/*
 * Node Declaration
 */
struct HashNode
{
    int element;
    enum EntryType info;
};
/*
 * Table Declaration
 */
struct HashTable
{
    int size;
    HashNode *table;
};
/*
 * Function to Genereate First Hash
 */
int HashFunc1(int key, int size)
{
	// to be implemented
    return 0;
}
/*
 * Function to Genereate Second Hash
 */
int HashFunc2(int key, int size)
{
	// to be implemented
    return 0;
}
/*
 * Function to Initialize Table
 */

void Retrieve(HashTable *htable)
{
    for (int i = 0; i < htable->size; i++)
    {
        int value = htable->table[i].element;
        if (!value)
            cout<<"Position: "<<i + 1<<" Element: Null"<<endl;
        else
            cout<<"Position: "<<i + 1<<" Element: "<<value<<endl;
    }
 
}

long UniversalFunction(string text)
{
  int i;
  long  res = 0;
  long M = (Hsize * k);
  int s=text.size();
  for(int i = s-1; i >= 0; i--) {
    res = a * (res * 256 + (int)text[i]);
    res=res % M;
  }
  long res1 = (res + b) / k;
  return res1;
}

int main() {
	cout << "ello" << endl;
	cout << UniversalFunction("bob the builder is cool") << endl;
	return 0;
}