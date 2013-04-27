// $Id: $
// Include files 



// local
#include "WeightsAnalyzer.h"

//-----------------------------------------------------------------------------
// Implementation file for class : WeightsAnalyzer
//
// 2012-09-14 : Andres Osorio
//-----------------------------------------------------------------------------

std::ifstream& operator>>(std::ifstream &istr, EventWeights &rhs) {

  bool m_debug = false;
  int entry = 0;
  
  // data 
  int event = 0;
  int perm_pos = -1;
  int config_pos = -1;
  double weight = 0.0;
  double weight_err = 0.0;
  
  int prev_perm_pos = -1;
  double weight_sum = 0.0;
  double weight_err_sum = 0.0;
  double counter = 1.0;
  
  std::vector<double> weights;
  std::vector<double> weights_err;
  
  while( istr.peek() != 42 ) {
    
    istr >> event >> perm_pos >> config_pos >> weight >> weight_err;

    if( entry == 0 ) prev_perm_pos = perm_pos;
    
    rhs.m_event = event;

    if ( (perm_pos != prev_perm_pos) ) {
      
      counter = 0.0;
      std::vector<double>::iterator itrWgt;
      for( itrWgt = weights.begin(); itrWgt != weights.end(); ++itrWgt ) {
        weight_sum+=(*itrWgt);
        counter += 1.0;
      }
      
      rhs.m_perm_weight[prev_perm_pos] = weight_sum / counter;
      weight_sum = 0.0;
      weight_err_sum = 0.0;
      weights.clear();
      weights_err.clear();
      prev_perm_pos = perm_pos;
      
    } 
    
    weights.push_back( weight );
    weights_err.push_back ( weight_err );
        
    ++entry;

    if ( istr.peek() == 10 ) istr.ignore(1);

    if ( istr.peek() == 42 ) { // this is the very last line for this event
      
      counter = 0.0;
      std::vector<double>::iterator itrWgt;
      for( itrWgt = weights.begin(); itrWgt != weights.end(); ++itrWgt ) {
        weight_sum+=(*itrWgt);
        counter += 1.0;
      }
      
      rhs.m_perm_weight[prev_perm_pos] = weight_sum / counter;
      weight_sum = 0.0;
      weight_err_sum = 0.0;
      weights.clear();
      weights_err.clear();
      prev_perm_pos = perm_pos;
      
    }

    if( istr.eof() ) break;

  }
  
  if ( m_debug ) { 

    std::cout << rhs.m_event << '\n';
    std::map<int,double>::iterator itr;
    
    for(itr = rhs.m_perm_weight.begin(); itr != rhs.m_perm_weight.end(); ++itr) {
      std::cout << " " << (*itr).first << '\t' << (*itr).second << '\n';
    }
    
  }
    
  if ( istr.peek() == 42 ) { 
    istr.ignore(1); 
    
    if ( istr.peek() == 10 ) {
      istr.ignore(1);
      
      if ( istr.peek() == 42 ) {
        istr.ignore(1);
        if( m_debug ) std::cout << " found a second * " << rhs.m_event << std::endl; 
        rhs.m_event = -1;
      }
      
    }
    
  }
  
  if( m_debug )  std::cout << " event read " << rhs.m_event << std::endl;
  
  return istr;
  
}


//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
WeightsAnalyzer::WeightsAnalyzer( const char * infile ) {

  m_in = new std::ifstream();

  m_in->open(infile);
  
  if (!m_in->good()) std::cout << "Data> could not open input file" << std::endl;
  
}
//=============================================================================
// Destructor
//=============================================================================
WeightsAnalyzer::~WeightsAnalyzer() { 

  if(m_in) {
    m_in->close(); 
    delete m_in;
  }
    
  if(m_eventweight) delete m_eventweight;
  
} 

//=============================================================================
int WeightsAnalyzer::Next( ) 
{
  
  if( !m_in->good() ) return -1;
  
  m_eventweight = new EventWeights();
    
  (*m_in) >> (*m_eventweight);

  if ( m_eventweight->m_event == -1 ) return -2; //return -2 in case no data for this event
  
  if( m_in->eof() ) return -1;
  
  //std::cout << "WeightsAnalyzer::Next> ready " << std::endl;

  return 1;
      
}
