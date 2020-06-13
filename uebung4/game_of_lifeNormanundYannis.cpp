#include <iostream>
#include <cstring>
#include <ctime>
#include "bitmap_image.hpp"



struct Raster {
	Raster(int w, int h) : width(w), height(h)
	{
		data = new int[width*height];
	}

	Raster(int w, int h, float seedProbability) : width(w), height(h)
	{
		data = new int[width*height];

			// TODO 4.1a: Fill randomly
			// Probability of value 1 is seedProbability, otherwise value is 0
			for (int i = 0; i < w * h; i++)
			{
				double r = ((double) rand() / (RAND_MAX )) ;
				std::cout << std::to_string(r);

				if (r < seedProbability)
				{
					data[i] = 1;
				}else{
					data[i] = 0;
				}
			}		
	}

	Raster(const std::string &filename)
	{
		bitmap_image image(filename);

		if (!image)
		{
			std::cerr << "Could not open bitmap!" << std::endl;
		}

		height = image.height();
		width = image.width();

		data = new int[width*height];

		// TODO 4.1a: Load image by using image.get_pixel
		// A black pixel represents 1, all other values represent 0

		unsigned char r;
		unsigned char g;
		unsigned char b;

		int x = 0;
		int y = 0;

		for (int i = 0; i < width * height; i++){			
			image.get_pixel(x, y, r, g ,b);
				if ((int)r == 0 && (int)g == 0 && (int)b == 0)
				{
					data[i] = 1;
				}else{
					data[i] = 0;
				}
			if(x<width-1){
				x++;
			}else{
				x = 0;
				y++;
			}
		}


		//NICE DEBUG FUNCTION
		int i = 0;
		std::cout << "Our Array: \n";
		for (int j = 1; j < height+1; j++)
		{
			for(i; i < width*j; i++){
				std::cout << std::to_string(data[i]);
			}
			std::cout << "\n";

		}
	}

	void save(const std::string &filename)
	{
		// TODO 4.1a: Save image by using image.set_pixel
		// Living cells should be stored as black pixels, all other pixels are white
		bitmap_image image(width, height);

		int x = 0;
		int y = 0;

		for (int i = 0; i < width * height; i++){			
				if (data[i] == 0)
				{
					image.set_pixel(x,y, 255,255,255);
				}else{
					image.set_pixel(x,y, 0,0,0);
				}
			if(x<width-1){
				x++;
			}else{
				x = 0;
				y++;
			}
		}

		image.save_image(filename);
	}

	~Raster()
	{
		delete[] data;
	}

	int width;
	int height;
	int* data;
};

// This struct parses all necessary command line parameters. It is already complete and doesn't have to be modified. However - feel free to add support for additional arguments if you like.
struct CommandLineParameter
{
	CommandLineParameter(int argc, char* argv[])
		: width(0)
		, height(0)
		, inversionFactor(0)
		, isTorus(false)
		, maxIterations(20)
	{
		if (argc % 2 == 0)
		{
			std::cerr << "Missing value for " << argv[argc - 1] << std::endl;
			argc--;
		}

		for (int i = 1; i < argc; i += 2)
		{
			if (!strcmp(argv[i], "-w"))
			{
				width = atoi(argv[i + 1]);
			}
			else if (!strcmp(argv[i], "-h"))
			{
				height = atoi(argv[i + 1]);
			}
			else if (!strcmp(argv[i], "-s"))
			{
				seedProbability = static_cast<float>(atof(argv[i + 1]));
			}
			else if (!strcmp(argv[i], "-p"))
			{
				patternFilename = argv[i + 1];
			}
			else if (!strcmp(argv[i], "-o"))
			{
				outputDirectory = argv[i + 1];
			}
			else if (!strcmp(argv[i], "-iv"))
			{
				inversionFactor = static_cast<float>(atof(argv[i + 1]));
			}
			else if (!strcmp(argv[i], "-t"))
			{
				isTorus = strcmp(argv[i + 1], "0") != 0;
			}
			else if (!strcmp(argv[i], "-i"))
			{
				maxIterations = atoi(argv[i + 1]);
			}
		}

		if ((width != 0 || height != 0) && !patternFilename.empty())
		{
			std::cout << "Width and height are ignored, because pattern is defined." << std::endl;
		}

		if (width < 0 || height < 0)
		{
			std::cerr << "Width or height has a invalid value." << std::endl;
			width = 0;
			height = 0;
		}
	}

