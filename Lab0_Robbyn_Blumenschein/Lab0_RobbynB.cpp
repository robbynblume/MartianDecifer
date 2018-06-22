/*	Implement an algorithm (using classes) to convert Degrees to ASCII codes.
	Implementan algorithm to find and store all the numeric values in a line of text.This algorithm should work on any text file (i.e. your implementation should not be specific to the AsciiDegrees.csv file).
	Minimize the number of IF statements in your program.Too many IF statements often indicate an inefficient implementation.
	Do not use advanced C++ features like <Regex>, <Map> however<vector> is ok.
	Do not use arrays unless no alternative is available.*/
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <list>
using namespace std;

vector<float> * readFloatPairsFromFile(string filename);

class DegreeEncodedMessageParser
{
private:
	bool haveNibble = false; // A nibble is half a byte/char
	unsigned char currentChar;
	vector<char> result;	
	unsigned int convertDegreeToNibble(float const degrees);

public:
	DegreeEncodedMessageParser();
	void feedAngle(float const degree);
	void feedAngles(vector<float> * degrees);
	string parseMessage();
	~DegreeEncodedMessageParser();
};


int main()
{
	DegreeEncodedMessageParser encode;
	encode.feedAngles(readFloatPairsFromFile("AsciiDegrees.csv"));
	
	cout << encode.parseMessage() <<endl;

	system("pause");
	return 0;
}
//this operator overloads the >> to push info into a float vector
istream& operator>> (istream& in, vector<float>* v) {
    float f;
	in >> f;
	while (in.fail())
	{
		if (in.eof())
		{
			return in;
		}
		in.clear();
		in.ignore();
		in >> f;  
		
    }
	v->push_back(f);
    return in;
	}


DegreeEncodedMessageParser::DegreeEncodedMessageParser(){}

unsigned int DegreeEncodedMessageParser::convertDegreeToNibble(float const degrees)
{
	return (unsigned int)(degrees / (360. / 16)) % 16;
}

void DegreeEncodedMessageParser::feedAngle(float const degree)
{
	if (!haveNibble) {
		currentChar = convertDegreeToNibble(degree) << 4;
		haveNibble = true;
		return;
	}
	currentChar += convertDegreeToNibble(degree);
	haveNibble = false;
	result.push_back(currentChar);

}
void DegreeEncodedMessageParser::feedAngles(vector<float> * v)
{
	for (vector<float>::iterator it = v->begin(); it != v->end(); ++it) 
	{ 
		feedAngle(*it);
	}
}
string DegreeEncodedMessageParser::parseMessage(){
	string message(result.begin(), result.end());
	return message;
}
 DegreeEncodedMessageParser::~DegreeEncodedMessageParser(){}

 vector<float> * readFloatPairsFromFile(string filename)
 {
	 ifstream file(filename); // declare file stream: http://www.cplusplus.com/reference/iostream/ifstream/
	 vector<float> *values = new vector<float>();
	 while (file.good())
	 {
		 file >> values; //this uses the shift operator overload 

	 }
	 return values;
 }
  