// Program: Baby photoshop.
// Authors: Youssef Hassan Fahmy Ahmed, S17, 20230492 => 2, 5, 8, 11, 13, 16, 17
//          Ahmed Hussein Ahmed Mohammed, S17, 20230015 => 1, 4, 7, 10
//          Zyad Atef Al-Abiad, S17, 20231068 => 3, 6, 9, 12

#include "Image_Class.h" // => To access the pixels of images.
#include <string> // => For using c.str() function.
#include <windows.h> // => For using ShellExecute() function.
#include <sys/stat.h>
#include <fstream>

using namespace std;

// Commands.
void open(const char *text) {
    ShellExecute(nullptr, "open", text, nullptr, nullptr, SW_SHOWNORMAL);
}

// Checks if a file exists.
inline bool checkFileExistance(const string &name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

// Save in new image.
string saveImages() {
    cout << "Enter the name of the new image to save: ";
    string newImage;
    getline(cin, newImage);
    while (newImage.empty()) {
        cin.clear();
        cin.ignore();
        cerr << "Enter the name of the new image to save: ";
        getline(cin, newImage);
    }

    string exe;

    exe = "";

    for (int i = 0; i < newImage.size(); i++) {
        if (newImage[i] == '.') {
            for (int j = i + 1; j < newImage.size(); j++)
                exe += newImage[j];
            break;
        }
    }

    while (!((exe == "jpg") || (exe == "jpeg") || (exe == "png") || (exe == "bmp"))) {
        cerr << "Import an image its extension is (jpg - jpeg - png - bmp): ";
        newImage = "";
        getline(cin, newImage);
        while (newImage.empty()) {
            cerr << "Enter the name of the image you want to edit: ";
            getline(cin, newImage);
        }

        exe = "";

        for (int i = 0; i < newImage.size(); i++) {
            if (newImage[i] == '.') {
                for (int j = i + 1; j < newImage.size(); j++)
                    exe += newImage[j];
                break;
            }
        }
    }
    return newImage;
}

// Apply filter in the same image or a new image.
bool applyFilter(string &currentImage) {
    cout << "\nApply the effect to the current photo:\n1. Yes\n2. No, to a new one" << endl
         << "=> ";
    string check;
    getline(cin, check);
    while (currentImage.empty()) {
        cerr << "Empty input, enter the name of the image you want to edit: ";
        getline(cin, currentImage);
    }
    while (check != "1" && check != "2") {
        cerr << "Enter 1 or 2 only: ";
        check = "";
        getline(cin, check);
        while (currentImage.empty()) {
            cerr << "Empty input, enter the name of the image you want to edit: ";
            getline(cin, currentImage);
        }
    }
    if (check == "1") {
        return true;
    } else {
        return false;
    }
}

// Grayscale.
Image Grayscale(string &imageName) {
    int progress = 0, temp2 = 0;
    Image grayedImage(imageName);
    double totalPixels = grayedImage.height * grayedImage.width * 0.01;
    for (int i = 0; i < grayedImage.height; i++) {
        for (int j = 0; j < grayedImage.width; j++) {
            grayedImage(j, i, 0) =
            grayedImage(j, i, 1) =
            grayedImage(j, i, 2) =
                    grayedImage(j, i, 0) * 0.2126 + grayedImage(j, i, 1) * 0.7152 + grayedImage(j, i, 2) * 0.0722;
            int temp = int(++progress / totalPixels);
            if (temp != temp2)//(0.2126 * r + 0.7152 * g + 0.0722 * b)
                cout << '\r' << "Grayscaling image... " << temp << '%';
            temp2 = int(progress / totalPixels);
        }
    }
    cout << endl;
    return grayedImage;
}

// Black and White.
Image Black_and_White(string &imageName) {
    int progress = 0, temp2 = 0;
    Image blackedImage(imageName);
    double totalPixels = blackedImage.height * blackedImage.width * 0.01;
    for (int i = 0; i < blackedImage.height; i++) {
        for (int j = 0; j < blackedImage.width; j++) {
            blackedImage(j, i, 0) =
            blackedImage(j, i, 1) =
            blackedImage(j, i, 2) =
                    ((blackedImage(j, i, 0) + blackedImage(j, i, 1) + blackedImage(j, i, 2)) / 3 > (255 / 2) ? 255 : 0);
            int temp = int(++progress / totalPixels);
            if (temp != temp2)
                cout << '\r' << "Applying filter... " << temp << '%';
            temp2 = int(progress / totalPixels);
        }
    }
    return blackedImage;
}

// Invert.
Image Invert(string &imageName) {
    int progress = 0, temp2 = 0;
    Image invertedImage(imageName);
    double totalPixels = invertedImage.height * invertedImage.width * 0.01;
    for (int i = 0; i < invertedImage.height; i++) {
        for (int j = 0; j < invertedImage.width; j++) {
            for (int k = 0; k < invertedImage.channels; k++)
                invertedImage(j, i, k) = 255 - invertedImage(j, i, k);
            int temp = int(++progress / totalPixels);
            if (temp != temp2)
                cout << '\r' << "Inverting colors... " << temp << '%';
            temp2 = int(progress / totalPixels);
        }
    }
    return invertedImage;
}

// Flip.
Image Flip(string &imageName) {
    int progress = 0, temp2 = 0;
    Image flippedImage(imageName);
    double totalPixels = flippedImage.height * flippedImage.width * 0.01;
    cout << "Enter the direction of flip (V - H): ";
    string flipDir;
    getline(cin, flipDir);
    while ((flipDir.size() != 1) ||
           (flipDir != "V" && flipDir != "v" && flipDir != "H" && flipDir != "h")) {
        cerr << "Enter the direction of flip (V - H): ";
        flipDir = "";
        getline(cin, flipDir);
    }
    if (flipDir == "v" || flipDir == "V") {
        for (int i = 0; i < flippedImage.height / 2; i++) {
            for (int j = 0; j < flippedImage.width; j++) {
                for (int h = 0; h < flippedImage.channels; h++)
                    swap(flippedImage(j, i, h), flippedImage(j, flippedImage.height - i - 1, h));
                int temp = int(++progress / (totalPixels));
                if (temp != temp2)
                    cout << '\r' << "Flipping image... " << temp + 1 << '%';
                temp2 = int(progress / (totalPixels));
            }
        }
    } else if (flipDir == "h" || flipDir == "H") {
        for (int i = 0; i < flippedImage.height; i++) {
            for (int j = 0; j < flippedImage.width / 2; j++) {
                for (int h = 0; h < flippedImage.channels; h++)
                    swap(flippedImage(j, i, h), flippedImage(flippedImage.width - j - 1, i, h));
                int temp = int(++progress / (totalPixels));
                if (temp != temp2)
                    cout << '\r' << "Flipping image... " << temp + 2 << '%';
                temp2 = int(++progress / (totalPixels));
            }
        }
    }
    return flippedImage;
}

// Rotate.
Image Rotate(string &imageName) {
    int progress = 0, temp2 = 0;
    Image photo(imageName);
    double totalPixels = photo.height * photo.width * 0.01;
    cout << "Choose the angle of rotation clockwise:\n1. 90\n2. 180\n3. 270" << endl
         << "=> ";
    string rotationAngle;
    getline(cin, rotationAngle);
    while (rotationAngle.empty() || rotationAngle != "1" && rotationAngle != "2" && rotationAngle != "3") {
        cerr << "Enter an integer of (1 - 2 - 3): ";
        rotationAngle = "";
        getline(cin, rotationAngle);
    }

    Image rotatedImage(imageName);

    if (stoi(rotationAngle) == 2) {
        rotatedImage.height = photo.height;
        rotatedImage.width = photo.width;
    } else {
        rotatedImage.width = photo.height;
        rotatedImage.height = photo.width;
    }

    if (stoi(rotationAngle) == 2) {
        for (int x = 0; x < rotatedImage.height; x++) {
            for (int y = 0; y < rotatedImage.width; y++) {
                for (int h = 0; h < rotatedImage.channels; h++)
                    rotatedImage(y, x, h) = photo(y, photo.height - x - 1, h);
                int temp = int(++progress / totalPixels);
                if (temp != temp2)
                    cout << '\r' << "Rotating image... " << temp << '%';
                temp2 = int(progress / totalPixels);
            }
        }
        for (int x = 0; x < rotatedImage.height; x++)
            for (int y = 0; y < rotatedImage.width / 2; y++)
                for (int h = 0; h < rotatedImage.channels; h++)
                    swap(rotatedImage(y, x, h), rotatedImage(photo.width - y - 1, x, h));
    } else {
        for (int x = 0; x < rotatedImage.height; x++) {
            for (int y = 0; y < rotatedImage.width; y++) {
                for (int h = 0; h < rotatedImage.channels; h++)
                    rotatedImage(y, x, h) = photo(x, y, h);
                int temp = int(++progress / totalPixels);
                if (temp != temp2)
                    cout << '\r' << "Rotating image... " << temp << '%';
                temp2 = int(progress / totalPixels);
            }
        }
        for (int x = 0; x < rotatedImage.height; x++)
            for (int y = 0; y < rotatedImage.width / 2; y++)
                for (int h = 0; h < rotatedImage.channels; h++)
                    swap(rotatedImage(y, x, h), rotatedImage(rotatedImage.width - y - 1, x, h));
        if (stoi(rotationAngle) == 3) {
            for (int x = 0; x < rotatedImage.height / 2; x++)
                for (int y = 0; y < rotatedImage.width; y++)
                    for (int h = 0; h < rotatedImage.channels; h++)
                        swap(rotatedImage(y, x, h), rotatedImage(y, rotatedImage.height - x - 1, h));
            for (int x = 0; x < rotatedImage.height; x++)
                for (int y = 0; y < rotatedImage.width / 2; y++)
                    for (int h = 0; h < rotatedImage.channels; h++)
                        swap(rotatedImage(y, x, h), rotatedImage(rotatedImage.width - y - 1, x, h));
        }
    }
    return rotatedImage;
}

// Darken and Lighten.
Image Darken_and_lighten(string &imageName) {
    int progress = 0, temp2 = 0;
    Image editedImage(imageName);
    double totalPixels = editedImage.height * editedImage.width * 0.01;
    cout << "1. Darken\n2. Lighten" << endl << "=> ";
    string value;
    getline(cin, value);
    while (value.empty() || (value != "1" && value != "2")) {
        cerr << "Enter (1 or 2): ";
        value = "";
        getline(cin, value);
    }
    cout << R"(How much (%)? "Without '%'": )";
    float perc;
    cin >> perc;
    while (!cin || perc < 0) {
        cerr << "Enter a non-negative number: ";
        cin >> perc;
    }
    for (int i = 0; i < editedImage.height; i++) {
        for (int j = 0; j < editedImage.width; j++) {
            for (int k = 0; k < editedImage.channels; k++) {
                if (stoi(value) == 2) {
                    if (editedImage(j, i, k) * (1 + (perc / 100)) > 255)
                        editedImage(j, i, k) = 255;
                    else
                        editedImage(j, i, k) = editedImage(j, i, k) * (1 + (perc / 100));
                } else {
                    if (editedImage(j, i, k) * (1 - (perc / 100)) < 0)
                        editedImage(j, i, k) = 0;
                    else
                        editedImage(j, i, k) = editedImage(j, i, k) * (1 - (perc / 100));
                }
            }
            int temp = (++progress / totalPixels);
            if (temp != temp2)
                cout << '\r' << "Editing lighting... " << temp << '%';
            temp2 = (progress / totalPixels);
        }
    }
    cin.ignore();
    return editedImage;
}

// Crop.
Image Crop(Image &photo) {
    int progress = 0, temp2 = 0;
    cout << "Enter the starting dimension of the cropped photo (in order): ";
    int x, y;
    cin >> x >> y;
    cout << "Enter the width and the height of the cropped photo (in order): ";
    int h, w;
    cin >> w >> h;
    while (x < 0 && y < 0 && x + w < 0 && y + h < 0 && x >= photo.width && y >= photo.height && x + w >= photo.width &&
           y + h >= photo.height) {
        cerr << "Enter the starting dimension of the cropped photo (in order): ";
        cin >> x >> y;
        cerr << "Enter the width and the height of the cropped photo (in order): ";
        cin >> w >> h;
    }
    Image croppedPhoto(w, h);
    double totalPixels = h * w * 0.01;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            for (int k = 0; k < photo.channels; k++)
                croppedPhoto(j, i, k) = photo(j + y, i + x, k);
            int temp = (++progress / totalPixels);
            if (temp != temp2)
                cout << '\r' << "Cropping image... " << temp << '%';
            temp2 = (progress / totalPixels);
        }
    }
    cin.ignore();
    return croppedPhoto;
}

