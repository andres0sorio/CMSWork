#include "XdaqRbcControlSync.h"

XDAQ_INSTANTIATOR_IMPL(XdaqRbcControlSync)

XdaqRbcControlSync::XdaqRbcControlSync(xdaq::ApplicationStub * s) throw (xdaq::exception::Exception): xdaq::Application(s), dbServiceClient(this), lboxAccessClient(this)
{

  rbcs* myrbcs=dbServiceClient.getAllRbcsInfo();
  
  for (rbcs::iterator irbc=myrbcs->begin(); irbc!=myrbcs->end();irbc++){
    //cout << (string)(irbc->bag.getLinkBoxName())<<"\n";
    rbcInstances[(string)(irbc->bag.getLinkBoxName())]=irbc->bag.getXdaqAppInstance();
  }
  
  for(int i=0; i<numReg;i++) {
    RegisterAddressFromName[RegisterName[i]] = RegisterAddress[i];
  }
  
  RegisterAddressFromName["Mask0"] =10; 
  RegisterAddressFromName["Mask1"] =11;
  RegisterAddressFromName["Mask2"] =12;
  RegisterAddressFromName["Mask3"] =13;
  
  RegisterAddressFromName["Force0"]=20;
  RegisterAddressFromName["Force1"]=21;
  RegisterAddressFromName["Force2"]=22;
  RegisterAddressFromName["Force3"]=23;
  
  xgi::bind(this,&XdaqRbcControlSync::Default, "Default");
  
  xgi::bind(this,&XdaqRbcControlSync::liteBlue, "liteBlue");
  xgi::bind(this,&XdaqRbcControlSync::menuBlue, "menuBlue");
  xgi::bind(this,&XdaqRbcControlSync::redBul  , "redBul");
  
  //for(int i=0; i<numReg; i++){cout << i<<RegisterName[i]<<"----->" <<RegisterAddressFromName[RegisterName[i]]<<endl;}
  
}


void XdaqRbcControlSync::Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception)
{
  
  if ( url[0]=="/" ) 
    for (int i=0;i<numUrl;i++) { 
      url[i] += getApplicationDescriptor()->getURN();
      url[i] += ModulesName[i];
    }
  
  *out<<"<html>"<<endl;
  *out<<head(title("RBC Send syncronization signal: XdaqRbcControlSync"))<<endl;

  


  
  *out<<frameset().set("cols","16%,42%,42%")<<endl; 
  *out<<frame().set("src",url[0]).set("name","left")<<endl;
  *out<<frame().set("src",url[1]).set("name","center")<<endl;
  *out<<frame().set("src",url[2]).set("name","right")<<endl;
  *out<<frameset()<<endl; 
  
  *out<<"</html>"<<endl;
  
}



int XdaqRbcControlSync::ReadRegister(string Register , string wheel, string sector)
{
  
  cout <<"==============================READING================================"<<endl;
  
  cout <<"Register......................"<< Register << endl;
  cout <<"Wheel........................."<< wheel    << endl;
  cout <<"Sector........................"<< sector   << endl;
  
  string linkBoxName="LBB_RB" + wheel + "_S" + sector;
  
  cout <<"Instance Number..............."<<rbcInstances[linkBoxName]<<endl;
  
  int IntRegister;
  
  if( Register=="Temperature" ) {
    
    int FalseTemp = lboxAccessClient.readRbcTemperature(linkBoxName,rbcInstances[linkBoxName]);
    
    cout << "Operation.....................readRbcTemperature(\""<<linkBoxName<<"\","<<rbcInstances[linkBoxName]<<")"<<endl;
    cout << "Temperature read..............." << FalseTemp << endl;
    
    bool FalseTempBool16[16];for(int i=0;i<16;i++) {FalseTempBool16[i]=BoolFromInt(FalseTemp,i);}
    
    bool FalseTempBool10[10];for(int i=0;i<10;i++) {FalseTempBool10[i]=FalseTempBool16[i+6];}
    
    cout << "Initial  16 Bit Register......{"; 
    for(int i=0;i<16;i++) {cout << FalseTempBool16[i]; if(i!=15)cout << ",";} 
    cout << "}"<<endl; 
    
    cout << "Obtained 10 Bit Register..................{"; 
    
    for(int i=0;i<10;i++) { 
      cout << FalseTempBool10[i]; 
      if(i!=9)cout << ",";} 
    cout << "}"<<endl;
    
    IntRegister = (FalseTempBool10[0]+
		   FalseTempBool10[1]*2+
		   FalseTempBool10[2]*4+
		   FalseTempBool10[3]*8+
		   FalseTempBool10[4]*16+
		   FalseTempBool10[5]*32+
		   FalseTempBool10[6]*64+
		   FalseTempBool10[7]*128+
		   FalseTempBool10[8]*256+
		   FalseTempBool10[9]*512);
    
    cout << "Temperature x 4..............."<< IntRegister << endl;
    
    float Temperature=IntRegister/4;
    
    cout << "Temperature..................."<< Temperature << endl;   
  
  }
  
  else {
  
    cout << "Register Address.............."<< RegisterAddressFromName[Register] << endl;
    
    cout << "Operation.....................readRbcRegister(\""<<linkBoxName<<"\","<<RegisterAddressFromName[Register]<<","<<rbcInstances[linkBoxName]<<")"<<endl;
    
    //... lbbox read register
    
    IntRegister = lboxAccessClient.readRbcRegister(linkBoxName,RegisterAddressFromName[Register],rbcInstances[linkBoxName]);
    
    cout << "Integer Register Read........." << dec << IntRegister << endl;     
    cout << "Hexadecimal Register Read....." << hex << IntRegister << dec<<endl;
    cout << "Register Byte Read............{";
    
    bool BoolResult[8]; 
    for(int i=0;i<8;i++) {
      BoolResult[i]=BoolFromInt(IntRegister,i);
      cout << BoolResult[i]; 
      if(i!=7)cout << ",";} cout << "}"<<endl;
    
  }   
  
  return IntRegister;

}


