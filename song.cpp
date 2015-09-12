//Mia Armstrong CS163
//Assignement 3
//File: song.cpp
/* this file has all the functions for the song_item data class.*/         

#include "song.h"

//This function initialises the arrays to NULL and the ints to zero.
song_item::song_item()
{
   title = NULL;
   artist = NULL;
   album = NULL;
   minutes = 0;
   plays = 0;
}
        
//This function deallocates the arrays.
song_item::~song_item()
{
   if (title)
      delete [] title;
  
   if (artist)
      delete [] artist;

   if (album)
      delete [] album;
}

         
//This function take sthe arguments and dynamically allocates
//them into arrays. It returns an int, 0 for failure and 1 for success.
int song_item::create_song(char * new_title, char * new_artist, char * new_album, float new_minutes, int new_plays)
{
   if (new_title && new_artist && new_album)
   {
      title = new char[strlen(new_title) + 1];
      strcpy(title, new_title); //deep copy title.
 
      artist = new char[strlen(new_artist) + 1];
      strcpy(artist, new_artist); //deep copy artist.

      album = new char[strlen(new_album) + 1];
      strcpy(album, new_album); //deep copy album;

      minutes = new_minutes;
   
      plays = new_plays;
    
      return 1;
    }
    else
       return 0;
   
}

//This function takes the argument and copies it into the song data members
//it returns an int, 0 for failure and 1 for success.         
int song_item::copy_entry(const song_item & a_new_song)
{
   if (title)
      delete [] title;
   if (artist)
      delete [] artist;
   if (album)
      delete [] album;  //deallocates any memory owned by the current object.

   if (!a_new_song.title || !a_new_song.artist || !a_new_song.album)
      return 0; //check for song

   title = new char[strlen(a_new_song.title) + 1];
   strcpy(title, a_new_song.title); //deep copy title.

   artist = new char[strlen(a_new_song.artist) + 1];
   strcpy(artist, a_new_song.artist); //deep copy artist

   album = new char[strlen(a_new_song.album) + 1];
   strcpy(album, a_new_song.album); //deep copy album. 

   minutes = a_new_song.minutes;

   plays = a_new_song.plays;

   return 1;
}

// This function will return non-zero if the feature sent in as an 
//argument matches the data member. It supplies the matching 
// back as an argument and increments the plays.         
int song_item::retrieve(char * key_word, song_item & found)const
{
   if (found.title)
      delete found.title;
   if (found.artist)
      delete found.artist;
   if (found.album)
      delete found.album;   

   bool match = false;
   int i = 0;
   while (title[i] != '\0')
   {
      for (int j = 0; title[i] != ' ' && title[i] != '\0'; ++i)
      {
         if (title[i] == key_word[j])
            match = true;
         else 
            match = false;

         ++j;
      }
      if (match)
      {
         found.title = new char[strlen(title) + 1];
         strcpy(found.title, title);
   
         found.artist = new char[strlen(artist) + 1];
         strcpy(found.artist, artist);

         found.album = new char[strlen(album) + 1];
         strcpy(found.album, album);

         found.minutes = minutes;

         found.plays = plays;

         return 1;
      }
      else
         ++i;
   }
   if (title)
      delete [] title;
   if (artist)
      delete [] artist;
   if (album)
      delete [] album;  //deallocates any memory owned by the current object.
   
}
         
int song_item::display() const
{
   if (title)
   {
      cout << endl;
      cout << "Title: " << title << endl;
      cout << "Artist: " << artist << endl;
      cout << "Album: " << album << endl;
      cout << "Minutes: " << minutes << endl;
      cout << "Number of plays: " << plays << endl;
      return 1;
   }
   else
      return 0;
}

int song_item::remove()
{
   if (title)
      delete [] title;

   if (artist)
      delete [] artist;
 
   if (album)
      delete [] album;
}

int song_item::play()
{
   ++plays;
}
