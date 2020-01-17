/*****************************************************/
/* plot1DHists.C                                     */
/* Usage: root -l -b -q plot1DHists.C                */
/* Description: Contains helper functions to create
   TH1Fs of any variable/ arbitrary cuts with the 
   weights/lumi/cross-sections necessary for the 
   resulting histogram to be number of events.       */
/*****************************************************/

#include "TCanvas.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1.h"
#include "TF1.h"
#include <math.h>
#include <iostream>
#include <string>

#ifndef PLOT1DHISTS_C_INCL
#define PLOT1DHISTS_C_INCL

/*****************************************************/

/* Using the file located at inputDirectory and the tree
   treePath, draws the branch "variable" into a TH1F
   with the name histName and returns a pointer to the TH1F.
   Applies the TStrings cut and weight. The resulting
   TH1F has (bins) number of bins
   and ranges from the values low to high. */

TH1F* makeHistogram(TString variable,
		    TString histName,
		    TCut cut,
		    TCut weight,
		    TString treePath,
		    TString inputDirectory,
		    int bins,
		    int low, 
		    int high)
{
  TFile *file = new TFile(inputDirectory);
 
  TTree* tree = (TTree*)file->Get(treePath);

  TH1F* hist = new TH1F(histName, histName, bins, low, high);
  
  if ((cut != "") && (weight != ""))
    tree->Draw(variable+">>+"+histName, cut * weight);
  else if (cut != "")
    tree->Draw(variable+">>+"+histName, cut);
  else if (weight != "")
    tree->Draw(variable+">>+"+histName, weight);
  else
    tree->Draw(variable+">>+"+histName);

  return hist;

}

/*****************************************************/

/* Apply template style to a TPad* pad1. */
void applyPadStyle(TPad* pad1)
{
  pad1->SetFillColor(0);
  pad1->Draw();  pad1->cd();  pad1->SetLeftMargin(0.2);  pad1->SetBottomMargin(0.13); pad1->SetRightMargin(0.1);
  //pad1->SetGrid(); 
  pad1->SetGrid(10,10); 
}

/*****************************************************/

/* Apply legend style to a TLegend *leg. */
void applyLegStyle(TLegend *leg)
{
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetHeader("");
  leg->SetShadowColor(0);
}

/*****************************************************/




/*****************************************************/

/* Plots histogram TH1F h, with axes labels xLabel and
   yLabel, with the legend entry legendEntry and saves it
   to a file with the directory and name outfileDirectory
   (include the extension). */

int makeHistPlot(TH1F *h,
		 TString xLabel,
		 TString yLabel,
		 TString legendEntry,
		 TString outfileDirectory)
{
  TCanvas* Tcan = new TCanvas("Tcan","", 100, 20, 800, 600);
  Tcan->cd();     /* Set current canvas */
  Tcan->SetFillColor(0);

  TLegend *leg = new TLegend(0.60,0.75,0.85,0.9);
  applyLegStyle(leg);

  h->Draw("E HIST");

  // Suppress statistics box
  h->SetStats(0);

  // Set axes labels
  h->GetXaxis()->SetTitle(xLabel);
  h->GetYaxis()->SetTitle(yLabel);

  // Format the legend
  leg->AddEntry(h, legendEntry, "l");
  leg->Draw();
  
  Tcan->SaveAs(outfileDirectory);
  
  delete Tcan;
  return 0;

}

/*****************************************************/

/* Takes TH1Fs h_data and h_MC_bkg, plots variable 
   and saves plot with axes labels xLabel and yLabel
   to the output file directory. */

int makeOverlayHistPlot(TH1F *h_data,
			TH1F *h_bkg,
			TH1F *h_sig,
			TString labelData,
			TString labelBkg,
			TString labelSig,
			TString variable,
			TString outfileDirectory)
{
  TCanvas* Tcan = new TCanvas("Tcan","", 100, 20, 800, 600);
  Tcan->cd();     /* Set current canvas */
  Tcan->SetFillColor(0);

  TLegend *leg = new TLegend(0.60,0.75,0.85,0.9);
  applyLegStyle(leg);

  // Change colors, marker style, etc.
  h_data->SetMarkerColor(kAzure-3);
  h_data->SetMarkerSize(0.4);
  h_data->SetMarkerStyle(8);
  h_data->SetLineWidth(1);

  h_bkg->SetMarkerColor(kRed-3);
  h_bkg->SetLineWidth(1);
  h_bkg->SetLineColor(kRed-10);
  
  h_sig->SetMarkerColor(kGreen+2);
  h_sig->SetMarkerSize(0.4);
  h_sig->SetMarkerStyle(8);
  h_sig->SetLineWidth(1);

  // To draw the error bars as shaded regions, we need to clone the 
  // original histogram. So we do this for the backgrond histogram:
  TH1F *h_bkgClone = (TH1F*) h_bkg->Clone("bkgClone");
  h_bkgClone->SetFillStyle(3001);
  h_bkgClone->SetFillColor(kGray);

  // Suppress stats box                                                                             
  h_data->SetStats(0);
  h_bkgClone->SetStats(0);
  h_bkg->SetStats(0);
  h_sig->SetStats(0);

  // Set axes labels
  h_bkg->GetXaxis()->SetTitle(variable);
  h_bkg->GetYaxis()->SetTitle("Events");

  // Need this line to set the title
  h_bkg->SetTitle(variable);

  // Drawing
  h_bkg->Draw("HIST");     // draw background as normal histogram
  h_bkgClone->Draw("E3 SAME");  // E3 is the shading
  h_data->Draw("EP Z SAME");  // draw signal as dots
  h_sig->Draw("HIST SAME");
  
  // Format and draw the legend                          
  leg->AddEntry(h_data, labelData, "l");
  leg->AddEntry(h_bkg, labelBkg, "l");
  leg->AddEntry(h_sig, labelSig, "l");
  leg->Draw();

  Tcan->SaveAs(outfileDirectory);

  delete Tcan;
  
  
  return 0;

}

