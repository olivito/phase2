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

int addAgedVars(TString infname, TString outfile){
  
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
  Float_t lep2pt;
  Float_t lep2eta;
  Float_t lep2phi;
  Int_t nleps;
  Float_t pujetmet;
  Float_t pujetmetphi;
  Float_t pujetmt;
  Int_t nb;
  Int_t nbgen;
  Int_t ncgen;

  TBranch* b_lep1pt;
  TBranch* b_lep1eta;
  TBranch* b_lep1phi;
  TBranch* b_lep2pt;
  TBranch* b_lep2eta;
  TBranch* b_lep2phi;
  TBranch* b_nleps;
  TBranch* b_pujetmet;
  TBranch* b_pujetmetphi;
  TBranch* b_pujetmt;
  TBranch* b_nb;
  TBranch* b_nbgen;
  TBranch* b_ncgen;

  // new branches
  Float_t agedweight = 1.;
  Int_t agednleps = -999;
  Float_t agedlep1pt = -999.;
  Float_t agedlep1eta = -999.;
  Float_t agedlep1phi = -999.;
  Float_t smearmet = -999.;
  Float_t smearmetphi = -999.;
  Float_t smearmt = -999.;

  // random generator
  TRandom3 rand;
  const float sigma = 40.; // smear by 40 GeV

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
  clone->SetBranchAddress("lep2pt"     ,  &lep2pt     , &b_lep2pt  );
  clone->SetBranchAddress("lep2eta"    ,  &lep2eta    , &b_lep2eta  );
  clone->SetBranchAddress("lep2phi"    ,  &lep2phi    , &b_lep2phi  );
  clone->SetBranchAddress("nleps"      ,  &nleps      , &b_nleps  );
  clone->SetBranchAddress("pujetmet"   ,  &pujetmet   , &b_pujetmet  );
  clone->SetBranchAddress("pujetmetphi",  &pujetmetphi, &b_pujetmetphi  );
  clone->SetBranchAddress("pujetmt"    ,  &pujetmt    , &b_pujetmt  );
  clone->SetBranchAddress("nb"         ,  &nb         , &b_nb  );
  clone->SetBranchAddress("nbgen"      ,  &nbgen      , &b_nbgen  );
  clone->SetBranchAddress("ncgen"      ,  &ncgen      , &b_ncgen  );

  // new branches
  TBranch* b_agedweight = clone->Branch("agedweight", &agedweight, "agedweight/F");
  TBranch* b_agednleps = clone->Branch("agednleps", &agednleps, "agednleps/I");
  TBranch* b_agedlep1pt = clone->Branch("agedlep1pt", &agedlep1pt, "agedlep1pt/F");
  TBranch* b_agedlep1eta = clone->Branch("agedlep1eta", &agedlep1eta, "agedlep1eta/F");
  TBranch* b_agedlep1phi = clone->Branch("agedlep1phi", &agedlep1phi, "agedlep1phi/F");
  TBranch* b_smearmet = clone->Branch("smearmet", &smearmet, "smearmet/F");
  TBranch* b_smearmetphi = clone->Branch("smearmetphi", &smearmetphi, "smearmetphi/F");
  TBranch* b_smearmt = clone->Branch("smearmt", &smearmt, "smearmt/F");
   
  Long64_t nentries = t->GetEntries();
  //Long64_t nentries = 100;
  for(Long64_t i = 0; i < nentries; i++) {
    clone->GetEntry(i);

    // set weight for reduced btagging eff
    if (nb == 2) {
      if ((nbgen+ncgen) == 2) agedweight = 0.667*0.667;
      else if ((nbgen+ncgen) == 1) agedweight = 0.667;
    } else {
      agedweight = 1.;
    }
    // cout << "nb: " << nb << ", nbgen: " << nbgen << ", ncgen: " << ncgen 
    // 	 << ", agedweight: " << agedweight << endl;

    // reduce lepton efficiency by 0.84
    if (nleps > 0) {
      int keeplep1 = 1;
      int keeplep2 = 1;
      // roll the dice for each lepton
      if (rand.Rndm() > 0.84) keeplep1 = 0;
      if (nleps == 1 || rand.Rndm() > 0.84) keeplep2 = 0;
      agednleps = keeplep1+keeplep2;

      // cout << "nleps: " << nleps << ", keeplep1: " << keeplep1
      // 	   << ", keeplep2: " << keeplep2 << ", agednleps: " << agednleps << endl;

      if (keeplep1 == 1) {
	agedlep1pt = lep1pt;
	agedlep1eta = lep1eta;
	agedlep1phi = lep1phi;
      } else if (keeplep2 == 1) {
	agedlep1pt = lep2pt;
	agedlep1eta = lep2eta;
	agedlep1phi = lep2phi;
      } else {
	agedlep1pt = -999;
	agedlep1eta = -999;
	agedlep1phi = -999;
      }
    }

    // smear met and propagate to MT
    float metx = pujetmet * cos(pujetmetphi);
    float mety = pujetmet * sin(pujetmetphi);
    float smearmetx = metx + rand.Gaus(0,sigma);
    float smearmety = mety + rand.Gaus(0,sigma);
    TVector2 smearmetvec(smearmetx,smearmety);
    smearmet = smearmetvec.Mod();
    smearmetphi = smearmetvec.Phi();
    if (agedlep1pt > 0.) {
      smearmt = sqrt( 2 * smearmet * agedlep1pt * ( 1 - cos( smearmetphi - agedlep1phi) ) );
    } else {
      smearmt = -99.;
    }

    // cout << "pujetmet: " << pujetmet << ", pujetmetphi: " << pujetmetphi
    // 	 << ", smearmet: " << smearmet << ", smearmetphi: " << smearmetphi 
    // 	 << ", pujetmt: " << pujetmt << ", smearmt: " << smearmt << endl;

    // fill new branches
    b_agedweight->Fill();
    b_agednleps->Fill();
    b_agedlep1pt->Fill(); 
    b_agedlep1eta->Fill();
    b_agedlep1phi->Fill();
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






