// $Id: $
// Include files 



// local
#include "L1Trigger/RPCTechnicalTrigger/src/ToyDB.h"
#include <iostream>
//-----------------------------------------------------------------------------
// Implementation file for class : ToyDB
//
// 2008-10-26 : Andres Osorio
//-----------------------------------------------------------------------------

std::istream& operator>>(std::istream &istr , RUN & rhs) 
{
  
  istr >> rhs.m_pkey;
  long int _fk;
  istr >> _fk;
  rhs.AddFK ( _fk );
  
  return istr;
  
}

std::ostringstream& operator<<(std::ostringstream& ostr , RUN & rhs) 
{
  
  ostr << "('" << rhs.m_pkey << "','";
  std::vector<long int>::iterator itr;
  itr = rhs.m_fkeys.begin();
  while ( itr != rhs.m_fkeys.end() ) {
    ostr << (*itr);
    ++itr;
    if ( itr != rhs.m_fkeys.end() ) ostr << "','";
    else ostr << "')";
  }
  
  return ostr;
  
}

std::ostream& operator<<(std::ostream& ostr , RUN & rhs) 
{
  
  ostr << "PK: " << rhs.m_pkey << '\t';
  std::vector<long int>::iterator itr;
  itr = rhs.m_fkeys.begin();
  while ( itr != rhs.m_fkeys.end() ) {
    ostr << (*itr) << '\t';
    ++itr;
  }
  
  ostr << '\n';
  
  return ostr;
  
}

std::istream& operator>>(std::istream &istr , RBCBoard & rhs) 
{
  
  istr >> rhs.m_pkey;
  istr >> rhs.m_fwversion
       >> rhs.m_wheel
       >> rhs.m_sectorA
       >> rhs.m_sectorB
       >> rhs.m_maskedstrips;
  
  return istr;
  
}

std::ostringstream& operator<<(std::ostringstream &ostr , RBCBoard & rhs) 
{
  
  ostr << "('"  << rhs.m_pkey
       << "','" << rhs.m_fwversion
       << "','" << rhs.m_wheel
       << "','" << rhs.m_sectorA
       << "','" << rhs.m_sectorB
       << "','" << rhs.m_maskedstrips << "')";
  
  return ostr;
  
}

std::ostream& operator<<(std::ostream &ostr , RBCBoard & rhs) 
{
  
  ostr << "PK: "  << rhs.m_pkey
       << '\t' << rhs.m_fwversion
       << '\t' << rhs.m_wheel
       << '\t' << rhs.m_sectorA
       << '\t' << rhs.m_sectorB
       << '\t' << rhs.m_maskedstrips << '\n';
  
  return ostr;
  
}


std::istream& operator>>(std::istream &istr , ToyDB & rhs) 
{
  
  RUN * m_run = new RUN("RUN");
  RBCBoard * m_rbcboard = new RBCBoard("RBCBoard");
      
  istr >> (*m_run);
  istr >> (*m_rbcboard);
  
  rhs.m_Tables.push_back( dynamic_cast<Dimension*>(m_run) );
  rhs.m_Tables.push_back( dynamic_cast<Dimension*>(m_rbcboard) );
  
  return istr;
  
}

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
ToyDB::ToyDB(  ) {

  m_tables.push_back(std::string("RUN"));
  m_tables.push_back(std::string("RBCBoard"));
  m_ntables = m_tables.size();
  
}
//=============================================================================
// Destructor
//=============================================================================
ToyDB::~ToyDB() {} 

//=============================================================================
void ToyDB::reset() 
{

  std::vector<Dimension*>::iterator itr;
  for(itr=m_Tables.begin(); itr!=m_Tables.end();++itr)
    if ( (*itr) ) delete (*itr);
  
  m_Tables.clear();
  
}

void ToyDB::SetTables() 
{
  
  RUN * m_run = new RUN("RUN");
  RBCBoard * m_rbcboard = new RBCBoard("RBCBoard");
  
  m_Tables.push_back( dynamic_cast<Dimension*>(m_run) );
  m_Tables.push_back( dynamic_cast<Dimension*>(m_rbcboard) );
  
}

std::ostringstream * ToyDB::GetQuery( int _idx ) 
{
  
  m_Tables[_idx]->SetQuery();
  return m_Tables[_idx]->GetQuery();
  
}

std::ostringstream * ToyDB::GetSelectQuery( int _idx ) 
{
  
  m_Tables[_idx]->SetSelectQuery();
  return m_Tables[_idx]->GetQuery();
  
}

void ToyDB::PrintInfo() 
{
  
  Dimension * _table = firstTable();
  
  while ( nextTable() )
  {
    _table->PrintInfo();
  }
  
  rewind();
  
}
