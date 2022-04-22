#include <iostream>
#include <cstring>
#include "bmplib.cpp"
#include "bmplib.h"
#include <string>

using namespace std;

unsigned char image[SIZE][SIZE];
unsigned char quarter1[SIZE][SIZE];
unsigned char quarter2[SIZE][SIZE];
unsigned char quarter3[SIZE][SIZE];
unsigned char quarter4[SIZE][SIZE];
unsigned char shuffledImage[SIZE][SIZE];

int choice5, choice8, quarterOrder, oldRows, oldCols, newRows, newCols, x, y;

string choice;
string choice4;
string choice_a;

void loadGrayImage();
void saveGrayImage();
void BlackWhiteFilter();
void invertImage():
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
void invertImage() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j] == 0) {
                image[i][j] = 255;
            } else if (image [i][j] == 255) {
                image[i][j] = 0;
            } else {
                image[i][j] = 255 - image[i][j];
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
void rotateImage() {
    cout << "Please, enter a number to select the clockwise degrees of rotation: " << endl;
    cout << "1 - 90 degrees." << endl;
    cout << "2 - 180 degrees." << endl;
    cout << "3 - 270 degrees." << endl;
    cin >> choice5;

    if (choice5 == 1) {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = i; j < SIZE - i - 1; j++) {
                int temp = image[i][j];
                image[i][j] = image[j][SIZE - 1 - i];
                image[j][SIZE - 1 - i] = image[SIZE - 1 - i][SIZE - 1 - j];
                image[SIZE - 1 - i][SIZE - 1 - j] = image[SIZE - 1 - j][i];
                image[SIZE - 1 - j][i] = temp;
            }
        }
    } else if (choice5 == 2) {
        for (int i = 0; i < SIZE; i++)
            for (int j = 0, k = SIZE - 1; j < k; j++, k--)
                swap(image[j][i], image[k][i]);

        for (int i = 0; i < SIZE; i++)
            for (int j = i; j < SIZE; j++)
                swap(image[i][j], image[j][i]);

        for (int i = 0; i < SIZE; i++)
            for (int j = 0, k = SIZE - 1; j < k; j++, k--)
                swap(image[j][i], image[k][i]);

        for (int i = 0; i < SIZE; i++)
            for (int j = i; j < SIZE; j++)
                swap(image[i][j], image[j][i]);
    } else {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = i; j < SIZE - i - 1; j++) {
                int temp = image[i][j];
                image[i][j] = image[j][SIZE - 1 - i];
                image[j][SIZE - 1 - i] = image[SIZE - 1 - i][SIZE - 1 - j];
                image[SIZE - 1 - i][SIZE - 1 - j] = image[SIZE - 1 - j][i];
                image[SIZE - 1 - j][i] = temp;
            }
        }

        for (int i = 0; i < SIZE; i++)
            for (int j = 0, k = SIZE - 1; j < k; j++, k--)
                swap(image[j][i], image[k][i]);

        for (int i = 0; i < SIZE; i++)
            for (int j = i; j < SIZE; j++)
                swap(image[i][j], image[j][i]);

        for (int i = 0; i < SIZE; i++)
            for (int j = 0, k = SIZE - 1; j < k; j++, k--)
                swap(image[j][i], image[k][i]);

        for (int i = 0; i < SIZE; i++)
            for (int j = i; j < SIZE; j++)
                swap(image[i][j], image[j][i]);
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
void enlargeImage() {
    cout << "Please, enter a number to determine which quarter to enlarge: " << endl;
    cout << "1 - Right upper quarter." << endl;
    cout << "2 - Left upper quarter." << endl;
    cout << "3 - Right lower quarter." << endl;
    cout << "4 - Left lower quarter." << endl;
    cin >> choice8;

    if (choice8 == 1) {
        for (int i = 0, x = 0; i < SIZE; i += 2, x++) {
            for (int j = 0, y = 0; j < SIZE; j += 2, y++) {
                quarter1[i][j] = image[x][y];
                quarter1[i][j + 1] = image[x][y];
                quarter1[i + 1][j] = image[x][y];
                quarter1[i + 1][j + 1] = image[x][y];
            }
        }
        char newImage[100];
        cout << "Please, enter the target image file name: " << endl;
        cin >> newImage;
        strcat(newImage, ".bmp");
        writeGSBMP(newImage, quarter1);

    } else if (choice8 == 2) {
        for (int i = 0, x = 0; i < SIZE; i += 2, x++) {
            for (int j = 0, y = 128; j < SIZE; j += 2, y++) {
                quarter2[i][j] = image[x][y];
                quarter2[i][j + 1] = image[x][y];
                quarter2[i + 1][j] = image[x][y];
                quarter2[i + 1][j + 1] = image[x][y];
            }
        }
        char newImage[100];
        cout << "Please, enter the target image file name: " << endl;
        cin >> newImage;
        strcat(newImage, ".bmp");
        writeGSBMP(newImage, quarter2);

    } else if (choice8 == 3) {
        for (int i = 0, x = 128; i < SIZE; i += 2, x++) {
            for (int j = 0, y = 0; j < SIZE; j += 2, y++) {
                quarter3[i][j] = image[x][y];
                quarter3[i][j + 1] = image[x][y];
                quarter3[i + 1][j] = image[x][y];
                quarter3[i + 1][j + 1] = image[x][y];
            }
        }
        char newImage[100];
        cout << "Please, enter the target image file name: " << endl;
        cin >> newImage;
        strcat(newImage, ".bmp");
        writeGSBMP(newImage, quarter3);

    } else {
        for (int i = 0, x = 128; i < SIZE; i += 2, x++) {
            for (int j = 0, y = 128; j < SIZE; j += 2, y++) {
                quarter4[i][j] = image[x][y];
                quarter4[i][j + 1] = image[x][y];
                quarter4[i + 1][j] = image[x][y];
                quarter4[i + 1][j + 1] = image[x][y];
            }
        }
        char newImage[100];
        cout << "Please, enter the target image file name: " << endl;
        cin >> newImage;
        strcat(newImage, ".bmp");
        writeGSBMP(newImage, quarter4);
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
//-----------------------------------------------
void shuffleImage() {
    for (int k = 1; k < 5; k++) {
        cout << "Please, enter the " << k << " quarter order: " << endl;
        cin >> quarterOrder;

        if (quarterOrder == 1 || quarterOrder == 2) {
            oldRows = 0;
        } else {
            oldRows = 128;
        }

        if (quarterOrder == 1 || quarterOrder == 3) {
            oldCols = 0;
        } else {
            oldCols = 128;
        }

        if (k == 1 || k == 2) {
            newRows = 0;
        } else {
            newRows = 128;
        }

        if (k == 1 || k == 3) {
            newCols = 0;
        } else {
            newCols = 128;
        }

        if (quarterOrder == 1) {
            x = newRows;
            for (int i = 0; i < 128; i++, x++) {
                y = newCols;
                for (int j = 0; j < 128; j++, y++) {
                    shuffledImage[x][y] = image[i][j];
                }
            }
        } else if (quarterOrder == 2) {
            x = newRows;
            for (int i = 0; i < 128; i++, x++) {
                y = newCols;
                for (int j = 128; j < 256; j++, y++) {
                    shuffledImage[x][y] = image[i][j];
                }
            }
        } else if (quarterOrder == 3) {
            x = newRows;
            for (int i = 128; i < 256; i++, x++) {
                y = newCols;
                for (int j = 0; j < 128; j++, y++) {
                    shuffledImage[x][y] = image[i][j];
                }
            }
        } else {
            x = newRows;
            for (int i = 128; i < 256; i++, x++) {
                y = newCols;
                for (int j = 128; j < 256; j++, y++) {
                    shuffledImage[x][y] = image[i][j];
                }
            }
        }
    }
}
//-----------------------------------------------
