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

const int iPeriod = 14;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV, 14= PU=140,14TeV 

  // second parameter in example_plot is iPos, which drives the position of the CMS logo in the plot
  // iPos=11 : top-left, left-aligned
  // iPos=33 : top-right, right-aligned
  // iPos=22 : center, centered
  // mode generally : 
  //   iPos = 10*(alignement 1/2/3) + position (1/2/3 = left/center/right)

const int iPos = 33;


void makePlot( vector<TChain*> samples , vector<string> names , const char* var , const char* xtitle , const char* ytitle , TCut sel , TCut weight , int nbin , float xmin , float xmax , vector<int> sig_mchi, vector<int> sig_mlsp, bool printplot = false , bool logplot = true , bool stacksig = false) {

  cout << "-- plotting var: " << var << ", with cuts: " << sel.GetTitle() << endl;
  
  const float bg_syst1 = 0.125;
  const float bg_syst2 = 0.25;

  const unsigned int n = samples.size();
  const unsigned int nsig = sig_mchi.size();
  const unsigned int ntot = n+nsig;
  int nbg_temp = 0;
  for( unsigned int i = 0 ; i < n ; i++ ){
    if( TString(names.at(i)).Contains("sig")  ) continue;
    ++nbg_temp;
  }
  const unsigned int nbg = nbg_temp;

  TH1D* h[nbg];
  TH1D* hsig[nsig];

  //  TCanvas* can = new TCanvas(Form("%s_can",var),Form("%s_can",var),800,600);
  TCanvas* can = new TCanvas(Form("%s_can",var),Form("%s_can",var),800,600);
  can->cd();
  gPad->SetTopMargin(0.08);
  gPad->SetRightMargin(0.05);
  gPad->Modified();

  //int colors[]     = {kBlue-10,kGreen+2,kRed+3,kViolet,kOrange,kBlue,kRed};
  int colors[]     = {kGray+2,kBlue+1,kRed-3,kGreen-2,kRed-4};
  int linecolors[] = {1,2,4,6,8,2,4,6};

  int sig_colors[]     = {kBlue,kRed,kMagenta,kGreen};
  //  int sig_linecolors[] = {2,4,6,5};
  int sig_linecolors[] = {kGreen,kMagenta,kCyan+1,kYellow+1};

  THStack* t = new THStack(Form("%s_stack",var),Form("%s_stack",var));
  TH1D* bkgtot = new TH1D();

  float ymax = 0;
  float ymin = 0.1;

  TLegend* leg = new TLegend(0.62,0.48,0.92,0.83);
  //  TLegend* leg = new TLegend(0.62,0.58,0.92,0.88);
  //  TLegend* leg = new TLegend(0.65,0.55,0.95,0.85);
  //  TLegend* leg = new TLegend(0.7,0.6,0.9,0.85);
  //TLegend* leg = new TLegend(0.5,0.45,0.85,0.6);

  leg->SetFillColor(0);
  leg->SetBorderSize(0);

  //TCut nj2("njets==2");
  //TCut nj2("");

  char* legentry = "";

  for( unsigned int i = 0 ; i < n ; i++ ){
    if( TString(names.at(i)).Contains("sig")  ) continue;
    h[i] = new TH1D(Form("hist_%s_%s",names.at(i).c_str(),var),"",nbin,xmin,xmax);
    h[i]->Sumw2();
    //samples.at(i)->Draw(Form("min(%s,%f)>>hist_%s_%s",var,xmax-0.0001,names.at(i).c_str(),var),(sel+nj2)*weight);
    samples.at(i)->Draw(Form("min(%s,%f)>>hist_%s_%s",var,xmax-0.0001,names.at(i).c_str(),var),(sel)*weight);
    h[i]->SetFillColor(colors[i]);
    Double_t yield, err;
    yield = h[i]->IntegralAndError(0,-1,err);
    if (yield > 10.) {
      cout << "Yield " << names.at(i) << " " << Form("%.0f $\\pm$ %.0f",yield,err) << endl; //<< yield << " $\\pm$ " << err << endl;
    } else {
      cout << "Yield " << names.at(i) << " " << Form("%.1f $\\pm$ %.1f",yield,err) << endl; //<< yield << " $\\pm$ " << err << endl;
    }
    //cout << "Bin3     " << names.at(i) << " " << h[i]->GetBinContent(3) << " +/- " << h[i]->GetBinError(3) << endl;
    t->Add(h[i]);
    ymax += h[i]->GetMaximum();
    // if( TString(names.at(i)).Contains("ttbar") ) legentry = "t#bar{t}";
    // if( TString(names.at(i)).Contains("Vjets") ) legentry = "V+jets";
    // if( TString(names.at(i)).Contains("diboson") ) legentry = "VV";
    // if( TString(names.at(i)).Contains("tW") ) legentry = "tW";
    // if( TString(names.at(i)).Contains("singletop") ) legentry = "single top";
    // if( TString(names.at(i)).Contains("WH") ) legentry = "SM WH";

    // leg->AddEntry(h[i],legentry,"f");
    if( i==0 ) bkgtot = (TH1D*) h[i]->Clone("bkgtot");
    else bkgtot->Add(h[i]);
  }

  // loop backwards to add to legend
  for (int ibg = nbg-1; ibg >= 0; --ibg) {
    if( TString(names.at(ibg)).Contains("ttbar") ) legentry = "t#bar{t}";
    if( TString(names.at(ibg)).Contains("Vjets") ) legentry = "V+jets";
    if( TString(names.at(ibg)).Contains("diboson") ) legentry = "VV";
    if( TString(names.at(ibg)).Contains("tW") ) legentry = "tW";
    if( TString(names.at(ibg)).Contains("singletop") ) legentry = "Single top";
    if( TString(names.at(ibg)).Contains("WH") ) legentry = "Other SM";

    leg->AddEntry(h[ibg],legentry,"f");
  }

  Double_t nbgtot, errbgtot;
  nbgtot = bkgtot->IntegralAndError(0,-1,errbgtot);
  cout << "Yield Total Bg: " << Form("%.0f $\\pm$ %.0f",nbgtot,errbgtot) << endl; //nbgtot << " $\\pm$ " << errbgtot << endl;

  for( unsigned int i = 0 ; i < n ; i++ ){
    if( !TString(names.at(i)).Contains("sig") ) continue;
    for ( unsigned int j = 0; j < sig_mchi.size(); ++j ) {
      int mchi = sig_mchi.at(j);
      int mlsp = sig_mlsp.at(j);
      // only do mchi for TChiWH
      // skip nonzero mchi values for natural model
      if (TString(names.at(i)).Contains("WH_sig") && mchi == 0 && mlsp == 0) continue;
      if (TString(names.at(i)).Contains("NM2_sig") && mchi != 0 && mlsp != 0) continue;
      hsig[j] = new TH1D(Form("hist_%s_%d_%d_%s",names.at(i).c_str(),mchi,mlsp,var),"",nbin,xmin,xmax);
      hsig[j]->Sumw2();
      TCut sig_sel(sel);
      if (TString(names.at(i)).Contains("WH_sig")) sig_sel = sel + Form("(mchi == %d && mlsp == %d)",mchi,mlsp);
      samples.at(i)->Draw(Form("min(%s,%f)>>hist_%s_%d_%d_%s",var,xmax-0.0001,names.at(i).c_str(),mchi,mlsp,var),sig_sel*weight);
      Double_t yield, err;
      yield = hsig[j]->IntegralAndError(0,-1,err);
      if (yield > 10.) {
	cout << "Yield " << names.at(i) << " (" << mchi << "," << mlsp << ") " << Form("%.0f $\\pm$ %.0f",yield,err);
      } else {
	cout << "Yield " << names.at(i) << " (" << mchi << "," << mlsp << ") " << Form("%.1f $\\pm$ %.1f",yield,err);
      }
      if (nbgtot > 0) { 
	cout << ", S/sqrt(B): " << yield/sqrt(nbgtot) 
	     << ", sig (syst of " << bg_syst1 << "): " << yield/sqrt(nbgtot + (bg_syst1**2)*(nbgtot**2))
	     << ", sig (syst of " << bg_syst2 << "): " << yield/sqrt(nbgtot + (bg_syst2**2)*(nbgtot**2));
      }
      cout << endl;
      if( TString(names.at(i)).Contains("WH_sig") ) legentry = Form("WH signal (%d,%d)",mchi,mlsp);
      if( TString(names.at(i)).Contains("NM2_sig") ) legentry = Form("NM2 ",mchi,mlsp);
      hsig[j]->SetLineColor(sig_linecolors[j]);
      hsig[j]->SetLineWidth(2);
      leg->AddEntry(hsig[j],legentry,"l");
      if( stacksig ) hsig[j]->Add(bkgtot);
    }
  }

  if( logplot ) ymax*=10;
  else          ymax*=1.1;

  TH2F* hdummy = new TH2F("hdummy","",nbin,xmin,xmax,100,ymin,ymax);
  if( logplot ) gPad->SetLogy();
  hdummy->GetXaxis()->SetTitle(xtitle);
  hdummy->GetXaxis()->SetNdivisions(9,5,0);
  hdummy->GetYaxis()->SetTitle(ytitle);
  hdummy->SetLabelSize(0.05, "XYZ");
  hdummy->SetTitleSize(0.06,"Y");
  hdummy->Draw();

  t->Draw("samehist");
  for( unsigned int j = 0 ; j < nsig ; ++j ){
    hsig[j]->Draw("samehist");
  }

  leg->Draw();
  hdummy->Draw("axissame");

  CMS_lumi( can, iPeriod, iPos );

  can->Update();

  if( printplot ) can->Print(Form("plots_WH/%s.pdf",var));

  cout << endl;
}