	int width;
	int height;
	float seedProbability;
	std::string patternFilename;
	std::string outputDirectory;
	float inversionFactor;
	bool isTorus;
	int maxIterations;
};

int cellValue(const Raster &raster, int x, int y, bool isTorus)
{
	// TODO 4.1b: Return whether cell is alive (1) or not (0)
	// In case isTorus is false and (x, y) is outside of raster, return 0                                          DONE
	// In case isTorus is true and (x, y) is outside of raster use value of matching cell of opposite side

	
	if(isTorus){

	}else{
		//Check if outside of boundaries
		if(x < 0 || y < 0 || x > raster.width-1 || y > raster.height-1){
			return 0;
		}

		return raster.data[x+(y*raster.width)];
	}

	return 0;
}

void simulateInversion(Raster &raster, float inversionFactor)
{
	if (inversionFactor <= 0)
	{
		return;
	}

	// TODO 4.1c: Flip some cells randomly (probability to flip for each cell is inversionFactor)
}

void simulateNextState(Raster &raster, bool isTorus)
{
	// TODO 4.1b: Play one iteration of Game of Life
	
	int x = 0;
	int y = 0;

	for (int i = 0; i < raster.height * raster.width ; i++){
		int alive_neighbour_count = 0;

		//upper row
		alive_neighbour_count = alive_neighbour_count + cellValue(raster, x-1, y-1, isTorus); //Sollte stimmen
		alive_neighbour_count = alive_neighbour_count + cellValue(raster, x, y-1, isTorus); //Sollte stimmen
		alive_neighbour_count = alive_neighbour_count + cellValue(raster, x+1, y-1, isTorus); //Sollte stimmen

		//same row
		alive_neighbour_count = alive_neighbour_count + cellValue(raster, x-1, y, isTorus); //Sollte stimmen
		alive_neighbour_count = alive_neighbour_count + cellValue(raster, x+1, y, isTorus);	// Sollte stimmen

		//lower row
		alive_neighbour_count = alive_neighbour_count + cellValue(raster, x-1, y+1, isTorus); //Sollte stimmen
		alive_neighbour_count = alive_neighbour_count + cellValue(raster, x, y+1, isTorus); // Sollte stimmen
		alive_neighbour_count = alive_neighbour_count + cellValue(raster, x+1, y+1, isTorus);

		if(x<raster.width-1){
			x++;
		}else{
			x = 0;
			y++;
		}

		std::cout << "CellNumber: " << std::to_string(i) << " Alive Count: "<< std::to_string(alive_neighbour_count);

		//Hier die ganzen Regeln implementieren
		if(raster.data[i]){
			if(alive_neighbour_count < 2 || alive_neighbour_count > 3){
				raster.data[i] = 0;
			}
		}else{
			if(alive_neighbour_count == 3){
				raster.data[i] = 1; //Gets alived. Perfect english. Nice. 69. Nice.
			}
		}

	}

	
}

int main(int argc, char* argv[])
{
	Raster* raster = nullptr;

	// TODO 4.1a: Initialize random seed
	srand(time(NULL));

	CommandLineParameter cmd(argc, argv);
	if (!cmd.patternFilename.empty())
	{
		raster = new Raster(cmd.patternFilename);
	}
	else
	{
		raster = new Raster(cmd.width, cmd.height, cmd.seedProbability);
	}

	for (int iteration = 0; iteration <= cmd.maxIterations; iteration++)
	{
		raster->save(cmd.outputDirectory + "game_of_life_" + std::to_string(iteration) + ".bmp");
		simulateInversion(*raster, cmd.inversionFactor);
		simulateNextState(*raster, cmd.isTorus);
	}

	delete raster;

	return 0;
}
