#ifndef CHECKHEADER_SLIB_CORE_TIME
#define CHECKHEADER_SLIB_CORE_TIME

#include "definition.h"

#include "string.h"
#include "parse.h"

SLIB_NAMESPACE_BEGIN

struct SLIB_EXPORT DATE
{
	int year;
	int month;
	int day;
	int dayOfWeek;
};

class SLIB_EXPORT Time
{
public:
	Time();

	Time(const Time& other);
	
	Time(sl_int32 time);
	
	Time(sl_uint32 time);
	
	Time(sl_int64 time);
	
	Time(sl_uint64 time);

	Time(int year, int month, int date);
	
	Time(int year, int month, int date, int hour, int minute, int second);
	
	Time(const String8& str);
	
	Time(const String16& str);
	
	Time(const SafeString8& str);
	
	Time(const SafeString16& str);
	
	Time(const sl_char8* str);
	
	Time(const sl_char16* str);

public:
	static Time now();
	
	static Time zero();
	
	void setZero();
	
	sl_bool isZero() const;
	
	sl_bool isNotZero() const;
	
	sl_int64 toInt() const;

	void setInt(sl_int64 time);
	
	void add(sl_int64 time);
	
	void add(const Time& other);

public:
	Time& operator=(const Time& other);
	
	Time& operator=(sl_int32 time);
	
	Time& operator=(sl_uint32 time);
	
	Time& operator=(sl_int64 time);
	
	Time& operator=(sl_uint64 time);
	
	Time& operator=(const String8& str);
	
	Time& operator=(const String16& str);
	
	Time& operator=(const SafeString8& str);
	
	Time& operator=(const SafeString16& str);
	
	Time& operator=(const sl_char8* str);
	
	Time& operator=(const sl_char16* str);

	
	sl_bool operator==(const Time& other) const;
	
	sl_bool operator<=(const Time& other) const;
	
	sl_bool operator>=(const Time& other) const;
	
	sl_bool operator!=(const Time& other) const;
	
	sl_bool operator<(const Time& other) const;
	
	sl_bool operator>(const Time& other) const;

	
	Time operator+(sl_int64 time) const;
	
	Time operator+(const Time& time) const;
	
	Time& operator+=(sl_int64 time);
	
	Time& operator+=(const Time& time);

	
	Time operator-(sl_int64 time) const;
	
	Time operator-(const Time& time) const;
	
	Time& operator-=(sl_int64 time);
	
	Time& operator-=(const Time& time);
	
public:
	void setElements(int year, int month, int date, int hour, int minute, int second);
	
	void setNow();
	
	void setToSystem();
	
	void getDate(DATE* date) const;
	
	void setDate(int year, int month, int day);
	
	int getYear() const;
	
	void setYear(int year);
	
	void addYears(int years);
	
	int getMonth() const;
	
	void setMonth(int month);
	
	void addMonths(int months);
	
	int getDay() const;
	
	void setDay(int day);
	
	void addDays(sl_int64 days);
	
	double getDayf() const;
	
	void setDayf(double day);
	
	void addDaysf(double days);
	
	int getHour() const;
	
	void setHour(int hour);
	
	void addHours(sl_int64 hours);
	
	double getHourf() const;
	
	void setHourf(double hour);
	
	void addHoursf(double hours);
	
	int getMinute() const;
	
	void setMinute(int minute);
	
	void addMinutes(sl_int64 minutes);
	
	double getMinutef() const;

	void setMinutef(double minute);
	
	void addMinutesf(double minutes);
	
	int getSecond() const;
	
	void setSecond(int second);
	
	void addSeconds(sl_int64 seconds);
	
	double getSecondf() const;
	
	void setSecondf(double second);
	
	void addSecondsf(double seconds);
	
	int getMillisecond() const;
	
	void setMillisecond(int millis);
	
	void addMilliseconds(sl_int64 millis);
	
	double getMillisecondf() const;
	
	void setMillisecondf(double millis);
	
	void addMillisecondsf(double millis);
	
	int getMicrosecond() const;
	
	void setMicrosecond(int micros);
	
	void addMicroseconds(sl_int64 micros);
	
	double getMicrosecondf() const;

	void setMicrosecondf(double micros);
	
	void addMicrosecondsf(double micros);
	
	int getDayOfWeek() const;
	
	void setDayOfWeek(int day);
	
	int getDayOfYear() const;
	
