#pragma once
#include "CoreMinimal.h"
#include "SlateStyleData.h"
#include "Widgets/SlateStyleTableRow.h"
#include "Widgets/Views/SListView.h"

class FSlateStyleWidgetTableRow : public FSlateStyleData, public TSharedFromThis<FSlateStyleWidgetTableRow>
{
public:
	virtual TSharedRef<SWidget> GenerateRowWidget() override
	{
		const FTableRowStyle* s = GetWidgetStyle<FTableRowStyle>();
		if (!s)
			return SNullWidget::NullWidget;
		
		DemoValues.Empty(1);
		DemoValues.Add(MakeShared<FString>("Hello World"));
	
		return SNew(SBox)
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Left)
			[
				SNew(SListView<TSharedPtr<FString>>)
				.ListItemsSource(&DemoValues)
				.OnGenerateRow(this, &FSlateStyleWidgetTableRow::GenerateRowWidget)
			];
	};

	virtual void InitializeDetails() override
	{
		FillDetailsWithProperties<FTableRowStyle>();
	};

	virtual void InitializePreview() override
	{
		ExtendedPreview = SNullWidget::NullWidget;
	};
	
private:
	TSharedRef<ITableRow> GenerateRowWidget(TSharedPtr<FString> InItem, const TSharedRef<STableViewBase>& OwnerTable)
	{
		return SNew(STableRow<TSharedPtr<FString>>, OwnerTable)
			.Style(GetWidgetStyle<FTableRowStyle>())
			[
				SNew(STextBlock)
				.Text(FText::FromString(*InItem))
			];
	}
	
private:
	TArray<TSharedPtr<FString>> DemoValues;
};
