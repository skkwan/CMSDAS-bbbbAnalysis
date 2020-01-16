#ifndef INPUT_TREE_H
#define INPUT_TREE_H

#include "TTree.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TTreeReaderArray.h"

#include <iostream>

class input_tree {
    public:

        enum sample_type{
            kData = 0,
            kBkg = 1,
            kSig = 2
        };

        input_tree(TTree* tIn, std::string sampletype);
        ~input_tree();

        bool Next();

        TTreeReader   fReader;

        std::unique_ptr<TTreeReaderValue<unsigned int>> run;                  
        std::unique_ptr<TTreeReaderValue<unsigned int>> luminosityBlock;      
        std::unique_ptr<TTreeReaderValue<long long>> event;                   
        std::unique_ptr<TTreeReaderValue<float>> xs;                          

        std::unique_ptr<TTreeReaderValue<float>> btag_SF;                     
        std::unique_ptr<TTreeReaderValue<float>> btag_SF_bup;                 
        std::unique_ptr<TTreeReaderValue<float>> btag_SF_bdown;               
        std::unique_ptr<TTreeReaderValue<float>> btag_SF_cup;                 
        std::unique_ptr<TTreeReaderValue<float>> btag_SF_cdown;               
        std::unique_ptr<TTreeReaderValue<float>> btag_SF_lightup;             
        std::unique_ptr<TTreeReaderValue<float>> btag_SF_lightdown;           
        // std::unique_ptr<TTreeReaderValue<float>> weight;                   
        std::unique_ptr<TTreeReaderValue<float>> norm_weight;                 

        std::unique_ptr<TTreeReaderValue<float>> jet1_pt;                     
        std::unique_ptr<TTreeReaderValue<float>> jet1_eta;                    
        std::unique_ptr<TTreeReaderValue<float>> jet1_phi;                    
        std::unique_ptr<TTreeReaderValue<float>> jet1_m;                      
        std::unique_ptr<TTreeReaderValue<float>> jet1_btagscore;              
        std::unique_ptr<TTreeReaderValue<float>> jet1_bRegCorr;               
        std::unique_ptr<TTreeReaderValue<float>> jet1_bRegRes;                
        std::unique_ptr<TTreeReaderValue<int>> jet1_jetId;                    
        std::unique_ptr<TTreeReaderValue<int>> jet1_puId;                     
        std::unique_ptr<TTreeReaderValue<int>> jet1_hadronFlavour;            

        std::unique_ptr<TTreeReaderValue<float>> jet2_pt;                     
        std::unique_ptr<TTreeReaderValue<float>> jet2_eta;                    
        std::unique_ptr<TTreeReaderValue<float>> jet2_phi;                    
        std::unique_ptr<TTreeReaderValue<float>> jet2_m;                      
        std::unique_ptr<TTreeReaderValue<float>> jet2_btagscore;              
        std::unique_ptr<TTreeReaderValue<float>> jet2_bRegCorr;               
        std::unique_ptr<TTreeReaderValue<float>> jet2_bRegRes;                
        std::unique_ptr<TTreeReaderValue<int>> jet2_jetId;                    
        std::unique_ptr<TTreeReaderValue<int>> jet2_puId;                     
        std::unique_ptr<TTreeReaderValue<int>> jet2_hadronFlavour;            

        std::unique_ptr<TTreeReaderValue<float>> jet3_pt;                     
        std::unique_ptr<TTreeReaderValue<float>> jet3_eta;                    
        std::unique_ptr<TTreeReaderValue<float>> jet3_phi;                    
        std::unique_ptr<TTreeReaderValue<float>> jet3_m;                      
        std::unique_ptr<TTreeReaderValue<float>> jet3_btagscore;              
        std::unique_ptr<TTreeReaderValue<float>> jet3_bRegCorr;               
        std::unique_ptr<TTreeReaderValue<float>> jet3_bRegRes;                
        std::unique_ptr<TTreeReaderValue<int>> jet3_jetId;                    
        std::unique_ptr<TTreeReaderValue<int>> jet3_puId;                     
        std::unique_ptr<TTreeReaderValue<int>> jet3_hadronFlavour;            

