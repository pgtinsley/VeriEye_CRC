#include <TutorialUtils.hpp>

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

using namespace std;
using namespace Neurotec;
using namespace Neurotec::Licensing;
using namespace Neurotec::Biometrics;
using namespace Neurotec::Biometrics::Client;
using namespace Neurotec::Biometrics::Standards;
using namespace Neurotec::IO;

#include <fstream>

const NChar title[] = N_T("EnrollIrisFromImage");
const NChar description[] = N_T("Demonstrates enrollment from one image.");
const NChar version[] = N_T("12.3.0.0");
const NChar copyright[] = N_T("Copyright (C) 2016-2022 Neurotechnology");

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

	/*
	if (argc < 3)
    {
		OnExit();
		return usage();
    }
    */

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
	// GetTrialModeFlag() method takes value from "Bin/Licenses/TrialFlag.txt" file. So to easily change mode for all our examples, modify that file.
	// Also you can just set TRUE to "TrialMode" property in code.

	NLicenseManager::SetTrialMode(GetTrialModeFlag());
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

        // Open filename of image filenames to read in.
        // Format of file looks like:
        // <image_filename1> <template_filename1>
        // <image_filename2> <template_filename2>
        // ...
        // <image_filenameN> <template_filenameN>
        // I like to use absolute paths for filenames in this instance, but that's just me.

        ifstream in;
        in.open(argv[1]);
        string fname, tname;

        // Keep processing until you reach end of file
        while(!in.eof()) {

    		NIris iris;
		
		in >> fname >> tname;
		
    		iris.SetFileName(fname);        // This line changed from SDK original. (argv[1] -> fname)
    		NSubject subject;
    		subject.GetIrises().Add(iris);
    		NBiometricStatus status = biometricClient.CreateTemplate(subject);
    		if (status == nbsOk)
    		{
    			//cout << "Template extracted" << endl;
    			NFile::WriteAllBytes(tname, subject.GetTemplateBuffer());     // This line changed from SDK original. (argv[2] -> tname)
    			//cout << "Template saved successfully" << endl;
    		}
    		else
    		{
    			cout << "Extraction failed: " << NEnum::ToString(NBiometricTypes::NBiometricStatusNativeTypeOf(), status) << endl;
    			return -1;
    		}
        }
	}
	catch (NError& ex)
	{
		return LastError(ex);
	}

	OnExit();
	return 0;
}
