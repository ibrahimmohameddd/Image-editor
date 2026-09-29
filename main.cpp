#include <stack>
#include <iostream>
#include <fstream>
#include <string>
#include "Image_Class.h"
#include "filters.h"
using namespace std;

stack<Image> versions;
string filename;
bool isSaved = true;
Image image;

void saveImage() {
    int choice;

    cout << "Press 0 to exit save menu: \n";
    cout << "Press 1 to save in the same file: \n";
    cout << "Press 2 to save in a new file: \n";
            
    cin >> choice;
            
    if(choice == 1 || choice == 2) isSaved = true;
    if(choice == 0) {
        cout << "Exiting save menu";
    }
    else if(choice == 1) image.saveImage(filename);
    else if(choice == 2) {
        string newFile;
        cout << "Enter new file name: \n";
        cin >> newFile;
                
        image.saveImage(newFile);
    }
}

int main() {

    while(true) {
            
        cout << "============================================\n";
        cout << "       IMAGE PROCESSING PROGRAM\n";
        cout << "============================================\n";
        cout << "Press 0 to exit program: \n";
        cout << "Press 1 to load an image: \n";
        cout << "Press 2 to apply filters: \n";
        cout << "Press 3 to undo changes: \n";
        cout << "Press 4 to save changes:\n";

        int input;
        cin >> input;    
            
        if (input == 0) {
            cout << "Exiting program. \n";
            return 0;
        }

        else if (input == 1) {
            if(!isSaved) {
                cout << "There are some unsaved changes.\n";
                cout << "Press 0 to cancel\n";
                cout << "Press 1 to discard changes\n";
                cout << "Press 2 to save changes\n";
                int savingChoice;
                cin >> savingChoice;

                if (savingChoice == 0) {continue;}
                else if (savingChoice == 1) {}
                else if (savingChoice == 2) saveImage();    
        }
            cout << "Enter image name: \n";
            cin >> filename;
            Image loadedImage(filename);
            image = loadedImage;
            isSaved = true;
            cout << "Image loaded successfully. \n";
        }

        else if (input == 2) {
            
            cout << "0. Exit filter menu\n";
            cout << "1. Grayscale\n";
            cout << "2. Black and White\n";
            cout << "3. Invert Image\n";
            cout << "4. Add Frame\n";
            cout << "5. Flip Image\n";
            cout << "6. Rotate Image\n";
            cout << "7. Darken Image\n";
            cout << "8. Lighten Image\n";
            cout << "9. Resize Image\n";
            cout << "10. Merge Images\n";
            cout << "11. Detect Edges\n";
            cout << "12. Crop Image\n";
            cout << "13. Blur Image\n";
            cout << "14. Sunlight Filter\n";
            cout << "15. TV Filter\n";
            cout << "16. Purple Filter\n";
            cout << "17. Infrared Filter\n";
            cout << "18. Skew Image\n";
            cout << "19. Oil Painting\n";

            int filterChoice;
            cin >> filterChoice;

            if(filterChoice > 0 && filterChoice < 20) {
                versions.push(image);
                isSaved = false;
            }

            switch (filterChoice) {

            case 0:
                cout << "Exiting filter menu.\n";
                continue;

            case 1:
                grayscale(image);
                cout << "Grayscale filter applied successfully.\n";
                break;

            case 2:
                blackAndWhite(image);
                cout << "Black and White filter applied successfully.\n";
                break;

            // case 3:
            //     invertImage(image);
            //     cout << "Invert filter applied successfully.\n";
            //     break;

            // case 4:
            //     addFrame(image);
            //     cout << "Frame added successfully.\n";
            //     break;

            case 5:
                flipImage(image);
                cout << "Flip filter applied successfully.\n";
                break;

            case 6: {
                int angle;

                cout << "Enter rotation angle (90, 180, or 270): ";
                cin >> angle;

                rotateImage(image, angle);
                cout << "Rotate filter applied successfully.\n";
                break;
            }

            // case 7:
            //     darkenImage(image);
            //     cout << "Darken filter applied successfully.\n";
            //     break;

            // case 8:
            //     lightenImage(image);
            //     cout << "Lighten filter applied successfully.\n";
            //     break;

            // case 9: {
            //     int newWidth, newHeight;

            //     cout << "Enter new width: ";
            //     cin >> newWidth;

            //     cout << "Enter new height: ";
            //     cin >> newHeight;

            //     resizeImage(image, newWidth, newHeight);
            //     cout << "Resize filter applied successfully.\n";
            //     break;
            // }

            // case 10: {
            //     string filename;

            //     cout << "Enter the filename of the second image: ";
            //     cin >> filename;

            //     Image secondImage(filename);

            //     mergeImages(image, secondImage);
            //     cout << "Merge filter applied successfully.\n";
            //     break;
            // }

            case 11:
                detectEdges(image);
                cout << "Edge detection filter applied successfully.\n";
                break;

            // case 12: {
            //     int startX, startY, width, height;

            //     cout << "Enter starting X: ";
            //     cin >> startX;

            //     cout << "Enter starting Y: ";
            //     cin >> startY;

            //     cout << "Enter crop width: ";
            //     cin >> width;

            //     cout << "Enter crop height: ";
            //     cin >> height;

            //     cropImage(image, startX, startY, width, height);
            //     cout << "Crop filter applied successfully.\n";
            //     break;
            // }

            // case 13:
            //     blurImage(image);
            //     cout << "Blur filter applied successfully.\n";
            //     break;

            // case 14:
            //     sunlightFilter(image);
            //     cout << "Sunlight filter applied successfully.\n";
            //     break;

            // case 15:
            //     tvFilter(image);
            //     cout << "TV filter applied successfully.\n";
            //     break;

            // case 16:
            //     purpleFilter(image);
            //     cout << "Purple filter applied successfully.\n";
            //     break;

            // case 17:
            //     infraredFilter(image);
            //     cout << "Infrared filter applied successfully.\n";
            //     break;

            // case 18:
            //     skewImage(image);
            //     cout << "Skew filter applied successfully.\n";
            //     break;

            case 19:
                oilPainting(image);
                cout << "Oil Painting filter applied successfully.\n";
                break;

            default:
                cout << "Invalid filter choice.\n";
                break;
        }
        }

        else if(input == 3) {
            image = versions.top();
            versions.pop();
            isSaved = false;
        }

        else if(input == 4) {
            
            saveImage();            
        } 
    }
}