/*
 *  Author: Michal Pietrusinski, William Whitacher & Giovanni Polese
 *  Version: $Id: XdaqRpcConnectivityTest.cpp,v 1.1 2008/11/21 11:39:54 tb Exp $ 
 *  
 */

#include "XdaqRpcConnectivityTest.h"

#include "xdaq/ApplicationGroup.h"

#include "xdata/soap/NamespaceURI.h"
#include "xdata/Serializable.h"
#include "xdata/exception/Exception.h"
#include "xdata/XStr.h"
#include "xdata/Float.h"
#include "xdata/Bag.h"
#include "xdata/Boolean.h"
#include "xdata/Integer.h"
#include "xdata/String.h"


#include "xoap/domutils.h"

#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

#include "rpct/devices/System.h"
#include "rpct/devices/XmlSystemBuilder.h"
#include "rpct/xdaqutils/FebAccessInfo.h"

#include <log4cplus/configurator.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;
using namespace rpct;
using namespace rpct::xdaqutils;
using namespace rpct::xdaqdiagaccess;
using namespace cgicc;

XDAQ_INSTANTIATOR_IMPL(XdaqRpcConnectivityTest);

const char* XdaqRpcConnectivityTest::RPCT_RPC_CONFIG_NS = "urn:rpct-rpc-connectivityTest:1.0";
const char* XdaqRpcConnectivityTest::RPCT_RPC_CONFIG_PREFIX = "rrc";

XdaqRpcConnectivityTest::XdaqRpcConnectivityTest(xdaq::ApplicationStub * s) : 
  xdaq::Application(s),
  dbServiceClient(this), lboxAccessClient(this), diagAccessClient(this), mainTitle("RPC Connectivity test"), subTitle("configure"), selectedChambers("")
{

  LOG4CPLUS_INFO(getApplicationLogger(),"Starting the application XdaqRpcConnectivityTest.");

  xgi::bind(this,&XdaqRpcConnectivityTest::Default,          "Default");
  xgi::bind(this,&XdaqRpcConnectivityTest::SelectChambers,   "SelectChambers");
  xgi::bind(this,&XdaqRpcConnectivityTest::SetFebValues,     "SetFebValues");
  xgi::bind(this,&XdaqRpcConnectivityTest::ReadFebValues,    "ReadFebValues");
  //  xgi::bind(this,&XdaqRpcConnectivityTest::ReadNoise,        "ReadNoise");
  //  xgi::bind(this,&XdaqRpcConnectivityTest::ConnectivityTest, "ConnectivityTest");
  //  xgi::bind(this,&XdaqRpcConnectivityTest::ThresholdScan,    "ThresholdScan");
  xgi::bind(this,&XdaqRpcConnectivityTest::Reset,            "Reset");
}

XdaqRpcConnectivityTest::~XdaqRpcConnectivityTest() {

  LOG4CPLUS_INFO(getApplicationLogger(),"Stopping the application XdaqRpcConnectivityTest.");

}

/**************************************************
** General layout                                **
**************************************************/
void XdaqRpcConnectivityTest::PageHeader(xgi::Input * in, xgi::Output * out, string mainTitle_, string subTitle_) throw (xgi::exception::Exception)
{

  LOG4CPLUS_INFO(getApplicationLogger(),"PageHeader.");

  *out << cgicc::HTMLDoctype(cgicc::HTMLDoctype::eStrict) << std::endl;
  *out << cgicc::html().set("lang","en").set("dir","ltr") << std::endl;
  *out << cgicc::head() << std::endl;
  *out << cgicc::title(mainTitle_) << std::endl;
  *out << cgicc::style() << cgicc::comment() << std::endl;
  *out << "body{font-size:3;font-family:Arial, Times New Roman, Times, Serif;}" << std::endl;
  *out << "h1{text-align:center;font-size:4;color:#003366;font-weight:bold;}" << std::endl;
  *out << "table{border:0;border-collapse:collapse;border-spacing:0;}" << std::endl;
  *out << "td{padding:5px;}" << std::endl;
  *out << "table.wborder{border:1px solid #003366;border-collapse:collapse;border-spacing:0;}" << std::endl;
  *out << "table.wborder td, table.wborder th{border: 1px solid #003366;}" << std::endl;
  *out << "table.wborder td table td, table.wborder td table th{border: 0;}" << std::endl;
  *out << "td.ok{background-color:white;font-weight:normal;}" << std::endl;
  *out << "td.problem{background-color:red;font-weight:bold;}" << std::endl;
  *out << cgicc::comment() << cgicc::style() << std::endl;
  *out << cgicc::head() << std::endl;
  *out << cgicc::body() << std::endl;
  
  if (subTitle_ != "")
    mainTitle_ += ": " + subTitle_;
  xgi::Utils::getPageHeader(
			    out, 
			    mainTitle_,
			    getApplicationDescriptor()->getContextDescriptor()->getURL(),
			    getApplicationDescriptor()->getURN(),
			        "/hyperdaq/images/Application.gif"
			    );
}

void XdaqRpcConnectivityTest::PageFooter(xgi::Input * in, xgi::Output * out) throw (xgi::exception::Exception)
{

  LOG4CPLUS_INFO(getApplicationLogger(),"PageFooter.");

  xgi::Utils::getPageFooter(*out);
  *out << body() << std::endl;
  *out << html() << std::endl;
}


/**************************************************
** Default                                       **
**************************************************/
void XdaqRpcConnectivityTest::Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception)
{

  LOG4CPLUS_INFO(getApplicationLogger(),"Default.");

  subTitle = "configuration";
  
  this->PageHeader(in, out, mainTitle, subTitle);
  this->SelectChambersGUI(in, out);
  this->SetFebValuesGUI(in, out);
  this->ReadFebValuesGUI(in, out);
  //  this->ReadNoiseGUI(in, out);
  //  this->connectivityTestGUI(in, out);
  //  this->ThresholdScanGUI(in, out);
  this->PageFooter(in, out);
}

