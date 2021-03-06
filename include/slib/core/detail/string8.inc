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

namespace slib
{
	
	struct _priv_String_Const
	{
		StringContainer* container;
		sl_int32 lock;
	};
	
	extern const _priv_String_Const _priv_String_Null;
	extern const _priv_String_Const _priv_String_Empty;
	
	SLIB_INLINE String::String(String&& src) noexcept
	{
		m_container = src.m_container;
		src.m_container = sl_null;
	}
	
	SLIB_INLINE String::String(AtomicString&& src) noexcept
	{
		m_container = src.m_container;
		src.m_container = sl_null;
	}
	
	SLIB_INLINE const String& String::null() noexcept
	{
		return *(reinterpret_cast<String const*>(&_priv_String_Null));
	}
	
	SLIB_INLINE const String& String::getEmpty() noexcept
	{
		return *(reinterpret_cast<String const*>(&_priv_String_Empty));
	}

	SLIB_INLINE const String& String::getNotNull() const noexcept
	{
		if (!m_container) {
			return *(reinterpret_cast<String const*>(&_priv_String_Empty));
		}
		return *this;
	}
	
	SLIB_INLINE sl_bool String::isNull() const noexcept
	{
		return m_container == sl_null;
	}

	SLIB_INLINE sl_bool String::isNotNull() const noexcept
	{
		return m_container != sl_null;
	}
	
	SLIB_INLINE sl_bool String::isEmpty() const noexcept
	{
		if (m_container) {
			return (m_container->len == 0);
		} else {
			return sl_true;
		}
	}
	
	SLIB_INLINE sl_bool String::isNotEmpty() const noexcept
	{
		if (m_container) {
			return (m_container->len != 0);
		} else {
			return sl_false;
		}
	}
	
	SLIB_INLINE sl_char8* String::getData() const noexcept
	{
		if (m_container) {
			return m_container->sz;
		} else {
			return (sl_char8*)((void*)(""));
		}
	}
	
	SLIB_INLINE sl_size String::getLength() const noexcept
	{
		if (m_container) {
			return m_container->len;
		} else {
			return 0;
		}
	}
	
	
	SLIB_INLINE AtomicString::Atomic(AtomicString&& src) noexcept
	{
		m_container = src.m_container;
		src.m_container = sl_null;
	}

	SLIB_INLINE AtomicString::Atomic(String&& src) noexcept
	{
		m_container = src.m_container;
		src.m_container = sl_null;
	}

	SLIB_INLINE const AtomicString& AtomicString::null() noexcept
	{
		return *(reinterpret_cast<AtomicString const*>(&_priv_String_Null));
	}
	
	SLIB_INLINE const AtomicString& AtomicString::getEmpty() noexcept
	{
		return *(reinterpret_cast<AtomicString const*>(&_priv_String_Empty));
	}

	SLIB_INLINE sl_bool AtomicString::isNull() const noexcept
	{
		return m_container == sl_null;
	}

	SLIB_INLINE sl_bool AtomicString::isNotNull() const noexcept
	{
		return m_container != sl_null;
	}


	extern const char* _priv_StringConv_radixPatternUpper;
	extern const char* _priv_StringConv_radixPatternLower;
	extern const sl_uint8* _priv_StringConv_radixInversePatternBig;
	extern const sl_uint8* _priv_StringConv_radixInversePatternSmall;

}
