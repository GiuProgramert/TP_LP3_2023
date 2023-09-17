#include <cassert> 
#include "listing_1.3.hpp" 
double reciprocal (int i) { 
 // I should be non-zero. 
 assert (i != 0); 
 return 1.0/i; 
} 