// Resize.
Image Resize(Image &photo) {
    int progress = 0, temp2 = 0;
    cout << "Enter width and height of the new photo (in order): ";
    int w, h;
    cin >> w >> h;
    while (w < 0 || h < 0 && !cin) {
        cerr << "Enter width and height of the new photo (in order): ";
        cin >> w >> h;
    }
    Image resizedPhoto(w, h);
    double totalPixels = h * w * 0.01;
    float n = 0;
    for (int i = 0; i < h; i++) {
        float m = 0;
        for (int j = 0; j < w; j++) {
            for (int k = 0; k < 3; k++)
                resizedPhoto(j, i, k) = photo(m, n, k);
            m += (float) photo.width / (float) w;

            int temp = (++progress / totalPixels);
            if (temp != temp2)
                cout << '\r' << "Resizing image... " << temp << '%';
            temp2 = (progress / totalPixels);
        }
        n += (float) photo.height / (float) h;
    }
    cin.ignore();
    return resizedPhoto;
}

// Blur.
Image Blur(string &imageName) {
    int progress = 0, temp2 = 0;
    Image blurredImage(imageName);
    double totalPixels = blurredImage.height * blurredImage.width * 0.01;
    cout << "Enter the power of blur: ";
    int kernelSize;
    cin >> kernelSize;
    while (kernelSize < 0 || !cin) {
        cin.clear();
        cin.ignore();
        cout << "Enter a positive integer value: ";
        cin >> kernelSize;
    }
    for (int i = 0; i < blurredImage.width; i++) {
        for (int j = 0; j < blurredImage.height; j++) {
            int avgR = 0, avgG = 0, avgB = 0, counter = 0;
            for (int h = -kernelSize; h <= kernelSize; h++) {
                int xIndex = i + h;
                if (xIndex >= 0 && xIndex < blurredImage.width) {
                    avgR += blurredImage(xIndex, j, 0);
                    avgG += blurredImage(xIndex, j, 1);
                    avgB += blurredImage(xIndex, j, 2);
                    counter++;
                }
            }
            blurredImage(i, j, 0) = avgR / counter;
            blurredImage(i, j, 1) = avgG / counter;
            blurredImage(i, j, 2) = avgB / counter;
            int temp = (++progress / (totalPixels * 2));
            if (temp != temp2 && temp < 50)
                cout << '\r' << "Blurring image... " << temp << '%';
            temp2 = (progress / (totalPixels * 2));
        }
    }
    for (int i = 0; i < blurredImage.width; i++) {
        for (int j = 0; j < blurredImage.height; j++) {
            int avgR = 0, avgG = 0, avgB = 0, counter = 0;
            for (int h = -kernelSize; h <= kernelSize; h++) {
                int yIndex = j + h;
                if (yIndex >= 0 && yIndex < blurredImage.height) {
                    avgR += blurredImage(i, yIndex, 0);
                    avgG += blurredImage(i, yIndex, 1);
                    avgB += blurredImage(i, yIndex, 2);
                    counter++;
                }
            }
            blurredImage(i, j, 0) = avgR / counter;
            blurredImage(i, j, 1) = avgG / counter;
            blurredImage(i, j, 2) = avgB / counter;
            int temp = int(++progress / (totalPixels * 2));
            if (temp != temp2 && temp >= 50)
                cout << '\r' << "Blurring image... " << temp << '%';
            temp2 = int(progress / (totalPixels * 2));
        }
    }
    cin.ignore();
    return blurredImage;
}

