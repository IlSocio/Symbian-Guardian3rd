/*
============================================================================
 Name        : PluginManager.cpp
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : CPluginManager implementation
============================================================================
*/

#include "PluginManager.h"

#include <Plugins_200112df.rsg>
#include <FuzzyByte\Guardian\client.h>
#include <FuzzyByte\Guardian\interface.h>
#include <FuzzyByte\resreader.h>

#include <Ecom\ECom.h>

TPluginParser::TPluginParser() 
{
	SetDelimiter(TChar(PLUGIN_DELIMITER));
}

/*void TPluginParser::Parse(const TDesC16& aData)
{
	TDelimitedParserBase16::Parse(aData);
}

void TPluginParser::SetDelimiter(TChar aDelimiter)
{
	TDelimitedParserBase16::SetDelimiter(aDelimiter);
}*/


CPluginManager::CPluginManager(RFs& fs) : iFs(fs)
{
	// No implementation required
}


CPluginManager::~CPluginManager()
{
	__LOG("Destructor:%d", iArray.Count());
	if (iArray.Count() > 0)
	{
		// Cancel di tutti i PluginAO presenti nell'array
		for (int i=0; i<iArray.Count(); i++) 
		{
			CPluginAO* tmp = iArray[i];
			delete tmp;
			tmp = NULL;
		}
		__LOG_TXT("FinalClose");
		REComSession::FinalClose();
	}
	// Cancellazione array
	iArray.Reset();
	iArray.Close();
	__LOG_TXT("EndDestructor");
	__LOG_CLOSE;
}


CPluginManager* CPluginManager::NewLC(RFs& fs)
{
	CPluginManager* self = new (ELeave)CPluginManager(fs);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
}


CPluginManager* CPluginManager::NewL(RFs& fs)
{
	CPluginManager* self=CPluginManager::NewLC(fs);
	CleanupStack::Pop(); // self;
	return self;
}


void CPluginManager::ConstructL()
{
	__LOG_OPEN("Guardian", "PluginManager.txt");
	RGuardian guard;
	User::LeaveIfError( guard.Connect() );
	iIsIridium = guard.IsIridium();
	guard.Close();
}

/*
	__LOG_TXT("Incoming Msg..."));
	TInt pos = aData.Find(KDelimiter);
	TInt posData = pos + KDelimiter().Length(); // Punta a quel che c'e' dopo "plugin//"

	if (pos < 0) 
	{
		__LOG_TXT("Delimiter not Found!"));
		pos = aData.Find(_L(" "));
		posData = pos + 1;						 // Punta a quel che c'e' dopo "plugin "
	}
	if (pos < 0) 
	{
		__LOG_TXT("Bad Syntax, Trash Message"));
		return;
	}

	TBuf<MAX_PLUGIN_NAME> pluginTxt;
	pluginTxt = aData.Left(pos);
	pluginTxt.UpperCase();
	
	if ((pluginTxt.Right(1) != _L("G")) || (CheckImsiL() == EValid))
	{
		// Verifica registrazione... Se il plugin non e' Config oppure se c'e' una SIM autorizzata nel cell...
		if ( !iStorage->iSettings.IsValidRegCodeL() ) 
			return;
	}

	if (pluginTxt != _L("FAKESMS")) 
		aData.UpperCase();

	MPlugin* plugin = LoadPluginL(pluginTxt);
	if (plugin == NULL) 
	{
		__LOG_TXT("Plugin not Found:"));
		__FLOG(pluginTxt);
		return;
	}

	__LOG_TXT("Launch Plugin:"));
	__FLOG(pluginTxt);

	__LOG_TXT("Data:"));
	__FLOG(	aData.Mid(posData) );

	// Invia richiesta passando iStatus come parametro, quando il process del plugin sara' completato sara' eseguito RunL
	TRAPD(error, plugin->ProcessIncomingSmsL(aFromAddress, aData.Mid(posData) ) );
	if (error != KErrNone) 
		{
		__LOG("ProcessIncomingSmsL Error:%d"), error);
		}	
*/


void CPluginManager::SendSmsL(const TDesC& number, const TDesC& sms)
{
	__LOG_TXT("SendSmsL");
	__LOG_DES(sms);
	RGuardian guard;
	User::LeaveIfError( guard.Connect() );
	CleanupClosePushL( guard );
	guard.SendMessage( number, sms );
	CleanupStack::PopAndDestroy();
}


HBufC* CPluginManager::ReadResL(TInt ResID)
	{
	CResReader* rdr = CResReader::NewLC(iFs, KResFileName);
	HBufC* txt = rdr->AllocReadLC(ResID);
	CleanupStack::Pop( txt );
	CleanupStack::PopAndDestroy( rdr );
	return txt;
	}


