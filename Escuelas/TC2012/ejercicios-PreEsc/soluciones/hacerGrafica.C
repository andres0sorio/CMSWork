//este es un macro de ROOT. 
// Su codigo debe ir encapsulado entre los corchetes { ...... }
// No olvidar que estamos en C++: 
//   - al final de cada linea insertar punto-y-coma
//   - todo comentario empieza con un doble slash //

{
  
  //definamos primero las variables que usaremos
  int i = 0;
  float x = 0.0;
  float dx = 0.01;
  
  // Crear un objeto de tipo TGraph
 
  TGraphPolar mygraph;  
  
  // hacemos el loop aqui adicionando en cada iteracion un punto de la funcion
  // en la grafica

  while ( x < 2.0*TMath::Pi() ) {
    // esta es nuestra funcion y = f(x)
    
    float fx = cos(x);
    mygraph.SetPoint(i,x,fx);
    i=i+1; 
    x=x+dx; 
  
  } 
  
  // Dibujar nuestra grafica (la opcion instruye a ROOT lo siguiente
  // A: dibujar ejes
  // C: unir los puntos con una linea continua
  // P: dibujar los puntos
  
  mygraph.SetLineColor(2);
  mygraph.Draw("ACP");
  
}
