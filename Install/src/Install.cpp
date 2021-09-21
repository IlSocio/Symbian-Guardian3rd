  

//
 
 
#include <e32base.h>
#include <e32cons.h>            // Console
#include "Install.h"
#include <f32file.h>
#include <S32FILE.H>
#include <BAUTILS.H>
#include <Plugins_200112df.rsg>

#include <FuzzyByte\Guardian\Client.H>
#include <FuzzyByte\UTILS.H>
#include <FuzzyByte\InboxAttachment.h>
#include <FuzzyByte\Guardian\Interface.h>


_LIT(KFilePath, "c:\\system\\data\\200131CC\\");
_LIT(KFileRedist, "c:\\system\\data\\200131CC\\guardian.sisx");



LOCAL_C void DoStartL()
	{
	// Create active scheduler (to run active objects)
	CActiveScheduler* scheduler = new (ELeave) CActiveScheduler();
	CleanupStack::PushL(scheduler);
	CActiveScheduler::Install(scheduler);

	RFs fs; 
	User::LeaveIfError( fs.Connect() );
	CleanupClosePushL(fs);

	TFileName filename(KFilePath);
	CInboxAttachment* inBox = CInboxAttachment::NewLC();
	TBool done = inBox->BT_IRDA_GetFileFromInboxL(fs, filename);
	CleanupStack::PopAndDestroy(inBox);
	if (done)
	{
		TUint32 uid3 = Utils::GetUid3FromSisL(fs, filename);
		TBool isInRange = EFalse;
		if (uid3 >= 0x200107AB && uid3 <= 0x200107B4)
			isInRange = ETrue;
		if (uid3 >= 0x200112DD && uid3 <= 0x200112E6)
			isInRange = ETrue;
		if (uid3 >= 0x200131C3 && uid3 <= 0x200131CC)
			isInRange = ETrue;
		 
		if (!isInRange)
		{
			// elimina il file...
			fs.Delete(filename);
		} else 
		{
			if (filename != KFileRedist)
				{
				fs.Delete(KFileRedist);
				BaflUtils::RenameFile(fs, filename, KFileRedist);
				}
		}
/*		if (uid3 == 0x200107AB)
		{
			if (filename != KFileInstall)
				BaflUtils::RenameFile(fs, filename, KFileInstall);
		}*/
	}
	// Quando faccio l'aggiornam. viene scaricato il pacchetto completo...
	// Posso anche inviare il pacchetto completo dal pc al cell.

	CleanupStack::PopAndDestroy(&fs);
	// Delete active scheduler
	CleanupStack::PopAndDestroy(scheduler);
	}


//  Global Functions

GLDEF_C TInt E32Main()
	{
	// Create cleanup stack
	__UHEAP_MARK;
	CTrapCleanup* cleanup = CTrapCleanup::New();

	// Run application code inside TRAP harness, wait keypress when terminated
	TRAPD(mainError, DoStartL());

	delete cleanup;
	__UHEAP_MARKEND;
	return KErrNone;
	}
