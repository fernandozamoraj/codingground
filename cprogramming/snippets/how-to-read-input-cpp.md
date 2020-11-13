## Example how to read input using c++.
This example reads in a comma separate file.
It reads the line and then it outputs it to the command line.

```cpp
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

void readFile(char* inputFileName) {

	ifstream file(inputFileName);
	string line;

	if (file.is_open())
	{
		int i = 0;

        //read first line
        //sometimes the first line has a 
        //different format than the rest of the
        //file
		getline(file, line);

        //convert line to int
		int linesAvailable = stoi(line);

		//Read until end of end of file or maxCount whichever comes first
		while (getline(file, line) && i < linesAvailable)
		{
			istringstream iss(line);


			string firstName;
			string lastName;
			string ageString;
            string battingAvgString;
			double battingAvg = 0.0;
            int age;

			getline(iss, firstName, ',');
			getline(iss, lastName, ',');
			getline(iss, ageString, ',');
			getline(iss, battingAvgString);

			age = stoi(ageString);
			battingAvg = stof(battingAvgString);

            cout << firstName;
            cout << lastName;
            cout << battingAvg;
            cout << age;
            cout << endl;

			i++;
		}
		file.close();
	}
}
```