#include "Menu/CSessionRow.h"
#include "global.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UCSessionRow::SetSelfIndex(class UCMenu* InParent, uint32 InIndex)
{
	Parent = InParent;
	Index = InIndex;

	RowButton->OnClicked.AddDynamic(this, &UCSessionRow::OnClick);
}

void UCSessionRow::OnClick()
{

}
