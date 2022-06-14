//This is the main file that would be running all the files
#include <iostream>
#include <string>
#include "videos.h"
#include "customers.h"
#include "customer-rent.h"
using namespace std;
using namespace ns;

int mainMenu();
int maintenanceMenu();

int main() {
    // Set the Variable for the Objects
    VideoList vidList;
    CustomerList cusList;
    CustomerRentList cusRentList;

    // Local Variable
    int choice, vidId, customerID, copies, temp;
    string title, genre, production, image, qa, name, address;
    bool loop = true;

	do {
        choice = mainMenu();
        system("cls");
        
        if (choice == 1) {
            //For the New Video
            cout << "[1] NEW VIDEO" << endl << endl;
            cout << "Video ID: " << vidList.autoVideoIdIncrement() << endl;
            cout << "Movie Title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Genre: ";
            getline(cin, genre);
            cout << "Production: ";
            getline(cin, production);
            cout << "Number of Copies: ";
            cin >> copies;
            cout << "Movie Image Filename: ";
            cin.ignore();
            getline(cin, image);
        
            vidList.insertVideo(0, title, genre, production, copies, image);
            cout << endl << endl;
            system("pause");

        } else if (choice == 2)	{
            // For Rent a Video
            cout << "[2] RENT A MOVIE" << endl << endl;
            cout << "Customer ID: ";
            cin >> customerID;
            cusList.customerDetails(customerID);
            cout << "\n\n-------------------------------------------------" << endl;
            cout << "Videos to Rent....\n" << endl;
            vidList.videoList();
            cout << "-------------------------------------------------" << endl << endl;
            do {
                cout << "Video ID: ";
                cin >> vidId;
                vidList.videoRentDetails(vidId);
                cusRentList.customerRentPush(customerID, vidId);
                vidList.rentVideo(vidId);
                cout << "\nRent another Video? ";
                cin.ignore();
                getline(cin,qa);
                if(qa == "Y" || qa == "y") {}
                else if (qa == "N" || qa == "n")
                    loop = false;
                cout << "\n";
            } while(loop);
            loop = true;
            system("\npause");

        } else if (choice == 3) {
            // For Return of Video
            cout << "[3] RETURN A MOVIE" << endl << endl;
            cout << "Customer ID: ";
            cin >> customerID;
            cusList.customerDetails(customerID);
            cout << "\n\nVides Rented...." << endl;
            cusRentList.customerRentPop(customerID, vidList);
            system("pause");

        } else if (choice == 4) {
            // For showing the Specific Details of a Video
            cout << "[4] SHOW VIDEO DETAILS" << endl << endl;
            cout << "Video ID: ";
            cin >> vidId;
            vidList.videoDetails(vidId);
            cout << endl << endl;
            system("pause");

        } else if (choice == 5) {
            // For displaying all the videos
            cout << "[5] DISPLAY ALL VIDEOS" << endl << endl;
            vidList.videoList();
            system("pause");

        } else if (choice == 6) {
            // For checking the availability of video
            // Video Copy should be greater than 0 to be Available
            cout << "[6] CHECK VIDEO AVAILABILITY" << endl << endl;
            cout << "Video ID: ";
            cin >> vidId;
            vidList.videoAvailableDetail(vidId);
            cout << endl << endl;
            system("pause");

        } else if (choice == 7) {
            // For Customer Maintinance Menu
            do {
                choice = maintenanceMenu();
                system("cls");
                if(choice == 1) {
                    // For adding a New Customer
                    cout << "[7-1] ADD NEW CUSTOMER" << endl << endl;
                    cout << "Customer ID: " << cusList.autoCustomerIdIncrement() << endl;
                    cout << "Name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Address: ";
                    getline(cin, address);

                    cusList.customerEnqueue(0, name, address);
                    cout << "Customer Successfully Added" << endl << endl;
                    system("pause");

                } else if(choice == 2) {
                    // For Showing Specific Customer Details
                    cout << "[7-2] SHOW CUSTOMER DETAILS" << endl << endl;
                    cout << "Customer ID: ";
                    cin >> customerID;

                    // Function used to show the Customer Details
                    cusList.customerDetails(customerID);
                    cout << endl << endl;
                    system("pause");

                } else if(choice == 3) {
                    // For listing all the Videos the the specific Customer Rented
                    cout << "[7-3] LIST ALL VIDEOS RENTED BY A CUSTOMER" << endl << endl;
                    cout << "Customer ID: ";
                    cin >> customerID;
                    cusRentList.customerRentList(customerID, vidList);
                    system("pause");

                } else if(choice == 4) {
                } else {
                    cout << "Invalid Input!" << endl << endl;
                    system("pause");
                }
            } while(choice != 4);

        } else if (choice == 8)	{
            // Exit of Program
            // Dequeue all the 3 Structures/Class
            vidList.~VideoList();
            cusList.~CustomerList();
            cusRentList.~CustomerRentList();
            exit(0);
        } else {
            cout << "Invalid Input!" << endl << endl;
            system("pause");
        }
        
        cout << endl;
    } while (choice != 8);
}


int mainMenu() {
    int choice;
    system("cls");
    cout << " << Video System >> " << endl << endl;
    cout << "[1] New Video" << endl;
    cout << "[2] Rent a Video" << endl;
    cout << "[3] Return a Video" << endl;
    cout << "[4] Show Video Details" << endl;
    cout << "[5] Display all Videos" << endl;
    cout << "[6] Check Video Availability" << endl;
    cout << "[7] Customer Maintinance" << endl;
    cout << "[8] Exit Program" << endl << endl;
    cout << "Enter Choice: ";
    cin >> choice;
    return(choice);
}

int maintenanceMenu() {
    int choice;
    system("cls");
    cout << " << Customer Maintinance >> " << endl << endl;
    cout << "[1] Add New Customer" << endl;
    cout << "[2] Show Customer Details" << endl;
    cout << "[3] List of Videos Rented by a Customer" << endl;
    cout << "[4] Back" << endl;
    cout << "Enter Choice: ";
    cin >> choice;
    return(choice);
}