#pragma once

#include <SDL.h>

class Save_Load
{
public:

	//Konstructor,Destructor
	Save_Load(const int amount); // creates a new file if there's no old save, amount -> array size ()
	~Save_Load();


	void open(); // loads data, opens file
	void close(); // saves data, closes file


	void save(Sint32 Data, int number); // saves Sint32 data to mData[number]

	Sint32 getData(int number); // returns the loaded Data mData[number] 





private:

	int TOTAL_DATA;

	// the data which will be saved
	Sint32* mData;





};