/**************************************************
** SelectChambers                                **
**************************************************/
void XdaqRpcConnectivityTest::SelectChambers(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception)
{

  LOG4CPLUS_INFO(getApplicationLogger(),"SelectChambers.");

  bool barrelOrEndcap;
  int wheel, secOrTow, tower, lsector, sector, layer;

  this->SelectChambersFormData(in, barrelOrEndcap, wheel, secOrTow, tower, lsector, sector, layer);
  this->SelectChambersAction(barrelOrEndcap, wheel, secOrTow, tower, lsector, sector, layer);
  this->Default(in, out);
}
void XdaqRpcConnectivityTest::SelectChambersGUI(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception)
{

  LOG4CPLUS_INFO(getApplicationLogger(),"SelectChambersGUI.");

  string actionSelectChambers =
    toolbox::toString("/%s/SelectChambers",getApplicationDescriptor()->getURN().c_str());
  
  *out << cgicc::form().set("method","POST").set("action", actionSelectChambers).set("enctype","multipart/form-data") << std::endl;
  *out << cgicc::table().set("width", "600").set("align","center").set("class","wborder")<< std::endl;
  *out << cgicc::tr()<< std::endl;
    *out << cgicc::th() << "Barrel <br />" << std::endl;
    *out << cgicc::input().set("type","radio").set("name","barrelOrEndcap").set("id","barrelOrEndcap").set("value","0").set("checked","checked") << std::endl;
    *out << cgicc::th() << std::endl;
    *out << cgicc::th() << "Endcap <br />" << std::endl;
    *out << cgicc::input().set("type","radio").set("name","barrelOrEndcap").set("id","barrelOrEndcap").set("value","1") << std::endl;
    *out << cgicc::th() << std::endl;
  *out << cgicc::tr()<< std::endl;
  
  // start selection
  *out << cgicc::tr()<< std::endl;
  //BARREL-COLUMN
  *out << cgicc::td()<< std::endl;
  *out << "<table>" << std::endl;
  // WHEEL
  *out << "<tr><td></td><td>wheel</td><td>" << std::endl;
  *out << cgicc::select().set("name","bWheel").set("id","bWheel") << std::endl;
    *out << "<option value=\"99\">all</option>" << std::endl;
    for (int i=-2;i<=2;i++)
      *out << "<option value=\"" << i << "\">" << i << "</option>" << std::endl;
  *out << cgicc::select() << std::endl;
  *out << "</td></tr>" << std::endl;
  // TOWER
  *out << "<tr><td>" << std::endl;
  *out << cgicc::input().set("type","radio").set("name","bSecOrTow").set("id","bSecOrTow").set("value","1").set("checked","checked")<<std::endl;
  *out << "</td><td>tower</td><td>" << std::endl;
  *out << cgicc::select().set("name","bTower").set("id","bTower") << std::endl;
    *out << "<option value=\"99\">both</option>" << std::endl;
    *out << "<option value=\"0\">near</option>" << std::endl;
    *out << "<option value=\"1\">far</option>" << std::endl;
  *out << cgicc::select() << std::endl;
  *out << "</td></tr>" << std::endl;
  // SECTOR = LSector
  *out << "<tr><td>" << std::endl;
  *out << cgicc::input().set("type","radio").set("name","bSecOrTow").set("id","bSecOrTow").set("value","0")<<std::endl;
  *out << "</td><td>sector</td><td>" << std::endl;
  *out << cgicc::select().set("name","bLSector").set("id","bLSector") << std::endl;
    *out << "<option value=\"99\">all</option>" << std::endl;
    for (int i=1;i<=12;i++)
      *out << "<option value=\"" << i << " \">" << i << "</option>" << std::endl;
  *out << cgicc::select() << std::endl;
  *out << "</td></tr>" << std::endl;
  // SUBSECTOR
  /*  *out << "<tr><td></td><td>subsector</td><td>" << std::endl;
   *out << cgicc::select().set("name","bSubSector").set("id","bSubSector") << std::endl;
   *out << "<option value=\"99\">all</option>" << std::endl;
   for (int i=0;i<4;i++)
   *out << "<option value=\"" << i << "\">" << bsubsectors[i] << "</option>" << std::endl;
   *out << cgicc::select() << std::endl;
   *out << "</td></tr>" << std::endl;
   */
  //  *out << cgicc::input().set("type","hidden").set("name","bSubSector").set("id","bSubSector").set("value","0") ;
  // LAYER
  *out << "<tr><td>" << std::endl;
  *out << cgicc::input().set("type","radio").set("name","bSecOrTow").set("id","bSecOrTow").set("value","3")<<std::endl;
  *out << "</td><td>layer</td><td>" << std::endl;
  *out << cgicc::select().set("name","bLayer").set("id","bLayer") << std::endl;
    *out << "<option value=\"99\">all</option>" << std::endl;
    for (int i=1;i<=6;i++)
      *out << "<option value=\"" << i << "\">" << blayers[i] << "</option>" << std::endl;
  *out << cgicc::select() << std::endl;
  *out << "</td></tr>" << std::endl;
  
  *out << "</table>" << std::endl;
  *out << cgicc::td()<< std::endl;
  // ENDCAP-COLUMN
  *out << cgicc::td()<< std::endl;
  
  *out << "<table border=\"0\">" << std::endl;
  // WHEEL
  *out << "<tr><td></td><td>disk</td><td>" << std::endl;
  *out << cgicc::select().set("name","eWheel").set("id","eWheel") << std::endl;
    *out << "<option value=\"99\">all</option>" << std::endl;
    for (int i=-3;i<=3;i++)
      if (i != 0)
	*out << "<option value=\"" << i << "\">" << i << "</option>" << std::endl;
  *out << cgicc::select() << std::endl;
  *out << "</td></tr>" << std::endl;
  // TOWER
  *out << "<tr><td>" << std::endl;
  *out << cgicc::input().set("type","radio").set("name","eSecOrTow").set("id","eSecOrTow").set("value","1").set("checked","checked")<<std::endl;
  *out << "</td><td>tower</td><td>" << std::endl;
  *out << cgicc::select().set("name","eTower").set("id","eTower") << std::endl;
    *out << "<option value=\"99\">both</option>" << std::endl;
    *out << "<option value=\"0\">near</option>" << std::endl;
    *out << "<option value=\"1\">far</option>" << std::endl;
  *out << cgicc::select() << std::endl;
  *out << "</td></tr>" << std::endl;
  // LINK-SECTOR
  *out << "<tr><td>" << std::endl;
  *out << cgicc::input().set("type","radio").set("name","eSecOrTow").set("id","eSecOrTow").set("value","0")<<std::endl;
  *out << "</td><td>link-sector</td><td>" << std::endl;
  *out << cgicc::select().set("name","eLSector").set("id","eLSector") << std::endl;
    *out << "<option value=\"99\">all</option>" << std::endl;
    for (int i=1;i<=12;i++)
      *out << "<option value=\"" << i << " \">" << i << "</option>" << std::endl;
  *out << cgicc::select() << std::endl;
  *out << "</td></tr>" << std::endl;
  // SECTOR
  *out << "<tr><td>" << std::endl;
  *out << cgicc::input().set("type","radio").set("name","eSecOrTow").set("id","eSecOrTow").set("value","2")<<std::endl;
  *out << "</td><td>sector</td><td>" << std::endl;
  *out << cgicc::select().set("name","eSector").set("id","eSector") << std::endl;
    *out << "<option value=\"99\">all</option>" << std::endl;
    for (int i=1;i<=36;i++)
      *out << "<option value=\"" << i << "\">" << i << "</option>" << std::endl;
  *out << cgicc::select() << std::endl;
  *out << "</td></tr>" << std::endl;
  // LAYER
  *out << "<tr><td>" << std::endl;
  *out << cgicc::input().set("type","radio").set("name","eSecOrTow").set("id","eSecOrTow").set("value","3")<<std::endl;
  *out << "</td><td>layer</td><td>" << std::endl;
  *out << cgicc::select().set("name","eLayer").set("id","eLayer") << std::endl;
    *out << "<option value=\"99\">all</option>" << std::endl;
    for (int i=1;i<=3;i++)
      *out << "<option value=\"" << i << "\">" << i << "</option>" << std::endl;
  *out << cgicc::select() << std::endl;
  *out << "</td></tr>" << std::endl;
  
  *out << "</table>" << std::endl;
  *out << cgicc::td()<< std::endl;
  // end selection
  *out << cgicc::tr()<< std::endl;
  
  *out << cgicc::tr()<< std::endl;
  *out << cgicc::td().set("colspan", "2")<< std::endl;
  *out << cgicc::input().set("type","submit").set("align","center").set("name", "send").set("value", "add selection")<<std::endl;
  *out << cgicc::td()<< std::endl;
  *out << cgicc::tr()<< std::endl;
  
  // start selected
  *out << cgicc::tr()<< std::endl;
  *out << cgicc::td().set("colspan", "2")<< std::endl;
  *out << cgicc::ul() << std::endl;
  *out << selectedChambers;
  *out << cgicc::ul() << std::endl;
  *out << cgicc::td()<< std::endl;
  // end selected
  *out << cgicc::tr()<< std::endl;
  
  *out << cgicc::table() << std::endl;
  *out << cgicc::form() << std::endl;

  string actionReset =
    toolbox::toString("/%s/Reset",getApplicationDescriptor()->getURN().c_str());
  
  *out << cgicc::form().set("method","POST").set("action", actionReset).set("enctype","multipart/form-data") << std::endl;
  *out << cgicc::table().set("width", "600").set("align","center").set("class","wborder")<< std::endl;
  *out << cgicc::tr()<< std::endl;
  *out << cgicc::td();
  *out << cgicc::input().set("type","submit").set("align","center").set("name", "send").set("value", "reset")<<std::endl;
  *out << cgicc::td()<< std::endl;
  *out << cgicc::tr()<< std::endl;
  *out << cgicc::table() << std::endl;
  *out << cgicc::form() << std::endl;
}
void XdaqRpcConnectivityTest::SelectChambersFormData(xgi::Input * in, bool &barrelOrEndcap, int &wheel, int &secOrTow, int &tower, int &lSector, int& sector, int &layer) throw (xgi::exception::Exception)
{

  LOG4CPLUS_INFO(getApplicationLogger(),"SelectChambersFormData.");

  try{

    Cgicc formData(in);
    
    barrelOrEndcap  = (bool)formData.getElement("barrelOrEndcap")->getIntegerValue();
    if (!barrelOrEndcap) {
      wheel           = formData.getElement("bWheel")->getIntegerValue();
      secOrTow        = formData.getElement("bSecOrTow")->getIntegerValue();
      tower           = formData.getElement("bTower")->getIntegerValue();
      lSector         = formData.getElement("bLSector")->getIntegerValue();
      sector          = lSector;
      layer           = formData.getElement("bLayer")->getIntegerValue();
    }
    else {
      wheel           = formData.getElement("eWheel")->getIntegerValue();
      secOrTow        = formData.getElement("eSecOrTow")->getIntegerValue();
      tower           = formData.getElement("eTower")->getIntegerValue();
      lSector         = formData.getElement("eLSector")->getIntegerValue();
      sector          = formData.getElement("eSector")->getIntegerValue();
      layer           = formData.getElement("eLayer")->getIntegerValue();
    }

  }
  catch(xgi::exception::Exception& e){
    LOG4CPLUS_ERROR(getApplicationLogger(), string("xgi-error at SelectChambersFormData. ") + e.what());
    //    XCEPT_RETHROW(xgi::exception::Exception, "xgi-error at SelectChambersFormData.", e);
  }
}
void XdaqRpcConnectivityTest::SelectChambersAction(bool &barrelOrEndcap, int &wheel, int &secOrTow, int &tower, int &lSector, int &sector, int &layer) throw (xoap::exception::Exception)
{

  LOG4CPLUS_INFO(getApplicationLogger(),"SelectChambersAction.");

  FAIV* febAccessInfoVector;
  std::vector<int> wheelV;
  std::vector<int> lsectorV;
  std::stringstream ss_selectedChambers;

  XdaqDbServiceClient::BarrelOrEndcap boe = boe_arr[(int)(barrelOrEndcap)];
  
  try {
    if ((secOrTow==0 && lSector==99) || (secOrTow == 1 && tower==99) || (secOrTow==2 && sector==99) || (secOrTow==3 && layer==99))
      {
	if (wheel == 99)
	  {
	    febAccessInfoVector = dbServiceClient.getFebsByBarrelOrEndcap(boe);
	    ss_selectedChambers << "<li>" << str_barrelOrEndcap[(int)barrelOrEndcap] << ", all wheels</li>";
	  }
	else
	  {
	    febAccessInfoVector = dbServiceClient.getFebsByDiskOrWheel(wheel, boe);
	    ss_selectedChambers << "<li>" << str_barrelOrEndcap[(int)barrelOrEndcap]+", wheel " << wheel << "</li>";
	  }
	FAIVVector.push_back(*febAccessInfoVector);
      }
    else
      {
	if (wheel == 99)
	  {
	    if (!barrelOrEndcap) // barrel
	      for (int i=-2;i<=2;i++)
		wheelV.push_back(i);
	    else
	      for (int i=-3;i<=3;i++)
		if (i != 0)
		  wheelV.push_back(i);
	    ss_selectedChambers << "<li>" << str_barrelOrEndcap[(int)barrelOrEndcap] << ", all wheels, ";
	  }
	else
	  {
	    wheelV.push_back(wheel);
	    ss_selectedChambers << "<li>" << str_barrelOrEndcap[(int)barrelOrEndcap] << ", wheel " << wheel << ", ";
	  }
	
	if (secOrTow == 3) // layer
	{
	  ss_selectedChambers << "layer " << layer << "</li>";
	  for (std::vector<int>::iterator iw=wheelV.begin();iw<wheelV.end();iw++)
	    {
	      febAccessInfoVector = dbServiceClient.getFebsByLayer(*iw,layer,boe);
	      FAIVVector.push_back(*febAccessInfoVector);
	    }
	}
	else if (secOrTow == 0 || secOrTow == 1) // tower or link-sector
	  {
	    if (secOrTow == 1) // tower
	      {
		if (tower==0) // near
		  {
		    ss_selectedChambers << "near tower</li>";
		    for (int i=1;i<=3;i++)
		      lsectorV.push_back(i);
		    for (int i=10;i<=12;i++)
		      lsectorV.push_back(i);
		  }
		else // far
		  {
		    ss_selectedChambers << "far tower</li>";
		    for (int i=4;i<=9;i++)
		      lsectorV.push_back(i);
		  }
	      }
	    else if (secOrTow == 0) // link-sector
	      {
		ss_selectedChambers << "linksector " << lSector << "</li>";
		lsectorV.push_back(lSector);
	      }
	  
	    int firstSector, currentSector;
	    for (std::vector<int>::iterator iw=wheelV.begin();iw<wheelV.end();iw++)
	      {
		for (std::vector<int>::iterator ils=lsectorV.begin();ils<lsectorV.end();ils++)
		  {
		    if (barrelOrEndcap) // endcap
		      {
			firstSector = 2;
		      if (*iw == 2 || *iw == -2)
			firstSector = 36;
		      for (int i=0;i<3;i++)
			{
			  currentSector = ( 3 * (*ils - 1) + i + firstSector - 1) % 36 + 1;
			  try
			    {
			      febAccessInfoVector = dbServiceClient.getFebsBySector(*iw,currentSector,boe);
			      FAIVVector.push_back(*febAccessInfoVector);
			      for (FAIV::iterator iFAI = (*febAccessInfoVector).begin();iFAI != (*febAccessInfoVector).end(); ++iFAI)
				{
				  stringstream ss_currentSector;
				  ss_currentSector << "Current sector is " << currentSector << ", app instance" << iFAI->bag.getXdaqAppInstance() << " " << string(iFAI->bag.getChamberLocationName());
				  LOG4CPLUS_INFO(getApplicationLogger(), ss_currentSector.str());
				}
			    }
			  catch(xdaq::exception::Exception& e){
			    LOG4CPLUS_ERROR(getApplicationLogger(), string("xdaq-error at SelectChambersAction. ") + e.what());
			    //    XCEPT_RETHROW(xoap::exception::Exception, "xoap-error at SelectChambersAction.", e);
			  }
			}
		      }
		    else
		      {
			febAccessInfoVector = dbServiceClient.getFebsBySector(*iw,*ils,boe);
			FAIVVector.push_back(*febAccessInfoVector);
		      }
		  }
	      }
	  }
	else if (barrelOrEndcap && secOrTow == 2) // sector
	  {
	    ss_selectedChambers << "sector " << sector << "</li>";
	    for (std::vector<int>::iterator iw=wheelV.begin();iw<wheelV.end();iw++)
	      {
		febAccessInfoVector = dbServiceClient.getFebsBySector(*iw,sector,boe);
		FAIVVector.push_back(*febAccessInfoVector);
	      }
	  }
      }
    selectedChambers += ss_selectedChambers.str();
  }
  catch(xoap::exception::Exception& e){
    LOG4CPLUS_ERROR(getApplicationLogger(), string("xoap-error at SelectChambersAction. ") + e.what());
    //    XCEPT_RETHROW(xoap::exception::Exception, "xoap-error at SelectChambersAction.", e);
  }
  catch(xdaq::exception::Exception& e){
    LOG4CPLUS_ERROR(getApplicationLogger(), string("xdaq-error at SelectChambersAction. ") + e.what());
    //    XCEPT_RETHROW(xoap::exception::Exception, "xoap-error at SelectChambersAction.", e);
  }
}


