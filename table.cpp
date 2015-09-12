//Mia Armstrong CS163
//Assignment 3
//File: table.cpp
/*This file has all the functions for the table adt.*/

#include "table.h"



         
table::table(int size)
{
   hash_table_size = size;

   hash_table = new node * [size];//allocate the hash table dynamically

   for (int i = 0; i < size; ++i)
      hash_table[i] = NULL; //initializes the pointers in the array to NULL.

   key = NULL;
   key2 = NULL;

   songs = new song_item[LIST_SIZE];
}
         
table::~table()
{
   if (hash_table)
   {
      for (int i = 0; i < hash_table_size; ++i)
      {
         while (hash_table[i])
         {
            node * temp = hash_table[i]->next;
            delete hash_table[i];
            hash_table[i] = NULL;
            hash_table[i] = temp;
         }
      }
      delete [] hash_table;
    }       
   if (key)
      delete [] key;
   if (key2)
      delete [] key2;

   if (songs)
   {
      for (int i = 0; i < LIST_SIZE; ++ i)
      {
         songs[i].remove();  
      }
  
      delete [] songs;
   }
}
         
int table::insert(char * key_value, const song_item & to_add)
{
  
   
   int i = 0;

   while (i < strlen(key_value) - 1)
   {
      if (key)
         delete [] key;

      if (key2)
         delete [] key2;

      key = new char[strlen(key_value) + 1];
      
      int count = 0;
      for (i; key_value[i] != ' ' && key_value[i] != '\0'; ++i)
      {
         key[i] = key_value[i];
         ++count;
      }
      key[count] = '\0';
      
      key2 = new char[strlen(key) + 1];
      strcpy(key2, key);
      
      if (strcmp(key2, "The") != 0 && strcmp(key2, "A") !=0 && strcmp(key2, "An") != 0 && strcmp(key2, "Of") != 0 && strcmp(key2, "Is") != 0 && strcmp(key2, "In") != 0
                 && strcmp(key2, "For") != 0 && strcmp(key2, "That") != 0 && strcmp(key2, "This") != 0 && strcmp(key2, "And") !=0) 
      {
         int N = hash_function(key2);
         node * temp = new node;
         temp->song.copy_entry(to_add);
   
         if (!hash_table[N])
         {
            hash_table[N] = temp;
            temp->next = NULL;
         }
         else
         {
            temp->next = hash_table[N];
            hash_table[N] = temp;
         }
      }

      ++i;
   }
   return 1;

}
         
int table::retrieve(char * word_to_find, song_item * found_songs)const
{
   int N = hash_function(word_to_find);
   int success = 0;

   node * current = hash_table[N];

   if (hash_table[N])
   {
      int i = 0;
      while (current)
      {
         current->song.retrieve(word_to_find, found_songs[i]);
         ++i;
         current = current->next;
      }
      return 1;
    } 
   else 
      return 0;
}

int table::display_all() const
{
   if(!hash_table)
      return 0;

   for (int i = 1; i < hash_table_size; ++i)
   {
      node * current = hash_table[i];
      int success = 0;
      cout << "Chain " << i << ": " << endl;
      while(current)
      {
         success = current->song.display();
         if (success == 0)
            return 0;
         current = current->next;
      }
      cout << endl << endl;
   }
   return 1;
}

         
int table::hash_function(char * key_value) const
{
   if (!key_value)
      return 0;

   int total = 0; //holds the value of the sum of the ASCII values in the array
   int key = 0; // holds the value of the key after computaions are finished.

   for (int i = 0; i < strlen(key_value); ++i)
      total = total + key_value[i]; //sums the ASCII values of the letters
   
   key = ((total << 6) ^ (total >> 26)) % hash_table_size;
   //takes the total then bit shifts it to the left and folds it using xor with
   // the total bit shifted to the right, then mod it by the hash table size.

   return key;
}

