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

#ifndef CHECKHEADER_SLIB_CORE_ANIMATION
#define CHECKHEADER_SLIB_CORE_ANIMATION

#include "definition.h"

#include "object.h"
#include "function.h"
#include "hash_map.h"
#include "math.h"
#include "interpolation.h"

/*
	Basic functions for Graphics/Rendering/UI animations
*/

#define SLIB_ANIMATION_DURATION_MINIMUM_SECONDS 0.0001f

namespace slib
{
	
	enum class AnimationCurve
	{
		Linear = 0,
		EaseInOut = 1,		// the rate of change starts and ends slowly but accelerates through the middle
		EaseIn = 2,			// the rate of change starts out slowly and and then accelerates
		EaseOut = 3,		// the rate of change starts out quickly and and then decelerates
		Cycle = 4,			// Repeats the animation for a specified number of cycles. The rate of change follows a sinusoidal pattern.
		Bounce = 5,			// bounces at the end
		Anticipate = 6,		// starts backward then flings forward
		Overshoot = 7,		// flings forward and overshoots the last value then comes back
		Custom = 50,
		Default = 100
	};
	
	class AnimationTarget;
	
	class AnimationLoop;
	
	class AnimationFlags
	{
	public:
		int value;
		SLIB_MEMBERS_OF_FLAGS(AnimationFlags, value)

	public:
		enum {
			Default = 0,
			AutoStart = 1,
			Repeat = 2,
			AutoReverse = 4,
			NotNative = 8,
			NotUpdateWhenStart = 16,
			NotSelfAlive = 32
		};

	};
	
	class Animation : public Object
	{
		SLIB_DECLARE_OBJECT

	protected:
		Animation();

		~Animation();

	public:
		static Ref<Animation> create(float duration);

		static Ref<Animation> create(const Ref<AnimationTarget>& target, float duration, const Function<void()>& onStop = sl_null, AnimationCurve curve = AnimationCurve::Default, const AnimationFlags& flags = AnimationFlags::Default);
		
		static Ref<Animation> start(const Ref<AnimationTarget>& target, float duration, const Function<void()>& onStop = sl_null, AnimationCurve curve = AnimationCurve::Default, const AnimationFlags& flags = AnimationFlags::Default);

		static Ref<Animation> createWithLoop(const Ref<AnimationLoop>& loop, float duration);

		static Ref<Animation> createWithLoop(const Ref<AnimationLoop>& loop, const Ref<AnimationTarget>& target, float duration, const Function<void()>& onStop = sl_null, AnimationCurve curve = AnimationCurve::Default, const AnimationFlags& flags = AnimationFlags::Default);
		
		static Ref<Animation> startWithLoop(const Ref<AnimationLoop>& loop, const Ref<AnimationTarget>& target, float duration, const Function<void()>& onStop = sl_null, AnimationCurve curve = AnimationCurve::Default, const AnimationFlags& flags = AnimationFlags::Default);

	public:
		Ref<AnimationLoop> getLoop();

		CList< Ref<AnimationTarget> >& getTargets();

		void addTarget(const Ref<AnimationTarget>& target);

		void removeTarget(const Ref<AnimationTarget>& target);

		void removeAllTargets();

		// linked animations are automatically started on the stop event
		void linkAnimation(const Ref<Animation>& animation);

		void unlinkAnimation(const Ref<Animation>& animation);

		void unlinkAllAnimations();


		sl_reg getId();

		sl_bool isSelfAlive();

		void setSelfAlive(sl_bool flagAlive);

		sl_bool isNativeEnabled();

		void setNativeEnabled(sl_bool flagNative);

		sl_bool isUpdateWhenStart();

		void setUpdateWhenStart(sl_bool flagUpdate);
	

		// seconds
		float getTime();

		void setTime(float seconds, sl_bool flagUpdateFrame = sl_false);
	
		// seconds
		float getDuration();

