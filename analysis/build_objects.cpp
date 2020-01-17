// code used to build the objects starting from the basic inputs of the analysis

// c++ -lm -o build_objects build_objects.cpp -I include/ `root-config --glibs --cflags`

#include<iostream>
#include<string>

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TGraphAsymmErrors.h"


#include "analysis_utils.h" // jet_t, init_jet_t
#include "input_tree.h"
#include "output_tree.h"
#include "bbbb_functions.h"

using namespace std;


int main(int argc, char** argv)
{
    // handling the I/O

    if (argc < 3)
    {
        cout << "*** usage : ./build_objects inputFile outputFile isData=0 isSignal=0" << endl;
        return 1;
    }

    string inputFile  = argv[1];
    string outputFile = argv[2];    

    TFile *fTrig =  TFile::Open("/uscms/home/skwan/nobackup/HHbbbb_exercise/CMSSW_10_2_18/src/CMSDAS-bbbbAnalysis/trigger/TriggerEfficiencies.root");
    cout << "[INFO] Input  file: " << inputFile << endl;
    TFile* fIn = TFile::Open(inputFile.c_str());
    TTree* tIn = (TTree*) fIn->Get("bbbbTree");

    cout << "[INFO] Output file: " << outputFile << endl;
    TFile* fOut = new TFile(outputFile.c_str(), "recreate");
    TTree* tOut = new TTree ("bbbbTree", "bbbbTree");

    bool isData = false;
    bool isSig  = false;
    if (argc >= 4)
        isData = (std::stoi(argv[3]) == 0 ? false : true);
    if (argc >= 5)
        isSig = (std::stoi(argv[4]) == 0 ? false : true);
    cout << "[INFO] Is data?   : " << std::boolalpha << isData << std::noboolalpha << endl;
    cout << "[INFO] Is signal? : " << std::boolalpha << isSig  << std::noboolalpha << endl;

    std::string sample_type = "bkg";
    if (isData) sample_type = "data";
    if (isSig)  sample_type = "sig";
    cout << "[INFO] The tree will be read for type : " << sample_type << endl;

    const float btag_WP_medium = 0.3093; // for DeepJet

    // Open the file with the histograms needed for the trigger efficiency and scale factors
    //TFile *fTrig =  TFile::Open("/uscms/home/skwan/nobackup/HHbbbb_exercise/CMSSW_10_2_18/src/CMSDAS-bbbbAnalysis/trigger/TriggerEfficiencies.root");
    TGraphAsymmErrors *SingleMuon_Double90Quad30_Efficiency_L1filter = (TGraphAsymmErrors*) fTrig->Get("SingleMuon_Double90Quad30_Efficiency_L1filter");
    TGraphAsymmErrors *SingleMuon_Double90Quad30_Efficiency_QuadCentralJet30 = (TGraphAsymmErrors*) fTrig->Get("SingleMuon_Double90Quad30_Efficiency_QuadCentralJet30");
    TGraphAsymmErrors *SingleMuon_Double90Quad30_Efficiency_DoubleCentralJet90 = (TGraphAsymmErrors*) fTrig->Get("SingleMuon_Double90Quad30_Efficiency_DoubleCentralJet90");
    TGraphAsymmErrors *SingleMuon_Double90Quad30_Efficiency_BTagCaloCSVp087Triple = (TGraphAsymmErrors*) fTrig->Get("SingleMuon_Double90Quad30_Efficiency_BTagCaloCSVp087Triple");
    TGraphAsymmErrors *SingleMuon_Double90Quad30_Efficiency_QuadPFCentralJetLooseID30  = (TGraphAsymmErrors*) fTrig->Get("SingleMuon_Double90Quad30_Efficiency_QuadPFCentralJetLooseID30");
    TGraphAsymmErrors *SingleMuon_Double90Quad30_Efficiency_DoublePFCentralJetLooseID90 = (TGraphAsymmErrors*) fTrig->Get("SingleMuon_Double90Quad30_Efficiency_DoublePFCentralJetLooseID90");

    TGraphAsymmErrors *SingleMuon_Quad45_Efficiency_L1filter = (TGraphAsymmErrors*) fTrig->Get("SingleMuon_Quad45_Efficiency_L1filter");
    TGraphAsymmErrors *SingleMuon_Quad45_Efficiency_QuadCentralJet45 = (TGraphAsymmErrors*) fTrig->Get("SingleMuon_Quad45_Efficiency_QuadCentralJet45");
    TGraphAsymmErrors *SingleMuon_Quad45_Efficiency_BTagCaloCSVp087Triple = (TGraphAsymmErrors*) fTrig->Get("SingleMuon_Quad45_Efficiency_BTagCaloCSVp087Triple");
    TGraphAsymmErrors *SingleMuon_Quad45_Efficiency_QuadPFCentralJetLooseID45 = (TGraphAsymmErrors*) fTrig->Get("SingleMuon_Quad45_Efficiency_QuadPFCentralJetLooseID45");

    TGraphAsymmErrors *SingleMuon_And_Efficiency_L1filterQuad45 = (TGraphAsymmErrors*) fTrig->Get("SingleMuon_And_Efficiency_L1filterQuad45");
    TGraphAsymmErrors *SingleMuon_And_Efficiency_QuadCentralJet45 = (TGraphAsymmErrors*) fTrig->Get("SingleMuon_And_Efficiency_QuadCentralJet45");
    TGraphAsymmErrors *SingleMuon_And_Efficiency_BTagCaloCSVp087Triple = (TGraphAsymmErrors*) fTrig->Get("SingleMuon_And_Efficiency_BTagCaloCSVp087Triple");
    TGraphAsymmErrors *SingleMuon_And_Efficiency_QuadPFCentralJetLooseID45 = (TGraphAsymmErrors*) fTrig->Get("SingleMuon_And_Efficiency_QuadPFCentralJetLooseID45");

    TGraphAsymmErrors *TTbar_Double90Quad30_Efficiency_L1filter = (TGraphAsymmErrors*) fTrig->Get("TTbar_Double90Quad30_Efficiency_L1filter");
    TGraphAsymmErrors *TTbar_Double90Quad30_Efficiency_QuadCentralJet30 = (TGraphAsymmErrors*) fTrig->Get("TTbar_Double90Quad30_Efficiency_QuadCentralJet30");
    TGraphAsymmErrors *TTbar_Double90Quad30_Efficiency_DoubleCentralJet90 = (TGraphAsymmErrors*) fTrig->Get("TTbar_Double90Quad30_Efficiency_DoubleCentralJet90");
    TGraphAsymmErrors *TTbar_Double90Quad30_Efficiency_BTagCaloCSVp087Triple = (TGraphAsymmErrors*) fTrig->Get("TTbar_Double90Quad30_Efficiency_BTagCaloCSVp087Triple");
    TGraphAsymmErrors *TTbar_Double90Quad30_Efficiency_QuadPFCentralJetLooseID30 = (TGraphAsymmErrors*) fTrig->Get("TTbar_Double90Quad30_Efficiency_QuadPFCentralJetLooseID30");
    TGraphAsymmErrors *TTbar_Double90Quad30_Efficiency_DoublePFCentralJetLooseID90 = (TGraphAsymmErrors*) fTrig->Get("TTbar_Double90Quad30_Efficiency_DoublePFCentralJetLooseID90");

    TGraphAsymmErrors *TTbar_Quad45_Efficiency_L1filter = (TGraphAsymmErrors*) fTrig->Get("TTbar_Quad45_Efficiency_L1filter");
    TGraphAsymmErrors *TTbar_Quad45_Efficiency_QuadCentralJet45 = (TGraphAsymmErrors*) fTrig->Get("TTbar_Quad45_Efficiency_QuadCentralJet45");
    TGraphAsymmErrors *TTbar_Quad45_Efficiency_BTagCaloCSVp087Triple = (TGraphAsymmErrors*) fTrig->Get("TTbar_Quad45_Efficiency_BTagCaloCSVp087Triple");
    TGraphAsymmErrors *TTbar_Quad45_Efficiency_QuadPFCentralJetLooseID45 = (TGraphAsymmErrors*) fTrig->Get("TTbar_Quad45_Efficiency_QuadPFCentralJetLooseID45");

    TGraphAsymmErrors *TTbar_And_Efficiency_L1filterQuad45 = (TGraphAsymmErrors*) fTrig->Get("TTbar_And_Efficiency_L1filterQuad45");
    TGraphAsymmErrors *TTbar_And_Efficiency_QuadCentralJet45 = (TGraphAsymmErrors*) fTrig->Get("TTbar_And_Efficiency_QuadCentralJet45");
    TGraphAsymmErrors *TTbar_And_Efficiency_BTagCaloCSVp087Triple = (TGraphAsymmErrors*) fTrig->Get("TTbar_And_Efficiency_BTagCaloCSVp087Triple");
    TGraphAsymmErrors *TTbar_And_Efficiency_QuadPFCentralJetLooseID45 = (TGraphAsymmErrors*) fTrig->Get("TTbar_And_Efficiency_QuadPFCentralJetLooseID45");
    
        
    // declaring the output tree - use the output_tree class
    // output variables are defined inside there
    output_tree otree;

    // prepare the input tree reader and run the event loop
    input_tree itree(tIn, sample_type);

    const auto nEv = tIn->GetEntries();
    for (uint iEv = 0; iEv < nEv; ++iEv)
    {
        tIn->GetEntry(iEv);

        if (iEv % 10000 == 0)
            cout << "... doing event " << iEv << " / " << nEv << endl;

        otree.clear_vars();

        // prepare the objects of the 4 jets
        jet_t jet1, jet2, jet3, jet4;
        // the macros below copy the properties of the jet with the specified index (1,2,3,4) to the jet object (jet1,jet2,jet3,jet4)
        init_jet_t(jet1, 1, itree, sample_type) ;
        init_jet_t(jet2, 2, itree, sample_type) ;
        init_jet_t(jet3, 3, itree, sample_type) ;
        init_jet_t(jet4, 4, itree, sample_type) ;

        // compute regressed quantities and other member variables
        jet1.pt_breg = jet1.bRegCorr * jet1.pt;
        jet1.m_breg  = jet1.bRegCorr * jet1.m;
        jet1.p4      .SetPtEtaPhiM(jet1.pt,      jet1.eta, jet1.phi, jet1.m);
        jet1.p4_breg .SetPtEtaPhiM(jet1.pt_breg, jet1.eta, jet1.phi, jet1.m_breg);

        jet2.pt_breg = jet2.bRegCorr * jet2.pt;
        jet2.m_breg  = jet2.bRegCorr * jet2.m;
        jet2.p4      .SetPtEtaPhiM(jet2.pt,      jet2.eta, jet2.phi, jet2.m);
        jet2.p4_breg .SetPtEtaPhiM(jet2.pt_breg, jet2.eta, jet2.phi, jet2.m_breg);

        jet3.pt_breg = jet3.bRegCorr * jet3.pt;
        jet3.m_breg  = jet3.bRegCorr * jet3.m;
        jet3.p4      .SetPtEtaPhiM(jet3.pt,      jet3.eta, jet3.phi, jet3.m);
        jet3.p4_breg .SetPtEtaPhiM(jet3.pt_breg, jet3.eta, jet3.phi, jet3.m_breg);

        jet4.pt_breg = jet4.bRegCorr * jet4.pt;
        jet4.m_breg  = jet4.bRegCorr * jet4.m;
        jet4.p4      .SetPtEtaPhiM(jet4.pt,      jet4.eta, jet4.phi, jet4.m);
        jet4.p4_breg .SetPtEtaPhiM(jet4.pt_breg, jet4.eta, jet4.phi, jet4.m_breg);

        // ========================================
        // ========================================
        // ---- here goes your analysis code to build the high level objects
        // cout << "JET 1 : " << jet1.pt << " " << jet1.eta << " " << jet1.genjet_pt << " " << endl;
        // cout << "JET 2 : " << jet2.pt << " " << jet2.eta << " " << jet2.genjet_pt << " " << endl;
        // cout << "JET 3 : " << jet3.pt << " " << jet3.eta << " " << jet3.genjet_pt << " " << endl;
        // cout << "JET 4 : " << jet4.pt << " " << jet4.eta << " " << jet4.genjet_pt << " " << endl;
        // cout << " -------------------------------------- " << endl;

        // pair the jets, using diagonal grouping
	std::vector<jet_t> jets {jet1, jet2, jet3, jet4};
        std::vector<jet_t> result = bbbb_jets_idxs_BothClosestToDiagonal(&jets);

        TLorentzVector v_H1, v_H2, v_HH;
        v_H1 = result.at(0).p4_breg + result.at(1).p4_breg;
        v_H2 = result.at(2).p4_breg + result.at(3).p4_breg;

        // order them by highest pT: pt(H1) > pt(H2)

        jet_t H1_b1 = result.at(0);
        jet_t H1_b2 = result.at(1);
        jet_t H2_b1 = result.at(2);
        jet_t H2_b2 = result.at(3);

        if (v_H1.Pt() < v_H2.Pt()){
            std::swap(v_H1, v_H2);
            std::swap(H1_b1, H2_b1);
            std::swap(H1_b2, H2_b2);
        }

        v_HH = v_H1 + v_H2;

	////////////////////////////////////
	////// Scale factor calculation //// 
	//////////////////////////////////// 
	
	float aJetPt[] = {jet1.pt, jet2.pt, jet3.pt, jet4.pt};  
	std::vector<float> vJetPt (aJetPt, aJetPt+4);
	std::sort(vJetPt.begin(), vJetPt.end());  // Sort in ascending order
	
	float aBtagScore[] = {jet1.btagscore, jet2.btagscore, jet3.btagscore, jet4.btagscore};
	std::vector<float> vBtagScore (aBtagScore, aBtagScore + 4);
	std::sort(vBtagScore.begin(), vBtagScore.end());

        // Multiply all the relevant trigger efficiencies in this path (See TWiki)             
        float fourhighestJetPt_sum = jet1.pt + jet2.pt + jet3.pt + jet4.pt;
        float secondHighestJetPt_pt = vJetPt[2]; // Vectors in C++ are zero-indexed
        float fourthHighestJetPt_pt = vJetPt[0];
        float firstHighestBTagScore_BTagScore = vBtagScore[3]; 

	// Efficiency from data

        float effDataDouble90Quad30 = (SingleMuon_Double90Quad30_Efficiency_L1filter->Eval(fourhighestJetPt_sum) *
                                       SingleMuon_Double90Quad30_Efficiency_QuadCentralJet30->Eval(fourthHighestJetPt_pt) *
                                       SingleMuon_Double90Quad30_Efficiency_DoubleCentralJet90->Eval(secondHighestJetPt_pt) *
                                       SingleMuon_Double90Quad30_Efficiency_BTagCaloCSVp087Triple->Eval(firstHighestBTagScore_BTagScore) *
                                       SingleMuon_Double90Quad30_Efficiency_QuadPFCentralJetLooseID30->Eval(fourthHighestJetPt_pt) *
                                       SingleMuon_Double90Quad30_Efficiency_DoublePFCentralJetLooseID90->Eval(secondHighestJetPt_pt)); 

        float effDataQuad45 = (SingleMuon_Quad45_Efficiency_L1filter->Eval(fourhighestJetPt_sum) *
                               SingleMuon_Quad45_Efficiency_QuadCentralJet45->Eval(fourthHighestJetPt_pt) *
                               SingleMuon_Quad45_Efficiency_BTagCaloCSVp087Triple->Eval(firstHighestBTagScore_BTagScore) * 
                               SingleMuon_Quad45_Efficiency_QuadPFCentralJetLooseID45->Eval(fourthHighestJetPt_pt));

        float effDataQuad45_DJ = (SingleMuon_And_Efficiency_L1filterQuad45->Eval(fourhighestJetPt_sum) *
                                  SingleMuon_And_Efficiency_QuadCentralJet45->Eval(fourthHighestJetPt_pt) *
                                  SingleMuon_And_Efficiency_BTagCaloCSVp087Triple->Eval(firstHighestBTagScore_BTagScore) * 
                                  SingleMuon_And_Efficiency_QuadPFCentralJetLooseID45->Eval(fourthHighestJetPt_pt)); 

        float effDataDouble90Quad30_and_effDataQuad45 =  effDataDouble90Quad30 * effDataQuad45_DJ;


        float effData = effDataDouble90Quad30 + effDataQuad45 - effDataDouble90Quad30_and_effDataQuad45;


        // Efficiency from MC
        float effMCDouble90Quad30 = (TTbar_Double90Quad30_Efficiency_L1filter->Eval(fourhighestJetPt_sum) *
                                     TTbar_Double90Quad30_Efficiency_QuadCentralJet30->Eval(fourthHighestJetPt_pt) *
                                     TTbar_Double90Quad30_Efficiency_DoubleCentralJet90->Eval(secondHighestJetPt_pt) *
                                     TTbar_Double90Quad30_Efficiency_BTagCaloCSVp087Triple->Eval(firstHighestBTagScore_BTagScore) *
                                     TTbar_Double90Quad30_Efficiency_QuadPFCentralJetLooseID30->Eval(fourthHighestJetPt_pt) *
                                     TTbar_Double90Quad30_Efficiency_DoublePFCentralJetLooseID90->Eval(secondHighestJetPt_pt)); 

        float effMCQuad45 = (TTbar_Quad45_Efficiency_L1filter->Eval(fourhighestJetPt_sum) *
                             TTbar_Quad45_Efficiency_QuadCentralJet45->Eval(fourthHighestJetPt_pt) *
                             TTbar_Quad45_Efficiency_BTagCaloCSVp087Triple->Eval(firstHighestBTagScore_BTagScore) *
                             TTbar_Quad45_Efficiency_QuadPFCentralJetLooseID45->Eval(fourthHighestJetPt_pt));

        float effMCQuad45_DJ = (TTbar_And_Efficiency_L1filterQuad45->Eval(fourhighestJetPt_sum) *
                                TTbar_And_Efficiency_QuadCentralJet45->Eval(fourthHighestJetPt_pt) *
                                TTbar_And_Efficiency_BTagCaloCSVp087Triple->Eval(firstHighestBTagScore_BTagScore) *
                                TTbar_And_Efficiency_QuadPFCentralJetLooseID45->Eval(fourthHighestJetPt_pt));


        float effMCDouble90Quad30_and_effMCQuad45 = effMCDouble90Quad30 * effMCQuad45_DJ; 

        float effMC = effMCDouble90Quad30 + effMCQuad45 - effMCDouble90Quad30_and_effMCQuad45;  

        float scale_factor = effData/effMC; 

	if (effMC == 0)
	  printf("%f = effMC \n");
	//	printf("%f = scale factor\n", scale_factor);

        // ========================================
        // ========================================

        // copy to the output
        otree.H1_pt_  = v_H1.Pt();
        otree.H1_eta_ = v_H1.Eta();
        otree.H1_phi_ = v_H1.Phi();
        otree.H1_m_   = v_H1.M();

        otree.H2_pt_  = v_H2.Pt();
        otree.H2_eta_ = v_H2.Eta();
        otree.H2_phi_ = v_H2.Phi();
        otree.H2_m_   = v_H2.M();

        otree.HH_pt_  = v_HH.Pt();
        otree.HH_eta_ = v_HH.Eta();
        otree.HH_phi_ = v_HH.Phi();
        otree.HH_m_   = v_HH.M();

        otree.H1_b1_pt_  = H1_b1.p4_breg.Pt();
        otree.H1_b1_eta_ = H1_b1.p4_breg.Eta();
        otree.H1_b1_phi_ = H1_b1.p4_breg.Phi();
        otree.H1_b1_m_   = H1_b1.p4_breg.M();

        otree.H1_b2_pt_  = H1_b2.p4_breg.Pt();
        otree.H1_b2_eta_ = H1_b2.p4_breg.Eta();
        otree.H1_b2_phi_ = H1_b2.p4_breg.Phi();
        otree.H1_b2_m_   = H1_b2.p4_breg.M();

        otree.H2_b1_pt_  = H2_b1.p4_breg.Pt();
        otree.H2_b1_eta_ = H2_b1.p4_breg.Eta();
        otree.H2_b1_phi_ = H2_b1.p4_breg.Phi();
        otree.H2_b1_m_   = H2_b1.p4_breg.M();

        otree.H2_b2_pt_  = H2_b2.p4_breg.Pt();
        otree.H2_b2_eta_ = H2_b2.p4_breg.Eta();
        otree.H2_b2_phi_ = H2_b2.p4_breg.Phi();
        otree.H2_b2_m_   = H2_b2.p4_breg.M();

        otree.H1H2_deltaEta_   = std::abs( v_H1.Eta() - v_H2.Eta() );
        otree.H1H2_deltaPhi_   = v_H1.DeltaPhi(v_H2);

        // boost H1 to the bbbb CM
        TLorentzVector vH1_cm = v_H1;
        vH1_cm.Boost(-v_HH.BoostVector());
        otree.H1_costhetaCM_  = vH1_cm.CosTheta();

        // and fw from the input
        otree.run_                = **(itree.run);
        otree.luminosityBlock_    = **(itree.luminosityBlock);
        otree.event_              = **(itree.event);
        otree.xs_                 = **(itree.xs);

        otree.btag_SF_            = **(itree.btag_SF);
        otree.btag_SF_bup_        = **(itree.btag_SF_bup);
        otree.btag_SF_bdown_      = **(itree.btag_SF_bdown);
        otree.btag_SF_cup_        = **(itree.btag_SF_cup);
        otree.btag_SF_cdown_      = **(itree.btag_SF_cdown);
        otree.btag_SF_lightup_    = **(itree.btag_SF_lightup);
        otree.btag_SF_lightdown_  = **(itree.btag_SF_lightdown);
        otree.norm_weight_        = **(itree.norm_weight);

        otree.n_btag_ = 0;
        if (result.at(0).btagscore > btag_WP_medium) ++otree.n_btag_;
        if (result.at(1).btagscore > btag_WP_medium) ++otree.n_btag_;
        if (result.at(2).btagscore > btag_WP_medium) ++otree.n_btag_;
        if (result.at(3).btagscore > btag_WP_medium) ++otree.n_btag_;

        otree.rndm_1_ = **(itree.rndm_1);
        otree.rndm_2_ = **(itree.rndm_2);
        otree.rndm_3_ = **(itree.rndm_3);
	
	otree.trigger_SF_ = scale_factor;

        otree.fill();
    }

    // save to output
    fOut->cd();
    otree.write();

    fIn->Close();
    fOut->Close();

}
