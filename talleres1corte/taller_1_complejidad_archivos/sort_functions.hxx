#ifndef __SORT_FUNCTIONS__HXX__
#define __SORT_FUNCTIONS__HXX__

// -------------------------------------------------------------------------
//Su tarea es comprobar si los elementos ya quedaron ordenados de menor a mayor.
template< class I > 
bool is_sorted( I first, I last )
{
  if( first == last )
    return( true );
  I next = first;
  while( ++next != last )
  {
    if( *next < *first )
      return( false );
    ++first;

  } // elihw
  return( true );
}

#endif // __SORT_FUNCTIONS__HXX__

// eof - sort_functions.hxx
