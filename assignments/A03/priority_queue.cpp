/*
Name: FaitH Howell
Date: October 4th, 2019
Dr. Terry Griffin
Advanced AlgoritHm and Data structures
Assignment #3

This program uses a binary animalheap to create a prioty queue. It reads information from a json file and stores the information into an array. After tHe priority is calculated, the values will be placed into max animalheaps wHere the order is based on calculation. These values will be Held in a bucket. At the end, the top 5 Animals of each bucket will be printed.
*/

#include "json_helper.cpp"
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

#define _USE_MATH_DEFINES

#include <math.h>

using namespace std;

// Used to calculate Halversine Distance
const static double EarthRadiusKm = 6372.8;

inline double DegreeToRadian(double angle) {
    return 3.14 * angle / 180.0;
}

// This function will take in a latitude and longitude and turn them
// into a cooridinate point
class Coordinate {
public:
    Coordinate(double latitude, double longitude) : myLatitude(latitude), myLongitude(longitude) {}

    double Latitude() const {
        return myLatitude;
    }

    double Longitude() const {
        return myLongitude;
    }

private:
    double myLatitude;
    double myLongitude;
};

// This function is used to compute the Haversine Distance between
// two coordinate objects. This distance will then be used
// to help calculate the priority
double HaversineDistance(const Coordinate &p1, const Coordinate &p2) {
    double latRad1 = DegreeToRadian(p1.Latitude());
    double latRad2 = DegreeToRadian(p2.Latitude());
    double lonRad1 = DegreeToRadian(p1.Longitude());
    double lonRad2 = DegreeToRadian(p2.Longitude());

    double diffLa = latRad2 - latRad1;
    double doffLo = lonRad2 - lonRad1;

    double computation = asin(sqrt(sin(diffLa / 2) * sin(diffLa / 2) 
    + cos(latRad1) * cos(latRad2) * sin(doffLo / 2) * sin(doffLo / 2)));
    return 2 * EarthRadiusKm * computation;
}

float getPriority(string animal_name, double lat, double lon, 
float adj, bool val)
{
    Coordinate c1(33.9137, -98.4934);
    Coordinate c2(lat, lon);
    double distance;
    float priority;

    distance = HaversineDistance(c1, c2);

    int Length = animal_name.length();
    
    priority = (EarthRadiusKm - distance) * adj / Length;

    if(val == true)
    {
        priority = 1 / priority;
    }

    return priority;
}

struct Animal {
    string animal_name;
    long date;
    double latitude;
    double longitude;
    float adjuster;
    bool validated;
    string version;
    float priority;

    // Default Constructor
    Animal() {
        animal_name = "";
        date = 0;
        latitude = 0.0;
        longitude = 0.0;
        adjuster = 0.0;
        validated = 0;
        version = "";
        priority = 0.0;
    }

    Animal(string name, long _date, double lat, double lon, float adj, bool val, string ver) {
        animal_name = name;
        date = _date;
        latitude = lat;
        longitude = lon;
        adjuster = adj;
        validated = val;
        version = ver;
        priority = 0.0;
    }

    Animal(json j) {
        animal_name = j["animal_name"];
        date = j["date"];
        latitude = j["latitude"];
        longitude = j["longitude"];
        adjuster = j["adjuster"];
        validated = j["validated"];
        version = j["version"];
        priority = getPriority(animal_name, latitude, longitude, adjuster, validated);
    }
};

class AnimalHelper {
private:
    Animal **Animals;
    JsonHelper *J;
    json obj;
    int size;

public:
    AnimalHelper(string filename) {
        J = new JsonHelper(filename);
        size = J->getSize();
        Animals = new Animal *[size];
        for (int i = 0; i < size; i++) {
            obj = J->getNext();
            Animals[i] = new Animal(obj);
        }
    }


