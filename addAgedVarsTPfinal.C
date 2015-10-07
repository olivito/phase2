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
// updated btagging eff numbers

 unsigned int npt_etaLT18 = 24; 
 float ptinf_etaLT18[] = { 20, 30, 40, 50, 60, 70, 80, 90, 100, 120, 
                          140, 160, 180, 200, 250, 300, 350, 400, 500, 600, 
			  700, 800, 1000, 1400 };
 float ptsup_etaLT18[] = { 30, 40, 50, 60, 70, 80, 90, 100, 120, 140, 
                          160, 180, 200, 250, 300, 350, 400, 500, 600, 700, 
			  800, 1000, 1400, 20000 };

float effi_B_phaseIaged_etaLT18_flat_medium[] = {
 0.4058, 0.4737, 0.5374, 0.572, 0.6031, 0.6095, 0.6113, 0.6178, 0.6133, 0.6046,
 0.5778, 0.5527, 0.5351, 0.4858, 0.4308, 0.3746, 0.3296, 0.2575, 0.1888, 0.1516,
 0.1342, 0.1246, 0.1218, 0.154};

float effi_B_phaseII_etaLT18_flat_medium[] = {
 0.5281, 0.6116, 0.6666, 0.7011, 0.7344, 0.7413, 0.7469, 0.7509, 0.7426, 0.7292,
 0.7114, 0.6948, 0.6847, 0.6421, 0.6022, 0.5549, 0.488, 0.4173, 0.3433, 0.2842,
 0.2503, 0.221, 0.1641, 0.173};

////////////////////////////////////////////////////////////////////////////////

 unsigned int npt_18eta24 = 20; 
 float ptinf_18eta24[] = { 20, 30, 40, 50, 60, 70, 80, 90, 100, 120, 
             	          140, 160, 180, 200, 250, 300, 350, 400, 500, 600};
 float ptsup_18eta24[] = { 30, 40, 50, 60, 70, 80, 90, 100, 120, 140, 
             	          160, 180, 200, 250, 300, 350, 400, 500, 600, 30000 };

float effi_B_phaseIaged_18eta24_flat_medium[] = {
 0.3135, 0.3537, 0.4078, 0.4413, 0.4674, 0.4787, 0.4862, 0.5011, 0.4746, 0.4531,
 0.4248, 0.3946, 0.392, 0.3295, 0.2646, 0.2228, 0.1914, 0.1544, 0.1262, 0.1423};

float effi_B_phaseII_18eta24_flat_medium[] = {
 0.3221, 0.4143, 0.4881, 0.5219, 0.5548, 0.5904, 0.5717, 0.5836, 0.5758, 0.5579,
 0.5361, 0.5165, 0.4832, 0.432, 0.366, 0.3231, 0.241, 0.252, 0.237, 0.2434};

////////////////////////////////////////////////////////////////////////////////

float getBtagSF(float pt, float eta) {

  if (fabs(eta) < 1.8) {
    for (unsigned int i=0; i<npt_etaLT18; ++i) {
      if (pt >= ptinf_etaLT18[i] && pt < ptsup_etaLT18[i]) {
	float sf = effi_B_phaseIaged_etaLT18_flat_medium[i] / effi_B_phaseII_etaLT18_flat_medium[i];
	//	if (sf < 0.1) std::cout << "btag SF for pt: " << pt << ", eta: " << eta << " is: " << sf << std::endl;
	return sf;
      }
    }
  } // eta < 1.8
  else if (fabs(eta) > 1.8 && fabs(eta) < 2.4) {
    for (unsigned int i=0; i<npt_18eta24; ++i) {
      if (pt >= ptinf_18eta24[i] && pt < ptsup_18eta24[i]) {
	float sf = effi_B_phaseIaged_18eta24_flat_medium[i] / effi_B_phaseII_18eta24_flat_medium[i];
	//	if (sf < 0.1) std::cout << "btag SF for pt: " << pt << ", eta: " << eta << " is: " << sf << std::endl;
	return sf;
      }
    }
  } // 1.8 < eta < 2.4

  std::cout << "WARNING: couldn't find SF for jet with pt: " << pt << ", eta: " << eta << std::endl;
  return 1.;
}

////////////////////////////////////////////////////////////////////////////////

int addAgedVarsTPfinal(TString infname, TString outfile){
  
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
  Float_t bjet1pt;
  Float_t bjet1eta;
  Float_t bjet2pt;
  Float_t bjet2eta;

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
  TBranch* b_bjet1pt;
  TBranch* b_bjet1eta;
  TBranch* b_bjet2pt;
  TBranch* b_bjet2eta;

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
  const float sigma = 20.; // smear by 20 GeV

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
  clone->SetBranchAddress("bjet1pt"    ,  &bjet1pt    , &b_bjet1pt  );
  clone->SetBranchAddress("bjet1eta"   ,  &bjet1eta   , &b_bjet1eta  );
  clone->SetBranchAddress("bjet2pt"    ,  &bjet2pt    , &b_bjet2pt  );
  clone->SetBranchAddress("bjet2eta"   ,  &bjet2eta   , &b_bjet2eta  );

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

    agedweight = 1.;
    // set weight for reduced btagging eff
    if (nb == 2) {
      // both jets are from heavy flavor - use both SFs
      if ((nbgen+ncgen) == 2) {
	agedweight *= getBtagSF(bjet1pt,bjet1eta);
	agedweight *= getBtagSF(bjet2pt,bjet2eta);
      }
      // only one HF jet - randomly guess which is fake
      else if ((nbgen+ncgen) == 1) {
	if (rand.Rndm() > 0.5) agedweight *= getBtagSF(bjet1pt,bjet1eta);
	else agedweight *= getBtagSF(bjet2pt,bjet2eta);
      }
    } 
    // cout << "nb: " << nb << ", nbgen: " << nbgen << ", ncgen: " << ncgen 
    // 	 << ", bjet1 pt: " << bjet1pt << ", eta: " << bjet1eta
    // 	 << ", bjet2 pt: " << bjet2pt << ", eta: " << bjet2eta
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






