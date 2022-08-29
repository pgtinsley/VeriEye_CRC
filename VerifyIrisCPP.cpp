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

#include <fstream>

const NChar title[] = N_T("VerifyIris");
const NChar description[] = N_T("Demonstrates iris verification.");
const NChar version[] = N_T("12.3.0.0");
const NChar copyright[] = N_T("Copyright (C) 2016-2022 Neurotechnology");

int usage()
{
	cout << "usage:" << endl;
	cout << "\t" << title << " [reference image] [candidate image]" << endl;
	return 1;
}
static NSubject CreateSubject(const NStringWrapper& subjectId, const NStringWrapper& fileName)
{
	NSubject subject;
	subject.SetId(subjectId);
	NIris iris;
	iris.SetFileName(fileName);
	subject.GetIrises().Add(iris);
	return subject;
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
	// ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	const NChar * licenses = { N_T("IrisMatcher,IrisExtractor") };
	//const NChar * licenses = { N_T("IrisMatcher,IrisClient") };
	//const NChar * licenses = { N_T("IrisFastMatcher,IrisFastExtractor") };

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
		// Obtain licenses
		if (!NLicense::Obtain(N_T("/local"), N_T("5000"), licenses))
		{
			NThrowException(NString::Format(N_T("Could not obtain licenses: {S}"), licenses)); 
		}

		NBiometricClient biometricClient;
		biometricClient.SetMatchingThreshold(48);
		biometricClient.SetIrisesMatchingSpeed(nmsLow);

        // Open input filename of template filenames to read in.
        // Format of file looks like:
        // <template_filename> // PROBE TEMPLATE 1
        // <template_filename> // GALLERY TEMPLATE 1
        // <template_filename> // GALLERY TEMPLATE 2
        // ...
        // <template_filename> // GALLERY TEMPLATE N
        // NEXT
        // <template_filename> // PROBE TEMPLATE 2
        // <template_filename> // GALLERY TEMPLATE 1
        // <template_filename> // GALLERY TEMPLATE 2
        // ...
        // <template_filename> // GALLERY TEMPLATE N
        // NEXT
        // ...
        // I like to use absolute paths for filenames in this instance, but that's just me.

        ifstream in;
        in.open(argv[1]);

        // Open output filename to write matching scores.
        ofstream out;
        out.open(argv[2]);

        string tname1, tname2;

        while(!in.eof()) {
            
            in >> tname1;

    		NSubject referenceSubject = CreateSubject(tname1, tname1); // read in PROBE template

            in >> tname2;

                while(tname2 != "NEXT") // while GALLERY template is not NEXT
                { 
    
            		NSubject candidateSubject = CreateSubject(tname2, tname2);
            		NBiometricStatus status = biometricClient.Verify(referenceSubject, candidateSubject);
            		
            		if (status == nbsOk || status == nbsMatchNotFound)
            		{
            			out << tname1 << "," << tname2 << "," << referenceSubject.GetMatchingResults().Get(0).GetScore() << endl;
            			
            			/*
            			if (status == nbsOk)
            			{
            				cout << "succeeded" << endl;
            			}
            			else
            			{
            				cout << "failed" << endl;
            			}
            			*/
            			
            		}

                    /*
            		else
            		{
            			cout << "Verification failed. Status: " << NEnum::ToString(NBiometricTypes::NBiometricStatusNativeTypeOf(), status) << endl;
            			return -1;
            		}
                    */
            		
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
