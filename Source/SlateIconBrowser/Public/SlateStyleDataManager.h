#pragma once

class FSlateStyleData;
class ISlateStyleDataProvider;

class ISlateStyleDataManager
{
public:
	virtual ~ISlateStyleDataManager() = default;
	
	virtual void RegisterWidgetStyleProvider(TSharedPtr<ISlateStyleDataProvider> InSlateStyleDataProvider) = 0;
	virtual TSharedPtr<ISlateStyleDataProvider> GetSlateStyleDataProvider(FName InWidgetType) = 0;
	virtual TSharedPtr<FSlateStyleData> MakeSlateStyleData(const ISlateStyle* SlateStyle, FName PropertyName, FName WidgetType) = 0;
	virtual void GetRegisteredTypes(TArray<FName>& OutTypes) = 0;
};