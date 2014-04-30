#include <iostream>
#include <utility>
#include <vector>

#include "TROOT.h"
#include "TCut.h"
#include "TStyle.h"
#include "TChain.h"
#include "TLatex.h"
#include "TSystem.h"
#include "TApplication.h"
#include "TString.h"
#include "TH2.h"
#include "THStack.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"
#include "TPaveText.h"
#include "TClonesArray.h"
#include "TLorentzVector.h"

using namespace std;


void makePlot( vector<TChain*> samples , vector<string> names , char* var , char* xtitle , TCut sel , TCut weight , int nbin , float xmin , float xmax , vector<int> sig_mchi, vector<int> sig_mlsp, bool printplot = false , bool logplot = true , bool stacksig = false) {
  
  const float bg_syst1 = 0.125;
  const float bg_syst2 = 0.25;

  const unsigned int n = samples.size();
  const unsigned int nsig = sig_mchi.size();
  const unsigned int ntot = n+nsig;

  TH1F* h[n];
  TH1F* hsig[nsig];

  TCanvas* can = new TCanvas(Form("%s_can",var),Form("%s_can",var),800,600);
  can->cd();

  //int colors[]     = {kBlue-10,kGreen+2,kRed+3,kViolet,kOrange,kBlue,kRed};
  int colors[]     = {kBlue+1,kRed-3,kGreen-2,kRed-4};
  int linecolors[] = {1,2,4,6,8,2,4,6};

  int sig_colors[]     = {kBlue,kRed,kMagenta,kGreen};
  //  int sig_linecolors[] = {2,4,6,5};
  int sig_linecolors[] = {kGreen,kMagenta,kCyan+1,kCyan+6};

  THStack* t = new THStack(Form("%s_stack",var),Form("%s_stack",var));
  TH1F* bkgtot = new TH1F();

  int   nbkg = 0;
  float ymax = 0;

  TLegend* leg = new TLegend(0.6,0.65,0.9,0.9);
  //TLegend* leg = new TLegend(0.5,0.45,0.85,0.6);

  leg->SetFillColor(0);
  leg->SetBorderSize(0);

  //TCut nj2("njets==2");
  //TCut nj2("");

  char* legentry = "";

  for( unsigned int i = 0 ; i < n ; i++ ){
    if( TString(names.at(i)).Contains("sig")  ) continue;
    h[i] = new TH1F(Form("hist_%s_%s",names.at(i).c_str(),var),"",nbin,xmin,xmax);
    //h[i]->Sumw2();
    //samples.at(i)->Draw(Form("min(%s,%f)>>hist_%s_%s",var,xmax-0.0001,names.at(i).c_str(),var),(sel+nj2)*weight);
    samples.at(i)->Draw(Form("min(%s,%f)>>hist_%s_%s",var,xmax-0.0001,names.at(i).c_str(),var),(sel)*weight);
    h[i]->SetFillColor(colors[i]);
    Double_t yield, err;
    yield = h[i]->IntegralAndError(0,-1,err);
    cout << "Yield " << names.at(i) << " " << Form("%.0f $\\pm$ %.0f",yield,err) << endl; //<< yield << " $\\pm$ " << err << endl;
    //cout << "Bin3     " << names.at(i) << " " << h[i]->GetBinContent(3) << " +/- " << h[i]->GetBinError(3) << endl;
    t->Add(h[i]);
    nbkg++;
    ymax += h[i]->GetMaximum();
    if( TString(names.at(i)).Contains("ttbar") ) legentry = "t#bar{t}";
    if( TString(names.at(i)).Contains("Vjets") ) legentry = "V+jets";
    if( TString(names.at(i)).Contains("diboson") ) legentry = "VV";
    if( TString(names.at(i)).Contains("tW") ) legentry = "tW";
    if( TString(names.at(i)).Contains("singletop") ) legentry = "single top";

    leg->AddEntry(h[i],legentry,"f");
    if( i==0 ) bkgtot = (TH1F*) h[i]->Clone("bkgtot");
    else bkgtot->Add(h[i]);
  }

  Double_t nbgtot, errbgtot;
  nbgtot = bkgtot->IntegralAndError(0,-1,errbgtot);
  cout << "Yield Total Bg: " << Form("%.0f $\\pm$ %.0f",nbgtot,errbgtot) << endl; //nbgtot << " $\\pm$ " << errbgtot << endl;

  for( unsigned int i = 0 ; i < n ; i++ ){
    if( !TString(names.at(i)).Contains("sig") ) continue;
    for ( unsigned int j = 0; j < sig_mchi.size(); ++j ) {
      unsigned int abs_index = i+j;
      int mchi = sig_mchi.at(j);
      int mlsp = sig_mlsp.at(j);
      hsig[j] = new TH1F(Form("hist_%s_%d_%d_%s",names.at(i).c_str(),mchi,mlsp,var),"",nbin,xmin,xmax);
      //h[i]->Sumw2();
      TCut sig_sel = sel + Form("(mchi == %d && mlsp == %d)",mchi,mlsp);
      samples.at(i)->Draw(Form("min(%s,%f)>>hist_%s_%d_%d_%s",var,xmax-0.0001,names.at(i).c_str(),mchi,mlsp,var),sig_sel*weight);
      Double_t yield, err;
      yield = hsig[j]->IntegralAndError(0,-1,err);
      cout << "Yield " << names.at(i) << " (" << mchi << "," << mlsp << ") " << Form("%.0f $\\pm$ %.0f",yield,err)
	   << ", S/sqrt(B): " << yield/sqrt(nbgtot) 
	   << ", sig (syst of " << bg_syst1 << "): " << yield/sqrt(nbgtot + (bg_syst1**2)*(nbgtot**2))
	   << ", sig (syst of " << bg_syst2 << "): " << yield/sqrt(nbgtot + (bg_syst2**2)*(nbgtot**2)) << endl;
      //cout << "Bin3     " << names.at(i) << " " << h[i]->GetBinContent(3) << " +/- " << h[i]->GetBinError(3) << endl;
      if( TString(names.at(i)).Contains("WH_sig") ) legentry = Form("WH signal (%d,%d)",mchi,mlsp);
      leg->AddEntry(hsig[j],legentry,"l");
      if( stacksig ) hsig[j]->Add(bkgtot);
    }
  }

  if( logplot ) ymax*=10;
  else          ymax*=1.1;

  TH2F* hdummy = new TH2F("hdummy","",nbin,xmin,xmax,100,1,ymax);
  if( logplot ) gPad->SetLogy();
  hdummy->GetXaxis()->SetTitle(xtitle);
  hdummy->Draw();

  t->Draw("same");
  for( unsigned int j = 0 ; j < nsig ; ++j ){
    hsig[j]->SetLineColor(sig_linecolors[j]);
    hsig[j]->SetLineWidth(2);
    hsig[j]->Draw("samehist");
  }

  leg->Draw();
  hdummy->Draw("axissame");

  if( printplot ) can->Print(Form("plots_WH/%s.pdf",var));
}

