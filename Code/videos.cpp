#include <iostream>
#include <fstream>
#include <windows.h>
#include <iomanip>
#include "videos.h"

using namespace std;
using namespace ns;

// Constructor
VideoList::VideoList() {
    // Set the Head of the Video Linked List to NULL
    head = NULL;

    // Local Variables
    string title, genre, production, id, copies, image;
    int cId, cCopies;

    // Set the path for the videos.txt file/csv
    // File Read
    ifstream file("videos.txt");
    

    // Check if the file can be access, otherwise not display an error
    if(file.is_open()) {
        // Loop while the videos.txt has not reach the end of the text file
        while(!file.eof()) {
            // Store the data from the videos.txt to the local variables
            getline(file, id, ',');
            getline(file, title, ',');
            getline(file, genre, ',');
            getline(file, production, ',');
            getline(file, copies, ',');
            getline(file, image, '\n');
            
            // If the data is not empty
            if(!id.empty()) {
                // Insert the data from the local variable to the Video Linked List
                cId = stoi(id);
                cCopies = stoi(copies);
                insertVideo(cId, title, genre, production, cCopies, image);
            }
        }
    } else {
        // Display an Error when the videos.txt file cannot be accessed
        cout << "\nError videos.txt cannot be opened." << endl;
        system("pause");
    }

    // Close the file
    file.close();
}

// Deconstructur
VideoList::~VideoList() {
    // Set the variables for the Video Linked List
    VideoNode *nodePtr, *nextNode;
    nodePtr = head;

    // Set the path for the videos.txt file/csv
    // File Write
    ofstream file("videos.txt");

    // Local Variable
    bool bFile;
    string sFile, dFile;

    // Check if the file can be access, otherwise not display an error
	if(file.is_open()) {
        // Loop while there is a Node in the Video Linked List
        while (nodePtr) {
            // This function is used to Copy the file from the source to the destination images folder
            sFile = nodePtr->videoImage;
            dFile = "images\\" + nodePtr->videoTitle + ".png";
            bFile = CopyFileA(sFile.c_str(), dFile.c_str(), TRUE);
            // Exclude Error 80, Means file already exist cannot override
            // https://docs.microsoft.com/en-us/windows/win32/debug/system-error-codes--0-499-
            if(!bFile && GetLastError() != 80) {
                cout << "Error Copying File: " << sFile << endl;
                cout << "Error Code: " << GetLastError() << endl;
                system("pause");
                cout << endl;
            }

            // Save the data in the format of:
            // Id,Title,Genre,Production,Copies,Image
            file << nodePtr->videoId << "," << nodePtr->videoTitle << "," << nodePtr->videoGenre << "," << nodePtr->videoProduction << "," << nodePtr->videoCopies << "," << dFile << endl;
            nodePtr = nodePtr->next;
        }
    } else {
        // Display an Error when the videos.txt file cannot be accessed
        cout << "\nError videos.txt cannot be opened." << endl;
        system("pause");
    }

    // Close the file
    file.close();
}

// Used for the Auto Incremention of the Video ID
int VideoList::autoVideoIdIncrement() {
    // Set the variables for the Video Linked List
    VideoNode *nodePtr;
    nodePtr = head;

    // Local Variable
    int id = 0;

    // Traverse through the Video Linked List
    while(nodePtr) {
        // Loop and get the Highest video id
        if(nodePtr->videoId > id)
            id = nodePtr->videoId;
        nodePtr = nodePtr->next;
    }

    // Return the highest id with an increment
    return id+1;
}