// SMS contiene: Plugin*Data
// oppure contiene: *Plugin*Data
void CPluginManager::ProcessSmsPluginL(const TDesC& number, const TDesC& sms)
{
	// PARSING INIZIALE DELL'SMS
	TPtrC sms_plugin;
	TPtrC sms_data;
	TPluginParser parser;
	parser.Parse(sms);
	parser.GetNext(sms_plugin);
	if (parser.Eos())
	{
		RBuf txt(ReadResL( R_NULL_DELIM ));
		txt.CleanupClosePushL();
		SendSmsL(number, txt);
		CleanupStack::PopAndDestroy(&txt);
		return;
	}

	parser.Remainder(sms_data);
	if (sms_data.Length()>0 && sms_data[0] == TChar(PLUGIN_DELIMITER))
		sms_data.Set( sms_data.Right(sms_data.Length()-1) );

//	TBuf8<200> b1;
//	b1.Copy(sms_data);

	if (sms_plugin.Length() > KMAX_PLUGIN_NAME)
	{
		RBuf txt(ReadResL( R_NULL_LENGTH ));
		txt.CleanupClosePushL();
		SendSmsL(number, txt);
		CleanupStack::PopAndDestroy(&txt);
		return;
	}

	TBuf<KMAX_PLUGIN_NAME> plugin_name_up;
	plugin_name_up = sms_plugin;
	plugin_name_up.UpperCase();
	__LOG_TXT("CreateECOMPlugin:");
	__LOG_DES(plugin_name_up);
	CPluginAO* plugin = CPluginAO::NewL(plugin_name_up);
	CleanupStack::PushL(plugin);

	// Check iridium... and MONITOR plugin
	TBool ignoreMonitor=EFalse;
	if (!iIsIridium && plugin_name_up.Length()>0 && plugin_name_up.Left(1) == _L("M"))
		ignoreMonitor=ETrue;
	
	// Se il plugin non e' stato trovato allora esce...
	if (!plugin->Exists() || ignoreMonitor)
	{
		__LOG_TXT("Plugin NOT Found!");
		CleanupStack::PopAndDestroy(plugin);

		RBuf txt( ReadResL( R_NULL_LENGTH ) );
		txt.CleanupClosePushL();

		// Anticrack Starts		
		// Se arriva qui iIsIridium e' = True ed ignoreMonitor e' False;
		// oppure iIsIridium e' = False ed ignoreMonitor e' True;
		// oppure iIsIridium e' = False ed ignoreMonitor e' False;
		// CleanupStack::PopAndDestroy( !(iIsIridium ^ ignoreMonitor) );
		// Anticrack Ends

		RBuf reply;
		reply.CleanupClosePushL();
		reply.Create(KMAX_PLUGIN_NAME + 50);
		reply.Append(txt);
		reply.Append(plugin_name_up);
		SendSmsL(number, reply);
		CleanupStack::PopAndDestroy(&reply);

		CleanupStack::PopAndDestroy(&txt);
		
		if (iArray.Count() == 0)
			REComSession::FinalClose();
		return;
	}
	__LOG_TXT("Plugin Found!");
	// IgnoreMonitor = EFalse
	
	// Il nome dell'ECOM plugin non coincide con l'id del plugin...
	// Verifica se esiste gia' nell'array e se c'e' cancella l'istanza precedente...
	TInt pos = FindElemPosById( plugin->PluginId() );
	__LOG("Plugin Pos:%d", pos);
	if (pos >= 0)
	{
		CPluginAO* oldPlugin = (CPluginAO*) iArray[pos];
		iArray.Remove(pos);
		delete oldPlugin;
	}

	// Passa l'ownership del nuovo plugin all'array
	__LOG_TXT("AppendArray");
	iArray.Append(plugin);
	CleanupStack::Pop(plugin);

	// Lancia l'esecuzione del plugin
	plugin->SetObserver(this);
	__LOG_TXT("StartPlugin");
	plugin->StartPlugin(number, sms_data);
	__LOG_TXT("End StartPlugin");
}


void CPluginManager::PluginCompletedL(TAny* src, TInt ris)
{
	__LOG("PluginCompletedL:%d", ris);
	__LOG("PluginsRunning:%d", iArray.Count());
	TInt pos = FindElemPosByObj(src);
	if (pos < 0) 
		return;

	// Elimina dall'array il plugin che ha completato l'esecuzione...
	iArray.Remove(pos);
	CPluginAO* plugin = (CPluginAO*) src;
	__LOG_DES(plugin->PluginId());
	delete plugin;

	if (iArray.Count() == 0)
		REComSession::FinalClose();
}


TInt CPluginManager::FindElemPosById(const TDesC& id)
{
	for (int i=0; i<iArray.Count(); i++) 
	{
		CPluginAO* plug2 = (CPluginAO*) iArray[i];
		if (plug2->PluginId().Compare( id ) == 0)
			return i;
	}
	return -1;
}


TInt CPluginManager::FindElemPosByObj(TAny* obj)
{
	for (int i=0; i<iArray.Count(); i++) 
	{
		if (iArray[i] == obj)
			return i;
	}
	return -1;
}


