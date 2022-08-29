#!/bin/bash
#$ -q gpu@@czajka
#$ -l gpu_card=0
#$ -N neurotec


####################### DO_NOT_TOUCH!! ###############################

cd ~/Neurotec_Biometric_12_3_SDK/Tutorials/Biometrics/CPP/EnrollIrisFromImageCPP/

######################################################################

./EnrollIrisFromImageCPP fnames.txt

# In this case, the "filename" file would be named fnames.txt.