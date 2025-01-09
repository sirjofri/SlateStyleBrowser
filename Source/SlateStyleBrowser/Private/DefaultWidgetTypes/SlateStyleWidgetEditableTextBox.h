#pragma once
#include "CoreMinimal.h"
#include "SlateStyleData.h"
#include "Widgets/Input/SEditableTextBox.h"

class FSlateStyleWidgetEditableTextBox : public FSlateStyleData
{
public:
	virtual TSharedRef<SWidget> GenerateRowWidget() override
	{
		const FEditableTextBoxStyle* s = GetWidgetStyle<FEditableTextBoxStyle>();
		if (!s)
			return SNullWidget::NullWidget;

		return SNew(SEditableTextBox)
			.Style(s)
			.Text(DefaultValues.HelloWorld);
	};

	virtual void InitializeDetails() override
	{
		FillDetailsWithProperties<FEditableTextBoxStyle>();
	};
};
