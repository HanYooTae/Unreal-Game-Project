#include "Menu/CSessionRow.h"
#include "global.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "CMainMenu.h"

void UCSessionRow::SetSelfIndex(UCMainMenu* InParent, uint32 InIndex)
{
	Parent = InParent;
	SelfClickedIndex = InIndex;

	RowButton->OnClicked.AddDynamic(this, &UCSessionRow::OnClick);
}

void UCSessionRow::OnClick()
{
	Parent->SetSelectedRowIndex(SelfClickedIndex);
}