void print_table( vector<TChain*> samples , vector<string> names , std::vector<std::string> sels , TCut weight , vector<int> sig_mchi, vector<int> sig_mlsp) {

  const unsigned int n = samples.size();
  const unsigned int nsig = sig_mchi.size();
  const unsigned int ntot = n+nsig;
  const unsigned int nsels = sels.size();

  vector<double> bgtot(nsels,0.);
  vector<double> bgerr(nsels,0.);

  for( unsigned int i = 0 ; i < n ; i++ ){
    if( TString(names.at(i)).Contains("sig")  ) continue;

    std::string legentry = "dummy";
    if( TString(names.at(i)).Contains("ttbar") ) legentry = "ttbar";
    if( TString(names.at(i)).Contains("Vjets") ) legentry = "V+jets";
    if( TString(names.at(i)).Contains("diboson") ) legentry = "VV";
    if( TString(names.at(i)).Contains("tW") ) legentry = "tW";
    if( TString(names.at(i)).Contains("singletop") ) legentry = "single top";
    if( TString(names.at(i)).Contains("WH") ) legentry = "SM WH";
    cout << legentry;

    for ( unsigned int isel = 0; isel < nsels; ++isel ) {
      TH1D* hdummy = new TH1D(Form("hdummy_%s_%d",names.at(i).c_str(),isel),"",10,0,1000);
      hdummy->Sumw2();
      samples.at(i)->Draw(Form("met>>hdummy_%s_%d",names.at(i).c_str(),isel),TCut(sels.at(isel).c_str())*weight);
      //      std::cout << TCut(TCut(sels.at(isel).c_str())*weight).GetTitle() << endl;
      Double_t yield, err;
      yield = hdummy->IntegralAndError(0,-1,err);
      bgtot.at(isel) += yield;
      bgerr.at(isel) = sqrt(bgerr.at(isel)**2 + err**2);
      if (yield > 10.) {
	cout << "  &  " << Form("%.0f $\\pm$ %.0f",yield,err);
      } else {
	cout << "  &  " << Form("%.1f $\\pm$ %.1f",yield,err);
      }
    }
    cout << " \\\\" << endl;
  }

  // print bg totals
  cout << "\\hline" << endl;
  cout << "Total SM";
  for ( unsigned int isel = 0; isel < nsels; ++isel ) {
    double yield = bgtot.at(isel);
    double err = bgerr.at(isel);
    if (yield > 10.) {
      cout << "  &  " << Form("%.0f $\\pm$ %.0f",yield,err);
    } else {
      cout << "  &  " << Form("%.1f $\\pm$ %.1f",yield,err);
    }
  }
  cout << " \\\\" << endl;
  cout << "\\hline" << endl;

  for( unsigned int i = 0 ; i < n ; i++ ){
    if( !TString(names.at(i)).Contains("sig") ) continue;

    for ( unsigned int j = 0; j < sig_mchi.size(); ++j ) {
      int mchi = sig_mchi.at(j);
      int mlsp = sig_mlsp.at(j);
      // only do mchi for TChiWH
      // skip nonzero mchi values for natural model
      if (TString(names.at(i)).Contains("WH_sig") && mchi == 0 && mlsp == 0) continue;
      if (TString(names.at(i)).Contains("NM2_sig") && mchi != 0 && mlsp != 0) continue;

      std::string legentry = "dummy";
      if( TString(names.at(i)).Contains("WH_sig") ) legentry = Form("WH signal (%d,%d)",mchi,mlsp);
      if( TString(names.at(i)).Contains("NM2_sig") ) legentry = Form("Natural Model 2 ",mchi,mlsp);
      cout << legentry;

      for ( unsigned int isel = 0; isel < nsels; ++isel ) {
	TH1D* hdummy = new TH1D(Form("hdummy_%s_%d",names.at(i).c_str(),isel),"",10,0,1000);
	hdummy->Sumw2();
        TCut sig_sel(sels.at(isel).c_str());
        if (TString(names.at(i)).Contains("WH_sig")) sig_sel += TCut(Form("(mchi == %d && mlsp == %d)",mchi,mlsp));
	samples.at(i)->Draw(Form("met>>hdummy_%s_%d",names.at(i).c_str(),isel),TCut(sig_sel)*weight);
	Double_t yield, err;
	yield = hdummy->IntegralAndError(0,-1,err);
	bgtot.at(isel) += yield;
	bgerr.at(isel) = sqrt(bgerr.at(isel)**2 + err**2);
	if (yield > 10.) {
	  cout << "  &  " << Form("%.0f $\\pm$ %.0f",yield,err);
	} else {
	  cout << "  &  " << Form("%.1f $\\pm$ %.1f",yield,err);
	}
      } // loop over selections
      cout << " \\\\" << endl;
    } // loop over masses
  } // loop over samples

}