void plotMaker_WH(){

  //char* version = (char*) "V00-00-01";
  char* version = (char*) "V00-00-05";

  char* phase = (char*) "PhaseI";

  char* config = (char*) "Configuration0";

  char* PU = (char*) "NoPileUp";
  //char* PU = (char*) "140PileUp";

  char* filter = "skim_1lpt30_2b";
  //char* filter = "";

  //---------------------------------
  // load ttbar samples
  //---------------------------------

  TChain* chtt = new TChain("t");
  chtt->Add(Form("output/%s/%s/tt-4p*_%s_%s_%s_baby.root"       , version, filter , phase , config , PU ) );

  // chtt->Add(Form("output/%s/tt-4p-0-600-v1510_14TEV_%s_%s_%s%s_baby.root"       , version , phase , config , PU , filter ) );
  // chtt->Add(Form("output/%s/tt-4p-600-1100-v1510_14TEV_%s_%s_%s%s_baby.root"    , version , phase , config , PU , filter ) );
  // chtt->Add(Form("output/%s/tt-4p-1100-1700-v1510_14TEV_%s_%s_%s%s_baby.root"   , version , phase , config , PU , filter ) );
  // chtt->Add(Form("output/%s/tt-4p-1700-2500-v1510_14TEV_%s_%s_%s%s_baby.root"   , version , phase , config , PU , filter ) );
  // chtt->Add(Form("output/%s/tt-4p-2500-100000-v1510_14TEV_%s_%s_%s%s_baby.root" , version , phase , config , PU , filter ) );

  cout << "tt entries " << chtt->GetEntries() << endl;

  //---------------------------------
  // load boson+jet samples
  //---------------------------------

  TChain* chw = new TChain("t");
  chw->Add(Form("output/%s/%s/Bj-4p*_%s_%s_%s_baby.root"       , version, filter , phase , config , PU ) );

  // chw->Add(Form("output/%s/Bj-4p-0-300-v1510_14TEV_%s_%s_%s%s_baby.root"       , version , phase , config , PU , filter ) );
  // chw->Add(Form("output/%s/Bj-4p-300-600-v1510_14TEV_%s_%s_%s%s_baby.root"     , version , phase , config , PU , filter ) );
  // chw->Add(Form("output/%s/Bj-4p-600-1100-v1510_14TEV_%s_%s_%s%s_baby.root"    , version , phase , config , PU , filter ) );
  // chw->Add(Form("output/%s/Bj-4p-1100-1800-v1510_14TEV_%s_%s_%s%s_baby.root"   , version , phase , config , PU , filter ) );
  // chw->Add(Form("output/%s/Bj-4p-1800-2700-v1510_14TEV_%s_%s_%s%s_baby.root"   , version , phase , config , PU , filter ) );
  // chw->Add(Form("output/%s/Bj-4p-2700-3700-v1510_14TEV_%s_%s_%s%s_baby.root"   , version , phase , config , PU , filter ) );
  // chw->Add(Form("output/%s/Bj-4p-3700-100000-v1510_14TEV_%s_%s_%s%s_baby.root" , version , phase , config , PU , filter ) );

  cout << "boson+jet entries " << chw->GetEntries() << endl;


  //---------------------------------
  // load diboson samples
  //---------------------------------

  TChain* chvv = new TChain("t");
  chvv->Add(Form("output/%s/%s/BB-4p*_%s_%s_%s_baby.root"       , version, filter , phase , config , PU ) );

  // chvv->Add(Form("output/%s/BB-4p-0-300-v1510_14TEV_%s_%s_%s%s_baby.root"       , version , phase , config , PU , filter ) );
  // chvv->Add(Form("output/%s/BB-4p-300-700-v1510_14TEV_%s_%s_%s%s_baby.root"     , version , phase , config , PU , filter ) );
  // chvv->Add(Form("output/%s/BB-4p-700-1300-v1510_14TEV_%s_%s_%s%s_baby.root"    , version , phase , config , PU , filter ) );
  // chvv->Add(Form("output/%s/BB-4p-1300-2100-v1510_14TEV_%s_%s_%s%s_baby.root"   , version , phase , config , PU , filter ) );
  // chvv->Add(Form("output/%s/BB-4p-2100-100000_14TEV_%s_%s_%s%s_baby.root"       , version , phase , config , PU , filter ) );

  cout << "diboson entries " << chvv->GetEntries() << endl;

  //---------------------------------
  // load single top samples
  //---------------------------------

  TChain* cht = new TChain("t");
  cht->Add(Form("output/%s/%s/tj-4p*_%s_%s_%s_baby.root"       , version, filter , phase , config , PU ) );

  // cht->Add(Form("output/%s/tj-4p-0-500-v1510_14TEV_%s_%s_%s%s_baby.root"       , version , phase , config , PU , filter ) );
  // cht->Add(Form("output/%s/tj-4p-500-1000-v1510_14TEV_%s_%s_%s%s_baby.root"    , version , phase , config , PU , filter ) );
  // cht->Add(Form("output/%s/tj-4p-1000-1600-v1510_14TEV_%s_%s_%s%s_baby.root"   , version , phase , config , PU , filter ) );
  // cht->Add(Form("output/%s/tj-4p-1600-2400-v1510_14TEV_%s_%s_%s%s_baby.root"   , version , phase , config , PU , filter ) );
  // cht->Add(Form("output/%s/tj-4p-2400-100000-v1510_14TEV_%s_%s_%s%s_baby.root" , version , phase , config , PU , filter ) );

  //  cout << "single top entries " << cht->GetEntries() << endl;

  //---------------------------------
  // load tW samples
  //---------------------------------

  // TChain* chtw = new TChain("t");
  // chtw->Add(Form("output/%s/%s/tB-4p*_%s_%s_%s_baby.root"       , version, filter , phase , config , PU ) );
  // merge with single top!
  cht->Add(Form("output/%s/%s/tB-4p*_%s_%s_%s_baby.root"       , version, filter , phase , config , PU ) );

  // chtw->Add(Form("output/%s/tB-4p-0-500-v1510_14TEV_%s_%s_%s%s_baby.root"       , version , phase , config , PU , filter ) );
  // chtw->Add(Form("output/%s/tB-4p-500-900-v1510_14TEV_%s_%s_%s%s_baby.root"     , version , phase , config , PU , filter ) );
  // chtw->Add(Form("output/%s/tB-4p-900-1500-v1510_14TEV_%s_%s_%s%s_baby.root"    , version , phase , config , PU , filter ) );
  // chtw->Add(Form("output/%s/tB-4p-1500-2200-v1510_14TEV_%s_%s_%s%s_baby.root"   , version , phase , config , PU , filter ) );
  // chtw->Add(Form("output/%s/tB-4p-2200-100000-v1510_14TEV_%s_%s_%s%s_baby.root" , version , phase , config , PU , filter ) );

  //  cout << "tW entries " << chtw->GetEntries() << endl;
  cout << "single top entries " << cht->GetEntries() << endl;


  //---------------------------------
  // signal samples
  //---------------------------------

  TChain* chWH = new TChain("t");
  // TChain* WH2 = new TChain("t");
  // TChain* WH3 = new TChain("t");

  chWH->Add(Form("output/%s/%s/TChiWH14Pythia_%s_%s_%s_baby.root"       , version, filter , phase , config , PU ) );

  cout << "TChiWH entries " << chWH->GetEntries() << endl;

  vector<TChain*> samples;
  vector<string>  names;

  samples.push_back(chvv); names.push_back("diboson");
  samples.push_back(cht);  names.push_back("singletop");
  //  samples.push_back(chtw); names.push_back("tW");
  samples.push_back(chw);  names.push_back("Vjets");
  samples.push_back(chtt); names.push_back("ttbar");
  samples.push_back(chWH); names.push_back("WH_sig");

  // signal mass points to plot
  vector<int> sig_mchi, sig_mlsp;
  sig_mchi.push_back(200); sig_mlsp.push_back(1);
  sig_mchi.push_back(500); sig_mlsp.push_back(1);
  sig_mchi.push_back(900); sig_mlsp.push_back(1);
  
  //---------------------------------
  // signal samples
  //---------------------------------

  TCut nlep1("nleps==1");
  TCut nlep3("nleps==3");
  TCut ptlep30("lep1pt>30");
  TCut ptlep50("lep1pt>50");
  TCut ptlep100("lep1pt>100");
  TCut nb2("nb==2");
  TCut nb2cent("nb==2 && abs(bjet1eta) < 2.4 && abs(bjet2eta) < 2.4");
  TCut nj2("njets==2");
  TCut nj23("njets==2 || njets==3");
  TCut nj0fwd("njetsfwd==0");
  TCut mt100("mt > 100.0");
  TCut mt200("mt > 200.0");
  TCut mt300("mt > 300.0");
  TCut mt500("mt > 500.0");
  TCut mt600("mt > 600.0");
  TCut met50("met > 50.0");
  TCut met100("met > 100.0");
  TCut met175("met > 175.0");
  TCut met200("met > 200.0");
  TCut met300("met > 300.0");
  TCut met400("met > 400.0");
  TCut metlt200("met <= 200.0");
  TCut metlt300("met <= 300.0");
  TCut metlt400("met <= 400.0");
  TCut met500("met > 500.0");
  TCut met600("met > 600.0");
  TCut met700("met > 700.0");
  TCut mct160("mct > 160.0");
  TCut st750("st > 750.0");
  TCut st1000("st > 1000.0");
  TCut mbb100("mbb > 100.0 && mbb < 150.0");
  TCut mbb90("mbb > 90.0 && mbb < 150.0");
  TCut jet1pt100("jet1pt > 100.0");
  TCut jet2pt50 ("jet2pt >  50.0");
  TCut jet3pt50 ("jet3pt <  50.0");
  TCut weight("3000. * weight * stweight");
  // TCut drlj1("sqrt( pow(lep1eta-jet1eta,2) + pow(acos(cos(lep1phi-jet1phi)) ,2) ) > 0.4");
  // TCut drlj2("sqrt( pow(lep1eta-jet2eta,2) + pow(acos(cos(lep1phi-jet2phi)) ,2) ) > 0.4");
  // TCut drlj3("sqrt( pow(lep1eta-jet3eta,2) + pow(acos(cos(lep1phi-jet3phi)) ,2) ) > 0.4");
  // TCut drlj4("sqrt( pow(lep1eta-jet4eta,2) + pow(acos(cos(lep1phi-jet4phi)) ,2) ) > 0.4");

  //------------------------------
  // plot selection
  //------------------------------

  TCut presel = nlep1 + ptlep30 + nb2cent + met50 + mbb90;
  //  TCut presel = nlep1 + ptlep30 + nb2 + met50 + mbb90;
  TCut sigsel = presel + nj2 + mt100 + mct160 + met100;
  //  TCut presel3 = presel2 + st750 + met300;// + mct160 + mt300;
  //TCut presel = nlep1 + ptlep30 + nb2;

  //  TCut plotsel = presel;
  TCut plotsel = sigsel;

  bool printplots = true;

  std::cout << "cuts: " << plotsel.GetTitle() << std::endl;

  // makePlot( samples , names , (char*)"njets"  , (char*) "N_{jets}, pt > 30"    , TCut(plotsel) , weight , 10 , 0 , 10 , sig_mchi , sig_mlsp , printplots );
  // makePlot( samples , names , (char*)"njets40"  , (char*) "N_{jets}, pt > 40"    , TCut(plotsel) , weight , 10 , 0 , 10 , sig_mchi , sig_mlsp , printplots );
  // makePlot( samples , names , (char*)"njetsfwd"  , (char*) "N_{fwd jets}, pt > 30"    , TCut(plotsel) , weight , 10 , 0 , 10 , sig_mchi , sig_mlsp , printplots );
  // makePlot( samples , names , (char*)"njetsfwd40"  , (char*) "N_{fwd jets}, pt > 40"    , TCut(plotsel) , weight , 10 , 0 , 10 , sig_mchi , sig_mlsp , printplots );

  // makePlot( samples , names , (char*)"st"     , (char*) "S_{T} [GeV]" , TCut(plotsel)              , weight , 60 , 0 , 3000 , sig_mchi , sig_mlsp , printplots );
  makePlot( samples , names , (char*)"lep1pt"   , (char*) "lepton p_{T} [GeV]" , TCut(plotsel)              , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  // makePlot( samples , names , (char*)"bjet1pt"   , (char*) "leading b-jet p_{T} [GeV]" , TCut(plotsel)              , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  // makePlot( samples , names , (char*)"met"  , (char*) "E_{T}^{miss} [GeV]"    , TCut(plotsel) , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  // makePlot( samples , names , (char*)"mt"  , (char*) "M_{T} [GeV]"    , TCut(plotsel) , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  // makePlot( samples , names , (char*)"mct"  , (char*) "M_{CT} [GeV]"    , TCut(plotsel) , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  // makePlot( samples , names , (char*)"ptbb" , (char*) "p_{T}(bb) [GeV]" , TCut(plotsel) , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  //  makePlot( samples , names , (char*)"mbb"  , (char*) "M_{bb} [GeV]"    , TCut(nlep1 + ptlep30 + nb2cent + met50) , weight , 50 , 0 , 500 , sig_mchi , sig_mlsp , printplots , false );

}
