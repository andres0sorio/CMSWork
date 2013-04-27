// $Id: HistoOutput.h,v 1.1 2009/02/16 09:11:30 aosorio Exp $
#ifndef HISTOOUTPUT_H 
#define HISTOOUTPUT_H 1

// Include files
#include <string>
#include <iostream>

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

//From ROOT:
#include <TH1D.h>
#include <TH2D.h>

/** @class HistoOutput HistoOutput.h
 *  
 *
 *  @author Andres Felipe Osorio Oliveros
 *  @date   2009-02-05
 */
class HistoOutput {
public: 
  /// Standard constructor
  HistoOutput( ) {};

  HistoOutput( edm::Service<TFileService> &, int , int );

  virtual ~HistoOutput( ); ///< Destructor
  
  TH1D * hbylayer[12];
  TH1D * hndigi[5];
  
  
    
protected:
  
private:
  
  std::string m_option;
  
};
#endif // HISTOOUTPUT_H