    // This function will print out the data that is read in from
    // animals.json.
    void PrintAnimals() {

        for (int i = 0; i < size; i++) {

            cout << Animals[i]->animal_name << " " 
            << Animals[i]->latitude << " " 
            << Animals[i]->longitude << " " 
            << Animals[i]->date << " " 
            << Animals[i]->adjuster << " " 
            << Animals[i]->validated << " " 
            << Animals[i]->version << " "
            << Animals[i]->priority << endl;

        }
    }

    // Points to an animal
    Animal * getAnimals(int i)
    {
        return Animals[i];
    }

    long getDate(int i)
    {
        return Animals[i]->date;
    }
};

class Heap{
private:
    Animal **animalheap;
    int size;
    int end;

    // Parent Node
    int Parent(int i)
    {
        return i / 2;
    }

    // Current Node's Left Child
    int LeftChild(int i)
    {
        return i * 2;
    }

    // Current Node's Right Child
    int RightChild(int i)
    {
        return i * 2 + 1;
    }

public:
    Heap()
    {
        size = 1000;
        animalheap = new Animal *[size];
        animalheap[0]->priority = INT32_MAX; 
        end = 0;
       
    }

    void Insert(Animal * ani)
    {
        animalheap[++end] = ani;
        BubbleUp();
    }

    void BubbleUp()
    {
        int i = end;
        Animal *temp;

        while(animalheap[Parent(i)]->priority < animalheap[i]->priority)
        {
            temp = animalheap[Parent(i)];
            animalheap[Parent(i)] = animalheap[i];
            animalheap[i] = temp;
            i = Parent(i);
        }
    }

    int LrgestChild(int i)
    {
        int largest = 0;

        if(2 * i > end)
        {
            return -1;
        }
        if(animalheap[2 * i]->priority > animalheap[2 * i + 1]->priority)
        {
      
            if(animalheap[i]->priority < animalheap[2 * i]->priority)
            {
                return 2 * i;
            }
    
            else
            {
                return -1;
            }
        }
        else
        {
            if(animalheap[i]->priority < animalheap[2 * i + 1]->priority)
            {
                return 2 * i + 1;
            }
            else
            {
                return -1;
            }
        }
        
    }


    void swap(int i, int j)
    {
        Animal *temp = animalheap[i];
        animalheap[i] = animalheap[j];
        animalheap[j] = temp;

    }

 
    void BubbleDown(int i)
    {
        int x = LrgestChild(i);

        if(x < 0)
        {
            return;
        }

        if(x != -1)
        {
            swap(i, x);
            BubbleDown(x);
        }
    }

    void Heapify()
    {
        int i = (end - 1) / 2;
        for(int j = i; j >= 1; j--)
        { 
            BubbleDown(j);
        }
    }

    
    void Print(ofstream & outfile)
    {
        for(int i = 1; i <= 5; i++)
        {
              outfile << animalheap[i]->animal_name << " " 
            << animalheap[i]->priority << "\n";
        }
    }


   
};

int main(int argc, char **argv) {

    ofstream outfile;
    outfile.open("Faith Howell Output.txt");
    outfile<<"Faith Howell\n";

    AnimalHelper AH("animals.json");
 
    int number_of_buckets = 5;

    Heap** Buckets = new Heap*[number_of_buckets];

    // Create the number of buckets required
    for(int i = 0; i < number_of_buckets; i++)
    {
        Buckets[i] = new Heap;
    }

    for (int i = 0; i < 500; i++)
    {
    int buck = abs(AH.getDate(i)) % number_of_buckets;
    
    Buckets[buck]->Insert(AH.getAnimals(i));
    }

    for(int i = 0; i < number_of_buckets; i++)
    {
        Buckets[i]->Heapify();
    }

    outfile << "\n\n";
    for(int i = 0; i < number_of_buckets; i++)
    {
        outfile << "Heap " << i << endl;
        outfile << "======================\n";
        Buckets[i]->Print(outfile);
    }
       outfile << "\n\n";

    outfile.close();
    return 0;
}
