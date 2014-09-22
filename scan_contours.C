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

void trim_diagonal(TH2F* h) {

  for (unsigned int ix = 1; ix <= h->GetNbinsX(); ++ix) {
    float xval = h->GetXaxis()->GetBinCenter(ix);
    for (unsigned int iy = 1; iy <= h->GetNbinsY(); ++iy) {
      float yval = h->GetYaxis()->GetBinCenter(iy);
      //      if (xval < 50)  h->SetBinContent(ix,iy,0.);
      if (xval - yval < 125.) h->SetBinContent(ix,iy,0.);
    }
  }

  return;
}

void scan_contours(TString infile = "test.root") {

  gROOT->LoadMacro("CMS_lumi.C");

  cmsText     = "CMS Phase II Simulation";
  writeExtraText = false;       // if extra text
  //  extraText  = "Preliminary";  // default extra text is "Preliminary"
  lumi_14TeV = ""; 
  //  lumi_14TeV = "300 fb^{-1}, PU = 50"; // default is "3000 fb^{-1}"
  lumi_14TeV = "3000 fb^{-1}, PU = 140"; // default is "3000 fb^{-1}"

  TCanvas* c1 = new TCanvas("c1","c1",800,600);

  TFile* f = new TFile(infile);
  //  TH2F* h_base = new TH2F("h_base","", 11, -50, 1050, 11, -50, 1050);
  TH2F* h_base = new TH2F("h_base",";m_{#tilde{#chi}_{1}^{#pm}} = m_{#tilde{#chi}_{2}^{0}} (GeV); m_{#tilde{#chi}_{1}^{0}} (GeV)", 90, 100, 1000, 100, 0, 1000);
  h_base->GetXaxis()->SetNdivisions(8,5,0);
  h_base->GetYaxis()->SetNdivisions(8,5,0);
  h_base->Draw();

  // double contours[1] = {1.0};

  // TH2F * contour_12p5 = (TH2F*) h_disc12p5->Clone("contour_12p5");
  // contour_12p5->SetContour(1,contours);
  // contour_12p5->SetLineWidth(3);
  // contour_12p5->SetLineColor(kBlue);
  // contour_12p5->Smooth(1,"k3a");

  // TH2F * contour_25 = (TH2F*) h_disc25->Clone("contour_25");
  // contour_25->SetContour(1,contours);
  // contour_25->SetLineWidth(3);
  // contour_25->SetLineColor(kRed);
  // contour_25->Smooth(1,"k3a");

  double contours_disc[1] = {5.0};
  //  double contours_exc[1] = {2.0};
  double contours_exc[1] = {1.0};

  TH2F * disc_contour_12p5 = (TH2F*) h_signif12p5_all->Clone("disc_contour_12p5");
  disc_contour_12p5->SetContour(1,contours_disc);
  disc_contour_12p5->SetLineWidth(3);
  disc_contour_12p5->SetLineStyle(3);
  disc_contour_12p5->SetLineColor(kBlue);
  disc_contour_12p5->Smooth(1,"k3a");
  //  disc_contour_12p5->Smooth(1,"k5a");
  trim_diagonal(disc_contour_12p5);

  TH2F * disc_contour_25 = (TH2F*) h_signif25_all->Clone("disc_contour_25");
  disc_contour_25->SetContour(1,contours_disc);
  disc_contour_25->SetLineWidth(3);
  disc_contour_25->SetLineColor(kBlue);
  disc_contour_25->Smooth(1,"k3a");
  //disc_contour_25->Smooth(1,"k5a");
  trim_diagonal(disc_contour_25);

  TH2F * exc_contour_12p5 = (TH2F*) h_rinv12p5_all->Clone("exc_contour_12p5");
  //TH2F * exc_contour_12p5 = (TH2F*) h_signif12p5_all->Clone("exc_contour_12p5");
  exc_contour_12p5->SetContour(1,contours_exc);
  exc_contour_12p5->SetLineWidth(3);
  exc_contour_12p5->SetLineStyle(3);
  exc_contour_12p5->SetLineColor(kRed);
  exc_contour_12p5->Smooth(1,"k3a");
  //exc_contour_12p5->Smooth(1,"k5a");
  trim_diagonal(exc_contour_12p5);

  TH2F * exc_contour_25 = (TH2F*) h_rinv25_all->Clone("exc_contour_25");
  //  TH2F * exc_contour_25 = (TH2F*) h_signif25_all->Clone("exc_contour_25");
  exc_contour_25->SetContour(1,contours_exc);
  exc_contour_25->SetLineWidth(3);
  exc_contour_25->SetLineColor(kRed);
  exc_contour_25->Smooth(1,"k3a");
  //exc_contour_25->Smooth(1,"k5a");
  trim_diagonal(exc_contour_25);

  TLine* diag = new TLine(125.,0.,675.,550.);
  //  TLine* diag = new TLine(125.,0.,1000.,875.);
  diag->SetLineWidth(3);
  diag->SetLineStyle(2);
  diag->SetLineColor(kBlack);

  disc_contour_12p5->Draw("cont3 same");
  disc_contour_25->Draw("cont3 same");
  exc_contour_12p5->Draw("cont3 same");
  exc_contour_25->Draw("cont3 same");

  TFile* fold = new TFile("limits_wh.root");
  observed->SetLineColor(kGreen+2);
  observed->Draw("same");

  diag->Draw("same");

  //  TLegend* leg = new TLegend(0.19,0.68,0.54,0.92);
  //TLegend* leg = new TLegend(0.19,0.68,0.54,0.85);
  TLegend* leg = new TLegend(0.19,0.61,0.54,0.85);
  leg->SetFillColor(0);
  leg->SetTextSize(0.035);
  leg->AddEntry(observed,"2012 Observed 95% CL Exclusion ","l");

  leg->AddEntry(exc_contour_12p5,"3000fb^{-1} 95% CL Exclusion, 12.5% syst","l");
  leg->AddEntry(exc_contour_25,"3000fb^{-1} 95% CL Exclusion, 25% syst","l");
  leg->AddEntry(disc_contour_12p5,"3000fb^{-1} 5#sigma Discovery, 12.5% syst","l");
  leg->AddEntry(disc_contour_25,"3000fb^{-1} 5#sigma Discovery, 25% syst","l");

  // leg->AddEntry(exc_contour_12p5,"300fb^{-1} 95% CL Exclusion, 12.5% syst","l");
  // leg->AddEntry(exc_contour_25,"300fb^{-1} 95% CL Exclusion, 25% syst","l");
  // leg->AddEntry(disc_contour_12p5,"300fb^{-1} 5#sigma Discovery, 12.5% syst","l");
  // leg->AddEntry(disc_contour_25,"300fb^{-1} 5#sigma Discovery, 25% syst","l");

  leg->Draw("same");

  CMS_lumi( c1, iPeriod, iPos );

  gPad->SetRightMargin(0.05);
  gPad->Modified();
}

