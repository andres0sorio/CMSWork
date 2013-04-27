// $Id: $
// Include files 



// local
#include "L1Trigger/RPCTechnicalTrigger/src/AccessConfigMySQL.h"

//-----------------------------------------------------------------------------
// Implementation file for class : AccessConfigMySQL
//
// 2008-10-25 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
AccessConfigMySQL::AccessConfigMySQL(  )
{
  m_db = TSQLServer::Connect("mysql://localhost/rbcttdb", "cmsexp", "muons");
}

AccessConfigMySQL::AccessConfigMySQL( const char * _infile )
{
  
  m_db = TSQLServer::Connect("mysql://localhost/rbcttdb", "cmsexp", "muons");
  
  m_in = new std::ifstream();
  m_in->open( _infile );
  
  if(!m_in) {
    std::cout << "AccessConfigMySQL> Could not open input file.\n";
    exit(1);
  } 
  
  m_data     = new ToyDB();
  m_nrecords = 0;
  m_mode     = 0; // default mode
  
}

//=============================================================================
// Destructor
//=============================================================================
AccessConfigMySQL::~AccessConfigMySQL() {
  
  if( m_db ) delete m_db;
  m_in->close();
  delete m_in;
  
} 

//=============================================================================
bool AccessConfigMySQL::write()
{
  
  //.
  
  if ( m_mode == 0 ) {
    
    for(int i=0; i < m_data->m_ntables; ++i) {
      char _delfrom[40];
      sprintf(_delfrom,"DELETE FROM %s", m_data->m_tables[i].c_str() );
      m_sqlres = m_db->Query(_delfrom);
      delete m_sqlres;
    }
    
  }
  
  //..
  
  while( !m_in->fail() ) {
    
    if( m_nrecords > 5 ) break;
    
    (*m_in) >> (*m_data);
    
    if ( m_in->eof() ) {
      m_data->reset();
      break;
    }
    
    //...
    
    for(int i=0; i < m_data->m_ntables; ++i) {
      
      m_oss =  m_data->GetQuery(i);
      std::cout << (*m_oss).str() << ";" << std::endl;
      m_sqlres = m_db->Query( (*m_oss).str().c_str() );
      delete m_sqlres;
      
    }
    
    ++m_nrecords;
    m_data->reset();
    
  }
  
  std::cout << "AccessConfigMySQL> total added records: " 
            << m_nrecords << '\n';

  return 1;
  
}


bool AccessConfigMySQL::read()
{
  
  printf("Server info: %s\n", m_db->ServerInfo());
  
  std::cout << "List all tables in database\n";
  
  m_sqlres = m_db->GetTables("rbcttdb");
  
  while ((m_row = m_sqlres->Next())) {
    printf("%s\n", m_row->GetField(0));
    delete m_row;
  }
  delete m_sqlres;
  
  TList* lst = m_db->GetTablesList();
  TIter next(lst);
  TObject* obj = next();
  
  while ( obj ) {
    std::cout << "Table: " << obj->GetName() << std::endl;
    obj = next();
  }
  
  delete lst;
  
  m_data->SetTables(); //initialise all Tables Objects
  
  Dimension * _table = m_data->firstTable();

  for(int k=0; k < m_data->m_ntables; ++k) {
    
    m_oss    = m_data->GetSelectQuery(k);
    m_sqlres = m_db->Query( (*m_oss).str().c_str() );
    
    int _val(0);
    int _nrows   = m_sqlres->GetRowCount();
    int _nfields = m_sqlres->GetFieldCount();
    
    for (int i=0; i < _nrows; i++) {
      
      m_row = m_sqlres->Next();
      
      for (int j = 0; j < _nfields; j++) {
        
        std::istringstream iss( m_row->GetField(j) );
        iss >> _val;
        _table->AddValue( _val );
        
      }
      
      _table->FillTable();
      
      //. do something here with the Table contents
      
      _table->PrintInfo();
      
      
      //...
      
      _table->ClearTable();
      
    }
    
    _table = m_data->nextTable();
    
    m_data->rewind();
        
    m_nrecords = _nrows;
    delete m_sqlres;
    
  
  }
  
  std::cout << "AccessConfigMySQL> total read records: " 
            << m_nrecords << '\n';
  
  return 1;
  
}