        std::unique_ptr<TTreeReaderValue<float>> jet4_pt;                     
        std::unique_ptr<TTreeReaderValue<float>> jet4_eta;                    
        std::unique_ptr<TTreeReaderValue<float>> jet4_phi;                    
        std::unique_ptr<TTreeReaderValue<float>> jet4_m;                      
        std::unique_ptr<TTreeReaderValue<float>> jet4_btagscore;              
        std::unique_ptr<TTreeReaderValue<float>> jet4_bRegCorr;               
        std::unique_ptr<TTreeReaderValue<float>> jet4_bRegRes;                
        std::unique_ptr<TTreeReaderValue<int>> jet4_jetId;                    
        std::unique_ptr<TTreeReaderValue<int>> jet4_puId;                     
        std::unique_ptr<TTreeReaderValue<int>> jet4_hadronFlavour;            

        std::unique_ptr<TTreeReaderValue<float>> genjet1_pt;                  
        std::unique_ptr<TTreeReaderValue<float>> genjet1_eta;                 
        std::unique_ptr<TTreeReaderValue<float>> genjet1_phi;                 
        std::unique_ptr<TTreeReaderValue<float>> genjet1_m;                   
        // std::unique_ptr<TTreeReaderValue<int>> genjet1_partonFlavour;         
        std::unique_ptr<TTreeReaderValue<int>> genjet1_hadronFlavour;         

        std::unique_ptr<TTreeReaderValue<float>> genjet2_pt;                  
        std::unique_ptr<TTreeReaderValue<float>> genjet2_eta;                 
        std::unique_ptr<TTreeReaderValue<float>> genjet2_phi;                 
        std::unique_ptr<TTreeReaderValue<float>> genjet2_m;                   
        // std::unique_ptr<TTreeReaderValue<int>> genjet2_partonFlavour;         
        std::unique_ptr<TTreeReaderValue<int>> genjet2_hadronFlavour;         

        std::unique_ptr<TTreeReaderValue<float>> genjet3_pt;                  
        std::unique_ptr<TTreeReaderValue<float>> genjet3_eta;                 
        std::unique_ptr<TTreeReaderValue<float>> genjet3_phi;                 
        std::unique_ptr<TTreeReaderValue<float>> genjet3_m;                   
        // std::unique_ptr<TTreeReaderValue<int>> genjet3_partonFlavour;         
        std::unique_ptr<TTreeReaderValue<int>> genjet3_hadronFlavour;         

        std::unique_ptr<TTreeReaderValue<float>> genjet4_pt;                  
        std::unique_ptr<TTreeReaderValue<float>> genjet4_eta;                 
        std::unique_ptr<TTreeReaderValue<float>> genjet4_phi;                 
        std::unique_ptr<TTreeReaderValue<float>> genjet4_m;                   
        // std::unique_ptr<TTreeReaderValue<int>> genjet4_partonFlavour;         
        std::unique_ptr<TTreeReaderValue<int>> genjet4_hadronFlavour;         

        std::unique_ptr<TTreeReaderValue<float>> gen_H1_m;                    
        std::unique_ptr<TTreeReaderValue<float>> gen_H1_pt;                   
        std::unique_ptr<TTreeReaderValue<float>> gen_H1_eta;                  
        std::unique_ptr<TTreeReaderValue<float>> gen_H1_phi;                  

        std::unique_ptr<TTreeReaderValue<float>> gen_H2_m;                    
        std::unique_ptr<TTreeReaderValue<float>> gen_H2_pt;                   
        std::unique_ptr<TTreeReaderValue<float>> gen_H2_eta;                  
        std::unique_ptr<TTreeReaderValue<float>> gen_H2_phi;                  

        std::unique_ptr<TTreeReaderValue<float>> gen_mHH;                     
        std::unique_ptr<TTreeReaderValue<float>> gen_costh_H1_cm;             
        std::unique_ptr<TTreeReaderValue<float>> gen_costh_H2_cm;             

