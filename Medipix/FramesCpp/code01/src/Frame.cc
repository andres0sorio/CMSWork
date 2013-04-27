// $Id: $
// Include files 
// local
#include "Frame.h"
#include <sstream>

//Plots the matrix of this frame
void PlotMatrix( Data * data, TH2F * hh)
{

  for(int i=0; i < 256; ++i)
  {
    for(int j=0; j < 256; ++j)
    {
      int counts = data->matrix[j][i];
      hh->SetBinContent(i+1,j+1, float(counts));
    }
    
  }
  
}

//-----------------------------------------------------------------------------
// Implementation file for class : Frame
//
// 2012-03: Andres Osorio/Iván Caicedo
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
Frame::Frame( const char * datos, const char * dsc, int fId ) {

  m_data = new Data( datos );
  m_dscreader = new DSCReader( dsc );
  m_frameId = fId;
  m_data->Read();
  m_dscreader->Read();
  m_data->SetTimestamp( 0.0 );

  //Extracts the name of the frame from the source files
  std::string fullname(datos);
  int pos = fullname.rfind("/");  
  m_fname = fullname.substr(pos+1,fullname.size());

}

//=============================================================================
// Destructor
//=============================================================================
Frame::~Frame() {

  delete m_data;
  delete m_dscreader;
  delete m_algo;

} 

//=============================================================================

//Compares the start time values from two different frames to make sure that they are coincident
bool Frame::Compare( const Frame & iFrame ) 
{
  
  double time1 = m_dscreader->GetTimeNs( );
  double time2 = iFrame.m_dscreader->GetTimeNs( );
  double diff = fabs ( time1-time2 );
  
  std::cout << time1 << " " << time2 << " " << diff << std::endl;
    
  if ( diff < 0.80E8 ) return true;
  std::cout << "Frame::Compare> No hay coincidencia entre los Frames" << std::endl;      
  return false;
  
}



//Looks for clusters in this frame
void Frame::Clusterize( ) 
{
  
  m_algo = new SimpleClusterAlgo( m_data );
  m_algo->Run();

  //Displays data and clusters using ROOT

  m_clusters = new TH2F("Clusters","Clusters Display",257,0,257,257,0,257);
  m_readings = new TH2F("Data","Hit Display",257,0,257,257,0,257);
  
  m_clusters->SetStats(0);
  m_readings->SetStats(0);
  m_clusters->SetMarkerStyle(24);
  m_clusters->SetMarkerSize(1.2);
  
  m_algo->PlotClusters( m_clusters );
    
  PlotMatrix( m_data, m_readings );

  TStyle * sty =  new TStyle();
  sty->SetPalette(1);
  sty->cd();
  
  TCanvas * c2 = new TCanvas("c2","Plots",100,50,600,400);
  c2->SetFillColor(10);
  c2->cd();
  
  m_readings->Draw("COLZ");
  m_clusters->Draw("SAME");
  
  std::stringstream filename;
  filename << "results_" << m_frameId << ".eps";
  
  c2->Print( filename.str().c_str() );

  delete m_clusters;
  delete m_readings;
  delete c2;

  m_algo->Filter();
  m_algo->Characterize();
  
}

void Frame::FindCoincidences( const Frame & f2 ) {
  
  //1. Find coincidence in *this frame
  std::cout << "this is frame " << (*this).m_frameId << std::endl;

  m_otherFrame = & f2;

  (*this).m_algo->FindCoincidences();
  
  //2. Find coincidence in second frame

  std::cout << "this is frame " << f2.m_frameId << std::endl;
  
  f2.m_algo->FindCoincidences();

  //3. Find coincidence between frames

  std::vector<Cluster*>::iterator itrClus1;
  std::vector<Cluster*>::iterator itrClus2;

  std::cout << "Now between frames " << std::endl;
  
  for( itrClus1 = (*this).m_algo->m_clusters.begin(); itrClus1 != (*this).m_algo->m_clusters.end();
       ++itrClus1 )
    {
    
      for( itrClus2 = f2.m_algo->m_clusters.begin(); itrClus2 != f2.m_algo->m_clusters.end();
	 ++itrClus2 )
      {
	
	if ( (*itrClus1) ==  (*itrClus2 ) ) continue;
	
	bool result =  compareCluster( (*itrClus1), (*itrClus2) );
	
	if( result ) { 
	  
	  std::cout << "Ahaha " << (*itrClus1)->Avg() << " " << (*itrClus2)->Avg() << std::endl;
	  m_coincidences.push_back( (*itrClus1) );
	  m_coincidences.push_back( (*itrClus2) );
	  
	} else std::cout << "No coincidence " << (*itrClus1)->Avg() << " " << (*itrClus2)->Avg() << std::endl;
	
      }
    }

}



//Prints the name of the Frame and the coincidences on a file
void Frame::ExportCoincidences( std::ofstream * m_out ) {
  //Prints the name of the frame
  (*m_out) << m_fname << '\n';

  std::vector<Cluster*>::iterator itrClus;
   
  int m_Id1 = (*this).m_frameId;
  int m_Id2 = (*m_otherFrame).m_frameId;
    
  //This Frame
  for( itrClus = (*this).m_algo->m_coincidences.begin(); itrClus != (*this).m_algo->m_coincidences.end();
       ++itrClus ) {
    
    (*m_out) << m_Id1 << " " << m_Id1 << '\t'
	     << (*itrClus)->X() << " "
	     << (*itrClus)->Y() << " "
      	     << (*itrClus)->Avg() << '\t';

    ++itrClus;
    
    (*m_out) << (*itrClus)->X() << " "
	     << (*itrClus)->Y() << " "
      	     << (*itrClus)->Avg() << '\n';
    
  }

  std::vector<Cluster*>::const_iterator itrClus2;

  //2nd Frame
  for( itrClus2 = (*m_otherFrame).m_algo->m_coincidences.begin(); itrClus2 != (*m_otherFrame).m_algo->m_coincidences.end();
       ++itrClus2 ) {
    
    (*m_out) << m_Id2 << " " << m_Id2 << '\t'
	     << (*itrClus2)->X() << " "
	     << (*itrClus2)->Y() << " "
      	     << (*itrClus2)->Avg() << '\t';
    
    ++itrClus2;
    
    (*m_out) << (*itrClus2)->X() << " "
	     << (*itrClus2)->Y() << " "
      	     << (*itrClus2)->Avg() << '\n';
    
  }

  //Between frames
  
  for( itrClus = m_coincidences.begin(); itrClus != m_coincidences.end();
       ++itrClus ) {
    
    (*m_out) << m_Id1 << " " << m_Id2 << '\t'
	     << (*itrClus)->X() << " "
	     << (*itrClus)->Y() << " "
      	     << (*itrClus)->Avg() << '\t';
    
    ++itrClus;
    
    (*m_out) << (*itrClus)->X() << " "
	     << (*itrClus)->Y() << " "
      	     << (*itrClus)->Avg() << '\n';
    
  } 


}
