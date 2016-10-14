#ifndef CHECKHEADER_SLIB_UI_LINEAR_VIEW
#define CHECKHEADER_SLIB_UI_LINEAR_VIEW

#include "definition.h"

#include "view.h"

SLIB_UI_NAMESPACE_BEGIN

class SLIB_EXPORT LinearView : public ViewGroup
{
	SLIB_DECLARE_OBJECT
	
public:
	LinearView();
	
public:
	LayoutOrientation getOrientation();
	
	void setOrientation(LayoutOrientation orientation, sl_bool flagRedraw = sl_true);
	
	sl_bool isHorizontal();
	
	void setHorizontal(sl_bool flagRedraw = sl_true);
	
	sl_bool isVertical();
	
	void setVertical(sl_bool flagRedraw = sl_true);
	
protected:
	// override
	void onResizeChild(View* child, sl_ui_len width, sl_ui_len height);
	
	// override
	void onChangeVisibilityOfChild(View* child, Visibility oldVisibility, Visibility newVisibility);
	
	// override
	void onMeasureLayout(sl_bool flagHorizontal, sl_bool flagVertical);
	
	// override
	void onMakeLayout();
	
private:
	LayoutOrientation m_orientation;
	
};

class SLIB_EXPORT VerticalLinearView : public LinearView
{
public:
	VerticalLinearView();
};

class SLIB_EXPORT HorizontalLinearView : public LinearView
{
public:
	HorizontalLinearView();
};

SLIB_UI_NAMESPACE_END

#endif