/**************************************************
** SetFebValues                                  **
**************************************************/
void XdaqRpcConnectivityTest::SetFebValues(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception)
{

  LOG4CPLUS_INFO(getApplicationLogger(),"SetFebValues.");

  int VTH[4], VMON[4];
  instanceResponseMap lbbAppMapResponse;
  this->SetFebValuesFormData(in, VTH, VMON);
  this->SetFebValuesAction(in, out, VTH, VMON, lbbAppMapResponse);
  this->SetFebValuesResult(in, out, lbbAppMapResponse);  
}
void XdaqRpcConnectivityTest::SetFebValuesGUI(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception)
{

  LOG4CPLUS_INFO(getApplicationLogger(),"SetFebValuesGUI.");

  string actionSetFebValues =
    toolbox::toString("/%s/SetFebValues",getApplicationDescriptor()->getURN().c_str());

  *out << cgicc::form().set("method","POST").set("action", actionSetFebValues).set("enctype","multipart/form-data") << std::endl;
  *out << cgicc::table().set("width", "600").set("align","center").set("class","wborder")<< std::endl;
  *out << cgicc::tr()<< std::endl;
  *out << cgicc::th() << "Threshold" << cgicc::th() << cgicc::th() << "Pulse width" << cgicc::th() << std::endl;
  *out << cgicc::tr()<< std::endl;
  
  *out << cgicc::tr() << std::endl;
  *out << cgicc::td() << std::endl;
  for (int i=0;i<4;i++)
    {
      if (i == 2)
	*out << "<br /><i>Only for endcap:</i><br />" << std::endl;
      *out << "VTH" << (i+1) << " <input type=\"text\" size=\"5\" id=\"VTH" << i << "\" name=\"VTH" << i << "\" value=\"210\"></input>";
      *out << "<br />" << std::endl;
    }
  *out << cgicc::td() << std::endl;
  
  *out << cgicc::td() << std::endl;
  for (int i=0;i<4;i++)
    {
      if (i == 2)
	*out << "<br /><i>Only for endcap:</i><br />" << std::endl;
      *out << "VMON" << (i+1) << " <input type=\"text\" size=\"5\" id=\"VMON" << i << "\" name=\"VMON" << i << "\" value=\"3500\"></input>";
      *out << "<br />" << std::endl;
    }  
  *out << cgicc::td() << std::endl;
  *out << cgicc::tr() << std::endl;

  *out << cgicc::tr()<< std::endl;
  *out << cgicc::td().set("colspan", "2")<< std::endl;
  *out << cgicc::input().set("type","submit").set("align","center").set("name", "send").set("value", "write to FEBs")<<std::endl;
  *out << cgicc::td()<< std::endl;
  *out << cgicc::tr()<< std::endl;

  *out << cgicc::table() << std::endl;
  *out << cgicc::form() << std::endl;
}
void XdaqRpcConnectivityTest::SetFebValuesFormData(xgi::Input * in, int VTH[], int VMON[]) throw (xgi::exception::Exception)
{

  LOG4CPLUS_INFO(getApplicationLogger(),"SetFebValuesFormData.");

  try{
    Cgicc formData(in);
    stringstream vth;
    stringstream vmon;
    for (int i=0;i< 4;i++)
      {
	vth  << "VTH" << i;
	vmon << "VMON" << i;
	VTH[i]  = formData.getElement(vth.str() )->getIntegerValue();
	VMON[i] = formData.getElement(vmon.str())->getIntegerValue();
      }
  }
  catch(xgi::exception::Exception& e){
    LOG4CPLUS_ERROR(getApplicationLogger(), string("xgi-error at SetFebValuesFormData. ") + e.what());
    //    XCEPT_RETHROW(xgi::exception::Exception, "xgi-error at SetFebValuesFormData.", e);
  }
}
void XdaqRpcConnectivityTest::SetFebValuesAction(xgi::Input * in, xgi::Output * out, int VTH[], int VMON[], instanceResponseMap &lbbAppMapResponse) throw (xoap::exception::Exception)
{

  LOG4CPLUS_INFO(getApplicationLogger(),"SetFebValuesAction.");

  instanceRequestMap lbbAppMapRequest;
  
  for( FAIVV::iterator iFAIV = FAIVVector.begin();iFAIV != FAIVVector.end(); ++iFAIV)
    {
      FAIV  febAccessInfoVector = *iFAIV;
      for (FAIV::iterator iFAI = febAccessInfoVector.begin();iFAI != febAccessInfoVector.end(); ++iFAI)
	{
	  FebAccessInfo& febAccessInfo = iFAI->bag;
	  int xdaqAppNumber = febAccessInfo.getXdaqAppInstance(); 
	  MassiveWriteRequest& writeRequest = lbbAppMapRequest[xdaqAppNumber].bag;
	  string name = febAccessInfo.getChamberLocationName();
	  bool barrelOrEndcap = (name.find("W") == name.npos);
	  int chips = (barrelOrEndcap?4:2);
	  if(lbbAppMapRequest[xdaqAppNumber].bag.getProperties().empty())
	    {
	      for (int i=0;i<chips;i++)
		{
		  writeRequest.getProperties().push_back(prop_vth[i]);
		  writeRequest.getProperties().push_back(prop_vmon[i]);
		}
	    }
	  xdata::Bag<FebValues> valuesBag;
	  valuesBag.bag.getFeb().bag.setCcuAddress(febAccessInfo.getCcuAddress());
	  valuesBag.bag.getFeb().bag.setChannel(febAccessInfo.getI2cChannel());
	  valuesBag.bag.getFeb().bag.setAddress(febAccessInfo.getFebAddress());
	  valuesBag.bag.getFeb().bag.setChamberLocationName(febAccessInfo.getChamberLocationName());
	  valuesBag.bag.getFeb().bag.setFebLocalEtaPartition(febAccessInfo.getFebLocalEtaPartition());
	  valuesBag.bag.getFeb().bag.setEndcap(barrelOrEndcap);
	  for (int i=0;i<chips;i++)
	    {
	      valuesBag.bag.getValues().push_back(VTH[i]);
	      valuesBag.bag.getValues().push_back(VMON[i]);
	    }
	  writeRequest.getFebValues().push_back(valuesBag);
	}
    }
  for(instanceRequestMap::iterator iMap = lbbAppMapRequest.begin(); iMap != lbbAppMapRequest.end(); ++iMap)
    {
      try
	{
	  lbbAppMapResponse[iMap->first] =lboxAccessClient.massiveWrite(iMap->second, iMap->first);
	}
      catch(xoap::exception::Exception& e){
	LOG4CPLUS_ERROR(getApplicationLogger(), string("xoap-error at SetFebValuesAction. ") + e.what());
	//	XCEPT_RETHROW(xoap::exception::Exception, "xoap-error at SetFebValuesAction.", e);
      }
    }
}
void XdaqRpcConnectivityTest::SetFebValuesResult(xgi::Input * in, xgi::Output * out, instanceResponseMap lbbAppMapResponse) throw (xgi::exception::Exception)
{

  LOG4CPLUS_INFO(getApplicationLogger(),"SetFebValuesResult.");

  subTitle = "Setting FEB Values Result.";
  this->PageHeader(in, out, mainTitle, subTitle);
  *out << cgicc::table().set("width", "600").set("align","left").set("class","wborder")<< std::endl;
  for(instanceResponseMap::iterator iMap = lbbAppMapResponse.begin(); iMap != lbbAppMapResponse.end(); ++iMap)
    {
      MassiveReadResponse& readResponse = lbbAppMapResponse[iMap->first]->bag;
      FebProperties& props = readResponse.getProperties();
      *out << cgicc::tr();         
      *out << cgicc::th() << "chamber" << cgicc::th() << std::endl;
      *out << cgicc::th() << "Local Partition" << cgicc::th() << std::endl;
      *out << cgicc::th() << "CCU Address" << cgicc::th() << std::endl;
      *out << cgicc::th() << "CB Channel" << cgicc::th() << std::endl;
      *out << cgicc::th() << "I2C Local Number" << cgicc::th() << std::endl;
      for (FebProperties::iterator iProp = props.begin(); iProp != props.end(); ++iProp)
	*out << cgicc::th() << (string)(*iProp) << cgicc::th() << std::endl;
      *out << cgicc::tr();
      
      FebValuesVector& valuesVector = readResponse.getFebValues();
      for (FebValuesVector::iterator iVal = valuesVector.begin(); iVal != valuesVector.end(); ++iVal) {
	FebValues& febValues = iVal->bag;
	FebInfo& febInfo = febValues.getFeb().bag;
	*out << cgicc::tr()
	     << cgicc::td().set("class","ok") << (string)febInfo.getChamberLocationName() << cgicc::td()
	     << cgicc::td().set("class","ok") << (string)febInfo.getFebLocalEtaPartition() << cgicc::td()
	     << cgicc::td().set("class","ok") << febInfo.getCcuAddress() << cgicc::td()
	     << cgicc::td().set("class","ok") << febInfo.getChannel() << cgicc::td()
	     << cgicc::td().set("class","ok") << febInfo.getAddress() << cgicc::td();
	FebValues::Values& values = febValues.getValues();
	for (FebValues::Values::iterator iValue = values.begin(); iValue != values.end(); ++iValue)
	  *out << cgicc::td().set("class","ok") << (*iValue) << cgicc::td();
	*out << cgicc::tr();
      }
      *out << cgicc::table() << std::endl;
    }
  this->PageFooter(in, out);
}