void combine_contours(TString infile1 = "results_V00-00-12_nopujetid_PhaseI__50PU.root", TString infile2 = "results_V00-00-12_PhaseII__140PU_cleaning.root") {

  gROOT->LoadMacro("CMS_lumi.C");

  cmsText     = "CMS Phase I/II Simulation";
  writeExtraText = false;       // if extra text
  //  extraText  = "Preliminary";  // default extra text is "Preliminary"
  lumi_14TeV = "300-3000 fb^{-1}, PU = 50-140"; 
  //  lumi_14TeV = "300 fb^{-1}, PU = 50"; // default is "3000 fb^{-1}"
  //  lumi_14TeV = "3000 fb^{-1}, PU = 140"; // default is "3000 fb^{-1}"

  TCanvas* c1 = new TCanvas("c1","c1",800,600);

  TFile* f1 = new TFile(infile1);
  TFile* f2 = new TFile(infile2);
  TH2F* h_base = new TH2F("h_base",";m_{#tilde{#chi}_{1}^{#pm}} = m_{#tilde{#chi}_{2}^{0}} (GeV); m_{#tilde{#chi}_{1}^{0}} (GeV)", 90, 100, 1000, 100, 0, 1000);
  h_base->GetXaxis()->SetNdivisions(8,5,0);
  h_base->GetYaxis()->SetNdivisions(8,5,0);
  h_base->Draw();

  double contours_disc[1] = {5.0};
  double contours_exc[1] = {1.0};

  f2->cd();
  TH2F * disc_contour_12p5_PhaseII = (TH2F*) h_signif12p5_all->Clone("disc_contour_12p5_PhaseII");
  disc_contour_12p5_PhaseII->SetContour(1,contours_disc);
  disc_contour_12p5_PhaseII->SetLineWidth(3);
  disc_contour_12p5_PhaseII->SetLineStyle(3);
  disc_contour_12p5_PhaseII->SetLineColor(kBlue);
  disc_contour_12p5_PhaseII->Smooth(1,"k3a");
  //  disc_contour_12p5_PhaseII->Smooth(1,"k5a");
  trim_diagonal(disc_contour_12p5_PhaseII);

  f2->cd();
  TH2F * exc_contour_12p5_PhaseII = (TH2F*) h_rinv12p5_all->Clone("exc_contour_12p5_PhaseII");
  //TH2F * exc_contour_12p5_PhaseII = (TH2F*) h_signif12p5_all->Clone("exc_contour_12p5_PhaseII");
  exc_contour_12p5_PhaseII->SetContour(1,contours_exc);
  exc_contour_12p5_PhaseII->SetLineWidth(3);
  exc_contour_12p5_PhaseII->SetLineStyle(1);
  exc_contour_12p5_PhaseII->SetLineColor(kBlue);
  exc_contour_12p5_PhaseII->Smooth(1,"k3a");
  //exc_contour_12p5_PhaseII->Smooth(1,"k5a");
  trim_diagonal(exc_contour_12p5_PhaseII);

  f1->cd();
  TH2F * exc_contour_12p5_PhaseI = (TH2F*) h_rinv12p5_all->Clone("exc_contour_12p5_PhaseI");
  //TH2F * exc_contour_12p5_PhaseI = (TH2F*) h_signif12p5_all->Clone("exc_contour_12p5_PhaseI");
  exc_contour_12p5_PhaseI->SetContour(1,contours_exc);
  exc_contour_12p5_PhaseI->SetLineWidth(3);
  exc_contour_12p5_PhaseI->SetLineStyle(1);
  exc_contour_12p5_PhaseI->SetLineColor(kRed);
  exc_contour_12p5_PhaseI->Smooth(1,"k3a");
  //exc_contour_12p5_PhaseI->Smooth(1,"k5a");
  trim_diagonal(exc_contour_12p5_PhaseI);

  TLine* diag = new TLine(125.,0.,675.,550.);
  //  TLine* diag = new TLine(125.,0.,1000.,875.);
  diag->SetLineWidth(3);
  diag->SetLineStyle(2);
  diag->SetLineColor(kBlack);

  exc_contour_12p5_PhaseI->Draw("cont3 same");
  exc_contour_12p5_PhaseII->Draw("cont3 same");
  disc_contour_12p5_PhaseII->Draw("cont3 same");

  TFile* fold = new TFile("limits_wh.root");
  observed->SetLineColor(kGreen+2);
  observed->Draw("same");

  diag->Draw("same");

  //  TLegend* leg = new TLegend(0.19,0.68,0.54,0.92);
    TLegend* leg = new TLegend(0.19,0.61,0.54,0.85);
  leg->SetFillColor(0);
  leg->SetTextSize(0.035);
  leg->AddEntry(observed,"2012 Observed 95% CL Exclusion ","l");

  leg->AddEntry(exc_contour_12p5_PhaseI,"300fb^{-1} 95% CL Exclusion","l");
  leg->AddEntry(exc_contour_12p5_PhaseII,"3000fb^{-1} 95% CL Exclusion","l");
  leg->AddEntry(disc_contour_12p5_PhaseII,"3000fb^{-1} 5#sigma Discovery","l");

  leg->Draw("same");

  CMS_lumi( c1, iPeriod, iPos );

  gPad->SetRightMargin(0.05);
  gPad->Modified();
}

