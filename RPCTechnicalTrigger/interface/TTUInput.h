// $Id: $
#ifndef INTERFACE_TTUINPUT_H 
#define INTERFACE_TTUINPUT_H 1

// Include files
#include <bitset>

/** @class TTUInput TTUInput.h interface/TTUInput.h
 *  
 *
 *  @author Andres Osorio
 *
 *  email: aosorio@uniandes.edu.co
 *
 *  @date   2008-10-16
 */
class TTUInput {
public: 
  /// Standard constructor
  TTUInput( ); 
  
  virtual ~TTUInput( ); ///< Destructor
  
  TTUInput( const TTUInput & _in)
  {
    for(int i=0; i < 12; ++i) 
      input_sec[i] = _in.input_sec[i];
  };
  
  TTUInput & operator=( const TTUInput & rhs )
  {
    if (this == &rhs) return (*this);
    for(int i=0; i < 12; ++i)
      (*this).input_sec[i] = rhs.input_sec[i];
    return (*this);
  };
  
  std::bitset<6> input_sec[12];
  
  void reset();
  
protected:
  
private:
  
};
#endif // INTERFACE_TTUINPUT_H