/**************************************************
** ReadFebValues                                 **
**************************************************/
void XdaqRpcConnectivityTest::ReadFebValues(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception)
{

  LOG4CPLUS_INFO(getApplicationLogger(),"ReadFebValues.");

  this->ReadFebValuesAction(in, out);
}
void XdaqRpcConnectivityTest::ReadFebValuesGUI(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception)
{

  LOG4CPLUS_INFO(getApplicationLogger(),"ReadFebValuesGUI.");
  
  string actionReadFebValues =
    toolbox::toString("/%s/ReadFebValues",getApplicationDescriptor()->getURN().c_str());

  *out << cgicc::form().set("method","POST").set("action", actionReadFebValues).set("enctype","multipart/form-data") << std::endl;
  *out << cgicc::table().set("width", "600").set("align","center").set("class","wborder")<< std::endl;
  *out << cgicc::tr()<< std::endl;
  *out << cgicc::td()<< std::endl;
  *out << cgicc::input().set("type","submit").set("align","center").set("name", "send").set("value", "read FEBs")<<std::endl;
  *out << cgicc::td()<< std::endl;
  *out << cgicc::tr()<< std::endl;
  *out << cgicc::table() << std::endl;
  *out << cgicc::form() << std::endl;
}
void XdaqRpcConnectivityTest::ReadFebValuesAction(xgi::Input * in, xgi::Output * out) throw (xoap::exception::Exception)
{

  LOG4CPLUS_INFO(getApplicationLogger(),"ReadFebValuesAction.");
  
  instanceReadRequestMap lbbAppMapRequest;
  instanceReadResponseMap lbbAppMapResponse;
  
  for( FAIVV::iterator iFAIV = FAIVVector.begin();iFAIV != FAIVVector.end(); ++iFAIV)
    {
      FAIV  febAccessInfoVector = *iFAIV;
      for (FAIV::iterator iFAI = febAccessInfoVector.begin();iFAI != febAccessInfoVector.end(); ++iFAI)
	{
	  FebAccessInfo& febAccessInfo = iFAI->bag;
	  int xdaqAppNumber = febAccessInfo.getXdaqAppInstance(); 
	  MassiveReadRequest& readRequest = lbbAppMapRequest[xdaqAppNumber].bag;
	  string name = febAccessInfo.getChamberLocationName();
	  bool barrelOrEndcap = (name.find("W") == name.npos);
	  int chips = (barrelOrEndcap?4:2);
	  int temperatures = (barrelOrEndcap?2:1);
	  if(lbbAppMapRequest[xdaqAppNumber].bag.getProperties().empty())
	    {
	      for (int i=0;i<chips;i++)
		{
		  readRequest.getProperties().push_back(prop_vth[i]);
		  readRequest.getProperties().push_back(prop_vmon[i]);
		}
	      for (int i=0;i<temperatures;i++)
		readRequest.getProperties().push_back(prop_temp[i]);
	    }
	  xdata::Bag<FebInfo> febInfoBag;
	  febInfoBag.bag.setXdaqAppInstance(xdaqAppNumber);
	  febInfoBag.bag.setFebLocalEtaPartition(febAccessInfo.getFebLocalEtaPartition());
	  febInfoBag.bag.setChamberLocationName(febAccessInfo.getChamberLocationName());
	  febInfoBag.bag.setCcuAddress(febAccessInfo.getCcuAddress());
	  febInfoBag.bag.setChannel(febAccessInfo.getI2cChannel());
	  febInfoBag.bag.setAddress(febAccessInfo.getFebAddress());
	  febInfoBag.bag.setEndcap(barrelOrEndcap);
	  readRequest.getFebs().push_back(febInfoBag);
	}
    }
  for(instanceReadRequestMap::iterator iMap = lbbAppMapRequest.begin(); iMap != lbbAppMapRequest.end(); ++iMap)
    {
      try
	{
	  lbbAppMapResponse[iMap->first] =lboxAccessClient.massiveRead(iMap->second, iMap->first);
	}
      catch(xoap::exception::Exception& e){
	LOG4CPLUS_ERROR(getApplicationLogger(), string("xoap-error at ReadFebValuesAction. ") + e.what());
	//	XCEPT_RETHROW(xoap::exception::Exception, "xoap-error at SetFebValuesAction.", e);
      }
    }
  this->ReadFebValuesResult(in, out, lbbAppMapResponse);  
}
void XdaqRpcConnectivityTest::ReadFebValuesResult(xgi::Input * in, xgi::Output * out, instanceReadResponseMap lbbAppMapResponse) throw (xgi::exception::Exception)
{

  LOG4CPLUS_INFO(getApplicationLogger(),"ReadFebValuesResult.");

  subTitle = "Setting FEB Values Result.";
  this->PageHeader(in, out, mainTitle, subTitle);
  *out << cgicc::table().set("width", "600").set("align","left").set("class","wborder")<< std::endl;
  for(instanceResponseMap::iterator iMap = lbbAppMapResponse.begin(); iMap != lbbAppMapResponse.end(); ++iMap)
    {
      MassiveReadResponse& readResponse = lbbAppMapResponse[iMap->first]->bag;
      FebProperties& props = readResponse.getProperties();
      *out << cgicc::tr();         
      *out << cgicc::th() << "chamber" << cgicc::th() << std::endl;
      *out << cgicc::th() << "Local Partition" << cgicc::th() << std::endl;
      *out << cgicc::th() << "CCU Address" << cgicc::th() << std::endl;
      *out << cgicc::th() << "CB Channel" << cgicc::th() << std::endl;
      *out << cgicc::th() << "I2C Local Number" << cgicc::th() << std::endl;
      for (FebProperties::iterator iProp = props.begin(); iProp != props.end(); ++iProp)
	*out << cgicc::th() << (string)(*iProp) << cgicc::th() << std::endl;
      *out << cgicc::tr();
      
      FebValuesVector& valuesVector = readResponse.getFebValues();
      for (FebValuesVector::iterator iVal = valuesVector.begin(); iVal != valuesVector.end(); ++iVal) {
	FebValues& febValues = iVal->bag;
	FebInfo& febInfo = febValues.getFeb().bag;
	*out << cgicc::tr()
	     << cgicc::td().set("class","ok") << (string)febInfo.getChamberLocationName() << cgicc::td()
	     << cgicc::td().set("class","ok") << (string)febInfo.getFebLocalEtaPartition() << cgicc::td()
	     << cgicc::td().set("class","ok") << febInfo.getCcuAddress() << cgicc::td()
	     << cgicc::td().set("class","ok") << febInfo.getChannel() << cgicc::td()
	     << cgicc::td().set("class","ok") << febInfo.getAddress() << cgicc::td();
	FebValues::Values& values = febValues.getValues();
	int i = 1;
	//	string name = febAccessInfo.getChamberLocationName();
	//	bool barrelOrEndcap = (name.find("W") == name.npos);
	//	int chips = (barrelOrEndcap?4:2);
	int chips = 2;
	std::string td_class = "ok";
	for (FebValues::Values::iterator iValue = values.begin(); iValue != values.end(); ++iValue)
	  {
	    if (i > chips)
	      {
		if ((int)(*iValue) > 32)
		  td_class="problem";
		else
		  td_class="ok";
	      }
	    *out << cgicc::td().set("class",td_class) << (*iValue) << cgicc::td();
	    i++;
	  }
	*out << cgicc::tr();
      }
      *out << cgicc::table() << std::endl;
    }
  this->PageFooter(in, out);
}


