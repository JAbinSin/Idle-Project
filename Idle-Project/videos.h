// This file would all hold the ADT for the Video ADT
#pragma once
#include <string>

namespace ns
{
	class VideoList	{
	   private:
		   struct VideoNode {
			    int videoId;
                std::string videoTitle;
                std::string videoGenre;
				std::string videoProduction;
				int videoCopies;
				std::string videoImage;
			    struct VideoNode *next;
		   };
		   VideoNode *head, *current;
        public:
			// The Codes below are a public Function
	        VideoList(); // Constructor
		    ~VideoList(); // Deconstructor
		    void insertVideo(int id, std::string title, std::string genre, std::string production, int copies, std::string image); // Insertion of a New Video
		    void rentVideo(int id); // Renting a Video
		    void returnVideo(int id); // Return all the video that the Customer rent/s
		    void videoDetails(int id); // Details about the specified Video using Video ID
			void videoRentDetails(int id);
            void videoList(); // List all the Video and their Details
			void videoAvailableDetail(int id); // Check if the Video is Available by looking at the Numebr of Copies
			int autoVideoIdIncrement(); // For the Auto Generation of Video ID    
			bool videoAvailable(int id);
			std::string videoTitle(int id);
	};
}