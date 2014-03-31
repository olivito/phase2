#include <iostream>
#include <utility>
#include <vector>

#include "TROOT.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TSystem.h"
#include "TApplication.h"
#include "TString.h"
#include "TH2.h"
#include "THStack.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TPaveText.h"
#include "TClonesArray.h"
#include "TLorentzVector.h"

using namespace std;

//---------------------------------------------------------------------
// This is a simple macro that chains together the ST*-binned
// Delphes samples, checks the normalization of each one, and plots
// the ST distribution, which should be smooth if the correct weights
// have been used.
//---------------------------------------------------------------------

void sanityChecker(){

  int rebin = 10;
  //  char* version = "V00-00-02";
  char* version = "temp";

  //-------------------------------
  // choose config/PU scenario
  //-------------------------------

  char* phase = (char*) "PhaseI";

  char* config = (char*) "Configuration0";

  char* PU = (char*) "NoPileUp";
  //char* PU = (char*) "40PileUp";
  //char* PU = (char*) "140PileUp";

  //-------------------------------
  // diboson filenames and labels
  //-------------------------------

  const unsigned int n = 5;

  char* names[n] = {Form("BB-4p-0-300-v1510_14TEV_%s_%s_%s"       , phase , config , PU ) ,
  		    Form("BB-4p-300-700-v1510_14TEV_%s_%s_%s"     , phase , config , PU ) ,
  		    Form("BB-4p-700-1300-v1510_14TEV_%s_%s_%s"    , phase , config , PU ) ,
  		    Form("BB-4p-1300-2100-v1510_14TEV_%s_%s_%s"   , phase , config , PU ) ,
  		    Form("BB-4p-2100-100000_14TEV_%s_%s_%s"       , phase , config , PU )  
  };

  char* labels[n] = {"S*_{T} < 0.3 TeV",
  		     "S*_{T} 0.3-0.7 TeV",
  		     "S*_{T} 0.7-1.3 TeV",
  		     "S*_{T} 1.3-2.1 TeV",
  		     "S*_{T} > 2.1 TeV"};

  char* filename = "plots/BB-ST.pdf";


  // //-------------------------------
  // // boson+jets filenames and labels
  // //-------------------------------

  // const unsigned int n = 7;

  // char* names[n] = {Form("Bj-4p-0-300-v1510_14TEV_%s_%s_%s"       , phase , config , PU ) ,
  // 		    Form("Bj-4p-300-600-v1510_14TEV_%s_%s_%s"     , phase , config , PU ) ,
  // 		    Form("Bj-4p-600-1100-v1510_14TEV_%s_%s_%s"    , phase , config , PU ) ,
  // 		    Form("Bj-4p-1100-1800-v1510_14TEV_%s_%s_%s"   , phase , config , PU ) ,
  // 		    Form("Bj-4p-1800-2700-v1510_14TEV_%s_%s_%s"   , phase , config , PU ) ,
  // 		    Form("Bj-4p-2700-3700-v1510_14TEV_%s_%s_%s"   , phase , config , PU ) ,
  // 		    Form("Bj-4p-3700-100000-v1510_14TEV_%s_%s_%s" , phase , config , PU ) 
  // };
 
  // char* labels[n] = {"S*_{T} < 0.3 TeV",
  // 		     "S*_{T} 0.3-0.6 TeV",
  // 		     "S*_{T} 0.6-1.1 TeV",
  // 		     "S*_{T} 1.1-1.8 TeV",
  // 		     "S*_{T} 1.8-2.7 TeV",
  // 		     "S*_{T} 2.7-3.7 TeV",
  // 		     "S*_{T} > 3.7 TeV"};

  // char* filename = "plots/Bj-ST.pdf";


  // //-------------------------------
  // // ttbar filenames and labels
  // //-------------------------------

  // const unsigned int n = 5;

  // char* names[n] = {Form("tt-4p-0-600-v1510_14TEV_%s_%s_%s"       , phase , config , PU ) ,
  // 		    Form("tt-4p-600-1100-v1510_14TEV_%s_%s_%s"    , phase , config , PU ) ,
  // 		    Form("tt-4p-1100-1700-v1510_14TEV_%s_%s_%s"   , phase , config , PU ) ,
  // 		    Form("tt-4p-1700-2500-v1510_14TEV_%s_%s_%s"   , phase , config , PU ) ,
  // 		    Form("tt-4p-2500-100000-v1510_14TEV_%s_%s_%s" , phase , config , PU )
  // };

  // char* labels[n] = {"S*_{T} < 0.6 TeV",
  // 		     "S*_{T} 0.6-1.1 TeV",
  // 		     "S*_{T} 1.1-1.7 TeV",
  // 		     "S*_{T} 1.7-2.5 TeV",
  // 		     "S*_{T} > 2.5 TeV"
  // };

  // char* filename = "plots/tt-ST.pdf";


  // //-------------------------------
  // // single top filenames and labels
  // //-------------------------------

  // const unsigned int n = 5;

  // char* names[n] = {Form("tj-4p-0-500-v1510_14TEV_%s_%s_%s"       , phase , config , PU ) ,
  // 		    Form("tj-4p-500-1000-v1510_14TEV_%s_%s_%s"    , phase , config , PU ) ,
  // 		    Form("tj-4p-1000-1600-v1510_14TEV_%s_%s_%s"   , phase , config , PU ) ,
  // 		    Form("tj-4p-1600-2400-v1510_14TEV_%s_%s_%s"   , phase , config , PU ) ,
  // 		    Form("tj-4p-2400-100000-v1510_14TEV_%s_%s_%s" , phase , config , PU )  
  // };

  // char* labels[n] = {"S*_{T} < 0.5 TeV",
  // 		     "S*_{T} 0.5-1.0 TeV",
  // 		     "S*_{T} 1.0-1.6 TeV",
  // 		     "S*_{T} 1.6-2.4 TeV",
  // 		     "S*_{T} > 2.4 TeV"
  // };

  // char* filename = "plots/tj-ST.pdf";

  // //-------------------------------
  // // tW filenames and labels
  // //-------------------------------

  // const unsigned int n = 5;

  // char* names[n] = {Form("tB-4p-0-500-v1510_14TEV_%s_%s_%s"       , phase , config , PU ) ,
  // 		    Form("tB-4p-500-900-v1510_14TEV_%s_%s_%s"     , phase , config , PU ) ,
  // 		    Form("tB-4p-900-1500-v1510_14TEV_%s_%s_%s"    , phase , config , PU ) ,
  // 		    Form("tB-4p-1500-2200-v1510_14TEV_%s_%s_%s"   , phase , config , PU ) ,
  // 		    Form("tB-4p-2200-100000-v1510_14TEV_%s_%s_%s" , phase , config , PU )  
  // };

  // char* labels[n] = {"S*_{T} < 0.5 TeV",
  // 		     "S*_{T} 0.5-0.9 TeV",
  // 		     "S*_{T} 0.9-1.5 TeV",
  // 		     "S*_{T} 1.5-2.2 TeV",
  // 		     "S*_{T} > 2.2 TeV"
  // };

  // char* filename = "plots/tB-ST.pdf";

  //--------------------------------------------
  // NO NEED TO MODIFY ANYTHING BELOW HERE
  //--------------------------------------------

  TFile* files[n];

  int   colors[6] = { 2 , 3 , 4 , 5 , 6 , 7 };

  TH1F* hst[n];
  TH1F* hstlo[n];

  THStack* htstack = new THStack();

  TLegend *leg = new TLegend(0.5,0.5,0.8,0.8);

  cout << endl << endl;
  cout << "Printing out yields in 1/pb using cross sections from:" << endl;
  cout << "https://twiki.cern.ch/twiki/bin/viewauth/CMS/HiggsWG/Phase2UpgradeStudies#Background_samples" << endl;
  cout << "The unweighted yields should match the cross sections on this page." << endl;
  cout << "The weighted yields have the additional Event.Weight applied." << endl;

  float ymax = 100;

  for( int i = 0 ; i < n ; i++ ){

    files[i] = TFile::Open(Form("output/%s/%s.root",version,names[i]));
    hst[i] = (TH1F*) files[i]->Get("st");
    hstlo[i] = (TH1F*) files[i]->Get("stlo");
    hst[i]->SetFillColor(colors[i]);

    hst[i]->Rebin(rebin);
    hst[i]->SetMinimum(1);

    cout << endl;
    cout << "1 pb yields for sample " << names[i] << endl;
    cout << "Unweighted yield                  " << hstlo[i]->Integral()/1000.0 << endl;
    cout << "Weighted yield                    " << hst[i]->Integral()/1000.0 << endl;
    cout << "Raw MC events                     " << hstlo[i]->GetEntries() << endl;
    cout << "Average event weight for 3 ab-1   " << 3000.0 * hst[i]->Integral()/(float) hstlo[i]->GetEntries() << endl;

    hst[i]->GetXaxis()->SetTitle("S_{T} [GeV]");
    hst[i]->GetYaxis()->SetTitle("events");

    leg->AddEntry( hst[i] , labels[i] , "lf" );

    htstack->Add(hst[i]);
  }

  ymax = hst[0]->GetMaximum();

  TCanvas *c2 = new TCanvas("c2","c2",1200,600);
  c2->cd();
  gStyle->SetOptStat(0);

  TH2F* hdummy = new TH2F("hdummy","",100,0,5000,100,0.001,5*ymax);
  hdummy->GetXaxis()->SetTitle("S_{T} [GeV]");
  hdummy->GetYaxis()->SetTitle("events");
  hdummy->Draw();

  gPad->SetLogy();
  htstack->Draw("samehist");
  hdummy->Draw("axissame");

  TLatex *t = new TLatex();
  t->SetNDC();
  t->DrawLatex(0.5,0.85,"14 TeV, L = 1 fb^{-1}");

  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->Draw();

  c2->Print(filename);
}