/**************************************************
** ReadFebNoise                                  **
**************************************************/
/*
void XdaqRpcConnectivityTest::ReadFebNoise(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception)
{

  LOG4CPLUS_INFO(getApplicationLogger(),"ReadFebNoise.");

  this->ReadFebNoiseAction(in, out);
}
void XdaqRpcConnectivityTest::ReadFebNoiseGUI(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception)
{

  LOG4CPLUS_INFO(getApplicationLogger(),"ReadFebNoiseGUI.");

  string actionReadFebNoise =
    toolbox::toString("/%s/readFebNoise",getApplicationDescriptor()->getURN().c_str());

  *out << cgicc::form().set("method","POST").set("action", actionReadFebNoise).set("enctype","multipart/form-data") << std::endl;
  *out << cgicc::table().set("width", "600").set("align","center").set("class","wborder")<< std::endl;
  *out << cgicc::tr()<< std::endl;
  *out << cgicc::td()<< std::endl;
  *out << cgicc::input().set("type","submit").set("align","center").set("name", "send").set("value", "read Noise")<<std::endl;
  *out << cgicc::td()<< std::endl;
  *out << cgicc::tr()<< std::endl;
  *out << cgicc::table() << std::endl;
  *out << cgicc::form() << std::endl;
}
void XdaqRpcConnectivityTest::ReadFebNoiseAction(xgi::Input * in, xgi::Output * out) throw (xoap::exception::Exception)
{

  LOG4CPLUS_INFO(getApplicationLogger(),"ReadFebNoiseAction.");

  instanceReadRequestMap lbbAppMapRequest;
  instanceReadResponseMap lbbAppMapResponse;
  
  for( FAIVV::iterator iFAIV = FAIVVector.begin();iFAIV != FAIVVector.end(); ++iFAIV)
    {
      FAIV  febAccessInfoVector = *iFAIV;
      for (FAIV::iterator iFAI = febAccessInfoVector.begin();iFAI != febAccessInfoVector.end(); ++iFAI)
	{
	  FebAccessInfo& febAccessInfo = iFAI->bag;
	  int xdaqAppNumber = febAccessInfo.getXdaqAppInstance(); 
	  MassiveReadRequest& readRequest = lbbAppMapRequest[xdaqAppNumber].bag;
	  string name = febAccessInfo.getChamberLocationName();
	  bool barrelOrEndcap = (name.find("W") == name.npos);
	  int chips = (barrelOrEndcap?4:2);
	  int temperatures = (barrelOrEndcap?2:1);
	  if(lbbAppMapRequest[xdaqAppNumber].bag.getProperties().empty())
	    {
	      for (int i=0;i<chips;i++)
		{
		  readRequest.getProperties().push_back(prop_vth[i]);
		  readRequest.getProperties().push_back(prop_vmon[i]);
		}
	      for (int i=0;i<temperatures;i++)
		readRequest.getProperties().push_back(prop_temp[i]);
	    }
	  xdata::Bag<FebInfo> febInfoBag;
	  febInfoBag.bag.setXdaqAppInstance(xdaqAppNumber);
	  febInfoBag.bag.setFebLocalEtaPartition(febAccessInfo.getFebLocalEtaPartition());
	  febInfoBag.bag.setChamberLocationName(febAccessInfo.getChamberLocationName());
	  febInfoBag.bag.setCcuAddress(febAccessInfo.getCcuAddress());
	  febInfoBag.bag.setChannel(febAccessInfo.getI2cChannel());
	  febInfoBag.bag.setAddress(febAccessInfo.getFebAddress());
	  febInfoBag.bag.setEndcap(barrelOrEndcap);
	  readRequest.getFebs().push_back(febInfoBag);
	}
    }
  for(instanceReadRequestMap::iterator iMap = lbbAppMapRequest.begin(); iMap != lbbAppMapRequest.end(); ++iMap)
    {
      try
	{
	  lbbAppMapResponse[iMap->first] =lboxAccessClient.massiveRead(iMap->second, iMap->first);
	}
      catch(xoap::exception::Exception& e){
	LOG4CPLUS_ERROR(getApplicationLogger(), string("xoap-error at ReadFebValuesAction. ") + e.what());
	//	XCEPT_RETHROW(xoap::exception::Exception, "xoap-error at SetFebValuesAction.", e);
      }
    }
  this->ReadFebValuesResult(in, out, lbbAppMapResponse);  
}
void XdaqRpcConnectivityTest::ReadFebNoiseResult(xgi::Input * in, xgi::Output * out, instanceReadResponseMap lbbAppMapResponse) throw (xgi::exception::Exception)
{

  LOG4CPLUS_INFO(getApplicationLogger(),"ReadFebNoiseResult.");

  subTitle = "Setting FEB Values Result.";
  this->PageHeader(in, out, mainTitle, subTitle);
  *out << cgicc::table().set("width", "600").set("align","left").set("class","wborder")<< std::endl;
  for(instanceResponseMap::iterator iMap = lbbAppMapResponse.begin(); iMap != lbbAppMapResponse.end(); ++iMap)
    {
      MassiveReadResponse& readResponse = lbbAppMapResponse[iMap->first]->bag;
      FebProperties& props = readResponse.getProperties();
      *out << cgicc::tr();         
      *out << cgicc::th() << "chamber" << cgicc::th() << std::endl;
      *out << cgicc::th() << "Local Partition" << cgicc::th() << std::endl;
      *out << cgicc::th() << "CCU Address" << cgicc::th() << std::endl;
      *out << cgicc::th() << "CB Channel" << cgicc::th() << std::endl;
      *out << cgicc::th() << "I2C Local Number" << cgicc::th() << std::endl;
      for (FebProperties::iterator iProp = props.begin(); iProp != props.end(); ++iProp)
	*out << cgicc::th() << (string)(*iProp) << cgicc::th() << std::endl;
      *out << cgicc::tr();
      
      FebValuesVector& valuesVector = readResponse.getFebValues();
      for (FebValuesVector::iterator iVal = valuesVector.begin(); iVal != valuesVector.end(); ++iVal) {
	FebValues& febValues = iVal->bag;
	FebInfo& febInfo = febValues.getFeb().bag;
	*out << cgicc::tr()
	     << cgicc::td().set("class","ok") << (string)febInfo.getChamberLocationName() << cgicc::td()
	     << cgicc::td().set("class","ok") << (string)febInfo.getFebLocalEtaPartition() << cgicc::td()
	     << cgicc::td().set("class","ok") << febInfo.getCcuAddress() << cgicc::td()
	     << cgicc::td().set("class","ok") << febInfo.getChannel() << cgicc::td()
	     << cgicc::td().set("class","ok") << febInfo.getAddress() << cgicc::td();
	FebValues::Values& values = febValues.getValues();
	int i = 1;
	//	string name = febAccessInfo.getChamberLocationName();
	//	bool barrelOrEndcap = (name.find("W") == name.npos);
	//	int chips = (barrelOrEndcap?4:2);
	int chips = 2;
	std::string td_class = "ok";
	for (FebValues::Values::iterator iValue = values.begin(); iValue != values.end(); ++iValue)
	  {
	    if (i > chips)
	      {
		if ((int)(*iValue) > 32)
		  td_class="problem";
		else
		  td_class="ok";
	      }
	    *out << cgicc::td().set("class",td_class) << (*iValue) << cgicc::td();
	    i++;
	  }
	*out << cgicc::tr();
      }
      *out << cgicc::table() << std::endl;
    }
  this->PageFooter(in, out);
}

*/

