#include "LHCOParser.h"

////////////////////////////////////////////
//operator definitions
//////////////////////
//1

std::ifstream& operator>>(std::ifstream &istr, pgsObject &rhs) {
  istr >> rhs.idpart; 
  istr >> rhs.type;
  istr >> rhs.eta ;
  istr >> rhs.phi ;
  istr >> rhs.pt; 
  istr >> rhs.jmas;
  istr >> rhs.ntrk ;
  istr >> rhs.btag ;
  istr >> rhs.hadem ;
  istr >> rhs.dum1 ;
  istr >> rhs.dum2; 
  return istr;
}

std::ostream& operator<<(std::ostream &ostr, pgsObject &rhs) {
  
  ostr << rhs.idpart << '\t'; 
  ostr << rhs.type << '\t'; 
  ostr.precision(3);
  ostr << rhs.eta << '\t'; 
  ostr << rhs.phi << '\t';
  ostr << rhs.pt << '\t'; 
  ostr << rhs.jmas << '\t'; 
  ostr << rhs.ntrk << '\t'; 
  ostr << rhs.btag << '\t'; 
  ostr << rhs.hadem << '\t'; 
  ostr << rhs.dum1 << '\t'; 
  ostr << rhs.dum2 << '\t'; 
  ostr << std::endl;
  return ostr;
}

//2
std::ifstream& operator>>(std::ifstream &istr, pgsEvent &rhs) {
  
  int code;
  istr >> code;
  istr >> rhs.nEvent;
  istr >> rhs.triggWord;
  
  while( (istr.peek() == 10) || (istr.peek() == 32 ) )
    istr.ignore(1);
  
  while( istr.peek() != 48 ) {
    pgsObject * obj = new pgsObject();
    istr >> (*obj);
    rhs.data.push_back( obj );
    while( (istr.peek() == 10) || (istr.peek() == 32 ) )
      istr.ignore(1);
    if( istr.eof() ) break;
    
  }
  
  return istr;
}

std::ostream& operator<<(std::ostream &ostr, pgsEvent &rhs) {
  
  ostr << rhs.nEvent << '\t'; 
  ostr << rhs.triggWord << '\n'; 
  
  std::vector<pgsObject*>::iterator itr;
  
  for( itr = rhs.data.begin(); itr != rhs.data.end(); ++itr) 
    std::cout << *(*itr);
  
  return ostr;

}

LHCOParser::LHCOParser(const char *infile ) {

  m_debug = false;
  
  m_in = new std::ifstream();

  m_in->open(infile);
  
  if (!m_in->good()) std::cout << "Data> could not open input file" << std::endl;
  
  char comment[256];
  
  //
  //Skip all initial comments and header
  //
  
  while( 1 ) {
    
    if ( (*m_in).peek() == 35 ) {
      (*m_in).getline( comment, 256 );
      if ( m_debug ) std::cout << "found a comment" << std::endl;
    } else if ( (*m_in).peek() == 32 ) {
      (*m_in).ignore(1);
    } else if ( (*m_in).peek() == 48 ) {
      if ( m_debug ) std::cout << "Ready to extract events"  << std::endl;
      break;
    } else { }
    
  }
  
  m_nEvt = 0;
  
  if ( m_debug ) std::cout << "LHCOParser> ready" << std::endl;
  
}

LHCOParser::~LHCOParser() 
{
  
  m_in->close();
  delete m_in;

  //if ( m_event ) delete m_event;
  
}

int LHCOParser::Next( ) 
{
  
  
  if( !m_in->good() ) return -1;
  if( m_in->eof() ) return -1;
  
  if( m_in->peek() ==  10 ) { 
    m_in->ignore(1);
    if( m_in->peek() == EOF ) {
      std::cout << "EOF"  << std::endl;
      return -1;
    }
    
  }
    
  m_event = new pgsEvent();
  
  (*m_in) >> (*m_event);
  
  ++m_nEvt;
  
  if (m_debug) 
    if ( m_nEvt < 3 ) std::cout << (*m_event);
  
  if( m_in->eof() ) return -1;
  
  return m_event->data.size();
  
}


