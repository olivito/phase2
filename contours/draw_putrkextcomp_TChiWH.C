#include "TLatex.h"
#include "TString.h"
#include "TH2.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TFile.h"

const int iPeriod = 14;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV, 14= PU=140,14TeV 

  // second parameter in example_plot is iPos, which drives the position of the CMS logo in the plot
  // iPos=11 : top-left, left-aligned
  // iPos=33 : top-right, right-aligned
  // iPos=22 : center, centered
  // mode generally : 
  //   iPos = 10*(alignement 1/2/3) + position (1/2/3 = left/center/right)

const int iPos = 33;

void draw_putrkextcomp_TChiWH(TString infile = "contours_TChiWH.root") {

  gROOT->LoadMacro("CMS_lumi_v2.C");

  cmsText     = "CMS Phase II Delphes Simulation";
  extraText = ""; // remove Preliminary
  writeExtraText = false;       // if extra text
  lumi_14TeV = "PU = 140/200"; // default is "3000 fb^{-1}"

  TCanvas* c1 = new TCanvas("c1","c1",800,600);
  c1->cd();
  gPad->SetTopMargin(0.08);
  gPad->SetRightMargin(0.05);

  TFile* f = new TFile(infile);
  TH2F* h_base = new TH2F("h_base",";m_{#tilde{#chi}_{1}^{#pm}} = m_{#tilde{#chi}_{2}^{0}} (GeV); m_{#tilde{#chi}_{1}^{0}} (GeV)", 90, 100, 1000, 100, 0, 1000);
  h_base->GetXaxis()->SetNdivisions(8,5,0);
  h_base->GetYaxis()->SetNdivisions(8,5,0);
  h_base->SetLabelSize(0.05, "XYZ");
  h_base->SetTitleSize(0.06,"Y");
  h_base->Draw();

  g_signif_PhaseII_3000fb->SetLineWidth(3);
  g_signif_PhaseII_3000fb->SetLineStyle(1);
  g_signif_PhaseII_3000fb->SetLineColor(kRed);
  g_signif_PhaseII_3000fb->Draw("l same");

  // g_signif_PhaseII_PU200_3000fb->SetLineWidth(3);
  // g_signif_PhaseII_PU200_3000fb->SetLineStyle(1);
  // g_signif_PhaseII_PU200_3000fb->SetLineColor(kGreen-2);
  // g_signif_PhaseII_PU200_3000fb->Draw("l same");

  g_signif_PhaseII_PU200_4000fb->SetLineWidth(3);
  g_signif_PhaseII_PU200_4000fb->SetLineStyle(1);
  g_signif_PhaseII_PU200_4000fb->SetLineColor(kMagenta);
  g_signif_PhaseII_PU200_4000fb->Draw("l same");

  g_signif_PhaseII_NoTrkExt_3000fb->SetLineWidth(3);
  g_signif_PhaseII_NoTrkExt_3000fb->SetLineStyle(1);
  g_signif_PhaseII_NoTrkExt_3000fb->SetLineColor(kBlue);
  g_signif_PhaseII_NoTrkExt_3000fb->Draw("l same");

  TLine* diag = new TLine(125.,0.,675.,550.);
  diag->SetLineWidth(3);
  diag->SetLineStyle(2);
  diag->SetLineColor(kBlack);

  diag->Draw("same");

  //  TLegend* leg = new TLegend(0.19,0.68,0.54,0.92);
  //TLegend* leg = new TLegend(0.19,0.68,0.54,0.85);
  TLegend* leg = new TLegend(0.19,0.56,0.54,0.84,"5#sigma Discovery Reach");
  leg->SetFillColor(0);
  leg->SetTextSize(0.04);
  leg->AddEntry(g_signif_PhaseII_3000fb,"3000 fb^{-1} Phase II, 140PU","l");
  //  leg->AddEntry(g_signif_PhaseII_PU200_3000fb,"3000 fb^{-1} Phase II, 200PU","l");
  leg->AddEntry(g_signif_PhaseII_PU200_4000fb,"4000 fb^{-1} Phase II, 200PU","l");
  leg->AddEntry(g_signif_PhaseII_NoTrkExt_3000fb,"3000 fb^{-1} Phase II, 140PU, No Tracker Extension","l");

  leg->Draw("same");

  CMS_lumi_v2( c1, iPeriod, iPos );

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    
  latex.SetTextFont(42);
  latex.SetTextAlign(11); 
  latex.SetTextSize(0.05);    
  latex.DrawLatex(0.22,0.5,"#tilde{#chi}_{1}^{#pm}#tilde{#chi}_{2}^{0} #rightarrow W#tilde{#chi}_{1}^{0} H#tilde{#chi}_{1}^{0}");

  gPad->Modified();

  c1->SaveAs("contours_putrkextcomp_4000fb.eps");
  c1->SaveAs("contours_putrkextcomp_4000fb.pdf");
}

