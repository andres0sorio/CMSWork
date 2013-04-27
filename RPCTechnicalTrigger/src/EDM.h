// $Id: $
#ifndef EDM_H 
#define EDM_H 1

// Include files

/** @namespace EDM EDM.h
 *  
 *  This is a temporal domain with classes
 *  before we jump to cmssw  ---- hopefuly soon
 *
 *  @author Andres Osorio
 *  @date   2008-10-16
 */
namespace edm {
  class EDAnalyzer {
  public:
    EDAnalyzer() { };
    ~EDAnalyzer() { };
    double a;
  };
  
  class Event {
  public:
    Event() {};
    ~Event() {};
    int a;
  };
  
  class EventSetup {
  public:
    EventSetup() {};
    ~EventSetup() {};
    int b;
  };
  
  class ParameterSet 
  {
  public:
    ParameterSet() {};
    ~ParameterSet() {};
    int c;
  };

}

#endif // EDM_H