		void setDuration(float seconds);

		// seconds
		float getStartDelay();

		void setStartDelay(float seconds);

		sl_int32 getRepeatCount();

		// negative count means infinite repeating
		void setRepeatCount(sl_int32 count);

		sl_bool isRepeatForever();

		void setRepeatForever(sl_bool flagRepeatForever);

		sl_bool isAutoReverse();

		void setAutoReverse(sl_bool flagReverse);

		sl_bool isAbsoluteTime();

		void setAbsoluteTime(sl_bool flagAbsolute);

		AnimationCurve getAnimationCurve();

		void setAnimationCurve(AnimationCurve curve);

		float getAnimationCurveEaseFactor();

		void setAnimationCurveEaseFactor(float factor);

		float getAnimationCurveCycles();

		void setAnimationCurveCycles(float cycles);

		float getAnimationCurveTension();

		void setAnimationCurveTension(float tension);

		Function<float(float)> getCustomAnimationCurve();

		void setCustomAnimationCurve(const Function<float(float)>& curve);


		// seconds
		float getCurrentTime(sl_uint32* outRepeatedCount = sl_null);

		float getTimeFraction();

		sl_uint32 getRepeatedCount();


		void start();

		void startAt(float seconds);
	
		void restart();

		void restartAt(float seconds);

		void stop();

		void resume();

		void pause();

		sl_bool isStarted();

		sl_bool isStopped();

		sl_bool isRunning();

		sl_bool isNotRunning();

		sl_bool isPaused();
	
		void update(float elapsedSeconds);

	public:
		SLIB_PROPERTY(AtomicFunction<void()>, OnStop)

		SLIB_PROPERTY(AtomicFunction<void(Animation*, float seconds)>, OnAnimationFrame)

		SLIB_PROPERTY(AtomicFunction<void(Animation*, sl_int32 nRemainingRepeatCount)>, OnRepeatAnimation)

		SLIB_PROPERTY(AtomicFunction<void(Animation*)>, OnStopAnimation)

	protected:
		virtual void onAnimationFrame(float seconds);

		virtual void onRepeatAnimation(sl_int32 nRemainingRepeatCount);

		virtual void onStopAnimation();

	public:
		void dispatchAnimationFrame(float seconds);

		void dispatchStartFrame();

		void dispatchEndFrame();
	
		void dispatchRepeatAnimation(sl_int32 nRemainingRepeatCount);

		void dispatchStopAnimation();

	private:
		float _getTime(sl_uint32& iRepeat, sl_bool& flagStop);

		float _getFraction(float time);

		float _applyCurve(float fraction);

		sl_bool _stop(sl_bool flagFromNative);

		void _stopFromNative();

		void _resume();

		void _pause();

	private:
		WeakRef<AnimationLoop> m_loop;
		CList< Ref<AnimationTarget> > m_targets;
		CList< Ref<Animation> > m_linkedAnimations;

		sl_reg m_id;
		sl_bool m_flagSelfAlive;
		sl_bool m_flagNativeEnabled;
		sl_bool m_flagUpdateWhenStart;

		float m_time; // seconds
		float m_duration; // seconds
		float m_delay; // seconds
		sl_int32 m_repeatCount;
		sl_bool m_flagAutoReverse;
		sl_bool m_flagAbsoluteTime;

		AnimationCurve m_curve;
		float m_curveEaseFactor;
		float m_curveEaseDoubleFactor;
		float m_curveCycles;
		float m_curveCycles2PI;
		float m_curveTension;
		AtomicFunction<float(float)> m_customAnimationCurve;

		sl_bool m_flagStarted;
		sl_bool m_flagRunning;
		sl_uint32 m_lastRepeatedCount;
		sl_bool m_flagStartedNative;

		AtomicRef<Referable> m_nativeInstance;
	
		friend class AnimationLoop;
	};
	
	class AnimationLoop : public Object
	{
	public:
		AnimationLoop();