        std::unique_ptr<TTreeReaderValue<float>> gen_H1_b1_m;                 
        std::unique_ptr<TTreeReaderValue<float>> gen_H1_b1_pt;                
        std::unique_ptr<TTreeReaderValue<float>> gen_H1_b1_eta;               
        std::unique_ptr<TTreeReaderValue<float>> gen_H1_b1_phi;               

        std::unique_ptr<TTreeReaderValue<float>> gen_H1_b2_m;                 
        std::unique_ptr<TTreeReaderValue<float>> gen_H1_b2_pt;                
        std::unique_ptr<TTreeReaderValue<float>> gen_H1_b2_eta;               
        std::unique_ptr<TTreeReaderValue<float>> gen_H1_b2_phi;               

        std::unique_ptr<TTreeReaderValue<float>> gen_H2_b1_m;                 
        std::unique_ptr<TTreeReaderValue<float>> gen_H2_b1_pt;                
        std::unique_ptr<TTreeReaderValue<float>> gen_H2_b1_eta;               
        std::unique_ptr<TTreeReaderValue<float>> gen_H2_b1_phi;               

        std::unique_ptr<TTreeReaderValue<float>> gen_H2_b2_m;                 
        std::unique_ptr<TTreeReaderValue<float>> gen_H2_b2_pt;                
        std::unique_ptr<TTreeReaderValue<float>> gen_H2_b2_eta;               
        std::unique_ptr<TTreeReaderValue<float>> gen_H2_b2_phi;               

        std::unique_ptr<TTreeReaderValue<float>> rndm_1;                
        std::unique_ptr<TTreeReaderValue<float>> rndm_2;               
        std::unique_ptr<TTreeReaderValue<float>> rndm_3;               

    private:
        void init();
        sample_type stype_;
};  

input_tree::input_tree(TTree* tIn, std::string sampletype):
    fReader(tIn)
{
    if (sampletype == "sig")
        stype_ = kSig;
    else if (sampletype == "bkg")
        stype_ = kBkg;
    else if (sampletype == "data")
        stype_ = kData;
    else {
        std::cout << "[ERROR] input_tree : could not recognize sample type " << sampletype << " (must be sig, bkg, data)" << std::endl;
        throw std::runtime_error("sample type is wrong");
    }
    
    init();
    fReader.SetEntry(0); // start from 0
}

input_tree::~input_tree()
{}    

bool input_tree::Next()
{
    bool next = fReader.Next();
    return next;
}

