#!/bin/bash
#$ -q gpu@@czajka
#$ -l gpu_card=0
#$ -N neurotec
#$ -t 1-5

####################### DO_NOT_TOUCH!! ###############################

cd ~/Neurotec_Biometric_12_3_SDK/Tutorials/Biometrics/CPP/EnrollIrisFromImageCPP/

######################################################################

./EnrollIrisFromImageCPP fnames$SGE_TASK_ID.txt.txt

# In this case, the "filename" files would be named fnames1.txt, fnames2.txt, fnames3.txt, fnames4.txt and fnames5.txt.