void plotMaker_WH(){

  gROOT->LoadMacro("CMS_lumi.C");

  // cmsText     = "CMS Phase I Simulation";
  // lumi_14TeV = "300 fb^{-1}, PU = 50"; // default is "3000 fb^{-1}"
  cmsText     = "CMS Phase II Simulation";
  lumi_14TeV = "3000 fb^{-1}, PU = 140"; // default is "3000 fb^{-1}"
  writeExtraText = false;       // if extra text
  //  extraText  = "Preliminary";  // default extra text is "Preliminary"

  //char* version = (char*) "V00-00-01";
  char* version = (char*) "V00-00-12";
  //char* version = (char*) "V00-00-12_nopujetid";
  //  char* version = (char*) "merge";

  // char* phase = (char*) "PhaseI";
  // char* config = (char*) "";
  // char* PU = (char*) "50PU";

  char* phase = (char*) "PhaseII";
  char* config = (char*) "";
  char* PU = (char*) "140PU";

  char* filter = "skim_1lpt30_2b";
  //  char* filter = "skim_1lpt30_2b_aged";
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
  // load triboson/vh samples
  //---------------------------------

  TChain* chvh = new TChain("t");
  chvh->Add(Form("output/%s/%s/BBB-4p*_%s_%s_%s_baby.root"       , version, filter , phase , config , PU ) );

  cout << "triboson/vh entries " << chvh->GetEntries() << endl;

  //---------------------------------
  // signal samples
  //---------------------------------

  TChain* chWH = new TChain("t");

  chWH->Add(Form("output/%s/%s/TChiWH14Pythia_%s_%s_%s_baby.root"       , version, filter , phase , config , PU ) );
  //chWH->Add(Form("output/%s/%s/TChiWH14PythiaTest_%s_%s_%s_baby.root"       , version, filter , phase , config , PU ) );

  cout << "TChiWH entries " << chWH->GetEntries() << endl;

  TChain* chNM2 = new TChain("t");
  chNM2->Add(Form("output/%s/%s/naturalModel2_%s_%s_%s_baby.root"       , version, filter , phase , config , PU ) );

  cout << "naturalModel2 entries " << chNM2->GetEntries() << endl;

  vector<TChain*> samples;
  vector<string>  names;

  samples.push_back(chvh); names.push_back("WH");
  samples.push_back(chvv); names.push_back("diboson");
  samples.push_back(cht);  names.push_back("singletop");
  samples.push_back(chw);  names.push_back("Vjets");
  samples.push_back(chtt); names.push_back("ttbar");
  samples.push_back(chWH); names.push_back("WH_sig");
  samples.push_back(chNM2); names.push_back("NM2_sig");

  //  samples.push_back(chtw); names.push_back("tW");

  // signal mass points to plot
  vector<int> sig_mchi, sig_mlsp;
  sig_mchi.push_back(200); sig_mlsp.push_back(1);
  sig_mchi.push_back(500); sig_mlsp.push_back(1);
  sig_mchi.push_back(900); sig_mlsp.push_back(1);
  sig_mchi.push_back(0); sig_mlsp.push_back(0);
  
  //---------------------------------
  // signal samples
  //---------------------------------

  TCut nlep1("nleps==1");
  TCut nlep3("nleps==3");
  TCut ptlep30("lep1pt>30");
  TCut ptlep40("lep1pt>40");
  TCut ptlep50("lep1pt>50");
  TCut ptlep100("lep1pt>100");
  TCut etalep("abs(lep1eta) < 2.4");
  TCut agednlep1("agednleps==1");
  TCut agedptlep40("agedlep1pt>40");
  TCut agedetalep("abs(agedlep1eta) < 2.4");
  TCut agedmu("agedlep1pt>35 && abs(agedlep1eta) < 1.1 && leptype == 1");
  TCut agedel("agedlep1pt>50 && abs(agedlep1eta) < 2.4 && leptype == 0");
  TCut agedlep = agedmu || agedel;

  TCut njmin2("njets>=2");
  TCut njmin2pt40("njets40>=2");
  TCut nb2("nb==2");
  TCut nj2pt40cent("nb==0 && bjet1pt > 40. && bjet2pt > 40. &&  abs(bjet1eta) < 2.4 && abs(bjet2eta) < 2.4");
  //TCut nb2pt40cent("nb==2 && bjet1pt > 40. && bjet2pt > 40. &&  abs(bjet1eta) < 2.4 && abs(bjet2eta) < 2.4");
  TCut nb2pt40cent("(nb==2 || (nb==0 && bgweight < 0.1)) && bjet1pt > 40. && bjet2pt > 40. &&  abs(bjet1eta) < 2.4 && abs(bjet2eta) < 2.4");
  TCut nb2cent("nb==2 && abs(bjet1eta) < 2.4 && abs(bjet2eta) < 2.4");
  TCut nj2("njets==2");
  TCut nj2pt40("njets40==2");
  TCut nj23("njets==2 || njets==3");
  TCut nj0fwd("njetsfwd==0");
  TCut mt100("mt > 100.0");
  TCut oldmt100("oldmt > 100.0");
  TCut mt200("mt > 200.0");
  TCut mt300("mt > 300.0");
  TCut mt500("mt > 500.0");
  TCut mt600("mt > 600.0");
  TCut pujetmt100("pujetmt > 100.0");
  TCut smearmt100("smearmt > 100.0");
  TCut dmet200("abs(met - pujetmet)< 200.0");
  TCut met50("met > 50.0");
  TCut met100("met > 100.0");
  TCut met175("met > 175.0");
  TCut met200("met > 200.0");
  TCut met300("met > 300.0");
  TCut met400("met > 400.0");
  TCut oldmet100("oldmet > 100.0");
  TCut oldmet200("oldmet > 200.0");
  TCut oldmet300("oldmet > 300.0");
  TCut oldmet400("oldmet > 400.0");
  TCut oldmet500("oldmet > 500.0");
  TCut pujetmet50("pujetmet > 50.0");
  TCut pujetmet100("pujetmet > 100.0");
  TCut pujetmet200("pujetmet > 200.0");
  TCut pujetmet300("pujetmet > 300.0");
  TCut pujetmet400("pujetmet > 400.0");
  TCut pujetmet500("pujetmet > 500.0");
  TCut smearmet200("smearmet > 200.0");
  TCut smearmet300("smearmet > 300.0");
  TCut smearmet400("smearmet > 400.0");
  TCut smearmet500("smearmet > 500.0");
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
  TCut dupjets ("!(abs(bjet1pt - bjet2pt) < 0.1 && abs(bjet1eta - bjet2eta) < 0.1 && abs(bjet1phi - bjet2phi) < 0.1)");
  TCut dphijetmet ("max(acos(cos(bjet1phi-pujetmetphi)),acos(cos(bjet2phi-pujetmetphi))) < 3. && min(acos(cos(bjet1phi-pujetmetphi)),acos(cos(bjet2phi-pujetmetphi))) > 0.1");
  TCut wlight ("nw == 1 && nbgen == 0 && ncgen == 0");
  TCut photveto100("phot1pt < 100.");

  TCut weight("3000. * weight * genweight * bgweight");
  //  TCut weight("300. * weight * genweight * bgweight");

  //  TCut weight("1000. * weight * genweight * bgweight");
  //  TCut weight("1000. * weight * genweight * bgweight * agedweight");

  //------------------------------
  // plot selection
  //------------------------------

  //  TCut presel = "";
  //  TCut presel = nlep1 + ptlep40 + etalep + njmin2pt40 + nb2pt40cent + mbb90;
  //  TCut presel = nlep1 + ptlep40 + etalep + njmin2pt40 + nb2pt40cent + mbb90 + dphijetmet;
  //TCut presel = nlep1 + ptlep40 + etalep + njmin2pt40 + nb2pt40cent + mbb90 + photveto100;
  TCut presel = nlep1 + ptlep40 + etalep + njmin2pt40 + nb2pt40cent + mbb90 + photveto100 + dmet200;
  //  TCut presel = agednlep1 + agedptlep40 + agedetalep + njmin2pt40 + nb2pt40cent + mbb90 + photveto100 + dmet200;
  //TCut presel = agednlep1 + agedlep + njmin2pt40 + nb2pt40cent + mbb90 + photveto100 + dmet200;
  //  TCut presel = nlep1 + ptlep40 + etalep + njmin2pt40 + nb2pt40cent + mbb90 + dupjets;
  //  TCut sigsel = presel + nj2;
  //  TCut sigsel = presel + nj2 + mt100 + mct160 + met100;
  //  TCut presel3 = presel2 + st750 + met300;// + mct160 + mt300;
  //TCut presel = nlep1 + ptlep30 + nb2;
  //  TCut sigsel = presel + nj2 + mct160;// + pujetmet200;
  //TCut sigsel = presel + nj2 + mt100 + mct160;// + met200;
  //  TCut sigsel = presel + nj2 + mt100 + mct160 + met200;
  TCut sigsel = presel + nj2 + pujetmt100 + mct160;// + pujetmet200;
  //TCut sigsel = presel + nj2 + smearmt100 + mct160;// + smearmet200;

  TCut plotsel = presel;
  //TCut plotsel = sigsel;

  bool printplots = false;

  //  std::cout << "cuts: " << plotsel.GetTitle() << std::endl;

  //makePlot( samples , names , (char*)"njets"  , (char*) "N_{jets}, p_{T} > 30 GeV"  , "Events"  , TCut(plotsel) , weight , 20 , 0 , 20 , sig_mchi , sig_mlsp , printplots );
   // makePlot( samples , names , (char*)"mt"  , (char*) "M_{T} (GeV)"    , TCut(plotsel+nj2) , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  // makePlot( samples , names , (char*)"mct"  , (char*) "M_{CT} (GeV)"    , TCut(plotsel+nj2+mt100) , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  // makePlot( samples , names , (char*)"met"  , (char*) "E_{T}^{miss} (GeV)"    , TCut(plotsel+nj2+mt100+mct160) , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );


  //  makePlot( samples , names , (char*)"njets"  , (char*) "N_{jets}, pt > 30"    , TCut(plotsel) , weight , 10 , 0 , 10 , sig_mchi , sig_mlsp , printplots );
  //makePlot( samples , names , (char*)"njets40"  , (char*) "N_{jets}, pt > 40"    , TCut(plotsel) , weight , 10 , 0 , 10 , sig_mchi , sig_mlsp , printplots );
  // makePlot( samples , names , (char*)"njetsfwd"  , (char*) "N_{fwd jets}, pt > 30"    , TCut(plotsel) , weight , 10 , 0 , 10 , sig_mchi , sig_mlsp , printplots );
  // makePlot( samples , names , (char*)"njetsfwd40"  , (char*) "N_{fwd jets}, pt > 40"    , TCut(plotsel) , weight , 10 , 0 , 10 , sig_mchi , sig_mlsp , printplots );

  // makePlot( samples , names , (char*)"st"     , (char*) "S_{T} (GeV)" , TCut(plotsel)              , weight , 60 , 0 , 3000 , sig_mchi , sig_mlsp , printplots );
  //  makePlot( samples , names , (char*)"lep1pt"   , (char*) "lepton p_{T} (GeV)" , TCut(plotsel)              , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  // makePlot( samples , names , (char*)"bjet1pt"   , (char*) "leading b-jet p_{T} (GeV)" , TCut(plotsel)              , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  //  makePlot( samples , names , (char*)"met"  , (char*) "E_{T}^{miss} (GeV)"    , TCut(plotsel) , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  //  makePlot( samples , names , (char*)"met"  , (char*) "E_{T}^{miss} (GeV)" , "Events / 50 GeV"   , TCut(plotsel) , weight , 20 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  //  makePlot( samples , names , (char*)"smearmet"  , (char*) "E_{T}^{miss} (GeV)" , "Events / 50 GeV"   , TCut(plotsel) , weight , 20 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  //  makePlot( samples , names , (char*)"pujetmet"  , (char*) "PUJET E_{T}^{miss} (GeV)"    , TCut(plotsel) , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  //  makePlot( samples , names , (char*)"pujetmet"  , (char*) "E_{T}^{miss} (GeV)",  "Events / 50 GeV"   , TCut(plotsel) , weight , 20 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  // makePlot( samples , names , (char*)"mt"  , (char*) "M_{T} (GeV)"    , TCut(plotsel) , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  // makePlot( samples , names , (char*)"pujetmt"  , (char*) "M_{T} (GeV)"  ,  "Events / 50 GeV"   , TCut(plotsel) , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  // makePlot( samples , names , (char*)"smearmt"  , (char*) "smeared M_{T} (GeV)"  ,  "Events / 50 GeV"   , TCut(plotsel) , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  // makePlot( samples , names , (char*)"mct"  , (char*) "M_{CT} (GeV)"    , TCut(plotsel) , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  // // //makePlot( samples , names , (char*)"ptbb" , (char*) "p_{T}(bb) (GeV)" , TCut(plotsel) , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  // makePlot( samples , names , (char*)"mbb"  , (char*) "M_{bb} (GeV)"    , TCut(nlep1 + ptlep30 + nb2cent + met50) , weight , 50 , 0 , 500 , sig_mchi , sig_mlsp , printplots , false );

  //  makePlot( samples , names , (char*)"min(acos(cos(bjet1phi-metphi)),acos(cos(bjet2phi-metphi)))"  , (char*) "min #Delta#phi(jet,MET)"    , TCut(plotsel) , weight , 50 , 0 , 3.14159 , sig_mchi , sig_mlsp , printplots );

  makePlot( samples , names , (char*)"pujetmt"  , (char*) "M_{T} (GeV)", "Events / 50 GeV"    , TCut(plotsel + nj2) , weight , 20 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  makePlot( samples , names , (char*)"mct"  , (char*) "M_{CT} (GeV)", "Events / 50 GeV"    , TCut(plotsel + nj2 + pujetmt100) , weight , 20 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  makePlot( samples , names , (char*)"pujetmet"  , (char*) "E_{T}^{miss} (GeV)", "Events / 50 GeV"    , TCut(plotsel + nj2 + pujetmt100 + mct160) , weight , 20 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );


  // makePlot( samples , names , (char*)"lep1pt"   , (char*) "lepton p_{T} (GeV)" , TCut(plotsel+met300)              , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  // makePlot( samples , names , (char*)"lep1pt"   , (char*) "lepton p_{T} (GeV)" , TCut(plotsel+met400)              , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  // makePlot( samples , names , (char*)"lep1pt"   , (char*) "lepton p_{T} (GeV)" , TCut(plotsel+met500)              , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );

  // makePlot( samples , names , (char*)"lep1pt"   , (char*) "lepton p_{T} (GeV)" , TCut(plotsel+pujetmet200)              , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  // makePlot( samples , names , (char*)"lep1pt"   , (char*) "lepton p_{T} (GeV)" , TCut(plotsel+pujetmet300)              , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  // makePlot( samples , names , (char*)"lep1pt"   , (char*) "lepton p_{T} (GeV)" , TCut(plotsel+pujetmet400)              , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  // makePlot( samples , names , (char*)"lep1pt"   , (char*) "lepton p_{T} (GeV)" , TCut(plotsel+pujetmet500)              , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );

   //  makePlot( samples , names , (char*)"lep1pt"   , (char*) "lepton p_{T} (GeV)" , TCut(plotsel+ptlep30+etalep)              , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
   // makePlot( samples , names , (char*)"lep1pt"   , (char*) "lepton p_{T} (GeV)" , TCut(plotsel+ptlep30+etalep+nlep1)              , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
   // makePlot( samples , names , (char*)"lep1pt"   , (char*) "lepton p_{T} (GeV)" , TCut(plotsel+ptlep30+etalep+nlep1+njmin2pt40)              , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
   // makePlot( samples , names , (char*)"lep1pt"   , (char*) "lepton p_{T} (GeV)" , TCut(plotsel+ptlep30+etalep+nlep1+njmin2pt40+nb2pt40cent)              , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );


  // makePlot( samples , names , (char*)"lep1pt"   , (char*) "lepton p_{T} (GeV)" , TCut(plotsel+met50)              , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  // makePlot( samples , names , (char*)"lep1pt"   , (char*) "lepton p_{T} (GeV)" , TCut(plotsel+met50+nj2)              , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  // makePlot( samples , names , (char*)"lep1pt"   , (char*) "lepton p_{T} (GeV)" , TCut(plotsel+met50+nj2+mt100)              , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  // makePlot( samples , names , (char*)"lep1pt"   , (char*) "lepton p_{T} (GeV)" , TCut(plotsel+met50+nj2+mt100+mct160)              , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  // makePlot( samples , names , (char*)"lep1pt"   , (char*) "lepton p_{T} (GeV)" , TCut(plotsel+met50+nj2+mt100+mct160+met100)              , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  // makePlot( samples , names , (char*)"lep1pt"   , (char*) "lepton p_{T} (GeV)" , TCut(plotsel+met50+nj2+mt100+mct160+met400)              , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );

  // makePlot( samples , names , (char*)"lep1pt"   , (char*) "lepton p_{T} (GeV)" , TCut(plotsel+pujetmet50)              , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  // makePlot( samples , names , (char*)"lep1pt"   , (char*) "lepton p_{T} (GeV)" , TCut(plotsel+pujetmet50+nj2)              , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  // makePlot( samples , names , (char*)"lep1pt"   , (char*) "lepton p_{T} (GeV)" , TCut(plotsel+pujetmet50+nj2+pujetmt100)              , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  // makePlot( samples , names , (char*)"lep1pt"   , (char*) "lepton p_{T} (GeV)" , TCut(plotsel+pujetmet50+nj2+pujetmt100+mct160)              , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  // makePlot( samples , names , (char*)"lep1pt"   , (char*) "lepton p_{T} (GeV)" , TCut(plotsel+pujetmet50+nj2+pujetmt100+mct160+pujetmet100)              , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
  // makePlot( samples , names , (char*)"lep1pt"   , (char*) "lepton p_{T} (GeV)" , TCut(plotsel+pujetmet50+nj2+pujetmt100+mct160+pujetmet400)              , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );

//   makePlot( samples , names , (char*)"mt"  , (char*) "M_{T} (GeV)"    , TCut(plotsel+pujetmt100) , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );
//   makePlot( samples , names , (char*)"pujetmt"  , (char*) "PUJET M_{T} (GeV)"    , TCut(plotsel+mt100) , weight , 50 , 0 , 1000 , sig_mchi , sig_mlsp , printplots );

  std::vector<std::string> selections;

  // selections.push_back((sigsel+pujetmet200).GetTitle());
  // selections.push_back((sigsel+pujetmet300).GetTitle());
  // selections.push_back((sigsel+pujetmet400).GetTitle());
  // selections.push_back((sigsel+pujetmet500).GetTitle());

  // selections.push_back((sigsel+met200).GetTitle());
  // selections.push_back((sigsel+met300).GetTitle());
  // selections.push_back((sigsel+met400).GetTitle());
  // selections.push_back((sigsel+met500).GetTitle());

  selections.push_back((sigsel+smearmet200).GetTitle());
  selections.push_back((sigsel+smearmet300).GetTitle());
  selections.push_back((sigsel+smearmet400).GetTitle());
  selections.push_back((sigsel+smearmet500).GetTitle());

  //  print_table(samples, names, selections, weight, sig_mchi, sig_mlsp);

}