		~AnimationLoop();

	public:
		static Ref<AnimationLoop> getDefault();
	
	public:
		void addAnimation(Animation* animation);

		void removeAnimation(Animation* animation);

		void pause();

		void resume();

		sl_bool isPaused();
	
		void wake();

		virtual sl_bool startNativeAnimation(Animation* animation);

		virtual void stopNativeAnimation(Animation* animation);
	
	protected:
		void _stopAnimationFromNative(Animation* animation);

		Ref<Referable> _getNativeInstance(Animation* animation);

		void _setNativeInstance(Animation* animation, Referable* instance);

	protected:
		virtual void _wake() = 0;

	protected:
		// returns millseconds to wait, negative when no animation is running
		sl_int32 _runStep();

	protected:
		CHashMap< sl_reg, Ref<Animation> > m_mapAnimations;
		CHashMap< sl_reg, WeakRef<Animation> > m_mapWeakAnimations;
		List< Ref<Animation> > m_animationsRunning;
		sl_bool m_flagPaused;

		sl_bool m_flagUpdateList;
		sl_int64 m_lastTime; // milliseconds

	};
	
	template <class T>
	class AnimationFrame
	{
	public:
		float fraction;
		T value;

	public:
		SLIB_INLINE AnimationFrame() : fraction(0) {}

		SLIB_INLINE AnimationFrame(const AnimationFrame& other) : fraction(other.fraction), value(other.value) {}

		SLIB_INLINE AnimationFrame(float _fraction, const T& _value) : fraction(_fraction), value(_value) {}

	};
	
	template < class T, class INTERPOLATION = Interpolation<T> >
	class AnimationFrames
	{
	public:
		SLIB_INLINE AnimationFrames() {}

		SLIB_INLINE AnimationFrames(const AnimationFrames& other) {}

		SLIB_INLINE AnimationFrames(const T& _startValue, const T& _endValue) : startValue(_startValue), endValue(_endValue) {}

	public:
		void addFrame(float fraction, const T& value);

		T getValue(float fraction);

	public:
		T startValue;
		T endValue;
		List< AnimationFrame<T> > frames;

	};
	
	
	template < class T, class INTERPOLATION = Interpolation<T> >
	class AnimationFramesSeeker : public Object
	{
	public:
		AnimationFramesSeeker(const AnimationFrames<T, INTERPOLATION>& frames);

	public:
		T seek(float fraction);

		sl_size getFramesCount();

		AnimationFrame<T>& getFrame(sl_size index);
	
	public:
		T startValue;
		T endValue;
	
	protected:
		Array< AnimationFrame<T> > m_arrFrames;
		AnimationFrame<T>* m_frames;
		sl_size m_countFrames;

		sl_size m_currentIndex;
		float m_currentStartFraction;
		float m_currentEndFraction;
		T* m_currentStartValue;
		T* m_currentEndValue;

	};
	
	
	class AnimationTarget : public Object
	{
		SLIB_DECLARE_OBJECT

	public:
		AnimationTarget();

		~AnimationTarget();

	public:
		Ref<Animation> getAnimation();

		void setAnimation(const Ref<Animation>& animation);

		void forceUpdate();

	public:
		virtual void update(float fraction) = 0;

	protected:
		AtomicWeakRef<Animation> m_animation;

	};
	
	template <class T>
	class AnimationTargetT : public AnimationTarget
	{
	public:
		SLIB_INLINE AnimationTargetT(const AnimationFrames<T>& frames) : m_seeker(frames) {}

	public:
		T& getStartValue();

		T& getEndValue();
	
		sl_size getFramesCount();

		T& getFrame(sl_size index);

		void update(float fraction) override;

		virtual void update(float fraction, const T& value) = 0;
		
	protected:
		AnimationFramesSeeker<T> m_seeker;
		
	};

}

#include "detail/animation.inc"

#endif


