#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TString.h"
#include "TRandom3.h"
#include "TVector2.h"

using namespace std;


////////////////////////////////////////////////////////////////////////////////

int addAgedVarsNoTrkExt(TString infname, TString outfile){
  
  cout << "Processing File " << infname << endl;

  TFile *f = TFile::Open(infname.Data(), "READ");
  if (! f || f->IsZombie()) {
    cout << "File does not exist!" << endl;
    return 1;
  }
  
  TTree* t = (TTree*)f->Get("t");
  if (! t || t->IsZombie()) {
    cout << "Tree does not exist!" << endl;
    return 2;
  }
        
  // old branches
  Float_t lep1pt;
  Float_t lep1eta;
  Float_t lep1phi;
  Float_t pujetmet;
  Float_t pujetmetphi;
  Float_t pujetmt;

  TBranch* b_lep1pt;
  TBranch* b_lep1eta;
  TBranch* b_lep1phi;
  TBranch* b_pujetmet;
  TBranch* b_pujetmetphi;
  TBranch* b_pujetmt;

  // new branches
  Float_t smearmet = -999.;
  Float_t smearmetphi = -999.;
  Float_t smearmt = -999.;

  // random generator
  TRandom3 rand;

  //-------------------------------------------------------------
  // Removes all non *_CMS2.* branches
  //-------------------------------------------------------------`
  t->SetBranchStatus("*", 1);

  TFile *out = TFile::Open(outfile.Data(), "RECREATE");
  TTree *clone;
  clone = t->CloneTree(-1, "fast");

  cout << "Cloning to File " << outfile << endl;

  //-------------------------------------------------------------

  // existing branches
  clone->SetBranchAddress("lep1pt"     ,  &lep1pt     , &b_lep1pt  );
  clone->SetBranchAddress("lep1eta"    ,  &lep1eta    , &b_lep1eta  );
  clone->SetBranchAddress("lep1phi"    ,  &lep1phi    , &b_lep1phi  );
  clone->SetBranchAddress("pujetmet"   ,  &pujetmet   , &b_pujetmet  );
  clone->SetBranchAddress("pujetmetphi",  &pujetmetphi, &b_pujetmetphi  );
  clone->SetBranchAddress("pujetmt"    ,  &pujetmt    , &b_pujetmt  );

  // new branches
  TBranch* b_smearmet = clone->Branch("smearmet", &smearmet, "smearmet/F");
  TBranch* b_smearmetphi = clone->Branch("smearmetphi", &smearmetphi, "smearmetphi/F");
  TBranch* b_smearmt = clone->Branch("smearmt", &smearmt, "smearmt/F");
   
  Long64_t nentries = t->GetEntries();
  //Long64_t nentries = 100;
  for(Long64_t i = 0; i < nentries; i++) {
    clone->GetEntry(i);

    // smear met and propagate to MT
    float metx = pujetmet * cos(pujetmetphi);
    float mety = pujetmet * sin(pujetmetphi);
    float smearmetx = metx + rand.Gaus(0,0.25 * pujetmet);
    float smearmety = mety + rand.Gaus(0,0.25 * pujetmet);
    TVector2 smearmetvec(smearmetx,smearmety);
    smearmet = smearmetvec.Mod();
    smearmetphi = smearmetvec.Phi();
    if (lep1pt > 0.) {
      smearmt = sqrt( 2 * smearmet * lep1pt * ( 1 - cos( smearmetphi - lep1phi) ) );
    } else {
      smearmt = -99.;
    }

    // cout << "pujetmet: " << pujetmet << ", pujetmetphi: " << pujetmetphi
    // 	 << ", smearmet: " << smearmet << ", smearmetphi: " << smearmetphi 
    // 	 << ", pujetmt: " << pujetmt << ", smearmt: " << smearmt << endl;

    // fill new branches
    b_smearmet->Fill();
    b_smearmetphi->Fill();
    b_smearmt->Fill();
  }
  //-------------------------------------------------------------

  clone->Write(); 
  out->Close();
  f->Close();

  cout << "Processed Events: " << nentries << endl;

  return 0;
  
}






