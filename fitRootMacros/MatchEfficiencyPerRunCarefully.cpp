#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLeaf.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TMath.h"
#include "TF1.h"
#include "TLatex.h"
using namespace std;
#include <math.h>
#include <vector>


#include "TH2.h"

//_____________________________________________________________________________
/* - Computes the efficiency of the MC on a
 * - run-by-run basis.
 * -
 */
void MatchEfficiencyPerRun(){

  // TFile* fileList = new TFile("../MyUPC-MonteCarlo/AnalysisResults.root");
  // TFile* fileList = new TFile("AnalysisResultsMC06062019.root");
  // TFile* fileList = new TFile("MCtrainResults/2019-06-16-LHC18qr/kCohJpsiToMu/AnalysisResults.root");
  // TFile* fileList = new TFile("MCtrainResults/2019-06-16-LHC15o/kCohJpsiToMu/AnalysisResults.root");
  // TFile* fileList = new TFile("MCtrain/LHC16b218l7.root");
  // TFile* fileList = new TFile("MCtrain/LHC16b2.root");
  // TFile* fileList = new TFile("MCtrain/LHC18l7.root");
  // TFile* fileList = new TFile("MCtrain/AnalysisResultsMatchLHC18qr29062019MC.root");
  // TFile* fileList = new TFile("MCtrain/AnalysisResultsMatchLHC15o29062019MC.root");
  TFile* fileList = new TFile("MCtrain/AnalysisResultsLHC18r04072019.root");
  TDirectory* dir = fileList->GetDirectory("MyTask");
  TList* listings;
  // dir->GetObject("MyOutputContainer", listings);
  dir->GetObject("SingleMuonTriggerMatch", listings);
  /* - We now do the same as before to ascertain if the TList was there and
   * - to try to retrieve the plots. Result:
   *   listings->ls()
   *     OBJ: TList	  MyOutputContainer	          Doubly linked list          : 0
   *     OBJ: TH1F	  fNumberMuonsH	              fNumberMuonsH               : 0 at: 0x5a145f0
   *     OBJ: TH1F	  fCounterH	                  fCounterH                   : 0 at: 0x5a3b570
   *     OBJ: TH1F	  fEtaMuonH	                  fEtaMuonH                   : 0 at: 0x5a3ba80
   *     OBJ: TH1F	  fRAbsMuonH	                fRAbsMuonH                  : 0 at: 0x5a3c0c0
   *     OBJ: TH1F	  fInvariantMassDistributionH	fInvariantMassDistributionH : 0 at: 0x5a3c720
   */
  TH1F* fEfficiencyPerRunH   = (TH1F*)listings->FindObject("fEfficiencyPerRunWithTriggeringH");
  TH1F* fMCEfficiencyPerRunH = (TH1F*)listings->FindObject("fEfficiencyPerRunH");
  fEfficiencyPerRunH  ->Sumw2();
  fMCEfficiencyPerRunH->Sumw2();

  // Double_t ArrayEfficiencyWithTrigg[fEfficiencyPerRunH->GetNbinsX()];
  // Double_t ArrayEfficiencyAllTrigge[fEfficiencyPerRunH->GetNbinsX()];
  // for(Int_t ixWithTrigg = 1; ixWithTrigg <= fEfficiencyPerRunH->GetNbinsX(); ixWithTrigg++){
  //   for(Int_t ixMC = 1; ixMC <= fMCEfficiencyPerRunH->GetNbinsX(); ixMC++){
  //     if( atoi(fEfficiencyPerRunH->GetXaxis()->GetBinLabel(ixWithTrigg)) == atoi(fMCEfficiencyPerRunH->GetXaxis()->GetBinLabel(ixMC)) ){
  //       if ( !(fEfficiencyPerRunH  ->GetBinContent(ixWithTrigg) < 1) ) {ArrayEfficiencyWithTrigg[ixWithTrigg] = fEfficiencyPerRunH  ->GetBinContent(ixWithTrigg);}
  //       if ( !(fMCEfficiencyPerRunH->GetBinContent(ixMC)        < 1) ) {ArrayEfficiencyAllTrigge[ixWithTrigg] = fMCEfficiencyPerRunH->GetBinContent(ixMC);}
  //     }
  //   }
  // }
  //
  // TCanvas* EffCanvas = new TCanvas("EffCanvas","EffCanvas",900,800);
  TH1F* RealEfficiency  = (TH1F*) fEfficiencyPerRunH->Clone("RealEfficiency");
  // TH1F* RealEfficiency2 = (TH1F*) fEfficiencyPerRunH->Clone("RealEfficiency");
  // TH1F* MCEfficiency    = (TH1F*) fEfficiencyPerRunH->Clone("RealEfficiency");
  // for( Int_t ixWithTrigg = 1; ixWithTrigg <= fEfficiencyPerRunH->GetNbinsX() - 3; ixWithTrigg++ ){
  //   RealEfficiency2->SetBinContent(ixWithTrigg, ArrayEfficiencyAllTrigge[ixWithTrigg]);
  //   RealEfficiency2->SetBinError(ixWithTrigg, TMath::Sqrt(ArrayEfficiencyAllTrigge[ixWithTrigg]) );
  // }
  // for( Int_t ixWithTrigg = 1; ixWithTrigg <= fEfficiencyPerRunH->GetNbinsX(); ixWithTrigg++ ){
  //   cout << "ArrayEfficiencyWithTrigg[" << ixWithTrigg << "] = " << ArrayEfficiencyWithTrigg[ixWithTrigg] << endl;
  // }
  // for( Int_t ixWithTrigg = 1; ixWithTrigg <= fEfficiencyPerRunH->GetNbinsX(); ixWithTrigg++ ){
  //   cout << "ArrayEfficiencyAllTrigge[" << ixWithTrigg << "] = " << ArrayEfficiencyAllTrigge[ixWithTrigg] << endl;
  // }

  RealEfficiency->Divide(fMCEfficiencyPerRunH);
  // RealEfficiency->Divide(RealEfficiency2);
  RealEfficiency->Draw("ep");




  // TFile f("pngResults/efficiency16b2.root", "recreate");
  // TFile f("pngResults/efficiency18l7.root", "recreate");
  // TFile f("pngResults/efficiency18qrMBv2.root", "recreate");
  // TFile f("pngResults/efficiency15oMBv2.root", "recreate");
  TFile f("pngResults/efficiency18rMB.root", "recreate");
  RealEfficiency->Write();
  f.Close();
}
