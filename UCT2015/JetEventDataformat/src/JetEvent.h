// Include files

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <cmath>
#include <vector>

/** @class JetEvent
 *  
 *
 *  @author Andres Osorio
 *  @date   2012-12-19
 */

class Region {
  
 public:
  
  float Et;
  float PhysicalEt;
  int   EtaPos;
  int   PhiPos;
    
  Region() { 
    Et = 0.0;
    PhysicalEt = 0.0;
    EtaPos = 0;
    PhiPos = 0;
    
  };
  
  void Initialize( float et, int etapos, int phipos ) {
    Et = et;
    EtaPos = etapos;
    PhiPos = phipos;
    PhysicalEt = 0.0;
  };

  void Initialize( float et, float pet, int etapos, int phipos ) {
    Et = et;
    PhysicalEt = pet;
    EtaPos = etapos;
    PhiPos = phipos;
  };

  virtual ~Region() { };
  
};

class SimpleJet 
{
 public:
  
  std::vector<Region> v_Regions; //4x4 regions that surround this Jet (neighbors)
  
  int   n_Reg; // 8 - 5
  Region m_Seed; //main seed region (et,eta,phi)
  
  SimpleJet() {
    n_Reg = 0;
  };
  
  virtual ~SimpleJet() { 
    n_Reg = -1;
    v_Regions.clear();
  };
  
  void AddRegion( float et , int etapos, int phipos ) {
    Region neighbor;
    neighbor.Initialize( et, etapos, phipos );
    v_Regions.push_back( neighbor );
  }

  //
  bool operator>( const SimpleJet & rhs ) const;
  bool operator<( const SimpleJet & rhs ) const;
  
  float jetEt() const { 
    return m_Seed.Et; 
  };
  
};

inline bool SimpleJet::operator>( const SimpleJet& rhs ) const { 
  return jetEt() > rhs.jetEt(); 
}

inline bool SimpleJet::operator<( const SimpleJet& rhs ) const { 
  return jetEt() < rhs.jetEt(); 
}

typedef std::vector<Region> RegionCollection;
typedef std::vector<SimpleJet> JetEventCollection;

