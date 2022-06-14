#pragma once
#include <string>

namespace ns
{
	class VideoList	{
	   	private:
	   	// This Structure would be a Linked List
			struct VideoNode {
				int videoId;
				std::string videoTitle;
				std::string videoGenre;
				std::string videoProduction;
				int videoCopies;
				std::string videoImage;
				struct VideoNode *next;
		   	};
			VideoNode *head;
		public:
			// The Codes below are the public Function
			VideoList(); // Constructor
			~VideoList(); // Deconstructor
			void insertVideo(int id, std::string title, std::string genre, std::string production, int copies, std::string image); // Insertion of a New Video
			void rentVideo(int id); // Renting a Video
			void returnVideo(int id); // Return all the video that the Customer rent/s
			void videoDetails(int id); // Details about the specified Video using Video ID
			void videoRentDetails(int id); // Would display the Movie Title and Number of Copies, of the specific user
			void videoList(); // List all the Video and their Details
			void videoAvailableDetail(int id); // Check if the Video is Available by looking at the Number of Copies
			int autoVideoIdIncrement(); // For the Auto Generation of Video ID
			bool videoAvailable(int id); // Would return true if the video has 1 or more number of copies
			std::string videoTitle(int id); // Would return the title of the specific video
	};
}