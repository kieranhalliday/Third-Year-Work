#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <string.h>       // provides string class
#include <cctype>         // provides isalpha() and tolower()


using namespace std;

// The following function should be moved into your skiplist.cc file when you
// write that.  It implements the random bit generation.
#include <ctime>                // for time()
#include <cstdlib>              // for rand(), srand(), and RAND_MAX

int linearSearch(string,long,std::vector<string>);
void printInOrder(std::vector<string>,int size);
void sort(std::vector<string>, int size);
void quicksort(std::vector<string>,int,int);

int randBit(void) {             // return a "random" bit
  static int bitsUpperBd=0;
  static int bits;              // store bits returned by rand()
  if( bitsUpperBd == 0 ) {      // refresh store when empty
    bitsUpperBd = RAND_MAX;
    bits = rand();
  }
  int b = bits & 1;
  bits >>= 1;
  bitsUpperBd >>= 1;
  return b;
}


// Remove all characters except letters (A-Z,a-z) from line,
// except keep '-' or '\'' if they are between letters.
void lowercaseWords(string & line) {
  for( string::iterator it = line.begin(); it != line.end(); ++it ) {
    if( !isalpha(*it) ) {
      if( (*it != '-' && *it != '\'') ||
          it == line.begin() || it+1 == line.end() ||
          !isalpha(*(it-1)) || !isalpha(*(it+1)) ) {
        *it = ' ';
      }
    } else {
      *it = tolower(*it);
    }
  }
}

void print(ostream & output, string & word) {
  output << word << endl;
}

int main(int argc, char *argv[]) {
	long size=0; //number of elements in array
	std::vector<std::string> array;
	//Used because without it my code had
	// a segmentation fault, it is removed later
	array.insert(array.begin(),"a");
	//Insert is supported by the vector insert fucntion
	//Defined by the library vector

  if( argc != 3 ) {
    cerr << "Usage: " << argv[0] << " book.txt index.txt" << endl;
    exit(1);
  }

  ifstream fin;
  fin.open(argv[1]);
  if( !fin.is_open() ) {
    cerr << "Unable to open " << argv[1] << endl;
    exit(2);
  }

  ofstream fout;
  fout.open(argv[2]);
  if( !fout.is_open() ) {
    cerr << "Unable to open " << argv[2] << endl;
    exit(3);
  }

  string line, word;
  while( !fin.eof() ) {
    getline(fin,line);
    lowercaseWords(line);
    istringstream iss(line, istringstream::in);
    while( iss >> word ) {
      	//Add words to vector array
	array.insert(array.begin()+1,word);
	size++;	
    }
  }
	printInOrder(array,size);
}


//Find is supported by linear search
//Returns the index of the word you are searching for
//Returns -1 if not found
int linearSearch(string word, long size, std::vector<string> array){
	for(long i=0;i<size;i++){
		if(word==array[i]){
			cout<<array[i]<<"\n";
			return i;
		}
	}
	cout<<"Not found\n";
	return -1;

}

//Print in order is supported by the function sort defined in the library algorithm
// and a basic print loop
//Sorts an array by to the function
//Prints of the elements in alphabetical order
void printInOrder(std::vector<string> array, int size){

         sort(array.begin(),array.end());
	 array.erase(array.begin()+1); // This removes the a I added earlier
         for(int i=0;i<size+1;i++){   // Size +1 because size starts at 0
                 cout<<array[i]<<"\n";
         }
}


//NOT USED FOR PART 1
/*void quicksort(std::vector<string> array, int low, int high){
	string temp;
	string pivot=array[(low+high)/2];
	int i=low, j=high;
	
	
	do{
		while((array[i].compare(pivot)<0) && (i<high)){
			i++;
		}
		while((array[j].compare(pivot)>0) && (j>low)){
			j--;
		}
		if(i<=j){
			temp=array[i];
			array[i]=array[j];
			array[j]=temp;
			i++;
			j--;
		}
	} while(i<=j);

	if(low<j)
		quicksort(array,low,j);
	if(i>high)
		quicksort(array,i,high);
}
//Very slow sorting algorithm
void sort(std::vector<string> array, int size){

         string temp;
         for(int i=0;i<size-1;i++){
                 for(int j=0;j<array[i].size() && j<array[i+1].size();j++){
                         if(array[i][j]>array[i+1][j]){
                                 temp=array[i];
                                 array[i]=array[i+1];
                                 array[i+1]=temp;
                          	 i=-1;
			}
		}
	}
} 
*/

