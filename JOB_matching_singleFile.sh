#!/bin/bash
#$ -q gpu@@czajka
#$ -l gpu_card=0
#$ -N neurotec


####################### DO_NOT_TOUCH!! ###############################

cd ~/Neurotec_Biometric_12_3_SDK/Tutorials/Biometrics/CPP/VerifyIrisCPP/

######################################################################

./VerifyIrisCPP matching.txt scores.txt

# In this case, the "matching" file would be named matching.txt.
# The output score file would be named scores.txt.