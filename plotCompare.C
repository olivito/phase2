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


void makePlot( vector<TChain*> samples , vector<string> names , char* var , char* xtitle , TCut sel , TCut weight , int nbin , float xmin , float xmax , bool printplot = false , bool logplot = true ) {
  
  const unsigned int n = samples.size();

  TH1F* h[n];

  TCanvas* can = new TCanvas(Form("%s_can",var),Form("%s_can",var),800,600);
  can->cd();

  int linecolors[]     = {kBlue,kRed,kGreen+2,kMagenta};

  int   nbkg = 0;
  float ymax = 0;

  TLegend* leg = new TLegend(0.5,0.70,0.9,0.9);
  //TLegend* leg = new TLegend(0.5,0.45,0.85,0.6);

  leg->SetFillColor(0);
  leg->SetBorderSize(0);

  char* legentry = "";

  for( unsigned int i = 0 ; i < n ; i++ ){
    h[i] = new TH1F(Form("hist_%s_%s",names.at(i).c_str(),var),"",nbin,xmin,xmax);
    samples.at(i)->Draw(Form("min(%s,%f)>>hist_%s_%s",var,xmax-0.0001,names.at(i).c_str(),var),(sel)*weight);
    h[i]->SetLineColor(linecolors[i]);
    h[i]->SetLineWidth(2);
    Double_t yield, err;
    yield = h[i]->IntegralAndError(0,-1,err);
    cout << "Yield " << names.at(i) << " " << Form("%.0f $\\pm$ %.0f",yield,err) << endl; //<< yield << " $\\pm$ " << err << endl;
    if (h[i]->GetMaximum() > ymax) ymax = h[i]->GetMaximum();
    legentry = names.at(i).c_str();
    leg->AddEntry(h[i],legentry,"l");
  }

  if( logplot ) ymax*=10;
  else          ymax*=1.1;

  TH2F* hdummy = new TH2F("hdummy","",nbin,xmin,xmax,100,1,ymax);
  if( logplot ) gPad->SetLogy();
  hdummy->GetXaxis()->SetTitle(xtitle);
  hdummy->Draw();

  for( unsigned int i = 0 ; i < n ; ++i ){
    h[i]->Draw("hist same");
  }

  leg->Draw();
  hdummy->Draw("axissame");

  if( printplot ) can->Print(Form("plots_compare/%s.pdf",var));
}

void plotCompare(){

  //char* version = (char*) "V00-00-01";
  char* version = (char*) "V00-00-05";

  //char* filter = "skim_1lpt30_2b";
  char* filter = "";

  vector<string> phases;
  vector<string> configs;
  vector<string> PUs;

  phases.push_back("PhaseI");   configs.push_back("Configuration0");   PUs.push_back("NoPileUp");
  phases.push_back("PhaseI");   configs.push_back("Configuration0");   PUs.push_back("140PileUp");
  phases.push_back("PhaseII");  configs.push_back("Configuration4v2"); PUs.push_back("140PileUp");

  // char* sample = "tt-4p*";
  // char* sample = "Bj-4p*";
  // char* sample = "BB-4p*";
  // char* sample = "tj-4p*";
  // char* sample = "tB-4p*";
  //  char* sample = "TChiWH14Pythia";
  char* sample = "TChiWH14PythiaTest";

  vector<TChain*> samples;
  vector<string>  names;

  //---------------------------------
  // load samples
  //---------------------------------

  for (unsigned int i = 0; i < phases.size(); ++i) {
    TChain* ch = new TChain("t");
    ch->Add(Form("output/%s/%s/%s_%s_%s_%s_baby.root"       , version, filter, sample, phases.at(i).c_str() , configs.at(i).c_str() , PUs.at(i).c_str() ) );
    samples.push_back(ch);
    names.push_back(phases.at(i) + "_" + configs.at(i) + "_" + PUs.at(i));
    cout << "Entries for config: " << names.at(i) << ": " << ch->GetEntries() << endl;
  }

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

  TCut mchi200 ("mchi == 200");
  TCut mchi500 ("mchi == 500");
  TCut mchi900 ("mchi == 900");

  TCut mlsp1 ("mlsp == 1");


  //------------------------------
  // plot selection
  //------------------------------

  TCut presel = nlep1 + ptlep30;
  //  TCut presel = nlep1 + ptlep30 + nb2cent + met50 + mbb90;
  //  TCut presel = nlep1 + ptlep30 + nb2 + met50 + mbb90;
  TCut sigsel = presel + nj2 + mt100 + mct160 + met100;
  //  TCut presel3 = presel2 + st750 + met300;// + mct160 + mt300;
  //TCut presel = nlep1 + ptlep30 + nb2;

  TCut mcsel = mchi200 + mlsp1;

  //  TCut plotsel = presel;
  TCut plotsel = presel + mcsel;

  bool printplots = false;

  std::cout << "cuts: " << plotsel.GetTitle() << std::endl;

  makePlot( samples , names , (char*)"njets"  , (char*) "N(jets, pt > 30)"    , TCut(plotsel) , weight , 10 , 0 , 10 , printplots, false );
  // makePlot( samples , names , (char*)"njets40"  , (char*) "N_{jets}, pt > 40"    , TCut(plotsel) , weight , 10 , 0 , 10 , printplots );
  // makePlot( samples , names , (char*)"njetsfwd"  , (char*) "N_{fwd jets}, pt > 30"    , TCut(plotsel) , weight , 10 , 0 , 10 , printplots );
  // makePlot( samples , names , (char*)"njetsfwd40"  , (char*) "N_{fwd jets}, pt > 40"    , TCut(plotsel) , weight , 10 , 0 , 10 , printplots );
  makePlot( samples , names , (char*)"nb"  , (char*) "N(b jets, pt > 30)"    , TCut(plotsel) , weight , 5 , 0 , 5 , printplots, false );

  // makePlot( samples , names , (char*)"st"     , (char*) "S_{T} [GeV]" , TCut(plotsel)              , weight , 60 , 0 , 3000 , printplots );
  //  makePlot( samples , names , (char*)"lep1pt"   , (char*) "lepton p_{T} [GeV]" , TCut(plotsel)              , weight , 50 , 0 , 1000 , printplots );
  // makePlot( samples , names , (char*)"bjet1pt"   , (char*) "leading b-jet p_{T} [GeV]" , TCut(plotsel)              , weight , 50 , 0 , 1000 , printplots );
  // makePlot( samples , names , (char*)"met"  , (char*) "E_{T}^{miss} [GeV]"    , TCut(plotsel) , weight , 50 , 0 , 1000 , printplots );
  // makePlot( samples , names , (char*)"mt"  , (char*) "M_{T} [GeV]"    , TCut(plotsel) , weight , 50 , 0 , 1000 , printplots );
  // makePlot( samples , names , (char*)"mct"  , (char*) "M_{CT} [GeV]"    , TCut(plotsel) , weight , 50 , 0 , 1000 , printplots );
  // makePlot( samples , names , (char*)"ptbb" , (char*) "p_{T}(bb) [GeV]" , TCut(plotsel) , weight , 50 , 0 , 1000 , printplots );
  //  makePlot( samples , names , (char*)"mbb"  , (char*) "M_{bb} [GeV]"    , TCut(nlep1 + ptlep30 + nb2cent + met50) , weight , 50 , 0 , 500 , printplots , false );

}
