# NOTE ON RUNTIMES

# QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.log
# ... the program took 13 seconds
# QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.log
# ... the program took 3 seconds
# QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.log
# ... the program took 16 seconds
# QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.log
# ... the program took 12 seconds
# QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.log
# ... the program took 4 seconds
# QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.log
# ... the program took 7 seconds
# QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.log
# ... the program took 16 seconds
# QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.log
# ... the program took 17 seconds
# TT_TuneCUETP8M2T4_13TeV-powheg-pythia8.log
# ... the program took 149 seconds
# data_BTagCSV_Run2016_ALL.log
# ... the program took 677 seconds
# gg_HH_bbbb_SM.log
# ... the program took 12 seconds


TAG="analysisNtuples_final"
# IN_FLDR="/store/user/lcadamur/bbbb_ntuples_CMSDAS"
IN_FLDR="/store/user/cmsdas/2020/long_exercises/DoubleHiggs/${TAG}/dasformat"
# TMP_FLDR=`pwd`
DEST_FLDR=`pwd`


SAMPLES_MC=( \
#    QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8  \
#    QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8  \
#    QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8  \
#    QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8  \
#    QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 \
#    QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8  \
#    QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8  \
#    QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 \
#    TT_TuneCUETP8M2T4_13TeV-powheg-pythia8 \
)

SAMPLES_SIG=( \
    gg_HH_bbbb_SM             \
    gg_HH_bbbb_SM_withBDT    \
)

SAMPLES_DATA=( \
#    data_BTagCSV_Run2016_ALL \
)


for sample in ${SAMPLES_MC[*]}; do
    echo ${sample}
    THELOG="logs/${sample}.log"
    touch $THELOG
    (
        echo "... starting" > $THELOG
        start=`date +%s`
        echo ${start} >> $THELOG 
        ./build_objects root://cmseos.fnal.gov/${IN_FLDR}/dasntuples_${sample}.root ${DEST_FLDR}/objects_${sample}.root 0 0 >> ${THELOG} 2>&1
        echo "... program done with status $?" >> $THELOG 
        end=`date +%s`
        echo ${end} >> $THELOG 
        runtime=$((end-start))
        echo "... the program took $runtime seconds" >> $THELOG 
        # xrdcp -f -s ${TMP_FLDR}/dasntuples_${sample}.root root://cmseos.fnal.gov/${DEST_FLDR}/dasntuples_${sample}.root >> $THELOG 2>&1
        # echo "... copy done with status $?" >> $THELOG 
        # rm ${TMP_FLDR}/dasntuples_${sample}.root
    )&
done

for sample in ${SAMPLES_SIG[*]}; do
    echo ${sample}
    THELOG="logs/${sample}.log"
    touch $THELOG
    (
        echo "... starting" > $THELOG
        start=`date +%s`
        echo ${start} >> $THELOG 
        ./build_objects root://cmseos.fnal.gov/${IN_FLDR}/dasntuples_${sample}.root ${DEST_FLDR}/objects_${sample}.root 0 1 >> ${THELOG} 2>&1
        echo "... program done with status $?" >> $THELOG 
        end=`date +%s`
        echo ${end} >> $THELOG 
        runtime=$((end-start))
        echo "... the program took $runtime seconds" >> $THELOG 
        # xrdcp -f -s ${TMP_FLDR}/dasntuples_${sample}.root root://cmseos.fnal.gov/${DEST_FLDR}/dasntuples_${sample}.root >> $THELOG 2>&1
        # echo "... copy done with status $?" >> $THELOG 
        # rm ${TMP_FLDR}/dasntuples_${sample}.root
    )&
done

for sample in ${SAMPLES_DATA[*]}; do
    echo ${sample}
    THELOG="logs/${sample}.log"
    touch $THELOG
    (
        echo "... starting" > $THELOG
        start=`date +%s`
        echo ${start} >> $THELOG 
        ./build_objects root://cmseos.fnal.gov/${IN_FLDR}/dasntuples_${sample}.root ${DEST_FLDR}/objects_${sample}.root 1 0 >> ${THELOG} 2>&1
        echo "... program done with status $?" >> $THELOG 
        end=`date +%s`
        echo ${end} >> $THELOG 
        runtime=$((end-start))
        echo "... the program took $runtime seconds" >> $THELOG 
        # xrdcp -f -s ${TMP_FLDR}/dasntuples_${sample}.root root://cmseos.fnal.gov/${DEST_FLDR}/dasntuples_${sample}.root >> $THELOG 2>&1
        # echo "... copy done with status $?" >> $THELOG 
        # rm ${TMP_FLDR}/dasntuples_${sample}.root
    )&
done


