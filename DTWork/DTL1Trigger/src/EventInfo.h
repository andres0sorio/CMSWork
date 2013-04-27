// $Id: $
#ifndef EVENTINFO_EVENTINFO_H 
#define EVENTINFO_EVENTINFO_H 1

// Include files

/** @class EventInfo EventInfo.h EventInfo/EventInfo.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2011-07-19
 */

class EventHeader {
 public:
  
  EventHeader();
  virtual ~EventHeader();
    
 private:
    
  int m_EvtNum;
  int m_Run;
  int m_Lumi;
  
};

class EventInfo {
 public:
  
  EventInfo();
  virtual ~EventInfo();
  
 private:
  
  EventHeader    m_EvtHdr;
  int            m_Tracks;
  std::vector<TrackInfo*>;
  
  ClassDef(EventInfo,1)
    
};

class DTHits : public TObject {
 public:
  
  DTHits();
  virtual ~DTHits();
  
 private:
  
  float m_xi;
  float m_yi;
  float m_lr;
  float m_time;
  int   m_trk;
  int   m_wh;
  int   m_st;
  int   m_sc;
  int   m_lyr;
  int   m_sly;
  
  ClassDef(DTHits,1)

};

class TrackInfo : public TObject{
 public:

  TrackInfo();
  virtual ~TrackInfo();

 private:
  
  float m_chi2;
  int   m_charge;
  TClonesArray * m_DThits;
  
  ClassDef(TrackInfo,1)
    
};

#endif // EVENTINFO_EVENTINFO_H
