// $Id: $
// Include files 



// local
#include "Data.h"

//-----------------------------------------------------------------------------
// Implementation file for class : Data
//
// 2008-04-29 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
Data::Data( const char * f_name ) {
  
  m_in = new std::ifstream();
  
  m_in->open(f_name);

  if (!m_in->good()) std::cout << "Data> could not open input file" << std::endl;
  
}

//=============================================================================
// Destructor
//=============================================================================

Data::~Data() {
  
  m_in->close();
  delete m_in;

  std::vector<MadWeightResults*>::iterator itr;
  
  for( itr = m_Results.begin(); itr != m_Results.end(); ++itr)
    delete (*itr);
  
    
} 

//=============================================================================

void Data::Read()
{

  float  tag;
  float  current_tag;
  double weight;
  double weightErr;

  current_tag = 0.0;
  
  MadWeightResults * mwr;
  
  while(1) {
    
    if( !m_in->good() ) break;

    (*m_in) >> tag >> weight >> weightErr;

    if( m_in->eof() ) break;
    
    double intpart = 0.0;
    double evt = modf( tag, &intpart );
    
    if ( current_tag != intpart ) {
      
      //std::cout << " Found new block of results" << std::endl;
      mwr = new MadWeightResults();
      mwr->m_ID = (int)intpart;
      m_Results.push_back(mwr);
      current_tag = intpart;
      
    }
    
    mwr->m_weights.push_back( weight );
    
  }
  
  
}

void Data::Show()
{
  
  std::cout << "Blocks found: " << m_Results.size() << std::endl;
  
  std::vector<MadWeightResults*>::iterator itr;
  
  for( itr = m_Results.begin(); itr != m_Results.end(); ++itr) {
    
    std::cout << "block contents: " << (*itr)->m_weights.size() << std::endl;
   
    std::vector<double>::iterator itr2;
    
    for( itr2 = (*itr)->m_weights.begin(); itr2 != (*itr)->m_weights.end(); ++itr2 )
      std::cout << "value " << (*itr2) << std::endl;
    
    
  }
  
  
}
