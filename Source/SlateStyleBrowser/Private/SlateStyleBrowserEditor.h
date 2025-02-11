#pragma once
#include "CoreMinimal.h"
#include "SlateStyleData.h"
#include "Runtime/Launch/Resources/Version.h"
#if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION > 1
#include "Engine/TimerHandle.h"
#else
#include "Engine/EngineTypes.h"
#endif
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Views/SListView.h"

class FTabManager;
class USlateStyleBrowserUserSettings;
class STableViewBase;
class FSlateStyleData;
class ITableRow;
class FMenuBarBuilder;
class FMenuBuilder;
class SDockTab;
class ISlateStyleDataManager;
class STypeFilterWidget;

class SSlateStyleBrowserEditor : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlateStyleBrowserEditor) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TSharedRef<SDockTab>& MajorTab, TWeakPtr<ISlateStyleDataManager> InSlateStyleDataManager);

private:
	void FillEditMenu(FMenuBuilder& MenuBuilder);
	static void FillHelpMenu(FMenuBuilder& MenuBuilder);
	void BuildTabMenu(FMenuBarBuilder& MenuBarBuilder);

	TSharedRef<ITableRow> GenerateRow(TSharedPtr<FSlateStyleData> SlateStyleData, const TSharedRef<STableViewBase>& TableViewBase);
	TSharedPtr<SWidget> EntryContextMenu();
	
	void CacheAllStyleNames();
	void SelectCodeStyle(EDefaultCopyStyle CopyCodeStyle);
	void InputTextChanged(const FText& Text);

	void UpdateList();
	
	TSharedPtr<FSlateStyleData> MakeSlateStyleData(const ISlateStyle* SlateStyle, FName Style, FName PropertyName);

	USlateStyleBrowserUserSettings* GetConfig();
	void MakeValidConfiguration();
	
	static bool FilterByString(const TArray<FString>& Tokens, const FString& String);
	static bool FilterByMeta(const TArray<FString>& Tokens, TSharedPtr<FSlateStyleData> Data);

private:
	TArray<TSharedPtr<FSlateStyleData>> Lines;
	TArray<TSharedPtr<FName>> AllStyles;
	
	TArray<FName> FilterTypes;

	FString FilterString;
	FTimerHandle FilterStringChangedTimer;
	EDefaultCopyStyle DefaultCopyStyle = DCS_FirstEntry;

private:
	TSharedPtr<FTabManager> TabManager;
	TWeakPtr<SDockTab> DockTab;
	TWeakPtr<ISlateStyleDataManager> SlateStyleDataManager;
	
	TSharedPtr<SListView<TSharedPtr<FSlateStyleData>>> ListView;
	TSharedPtr<SComboBox<TSharedPtr<FName>>> StyleSelectionComboBox;
	TSharedPtr<STypeFilterWidget> TypeFilterWidget;

	TMap<FName,FString> DefaultStyleSetCode;

	FName Name_AllStyles = FName("(All Styles)");
	FText QuickStyleTooltipText = NSLOCTEXT("SlateStyleBrowser", "CustomStyleTooltipText", "Enter custom style. $1 will be replaced with the icon name, $2 with the style name.");
};
