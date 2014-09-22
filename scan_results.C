#include <iostream>
#include <utility>
#include <vector>
#include <fstream>

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

// #include "TFile.h"
// #include "TCut.h"
// #include "TString.h"
// #include "TH1.h"
// #include "TH2.h"

// bool write_yields = true;
// bool write_signif = true;
// bool write_rinv = true;

void scan_results(TString infile = "output/V00-00-12/skim_1lpt30_2b_aged/TChiWH14Pythia_PhaseII__140PU_baby.root", TString output = "test.root", float br = 1.0) {

  TFile* f = new TFile(infile);
  TTree* t = f->Get("t");

  TFile* fout = new TFile(output,"RECREATE");

  ofstream out_yields("yields.txt");
  ofstream out_signif("signif.txt");
  ofstream out_rinv("rinv.txt");

  ofstream out_signif_syst25("signif_syst25.txt");
  ofstream out_rinv_syst25("rinv_syst25.txt");


  // -----------------------------
  //  cuts

  TCut nlep1("nleps==1");
  TCut ptlep40("lep1pt>40");
  TCut etalep("abs(lep1eta) < 2.4");
  TCut agednlep1("agednleps==1");
  TCut agedptlep40("agedlep1pt>40");
  TCut agedetalep("abs(agedlep1eta) < 2.4");
  TCut agedmu("agedlep1pt>35 && abs(agedlep1eta) < 1.1 && leptype == 1");
  TCut agedel("agedlep1pt>50 && abs(agedlep1eta) < 2.4 && leptype == 0");
  TCut agedlep = agedmu || agedel;
  TCut njmin2pt40("njets40>=2");
  TCut nb2("nb==2");
  TCut nb2pt40cent("nb==2 && bjet1pt > 40. && bjet2pt > 40. &&  abs(bjet1eta) < 2.4 && abs(bjet2eta) < 2.4");
  TCut nj2("njets==2");
  TCut mt100("mt > 100.0");
  TCut pujetmt100("pujetmt > 100.0");
  TCut smearmt100("smearmt > 100.0");
  TCut met200("met > 200.0");
  TCut met300("met > 300.0");
  TCut met400("met > 400.0");
  TCut met500("met > 500.0");
  TCut pujetmet200("pujetmet > 200.0");
  TCut pujetmet300("pujetmet > 300.0");
  TCut pujetmet400("pujetmet > 400.0");
  TCut pujetmet500("pujetmet > 500.0");
  TCut smearmet200("smearmet > 200.0");
  TCut smearmet300("smearmet > 300.0");
  TCut smearmet400("smearmet > 400.0");
  TCut smearmet500("smearmet > 500.0");
  TCut mct160("mct > 160.0");
  TCut mbb90("mbb > 90.0 && mbb < 150.0");
  TCut photveto100("phot1pt < 100.");
  TCut dmet200("abs(met - pujetmet)< 200.0");

  // TCut weight("3000. * weight * genweight * bgweight");
  // //  TCut weight("1000. * weight * genweight * bgweight");
  // //TCut presel = nlep1 + ptlep40 + etalep + njmin2pt40 + nb2pt40cent + mbb90;
  // TCut presel = nlep1 + ptlep40 + etalep + njmin2pt40 + nb2pt40cent + mbb90 + photveto100 + dmet200;
  // TCut sigsel = presel + nj2 + pujetmt100 + mct160;
  // TCut sig200 = sigsel + pujetmet200;
  // TCut sig300 = sigsel + pujetmet300;
  // TCut sig400 = sigsel + pujetmet400;
  // TCut sig500 = sigsel + pujetmet500;

  // --- aged detector
  TCut weight("1000. * weight * genweight * bgweight * agedweight");
  TCut presel = agednlep1 + agedlep + njmin2pt40 + nb2pt40cent + mbb90 + photveto100 + dmet200;
  TCut sigsel = presel + nj2 + smearmt100 + mct160;
  TCut sig200 = sigsel + smearmet200;
  TCut sig300 = sigsel + smearmet300;
  TCut sig400 = sigsel + smearmet400;
  TCut sig500 = sigsel + smearmet500;

  const unsigned int nregs = 4;
  TCut sigregs[nregs] = {sig200, sig300, sig400, sig500};

  // TCut weight("300. * weight * genweight * bgweight");
  // TCut presel = nlep1 + ptlep40 + etalep + njmin2pt40 + nb2pt40cent + mbb90;
  // TCut sigsel = presel + nj2 + mt100 + mct160;
  // TCut sig200 = sigsel + met200;
  // TCut sig300 = sigsel + met300;
  // TCut sig400 = sigsel + met400;

  // const unsigned int nregs = 3;
  // TCut sigregs[nregs] = {sig200, sig300, sig400};

  //----------------------------------------------

  // background results
  std::vector<float> bg_yields;

  //  // numbers with additional MET cleaning, PhaseII 140PU
  // bg_yields.push_back(1408.);
  // bg_yields.push_back(354.);
  // bg_yields.push_back(39.);
  // bg_yields.push_back(7.5);

   // numbers with additional MET cleaning, PhaseII 140PU
  // for 1000/fb
  // bg_yields.push_back(469.);
  // bg_yields.push_back(118.);
  // bg_yields.push_back(13.);
  // bg_yields.push_back(2.5);

  // numbers with additional MET cleaning, PhaseII 140PU, AGED detector
  // for 1000/fb
  bg_yields.push_back(605.);
  bg_yields.push_back(119.);
  bg_yields.push_back(14.);
  bg_yields.push_back(3.4);

  // // numbers from PhaseI 50PU
  // bg_yields.push_back(129.);
  // bg_yields.push_back(27.);
  // bg_yields.push_back(3.7.);

  // // limits on nevents, from LandS with no signal systs, PhaseII 140PU
  // std::vector<float> limits_25;
  // limits_25.push_back(534.);
  // limits_25.push_back(145.);
  // limits_25.push_back(24.9);
  // limits_25.push_back(10.7);

  // std::vector<float> limits_12p5;
  // limits_12p5.push_back(307.);
  // limits_12p5.push_back(88.);
  // limits_12p5.push_back(18.9);
  // limits_12p5.push_back(9.6);

  // // // limits on nevents, from LandS with no signal systs, PhaseII 140PU
  // // // with additional met cleaning
  // std::vector<float> limits_25;
  // limits_25.push_back(505.);
  // limits_25.push_back(130.);
  // limits_25.push_back(19.5);
  // limits_25.push_back(7.2);

  // std::vector<float> limits_12p5;
  // limits_12p5.push_back(287.);
  // limits_12p5.push_back(80.);
  // limits_12p5.push_back(15.6);
  // limits_12p5.push_back(6.9);

  // // limits on nevents, from LandS with no signal systs, PhaseII 140PU
  // // with additional met cleaning
  // // for 1000/fb
  // std::vector<float> limits_25;
  // limits_25.push_back(171.);
  // limits_25.push_back(47.4);
  // limits_25.push_back(9.7);
  // limits_25.push_back(4.6);

  // std::vector<float> limits_12p5;
  // limits_12p5.push_back(103.);
  // limits_12p5.push_back(32.5);
  // limits_12p5.push_back(8.7);
  // limits_12p5.push_back(4.5);

  // limits on nevents, from LandS with no signal systs, PhaseII 140PU, AGED detector
  // with additional met cleaning
  // for 1000/fb
  std::vector<float> limits_25;
  limits_25.push_back(218.);
  limits_25.push_back(47.9);
  limits_25.push_back(10.2);
  limits_25.push_back(5.1);

  std::vector<float> limits_12p5;
  limits_12p5.push_back(130.);
  limits_12p5.push_back(32.7);
  limits_12p5.push_back(9.1);
  limits_12p5.push_back(5.0);

  // // limits on nevents, from LandS with no signal systs, PhaseI 50PU
  // std::vector<float> limits_25;
  // limits_25.push_back(51.4);
  // limits_25.push_back(15.1);
  // limits_25.push_back(5.3);

  // std::vector<float> limits_12p5;
  // limits_12p5.push_back(34.5);
  // limits_12p5.push_back(12.7);
  // limits_12p5.push_back(5.2);

  TH2F* h_base = new TH2F("h_base","", 11, -50, 1050, 11, -50, 1050);
  //  TH2F* h_base = new TH2F("h_base","", 22, -50, 1050, 22, -50, 1050);

  TH2F* hists_yields[nregs];
  TH2F* hists_signif_25[nregs];
  TH2F* hists_signif_12p5[nregs];
  TH2F* hists_rinv_25[nregs];
  TH2F* hists_rinv_12p5[nregs];

  for (unsigned int ireg = 0; ireg < nregs; ++ireg) {
    TString histname = Form("h_yields_%d",ireg);
    TH2F* h_yields = h_base->Clone(histname);
    t->Draw("mlsp:mchi>>"+histname,sigregs[ireg]*weight);
    hists_yields[ireg] = h_yields;
    h_yields->Write();

    TString histname_signif25 = Form("h_signif25_%d",ireg);
    TH2F* h_signif25 = h_base->Clone(histname_signif25);
    TString histname_rinv25 = Form("h_rinv25_%d",ireg);
    TH2F* h_rinv25 = h_base->Clone(histname_rinv25);

    TString histname_signif12p5 = Form("h_signif12p5_%d",ireg);
    TH2F* h_signif12p5 = h_base->Clone(histname_signif12p5);
    TString histname_rinv12p5 = Form("h_rinv12p5_%d",ireg);
    TH2F* h_rinv12p5 = h_base->Clone(histname_rinv12p5);

    for (unsigned int ix = 1; ix <= h_yields->GetNbinsX(); ++ix) {
      for (unsigned int iy = 1; iy <= h_yields->GetNbinsY(); ++iy) {
	// skip empty bins
	float nsig = h_yields->GetBinContent(ix,iy) * br;
	float nbg = bg_yields.at(ireg);
	if (nsig < 0.001) continue;
	float zbi_val_25 = RooStats::NumberCountingUtils::BinomialObsZ(nsig+nbg,nbg,0.25);
	h_signif25->SetBinContent(ix,iy,zbi_val_25);
	h_rinv25->SetBinContent(ix,iy,nsig/limits_25.at(ireg));
	float zbi_val_12p5 = RooStats::NumberCountingUtils::BinomialObsZ(nsig+nbg,nbg,0.125);
	h_signif12p5->SetBinContent(ix,iy,zbi_val_12p5);
	h_rinv12p5->SetBinContent(ix,iy,nsig/limits_12p5.at(ireg));
      } // y bins
    } // x bins
    hists_signif_25[ireg] = h_signif25;
    h_signif25->Write();
    hists_signif_12p5[ireg] = h_signif12p5;
    h_signif12p5->Write();
    hists_rinv_25[ireg] = h_rinv25;
    h_rinv25->Write();
    hists_rinv_12p5[ireg] = h_rinv12p5;
    h_rinv12p5->Write();

  } // loop over signal regions

  TH2F* h_signif25_best = h_base->Clone("h_signif25_best");
  TH2F* h_rinv25_best = h_base->Clone("h_rinv25_best");
  TH2F* h_signif25_all = h_base->Clone("h_signif25_all");
  TH2F* h_rinv25_all = h_base->Clone("h_rinv25_all");
  TH2F* h_disc25 = h_base->Clone("h_disc25");
  TH2F* h_exc25 = h_base->Clone("h_exc25");

  TH2F* h_signif12p5_best = h_base->Clone("h_signif12p5_best");
  TH2F* h_rinv12p5_best = h_base->Clone("h_rinv12p5_best");
  TH2F* h_signif12p5_all = h_base->Clone("h_signif12p5_all");
  TH2F* h_rinv12p5_all = h_base->Clone("h_rinv12p5_all");
  TH2F* h_disc12p5 = h_base->Clone("h_disc12p5");
  TH2F* h_exc12p5 = h_base->Clone("h_exc12p5");

  // out_yields << "C1   N1    BKg  TChiWH" << endl;
  // out_signif << "C1   N1    Signif" << endl;
  // out_rinv << "C1   N1    Rinv" << endl;

  // for each point, find signal region with best expected significance
  for (unsigned int ix = 1; ix <= h_base->GetNbinsX(); ++ix) {
    for (unsigned int iy = 1; iy <= h_base->GetNbinsY(); ++iy) {

      int c1 = h_signif12p5_all->GetXaxis()->GetBinCenter(ix);
      int n1 = h_signif12p5_all->GetYaxis()->GetBinCenter(iy);
      if (c1 == 100) c1 = 130;
      if (n1 == 0) n1 = 1;
      else if (c1-n1 == 100) n1 = c1 - 130;
      //      cout << Form("%d  %d",c1,n1) << endl;

      float max_signif_25 = 0.;
      float max_signif_12p5 = 0.;
      int best_signif_25 = -1;
      int best_signif_12p5 = -1;

      // float max_rinv_25 = 999999.;
      // float max_rinv_12p5 = 999999.;
      float max_rinv_25 = 0.;
      float max_rinv_12p5 = 0.;
      int best_rinv_25 = -1;
      int best_rinv_12p5 = -1;
      for (unsigned int ireg = 0; ireg < nregs; ++ireg) {
	float signif_25 = hists_signif_25[ireg]->GetBinContent(ix,iy);
	if (signif_25 > max_signif_25) {
	  max_signif_25 = signif_25;
	  best_signif_25 = ireg+1;
	}

	float rinv_25 = hists_rinv_25[ireg]->GetBinContent(ix,iy);
	//	if ((rinv_25 < max_rinv_25) && (rinv_25 > 0.0001)) {
	if (rinv_25 > max_rinv_25) {
	  max_rinv_25 = rinv_25;
	  best_rinv_25 = ireg+1;
	}

	float signif_12p5 = hists_signif_12p5[ireg]->GetBinContent(ix,iy);
	if (signif_12p5 > max_signif_12p5) {
	  max_signif_12p5 = signif_12p5;
	  best_signif_12p5 = ireg+1;
	}

	float rinv_12p5 = hists_rinv_12p5[ireg]->GetBinContent(ix,iy);
	//	if ((rinv_12p5 < max_rinv_12p5) && (rinv_12p5 > 0.0001) ) {
	if (rinv_12p5 > max_rinv_12p5 ) {
	  max_rinv_12p5 = rinv_12p5;
	  best_rinv_12p5 = ireg+1;
	}

      } // sig regions

      if (best_signif_25 >= 1) {
	h_signif25_all->SetBinContent(ix,iy,max_signif_25);
	h_signif25_best->SetBinContent(ix,iy,best_signif_25);
	if (max_signif_25 >= 5.0) h_disc25->SetBinContent(ix,iy,1.);
	out_signif_syst25 << Form("%d  %d    %.3f",c1,n1,max_signif_25) << endl;
      }

      if (best_rinv_25 >= 1) {
	h_rinv25_all->SetBinContent(ix,iy,max_rinv_25);
	h_rinv25_best->SetBinContent(ix,iy,best_rinv_25);
	//	if (max_rinv_25 <= 1.0) h_exc25->SetBinContent(ix,iy,1.);
	if (max_rinv_25 >= 1.0) h_exc25->SetBinContent(ix,iy,1.);
	out_rinv_syst25 << Form("%d  %d    %.3f",c1,n1,max_rinv_25) << endl;
      }

      if (best_signif_12p5 >= 1) {
	h_signif12p5_all->SetBinContent(ix,iy,max_signif_12p5);
	h_signif12p5_best->SetBinContent(ix,iy,best_signif_12p5);
	if (max_signif_12p5 >= 5.0) h_disc12p5->SetBinContent(ix,iy,1.);
	float nsig = hists_yields[best_signif_12p5-1]->GetBinContent(ix,iy) * br;
	float nbg = bg_yields.at(best_signif_12p5-1);
	out_yields << Form("%d  %d    %.1f    %.1f",c1,n1,nbg,nsig) << endl;
	out_signif << Form("%d  %d    %.3f",c1,n1,max_signif_12p5) << endl;
      }

      if (best_rinv_12p5 >= 1) {
	h_rinv12p5_all->SetBinContent(ix,iy,max_rinv_12p5);
	h_rinv12p5_best->SetBinContent(ix,iy,best_rinv_12p5);
	//	if (max_rinv_12p5 <= 1.0) h_exc12p5->SetBinContent(ix,iy,1.);
	if (max_rinv_12p5 >= 1.0) h_exc12p5->SetBinContent(ix,iy,1.);
	out_rinv << Form("%d  %d    %.3f",c1,n1,max_rinv_12p5) << endl;
      }

    } // y bins
  } // x bins

  // fix a couple bins by hand
  h_disc25->SetBinContent(2,1,0.);

  h_signif25_best->Write();
  h_signif25_all->Write();
  h_disc25->Write();
  h_rinv25_best->Write();
  h_rinv25_all->Write();
  h_exc25->Write();

  h_signif12p5_best->Write();
  h_signif12p5_all->Write();
  h_disc12p5->Write();
  h_rinv12p5_best->Write();
  h_rinv12p5_all->Write();
  h_exc12p5->Write();

  //  fout->Write();
  fout->Close();

  out_yields.close();
  out_signif.close();
  out_rinv.close();
}

