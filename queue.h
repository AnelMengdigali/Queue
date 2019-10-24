
#ifndef QUEUE_INCLUDED 
#define QUEUE_INCLUDED  1

#include <iostream>
#include <initializer_list>

struct queue
{
   size_t current_size; 
   size_t current_capacity; 
   size_t begin;
   size_t end;   

   double* data; 
      // INVARIANТ: a function checkinvariant( ) const checks the invariant  

   void ensure_capacity( size_t c );
      // Ensure that queue has capacity of at least c. 

   // Return i+1, but 0 if we reach current_capacity.
   size_t next( size_t i ) const 
   {
      i = i + 1; 
      if( i == current_capacity )
         i = 0; 
      return i;
   }

   void checkinvariant( ) const;
      // For testing the invariants

   void printfields( std::ostream& ) const;
      // For checking all fields of the queue by printing 

public: 
      //Function prototypes:

   queue( );               
      //Default constructor constructing empty queue

   queue( const queue& q );
      //Copy constructor copying from queue q

   ~queue( );
      //Destructor freeing allocated memory

   const queue& operator = ( const queue& q );
      //Assignment operator

   queue( std::initializer_list<double> init );
      //Other constructor that does initialization of form q = { 1,2,3 }

   void push( double d );  
      //Add an element at the end

   void pop( );
      //Delete the first element in the queue

   void clear( );
      //Make the queue empty

   double peek( ) const;
      //Returns the first element in the queue

   size_t size( ) const;
      //Returns a current size of the queue

   bool empty( ) const; 
      //Returns 1(true) if the queue is empty
   
   friend std::ostream& operator << ( std::ostream& , const queue& ); 
}; 
      //Additional method that does printing

std::ostream& operator << ( std::ostream& , const queue& );

#endif


