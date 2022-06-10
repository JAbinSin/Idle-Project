#include <iostream>
#include <fstream>
#include "videos.h"

using namespace std;
using namespace ns;

// Constructor
VideoList::VideoList() {
	head = NULL;

    ifstream file("videos.txt");
    string title, genre, production, id, copies, image;
	int cId, cCopies;

    if(file.is_open()) {
        while(!file.eof()) {
            getline(file, id, ',');
            getline(file, title, ',');
            getline(file, genre, ',');
            getline(file, production, ',');
            getline(file, copies, ',');
            getline(file, image, '\n');

			if(!id.empty()) {
				cId = stoi(id);
				cCopies = stoi(copies);
				insertVideo(cId, title, genre, production, cCopies, image);
			}
        }
    }
	file.close();
}

// Deconstructur
VideoList::~VideoList() {
    ofstream file("videos.txt");
	VideoNode *nodePtr, *nextNode;
    nodePtr = head;

	if(file.is_open()) {
		while (nodePtr) {
			file << nodePtr->videoId << "," << nodePtr->videoTitle << "," << nodePtr->videoGenre << "," << nodePtr->videoProduction << "," << nodePtr->videoCopies << "," << nodePtr->videoImage << endl;
			nodePtr = nodePtr->next;
		}
	}
	file.close();
}

// Used for the Auto Incremention of the Video ID
int VideoList::autoVideoIdIncrement() {
    int id = 0;
	VideoNode *nodePtr;
    nodePtr = head;
    while(nodePtr) {
        id = nodePtr->videoId;
		nodePtr = nodePtr->next;
    }
    return id+1;
}

// This function is used to insert a New Movie in the Linked List
void VideoList::insertVideo(int vidId, string title, string genre, string production, int copies, string image) {
	VideoNode *newNode, *nodePtr, *previousNode;
	int id;

	if(vidId == 0) {
		//Get the next Video ID
    	id = autoVideoIdIncrement();
	} else {
		id = vidId;
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
	} else { // Otherwise, insert a new node.
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

void VideoList::returnVideo(int id) {
	VideoNode *nodePtr;
    nodePtr = head;

    while (nodePtr) {
        if(nodePtr->videoId == id) 
            nodePtr->videoCopies++;
        nodePtr = nodePtr->next;
    }
}

// This function traverse to all the nodes in the VideoNode Linked List
// It ask for an input ID and output the details of the equivalent ID
void VideoList::videoDetails(int id) {
    bool empty = true; // Use to check if there is a Video found or not
	VideoNode *nodePtr;
    nodePtr = head;

    while (nodePtr) {
        if(nodePtr->videoId == id) {
            cout << "Movie Title: " << nodePtr->videoTitle << endl;
            cout << "Genre: " << nodePtr->videoGenre << endl;
            cout << "Production: " << nodePtr->videoProduction << endl;
            cout << "Number of Copies: " << nodePtr->videoCopies << endl;
            cout << "Movie Image: " << nodePtr->videoImage << endl;
            empty = false;
        }
        nodePtr = nodePtr->next;
    }

    if(empty)
        cout << "\nNo Matching Video ID Found." << endl << endl;
}

void VideoList::videoRentDetails(int id) {
    bool empty = true; // Use to check if there is a Video found or not
    int temp;
	VideoNode *nodePtr;
    nodePtr = head;

    while (nodePtr) {
        if(nodePtr->videoId == id) {
            temp = nodePtr->videoCopies;
            cout << "Movie Title: " << nodePtr->videoTitle << endl;
			cout << "Number of Copies: " << --temp << endl;
            empty = false;
        }
        nodePtr = nodePtr->next;
    }

    if(empty)
        cout << "\nNo Matching Video ID Found." << endl << endl;
}

// This function display all the Videos on the VideoNode Linked List
void VideoList::videoList() {
	VideoNode *nodePtr;
	if (head == NULL)
		cout << "The Video list is empty!" << endl;
	else {
		nodePtr = head;
		while (nodePtr) {
			cout << "Video ID: " << nodePtr->videoId << endl;
            cout << "Movie Title: " << nodePtr->videoTitle << endl;
            cout << "Genre: " << nodePtr->videoGenre << endl;
            cout << "Production: " << nodePtr->videoProduction << endl;
            cout << "Number of Copies: " << nodePtr->videoCopies << endl;
            cout << "Movie Image:" << nodePtr->videoImage << endl << endl;
			nodePtr = nodePtr->next;
		}
	}
}


void VideoList::rentVideo(int id) {
	VideoNode *nodePtr;
    nodePtr = head;

    while (nodePtr) {
        if(nodePtr->videoId == id) {
            nodePtr->videoCopies--;
            cout << "Loop!" << endl;
        }
            
        nodePtr = nodePtr->next;
    }
}

// This function checks if there is a still a Copy left of the Video
void VideoList::videoAvailableDetail(int id) {
	VideoNode *nodePtr;
    nodePtr = head;
    string available = "Not Available";
    bool found = false;

    while (nodePtr) {
        if(nodePtr->videoId == id) {
            found = true;
            if(nodePtr->videoCopies > 0)
                available = "Available";

            cout << "Movie Title: " << nodePtr->videoTitle << endl;
            cout << "Genre: " << nodePtr->videoGenre << endl;
            cout << "Producttion: " << nodePtr->videoProduction << endl;
            cout << "Number of Copies: " << nodePtr->videoCopies << endl;
            cout << "Availability: " << available << endl;
        }
        nodePtr = nodePtr->next;
    }
    if(!found)
        cout << "\nNo Video with similar Video ID Found!" << endl;
}

bool VideoList::videoAvailable(int id) {
	VideoNode *nodePtr;
    nodePtr = head;
	bool available = false;

	while (nodePtr) {
        if(nodePtr->videoId == id) 
            if(nodePtr->videoCopies > 0)
                available = true;
        nodePtr = nodePtr->next;
    }
	return available;
}

string VideoList::videoTitle(int id) {
	string temp;
	VideoNode *nodePtr;
    nodePtr = head;

    while (nodePtr) {
        if(nodePtr->videoId == id) 
            temp = nodePtr->videoTitle;
        nodePtr = nodePtr->next;
    }
	return temp;
}