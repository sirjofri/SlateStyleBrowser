#pragma once
#include "CoreMinimal.h"
#include "SlateStyleData.h"

class FSlateStyleWidgetScrollBar : public FSlateStyleData
{
public:
	virtual TSharedRef<SWidget> GenerateRowWidget() override
	{
		const FScrollBarStyle* s = GetWidgetStyle<FScrollBarStyle>();
		if (!s)
			return SNullWidget::NullWidget;

		TSharedPtr<SScrollBar> sb = SNew(SScrollBar)
			.Style(s)
			.AlwaysShowScrollbar(true)
			.Orientation(Orient_Horizontal);

		sb->SetOnUserScrolled(FOnUserScrolled::CreateLambda([&](float f, TSharedPtr<SScrollBar> sbar)
		{
			if (sbar.IsValid())
				sbar->SetState(f, .2f);
		}, sb));
		sb->SetState(.7f, .2f);

		return sb.ToSharedRef();
	};

	virtual void InitializeDetails() override
	{
		FillDetailsWithProperties<FScrollBarStyle>();
	};
};