// Edge Detection.
Image edgeDetection(string &imageName) {
    int progress = 0, temp2 = 0;
    Image inputImage(imageName);
    double totalPixels = (inputImage.height - 2) * (inputImage.width - 2) * 0.01;
    // Convert image to grayscale
    Image grayImage = Grayscale(imageName);
    Image blacked = Black_and_White(imageName);

    // Sobel Operator
    Image edgeImage(inputImage.width, inputImage.height);
    int Gx, Gy;
    for (int y = 1; y < inputImage.height - 1; ++y) {
        for (int x = 1; x < inputImage.width - 1; ++x) {
            int temp = int(++progress / totalPixels);
            if (temp != temp2)
                cout << '\r' << "Detecting edges... " << temp << '%';
            temp2 = int(progress / totalPixels);

            Gx = (-1 * blacked(x - 1, y - 1, 0)) + (0 * blacked(x, y - 1, 0)) + (1 * blacked(x + 1, y - 1, 0)) +
                 (-2 * blacked(x - 1, y, 0)) + (0 * blacked(x, y, 0)) + (2 * blacked(x + 1, y, 0)) +
                 (-1 * blacked(x - 1, y + 1, 0)) + (0 * blacked(x, y + 1, 0)) + (1 * blacked(x + 1, y + 1, 0));

            Gy = (-1 * blacked(x - 1, y - 1, 0)) + (-2 * blacked(x, y - 1, 0)) + (-1 * blacked(x + 1, y - 1, 0)) +
                 (0 * blacked(x - 1, y, 0)) + (0 * blacked(x, y, 0)) + (0 * blacked(x + 1, y, 0)) +
                 (1 * blacked(x - 1, y + 1, 0)) + (2 * blacked(x, y + 1, 0)) + (1 * blacked(x + 1, y + 1, 0));

            float magnitude = sqrt(Gx * Gx + Gy * Gy);

            if (magnitude >= 150) {
                edgeImage.setPixel(x, y, 0, 0); // Black
                edgeImage.setPixel(x, y, 1, 0); // Black
                edgeImage.setPixel(x, y, 2, 0); // Black
            } else {
                edgeImage.setPixel(x, y, 0, 255); // White
                edgeImage.setPixel(x, y, 1, 255); // White
                edgeImage.setPixel(x, y, 2, 255); // White
            }
        }
    }
    return edgeImage;
}

