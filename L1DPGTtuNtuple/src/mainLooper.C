// $Id: main.C,v 1.2 2007/10/16 12:24:54 aosorio Exp $
// Include files 


#include "CommonIncludes.h"
#include "LoopSelector.h"
#include "L1Tree.h"
#include "L1TTUTree.h"
#include <map>

int main(int iargv, const char **argv) {

  
  const char * infile = argv[1];
  std::ifstream * m_inDataA = new std::ifstream( infile , ifstream::in );

  const char * selTree = argv[2];
    
  bool m_noinputfile = false;
  
  if ( m_inDataA->bad() ) m_noinputfile |= true;
  else m_noinputfile = false;
  if ( m_noinputfile ) exit(1);
  
  //.......................................................................
  std::map<std::string, std::string> m_classes;
  
  m_classes["L1Tree"]   = std::string("l1NtupleProducer/L1Tree");
  m_classes["MuonReco"] = std::string("l1MuonRecoTreeProducer/MuonRecoTree");
  m_classes["L1Extra"]  = std::string("l1ExtraTreeProducer/L1ExtraTree");
  m_classes["L1TTU"]    = std::string("l1gtAnalyzer/L1TTUTree");
  
  TChain * m_chain = new TChain( m_classes[std::string(selTree)].c_str() );

  int nfiles = 0;
  
  while (1) {
    
    std::string dataA;
    
    if ( m_inDataA->fail()) break;
    (*m_inDataA) >> dataA;
    if ( m_inDataA->eof() ) break;
    
    m_chain->Add(  dataA.c_str() );
    
    ++nfiles;
        
  }
  
  //.......................................................................
  std::cout << "Total file added: " << nfiles << std::endl;

  //LoopSelector< L1Tree > * h1 = new LoopSelector<L1Tree>( m_chain , "someopt");

  LoopSelector< L1TTUTree > * h1 = new LoopSelector<L1TTUTree>( m_chain , "someopt");

  h1->Initialize();
  h1->Loop(-1);
  delete h1;
  
  return 1;
    
}