void combine_brs(TString infile1 = "results_V00-00-12_PhaseII__140PU_cleaning_br50.root", TString infile2 = "results_V00-00-12_PhaseII__140PU_cleaning.root") {

  gROOT->LoadMacro("CMS_lumi.C");

  cmsText     = "CMS Phase II Simulation";
  writeExtraText = false;       // if extra text
  //  extraText  = "Preliminary";  // default extra text is "Preliminary"
  //  lumi_14TeV = "300 fb^{-1}, PU = 50"; // default is "3000 fb^{-1}"
  lumi_14TeV = "3000 fb^{-1}, PU = 140"; // default is "3000 fb^{-1}"

  TCanvas* c1 = new TCanvas("c1","c1",800,600);

  TFile* f1 = new TFile(infile1);
  TFile* f2 = new TFile(infile2);
  TH2F* h_base = new TH2F("h_base",";m_{#tilde{#chi}_{1}^{#pm}} = m_{#tilde{#chi}_{2}^{0}} (GeV); m_{#tilde{#chi}_{1}^{0}} (GeV)", 90, 100, 1000, 100, 0, 1000);
  h_base->GetXaxis()->SetNdivisions(8,5,0);
  h_base->GetYaxis()->SetNdivisions(8,5,0);
  h_base->Draw();

  double contours_disc[1] = {5.0};
  double contours_exc[1] = {1.0};

  f2->cd();
  TH2F * disc_contour_12p5_br1 = (TH2F*) h_signif12p5_all->Clone("disc_contour_12p5_br1");
  disc_contour_12p5_br1->SetContour(1,contours_disc);
  disc_contour_12p5_br1->SetLineWidth(3);
  disc_contour_12p5_br1->SetLineStyle(3);
  disc_contour_12p5_br1->SetLineColor(kBlue);
  disc_contour_12p5_br1->Smooth(1,"k3a");
  //  disc_contour_12p5_br1->Smooth(1,"k5a");
  trim_diagonal(disc_contour_12p5_br1);

  f2->cd();
  TH2F * exc_contour_12p5_br1 = (TH2F*) h_rinv12p5_all->Clone("exc_contour_12p5_br1");
  //TH2F * exc_contour_12p5_br1 = (TH2F*) h_signif12p5_all->Clone("exc_contour_12p5_br1");
  exc_contour_12p5_br1->SetContour(1,contours_exc);
  exc_contour_12p5_br1->SetLineWidth(3);
  exc_contour_12p5_br1->SetLineStyle(1);
  exc_contour_12p5_br1->SetLineColor(kBlue);
  exc_contour_12p5_br1->Smooth(1,"k3a");
  //exc_contour_12p5_br1->Smooth(1,"k5a");
  trim_diagonal(exc_contour_12p5_br1);

  f1->cd();
  TH2F * disc_contour_12p5_br50 = (TH2F*) h_signif12p5_all->Clone("disc_contour_12p5_br50");
  disc_contour_12p5_br50->SetContour(1,contours_disc);
  disc_contour_12p5_br50->SetLineWidth(3);
  disc_contour_12p5_br50->SetLineStyle(3);
  disc_contour_12p5_br50->SetLineColor(kMagenta);
  disc_contour_12p5_br50->Smooth(1,"k3a");
  //  disc_contour_12p5_br50->Smooth(1,"k5a");
  trim_diagonal(disc_contour_12p5_br50);

  f1->cd();
  TH2F * exc_contour_12p5_br50 = (TH2F*) h_rinv12p5_all->Clone("exc_contour_12p5_br50");
  //TH2F * exc_contour_12p5_br50 = (TH2F*) h_signif12p5_all->Clone("exc_contour_12p5_br50");
  exc_contour_12p5_br50->SetContour(1,contours_exc);
  exc_contour_12p5_br50->SetLineWidth(3);
  exc_contour_12p5_br50->SetLineStyle(1);
  exc_contour_12p5_br50->SetLineColor(kMagenta);
  exc_contour_12p5_br50->Smooth(1,"k3a");
  //exc_contour_12p5_br50->Smooth(1,"k5a");
  trim_diagonal(exc_contour_12p5_br50);

  TLine* diag = new TLine(125.,0.,675.,550.);
  //  TLine* diag = new TLine(125.,0.,1000.,875.);
  diag->SetLineWidth(3);
  diag->SetLineStyle(2);
  diag->SetLineColor(kBlack);

  exc_contour_12p5_br50->Draw("cont3 same");
  disc_contour_12p5_br50->Draw("cont3 same");
  exc_contour_12p5_br1->Draw("cont3 same");
  disc_contour_12p5_br1->Draw("cont3 same");

  diag->Draw("same");

  //  TLegend* leg = new TLegend(0.19,0.68,0.54,0.92);
    TLegend* leg = new TLegend(0.19,0.61,0.54,0.85);
  leg->SetFillColor(0);
  leg->SetTextSize(0.035);
  leg->AddEntry(exc_contour_12p5_br1,"3000fb^{-1} 95% CL Exclusion, BR = 1.0","l");
  leg->AddEntry(disc_contour_12p5_br1,"3000fb^{-1} 5#sigma Discovery, BR = 1.0","l");
  leg->AddEntry(exc_contour_12p5_br50,"3000fb^{-1} 95% CL Exclusion, BR = 0.5","l");
  leg->AddEntry(disc_contour_12p5_br50,"3000fb^{-1} 5#sigma Discovery, BR = 0.5","l");

  leg->Draw("same");

  CMS_lumi( c1, iPeriod, iPos );

  gPad->SetRightMargin(0.05);
  gPad->Modified();
}