// Purple.
Image purple(string &imageName) {
    int progress = 0, temp2 = 0;
    Image purpleImage(imageName);
    double totalPixels = purpleImage.height * purpleImage.width * 0.01;
    for (int i = 0; i < purpleImage.height; ++i) {
        for (int j = 0; j < purpleImage.width; ++j) {
            purpleImage(j, i, 1) *= 0.75;
            int temp = int(++progress / totalPixels);
            if (temp != temp2)
                cout << '\r' << "Applying filter... " << temp << '%';
            temp2 = int(progress / totalPixels);
        }
    }
    return purpleImage;
}

// Infrared.
Image infrared(string &imageName) {
    int progress = 0, temp2 = 0;
    Image photo(imageName);
    double totalPixels = photo.height * photo.width * 0.01;
    for (int i = 0; i < photo.height; ++i) {
        for (int j = 0; j < photo.width; ++j) {
            photo(j, i, 0) = 255;
            photo(j, i, 1) = 255 - photo(j, i, 1);
            photo(j, i, 2) = 255 - photo(j, i, 2);
            int temp = int(++progress / totalPixels);
            if (temp != temp2)
                cout << '\r' << "Detecting edges... " << temp << '%';
            temp2 = int(progress / totalPixels);
        }
    }
    return photo;
}