void XdaqRbcControlSync::WriteRegister(string Register,string wheel, string sector, bool RegisterBool[8])
{
  
  string linkBoxName="LBB_RB" + wheel + "_S" + sector;         
  int address=RegisterAddressFromName[Register];
  int RegisterInt=IntFromBool(RegisterBool);
  int instanceNumber=rbcInstances[linkBoxName];
  
  cout << "==============================WRITING================================"<<endl;
  cout << "Register......................"<<Register<<endl;
  cout << "Wheel........................."<<wheel<<endl;
  cout << "Sector........................"<<sector<<endl;
  cout << "Instance Number..............."<<rbcInstances[linkBoxName]<<endl;
  cout << "Register Address.............."<<RegisterAddressFromName[Register]<<endl;
  cout << "Integer Register Written......"<<RegisterInt<<endl;
  cout << "Operation.....................writeRbcRegister(\""<<linkBoxName<<"\","<<address<<","<<RegisterInt<<","<<instanceNumber<<")"<<endl;  
  cout << "Hexadecimal Register Written.."<<hex<<RegisterInt<<dec<<endl; 
  cout << "Byte Written..................{";
  
  for(int i=0;i<8;i++){cout << RegisterBool[i]; if(i!=7)cout << ",";} cout << "}"<<endl;            
  
  //....send write message to lbbox
  lboxAccessClient.writeRbcRegister(linkBoxName,address,RegisterInt,instanceNumber);
  
}

int XdaqRbcControlSync::IntFromBool(bool Register[8])
{

  return ( Register[0]+
	   Register[1]*2+
	   Register[2]*4+
	   Register[3]*8+
	   Register[4]*16+
	   Register[5]*32+
	   Register[6]*64+
	   Register[7]*128 ); 
}

bool XdaqRbcControlSync::BoolFromInt(int integer, int i)
{
  
  for(int j=0; j<i ;j++){ integer = integer/2; }
  return integer%2;
  
}


void XdaqRbcControlSync::menuBlue(xgi::Input * in, xgi::Output * out )throw (xgi::exception::Exception)
{ 
  ifstream infile("/nfshome0/tbpro/rpct/xdaqRbcControlSync/images/menuBlue.gif"); 
  *out<<infile.rdbuf();
}

void XdaqRbcControlSync::redBul(xgi::Input * in, xgi::Output * out )throw (xgi::exception::Exception)
{ 
  ifstream infile("/nfshome0/tbpro/rpct/xdaqRbcControlSync/images/redBul.gif"); 
  *out<<infile.rdbuf();
}

void XdaqRbcControlSync::liteBlue(xgi::Input * in, xgi::Output * out )throw (xgi::exception::Exception)
{ 
  ifstream infile("/nfshome0/tbpro/rpct/xdaqRbcControlSync/images/liteBlue.gif"); 
  *out<<infile.rdbuf();
}

