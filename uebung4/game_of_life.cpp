#include <iostream>
#include <cstring>
#include <ctime>
#include "bitmap_image.hpp"
#include <random>
#include <ctime>

// random number in [a,b] range
inline float frand(float a, float b) {
	return a+((b-a) * (float)rand() / (float)RAND_MAX);
}

// struct handling the color coding:
struct rgb_t{
      unsigned char   red;
      unsigned char green;
      unsigned char  blue;
};

// black and white color

rgb_t white_pixel {255,255,255};
rgb_t black_pixel {0,0,0};

struct Raster {
	Raster(int w, int h) : width(w), height(h)
	{
		data = new int[width*height];
	}

	Raster(int w, int h, float seedProbability) : width(w), height(h)
	{
		float dice;
		data = new int[width*height];
		for(int i = 0; i < width*height; i++){
				dice = frand(0,1);
				data[i] = (dice <= seedProbability) ? 1 : 0;
		}
		// TODO 4.1a: Fill randomly
		// Probability of value 1 is seedProbability, otherwise value is 0
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

		// assuming there are only black or white pixels, any color value == 0 results in the pixel 
		// being white (as black == RGB(0,0,0))
		int num_white = 0;
		int num_black = 0;
		for (std::size_t y = 0; y < height; ++y){
      		for (std::size_t x = 0; x < width;++x){
         		rgb_t color;

         		image.get_pixel(x, y, color.red, color.green, color.blue);
				data[(y*width) + x] = (color.blue > 0) ? 0 : 1;
				// std::cout << color.red <<color.green <<color.blue  << std::endl;
      		}	
  		}
		// std::cout << num_white << "  ||  " << num_black << std::endl;
	}

	void save(const std::string &filename)
	{
		// TODO 4.1a: Save image by using image.set_pixel
		// Living cells should be stored as black pixels, all other pixels are white
		bitmap_image image(width, height);

		
		for (int y = 0; y < height; ++y){
      		for (int x = 0; x < width; ++x){
         		rgb_t color;
				if (data[(y*width) + x] == 0)
					image.set_pixel(x, y, 255, 255, 255);
				else
					image.set_pixel(x, y, 0, 0, 0);
				
				// std::cout << color.red <<color.green <<color.blue  << std::endl;
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
	// In case isTorus is false and (x, y) is outside of raster, return 0
	// In case isTorus is true and (x, y) is outside of raster use value of matching cell of opposite side
	
	// pixel in Raster?
	if (x > 0 && x < raster.width && y > 0 && y < raster.height)
		return raster.data[(raster.width * y) +x];

	if(isTorus){
		if ( x >= raster.width)
        	x -= raster.width;
		if (x < 0)
			x += raster.width;
		if (y >= raster.height)
			y -= raster.height;
		if (y < 0)
			y += raster.height;
		return raster.data[(raster.width * y) +x];
	}
	// Wenn Pixel nicht im Raster liegt und Torus deaktiviert ist:
	return 0;
}

void simulateInversion(Raster &raster, float inversionFactor)
{
	if (inversionFactor <= 0)
	{
		return;
	}
	
	float dice;

	for(int i = 0; i < raster.width * raster.height; i++){
		dice = frand(0,1);
		if(dice <= inversionFactor)
			raster.data[i] ^= 1;
	}
	// TODO 4.1c: Flip some cells randomly (probability to flip for each cell is inversionFactor)
}


// returns the amount of alive neighbours in 3 x 3 circumfence
int aliveNeighborCount(const Raster &raster, int x, int y, bool isTorus) {
    int count = 0;
    if (raster.data[(y * raster.width)+x])
        count -= 1;
    for(int check_x = x -1; check_x <= x +1 ; check_x++ ){
        for(int check_y =y -1; check_y <= y +1 ; check_y++ ){
        	count += cellValue(raster, check_x, check_y, isTorus);
        }
    }
    return count;
}

int shouldBeAlive(const Raster &raster, int x, int y, bool isTorus) {
    int nachbarn = aliveNeighborCount(raster, x, y, isTorus);
    if(raster.data[(y*raster.width) + x]){
        if ((nachbarn >= 2) && (nachbarn < 4))
            return 1;
        return 0;
    }else if ( nachbarn == 3)
        return 1;
    return 0;
}

void simulateNextState(Raster &raster, bool isTorus)
{
	// TODO 4.1b: Play one iteration of Game of Life
	// Array for saving our new cell states:
	int * data = (int *)malloc(sizeof(int)*raster.height*raster.width);
	
	for(int y = 0; y < raster.height; y++){
		for(int x = 0; x < raster.width; x++){
			data[(y*raster.width)+x] = shouldBeAlive(raster, x, y, isTorus);
		}
	}
	
	// write new data into Raster struct
	for(int i = 0; i < raster.width * raster.height; i++)
		raster.data[i] = data[i];
	free(data);
}

int main(int argc, char* argv[])
{
	Raster* raster = nullptr;

	// TODO 4.1a: Initialize random seed
	srand (time(NULL));

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
