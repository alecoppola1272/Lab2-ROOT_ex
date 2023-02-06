//Esame da Lezione IX
#include<iostream>
#include"TRandom.h"
#include"TH1F.h"
#include"TF1.h"
#include"TCanvas.h"
#include"TStyle.h"

//Es 1
void macro1(int nGen = 10E5){
gRandom->SetSeed();
gStyle->SetOptStat(2210);
gStyle->SetOptFit(1111);
TH1F *h1 = new TH1F ("h1","histo1",100,0,10);
TH1F *h2 = new TH1F ("h2","histo2",100,0,10);
h1->Sumw2();
h2->Sumw2();

TF1 *eff = new TF1("eff","x/10",.0,10);

float x,y;

for(int i = 0;i<nGen;i++){
    x=gRandom->Gaus(5.,1.);
    h1->Fill(x);
    y=gRandom->Rndm();
    if(y<eff->Eval(x)) h2->Fill(x);
}

TH1F *hEff = new TH1F(*h1);
hEff->Divide(h2,h1,1,1,"B");
hEff->SetTitle("histo3");
hEff->SetName("h3");

TCanvas *c = new TCanvas("canvas","Histograms");
c->Divide(1,3);
c->cd(1);
h1->Draw("HISTO");
c->cd(2);
h2->Draw("HISTO");
c->cd(3);
hEff->Draw("HISTO");

}
//Es 1 variante
void macro1_2(int nGen = 10E5){
gRandom->SetSeed();
gStyle->SetOptStat(2210);
gStyle->SetOptFit(1111);
TH1F *h1 = new TH1F ("h1","histo1",100,0,10);
TH1F *h2 = new TH1F ("h2","histo2",100,0,10);
h1->Sumw2();
h2->Sumw2();

TF1 *eff = new TF1("eff","(x>= 0 && x<=3)*0.3+(x>3)*0.7",.0,10);

float x,y;

for(int i = 0;i<nGen;i++){
    x=gRandom->Gaus(5.,1.);
    h1->Fill(x);
    y=gRandom->Rndm();
    if(y<eff->Eval(x)) h2->Fill(x);
}

TH1F *hEff = new TH1F(*h1);
hEff->Divide(h2,h1,1,1,"B");
hEff->SetTitle("histo3");
hEff->SetName("h3");

TCanvas *c = new TCanvas("canvas","Histograms");
c->Divide(1,3);
c->cd(1);
h1->Draw("HISTO");
c->cd(2);
h2->Draw("HISTO");
c->cd(3);
hEff->Draw("HISTO");

}

//Es 2
void macro2(int nGen1=10E6, int nGen2=10E5){
gRandom->SetSeed();
TH1F *hgaus = new TH1F("hgaus","gauss distribution",500,0,5);
TH1F *hexp = new TH1F("hexp","exponential distribution",500,0,5);
hgaus->Sumw2();
hexp->Sumw2();

for(int i = 0;i<nGen1;i++){
    double x=gRandom->Gaus(2.5,0.25);
    hgaus->Fill(x);
}
for(int i = 0;i<nGen2;i++){
    double x=gRandom->Exp(1);
    hexp->Fill(x);
}
TH1F *hsum =new TH1F(*hgaus);
hsum->Add(hgaus,hexp);
hsum->SetTitle("exponential and gaussian sum");
hsum->SetName("hsum");
TF1 *f =  new TF1 ("f","[0]*exp(-0.5*(x-[1])/[2] *(x-[1])/[2]) + [3]*exp(-x/[4])",0.,5.);
f->SetParameters(10,10,10,10,10);
hsum->Fit(f);
TF1 *fit = hsum->GetFunction("f");

TString par = "Parameter";
for(int i = 0; i<5;i++){
std::cout<<par+i<<" : "<<fit->GetParameter(i)<<"+/-"<<fit->GetParError(i)<<'\n';
}
std::cout<<"Reduct CHI SQUARE "<<fit->GetChisquare()/fit->GetNDF()<<'\n';

}

//Es 3
void macro3(int nGen=10E6){
    gRandom->SetSeed();
    TH1F *h = new TH1F("h","histo",4,0,4);
    for(int i=0;i<nGen;i++){
    double x = gRandom->Rndm();
    if(x<0.6) h->Fill(0);
    else if(x<0.9) h->Fill(1);
    else if(x<0.99) h->Fill(2);
    else h->Fill(3);
    }
    TString bin = "Bin Content ";

    for (int i = 1; i <=4; i++)
    {
    std::cout<<bin+i<<" : "<<h->GetBinContent(i)<<"+/-"<<h->GetBinError(i)<<'\n';
    }
    h->Draw("HISTO");
}

//Es 3.1

void macro3_2(int nGen=10E5){
//gRandom->SetSeed();
TH1F *h = new TH1F("h","histo",100,0,10);
TF1 *f = new TF1("f","x",0,10);
h->FillRandom("f",nGen);
h->GetXaxis()->SetTitle("X axis");
h->GetYaxis()->SetTitle("Y axis");
h->SetLineColor(kBlue);
h->Draw("HISTO");

}
