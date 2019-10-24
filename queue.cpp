
#include "queue.h"


void queue::ensure_capacity( size_t c ) 
{
   if( current_capacity < c )
   {
      // New capacity will be the greater of c and
      // 2 * current_capacity. 

      if( c < 2 * current_capacity )
         c = 2 * current_capacity;

      if( c < 8 ) 
         c = 8;
 
      double* newdata = new double[c];
      for( size_t s = 0; s < current_size; ++ s )
      {
         newdata[s] = data[ begin ];
         begin = next( begin );
      }

      current_capacity = c;
      begin = 0;
      end = current_size;

      delete[] data;
      data = newdata;
   }
}

void queue::printfields( std::ostream& out ) const
{
   out << "   current_size =     " << current_size << "\n";
   out << "   current_capacity = " << current_capacity << "\n";
   out << "   begin =            " << begin << "\n";
   out << "   end =              " << end << "\n";
}

void queue::checkinvariant( ) const 
{

   if( current_capacity == 0 )
   {
      std::cout << "current capacity == 0\n";
      printfields( std::cout ); 
      std::abort( );
   }

   if( begin >= current_capacity ) 
   {
      std::cout << "begin >= current_capacity\n";
      printfields( std::cout ); 
      std::abort( );
   }

   if( end >= current_capacity )
   {
      std::cout << "end >= current_capacity\n";
      printfields( std::cout ); 
      std::abort( );
   }

   if( current_size > current_capacity )
   {
      std::cout << "current_size > current_capacity\n";
      printfields( std::cout ); 
      std::abort( );
   }

   if( ( begin + current_size ) % current_capacity != end )
   {
      std::cout << 
         "distance between begin and end does not fit to current_size\n";
      printfields( std::cout );  
      std::abort( );
   }
}
 
queue::queue()
   : current_size{0},
     current_capacity{10},
     data{ new double[ current_capacity ] },
     begin{0},
     end{0}
{ }           

queue::queue( const queue& q )
   : current_size{ q. current_size },
     current_capacity{ q. current_capacity },
     data{ new double[ current_capacity ] },
     begin{0},
     end{ current_size }

{ 
   size_t copy_data = q.begin;

   for( size_t receive_data = 0; receive_data != current_size; ++receive_data ) 
   {   
      data[ receive_data ] = q. data[ copy_data ];
      copy_data = q.next( copy_data );  
   }
}

queue::~queue( )
{
   delete[] data;
}

const queue& queue::operator = ( const queue& q )
{	
   ensure_capacity ( q. current_capacity );

   begin = 0;
   end = q.current_size;

   size_t assign_data = q.begin;
	
   for ( size_t receive_data = 0; receive_data != current_size; ++receive_data )
   {	
      data[ receive_data ] = q. data[ assign_data ];
      assign_data = q.next( assign_data );
   }
	
   current_size = q. current_size;

   return q;
	
}

queue::queue( std::initializer_list<double> init )
   : queue()
{
   for ( double d: init ) 
   {
      push(d);
   }
}

void queue::push( double d ) 
{
   ensure_capacity( current_size + 1 );

   data[ end ] = d;

   end = next( end );

   current_size = current_size + 1;
}


void queue::pop( ) 
{
   //precondition: stack must be non-empty
   current_size = current_size - 1; 

   begin = next( begin );
}


void queue::clear( ) 
{
   current_size = 0;

   begin = 0;
   end = 0;
}

double queue::peek( ) const 
{
   //precondition: stack must be non-empty
   return data[ begin ];
}


size_t queue::size( ) const
{
   return current_size;
}


bool queue::empty( ) const
{
   return current_size == 0;
}

std::ostream& operator << ( std::ostream& out, const queue& q )
{
   out << "[";

   size_t it_data = q. begin; 

   for( size_t i = 0; i < q. size( ); ++ i )
   {
      if(i) out << ", ";
      else out << " ";
      out << q. data[ it_data ];

      it_data = q.next( it_data ); 
   }

   out << " ]";

   return out;
}

