{
  
 TGraphFromXML graphinfo;
 
 graphinfo.ParseFile("../bin/graph_config.xml");
 graphinfo.SetRange(10.0, 28.0, -13.0, -9.0);
 graphinfo.MakePlots( );
 
  
}
