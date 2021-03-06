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

#include "slib/core/definition.h"

#if defined(SLIB_PLATFORM_IS_APPLE)

#include "slib/core/platform_apple.h"

#include "slib/core/file.h"
#include "slib/core/safe_static.h"

namespace slib
{
	
#if defined(SLIB_PLATFORM_IS_IOS)
	UIInterfaceOrientation _g_slib_ui_screen_orientation = UIInterfaceOrientationPortrait;
#endif

	NSString* Apple::getNSStringFromString(const String& str, NSString* def)
	{
		String s = str;
		if (s.isNull()) {
			return def;
		}
		NSString* ret = [[NSString alloc] initWithUTF8String:s.getData()];
		if (ret != nil) {
			return ret;
		}
		return def;
	}

	NSString* Apple::getNSStringFromString16(const String16& str, NSString* def)
	{
		String16 s = str;
		if (s.isNull()) {
			return def;
		}
		NSString* ret = [[NSString alloc] initWithCharacters:(unichar*)s.getData() length:s.getLength()];
		if (ret != nil) {
			return ret;
		}
		return def;
	}

	String Apple::getStringFromNSString(NSString* str)
	{
		if (str == nil) {
			return sl_null;
		}
		const char* buf = [str UTF8String];
		return String::fromUtf8(buf);
	}

	String16 Apple::getString16FromNSString(NSString* str)
	{
		if (str == nil) {
			return sl_null;
		}
		sl_size len = (sl_size)([str length]);
		String16 ret = String16::allocate(len);
		if (ret.isNull()) {
			return ret;
		}
		NSRange range;
		range.length = len;
		range.location = 0;
		[str getCharacters:((unichar*)(ret.getData())) range:range];
		return ret;
	}

	String Apple::getFilePathFromNSURL(NSURL* url)
	{
		if (url != nil) {
			SLIB_STATIC_STRING(prefix, "file://");
			String path = Apple::getStringFromNSString([url path]);
			if (path.startsWith(prefix)) {
				path = path.substring(7);
			}
			return path;
		}
		return sl_null;
	}

	Memory Apple::getMemoryFromNSData(NSData* data)
	{
		if (data != nil) {
			sl_size n = (sl_size)([data length]);
			if (n > 0) {
				Memory mem = Memory::create(n);
				if (mem.isNotNull()) {
					char* p = (char*)(mem.getData());
					[data enumerateByteRangesUsingBlock:^(const void* bytes, NSRange byteRange, BOOL* stop) {
						Base::copyMemory(p + byteRange.location, bytes, byteRange.length);
					}];
					return mem;
				}
			}
		}
		return sl_null;
	}

	NSData* Apple::getNSDataFromMemory(const Memory& memory)
	{
		if(memory.isNotNull()) {
			return [NSData dataWithBytes:memory.getData() length:memory.getSize()];
		}
		
		return nil;
	}

	String Apple::getAssetFilePath(const String &path)
	{
		String fileExt = File::getFileExtension(path);
		String fileName = File::getFileNameOnly(path);
		String dirPath = File::getParentDirectoryPath(path);
		
		NSString* strFileName = getNSStringFromString(fileName);
		NSString* strFolderPath = getNSStringFromString(dirPath);
		NSString* strFileExtension = getNSStringFromString(fileExt);
		
		NSString *filePath = [[NSBundle mainBundle] pathForResource:strFileName ofType:strFileExtension inDirectory:strFolderPath];
		return Apple::getStringFromNSString(filePath);
	}

	SLIB_STATIC_ZERO_INITIALIZED(AtomicString, _g_system_version);
	sl_uint32 _g_system_version_major = 0;
	sl_uint32 _g_system_version_minor = 0;
	sl_bool _g_system_flagInitVersion = sl_true;

	void _priv_Apple_initSystemVersion()
	{
		if (_g_system_flagInitVersion) {
#if defined(SLIB_PLATFORM_IS_MACOS)
			double v = NSAppKitVersionNumber;
			if (v >= NSAppKitVersionNumber10_10) {
				_g_system_version = "10.10";
				_g_system_version_major = 10;
				_g_system_version_minor = 10;
			} else if (v >= NSAppKitVersionNumber10_9) {
				_g_system_version = "10.9";
				_g_system_version_major = 10;
				_g_system_version_minor = 9;
			} else if (v >= NSAppKitVersionNumber10_8) {
				_g_system_version = "10.8";
				_g_system_version_major = 10;
				_g_system_version_minor = 8;
			} else if (v >= NSAppKitVersionNumber10_7) {
				_g_system_version = "10.7";
				_g_system_version_major = 10;
				_g_system_version_minor = 7;
			} else if (v >= NSAppKitVersionNumber10_6) {
				_g_system_version = "10.6";
				_g_system_version_major = 10;
				_g_system_version_minor = 6;
			}
#elif defined(SLIB_PLATFORM_IS_IOS)
			NSString* _version = [[UIDevice currentDevice] systemVersion];
			String version = Apple::getStringFromNSString(_version);
			if (version.isNotEmpty()) {
				ListLocker<String> list(version.split("."));
				if (list.count > 0) {
					_g_system_version_major = list[0].parseUint32();
					if (list.count > 1) {
						_g_system_version_minor = list[1].parseUint32();
					}
				}
			}
			_g_system_version = version;
#endif
			_g_system_flagInitVersion = sl_false;
		}
	}

	String Apple::getSystemVersion()
	{
		_priv_Apple_initSystemVersion();
		return _g_system_version;
	}

	sl_uint32 Apple::getSystemMajorVersion()
	{
		_priv_Apple_initSystemVersion();
		return _g_system_version_major;
	}

	sl_uint32 Apple::getSystemMinorVersion()
	{
		_priv_Apple_initSystemVersion();
		return _g_system_version_minor;
	}

	String Apple::getMainBundlePath()
	{
		NSString* path = [[NSBundle mainBundle] bundlePath];
		return getStringFromNSString(path);
	}

}

#endif