// Merge.
Image merge(Image &firstImage, Image &secondImage) {
    Image tempImage(firstImage.width, firstImage.height);

    // Resizing smaller image to fit bigger image.
    int h = firstImage.height, w = firstImage.width;
    float n = 0;
    int progress = 0, temp2 = 0;
    double totalPixels = h * w * 0.01;
    for (int i = 0; i < h; i++) {
        float m = 0;
        for (int j = 0; j < w; j++) {
            for (int k = 0; k < 3; k++)
                tempImage(j, i, k) = secondImage(m, n, k);
            m += (float) secondImage.width / (float) w;

            int temp = (++progress / totalPixels);
            if (temp != temp2)
                cout << '\r' << "Resizing images... " << temp << '%';
            temp2 = (progress / totalPixels);
        }
        n += (float) secondImage.height / (float) h;
    }
    cout << endl;

    Image mergedImages(firstImage.width, firstImage.height);

    for (int i = 0; i < firstImage.height; ++i) {
        for (int j = 0; j < firstImage.width; ++j) {
            for (int k = 0; k < firstImage.channels; ++k) {
                mergedImages(j, i, k) = (firstImage(j, i, k) + tempImage(j, i, k)) / 2;
            }
        }
    }
    return mergedImages;
}

// Sunlight.
Image sunlight(string &imageName) {
    int progress = 0, temp2 = 0;
    Image sunlightImage(imageName);
    double totalPixels = sunlightImage.height * sunlightImage.width * 0.01;
    for (int i = 0; i < sunlightImage.height; ++i) {
        for (int j = 0; j < sunlightImage.width; ++j) {
            sunlightImage(j, i, 2) *= 0.75;
            int temp = int(++progress / totalPixels);
            if (temp != temp2)
                cout << '\r' << "Applying filter... " << temp << '%';
            temp2 = int(progress / totalPixels);
        }
    }
    return sunlightImage;
}

