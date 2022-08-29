#include <TutorialUtils.hpp>
#include <sys/stat.h>
#include <unistd.h>
#include <string>

#ifdef N_MAC_OSX_FRAMEWORKS
	#include <NCore/NCore.hpp>
	#include <NBiometricClient/NBiometricClient.hpp>
	#include <NBiometrics/NBiometrics.hpp>
	#include <NMedia/NMedia.hpp>
	#include <NLicensing/NLicensing.hpp>
#else
	#include <NCore.hpp>
	#include <NBiometricClient.hpp>
	#include <NBiometrics.hpp>
	#include <NMedia.hpp>
	#include <NLicensing.hpp>
#endif

#include <fstream>

using namespace std;
using namespace Neurotec;
using namespace Neurotec::Licensing;
using namespace Neurotec::Biometrics;
using namespace Neurotec::Biometrics::Client;
using namespace Neurotec::Biometrics::Standards;
using namespace Neurotec::IO;

const NChar title[] = N_T("EnrollIrisFromImage");
const NChar description[] = N_T("Demonstrates enrollment from one image.");
const NChar version[] = N_T("12.3.0.0");
const NChar copyright[] = N_T("Copyright (C) 2016-2022 Neurotechnology");

inline bool exists_test3 (const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}

int usage()
{
	cout << "usage:" << endl;
	cout << "\t" << title << " [image] [template]" << endl << endl;
	cout << "\t[image]    - filename of image." << endl;
	cout << "\t[template] - filename for template." << endl;
	return 1;
}

int main(int argc, NChar **argv)
{
	OnStart(title, description, version, copyright, argc, argv);

	/*if (argc < 3)
	{
		OnExit();
		return usage();
	}*/

	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	const NString license = N_T("IrisExtractor");
	//const NString license = N_T("IrisClient");
	//const NString license = N_T("IrisFastExtractor");

	//=========================================================================

	//=========================================================================
	// TRIAL MODE
	//=========================================================================
	// Below code line determines whether TRIAL is enabled or not. To use purchased licenses, don't use below code line.
	// GetTrialModeFlag() method takes value from "Bin/Licenses/TrialFlag.txt" file. So, to easily change mode for all our examples, modify that file.
	// Also you can just set TRUE to "TrialMode" property in code.

	//NLicenseManager::SetTrialMode(GetTrialModeFlag());
	NLicenseManager::SetTrialMode(1);
	cout << "Trial mode: " << NLicenseManager::GetTrialMode() << endl;

	//=========================================================================

	try
	{
		// Obtain license
		if (!NLicense::Obtain(N_T("/local"), N_T("5000"), license))
		{
			NThrowException(NString::Format(N_T("Could not obtain license: {S}"), license.GetBuffer())); 
		}

		NBiometricClient biometricClient;
		biometricClient.SetIrisesTemplateSize(ntsLarge);

        ifstream in;
        //in.open("fnames_fake.txt");
        in.open(argv[1]);
        
        string fname, tname;
        
        while(!in.eof()) {
            in >> fname >> tname;
            //cout << fname << " " << tname << endl;

            NIris iris;
    		iris.SetFileName(fname);
    		NSubject subject;
    		subject.GetIrises().Add(iris);
    		
    		NBiometricStatus status = biometricClient.CreateTemplate(subject);
    		if (status == nbsOk)
    		{
    			//cout << "Template extracted" << endl;
    			//NFile::WriteAllBytes(argv[2], subject.GetTemplateBuffer());
    			NFile::WriteAllBytes(tname, subject.GetTemplateBuffer());
    			//cout << "Template saved successfully" << endl;
    		}

    		/*else
    		{
    			//cout << "Extraction failed: " << NEnum::ToString(NBiometricTypes::NBiometricStatusNativeTypeOf(), status) << endl;
    			//return -1;
    		}*/
        }
		 
		/*
		iris.SetFileName(fname);
		NSubject subject;
		subject.GetIrises().Add(iris);
		NBiometricStatus status = biometricClient.CreateTemplate(subject);
		if (status == nbsOk)
		{
			cout << "Template extracted" << endl;
			NFile::WriteAllBytes(argv[2], subject.GetTemplateBuffer());
			cout << "Template saved successfully" << endl;
		}
		else
		{
			cout << "Extraction failed: " << NEnum::ToString(NBiometricTypes::NBiometricStatusNativeTypeOf(), status) << endl;
			return -1;
		}
		*/
	}
	catch (NError& ex)
	{
		return LastError(ex);
	}

	OnExit();
	return 0;
}
