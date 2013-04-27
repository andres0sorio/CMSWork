// $Id: $
#ifndef RPCTECHNICALTRIGGER_H 
#define RPCTECHNICALTRIGGER_H 1

// system include files
#include <memory>

// Include files From CMSSW

#include "L1Trigger/RPCTechnicalTrigger/src/EDM.h"

//Local to project
#include "L1Trigger/RPCTechnicalTrigger/src/RPCTTU.h"
#include "L1Trigger/RPCTechnicalTrigger/src/RPCProcessTestSignal.h"


/** @class RPCTechnicalTrigger RPCTechnicalTrigger.h
 *  
 *
 *  @author Andres Osorio
 *
 *  email: aosorio@uniandes.edu.co
 *
 *  @date   2008-10-15
 */

class RPCTechnicalTrigger : public edm::EDAnalyzer {
public: 
  /// Standard constructor
  explicit RPCTechnicalTrigger(const edm::ParameterSet&);
  
  ~RPCTechnicalTrigger( ); ///< Destructor
  
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  
protected:
  
private:
  
  virtual void beginJob(const edm::EventSetup&);

  virtual void endJob() ;

  bool initialise();

  void printinfo();

  RPCTTU * m_ttu[3];

  //edm::ESHandle<RPCGeometry> m_rpcGeometry;

  int m_debugmode;
  std::string m_rbclogictype;
  std::string m_ttulogictype;

  std::map<int,RBCInput*> m_data;

  RPCProcessTestSignal * m_signal;
      
};
#endif // RPCTECHNICALTRIGGER_H