// Frame.
Image frame(string &imageName, int thickness) {
    int progress = 0, temp2 = 0;
    Image framedImage(imageName);
    // Upper frame.
    for (int i = 0; i < thickness; ++i) {
        for (int j = 0; j < framedImage.width; ++j) {
            for (int k = 0; k < framedImage.channels; ++k) {
                framedImage(j, i, 0) = 0;
                framedImage(j, i, 1) = 0;
                framedImage(j, i, 2) = 255;

                int temp = int(++progress / (double) thickness * framedImage.width * 0.01);
                if (temp != temp2)
                    cout << '\r' << "Applying upper frame... " << temp << '%';
                temp2 = int(progress / (double) thickness * framedImage.width * 0.01);
            }
        }
    }

    // Left frame.
    for (int i = 0; i < framedImage.height; ++i) {
        for (int j = 0; j < thickness; ++j) {
            for (int k = 0; k < framedImage.channels; ++k) {
                framedImage(j, i, 0) = 0;
                framedImage(j, i, 1) = 0;
                framedImage(j, i, 2) = 255;

                int temp = int(++progress / (double) thickness * framedImage.height * 0.01);
                if (temp != temp2)
                    cout << '\r' << "Applying left frame... " << temp << '%';
                temp2 = int(progress / (double) thickness * framedImage.height * 0.01);
            }
        }
    }

    // Lower frame.
    for (int i = framedImage.height - thickness; i < framedImage.height; ++i) {
        for (int j = 0; j < framedImage.width; ++j) {
            for (int k = 0; k < framedImage.channels; ++k) {
                framedImage(j, i, 0) = 0;
                framedImage(j, i, 1) = 0;
                framedImage(j, i, 2) = 255;

                int temp = int(++progress / (double) thickness * framedImage.width * 0.01);
                if (temp != temp2)
                    cout << '\r' << "Applying upper frame... " << temp << '%';
                temp2 = int(progress / (double) thickness * framedImage.width * 0.01);
            }
        }
    }

    // Right frame.
    for (int i = 0; i < framedImage.height; ++i) {
        for (int j = framedImage.width - thickness; j < framedImage.width; ++j) {
            for (int k = 0; k < framedImage.channels; ++k) {
                framedImage(j, i, 0) = 0;
                framedImage(j, i, 1) = 0;
                framedImage(j, i, 2) = 255;

                int temp = int(++progress / (double) thickness * framedImage.height * 0.01);
                if (temp != temp2)
                    cout << '\r' << "Applying left frame... " << temp << '%';
                temp2 = int(progress / (double) thickness * framedImage.height * 0.01);
            }
        }
    }
    return framedImage;
}