	void setDayOfYear(int day);
	
	sl_int64 getDaysCount() const;
	
	void setDaysCount(sl_int64 days);
	
	double getDaysCountf() const;
	
	void setDaysCountf(double days);
	
	sl_int64 getHoursCount() const;
	
	void setHoursCount(sl_int64 hours);
	
	double getHoursCountf() const;
	
	void setHoursCountf(double hours);
	
	sl_int64 getMinutesCount() const;
	
	void setMinutesCount(sl_int64 minutes);
	
	double getMinutesCountf() const;
	
	void setMinutesCountf(double minutes);
	
	sl_int64 getSecondsCount() const;
	
	void setSecondsCount(sl_int64 seconds);
	
	double getSecondsCountf() const;
	
	void setSecondsCountf(double seconds);
	
	sl_int64 getMillisecondsCount() const;
	
	void setMillisecondsCount(sl_int64 milis);
	
	double getMillisecondsCountf() const;
	
	void setMillisecondsCountf(double milis);
	
	sl_int64 getMicrosecondsCount() const;
	
	void setMicrosecondsCount(sl_int64 micros);
	
	double getMicrosecondsCountf() const;

	void setMicrosecondsCountf(double micros);

	
	int getDaysCountInMonth() const;
	
	int getDaysCountInYear() const;
	
	int getQuarter() const;

	String getWeekday(sl_bool flagShort = sl_true) const;

	Time getTimeOnly() const;
	
	
	String toString() const;

	String8 toString8() const;
	
	String16 toString16() const;
	
	String getDateString() const;
	
	String8 getDateString8() const;
	
	String16 getDateString16() const;
	
	String getTimeString() const;
	
	String8 getTimeString8() const;
	
	String16 getTimeString16() const;
	
	sl_bool setString(const String8& str);
	
	sl_bool setString(const String16& str);
	
	sl_bool setString(const SafeString8& str);
	
	sl_bool setString(const SafeString16& str);
	
	sl_bool setString(const sl_char8* str);
	
	sl_bool setString(const sl_char16* str);
	
	String format(const String8& fmt) const;
	
	String format(const SafeString8& fmt) const;
	
	String format(const String16& fmt) const;
	
	String format(const SafeString16& fmt) const;
	
	String format(const sl_char8* fmt) const;
	
	String format(const sl_char16* fmt) const;

	
	static sl_reg parseElements(sl_int32* outArrayYMDHMS, const sl_char8* sz, sl_size posBegin = 0, sl_size len = SLIB_SIZE_MAX);
	
	static sl_reg parseElements(sl_int32* outArrayYMDHMS, const sl_char16* sz, sl_size posBegin = 0, sl_size len = SLIB_SIZE_MAX);
	
	static sl_bool parseElements(const String8& time, sl_int32* outArrayYMDHMS);
	
	static sl_bool parseElements(const String16& time, sl_int32* outArrayYMDHMS);
	
	static sl_bool parseElements(const SafeString8& time, sl_int32* outArrayYMDHMS);
	
	static sl_bool parseElements(const SafeString16& time, sl_int32* outArrayYMDHMS);
	
	static sl_bool parseElements(const sl_char8* time, sl_int32* outArrayYMDHMS);
	
	static sl_bool parseElements(const sl_char16* time, sl_int32* outArrayYMDHMS);

	SLIB_DECLARE_PARSE_FUNCTIONS(Time)
	
protected:
	sl_int64 m_time; // microseconds
	
	/* platform functions */
protected:
	sl_bool _getDate(DATE* date) const;
	
	void _setElements(int year, int month, int date, int hour, int minute, int second);
	
	void _setNow();
	
	void _setToSystem();
	
};


class SLIB_EXPORT TimeCounter
{
public:
	TimeCounter();

public:
	Time getTime() const;
	
	Time getTime(const Time& current) const;

	sl_uint64 getEllapsedMilliseconds() const;
	
	sl_uint64 getEllapsedMilliseconds(const Time& current) const;

	void reset();
	
	void reset(const Time& current);
	
	void update();
	
	void update(const Time& current);
	
protected:
	Time m_timeLast;
	Time m_timeEllapsed;
	
};


class SLIB_EXPORT TimeKeeper
{
public:
	TimeKeeper();
	
public:
	void start();
	
	void start(const Time& current);
	
	void startAndSetTime(const Time& initialTimeValue);
	
