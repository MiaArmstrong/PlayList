//Mia Armstrong CS163
//Assignment 3
//File: main.cpp
/* This file is the test bed for the Table ADT.
This program loads a list of songs from an external file and stores them in a hash table adt. Each song includes a title, an artist, an album name, the number
of minutes, and how many times it has been played. The user can enter a key word and retrieve all songs in the table with that word in the title. The user can also delete a song by key word and then chose one of the songs from the results to delete.*/

#include "table.h"

const int SIZE = 100;

bool again();

int main()
{
   char filename[SIZE] = "data.txt";
   song_item a_song, found;
   song_item songs[LIST_SIZE];
   table my_music;
   char new_title[SIZE]; //temporary for song_info
   char new_artist[SIZE];
   char new_album[SIZE];
   char key_word[SIZE];
   float new_minutes = 0;
   int new_plays = 0;
   int  success;
   

//loads song library into hash table from file.
//returns false if file cannot open or does not work.
   ifstream file_in;
   file_in.open(filename); //reads in file.
   if (!file_in)
   {
      cout << "Could not open file " << filename << " for reading." << endl;
      return 0;
   }

   //connect to the file and ready to read
   file_in.get(new_title, SIZE, ';'); file_in.ignore(SIZE, ';');
   while (!file_in.eof()) //previous read was successful.
   {
      file_in.get(new_artist, SIZE, ';'); file_in.ignore(SIZE, ';');
      file_in.get(new_album, SIZE, ';'); file_in.ignore(SIZE, ';');
      file_in >> new_minutes; file_in.ignore(SIZE, ';');
      file_in >> new_plays; file_in.ignore(SIZE, ';'); 
      a_song.create_song(new_title, new_artist, new_album, new_minutes, new_plays);
      my_music.insert(new_title, a_song);
      file_in.get(new_title, SIZE, ';'); file_in.ignore(SIZE, ';');
   }
   file_in.close(); 

   success = my_music.display_all();
   
   if (success == 0)
      cout << "Unable to display music." << endl;

   do
   {
      cout << "Enter a key word: " << endl;
      cin.get(key_word, SIZE); cin.ignore(SIZE, '\n');
      key_word[0] = toupper(key_word[0]);
  
      success = my_music.retrieve(key_word, songs);
      if (success != 0)
      {
         cout << "\n\nHere are the songs that contain " << key_word << " in the title." << endl;
         for (int i = 0; i < LIST_SIZE; ++i)
         {
            songs[i].play();
            songs[i].display();
         }
      }
      else
         cout << "\n\nThere were no matches." << endl;
            
     
      for (int i = 0; i < LIST_SIZE; ++ i)
         songs[i].remove();  
      
      
         
    }while(again());

      return 0;
}

//Asks user if the would like to search for another song.
//Returns true for yes and falser for everything else.
bool again()
{
   char responce;
   cout << "\nEnter another key word (y/n)? " << endl;
   cin >> responce; cin.ignore(SIZE, '\n');

   if (responce == 'y' || responce == 'Y')
      return true;
   else
      return false;
}
