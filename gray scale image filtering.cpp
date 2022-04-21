#include <iostream>
#include <cstring>
#include "bmplib.cpp"
#include "bmplib.h"
#include <string>
using namespace std;
unsigned char image[SIZE][SIZE];
string choice;
string choice4;
string choice_a;
void loadGrayImage();
void saveGrayImage();
void BlackWhiteFilter();
void FlipImage();
void DetectImageEdges();
void MirrorHalfImage();
int main(){
    cout << "hello our dear user " << endl;
    loadGrayImage(); // take the name of the image from the user and load it to do the filters in
    cout << "please select a filter to apply or 0 to exit:  " << endl;
    cout << "1- Black and white Filter." << endl;
    cout << "2- Invert Filter." << endl;
    cout << "3- Merge Filter." << endl;
    cout << "4- Flip Image ." << endl;
    cout << "5- Darken and Lighten Filter." << endl;
    cout << "6- Rotate Image." << endl;
    cout << "7- Detect Image Edges." << endl;
    cout << "8- Enlarge Image ." << endl;
    cout << "9- Shrink Image ." << endl;
    cout << "a- Mirror 1/2 Image ." << endl;
    cout << "b- Shuffle Image ." << endl;
    cout << "c- Blur Image ." << endl;
    cout << "s- Save the Image to a file." << endl;
    cout << "0- Exit ." << endl;
    cin >> choice; // take the no. of the filter that user want to apply
    if (choice == "1") {
        BlackWhiteFilter();
    }
    if (choice == "4") {
        FlipImage();
    }
    if (choice == "7") {
        DetectImageEdges();
    }
    if (choice == "a") {
        MirrorHalfImage();
    }
    if (choice == "0") {
        cout << " thank you for using out filter"; // exit
    }
    saveGrayImage(); // this function to save the changes on the image after apply the filter on it (gray version)
}
//_______________
void loadGrayImage() {
    char image_file_name[100];

    // Get gray scale image file name
    cout << "Please enter the source file name: ";
    cin >> image_file_name;

    // Add to it .bmp extension and load image
    strcat(image_file_name, ".bmp");
    readGSBMP(image_file_name, image);
}
//_______________
void saveGrayImage() {
    char image_file_name[100];

    // Get gray scale image target file name
    cout << "Please enter the target image file name: ";
    cin >> image_file_name;

    // Add to it .bmp extension and load image
    strcat(image_file_name, ".bmp");
    writeGSBMP(image_file_name, image);
}

//_______________
void BlackWhiteFilter() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // we compare the average of gray in each pixel
            // with 127 so if it is greater will be white otherwise will be black
            if (image[i][j] > 127) {
                image[i][j] = 255;
            } else {
                image[i][j] = 0;
            }
        }
    }
}
//_______________
void FlipImage() {
    cout << " please select a number to determine how to flip " << endl;
    cout << "1- Flip Horizontally. " << endl;
    cout << "2- Flip Vertically. " << endl;
    cin >> choice4; // take the input from the user to flip the image horizontally or vertically
    if (choice4 == "1") {
        for (int i = 0; i < (SIZE / 2); i++) {
            for (int j = 0; j < SIZE; j++) {
                // here we loop on the half of the rows
                // because we want to swap the elements on each row to flip it 180 deg
                swap(image[i][j], image[SIZE - 1 - i][j]);
            }
        }
    }
    else if (choice4 == "2") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < (SIZE / 2); j++) {
                // here we loop on the half of the columns
                // because we want to swap the elements on each column to do as reflection
                swap(image[i][j], image[i][SIZE - 1 - j]);
            }
        }
    }
}
//-----------------------------------------------
void DetectImageEdges() {
    BlackWhiteFilter(); // we call the black and white function
    // because we compare each index and the next to it with 0 and 255
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // we check each two adjacent pixels
            // if they are the same put each equals to 255 (white) otherwise equals 0 (black)
            if (image[i][j] == image[i][j + 1]) {
                image[i][j] = 255;
            }
            else if (image[i][j] != image[i][j + 1]) {
                image[i][j] = 0;
            }
        }
    }
}
//-----------------------------------------------
void MirrorHalfImage() {
    cout << "please select which half you want: " << endl;
    cout << "1- Right half" << endl;
    cout << "2- left half" << endl;
    cout << "3- Upper half" << endl;
    cout << "4- lower half" << endl;
    cin >> choice_a; // take the input from the user to miror which half
    if (choice_a == "1") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < (SIZE / 2); j++) {
                // we loop on the half of the columns to reflect the right or the left of the image
                image[i][j] = image[i][SIZE - 1 - j];
                // we take the value of the right pixels and put it on the left in the same row
            }
        }
    }
    if (choice_a == "2") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < (SIZE / 2); j++) {
                // we loop on the half of the columns to reflect the right or the left of the image
                image[i][SIZE - 1 - j] = image[i][j];
                // we take the value of the left pixels and put it on the right in the same row

            }
        }
    }
    if (choice_a == "3") {
        for (int i = 0; i < (SIZE / 2); i++) {
            for (int j = 0; j < SIZE; j++) {
                // we loop on the half of the rows to reflect
                // the upper half or the lower half of the image
                image[SIZE - 1 - i][j] = image[i][j];
                // we take the value of the upper pixels and put it on the lower in the same column

            }
        }
    }
    if (choice_a == "4") {
        for (int i = 0; i < (SIZE / 2); i++) {
            for (int j = 0; j < SIZE; j++) {
                // we loop on the half of the rows to reflect
                // the upper half or the lower half of the image
                image[i][j] = image[SIZE - 1 - i][j];
                // we take the value of the lower pixels and put it on the upper in the same column
            }
        }
    }
}