	void startAndSetTime(const Time& initialTimeValue, const Time& current);
	
	void restart();
	
	void restart(const Time& current);
	
	void restartAndSetTime(const Time& initialTimeValue);
	
	void restartAndSetTime(const Time& initialTimeValue, const Time& current);

	void stop();
	
	void resume();
	
	void resume(const Time& current);
	
	void pause();
	
	void pause(const Time& current);

	Time getTime() const;
	
	Time getTime(const Time& current) const;
	
	void setTime(const Time& time);
	
	void setTime(const Time& time, const Time& current);
	
	void update();
	
	void update(const Time& current);
	
	sl_bool isStarted() const;
	
	sl_bool isStopped() const;
	
	sl_bool isRunning() const;
	
	sl_bool isNotRunning() const;

	sl_bool isPaused() const;

protected:
	sl_bool m_flagStarted;
	sl_bool m_flagRunning;
	Time m_timeLast;
	Time m_timeEllapsed;
	SpinLock m_lock;
	
};

SLIB_NAMESPACE_END


SLIB_NAMESPACE_BEGIN

SLIB_INLINE Time::Time()
{
}

SLIB_INLINE Time::Time(const Time& other)
{
	m_time = other.m_time;
}

SLIB_INLINE Time::Time(sl_int32 time)
{
	m_time = time;
}

SLIB_INLINE Time::Time(sl_uint32 time)
{
	m_time = time;
}

SLIB_INLINE Time::Time(sl_int64 time)
{
	m_time = time;
}

SLIB_INLINE Time::Time(sl_uint64 time)
{
	m_time = time;
}

SLIB_INLINE Time Time::now()
{
	Time ret;
	ret.setNow();
	return ret;
}

SLIB_INLINE Time Time::zero()
{
	return 0;
}

SLIB_INLINE void Time::setZero()
{
	m_time = 0;
}

SLIB_INLINE sl_bool Time::isZero() const
{
	return m_time == 0;
}

SLIB_INLINE sl_bool Time::isNotZero() const
{
	return m_time != 0;
}

SLIB_INLINE sl_int64 Time::toInt() const
{
	return m_time;
}

SLIB_INLINE Time& Time::operator=(const Time& other)
{
	m_time = other.m_time;
	return *this;
}

SLIB_INLINE Time& Time::operator=(sl_int32 time)
{
	m_time = time;
	return *this;
}

SLIB_INLINE Time& Time::operator=(sl_uint32 time)
{
	m_time = time;
	return *this;
}

SLIB_INLINE Time& Time::operator=(sl_int64 time)
{
	m_time = time;
	return *this;
}

SLIB_INLINE Time& Time::operator=(sl_uint64 time)
{
	m_time = time;
	return *this;
}

SLIB_INLINE sl_bool Time::operator==(const Time& other) const
{
	return m_time == other.m_time;
}

SLIB_INLINE sl_bool Time::operator<=(const Time& other) const
{
	return m_time <= other.m_time;
}

SLIB_INLINE sl_bool Time::operator>=(const Time& other) const
{
	return m_time >= other.m_time;
}

SLIB_INLINE sl_bool Time::operator!=(const Time& other) const
{
	return m_time != other.m_time;
}

SLIB_INLINE sl_bool Time::operator<(const Time& other) const
{
	return m_time < other.m_time;
}

SLIB_INLINE sl_bool Time::operator>(const Time& other) const
{
	return m_time > other.m_time;
}

SLIB_INLINE Time Time::operator+(sl_int64 time) const
{
	return m_time + time;
}

SLIB_INLINE Time Time::operator+(const Time& time) const
{
	return m_time + time.m_time;
}

SLIB_INLINE Time& Time::operator+=(sl_int64 time)
{
	m_time += time;
	return *this;
}

SLIB_INLINE Time& Time::operator+=(const Time& time)
{
	m_time += time.m_time;
	return *this;
}

SLIB_INLINE Time Time::operator-(sl_int64 time) const
{
	return m_time - time;
}

SLIB_INLINE Time Time::operator-(const Time& time) const
{
	return m_time - time.m_time;
}

SLIB_INLINE Time& Time::operator-=(sl_int64 time)
{
	m_time -= time;
	return *this;
}

SLIB_INLINE Time& Time::operator-=(const Time& time)
{
	m_time -= time.m_time;
	return *this;
}

SLIB_NAMESPACE_END

#endif
