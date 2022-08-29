# NeuroTechnology VeriEye on CRC Instructions

- Log into the CRC frontend of your choice. 

- (~2 minutes) Download "MegaMatcher, VeriFinger, VeriLook, VeriSpeak, and VeriEye SDK Trial" with this command: 

```
wget https://www.neurotechnology.com/download.html#megamatcher_verifinger_verilook_verieye_sdk_trial.zip
```

- (~2 minutes) Unzip the downloaded SDK zip file. Note that this SDK is a trial version, so frontend runs won't work after the 30-day trial/grace period. The @czajka hostgroup has a full license, so you have to submit jobs to this hostgroup later.

```
unzip Neurotec_Biometric_12_3_SDK_2022-07-07.zip
```

- If you want to extract iris templates from images, then navigate to the proper directory in the SDK folder.

```
cd Neurotec_Biometric_12_3_SDK/Tutorials/Biometrics/CPP/EnrollIrisFromImage/
```

- Depending on how many images you want to create templates for, create corresponding "filename" file(s). These "filename" files look like this for N image files:

```
<image_filename1> <template_filename1>
<image_filename2> <template_filename2>
...
<image_filenameN> <template_filenameN>

# I like to use absolute paths for filenames
# in this instance, but that's just me.
```

- In the case of a lot of images (> several thousand), I suggest using the task array functionality of the CRC. This means that you have to get a bit creative with splitting up image filenames and naming convention for the "filename" files. Different job submission scripts for the two scenarios are included in this repo. Note that AFS has a file limit of ~64k, so you may need to create several different directories to hold all the templates.

- Replace the original SDK EnrollIrisFromImage.cpp file with the file in this repo. If you want to keep the original, I recommend renaming the original EnrollIrisFromImageCPP.cpp file to something else.

- From the frontend, compile the script with a ```make``` command while in the directory.

- Copy/move the job scripts in this repository into the same EnrollIrisFromImage directory.

- Modify the submission job script to your filenames file(s) locations (line 13) and ```qsub``` the job script.

- Once templates are generated, you can run the IdentifyIrisCPP file (still to be done -- will add to this readme and repo when that's done).

- Slack me (PT) or reach out via email (ptinsley@nd.edu) if you have any questions/troubles. 
