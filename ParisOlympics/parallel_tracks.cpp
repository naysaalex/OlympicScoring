#include <iostream>
#include <iomanip>
#include <string>
#include "parallel_tracks.h"
#include <fstream>
#include <sstream>

using std::string;
using std::ifstream;


//-------------------------------------------------------
// Name: get_runner_data
// PreCondition:  the prepped parallel arrays , and a legit filename is pass
// PostCondition: all arrays contain data from the text file given
//---------------------------------------------------------
void get_runner_data( const std::string& file, double timeArray[], std::string countryArray[], 
		unsigned int numberArray[], std::string lastnameArray[]) 
{
  //TODO
	ifstream inFS;
	inFS.open(file);
	if(!inFS.is_open())
	{
		throw std::invalid_argument("Cannot open file");
	}

	for(int i=0;i<(int)SIZE;i++)
	{
		string performance;
		getline(inFS, performance);
		if(performance == "" && i!=(int)SIZE)
		{
			throw std::domain_error("File missing data");
		}
		std::stringstream ss(performance);
		double time = 0.0;
		string country = "";
		string lastname = "";
		int number = 0;
		ss>>time;
		if(ss.fail()||time<0)
		{
			throw std::domain_error("File contains invalid data (time)");
		}
		else if(ss.good())
		{
			timeArray[i] = time;
		}

		ss>>country;
		if(ss.fail())
		{
			throw std::domain_error("File contains invalid data (country)");
		}
		else if(ss.good())
		{
			
			int stringsize = country.length();
			bool check = false;
			if(stringsize!=3)
				throw std::domain_error("File contains invalid data (country)");
			for(int s = 0; s<stringsize;s++)
			{
				if((country.at(s)=='A' ||country.at(s)>'A') && (country.at(s)=='Z' || country.at(s)<'Z'))
					check = true;
				else 
				{
					check = false;
					throw std::domain_error("File contains invalid data (country)");
				}
			}
			//std::cout<<lastname;
			if(check)
				countryArray[i] = country;
		}
		ss>>number;
		if(ss.fail())
		{
			throw std::domain_error("File contains invalid data (number)");
		}
		else if(ss.good())
		{
			if(number>=0 && number<100)
				numberArray[i] = number;
			else	
				throw std::domain_error("File contains invalid data (number)");
		}
		ss>>lastname;
		// if(ss.good())
		// 	std::cout<<"good "<<lastname<<std::endl;
		// else	
		// 	std::cout<<"bad "<<lastname<<std::endl;
		if(ss.fail())
		{
			throw std::domain_error("File contains invalid data (name)");
		}
		else 
		{
			string name = trim(lastname);
			//std::cout<<name<<std::endl;
			int stringsize = name.length();
			bool check = false;
			if(stringsize<=1)
				throw std::domain_error("File contains invalid data (name)");
			for(int s = 0; s<stringsize;s++)
			{
				if((lastname.at(s)=='a' ||lastname.at(s)>'a') && (lastname.at(s)=='z' || lastname.at(s)<'z'))
					check = true;
				else if((lastname.at(s)=='A' ||lastname.at(s)>'A') && (lastname.at(s)=='Z' || lastname.at(s)<'Z'))
					check = true;
				else if(lastname.at(s)==' ')
					check = true;
				else 
				{
					check = false;
					throw std::domain_error("File contains invalid data (name)");
				}
			}
			//std::cout<<lastname;
			if(check)
				lastnameArray[i] = lastname;
		}
	}
}

//-------------------------------------------------------
// Name: prep_double_array
// PreCondition:  a double arrays is passed in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_double_array(double ary[])
// making sure all values within the array are set to 0.0;
{
  //TODO
  for(int i=0;i<(int)SIZE;i++)
  {
	  ary[i] = 0.0;
  }
}

//-------------------------------------------------------
// Name: prep_double_array
// PreCondition:  an unsigned int arrays is passed in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_unsigned_int_array(unsigned int ary[])
// making sure all values within the array are set to 0;
{
	//TODO
	for(int i=0;i<(int)SIZE;i++)
  	{
	  ary[i] = 0;
  	}
}

//-------------------------------------------------------
// Name: prep_string_array
// PreCondition:  a string arrays is pass in
// PostCondition: data in the array is "N/A" out to determine if
// a value has changed
//---------------------------------------------------------
void prep_string_array(std::string ary[])
// making sure all values within the array are set to "N/A";
{
	//TODO
	for(int i=0;i<(int)SIZE;i++)
  	{
	  ary[i] = "N/A";
  	}
}

//-------------------------------------------------------
// Name: get_ranking
// PreCondition:  just the time array is passed in, and has valid data
// PostCondition: after a very inefficient nested loop to determine the placements 
// and places the ranks in a new array. That new array is returned
//---------------------------------------------------------
void get_ranking(const double timeArray[], unsigned int rankArray[])
{
	//TODO
	for(int i=0; i<(int)SIZE;i++)
	{
		int count = 1;
		for(int j =0; j<(int)SIZE;j++)
		{
			if(j!=i && timeArray[j]<timeArray[i])
			{
				count++;
			}
		}
		rankArray[i] = count;
	}
}


//-------------------------------------------------------
// Name: print_results
// PreCondition:  almost all parallel arrays are passed in and have valid data
// PostCondition: after a very inefficient nested loop to determine the ranks
// it then displays then along with a delta in time from the start
//---------------------------------------------------------
void print_results(const double timeArray[], const std::string countryArray[],
		const std::string lastnameArray[], const unsigned int rankArray[])
{

	std::cout << "Final results!!";
	std::cout << std::setprecision(2) << std::showpoint << std::fixed << std::endl;
	double best_time = 0.0;
		
	// print the results, based on rank, but measure the time difference_type
	for(unsigned int j = 1; j <= SIZE; j++)
	{
		
		// go thru each array, find who places in "i" spot
		for(unsigned int i = 0; i < SIZE; i++)
		{
			if(rankArray[i] == 1) // has to be a better way, but need the starting time
			{
				best_time = timeArray[i];
			}
			
			
			if(rankArray[i] == j) // then display this person's data
			{
				// this needs precision display
				std::cout << "[" << j << "]  " << timeArray[i] << " " << std::setw(15) << std::left << lastnameArray[i] << "\t" << "(" << countryArray[i] << ")  +" << (timeArray[i] - best_time) << std::endl; 
			}
			
		}
	}	
}

std::string trim(std::string ret) {
	// remove whitespace from the beginning
	while (!ret.empty() && isspace(ret.at(0))) {
			ret.erase(0, 1);
		}

	// remove whitespace from the end
	//  Note: last index is (.size() - 1) due to 0 based indexing
	while (!ret.empty() && isspace(ret.at(ret.size()-1))) {
		ret.erase(ret.size()-1, 1);
	}
	
	return ret;
}