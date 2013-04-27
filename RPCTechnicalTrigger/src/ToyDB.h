// $Id: $
#ifndef TOYDB_H 
#define TOYDB_H 1

// Include files
#include "L1Trigger/RPCTechnicalTrigger/src/Dimension.h"
#include <vector>

/** @class ToyDB ToyDB.h
 *  
 *  ToyDB class: encapsulates data fields
 *
 *
 *  @author Andres Osorio
 *  @date   2008-10-26
 */

//...RUN fact table
class RUN : public Dimension
{
public:
  
  RUN() {};
  RUN( const char * _name ) : Dimension( _name ) {}; 
  RUN( const char * _name , long int _key ): 
    Dimension (_name,_key) {};
  
  ~RUN() {
    m_fkeys.clear(); 
  };
  
  void AddFK( long int & _fk) {
    m_fkeys.push_back( _fk );
  };
  
  // io functions
  friend std::istream& operator>>(std::istream &istr, RUN &);
  friend std::ostream& operator<<(std::ostream &ostr, RUN &);
  friend std::ostringstream& operator<<(std::ostringstream &ostr, RUN &);
  
  
  void SetQuery() 
  {
    (*m_oss) << "INSERT INTO " << (this->m_name) << " VALUES ";
    (*m_oss) << (*this);
  };
  
  void SetSelectQuery() 
  {
    (*m_oss) << "SELECT * from " << (this->m_name);
  };
  
  void AddValue( int _val) { m_int_values.push_back(_val); };
  
  void FillTable() { 
    std::vector<int>::iterator itr = m_int_values.begin();
    m_pkey = (*itr); //first item is the PK
    ++itr;
    while( itr!=m_int_values.end()) {
      m_fkeys.push_back( (*itr) );
      ++itr;
    }
    
  };
  
  void PrintInfo() { std::cout << (*this); };
  
  void ClearTable() 
  {
    m_fkeys.clear();
    m_int_values.clear();
  };
    
  std::vector<long int> m_fkeys;
  std::vector<int> m_int_values;
  
};

class RBCBoard : public Dimension
{
public:
  
  RBCBoard() : Dimension() {};
  RBCBoard(const char * _name) : Dimension( _name) {};
  RBCBoard(const char * _name, long int _key ) : 
    Dimension (_name,_key) { };
  
  ~RBCBoard() {
  };
  
  // io functions
  friend std::istream& operator>>(std::istream &istr, RBCBoard &);
  friend std::ostream& operator<<(std::ostream &ostr, RBCBoard &);
  friend std::ostringstream& operator<<(std::ostringstream &ostr, RBCBoard &);
  
  void SetQuery() 
  {
    (*m_oss) << "INSERT INTO " << (this->m_name) << " VALUES ";
    (*m_oss) << (*this);
  };
  
  void SetSelectQuery() 
  {
    (*m_oss) << "SELECT * from " << (this->m_name) << ";";
  };
  
  //... fill methods

  void AddValue( int _val) { m_int_values.push_back(_val); };
  
  void FillTable() {
    m_pkey = m_int_values[0]; //first item is the PK
    m_fwversion = m_int_values[1];
    m_wheel = m_int_values[2];
    m_sectorA = m_int_values[3];
    m_sectorB = m_int_values[4];
    m_maskedstrips = m_int_values[5];
  };
  
  void PrintInfo() { std::cout << (*this); };
  
  void ClearTable() 
  {
    m_int_values.clear();
  };
  
  int m_fwversion;
  int m_wheel;
  int m_sectorA;
  int m_sectorB;
  int m_maskedstrips;
  
  std::vector<int> m_int_values;

};

class ToyDB {
public: 
  /// Standard constructor
  ToyDB( ); 
  
  virtual ~ToyDB( ); ///< Destructor
  
  friend std::istream& operator>>(std::istream &istr, ToyDB &);
  friend std::ostream& operator<<(std::ostream &ostr, ToyDB &);
  
  void reset();
  
  void SetTables();
  
  std::ostringstream * GetQuery( int );
  std::ostringstream * GetSelectQuery( int );
  
  int m_ntables;
  
  std::vector<std::string> m_tables;

  Dimension * firstTable() 
  {
    m_itr = m_Tables.begin();
    return (*m_itr);
  };
  
  Dimension * nextTable()
  {
    ++m_itr;
    if ( m_itr==m_Tables.end() ) return NULL;
    return (*m_itr); 
  };
  
  void rewind() { m_itr = m_Tables.begin(); };
  
  void PrintInfo();
  

protected:
  
private:
  
  std::vector<Dimension*> m_Tables;
  
  std::vector<Dimension*>::const_iterator m_itr;
  
  //...
  
};
#endif // TOYDB_H