/**************************************************
** ConnectivityTest                              **
**************************************************/
void XdaqRpcConnectivityTest::ConnectivityTest(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception)
{

  LOG4CPLUS_INFO(getApplicationLogger(),"ConnectivityTest.");

  int VTHlow, VTHhigh;
  this->ConnectivityTestFormData(in, VTHlow, VTHhigh);
  this->ConnectivityTestAction(in, out, VTHlow, VTHhigh);
  this->Default(in, out);
  //  this->ConnectivityTestResult(in, out);
}
void XdaqRpcConnectivityTest::ConnectivityTestGUI(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception)
{

  LOG4CPLUS_INFO(getApplicationLogger(),"ConnectivityTestGUI.");

  string actionConnectivityTest =
    toolbox::toString("/%s/ConnectivityTest",getApplicationDescriptor()->getURN().c_str());

  *out << cgicc::form().set("method","POST").set("action", actionConnectivityTest).set("enctype","multipart/form-data") << std::endl;
  *out << cgicc::table().set("width", "600").set("align","center").set("class","wborder")<< std::endl;
  *out << cgicc::tr()<< std::endl;
  *out << cgicc::th() << "Low threshold" << cgicc::th() << cgicc::th() << "High threshold" << cgicc::th() << std::endl;
  *out << cgicc::tr()<< std::endl;
 
  *out << cgicc::tr() << std::endl;
  *out << cgicc::td() << std::endl;
  *out << cgicc::select().set("name","VTHlow").set("id","VTHlow") << std::endl;
    for (int i=100;i>=30;i-=10)
      {
	if (i==40)
	  *out << "<option value=\"" << i << "\" checked=\"checked\">" << i << "</option>" << std::endl;
	else
	  *out << "<option value=\"" << i << "\">" << i << "</option>" << std::endl;
      }
  *out << cgicc::select() << std::endl;
  *out << cgicc::td() << std::endl;
  *out << cgicc::td() << std::endl;
  *out << cgicc::select().set("name","VTHhigh").set("id","VTHhigh") << std::endl;
    for (int i=400;i>=100;i-=50)
      {
	if (i==400)
	  *out << "<option value=\"" << i << "\" checked=\"checked\">" << i << "</option>" << std::endl;
	else
	  *out << "<option value=\"" << i << "\">" << i << "</option>" << std::endl;
      }
  *out << cgicc::select() << std::endl;
  *out << cgicc::td() << std::endl;
  *out << cgicc::tr() << std::endl;
  
  *out << cgicc::tr()<< std::endl;
  *out << cgicc::td().set("colspan", "2")<< std::endl;
  *out << cgicc::input().set("type","submit").set("align","center").set("name", "send").set("value", "start the connectivity test")<<std::endl;
  *out << cgicc::td()<< std::endl;
  *out << cgicc::tr()<< std::endl;

  *out << cgicc::table() << std::endl;
  *out << cgicc::form() << std::endl;
}
void XdaqRpcConnectivityTest::ConnectivityTestFormData(xgi::Input * in, int &VTHlow, int &VTHhigh) throw (xgi::exception::Exception)
{

  LOG4CPLUS_INFO(getApplicationLogger(),"ConnectivityTestFormData.");

  try{
    Cgicc formData(in);
    VTHlow  = formData.getElement("VHTlow")->getIntegerValue();
    VTHhigh = formData.getElement("VTHhigh")->getIntegerValue();
  }
  catch(xgi::exception::Exception& e){
    LOG4CPLUS_ERROR(getApplicationLogger(), string("xgi-error at SetFebValuesFormData. ") + e.what());
    //    XCEPT_RETHROW(xgi::exception::Exception, "xgi-error at SetFebValuesFormData.", e);
  }
}
void XdaqRpcConnectivityTest::ConnectivityTestAction(xgi::Input * in, xgi::Output * out, int VTHlow, int VTHhigh) throw (xoap::exception::Exception)
{

  LOG4CPLUS_INFO(getApplicationLogger(),"ConnectivityTestAction.");

  time_t now = time(NULL);
  struct tm nowstruct = (*localtime(&now));
  std::stringstream ss_outfile;
  ss_outfile <<"ConnectivityTest_" << nowstruct.tm_year << (nowstruct.tm_mon+1) << nowstruct.tm_mday << "_" << nowstruct.tm_hour << "_" << nowstruct.tm_min << "_" << nowstruct.tm_sec << ".log";
  std::ofstream conntestfile;
  conntestfile.open(ss_outfile.str().c_str(),ios::app);
  if (conntestfile.fail()) {
    //throw TException("Could not open the file '" +  sfile.str() + "' for writing");
    LOG4CPLUS_INFO(this->getApplicationLogger(), "Could not open the file '" + ss_outfile.str() + "' for appending.");
    return;
  }

  LOG4CPLUS_INFO(getApplicationLogger(),"Connectivity-test output in \'" << ss_outfile << "\' .");
  
  
  LOG4CPLUS_INFO(getApplicationLogger(),"Setting all thresholds to high threshold...");
  int arr_VTHhigh[] = {VTHhigh, VTHhigh, VTHhigh, VTHhigh};
  int arr_VMON[] = {XdaqRpcConnectivityTest::DEFAULT_VMON, XdaqRpcConnectivityTest::DEFAULT_VMON, XdaqRpcConnectivityTest::DEFAULT_VMON, XdaqRpcConnectivityTest::DEFAULT_VMON};
  try
    {
      instanceResponseMap lbbAppMapResponse;
      this->SetFebValuesAction(in, out, arr_VTHhigh, arr_VMON, lbbAppMapResponse);
    }
  catch (xoap::exception::Exception &e)
    {
      LOG4CPLUS_ERROR(getApplicationLogger(), string("xoap-error at ConnectivityTestAction calling SetFebValuesAction. ") + e.what());
    }
  LOG4CPLUS_INFO(getApplicationLogger(),"Done.");
  
  LOG4CPLUS_INFO(getApplicationLogger(),"Performing actual Connectivity Test...");
  
  for( FAIVV::iterator iFAIV = FAIVVector.begin();iFAIV != FAIVVector.end(); ++iFAIV)
    {
      FAIV  febAccessInfoVector = *iFAIV;
      for (FAIV::iterator iFAI = febAccessInfoVector.begin();iFAI != febAccessInfoVector.end(); ++iFAI)
	{
	  FebAccessInfo& febAccessInfo = iFAI->bag;
	  
	  string name = febAccessInfo.getChamberLocationName();
	  bool barrelOrEndcap;
	  XdaqDbServiceClient::BarrelOrEndcap boe;
	  int wheel, layer, sector;
	  string subsector;
	  getLocationFromName(name, barrelOrEndcap, boe, wheel, layer, sector, subsector);

	  int partition = XdaqRpcConnectivityTest::partitions[(int)barrelOrEndcap][(int)febAccessInfo.getFebAddress()];
	  int signalCablesPerFEB = (barrelOrEndcap?2:1);
	  for (int signalCable = 0; signalCable < signalCablesPerFEB ; signalCable++)
	    {
	      int arr_VTHlow[] = {VTHhigh, VTHhigh, VTHhigh, VTHhigh};
	      for (int i=0;i<signalCablesPerFEB;i++)
		arr_VTHlow[XdaqRpcConnectivityTest::CHIPS_PER_SIGNALCABLE*XdaqRpcConnectivityTest::feb_locations[(int)barrelOrEndcap][wheel][signalCable+partition*2] + i] = VTHlow;

	      rpct::XdaqLBoxAccessClient::MassiveWriteResponseBag* responseBag;
	      
	      instanceResponseMap lbbAppMapResponse;

	      responseBag = this->SetSingleFebValues(febAccessInfo, barrelOrEndcap, arr_VTHlow, arr_VMON);
	      conntestfile << (string)febAccessInfo.getFebLocalEtaPartition() << (signalCable+1) << " values: ";
	      //	      for (xdata::Float::iterator iValue = responseBag.bag.getFebValues().bag.getValues().begin(); iValue < responseBag.bag.getFebValues().bag.getValues().end(); iValue++)
	      //		conntestfile << *iValue << " " ;
	      conntestfile << std::endl;
	      delete responseBag;
	      ReadSingleChamberNoiseToFile(conntestfile, boe, wheel, layer, sector, subsector);

	      responseBag = this->SetSingleFebValues(febAccessInfo, barrelOrEndcap, arr_VTHhigh, arr_VMON);
	      conntestfile << (string)febAccessInfo.getFebLocalEtaPartition() << (signalCable+1) << " values: ";
	      //	      for (xdata::Float::iterator iValue = responseBag.bag.getFebValues().bag.getValues().begin(); iValue < responseBag.bag.getFebValues().bag.getValues().end(); iValue++)
	      //		conntestfile << *iValue << " " ;
	      conntestfile << std::endl;
	      delete responseBag;
	      ReadSingleChamberNoiseToFile(conntestfile, boe, wheel, layer, sector, subsector);
	    }
	}
    }
  conntestfile.close();
  LOG4CPLUS_INFO(getApplicationLogger(),"Done.");
}
rpct::XdaqLBoxAccessClient::MassiveWriteResponseBag* XdaqRpcConnectivityTest::SetSingleFebValues(FebAccessInfo febAccessInfo, bool barrelOrEndcap, int arr_VTH[], int arr_VMON[])
{
  try{
    instanceRequestMap  instanceForLBBox;
    int xdaqInstanceNumber = febAccessInfo.getXdaqAppInstance(); 
    MassiveWriteRequest& writeRequest = instanceForLBBox[xdaqInstanceNumber].bag;
    
    int chips = (barrelOrEndcap?4:2);

    
    if(instanceForLBBox[xdaqInstanceNumber].bag.getProperties().empty()){
      for (int i=0;i<chips;i++)
	{
	  writeRequest.getProperties().push_back(prop_vth[i]);
	  writeRequest.getProperties().push_back(prop_vmon[i]);
	}
    }
    xdata::Bag<FebValues> valuesBag;
    valuesBag.bag.getFeb().bag.setCcuAddress(febAccessInfo.getCcuAddress());
    valuesBag.bag.getFeb().bag.setChannel(febAccessInfo.getI2cChannel());
    valuesBag.bag.getFeb().bag.setAddress(febAccessInfo.getFebAddress());
    valuesBag.bag.getFeb().bag.setChamberLocationName(febAccessInfo.getChamberLocationName());
    valuesBag.bag.getFeb().bag.setFebLocalEtaPartition(febAccessInfo.getFebLocalEtaPartition());
    valuesBag.bag.getFeb().bag.setEndcap(barrelOrEndcap);

    for (int i=0;i<chips;i++)
      {
	valuesBag.bag.getValues().push_back(arr_VTH[i]);
	valuesBag.bag.getValues().push_back(arr_VMON[i]);
      }
    writeRequest.getFebValues().push_back(valuesBag);
    
    try{
      return lboxAccessClient.massiveWrite(instanceForLBBox[xdaqInstanceNumber], xdaqInstanceNumber);
    }
    catch (std::exception& e){
      LOG4CPLUS_ERROR(getApplicationLogger(), "std exception: " << e.what());
    }
    catch(...){
      LOG4CPLUS_ERROR(getApplicationLogger(), "other error");      
    }    
  }
  catch(...){
    LOG4CPLUS_ERROR(getApplicationLogger(), "other error 2");      
  }
  return NULL;
}

