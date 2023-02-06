#include "TH1F.h"
#include "TF1.h"
#include "TRandom.h"
#include <iostream>
#include "TCanvas.h"

//ES_1
void macro1(int nGen = 10E6){
TH1F *hgen = new TH1F("hgen","generated variables",1000,0.,5.);
hgen->Sumw2();
TH1F *hacc = new TH1F("hacc","accepted variables",1000,0.,5.);
hacc->Sumw2();

TF1 *eff = new TF1("eff","x/5",0.,5.);
gRandom->SetSeed();
for(int i=0;i<nGen;i++){
    double y=gRandom->Rndm();
    double x=gRandom->Exp(1);
    if(y<eff->Eval(x)) hacc->Fill(x);
    hgen->Fill(x);
}
TH1F *heff = new TH1F(*hgen);
heff->Divide(hacc,hgen,1,1,"B");
heff->SetName("heff");
heff->SetTitle("efficency");
heff->Draw("HISTO,E");

}

//ES_2
void macro2(int nGen1=10E6,int nGen2=10E4){
TH1F *h1 = new TH1F("h1","histo 1",500,0,5);
h1->Sumw2();
TH1F *h2 = new TH1F("h2","histo 2",500,0,5);
h2->Sumw2();
gRandom->SetSeed();
for(int i =0;i<nGen1;i++){
double x = gRandom->Gaus(2.5,0.25);
h1->Fill(x);
}
for (int i = 0; i < nGen2; i++)
{
double x = gRandom->Uniform(0,5);
h2->Fill(x);
}
TH1F *hsum = new TH1F(*h1);
hsum->Add(h1,h2);
hsum->SetName("hsum");
hsum->SetTitle("sum of h1 and h2");

TF1 *f = new TF1("f","[0]*exp(-0.5*(x-[1])/[2] *(x-[1])/[2]) + [3]",0,5);
f->SetParameters(5,5,5,5);
hsum->Fit(f);
TF1 *fit = hsum->GetFunction("f");

std::cout<<"Reduct CHISQUARE : "<<fit->GetChisquare()/fit->GetNDF()<<'\n';
TString par = "parameter";
for (int i = 0; i < 4; i++)
{
std::cout<<par+i<<" : "<<fit->GetParameter(i)<<"+/-"<<fit->GetParError(i)<<'\n';
}
}

//ES_3
void macro3(int nGen=10E7){
TH1F *h = new TH1F("h","histo",100,0,10);
TF1 *f = new TF1("f","sqrt(x)+x*x",0,10);
h->FillRandom("f",nGen);
TCanvas *c = new TCanvas("c","myCanavas");
h->Draw("HISTO");
}




