//Mia Armstrong CS163
//Assignment 3
//File: table.h
/* This file is the header file for the table adt and the node struct.*/

#include "song.h"

const int LIST_SIZE = 10; //max size of the array of songs.

struct node
{
   song_item song;
   node * next;
};

class table
{
   public:
         table(int size = 7);
         ~table();
         int insert(char * key_value, const song_item & to_add);
         int retrieve(char * word_to_find, song_item * found_songs)const;
         int display_all() const;
         int hash_function(char * key_value) const;
   private:
         node ** hash_table; //a dynamically allocated array of head pointers.
         int hash_table_size;
         char * key;
         char * key2;
         song_item * songs; //a dynamically allocated array of songs.  
};