int main() {
    open("cls");
    cout << "Choose the filter you want: " << endl;
    cout
            << "0.  Exit\n1.  Grayscale\n2.  Black and White\n3.  Invert Image\n4.  Flip Image\n5.  Rotate Image\n6.  Darken and Lighten\n7.  Crop Image\n8.  Resize Image\n9.  Blur\n10. Edge Detection\n11. Purple\n12. Infrared\n13. Merge\n14. Sunlight\n15. Frame\n"
            << "=> ";
    string filterNumber;
    getline(cin, filterNumber);
    while (filterNumber.empty() ||
           filterNumber != "0" && filterNumber != "1" && filterNumber != "2" && filterNumber != "3" &&
           filterNumber != "4" && filterNumber != "5" && filterNumber != "6" && filterNumber != "7" &&
           filterNumber != "8" && filterNumber != "9" && filterNumber != "10" && filterNumber != "11" &&
           filterNumber != "12" && filterNumber != "13" && filterNumber != "14" && filterNumber != "15") {
        cerr << "Enter an integer from 0 to 15: ";
        filterNumber = "";
        getline(cin, filterNumber);
    }

    if (stoi(filterNumber)) {
        cout << "Enter the name of the image you want to edit: ";
        string imageName;
        getline(cin, imageName);
        while (imageName.empty()) {
            cerr << "Empty input, enter the name of the image you want to edit: ";
            getline(cin, imageName);
        }

        string exe = "";

        for (int i = 0; i < imageName.size(); i++) {
            if (imageName[i] == '.') {
                for (int j = i + 1; j < imageName.size(); j++)
                    exe += imageName[j];
                break;
            }
        }

        while (!((exe == "jpg") || (exe == "jpeg") || (exe == "png") || (exe == "bmp"))) {
            cerr << "Import an image its extension is (jpg - jpeg - png - bmp): ";
            imageName = "";
            getline(cin, imageName);
            while (!imageName.size()) {
                cerr << "Enter the name of the image you want to edit: ";
                getline(cin, imageName);
            }

            exe = "";

            for (int i = 0; i < imageName.size(); i++) {
                if (imageName[i] == '.') {
                    for (int j = i + 1; j < imageName.size(); j++)
                        exe += imageName[j];
                    break;
                }
            }
        }

        while (!checkFileExistance(imageName)) {
            cout << "Enter an existing image name: ";
            imageName = "";
            getline(cin, imageName);
            while (imageName.empty()) {
                cerr << "Empty input, enter the name of the image you want to edit: ";
                getline(cin, imageName);
            }

            exe = "";

            for (int i = 0; i < imageName.size(); i++) {
                if (imageName[i] == '.') {
                    for (int j = i + 1; j < imageName.size(); j++)
                        exe += imageName[j];
                    break;
                }
            }

            while (!((exe == "jpg") || (exe == "jpeg") || (exe == "png") || (exe == "bmp"))) {
                cerr << "Import an image its extension is (jpg - jpeg - png - bmp): ";
                imageName = "";
                getline(cin, imageName);
                while (!imageName.size()) {
                    cerr << "Enter the name of the image you want to edit: ";
                    getline(cin, imageName);
                }

                exe = "";

                for (int i = 0; i < imageName.size(); i++) {
                    if (imageName[i] == '.') {
                        for (int j = i + 1; j < imageName.size(); j++)
                            exe += imageName[j];
                        break;
                    }
                }
            }
        }
        Image photo(imageName);


        // Grayscale.
        if (stoi(filterNumber) == 1) {
            Image grayedImage = Grayscale(imageName);
            if (applyFilter(imageName)) {
                grayedImage.saveImage(imageName);
                open(imageName.c_str());
            } else {
                string newI = saveImages();
                grayedImage.saveImage(newI);
                open(newI.c_str());
            }
        }
            // Black and White.
        else if (stoi(filterNumber) == 2) {
            Image blackedImage = Black_and_White(imageName);
            if (applyFilter(imageName)) {
                blackedImage.saveImage(imageName);
                open(imageName.c_str());
            } else {
                string newI = saveImages();
                blackedImage.saveImage(newI);
                open(newI.c_str());
            }
        }
            // Invert Image.
        else if (stoi(filterNumber) == 3) {
            Image invertedImage = Invert(imageName);
            if (applyFilter(imageName)) {
                invertedImage.saveImage(imageName);
                open(imageName.c_str());
            } else {
                string newI = saveImages();
                invertedImage.saveImage(newI);
                open(newI.c_str());
            }
        }
            // Flip Image.
        else if (stoi(filterNumber) == 4) {
            Image flippedImage = Flip(imageName);
            if (applyFilter(imageName)) {
                flippedImage.saveImage(imageName);
                open(imageName.c_str());
            } else {
                string newI = saveImages();
                flippedImage.saveImage(newI);
                open(newI.c_str());
            }
        }
            // Rotate Image.
        else if (stoi(filterNumber) == 5) {
            Image rotatedImage = Rotate(imageName);
            if (applyFilter(imageName)) {
                rotatedImage.saveImage(imageName);
                open(imageName.c_str());
            } else {
                string newI = saveImages();
                rotatedImage.saveImage(newI);
                open(newI.c_str());
            }
        }
            // Darken and Lighten.
        else if (stoi(filterNumber) == 6) {
            Image editedImage = Darken_and_lighten(imageName);
            if (applyFilter(imageName)) {
                editedImage.saveImage(imageName);
                open(imageName.c_str());
            } else {
                string newI = saveImages();
                editedImage.saveImage(newI);
                open(newI.c_str());
            }
        }
            // Crop Image.
        else if (stoi(filterNumber) == 7) {
            Image croppedImage = Crop(photo);
            if (applyFilter(imageName)) {
                croppedImage.saveImage(imageName);
                open(imageName.c_str());
            } else {
                string newI = saveImages();
                croppedImage.saveImage(newI);
                open(newI.c_str());
            }

        }
            // Resize Image.
        else if (stoi(filterNumber) == 8) {
            Image resizedImage = Resize(photo);
            if (applyFilter(imageName)) {
                resizedImage.saveImage(imageName);
                open(imageName.c_str());
            } else {
                string newI = saveImages();
                resizedImage.saveImage(newI);
                open(newI.c_str());
            }

        }
            // Blur Image.
        else if (stoi(filterNumber) == 9) {
            Image blurredImage = Blur(imageName);
            if (applyFilter(imageName)) {
                blurredImage.saveImage(imageName);
                open(imageName.c_str());
            } else {
                string newI = saveImages();
                blurredImage.saveImage(newI);
                open(newI.c_str());
            }

        }
            // Edge Detection.
        else if (stoi(filterNumber) == 10) {
            Image editedImage = edgeDetection(imageName);
            if (applyFilter(imageName)) {
                editedImage.saveImage(imageName);
                open(imageName.c_str());
            } else {
                string newI = saveImages();
                editedImage.saveImage(newI);
                open(newI.c_str());
            }
        }
            // Purple.
        else if (stoi(filterNumber) == 11) {
            Image purpleImage = purple(imageName);
            if (applyFilter(imageName)) {
                purpleImage.saveImage(imageName);
                open(imageName.c_str());
            } else {
                string newI = saveImages();
                purpleImage.saveImage(newI);
                open(newI.c_str());
            }
        }
            // Infrared.
        else if (stoi(filterNumber) == 12) {
            Image purpleImage = infrared(imageName);
            if (applyFilter(imageName)) {
                purpleImage.saveImage(imageName);
                open(imageName.c_str());
            } else {
                string newI = saveImages();
                purpleImage.saveImage(newI);
                open(newI.c_str());
            }
        }
            // Merge.
        else if (stoi(filterNumber) == 13) {
            cout << "Enter the second image to merge: ";
            string secondImageName;
            getline(cin, secondImageName);
            while (secondImageName.empty()) {
                cerr << "Empty input, enter the name of the image you want to edit: ";
                getline(cin, imageName);
            }

            exe = "";

            for (int i = 0; i < secondImageName.size(); i++) {
                if (secondImageName[i] == '.') {
                    for (int j = i + 1; j < secondImageName.size(); j++)
                        exe += secondImageName[j];
                    break;
                }
            }

            while (!((exe == "jpg") || (exe == "jpeg") || (exe == "png") || (exe == "bmp"))) {
                cerr << "Import an image its extension is (jpg - jpeg - png - bmp): ";
                secondImageName = "";
                getline(cin, secondImageName);
                while (!secondImageName.size()) {
                    cerr << "Enter the name of the image you want to edit: ";
                    getline(cin, secondImageName);
                }

                exe = "";

                for (int i = 0; i < secondImageName.size(); i++) {
                    if (secondImageName[i] == '.') {
                        for (int j = i + 1; j < secondImageName.size(); j++)
                            exe += secondImageName[j];
                        break;
                    }
                }
            }

            while (!checkFileExistance(secondImageName)) {
                cout << "Enter an existing image name: ";
                secondImageName = "";
                getline(cin, secondImageName);
                while (secondImageName.empty()) {
                    cerr << "Empty input, enter the name of the image you want to edit: ";
                    getline(cin, secondImageName);
                }

                exe = "";

                for (int i = 0; i < secondImageName.size(); i++) {
                    if (secondImageName[i] == '.') {
                        for (int j = i + 1; j < secondImageName.size(); j++)
                            exe += secondImageName[j];
                        break;
                    }
                }

                while (!((exe == "jpg") || (exe == "jpeg") || (exe == "png") || (exe == "bmp"))) {
                    cerr << "Import an image its extension is (jpg - jpeg - png - bmp): ";
                    secondImageName = "";
                    getline(cin, secondImageName);
                    while (!secondImageName.size()) {
                        cerr << "Enter the name of the image you want to edit: ";
                        getline(cin, secondImageName);
                    }

                    exe = "";

                    for (int i = 0; i < secondImageName.size(); i++) {
                        if (secondImageName[i] == '.') {
                            for (int j = i + 1; j < secondImageName.size(); j++)
                                exe += secondImageName[j];
                            break;
                        }
                    }
                }
            }

            Image secondImage(secondImageName);
            Image mergedImages = merge(photo, secondImage);
            if (applyFilter(secondImageName)) {
                mergedImages.saveImage(secondImageName);
                open(secondImageName.c_str());
            } else {
                string newI = saveImages();
                mergedImages.saveImage(newI);
                open(newI.c_str());
            }
        }
            // Sunlight.
        else if (stoi(filterNumber) == 14) {
            Image sunImage = sunlight(imageName);
            if (applyFilter(imageName)) {
                sunImage.saveImage(imageName);
                open(imageName.c_str());
            } else {
                string newI = saveImages();
                sunImage.saveImage(newI);
                open(newI.c_str());
            }
        }
            // Frame.
        else if (stoi(filterNumber) == 15) {
            cout << "Enter the thickness of the frame: ";
            short int thickness;
            cin >> thickness;
            while (!cin || thickness < 0) {
                cout << "Enter a positive integer: ";
                cin.clear();
                cin.ignore();
                cin >> thickness;
            }
            Image framedImage = frame(imageName, thickness);
            cin.clear();
            cin.ignore();
            if (applyFilter(imageName)) {
                framedImage.saveImage(imageName);
                open(imageName.c_str());
            } else {
                string newI = saveImages();
                framedImage.saveImage(newI);
                open(newI.c_str());
            }
        }
        cout << endl;
        cin.clear();
    } else {
        cout << endl;
        return 0;
    }
    main();
}