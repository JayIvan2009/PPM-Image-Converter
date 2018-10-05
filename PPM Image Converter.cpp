#include <iostream>
#include <string>
#include <fstream>
#include <istream>
#include <stdlib.h>

using namespace std;

class Image {
public:
	Image() {													// deallocates 'colors' memory				
		colors = nullptr; };
	~Image() {
	};

	void menu(Image &img) {																// menu function
		ifstream inFile;
		ofstream outFile;
		string inName, outName;
		bool menu = true;

		while (menu) {															// menu loop
			cout << "Portable Pixmap (PPM) Image Modder by Jay Ivan Gentallan" << endl << endl;

			cout << "Enter image file name: ";
			cin >> inName;														// gets input for inName

			inFile.open(inName + ".ppm");										// opens up inFile file

			if (!inFile) {														// makes sure file exists
				cout << "File not found! Please try again." << endl << endl;
				continue;
			}

			cout << endl << "Loading..." << endl << endl;

			inFile >> img;														// extracts file data and passes it to class istream& operator

			inFile.close();														// closes inFile

			cout << "Enter output image file name: ";
			cin >> outName;														// gets input for outName
			cout << endl;

			cin.get();

			img.options();														// opens options menu

			outFile.open(outName + ".ppm");										// creates outFile
			outFile << img;														// file data is passed through class ostream& operator and put into outFile
			outFile.close();													// closes file

			bool again = true;
			char input;

			while (again) {														// again loop
				cout << "Do you want to try again? Y/N" << endl;
				cin >> input;
				cout << endl;

				delete[] colors;
				colors = nullptr;

				switch (input) {
				case 'y':
				case 'Y': again = false;
					continue;
				case 'n':
				case 'N': again = false;
					menu = false;
					break;
				default: cout << endl << "Invalid input. Please try again!" << endl;
					break;
				}
			}
		}
	};

	void options() {															// options function
		int input;
		bool again = true;
		float i = 0;

		cout << "Image Processing Choices:" << endl;
		cout << "1. Convert to grayscale" << endl;
		cout << "2. Invert red" << endl;
		cout << "3. Invert green" << endl;
		cout << "4. Invert blue" << endl;
		cout << "5. Invert all" << endl;
		cout << "6. Add noise" << endl;
		cout << "7. Remove a color" << endl;
		cout << "8. Adjust contrast" << endl;
		cout << "9. Adjust brightness" << endl;

		cout << "Enter choice: ";
		cin >> input;

		switch (input) {
		case 1:
			grayscale();																// calls in grayscale function
			break;

		case 2:
			red();																		// calls in red function
			break;

		case 3:
			green();																	// calls in green function
			break;

		case 4:
			blue();																		// calls in blue function
			break;

		case 5:
			invert();																	// calls in invert function
			break;

		case 6:
			while (again) {																// while loop to make sure user inputs valid input
				cout << endl << "How much noise do you want? (0 to 100%)" << endl;
				cin >> i;
				if (i < 0 || i > 100) {
					cout << endl << "Invalid input. Please try again!" << endl;
				}
				else {
					i / 100;
					again = false;
					noise(i);															// calls in noise function with float i in parameter
				}
			}
			break;

		case 7:
			while (again) {																// while loop to make sure user inputs valid input
				cout << endl << "Which color do you want to remove?" << endl;
				cout << "1. Red" << endl;
				cout << "2. Green" << endl;
				cout << "3. Blue" << endl;
				cin >> input;
				if (input < 1 || input > 3) {
					cout << "Invalid input! Please try again." << endl;
					continue;
				}
				else {
					again = false;
					remove(input);														// calls in remove function with int input in parameter
				}
			}
			break;

		case 8:
			while (again) {																// while loop to make sure user inputs valid input
				cout << endl << "How much contrast do you want? (-100% to 100%)" << endl;
				cin >> i;
				if (i < -100 || i > 100) {
					cout << endl << "Invalid input. Please try again!" << endl;
				}
				else {
					i / 100;
					again = false;
					contrast(i);														// calls in contrast function with float i in parameter
				}
			}
			break;

		case 9:
			while (again) {																// while loop to make sure user inputs valid input
				cout << endl << "How much brightness do you want? (-100% to 100%)" << endl;
				cin >> i;
				if (i < -100 || i > 100) {
					cout << endl << "Invalid input. Please try again!" << endl;
				}
				else {
					i / 100 * 255;
					again = false;
					brightness(i);														// calls in contrast function with float i in parameter
				}
			}
			break;

		default:
			cout << endl << "Choice not found. Please try again!" << endl << endl;		// if invalid input, ask user to enter again
			cin >> input;
		}
		return;
	};