// This function is used to insert a New Movie into the Video Linked List
void VideoList::insertVideo(int vidId, string title, string genre, string production, int copies, string image) {
    // Set the variables for the Video Linked List
    VideoNode *newNode, *nodePtr, *previousNode;

    // Local Variable
    int id;

    // The vidId default value when inserting is 0
    // But when getting the data from the videos.txt it would diretcly insert the data
    if(vidId == 0) {
        // Get the next Video ID
        id = autoVideoIdIncrement();
    } else {
        // Get the direct value
        id = vidId;
    }

    // Check if the vidId already exist in the Video Linked List
    // If true display an error and stop the function from inserting the data
    if(videoIdDuplicate(vidId)) {
        cout << "Video Id Already Exist" << endl;
        system("pause");
        return;
    }
    
    // Allocate a new node & store the Data
    newNode = new VideoNode;
    newNode->videoId = id;
    newNode->videoTitle = title;
    newNode->videoGenre = genre;
    newNode->videoProduction = production;
    newNode->videoCopies = copies;
    newNode->videoImage = image;

	// If there are no nodes in the VideoNode
	// make the first node
	if (!head) {
        head = newNode;
        newNode->next = NULL;
	} else { 
        // Otherwise, insert a new node.
        // Initialize nodePtr to head of list
        nodePtr = head;
        previousNode = NULL;
        
        // Skip all nodes whose value member is less than num.
        while (nodePtr != NULL && nodePtr->videoId < id) {
            previousNode = nodePtr;
            nodePtr = nodePtr->next;
        }
        // If the new mode is to be the 1st in the list,
        // insert it before all other nodes.
        if (previousNode == NULL) {
            head = newNode;
            newNode->next = nodePtr;
        } else {
            previousNode->next = newNode;
            newNode->next = nodePtr;
		}
    }
}

// This function is called when the user Return a Video
void VideoList::returnVideo(int id) {
    // Set the variables for the Video Linked List
    VideoNode *nodePtr;
    nodePtr = head;

    // Traverse through the Video Linked List
    while (nodePtr) {
        // Loop and find the exact Video Id in the Video Linked List
        // Increment the Video Copies because the Video is Returned
        if(nodePtr->videoId == id) 
            nodePtr->videoCopies++;
        nodePtr = nodePtr->next;
    }
}

// This function traverse to all the nodes in the Video Linked List
// It ask for an argument Video ID and display the details of the equivalent Video ID
void VideoList::videoDetails(int id) {
    // Set the variables for the Video Linked List
    VideoNode *nodePtr;
    nodePtr = head;

    // Local Variables
    bool empty = true;
	
    // Traverse through the Video Linked List
    while (nodePtr) {
        // If the exact Video Id is found in the Video Link List
        // Display all the details of that Video
        if(nodePtr->videoId == id) {
            cout << "Movie Title: " << nodePtr->videoTitle << endl;
            cout << "Genre: " << nodePtr->videoGenre << endl;
            cout << "Production: " << nodePtr->videoProduction << endl;
            cout << "Number of Copies: " << nodePtr->videoCopies << endl;
            cout << "Movie Image: " << nodePtr->videoTitle + ".png" << endl;
            system(nodePtr->videoImage.c_str());
            empty = false;
        }
        nodePtr = nodePtr->next;
    }

    // Display an Error when there is no Matching Video ID Found
    if(empty)
        cout << "\nNo Matching Video ID Found." << endl << endl;
}

// This function display all details of a specific Video
// This function need a  Video Id
void VideoList::videoRentDetails(int id) {
    // Set the variables for the Video Linked List
    VideoNode *nodePtr;
    nodePtr = head;
    
    // Local Variables
    bool empty = true;
    int temp;

    // Traverse through the Video Linked List
    while (nodePtr) {
        // If the exact Video Id is found in the Video Link List
        // Display the Title and Number of Copies, of that Video
        if(nodePtr->videoId == id) {
            temp = nodePtr->videoCopies;
            cout << "Movie Title: " << nodePtr->videoTitle << endl;
            cout << "Number of Copies: " << --temp << endl;
            empty = false;
        }
        nodePtr = nodePtr->next;
    }

    // Display an Error when there is no Matching Video ID Found
    if(empty)
        cout << "\nNo Matching Video ID Found." << endl << endl;
}