void compare_aged(TString infile1 = "results_V00-00-12_PhaseII__140PU_cleaning_aged_1ab.root", TString infile2 = "results_V00-00-12_PhaseII__140PU_cleaning_1ab.root") {

  gROOT->LoadMacro("CMS_lumi.C");

  cmsText     = "CMS Phase II Simulation";
  writeExtraText = false;       // if extra text
  //  extraText  = "Preliminary";  // default extra text is "Preliminary"
  //  lumi_14TeV = "300 fb^{-1}, PU = 50"; // default is "3000 fb^{-1}"
  lumi_14TeV = "1000 fb^{-1}, PU = 140"; // default is "3000 fb^{-1}"

  TCanvas* c1 = new TCanvas("c1","c1",800,600);

  TFile* f1 = new TFile(infile1);
  TFile* f2 = new TFile(infile2);
  TH2F* h_base = new TH2F("h_base",";m_{#tilde{#chi}_{1}^{#pm}} = m_{#tilde{#chi}_{2}^{0}} (GeV); m_{#tilde{#chi}_{1}^{0}} (GeV)", 90, 100, 1000, 100, 0, 1000);
  h_base->GetXaxis()->SetNdivisions(8,5,0);
  h_base->GetYaxis()->SetNdivisions(8,5,0);
  h_base->Draw();

  double contours_disc[1] = {5.0};
  double contours_exc[1] = {1.0};

  f2->cd();
  TH2F * disc_contour_12p5 = (TH2F*) h_signif12p5_all->Clone("disc_contour_12p5");
  disc_contour_12p5->SetContour(1,contours_disc);
  disc_contour_12p5->SetLineWidth(3);
  disc_contour_12p5->SetLineStyle(3);
  disc_contour_12p5->SetLineColor(kBlue);
  disc_contour_12p5->Smooth(1,"k3a");
  //  disc_contour_12p5->Smooth(1,"k5a");
  trim_diagonal(disc_contour_12p5);

  f2->cd();
  TH2F * exc_contour_12p5 = (TH2F*) h_rinv12p5_all->Clone("exc_contour_12p5");
  //TH2F * exc_contour_12p5 = (TH2F*) h_signif12p5_all->Clone("exc_contour_12p5");
  exc_contour_12p5->SetContour(1,contours_exc);
  exc_contour_12p5->SetLineWidth(3);
  exc_contour_12p5->SetLineStyle(1);
  exc_contour_12p5->SetLineColor(kBlue);
  exc_contour_12p5->Smooth(1,"k3a");
  //exc_contour_12p5->Smooth(1,"k5a");
  trim_diagonal(exc_contour_12p5);

  f1->cd();
  TH2F * disc_contour_12p5_aged = (TH2F*) h_signif12p5_all->Clone("disc_contour_12p5_aged");
  disc_contour_12p5_aged->SetContour(1,contours_disc);
  disc_contour_12p5_aged->SetLineWidth(3);
  disc_contour_12p5_aged->SetLineStyle(3);
  disc_contour_12p5_aged->SetLineColor(kOrange+10);
  disc_contour_12p5_aged->Smooth(1,"k3a");
  //  disc_contour_12p5_aged->Smooth(1,"k5a");
  trim_diagonal(disc_contour_12p5_aged);

  f1->cd();
  TH2F * exc_contour_12p5_aged = (TH2F*) h_rinv12p5_all->Clone("exc_contour_12p5_aged");
  //TH2F * exc_contour_12p5_aged = (TH2F*) h_signif12p5_all->Clone("exc_contour_12p5_aged");
  exc_contour_12p5_aged->SetContour(1,contours_exc);
  exc_contour_12p5_aged->SetLineWidth(3);
  exc_contour_12p5_aged->SetLineStyle(1);
  exc_contour_12p5_aged->SetLineColor(kOrange+10);
  exc_contour_12p5_aged->Smooth(1,"k3a");
  //exc_contour_12p5_aged->Smooth(1,"k5a");
  trim_diagonal(exc_contour_12p5_aged);

  TLine* diag = new TLine(125.,0.,675.,550.);
  //  TLine* diag = new TLine(125.,0.,1000.,875.);
  diag->SetLineWidth(3);
  diag->SetLineStyle(2);
  diag->SetLineColor(kBlack);

  exc_contour_12p5_aged->Draw("cont3 same");
  disc_contour_12p5_aged->Draw("cont3 same");
  exc_contour_12p5->Draw("cont3 same");
  disc_contour_12p5->Draw("cont3 same");

  diag->Draw("same");

  //  TLegend* leg = new TLegend(0.19,0.68,0.54,0.92);
    TLegend* leg = new TLegend(0.19,0.61,0.54,0.85);
  leg->SetFillColor(0);
  leg->SetTextSize(0.035);
  leg->AddEntry(exc_contour_12p5,"1000fb^{-1} 95% CL Exclusion","l");
  leg->AddEntry(disc_contour_12p5,"1000fb^{-1} 5#sigma Discovery","l");
  leg->AddEntry(exc_contour_12p5_aged,"1000fb^{-1} 95% CL Exclusion,  Aged Detector","l");
  leg->AddEntry(disc_contour_12p5_aged,"1000fb^{-1} 5#sigma Discovery,  Aged Detector","l");

  leg->Draw("same");

  CMS_lumi( c1, iPeriod, iPos );

  gPad->SetRightMargin(0.05);
  gPad->Modified();
}

