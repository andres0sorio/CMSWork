{

  //Para la lectura del archivo en formato ascii, usaremos la clase de C++ ifstream

  ifstream hepdata("missingEt-Figure1.txt");

  //Creamos el Objeto para hacer la grafica
 
  //Si queremos los errores asimetricos, debemos definir un objeto de tipo
  TGraphAsymmErrors missingEt_Err;
   
  //Leamos primero la linea que componen el encabezado
  
  char comment[256];
  hepdata.getline(comment,256); //leemos toda la 1era linea

  //definamos las variables que van a guardar los valores asignados a cada columna
  // x, xlow, xhigh, y, dy+, dy-

  float x;
  float xlow;
  float xhigh;
  
  float y;
  float dxp; //dx+
  float dxm; //dx-
  float dyp; //dy+
  float dym; //dy-

  //No nos ocuparemos por el momento de las siguientes variables, pero debemos declararlas
  
  float yMC; // Datos de simulacion
  float dyMCp;
  float dyMCm;
  float dyErrp;
  float dyErrm;
  
  //////////////////////////////
  
  int k = 0;
  
  dxp = 0.0;
  dxm = 0.0;
  
  //Demos inicio al loop sobre el que se hara la lectura de los datos
  // (existen muchas formas de hacerlo, esta es tan solo una de ellas)
  
  while( 1 ) 
  {
    
    if ( hepdata.eof() ) break;

    //Aqui see leen los datos (11 columnas en total)
    hepdata >> x >> xlow >> xhigh >> y >> dyp >> dym >> yMC >> dyMCp >> dyMCm >> dyErrp >> dyErrm;

    missingEt_Err.SetPoint(k, x, y);
    missingEt_Err.SetPointError(k, dxp, dxm, fabs(dym), dyp );
    
    k = k + 1;
    
  }
  missingEt_Err.SetMaximum(10000); //Fijamos un maximo en Y
  missingEt_Err.SetMinimum(0.01); //Fijamos el minimo en Y
  missingEt_Err.SetMarkerStyle(20); //Queremos que los datos tengan un punto

  //Finalmente graficamos

  missingEt_Err.Draw("AP");

  hepdata.close();
  
}
