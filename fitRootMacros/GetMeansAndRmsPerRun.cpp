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
void GetMeansAndRmsPerRun(){

  // TFile* fileList = new TFile("../MyUPC-MonteCarlo/AnalysisResults.root");
  // TFile* fileList = new TFile("AnalysisResultsMC06062019.root");
  // TFile* fileList = new TFile("MCtrainResults/2019-06-16-LHC18qr/kCohJpsiToMu/AnalysisResults.root");
  // TFile* fileList = new TFile("MCtrainResults/2019-06-16-LHC15o/kCohJpsiToMu/AnalysisResults.root");
  // TFile* fileList = new TFile("MCtrain/LHC16b218l7.root");
  // TFile* fileList = new TFile("MCtrain/LHC16b2.root");
  // TFile* fileList = new TFile("MCtrain/LHC18l7.root");
  // TFile* fileList = new TFile("MCtrain/LHC18r_Pass3_01072019.root");
  TFile* fileList = new TFile("MCtrain/AnalysisResultsLHC18r04072019.root");
  // TFile* fileList = new TFile("MCtrain/AnalysisResultsMatchLHC18qr29062019MC.root");
  // TFile* fileList = new TFile("MCtrain/AnalysisResultsMatchLHC15o29062019MC.root");
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
  TH1F* HistoZNC = 0x0;
  TH1F* HistoZNA = 0x0;
  TH1F* fMeanWithRmsAsErrorPerRunZNCH =  new TH1F( "fMeanWithRmsAsErrorPerRunZNCH",
                                                   "fMeanWithRmsAsErrorPerRunZNCH",
                                                   3, 0, 3
                                                   );
  fMeanWithRmsAsErrorPerRunZNCH->SetStats(0);
  fMeanWithRmsAsErrorPerRunZNCH->SetFillColor(38);
  fMeanWithRmsAsErrorPerRunZNCH->LabelsDeflate();
  TH1F* fMeanWithRmsAsErrorPerRunZNAH =  new TH1F( "fMeanWithRmsAsErrorPerRunZNAH",
                                                   "fMeanWithRmsAsErrorPerRunZNAH",
                                                   3, 0, 3
                                                   );
  fMeanWithRmsAsErrorPerRunZNAH->SetStats(0);
  fMeanWithRmsAsErrorPerRunZNAH->SetFillColor(38);
  fMeanWithRmsAsErrorPerRunZNAH->LabelsDeflate();
  TH1F* fMeanWithRmsAsErrorPerRunZNC1nH =  new TH1F( "fMeanWithRmsAsErrorPerRunZNC1nH",
                                                     "fMeanWithRmsAsErrorPerRunZNC1nH",
                                                     3, 0, 3
                                                     );
  fMeanWithRmsAsErrorPerRunZNC1nH->SetStats(0);
  fMeanWithRmsAsErrorPerRunZNC1nH->SetFillColor(38);
  fMeanWithRmsAsErrorPerRunZNC1nH->LabelsDeflate();
  TH1F* fMeanWithRmsAsErrorPerRunZNA1nH =  new TH1F( "fMeanWithRmsAsErrorPerRunZNA1nH",
                                                     "fMeanWithRmsAsErrorPerRunZNA1nH",
                                                     3, 0, 3
                                                     );
  fMeanWithRmsAsErrorPerRunZNA1nH->SetStats(0);
  fMeanWithRmsAsErrorPerRunZNA1nH->SetFillColor(38);
  fMeanWithRmsAsErrorPerRunZNA1nH->LabelsDeflate();
  Int_t listOfGoodRunNumbersLHC18r[] = { 296690, 296691, 296694, 296749, 296750, 296781,
                                         296784, 296785, 296786, 296787, 296791, 296793,
                                         296794, 296799, 296836, 296838, 296839, 296848,
                                         296849, 296850, 296851, 296852, 296890, 296894,
                                         296899, 296900, 296903, 296930, 296931, 296932,
                                         296934, 296935, 296938, 296941, 296966, 296967,
                                         296968, 296969, 296971, 296975, 296976, /*296977,*/
                                         296979, 297029, 297031, 297035, 297085, 297117,
                                         297118, 297119, 297123, 297124, 297128, 297129,
                                         297132, 297133, 297193, 297194, 297196, 297218,
                                         297219, 297221, 297222, 297278, 297310, 297312,
                                         297315, 297317, 297363, 297366, 297367, 297372,
                                         297379, 297380, 297405, 297408, 297413, 297414,
                                         297415, 297441, 297442, 297446, 297450, 297451,
                                         297452, 297479, 297481, 297483, 297512, 297537,
                                         297540, 297541, 297542, 297544, 297558, 297588,
                                         297590, 297595/*, 297623, 297624*/ };
  for( Int_t iLoopRun = 0; iLoopRun < 97; iLoopRun++ ){
    HistoZNC = (TH1F*)listings->FindObject( Form("fZNCEnergyPerRunH_%d", listOfGoodRunNumbersLHC18r[iLoopRun] ) );
    HistoZNA = (TH1F*)listings->FindObject( Form("fZNAEnergyPerRunH_%d", listOfGoodRunNumbersLHC18r[iLoopRun] ) );
    HistoZNC->Rebin(2);
    HistoZNA->Rebin(2);
    Double_t MeanZNC = HistoZNC->GetMean();
    Double_t RmsZNC  = HistoZNC->GetRMS();
    Double_t MeanZNA = HistoZNA->GetMean();
    Double_t RmsZNA  = HistoZNA->GetRMS();
    fMeanWithRmsAsErrorPerRunZNCH->Fill( Form("%d", listOfGoodRunNumbersLHC18r[iLoopRun]) , MeanZNC );
    fMeanWithRmsAsErrorPerRunZNAH->Fill( Form("%d", listOfGoodRunNumbersLHC18r[iLoopRun]) , MeanZNA );
    fMeanWithRmsAsErrorPerRunZNCH->SetBinError( iLoopRun + 1, RmsZNC );
    fMeanWithRmsAsErrorPerRunZNAH->SetBinError( iLoopRun + 1, RmsZNA );
    HistoZNC->GetXaxis()->SetRangeUser( -2000, 3500 );
    HistoZNA->GetXaxis()->SetRangeUser( -2000, 3500 );
    Double_t MeanZNC1n = HistoZNC->GetMean();
    Double_t RmsZNC1n  = HistoZNC->GetRMS();
    Double_t MeanZNA1n = HistoZNA->GetMean();
    Double_t RmsZNA1n  = HistoZNA->GetRMS();
    fMeanWithRmsAsErrorPerRunZNC1nH->Fill( Form("%d", listOfGoodRunNumbersLHC18r[iLoopRun]) , MeanZNC1n );
    fMeanWithRmsAsErrorPerRunZNA1nH->Fill( Form("%d", listOfGoodRunNumbersLHC18r[iLoopRun]) , MeanZNA1n );
    fMeanWithRmsAsErrorPerRunZNC1nH->SetBinError( iLoopRun + 1, RmsZNC1n );
    fMeanWithRmsAsErrorPerRunZNA1nH->SetBinError( iLoopRun + 1, RmsZNA1n );

  }




  TCanvas* MeanCanvas  = new TCanvas("MeanCanvas","MeanCanvas",900,800);
  fMeanWithRmsAsErrorPerRunZNCH->Draw("ep");
  TCanvas* MeanCanvas2 = new TCanvas("MeanCanvas2","MeanCanvas2",900,800);
  fMeanWithRmsAsErrorPerRunZNAH->Draw("ep");
  TCanvas* MeanCanvas3 = new TCanvas("MeanCanvas3","MeanCanvas3",900,800);
  fMeanWithRmsAsErrorPerRunZNC1nH->Draw("ep");
  TCanvas* MeanCanvas4 = new TCanvas("MeanCanvas4","MeanCanvas4",900,800);
  fMeanWithRmsAsErrorPerRunZNA1nH->Draw("ep");

  // TFile f("pngResults/efficiency18qrMB.root", "recreate");
  // RealEfficiency->Write();
  // f.Close();
}