void input_tree::init()
{

    run                   = std::unique_ptr<TTreeReaderValue<unsigned int>>  (new TTreeReaderValue<unsigned int>   (fReader, "run"));
    luminosityBlock       = std::unique_ptr<TTreeReaderValue<unsigned int>>  (new TTreeReaderValue<unsigned int>   (fReader, "luminosityBlock"));
    event                 = std::unique_ptr<TTreeReaderValue<long long>>     (new TTreeReaderValue<long long>      (fReader, "event"));
    xs                    = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "xs"));

    btag_SF               = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "btag_SF"));
    btag_SF_bup           = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "btag_SF_bup"));
    btag_SF_bdown         = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "btag_SF_bdown"));
    btag_SF_cup           = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "btag_SF_cup"));
    btag_SF_cdown         = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "btag_SF_cdown"));
    btag_SF_lightup       = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "btag_SF_lightup"));
    btag_SF_lightdown     = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "btag_SF_lightdown"));

    //weight                = // std::unique_ptr<TTreeReaderValue<float>>      (new TTreeReaderValue<float>          (fReader, "weight")); // not to be used
    norm_weight           = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "norm_weight"));
    
    jet1_pt               = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "jet1_pt"));
    jet1_eta              = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "jet1_eta"));
    jet1_phi              = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "jet1_phi"));
    jet1_m                = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "jet1_m"));
    jet1_btagscore        = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "jet1_btagscore"));
    jet1_bRegCorr         = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "jet1_bRegCorr"));
    jet1_bRegRes          = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "jet1_bRegRes"));
    jet1_jetId            = std::unique_ptr<TTreeReaderValue<int>>           (new TTreeReaderValue<int>            (fReader, "jet1_jetId"));
    jet1_puId             = std::unique_ptr<TTreeReaderValue<int>>           (new TTreeReaderValue<int>            (fReader, "jet1_puId"));
    if (stype_ != kData) jet1_hadronFlavour    = std::unique_ptr<TTreeReaderValue<int>>           (new TTreeReaderValue<int>            (fReader, "jet1_hadronFlavour"));
    
    jet2_pt               = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "jet2_pt"));
    jet2_eta              = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "jet2_eta"));
    jet2_phi              = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "jet2_phi"));
    jet2_m                = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "jet2_m"));
    jet2_btagscore        = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "jet2_btagscore"));
    jet2_bRegCorr         = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "jet2_bRegCorr"));
    jet2_bRegRes          = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "jet2_bRegRes"));
    jet2_jetId            = std::unique_ptr<TTreeReaderValue<int>>           (new TTreeReaderValue<int>            (fReader, "jet2_jetId"));
    jet2_puId             = std::unique_ptr<TTreeReaderValue<int>>           (new TTreeReaderValue<int>            (fReader, "jet2_puId"));
    if (stype_ != kData) jet2_hadronFlavour    = std::unique_ptr<TTreeReaderValue<int>>           (new TTreeReaderValue<int>            (fReader, "jet2_hadronFlavour"));
    
    jet3_pt               = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "jet3_pt"));
    jet3_eta              = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "jet3_eta"));
    jet3_phi              = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "jet3_phi"));
    jet3_m                = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "jet3_m"));
    jet3_btagscore        = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "jet3_btagscore"));
    jet3_bRegCorr         = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "jet3_bRegCorr"));
    jet3_bRegRes          = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "jet3_bRegRes"));
    jet3_jetId            = std::unique_ptr<TTreeReaderValue<int>>           (new TTreeReaderValue<int>            (fReader, "jet3_jetId"));
    jet3_puId             = std::unique_ptr<TTreeReaderValue<int>>           (new TTreeReaderValue<int>            (fReader, "jet3_puId"));
    if (stype_ != kData) jet3_hadronFlavour    = std::unique_ptr<TTreeReaderValue<int>>           (new TTreeReaderValue<int>            (fReader, "jet3_hadronFlavour"));
    
    jet4_pt               = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "jet4_pt"));
    jet4_eta              = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "jet4_eta"));
    jet4_phi              = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "jet4_phi"));
    jet4_m                = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "jet4_m"));
    jet4_btagscore        = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "jet4_btagscore"));
    jet4_bRegCorr         = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "jet4_bRegCorr"));
    jet4_bRegRes          = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "jet4_bRegRes"));
    jet4_jetId            = std::unique_ptr<TTreeReaderValue<int>>           (new TTreeReaderValue<int>            (fReader, "jet4_jetId"));
    jet4_puId             = std::unique_ptr<TTreeReaderValue<int>>           (new TTreeReaderValue<int>            (fReader, "jet4_puId"));
    if (stype_ != kData) jet4_hadronFlavour    = std::unique_ptr<TTreeReaderValue<int>>           (new TTreeReaderValue<int>            (fReader, "jet4_hadronFlavour"));
   
    if (stype_ != kData) {
        genjet1_pt            = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "genjet1_pt"));
        genjet1_eta           = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "genjet1_eta"));
        genjet1_phi           = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "genjet1_phi"));
        genjet1_m             = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "genjet1_m"));
        // genjet1_partonFlavour = std::unique_ptr<TTreeReaderValue<int>>           (new TTreeReaderValue<int>            (fReader, "genjet1_partonFlavour"));
        genjet1_hadronFlavour = std::unique_ptr<TTreeReaderValue<int>>           (new TTreeReaderValue<int>            (fReader, "genjet1_hadronFlavour"));
        
        genjet2_pt            = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "genjet2_pt"));
        genjet2_eta           = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "genjet2_eta"));
        genjet2_phi           = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "genjet2_phi"));
        genjet2_m             = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "genjet2_m"));
        // genjet2_partonFlavour = std::unique_ptr<TTreeReaderValue<int>>           (new TTreeReaderValue<int>            (fReader, "genjet2_partonFlavour"));
        genjet2_hadronFlavour = std::unique_ptr<TTreeReaderValue<int>>           (new TTreeReaderValue<int>            (fReader, "genjet2_hadronFlavour"));
        
        genjet3_pt            = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "genjet3_pt"));
        genjet3_eta           = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "genjet3_eta"));
        genjet3_phi           = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "genjet3_phi"));
        genjet3_m             = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "genjet3_m"));
        // genjet3_partonFlavour = std::unique_ptr<TTreeReaderValue<int>>           (new TTreeReaderValue<int>            (fReader, "genjet3_partonFlavour"));
        genjet3_hadronFlavour = std::unique_ptr<TTreeReaderValue<int>>           (new TTreeReaderValue<int>            (fReader, "genjet3_hadronFlavour"));
        
        genjet4_pt            = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "genjet4_pt"));
        genjet4_eta           = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "genjet4_eta"));
        genjet4_phi           = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "genjet4_phi"));
        genjet4_m             = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "genjet4_m"));
        // genjet4_partonFlavour = std::unique_ptr<TTreeReaderValue<int>>           (new TTreeReaderValue<int>            (fReader, "genjet4_partonFlavour"));
        genjet4_hadronFlavour = std::unique_ptr<TTreeReaderValue<int>>           (new TTreeReaderValue<int>            (fReader, "genjet4_hadronFlavour"));
    }

    if (stype_ == kSig) {
        gen_H1_m              = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "gen_H1_m"));
        gen_H1_pt             = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "gen_H1_pt"));
        gen_H1_eta            = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "gen_H1_eta"));
        gen_H1_phi            = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "gen_H1_phi"));
       
        gen_H2_m              = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "gen_H2_m"));
        gen_H2_pt             = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "gen_H2_pt"));
        gen_H2_eta            = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "gen_H2_eta"));
        gen_H2_phi            = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "gen_H2_phi"));
       
        gen_mHH               = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "gen_mHH"));
        gen_costh_H1_cm       = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "gen_costh_H1_cm"));
        gen_costh_H2_cm       = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "gen_costh_H2_cm"));
       
        gen_H1_b1_m           = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "gen_H1_b1_m"));
        gen_H1_b1_pt          = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "gen_H1_b1_pt"));
        gen_H1_b1_eta         = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "gen_H1_b1_eta"));
        gen_H1_b1_phi         = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "gen_H1_b1_phi"));
       
        gen_H1_b2_m           = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "gen_H1_b2_m"));
        gen_H1_b2_pt          = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "gen_H1_b2_pt"));
        gen_H1_b2_eta         = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "gen_H1_b2_eta"));
        gen_H1_b2_phi         = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "gen_H1_b2_phi"));
       
        gen_H2_b1_m           = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "gen_H2_b1_m"));
        gen_H2_b1_pt          = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "gen_H2_b1_pt"));
        gen_H2_b1_eta         = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "gen_H2_b1_eta"));
        gen_H2_b1_phi         = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "gen_H2_b1_phi"));
       
        gen_H2_b2_m           = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "gen_H2_b2_m"));
        gen_H2_b2_pt          = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "gen_H2_b2_pt"));
        gen_H2_b2_eta         = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "gen_H2_b2_eta"));
        gen_H2_b2_phi         = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "gen_H2_b2_phi"));
    }

    rndm_1 = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "rndm_1"));
    rndm_2 = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "rndm_2"));
    rndm_3 = std::unique_ptr<TTreeReaderValue<float>>         (new TTreeReaderValue<float>          (fReader, "rndm_3"));
}


#endif
