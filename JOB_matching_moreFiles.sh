#!/bin/bash
#$ -q gpu@@czajka
#$ -l gpu_card=0
#$ -N neurotec
#$ -t 1-5

####################### DO_NOT_TOUCH!! ###############################

cd ~/Neurotec_Biometric_12_3_SDK/Tutorials/Biometrics/CPP/VerifyIrisCPP/

######################################################################

./VerifyIrisCPP matching$SGE_TASK_ID.txt scores$SGE_TASK_ID.txt

# In this case, the "matching" files would be named matching1.txt, matching2.txt, matching3.txt, matching4.txt and matching5.txt.
# The output score files would be scores1.txt, scores2.txt, scores3.txt, scores4.txt and scores5.txt.