void XdaqRpcConnectivityTest::ReadSingleChamberNoiseToFile(std::ofstream &ofile, XdaqDbServiceClient::BarrelOrEndcap boe, int wheel, int layer, int sector, std::string subsector)
{
  try{
    XdaqDbServiceClient::ChamStripAccessInfoVector* chamStripAccessInfoVector = dbServiceClient.getChamStripByChamLoc(wheel, layer, sector, subsector, boe);
    if(chamStripAccessInfoVector->empty()){
      LOG4CPLUS_INFO(getApplicationLogger(),"No results were returned from the database. Perhaps this chamber does not have a link board assignment in the database.");
      return;
    }
    std::map<int,std::map<int,int> > febIds;
    std::map<int,int> febToI2CAddress;
    std::map<int,std::set<int> > chipIds;
    std::map<int,int> chipToinstance;
    std::map<int, std::string > boardToChamber;
    std::map<int, std::string > boardToPartition;
    LOG4CPLUS_INFO(getApplicationLogger(),"Size of stripAccess vector = "<<chamStripAccessInfoVector->size());
    
    for (XdaqDbServiceClient::ChamStripAccessInfoVector::iterator iCSAI = chamStripAccessInfoVector->begin();
	 iCSAI != chamStripAccessInfoVector->end(); ++iCSAI) {
      ChamStripAccessInfo& chamStripAccessInfo = iCSAI->bag;
      xdata::String chamberName = chamStripAccessInfo.getChamberLocationName();
      xdata::Integer boardId = chamStripAccessInfo.getBoardId();
      xdata::Integer xdaqAppInstance = chamStripAccessInfo.getXdaqAppInstance();
      xdata::Integer chipId = chamStripAccessInfo.getChipId();
      xdata::Integer febId = chamStripAccessInfo.getFebId();
      xdata::Integer febConnectorNum = chamStripAccessInfo.getFebConnectorNum();
      xdata::String febLocalEtaPartition = chamStripAccessInfo.getFebLocalEtaPartition();
      xdata::Integer febI2cAddress = chamStripAccessInfo.getFebI2cAddress();
      xdata::Integer cableChanNum = chamStripAccessInfo.getCableChanNum();
      xdata::Integer chamberStripNum = chamStripAccessInfo.getChamberStripNum();
      LOG4CPLUS_INFO(getApplicationLogger(), "Chamber Name: " << (string)chamberName << "  "
		     << "Board Id: " << (int)boardId << "  "
		     << "Instance: " << (int)xdaqAppInstance << "  "
		     << "Chip Id: " << (int)chipId << "  "
		     << "Feb Id: " << (int)febId << "  "
		     << "FebConnectorNum: " << (int)febConnectorNum << "  "
		     << "FebLocalEtaPartition: " << (string)febLocalEtaPartition << "  "
		     << "FebI2cAddress: " << (int)febI2cAddress << "  "
		     << "CableChanNum: " << (int)cableChanNum << "  "
		     << "ChamberStripNum: " << (int)chamberStripNum << endl);
      
      std::map<int,int> strips;
      if (febIds.find((int)febId) != febIds.end()){
	strips = febIds[ (int)febId];
      }else{
	febToI2CAddress[ (int) febId] = (int) febI2cAddress;
      }
      strips[ (int) chamberStripNum] = (int)(febConnectorNum-1)*16 + 
	(int) cableChanNum - 1;
      febIds[(int)febId]=strips;
      
      
      std::set<int> febs;
      if (chipIds.find((int)chipId)!= chipIds.end()){
	febs = chipIds[ (int)chipId];
      } else {
	chipToinstance[ (int) chipId ] = (int)xdaqAppInstance;
	boardToChamber [(int) chipId ] = (string) chamberName;
	boardToPartition [(int)chipId] = (string)febLocalEtaPartition;
      }
      
      
      febs.insert( (int) febId);
      chipIds[ (int) chipId] = febs;
      
      
    }
    LOG4CPLUS_INFO(getApplicationLogger(), 
		   " Number of FEBS "<<febIds.size()
		   <<" Number of CHIPS " <<chipIds.size()<<endl);
    
    
    
    std::map<int, std::set<int> >::iterator ich;
    for (ich=chipIds.begin(); ich!=chipIds.end(); ich++){
      int chip = ich->first;
      
      ofile <<"--> Chamber "<<boardToChamber[chip]<<" "<<boardToPartition[chip]<<endl;
      
      LOG4CPLUS_INFO(getApplicationLogger(), 
		     "chip="<<chip);
      
      int instance = chipToinstance[chip];
      ofile <<"Chip Id = " <<chip<<" instance="<<instance<<std::endl;
      double data[96];
      for (int i=0;i<96;i++)
	data[i]=0;
      this->linkBoardCounters(instance, chip, data);
      
      
      std::set<int> allfebs = ich->second;
      ofile <<"Number of FEBS for chip="<<chip<<" ="<<allfebs.size()<<std::endl;
      std::set<int>::iterator ifb;
      for(ifb=allfebs.begin(); ifb!=allfebs.end(); ifb++){
	
	LOG4CPLUS_INFO(getApplicationLogger(), " feb="<<*ifb<<endl);
	ofile <<"FEB Id = "<< *ifb <<" I2c Address ="<<febToI2CAddress[*ifb]<<endl;
	std::map<int,int> romap = febIds[*ifb];
	std::map<int,int>::iterator istr;
	ofile<<"->|";
	for (istr=romap.begin();istr!=romap.end(); istr++){
	  int rpcstrip  = istr->first;
	  int lbchannel = istr->second;
	  double noise  = data[lbchannel];
	  ofile << "strip "<<setw(2)<<rpcstrip<<" noise="<<noise<<"|";
	  LOG4CPLUS_INFO(getApplicationLogger()," strip "<<rpcstrip<<" noise="<<noise<<"|");
	}
	LOG4CPLUS_INFO(getApplicationLogger(), endl);
	ofile <<std::endl;
	
      }
    }
    
  }catch (xcept::Exception& e) {
    LOG4CPLUS_ERROR(this->getApplicationLogger(), e.what());
    XCEPT_RETHROW(xgi::exception::Exception, e.what(), e);
  }
  catch (std::exception& e) {
    LOG4CPLUS_ERROR(this->getApplicationLogger(), e.what());
    XCEPT_RAISE(xgi::exception::Exception, e.what());
  }
}



