{

  // Para la lectura del archivo en formato ascii, usaremos la clase de C++ ifstream

  ifstream hepdata( XXXXXXXXXX ); ///colocar aqui entre comillas el nombre de archivo de entrada

  // Los datos originales vienen con Errores asimetricos.
  // Si queremos graficarlos, debemos usar la clase TGraphAsymmErrors

  //Si queremos los errores asimetricos, debemos definir un objeto de tipo
  TGraphAsymmErrors missingEt_Err;
  
  // definamos las 11 variables que van a guardar los valores asignados a cada columna
  // x, xlow, xhigh, y, dyp, dym, ...

  // * adicionar aqui las 11 variables (estan son de tipo float)
  
  float .... ;
  float .... ;
  
  // * adicionar aqui un contador entero que empieze en 0
  
  int ....;
  
    
  //Demos inicio al loop sobre el que se hara la lectura de los datos
  // (existen muchas formas de hacerlo, esta es tan solo una de ellas)
  
  while( 1 ) 
  {
    
    // * necesitamos aqui una condicion para detener el ciclo
    
    // * Leer aqui los datos haciendo uso del operador ">>" - cada variable debe ir en el orden en
    //   en el que esta en los datos
    
    hepdata >> x >> .............. ;

    // * adicionar el punto (x,y) i-esimo
    //missingEt_Err.SetPoint(i,x,y);
    
    // * adicionar los errores correspondientes dx-, dx+, dy-, dy+
    // missingEt_Err.SetPointError(i, xMinus, xPlus, yMinus, yPlus);

    //: nota ROOT requiere de estos errores en valores absolutos - usar funcion fabs

    // * incrementar el contador
    
  }
  
  //podemos cambiar el estilo del marcador para cada punto en el grafica
  missingEt_Err.SetMarkerStyle(20);

  // * dibujar la grafica
  // missingEt_Err.Draw("ACP");
  
  //cerramos aqui el archivo de datos de entrada
  hepdata.close();
  
}

