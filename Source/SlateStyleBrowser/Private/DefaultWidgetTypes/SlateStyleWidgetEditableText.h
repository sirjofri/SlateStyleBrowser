#pragma once
#include "CoreMinimal.h"
#include "SlateStyleData.h"
#include "Widgets/Input/SEditableText.h"

class FSlateStyleWidgetEditableText : public FSlateStyleData
{
public:
	virtual TSharedRef<SWidget> GenerateRowWidget() override
	{
		const FEditableTextStyle* s = GetWidgetStyle<FEditableTextStyle>();
		if (!s)
			return SNullWidget::NullWidget;

		return SNew(SEditableText)
			.Style(s)
			.Text(DefaultValues.HelloWorld);
	};

	virtual void InitializeDetails() override
	{
		FillDetailsWithProperties<FEditableTextStyle>();
	};
};
