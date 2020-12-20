#include <iostream>
#include <math.h>
#include <vector>
#include "Image.h"

using namespace std;

int main(int argc, char** argv)
{
	Image img("sudoku.png");

	vector<double> kernel = {-0.016, 0.3, -0.016,
							-0.016, 0.3, -0.016,
							-0.016, 0.3, -0.016};

	img = img.convolution(&kernel);

	img.save_as("out.png");

	return 0;
}