// This function display all the Videos on the VideoNode Linked List
void VideoList::videoList() {
    // Set the variables for the Video Linked List
    VideoNode *nodePtr;

    // If there is no data in the 1st node of the Video Link List
    if (head == NULL)
    	cout << "The Video list is empty!" << endl;
    else {
        // Set the start of the node to the head or the 1st node of the Video Link List
        nodePtr = head;
        
        // Open the Directory where the Images should be located
        system("explorer images");

        // Set the formatting for the display
        cout << setw(10) << left << "Video ID" << setw(35) << "Movie Title" << setw(10) << "Genre" << setw(25) << "Production" << setw(35) << "Image [Directory is \\images]" << endl;
        
        // Traverse through the Video Linked List
        while (nodePtr) {
            // Display All the Details of the Video
            cout << setw(10) << nodePtr->videoId << setw(35) << nodePtr->videoTitle  << setw(10) << nodePtr->videoGenre << setw(25) << nodePtr->videoProduction << setw(35) << nodePtr->videoTitle + ".png" << endl;
            nodePtr = nodePtr->next;
        }
    }
}

// This function is called when the user Rent a Video
void VideoList::rentVideo(int id) {
    // Set the variables for the Video Linked List
    VideoNode *nodePtr;
    nodePtr = head;

    // Traverse through the Video Linked List
    while (nodePtr) {
        // If the exact Video Id is found in the Video Link List
        // Decrement the Copies of the Video
        if(nodePtr->videoId == id) {
            nodePtr->videoCopies--;
        }
        
        nodePtr = nodePtr->next;
    }
}

// This function checks if there is a still a Copy left of the Video
void VideoList::videoAvailableDetail(int id) {
    // Set the variables for the Video Linked List
    VideoNode *nodePtr;
    nodePtr = head;

    // Local Variables
    string available = "Not Available";
    bool found = false;

    // Traverse through the Video Linked List
    while (nodePtr) {
        // If the exact Video Id is found in the Video Link List
        // It would then display the title, genre, production, no. copies, and availability
        if(nodePtr->videoId == id) {
            found = true;

            // Check if the Video is still available
            if(nodePtr->videoCopies > 0)
                available = "Available";

            cout << "Movie Title: " << nodePtr->videoTitle << endl;
            cout << "Genre: " << nodePtr->videoGenre << endl;
            cout << "Production: " << nodePtr->videoProduction << endl;
            cout << "Number of Copies: " << nodePtr->videoCopies << endl;
            cout << "Availability: " << available << endl;
        }
        nodePtr = nodePtr->next;
    }

    // Would display an Error when there is no exact video id found
    if(!found)
        cout << "\nNo Video with similar Video ID Found!" << endl;
}

// This function is called to check if the video is Available
bool VideoList::videoAvailable(int id) {
    // Set the variables for the Video Linked List
    VideoNode *nodePtr;
    nodePtr = head;

    // Local Variable
    bool available = false;

    // Traverse through the Video Linked List
    while (nodePtr) {
        // If the exact Video Id is found in the Video Link List
        if(nodePtr->videoId == id)
            // Check if the number of copies is greater than 0
            if(nodePtr->videoCopies > 0)
                available = true;
        nodePtr = nodePtr->next;
    }
    return available;
}

// This function is called when the user need to find the video title
// Need an argument of Video Id
string VideoList::videoTitle(int id) {
    // Set the variables for the Video Linked List
    VideoNode *nodePtr;
    nodePtr = head;

    // Local Variable
    string temp = "";

    // Traverse through the Video Linked List
    while (nodePtr) {
        // If the exact Video Id is found in the Video Link List
        // Set the video title to the temp and return it
        if(nodePtr->videoId == id)
            temp = nodePtr->videoTitle;
        nodePtr = nodePtr->next;
    }
    return temp;
}

bool VideoList::videoIdDuplicate(int id) {
    // Set the variables for the Video Linked List
    VideoNode *nodePtr;
    nodePtr = head;

    // Traverse through the Video Linked List
    while (nodePtr) {
        // If the Video Id already exist in the Video Linked List
        // Return true
        if(nodePtr->videoId == id)
            return true;
        nodePtr = nodePtr->next;
    }
    return false;
}