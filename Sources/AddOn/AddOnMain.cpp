#include "APIEnvir.h"
#include "ACAPinc.h"

#include "DGModule.hpp"

#define ID_ADDON_INFO		32000
#define ID_ADDON_MENU		32500
#define ID_ADDON_DIALOG		32600

class ExampleDialog :	public DG::ModalDialog,
						public DG::PanelObserver,
						public DG::ButtonItemObserver,
						public DG::CompoundItemObserver
{
public:
	enum DialogResourceIds
	{
		ExampleDialogResourceId = ID_ADDON_DIALOG,
		OKButtonId = 1,
		CancelButtonId = 2,
		SeparatorId = 3
	};

	ExampleDialog () :
		DG::ModalDialog (ACAPI_GetOwnResModule (), ExampleDialogResourceId, ACAPI_GetOwnResModule ()),
		okButton (GetReference (), OKButtonId),
		cancelButton (GetReference (), CancelButtonId),
		separator (GetReference (), SeparatorId)
	{
		AttachToAllItems (*this);
		Attach (*this);
	}

	~ExampleDialog ()
	{
		Detach (*this);
		DetachFromAllItems (*this);
	}

private:
	virtual void PanelResized (const DG::PanelResizeEvent& ev) override
	{
		BeginMoveResizeItems ();
		okButton.Move (ev.GetHorizontalChange (), ev.GetVerticalChange ());
		cancelButton.Move (ev.GetHorizontalChange (), ev.GetVerticalChange ());
		separator.MoveAndResize (0, ev.GetVerticalChange (), ev.GetHorizontalChange (), 0);
		EndMoveResizeItems ();
	}

	virtual void ButtonClicked (const DG::ButtonClickEvent& ev) override
	{
		if (ev.GetSource () == &okButton) {
			PostCloseRequest (DG::ModalDialog::Accept);
		} else if (ev.GetSource () == &cancelButton) {
			PostCloseRequest (DG::ModalDialog::Cancel);
		}
	}

	DG::Button		okButton;
	DG::Button		cancelButton;
	DG::Separator	separator;
};

API_AddonType __ACDLL_CALL CheckEnvironment (API_EnvirParams* envir)
{
	RSGetIndString (&envir->addOnInfo.name, ID_ADDON_INFO, 1, ACAPI_GetOwnResModule ());
	RSGetIndString (&envir->addOnInfo.description, ID_ADDON_INFO, 2, ACAPI_GetOwnResModule ());

	return APIAddon_Normal;
}

GSErrCode __ACENV_CALL MenuCommandHandler (const API_MenuParams *menuParams)
{
	switch (menuParams->menuItemRef.menuResID) {
		case ID_ADDON_MENU:
			switch (menuParams->menuItemRef.itemIndex) {
				case 1:
					{
						ExampleDialog dialog;
						dialog.Invoke ();
					}
					break;
			}
			break;
	}
	return NoError;
}

GSErrCode __ACDLL_CALL RegisterInterface (void)
{
	return ACAPI_Register_Menu (ID_ADDON_MENU, 0, MenuCode_Tools, MenuFlag_Default);
}

GSErrCode __ACENV_CALL Initialize (void)
{
	return ACAPI_Install_MenuHandler (ID_ADDON_MENU, MenuCommandHandler);
}

GSErrCode __ACENV_CALL FreeData (void)
{
	return NoError;
}