void XdaqRpcConnectivityTest::linkBoardCounters(int instance, int chipId, double rate[96], int seconds) 
{
  try{
    
    const int binCount=96;
    const xdata::Binary counterLimit((unsigned long)(SECOND_IN_BX * seconds));
    
    DiagIdBag diagCtrlId;
    diagCtrlId.bag.init(chipId, "STATISTICS_DIAG_CTRL");
    XdaqDiagAccessClient::DiagIdVector diagCtrlIds;
    diagCtrlIds.push_back(diagCtrlId);
    
    DiagId rateId;
    rateId.init(chipId, "RATE");
    HistoMgrInfoBag histoInfoBag;
    histoInfoBag.bag.init(rateId, binCount, rateId);
    XdaqDiagAccessClient::HistoMgrInfoVector histos;
    histos.push_back(histoInfoBag);
    
    diagAccessClient.resetDiagCtrl(diagCtrlIds, "XdaqLBoxAccess", instance);
    diagAccessClient.resetHistoMgr(histos, "XdaqLBoxAccess", instance);
    
    diagAccessClient.configureDiagCtrl(diagCtrlIds, counterLimit, IDiagCtrl::ttManual, "XdaqLBoxAccess", instance);
    diagAccessClient.startDiagCtrl(diagCtrlIds, "XdaqLBoxAccess", instance);
    while (!diagAccessClient.checkCountingEnded(diagCtrlIds, "XdaqLBoxAccess", instance)) {
      usleep(100000); // wait for it to end
    }
    diagAccessClient.stopDiagCtrl(diagCtrlIds, "XdaqLBoxAccess", instance);
    xdata::Vector<xdata::Binary>* data;
    
    for (XdaqDiagAccessClient::HistoMgrInfoVector::iterator iHisto = histos.begin(); iHisto != histos.end(); ++iHisto) {
      data = diagAccessClient.readDataHistoMgr(iHisto->bag.getIdBag(), "XdaqLBoxAccess", instance);
      for (int bin = 0, k=0; bin < iHisto->bag.getBinCount(); bin++, k++) {
	rate[k] = ((unsigned long)data->at(bin));
      }
      delete data;
    }
  }catch (xcept::Exception& e) {
    LOG4CPLUS_ERROR(this->getApplicationLogger(), e.what());
    XCEPT_RETHROW(xgi::exception::Exception, e.what(), e);
  }
  catch (std::exception& e) {
    LOG4CPLUS_ERROR(this->getApplicationLogger(), e.what());
    XCEPT_RAISE(xgi::exception::Exception, e.what());
  }
}

/*
void XdaqRpcConnectivityTest::ConnectivityTestResult(xgi::Input * in, xgi::Output * out, instanceReadResponseMap lbbAppMapResponse) throw (xgi::exception::Exception)
{

  LOG4CPLUS_INFO(getApplicationLogger(),"ConnectivityTestResult.");

  subTitle = "Result of the Connectivity test";
  this->PageHeader(in, out, mainTitle, subTitle);
  *out << cgicc::table().set("width", "600").set("align","left").set("class","wborder")<< std::endl;
  for(instanceResponseMap::iterator iMap = lbbAppMapResponse.begin(); iMap != lbbAppMapResponse.end(); ++iMap)
    {
      MassiveReadResponse& readResponse = lbbAppMapResponse[iMap->first]->bag;
      FebProperties& props = readResponse.getProperties();
      *out << cgicc::tr();         
      *out << cgicc::th() << "chamber" << cgicc::th() << std::endl;
      *out << cgicc::th() << "Local Partition" << cgicc::th() << std::endl;
      *out << cgicc::th() << "CCU Address" << cgicc::th() << std::endl;
      *out << cgicc::th() << "CB Channel" << cgicc::th() << std::endl;
      *out << cgicc::th() << "I2C Local Number" << cgicc::th() << std::endl;
      for (FebProperties::iterator iProp = props.begin(); iProp != props.end(); ++iProp)
	*out << cgicc::th() << (string)(*iProp) << cgicc::th() << std::endl;
      *out << cgicc::tr();
      
      FebValuesVector& valuesVector = readResponse.getFebValues();
      for (FebValuesVector::iterator iVal = valuesVector.begin(); iVal != valuesVector.end(); ++iVal) {
	FebValues& febValues = iVal->bag;
	FebInfo& febInfo = febValues.getFeb().bag;
	*out << cgicc::tr()
	     << cgicc::td().set("class","ok") << (string)febInfo.getChamberLocationName() << cgicc::td()
	     << cgicc::td().set("class","ok") << (string)febInfo.getFebLocalEtaPartition() << cgicc::td()
	     << cgicc::td().set("class","ok") << febInfo.getCcuAddress() << cgicc::td()
	     << cgicc::td().set("class","ok") << febInfo.getChannel() << cgicc::td()
	     << cgicc::td().set("class","ok") << febInfo.getAddress() << cgicc::td();
	FebValues::Values& values = febValues.getValues();
	int i = 1;
	//	string name = febAccessInfo.getChamberLocationName();
	//	bool barrelOrEndcap = (name.find("W") == name.npos);
	//	int chips = (barrelOrEndcap?4:2);
	int chips = 2;
	std::string td_class = "ok";
	for (FebValues::Values::iterator iValue = values.begin(); iValue != values.end(); ++iValue)
	  {
	    if (i > chips)
	      {
		if ((int)(*iValue) > 32)
		  td_class="problem";
		else
		  td_class="ok";
	      }
	    *out << cgicc::td().set("class",td_class) << (*iValue) << cgicc::td();
	    i++;
	  }
	*out << cgicc::tr();
      }
      *out << cgicc::table() << std::endl;
    }
  this->PageFooter(in, out);
}
*/
/**************************************************
** Reset                                         **
**************************************************/

void XdaqRpcConnectivityTest::Reset(xgi::Input * in, xgi::Output * out) throw (xgi::exception::Exception)
{
      
  LOG4CPLUS_INFO(getApplicationLogger(),"Reset");
  
  try
    {
      mainTitle = "RPC Connectivity test";
      subTitle = "configure";
      selectedChambers = "";
      FAIVVector.clear();
      this->Default(in,out);
    }
  catch (xdaq::exception::Exception& e) {
    LOG4CPLUS_ERROR(getApplicationLogger(), "Error");
    //   XCEPT_RETHROW(xgi::exception::Exception, "Cannot send message", e);
  }
}



void XdaqRpcConnectivityTest::getLocationFromName(std::string name, bool &barrelOrEndcap,  XdaqDbServiceClient::BarrelOrEndcap boe, int &wheel, int &layer, int &sector, std::string &subsector)
{
  barrelOrEndcap = (name.find("W") == name.npos);
  boe = boe_arr[(int)(barrelOrEndcap)];
  
  int string_pos[6];
  if (barrelOrEndcap) // endcap
    { // RE_wheel_/_layer_/_sector
      string_pos[0] = name.find("RE")+2;
      string_pos[1] = name.find("/");
      string_pos[2] = string_pos[1]+1;
      string_pos[3] = name.rfind("/");
      string_pos[4] = string_pos[3]+1;
      string_pos[5] = name.length();
    }
  else // barrel
    { // W_wheel_/RB_layerstring_/_sector_subsectorstring
      string_pos[0] = name.find("W")+1;
      string_pos[1] = name.find("/RB");
      string_pos[2] = string_pos[1]+3;
      string_pos[3] = name.rfind("/");
      string_pos[4] = string_pos[3]+1;
      std::string temp_name = name.substr(string_pos[3],name.npos);
      int plus = (int)temp_name.find("+");
      int min = (int)temp_name.find("-");
      int pos;
      if (plus == min)
	pos = name.length();
      else if (plus == (int)name.npos)
	pos = min;
      else
	pos = plus;
      string_pos[5] = pos + string_pos[3];
    }
  wheel  = atoi((name.substr(string_pos[0], string_pos[1]-string_pos[0])).c_str());
  layer  = atoi((name.substr(string_pos[2], string_pos[3]-string_pos[2])).c_str());
  sector = atoi((name.substr(string_pos[4], string_pos[5]-string_pos[4])).c_str());
  subsector = name.substr(string_pos[5], name.npos);
  stringstream fromname;
  fromname << "getLocationFromName: " << name << " -> " << "wheel " << wheel << ", layer " << layer << ", sector " << sector << ", subsector " << subsector;
  LOG4CPLUS_INFO(getApplicationLogger(),fromname.str());  
}
