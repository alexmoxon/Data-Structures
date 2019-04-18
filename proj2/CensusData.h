/**
 * @file CensusData.h   Declaration of the CensusData class.
 *
 * @author Alex Moxon
 * @date 2/14/19
 */

#ifndef CSCI_311_CENSUSDATA_H
#define CSCI_311_CENSUSDATA_H

#include <vector>
using std::ifstream;
using std::string;
using std::vector;

class CensusData {

public:
   static const int POPULATION = 0;       // type of sort
   static const int NAME = 1;
   ~CensusData();
   void initialize(ifstream&);            // reads in data
   int getSize(){return data.size();}
   void print();                          // prints out data
   void insertionSort(int);               // sorts data using insertionSort
   void mergeSort(int);                   // sorts data using mergeSort
   void quickSort(int);                   // sorts data using quickSort

private:
   class Record {                         // declaration of a Record
   
   public:
      string* city;
      string* state;
      int population;
      Record(string&, string&, int);
      ~Record();
   };

   vector<Record*> data;                  // data storage

// You may add your private helper functions here!

   bool isSmaller(int, Record*, Record*); // this is one i used-you may delete

   void quickSort(int, int, int);

   int partition(int, int, int);
   int randomPartition(int, int, int);

   void mergeSort(int, int, int);
   void merge(int, int, int, int);

};

#endif // CSCI_311_CENSUSDATA_H