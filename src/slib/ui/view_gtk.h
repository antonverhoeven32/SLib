/*
 *   Copyright (c) 2008-2018 SLIBIO <https://github.com/SLIBIO>
 *
 *   Permission is hereby granted, free of charge, to any person obtaining a copy
 *   of this software and associated documentation files (the "Software"), to deal
 *   in the Software without restriction, including without limitation the rights
 *   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *   copies of the Software, and to permit persons to whom the Software is
 *   furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in
 *   all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *   THE SOFTWARE.
 */

#ifndef CHECKHEADER_SLIB_UI_VIEW_GTK
#define CHECKHEADER_SLIB_UI_VIEW_GTK

#include "slib/core/definition.h"

#if defined(SLIB_UI_IS_GTK)

#include "slib/ui/view.h"
#include "slib/ui/platform.h"

namespace slib
{

	class GTK_ViewInstance : public ViewInstance
	{
	public:
		GTK_ViewInstance();

		~GTK_ViewInstance();
		
	public:
		template <class T>
		static Ref<T> create(GtkWidget* handle)
		{
			if (handle) {
				Ref<T> ret = new T();
				if (ret.isNotNull()) {
					ret->_init(handle);
					return ret;
				}
			}
			return sl_null;
		}

		template <class T>
		static Ref<T> create(View* view, ViewInstance* parent, GtkWidget* handle)
		{
			Ref<T> ret = create<T>(handle);
			if (ret.isNotNull()) {
				ret->applyProperties(view, parent);
				return ret;
			}
			return sl_null;
		}

	public:

		void applyProperties(View* view, ViewInstance* parent);

		GtkWidget* getHandle();
		
		void setChildrenContainer(GtkWidget* widget);

		sl_bool isValid() override;

		void setFocus() override;

		void invalidate() override;

		void invalidate(const UIRect& rect) override;

		UIRect getFrame() override;

		void setFrame(const UIRect& frame) override;

		void setTransform(const Matrix3& transform) override;

		void setVisible(sl_bool flag) override;

		void setEnabled(sl_bool flag) override;

		void setOpaque(sl_bool flag) override;

		void setAlpha(sl_real alpha) override;

		void setClipping(sl_bool flag) override;

		void setDrawing(sl_bool flag) override;
		
		UIPointf convertCoordinateFromScreenToView(const UIPointf& ptScreen) override;

		UIPointf convertCoordinateFromViewToScreen(const UIPointf& ptView) override;

		void addChildInstance(const Ref<ViewInstance>& instance) override;

		void removeChildInstance(const Ref<ViewInstance>& instance) override;

		void bringToFront() override;
		
	public:
		void installEvents();
		
		static gboolean eventCallback(GtkWidget* widget, GdkEvent* event, gpointer user_data);
		
		static void applyModifiers(UIEvent* event, guint state);
		
	public:
		virtual gboolean onExposeEvent(GdkEventExpose* event);
		
		virtual gboolean onMotionNotifyEvent(GdkEventMotion* event);
		
		virtual gboolean onButtonEvent(GdkEventButton* event);
		
		virtual gboolean onCrossingEvent(GdkEventCrossing* event);

		virtual gboolean onKeyEvent(GdkEventKey* event);

		virtual gboolean onScrollEvent(GdkEventScroll* event);
		
	private:
		void _init(GtkWidget* handle);

		void _release();

	protected:
		GtkWidget* m_handle;
		GtkWidget* m_handleChildrenContainer;
		UIAction m_actionDrag;

	};

}

#endif

#endif
