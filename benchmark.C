#include "TStyle.h"
#include "TH1F.h"
#include "TRandom.h"
#include "TBenchmark.h"

void benchmark(Int_t nGen){
  gStyle->SetOptStat(111111);
  TString histName="h";
  TH1F *h[2];
  for(Int_t i=0;i<2;i++){

    h[i] =new TH1F(histName+i,"test histogram",1000,-5,5.);
//cosmetics
    h[i]->SetMarkerStyle(20);
    h[i]->SetMarkerSize(0.5);
    h[i]->SetLineColor(1);
    h[i]->GetYaxis()->SetTitleOffset(1.5);
    h[i]->GetXaxis()->SetTitle("x");
    h[i]->GetYaxis()->SetTitle("Entries");
  }

  h[0]->SetFillColor(4);
  h[1]->SetFillColor(2);
  TBenchmark *b = new TBenchmark();
//filling the histo
  b->Start("With TH1::FillRandom");

//with numerical inverse transform
  h[0]->FillRandom("gaus",nGen);
//stop and show benchmark
  b->Show("With TH1::FillRandom");

//with inverse transform
  Double_t x=0;
  b->Start("Direct TRandom::Gaus invocation");
  for (Int_t i =0;i<nGen;i++){
    x=gRandom->Gaus(0,1);
    h[1]->Fill(x);
  }
//Stop and show benchmark
  b->Show("Direct TRandom::Gaus invocation");

}


void bench_es(int nGen=10E5){

  TBenchmark *b = new TBenchmark();
  TH1F *h[2];
  TString histname="h";
  for(int i=0;i<2;i++){
    h[i]= new TH1F(histname+i,"test histogra",1000,0,10);
    h[i]->GetXaxis()->SetTitle("x");
    h[i]->GetYaxis()->SetTitle("Entries");
  }
 b->Start("Test with gRandom");

 for(int j=0;j<nGen;j++){
  double x = gRandom->Gaus(0,1);
  h[0]->Fill(x);
 }

 b->Show("Test with gRandom");

 b->Start("Test with FillRandom");
 h[1]->FillRandom("gaus",nGen);
 b->Show("Test with FillRandom");
}