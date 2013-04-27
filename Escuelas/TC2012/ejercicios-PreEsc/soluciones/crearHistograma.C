{

  // Crear un simple histograma de una distribucion gaussiana

  //1. definir la funcion que nos defina la distribucion
  TF1* myFunc1 = new TF1("func1","gaus");

  //fijamos los parametros de esta funcion 1: media 2: sigma
  myFunc1->SetParameter(0, 1.0); //es la constante al frente de la funcion
  myFunc1->SetParameter(1, 6.0); 
  myFunc1->SetParameter(2, 2.0); 
  
  //2. definir un histograma 
  TH1F* myHist1 = new TH1F("hist1","Function to be fit",100, 0.0,15.0);

  //3. Llenar el histograma con 10000 numeros aleatorios que siguen la distribucion func1
  myHist1->FillRandom("func1",10000);

  //4. Algunas opciones graficas de presentacion del histograma
  myHist1->GetXaxis()->SetTitle("Gaussian"); //titulo en X
  myHist1->SetLineColor(9); //color de la linea
                                                      
  //5. Dibujar el histograma "e1" es la opcion para que se haga con barras de error
  myHist1->Draw("e1");
 

}
