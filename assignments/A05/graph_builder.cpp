///////////////////////////////////////////////////////////////////////////////
//
// Date:             13 December 2019
// Title:            Program 3 - Graphs
// Semester:         Fall 2019
// Course:           CMPS 3013 
// Assignment:       A05
// Author:           (Faith Howell)
// Email:            (fath-howell@outlook.com)
// Files:            (Json.hpp, HsonFacade.hpp,cities.json,Geo.hpp)
// Description:
//       This program reads information from a json file and uses it to create an array of  //       cities. It consists  a heap with 1000 cities. It goes throuch each city by using   //       the min heap and gets the closest cities. Then prints out in order in output.txt.
/////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include "Heap.hpp"
#include "JsonFacade.hpp"
#include "json.hpp"
#include "Geo.hpp"

using namespace std;

using json = nlohmann::json;

struct City {
	float longitude, latitude;
	long double Priority;
	string Name;
	City() {
		Priority = 0;
		Name = "";
	}
	City(json obj) {
		Name = obj["city"];
		latitude = obj["latitude"];
		longitude = obj["longitude"];
		Priority = 0;
	}
};
  float findDistance(double lat1, double log1, double lat2, double log2) {

	Coordinate Coord1(lat1, log1);

	Coordinate Coord2(lat1, log2);

	return HaversineDistance(Coord1, Coord2);

  }


int main(int argc, char *argv[]) {
  json obj;
  int max, count = 0, c=0;
	ofstream outfile;
	outfile.open("output.txt");
    City** Cities;
    City* temp;
    string filename = "cities.json";
    JsonFacade J(filename);

    ofstream out;
		out.open("output.txt");

	if (argc >= 2)
	{
		max = atoi(argv[1]);
		cout << endl << endl;
	}
	else
	{
		max= 5;
		system("pause");
		cout << endl << endl;
	}

    outfile << "Faith Howell\n";
    outfile << "Program 3 - Graphs\n";
    outfile << "13th December 2019\n";

    Heap <City> H(1000,false);

    int size = J.getSize();
    Cities = new City *[size];
    // loads an array of cities with the json data
    for (int i = 0; i < size; i++) {
        obj = J.getNext();
        Cities[i] = new City(obj);
    }

	
	for (int i = 0; i < size; i++)
	{
		count++;
		if (i < 10 || i >= size - 10)
		{
			out << setfill('0') << setw(4) << count << ":" << Cities[i]->Name << endl;


			for (int j = 0; j < size; j++)
			{
				
				Coordinate p1(Cities[i]->latitude, Cities[i]->longitude);
				Coordinate p2(Cities[j]->latitude, Cities[j]->longitude);
				Cities[j]->Priority = HaversineDistance(p1, p2);
				H.Insert(Cities[j]);
			}
			//Empty Heap
			for (int p = 0; p < size; p++)
			{
				City* temp = H.Extract();
				if (p > 0 && p < max + 1)
				{
					c++;
					out << setfill(' ') << setw(8) << " " << c << " \)"<< temp->Name << " " << temp->Priority << endl;
				}	
			}
			c = 0;

			out << endl << endl;
		}
	}
	//system("pause");
	return 0;
}
