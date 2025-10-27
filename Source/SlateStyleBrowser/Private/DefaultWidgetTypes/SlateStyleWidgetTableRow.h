#pragma once
#include "CoreMinimal.h"
#include "Editor.h"
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
		DemoValues.Add(MakeShared<FString>("Hello Unreal"));
		DemoValues.Add(MakeShared<FString>("Hello Slate"));
	
		return SNew(SBox)
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Fill)
			[
				SAssignNew(ListView, SListView<TSharedPtr<FString>>)
				.ListItemsSource(&DemoValues)
				.OnGenerateRow(this, &FSlateStyleWidgetTableRow::GenerateRowWidget)
				.OnSelectionChanged(this, &FSlateStyleWidgetTableRow::DeselectTimeout)
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
			.Padding(FMargin(20, 5))
			[
				SNew(STextBlock)
				.Text(FText::FromString(*InItem))
			];
	}
	
	void DeselectAll()
	{
		if (ListView.IsValid())
			ListView->ClearSelection();
	}
	
	void DeselectTimeout(TSharedPtr<FString> String, ESelectInfo::Type Arg)
	{
		if (DeselectTimer.IsValid()) {
			GEditor->GetTimerManager()->ClearTimer(DeselectTimer);
		}
		GEditor->GetTimerManager()->SetTimer(DeselectTimer, FTimerDelegate::CreateSP(this, &FSlateStyleWidgetTableRow::DeselectAll), 2., false);
	}
	
private:
	FTimerHandle DeselectTimer;
	TSharedPtr<SListView<TSharedPtr<FString>>> ListView;
	TArray<TSharedPtr<FString>> DemoValues;
};