	void grayscale() {
		int *init, *reset;
		int oldRed, oldGreen, oldBlue, newRed, newGreen, newBlue;

		reset = colors;																	// keep track of initial pointer position

		for (int i = 0; i < width * height; i++) {
			init = colors;																// keep track of initial color values

			oldRed = *colors;
			colors++;
			oldGreen = *colors;
			colors++;
			oldBlue = *colors;

			newRed = (oldRed * 0.299) + (oldGreen * 0.587) + (oldBlue * 0.114);			// changes value of red pixel
			newGreen = (oldRed * 0.299) + (oldGreen * 0.587) + (oldBlue * 0.114);		// changes value of green pixel
			newBlue = (oldRed * 0.299) + (oldGreen * 0.587) + (oldBlue * 0.114);		// changes value of blue pixel

			colors = init;																// resets color values
			*colors = newRed;															// puts new red value to pointer colors
			colors++;
			*colors = newGreen;															// puts new green value to pointer colors
			colors++;
			*colors = newBlue;															// puts new blue value to pointer colors
			colors++;
		}
		colors = reset;																	// reset pointer position

		cout << endl << "Loading..." << endl << endl;
	};

	void red() {
		int *init, *reset;
		int oldRed, oldGreen, oldBlue, newRed, newGreen, newBlue;

		reset = colors;																	// keep track of initial pointer position

		for (int i = 0; i < width * height; i++) {
			init = colors;																// keep track of initial color values

			oldRed = *colors;
			colors++;
			oldGreen = *colors;
			colors++;
			oldBlue = *colors;

			newRed = (255 - oldRed);													// changes value of red pixel
			newGreen = oldGreen;														// keeps value of green pixel
			newBlue = oldBlue;															// keeps value of blue pixel

			colors = init;																// resets color values
			*colors = newRed;															// puts new red value to pointer colors
			colors++;
			*colors = newGreen;															// puts new green value to pointer colors
			colors++;
			*colors = newBlue;															// puts new blue value to pointer colors
			colors++;
		}
		colors = reset;																	// reset pointer position

		cout << endl << "Loading..." << endl << endl;
	};

	void green() {
		int *init, *reset;
		int oldRed, oldGreen, oldBlue, newRed, newGreen, newBlue;

		reset = colors;																	// keep track of initial pointer position

		for (int i = 0; i < width * height; i++) {
			init = colors;																// keep track of initial color values

			oldRed = *colors;
			colors++;
			oldGreen = *colors;
			colors++;
			oldBlue = *colors;

			newRed = oldRed;															// keeps value of red pixel
			newGreen = (255 - oldGreen);												// changes value of green pixel
			newBlue = oldBlue;															// keeps value of blue pixel

			colors = init;																// resets color values
			*colors = newRed;															// puts new red value to pointer colors
			colors++;
			*colors = newGreen;															// puts new green value to pointer colors
			colors++;
			*colors = newBlue;															// puts new blue value to pointer colors
			colors++;
		}
		colors = reset; 																// reset pointer position

		cout << endl << "Loading..." << endl << endl;
	};

	void blue() {
		int *init, *reset;
		int oldRed, oldGreen, oldBlue, newRed, newGreen, newBlue;

		reset = colors;																	// keep track of initial pointer position

		for (int i = 0; i < width * height; i++) {
			init = colors;																// keep track of initial color values

			oldRed = *colors;
			*colors++;
			oldGreen = *colors;
			*colors++;
			oldBlue = *colors;

			newRed = oldRed;															// keeps value of red pixel
			newGreen = oldGreen;														// keeps value of green pixel
			newBlue = (255 - oldBlue);													// changes value of blue pixel

			colors = init;																// resets color values
			*colors = newRed;															// puts new red value to pointer colors
			colors++;
			*colors = newGreen;															// puts new green value to pointer colors
			colors++;
			*colors = newBlue;															// puts new blue value to pointer colors
			colors++;
		}
		colors = reset; 																// reset pointer position

		cout << endl << "Loading..." << endl << endl;
	};

