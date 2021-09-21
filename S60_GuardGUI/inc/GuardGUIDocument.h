/*
============================================================================
 Name        : CGuardGUIDocument from GuardGUIDocument.h
 Author      : Marco Bellino
 Version     :
 Copyright   : All Rights Reserved
 Description : Declares document for application.
============================================================================
*/

#ifndef GUARDGUIDOCUMENT_H
#define GUARDGUIDOCUMENT_H

// INCLUDES
#include <akndoc.h>
   
// CONSTANTS

// FORWARD DECLARATIONS
class  CEikAppUi;

// CLASS DECLARATION

/**
*  CGuardGUIDocument application class.
*/
class CGuardGUIDocument : public CAknDocument
	{
	public: // Constructors and destructor
		/**
		* Two-phased constructor.
		*/
		static CGuardGUIDocument* NewL(CEikApplication& aApp);

		/**
		* Destructor.
		*/
		virtual ~CGuardGUIDocument();

	public: // New functions

	public: // Functions from base classes
	protected:  // New functions

	protected:  // Functions from base classes

	private:

		/**
		* EPOC default constructor.
		*/
		CGuardGUIDocument(CEikApplication& aApp);
		void ConstructL();

	private:

		/**
		* From CEikDocument, create CGuardGUIAppUi "App UI" object.
		*/
		CEikAppUi* CreateAppUiL();
	};

#endif



