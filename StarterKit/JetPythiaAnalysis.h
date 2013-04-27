// $Id: $
#ifndef STARTERKIT_JETPYTHIAANALYSIS_H 
#define STARTERKIT_JETPYTHIAANALYSIS_H 1

// Include files
#include "PythiaAnalysis.h"
#include "fastjet/ClusterSequence.hh"

/** @class JetPythiaAnalysis JetPythiaAnalysis.h StarterKit/JetPythiaAnalysis.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2011-03-31
 */
class JetPythiaAnalysis : public PythiaAnalysis{
public: 
  /// Standard constructor
  JetPythiaAnalysis(const char * fname, const char * opt, int type);

  virtual ~JetPythiaAnalysis( ); ///< Destructor

  virtual void Loop();
  
protected:

private:

};
#endif // STARTERKIT_JETPYTHIAANALYSIS_H