	void invert() {
		int *init, *reset;
		int oldRed, oldGreen, oldBlue, newRed, newGreen, newBlue;

		reset = colors;																	// keep track of initial pointer position

		for (int i = 0; i < width * height; i++) {
			init = colors;																// keep track of initial color values

			oldRed = *colors;
			colors++;
			oldGreen = *colors;
			colors++;
			oldBlue = *colors;

			newRed = (255 - oldRed);													// changes value of blue pixel
			newGreen = (255 - oldGreen);												// changes value of blue pixel
			newBlue = (255 - oldBlue);													// changes value of blue pixel

			colors = init;																// resets color values
			*colors = newRed;															// puts new red value to pointer colors
			colors++;
			*colors = newGreen;															// puts new green value to pointer colors
			colors++;
			*colors = newBlue;															// puts new blue value to pointer colors
			colors++;
		}
		colors = reset; 																// reset pointer position

		cout << endl << "Loading..." << endl << endl;
	};

	double randNoise() {																// function to return a random value
		return (rand() / (float)0x7fff) - 0.5;
	};

	void noise(float noise) {
		int *init, *reset;
		int oldRed, oldGreen, oldBlue, newRed, newGreen, newBlue;

		reset = colors;																	// keep track of initial pointer position

		for (int i = 0; i < width * height; i++) {
			init = colors;																// keep track of initial color values

			int rnoise = (char)((randNoise())*noise);

			oldRed = *colors;
			colors++;
			oldGreen = *colors;
			colors++;
			oldBlue = *colors;

			newRed = oldRed + rnoise;													// adds noise to red pixel
			if (newRed < 0) {															// makes sure pixel doesn't go under 0
				newRed = 0;
			}
			if (newRed > 255) {															// makes sure pixel doesn't go above 255
				newRed = 255;
			}

			newGreen = oldGreen + rnoise;												// adds noise to green pixel
			if (newGreen < 0) {															// makes sure pixel doesn't go under 0
				newGreen = 0;
			}
			if (newGreen > 255) {														// makes sure pixel doesn't go above 255
				newGreen = 255;
			}

			newBlue = oldBlue + rnoise;													// adds noise to blue pixel
			if (newBlue < 0) {															// makes sure pixel doesn't go under 0
				newBlue = 0;
			}
			if (newBlue > 255) {														// makes sure pixel doesn't go above 255
				newBlue = 255;
			}

			colors = init;																// resets color values
			*colors = newRed;															// puts new red value to pointer colors
			colors++;
			*colors = newGreen;															// puts new green value to pointer colors
			colors++;
			*colors = newBlue;															// puts new blue value to pointer colors
			colors++;
		}
		colors = reset; 																// reset pointer position

		cout << endl << "Loading..." << endl << endl;
	};

	void remove(int input) {
		int *init, *reset;
		int oldRed, oldGreen, oldBlue, newRed, newGreen, newBlue;

		reset = colors;																	// keep track of initial pointer position

		for (int i = 0; i < width * height; i++) {
			init = colors;																// keep track of initial color values

			oldRed = *colors;
			*colors++;
			oldGreen = *colors;
			*colors++;
			oldBlue = *colors;

			switch (input) {
			case 1:
				newRed = oldRed * 0;													// sets red pixel value to 0
				newGreen = oldGreen;
				newBlue = oldBlue;
				break;
			case 2:
				newRed = oldRed;
				newGreen = oldGreen * 0;												// sets red green value to 0
				newBlue = oldBlue;
				break;
			case 3:
				newRed = oldRed;														// sets red blue value to 0
				newGreen = oldGreen;
				newBlue = oldBlue * 0;
				break;
			}

			colors = init;																// resets color values
			*colors = newRed;															// puts new red value to pointer colors
			colors++;
			*colors = newGreen;															// puts new green value to pointer colors
			colors++;
			*colors = newBlue;															// puts new blue value to pointer colors
			colors++;
		}
		colors = reset; 																// reset pointer position

		cout << endl << "Loading..." << endl << endl;
	};

	void contrast(float val) {
		int *init, *reset;
		int oldRed, oldGreen, oldBlue, newRed, newGreen, newBlue;
		float con = (259 * (val + 255)) / (255 * (259 - val));							// contrast formula

		reset = colors;																	// keep track of initial pointer position

		for (int i = 0; i < width * height; i++) {
			init = colors;																// keep track of initial color values
			oldRed = *colors;
			colors++;
			oldGreen = *colors;
			colors++;
			oldBlue = *colors;

			newRed = con * (oldRed - 128) + 128;										// adds the contrast formula to the red pixel
			if (newRed < 0) {															// makes sure pixel doesn't go under 0
				newRed = 0;
			}
			if (newRed > 255) {															// makes sure pixel doesn't go above 255
				newRed = 255;
			}

			newGreen = con * (oldGreen - 128) + 128;
			if (newGreen < 0) {															// makes sure pixel doesn't go under 0
				newGreen = 0;
			}
			if (newGreen > 255) {														// makes sure pixel doesn't go above 255
				newGreen = 255;
			}

			newBlue = con * (oldBlue - 128) + 128;
			if (newBlue < 0) {															// makes sure pixel doesn't go under 0
				newBlue = 0;
			}
			if (newBlue > 255) {														// makes sure pixel doesn't go above 255
				newBlue = 255;
			}

			colors = init;																// resets color values
			*colors = newRed;															// puts new red value to pointer colors
			colors++;
			*colors = newGreen;															// puts new green value to pointer colors
			colors++;
			*colors = newBlue;															// puts new blue value to pointer colors
			colors++;
		}
		colors = reset; 																// reset pointer position

		cout << endl << "Loading..." << endl << endl;
	};

