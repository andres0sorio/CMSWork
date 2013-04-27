{
  
 TGraphFromXML graphinfo;
 
 graphinfo.ParseFile("../bin/egret-all.xml");
 graphinfo.SetRange(1.0E-11, 1.0E25, 1E-14, 1E2);
 graphinfo.MakePlots( );
 
  
}
