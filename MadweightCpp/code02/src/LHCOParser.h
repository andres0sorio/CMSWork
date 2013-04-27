#ifndef LHCOPARSER_H
#define LHCOPARSER_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <map>



struct pgsObject {
  
  // io functions
  friend std::ifstream& operator>>(std::ifstream &istr, pgsObject &rhs);
  friend std::ofstream& operator<<(std::ofstream &ostr, pgsObject &rhs);

  friend std::ostream& operator<<(std::ostream &ostr, pgsObject &rhs);
  
  // generated particle record  
  int idpart;
  int type;
  double eta;
  double phi;
  double pt;
  double jmas;
  double ntrk;
  double btag;
  double hadem;
  double dum1;
  double dum2;

  pgsObject() { };
  ~pgsObject() { };
  
};

struct pgsEvent {
  
  // io functions
  
  friend std::ifstream& operator>>(std::ifstream &istr, pgsEvent &rhs);
  
  friend std::ofstream& operator<<(std::ofstream &ostr, pgsEvent &rhs);
  friend std::ostream& operator<<(std::ostream &ostr, pgsEvent &rhs);
  
  // x variable
  
  int nEvent;
  int triggWord;
  
  std::vector<pgsObject*> data;
  
  pgsEvent() { }
  
  ~pgsEvent( ) {
    
    std::vector<pgsObject*>::iterator itr_pgs = data.begin();
    while(itr_pgs != data.end()) {
      delete *itr_pgs;
      ++itr_pgs;
    }
    data.clear();
  }
  
};


class LHCOParser {
public:
  
  LHCOParser( ) {};
  LHCOParser( const char * );
  
  virtual ~LHCOParser( );
  
  int Next();
  pgsEvent * m_event;
  
private:
  
  int m_nEvt;

  std::ifstream * m_in;

  
    
};

  
#endif