	void brightness(float val) {
		int *init, *reset;
		int oldRed, oldGreen, oldBlue, newRed, newGreen, newBlue;

		reset = colors;																	// keep track of initial pointer position

		for (int i = 0; i < width * height; i++) {
			init = colors;																// keep track of initial color values
			oldRed = *colors;
			colors++;
			oldGreen = *colors;
			colors++;
			oldBlue = *colors;

			newRed = oldRed + val;														// adds brightness value to red pixel
			if (newRed < 0) {															// makes sure pixel doesn't go under 0
				newRed = 0;
			}
			if (newRed > 255) {															// makes sure pixel doesn't go above 255
				newRed = 255;
			}

			newGreen = oldGreen + val;													// adds brightness value to red pixel
			if (newGreen < 0) {															// makes sure pixel doesn't go under 0
				newGreen = 0;
			}
			if (newGreen > 255) {														// makes sure pixel doesn't go above 255
				newGreen = 255;
			}

			newBlue = oldBlue + val;
			if (newBlue < 0) {															// makes sure pixel doesn't go under 0
				newBlue = 0;
			}
			if (newBlue > 255) {														// makes sure pixel doesn't go above 255
				newBlue = 255;
			}

			colors = init;																// resets color values
			*colors = newRed;															// puts new red value to pointer colors
			colors++;
			*colors = newGreen;															// puts new green value to pointer colors
			colors++;
			*colors = newBlue;															// puts new blue value to pointer colors
			colors++;
		}
		colors = reset; 																// reset pointer position

		cout << endl << "Loading..." << endl << endl;
	};

	friend istream& operator >>(ifstream& inFile, Image& img) {							// gets called once inFile is streamed into the class img
		string fileName, myString;
		char dump;

		inFile >> img.type;																// extracts type from file

		inFile >> myString;																// extracts width from file and puts it into the private width member
		img.width = stoi(myString.c_str());

		inFile >> myString;																// extracts height from file and puts it into the private height member
		img.height = stoi(myString.c_str());

		inFile >> myString;																// extracts max color value from file and puts it into the private maxColor member
		img.maxColor = stoi(myString.c_str());

		if (img.height > 1000 || img.width > 1000) {									// makes sure image file isn't bigger than 1000 on both dimensions
			cout << "Image is too big! Please use another one." << endl;
			img.menu(img);
		}

		int size = img.width * img.height * 3;											// this means height and width times 3 bytes

		img.colors = new int[size];
		img.reset = img.colors;															// set initial pointer for colors

		inFile.read(&dump, 1);															// ignore newline
		for (int i = 0; i < size; i++) {												// loops image file to extract each pixel data
			inFile >> *img.colors;
			*++img.colors;
		}
		cout << "Completed!" << endl << endl;

		img.colors = img.reset;															// reset pointer location

		return inFile;
	};

	friend ostream& operator <<(ofstream& outFile, Image& img) {						// gets called once img is streamed out into outFile
		int size = img.width * img.height * 3;											// this means height and width times 3 bytes
		int *reset;

		reset = img.colors;

		outFile << img.type << '\n' << img.width << ' ' << img.height << '\n' << img.maxColor << '\n';		// puts the headers into the outFile
		for (int i = 0; i < size; i++) {												// loops colors and puts it into outFile
			outFile << *img.colors << " ";
			*++img.colors;
		}

		img.colors = reset;

		cout << "Completed!" << endl << endl;

		return outFile;
	};

private:

	string type;	// type of picture
	int width;		// width of picture
	int height;		// height of picture
	int maxColor;   // max color value of picture
	int *colors;	// pointer for pixel data
	int *reset;		// resets pointer location for *colors

};

int main() {
	Image img;		// creates Image class img

	img.menu(img);		// opens up menu
}