/*****************************************************/

/* Creates TH1Fs of variable, saves them to a ROOT file
   (one TH1F for data, one for signal, and one for
   backgrond (QCD + TT), and plots them. */

int makeDataBkgHists(TString variable,
		     TString outputFileDirectory,
		     TString treePath,
		     TString dataDir, TCut dataCut, TCut dataWeight, TString dataLabel,
		     TString bkgDir,  TCut bkgCut,  TCut bkgWeight,  TString bkgLabel,
		     TString sigDir,  TCut sigCut,  TCut sigWeight,  TString sigLabel,
		     int nBins, int low, int high)
{
  // Data: weight is 1
  TH1F *h_dataAll = makeHistogram(variable, "data",       dataCut, dataWeight, treePath, dataDir, nBins, low, high);
  TH1F *h_dataBkg = makeHistogram(variable, "background", bkgCut, bkgWeight, treePath, bkgDir, nBins, low, high);
  TH1F *h_MCsig   = makeHistogram(variable, "signal",     sigCut, sigWeight, treePath, sigDir, nBins, low, high);

  // Create an output ROOT file, writing histograms to the file    
  TFile *fOut = new TFile(outputFileDirectory, "RECREATE"); 
  if ( fOut->IsOpen() ) printf("File opened successfully\n");
  fOut->cd(); 
  h_dataAll->Write();
  h_dataBkg->Write();
  fOut->Close();

  makeOverlayHistPlot(h_dataAll, h_dataBkg, h_MCsig, dataLabel, bkgLabel, sigLabel,
		      variable, 
		      variable + "_dataAll_and_dataBkg.png");

  return 0;
}

/*****************************************************/

int plot1DHists(void)
{
  TString desc = "data_and_databkg.root";
  TString treePath = "bbbbTree";

  TString dataDir = "/uscms/home/lcadamur/nobackup/CMSDAS_bbbbAnalysis_sl7/CMSSW_10_2_18/src/CMSDAS-bbbbAnalysis/background/data_4btag_Fabio.root";
  TCut dataCut = "TMath::Sqrt((H1_m - 120.)**2 + (H2_m - 110.)**2) < 30."; // cut in signal region
  TCut dataWeight = "1";

  TString bkgDir = "/uscms/home/lcadamur/nobackup/CMSDAS_bbbbAnalysis_sl7/CMSSW_10_2_18/src/CMSDAS-bbbbAnalysis/background/data_3btag_with_weights_VR_Fabio.root";
  TCut bkgCut = "TMath::Sqrt((H1_m - 120.)**2 + (H2_m - 110.)**2) < 30.";
  TCut bkgWeight = "bkg_model_w";

  TString sigDir = "/uscms/home/skwan/nobackup/HHbbbb_exercise/CMSSW_10_2_18/src/CMSDAS-bbbbAnalysis/analysis/objects_gg_HH_bbbb_SM.root";
  TCut sigCut = "TMath::Sqrt((H1_m - 120.)**2 + (H2_m - 110.)**2) < 30.";
  TCut sigWeight = "norm_weight * xs * 35920 * btag_SF * trigger_SF";

  TString dataLabel = "Data (Signal region)";
  TString bkgLabel = "Data-driven background estimate (Signal region)";
  TString sigLabel = "MC Signal (Signal region)";

  int nBins = 800;
  int low = 0;
  int high = 800;

  /*
  makeDataBkgHists("H1_m", "H1_m_" + desc, treePath, dataDir, dataCut, dataWeight, dataLabel,
		   bkgDir, bkgCut, bkgWeight, bkgLabel,
		   sigDir, sigCut, sigWeight, sigLabel, nBins, low, high);
  makeDataBkgHists("H2_m", "H2_m_" + desc, treePath, dataDir, dataCut, dataWeight, dataLabel,
                   bkgDir, bkgCut, bkgWeight, bkgLabel, 
		   sigDir, sigCut, sigWeight, sigLabel, nBins, low, high);
  */
  makeDataBkgHists("HH_m", "HH_m_" + desc, treePath, dataDir, dataCut, dataWeight, dataLabel,
		   bkgDir, bkgCut, bkgWeight, bkgLabel,
		   sigDir, sigCut, sigWeight, sigLabel, nBins, low, high);

  return 0;
}


#endif
