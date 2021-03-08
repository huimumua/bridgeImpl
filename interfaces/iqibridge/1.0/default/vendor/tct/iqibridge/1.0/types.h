#ifndef HIDL_GENERATED_VENDOR_TCT_IQIBRIDGE_V1_0_TYPES_H
#define HIDL_GENERATED_VENDOR_TCT_IQIBRIDGE_V1_0_TYPES_H

#include <hidl/HidlSupport.h>
#include <hidl/MQDescriptor.h>
#include <utils/NativeHandle.h>
#include <utils/misc.h>

namespace vendor {
namespace tct {
namespace iqibridge {
namespace V1_0 {

// Forward declaration for forward reference support:
enum class iq_porting_base_status : int64_t;
enum class iq_porting_status : int64_t;
enum class iq_porting_io_status : int64_t;

typedef int64_t iq_porting_status_t;

typedef uint64_t iq_io_event_t;

enum class iq_porting_base_status : int64_t {
    IQ_PORTING_IOEVENT_WRITABLE = 1ll,
    IQ_PORTING_IOEVENT_WRITE_COMPLETE = 2ll /* (::vendor::tct::iqibridge::V1_0::iq_porting_base_status.IQ_PORTING_IOEVENT_WRITABLE implicitly + 1) */,
    IQ_PORTING_IOEVENT_READABLE = 3ll /* (::vendor::tct::iqibridge::V1_0::iq_porting_base_status.IQ_PORTING_IOEVENT_WRITE_COMPLETE implicitly + 1) */,
    IQ_PORTING_IOEVENT_READ_COMPLETE = 4ll /* (::vendor::tct::iqibridge::V1_0::iq_porting_base_status.IQ_PORTING_IOEVENT_READABLE implicitly + 1) */,
    IQ_PORTING_IOEVENT_ERROR = 5ll /* (::vendor::tct::iqibridge::V1_0::iq_porting_base_status.IQ_PORTING_IOEVENT_READ_COMPLETE implicitly + 1) */,
    IQ_PORTING_IOEVENT_OPEN_COMPLETE = 6ll /* (::vendor::tct::iqibridge::V1_0::iq_porting_base_status.IQ_PORTING_IOEVENT_ERROR implicitly + 1) */,
    IQ_PORTING_IOEVENT_NETWORK_BASE = 2048ll /* 0x800 */,
    IQ_PORTING_IOEVENT_SOCKET_BASE = 4096ll /* 0x1000 */,
    IQ_PORTING_IOEVENT_SMS_BASE = 6144ll /* 0x1800 */,
};

enum class iq_porting_status : int64_t {
    IQ_PORTING_OK = 0ll,
    IQ_PORTING_ERROR = -65536ll /* (-0x10000) */,
    IQ_PORTING_NOT_IMPLEMENTED = -65535ll /* (::vendor::tct::iqibridge::V1_0::iq_porting_status.IQ_PORTING_ERROR implicitly + 1) */,
    IQ_PORTING_INVALID_PARAM = -65534ll /* (::vendor::tct::iqibridge::V1_0::iq_porting_status.IQ_PORTING_NOT_IMPLEMENTED implicitly + 1) */,
    IQ_PORTING_TIMEOUT = -65533ll /* (::vendor::tct::iqibridge::V1_0::iq_porting_status.IQ_PORTING_INVALID_PARAM implicitly + 1) */,
    IQ_PORTING_OUT_OF_MEMORY = -65532ll /* (::vendor::tct::iqibridge::V1_0::iq_porting_status.IQ_PORTING_TIMEOUT implicitly + 1) */,
    IQ_PORTING_SHUTDOWN_COMPLETE = -65531ll /* (::vendor::tct::iqibridge::V1_0::iq_porting_status.IQ_PORTING_OUT_OF_MEMORY implicitly + 1) */,
    IQ_PORTING_IO_ERROR_BASE = -69632ll /* (-0x11000) */,
    IQ_PORTING_FILE_ERROR_BASE = -73728ll /* (-0x12000) */,
    IQ_PORTING_SERIAL_ERROR_BASE = -77824ll /* (-0x13000) */,
    IQ_PORTING_NET_ERROR_BASE = -81920ll /* (-0x14000) */,
    IQ_PORTING_CLIENT_ERROR_BASE = -86016ll /* (-0x15000) */,
    IQ_PORTING_SERVER_ERROR_BASE = -90112ll /* (-0x16000) */,
};

enum class iq_porting_io_status : int64_t {
    IQ_PORTING_IO_COMPLETED = 0ll,
    IQ_PORTING_IO_WOULDBLOCK = -69632ll /* (-0x11000) */,
    IQ_PORTING_IO_ASYNC_PENDING = -69631ll /* (::vendor::tct::iqibridge::V1_0::iq_porting_io_status.IQ_PORTING_IO_WOULDBLOCK implicitly + 1) */,
    IQ_PORTING_IO_BROKEN = -69630ll /* (::vendor::tct::iqibridge::V1_0::iq_porting_io_status.IQ_PORTING_IO_ASYNC_PENDING implicitly + 1) */,
};

//
// type declarations for package
//

template<typename>
static inline std::string toString(int64_t o);
static inline std::string toString(::vendor::tct::iqibridge::V1_0::iq_porting_base_status o);

constexpr int64_t operator|(const ::vendor::tct::iqibridge::V1_0::iq_porting_base_status lhs, const ::vendor::tct::iqibridge::V1_0::iq_porting_base_status rhs) {
    return static_cast<int64_t>(static_cast<int64_t>(lhs) | static_cast<int64_t>(rhs));
}
constexpr int64_t operator|(const int64_t lhs, const ::vendor::tct::iqibridge::V1_0::iq_porting_base_status rhs) {
    return static_cast<int64_t>(lhs | static_cast<int64_t>(rhs));
}
constexpr int64_t operator|(const ::vendor::tct::iqibridge::V1_0::iq_porting_base_status lhs, const int64_t rhs) {
    return static_cast<int64_t>(static_cast<int64_t>(lhs) | rhs);
}
constexpr int64_t operator&(const ::vendor::tct::iqibridge::V1_0::iq_porting_base_status lhs, const ::vendor::tct::iqibridge::V1_0::iq_porting_base_status rhs) {
    return static_cast<int64_t>(static_cast<int64_t>(lhs) & static_cast<int64_t>(rhs));
}
constexpr int64_t operator&(const int64_t lhs, const ::vendor::tct::iqibridge::V1_0::iq_porting_base_status rhs) {
    return static_cast<int64_t>(lhs & static_cast<int64_t>(rhs));
}
constexpr int64_t operator&(const ::vendor::tct::iqibridge::V1_0::iq_porting_base_status lhs, const int64_t rhs) {
    return static_cast<int64_t>(static_cast<int64_t>(lhs) & rhs);
}
constexpr int64_t &operator|=(int64_t& v, const ::vendor::tct::iqibridge::V1_0::iq_porting_base_status e) {
    v |= static_cast<int64_t>(e);
    return v;
}
constexpr int64_t &operator&=(int64_t& v, const ::vendor::tct::iqibridge::V1_0::iq_porting_base_status e) {
    v &= static_cast<int64_t>(e);
    return v;
}

template<typename>
static inline std::string toString(int64_t o);
static inline std::string toString(::vendor::tct::iqibridge::V1_0::iq_porting_status o);

constexpr int64_t operator|(const ::vendor::tct::iqibridge::V1_0::iq_porting_status lhs, const ::vendor::tct::iqibridge::V1_0::iq_porting_status rhs) {
    return static_cast<int64_t>(static_cast<int64_t>(lhs) | static_cast<int64_t>(rhs));
}
constexpr int64_t operator|(const int64_t lhs, const ::vendor::tct::iqibridge::V1_0::iq_porting_status rhs) {
    return static_cast<int64_t>(lhs | static_cast<int64_t>(rhs));
}
constexpr int64_t operator|(const ::vendor::tct::iqibridge::V1_0::iq_porting_status lhs, const int64_t rhs) {
    return static_cast<int64_t>(static_cast<int64_t>(lhs) | rhs);
}
constexpr int64_t operator&(const ::vendor::tct::iqibridge::V1_0::iq_porting_status lhs, const ::vendor::tct::iqibridge::V1_0::iq_porting_status rhs) {
    return static_cast<int64_t>(static_cast<int64_t>(lhs) & static_cast<int64_t>(rhs));
}
constexpr int64_t operator&(const int64_t lhs, const ::vendor::tct::iqibridge::V1_0::iq_porting_status rhs) {
    return static_cast<int64_t>(lhs & static_cast<int64_t>(rhs));
}
constexpr int64_t operator&(const ::vendor::tct::iqibridge::V1_0::iq_porting_status lhs, const int64_t rhs) {
    return static_cast<int64_t>(static_cast<int64_t>(lhs) & rhs);
}
constexpr int64_t &operator|=(int64_t& v, const ::vendor::tct::iqibridge::V1_0::iq_porting_status e) {
    v |= static_cast<int64_t>(e);
    return v;
}
constexpr int64_t &operator&=(int64_t& v, const ::vendor::tct::iqibridge::V1_0::iq_porting_status e) {
    v &= static_cast<int64_t>(e);
    return v;
}

template<typename>
static inline std::string toString(int64_t o);
static inline std::string toString(::vendor::tct::iqibridge::V1_0::iq_porting_io_status o);

constexpr int64_t operator|(const ::vendor::tct::iqibridge::V1_0::iq_porting_io_status lhs, const ::vendor::tct::iqibridge::V1_0::iq_porting_io_status rhs) {
    return static_cast<int64_t>(static_cast<int64_t>(lhs) | static_cast<int64_t>(rhs));
}
constexpr int64_t operator|(const int64_t lhs, const ::vendor::tct::iqibridge::V1_0::iq_porting_io_status rhs) {
    return static_cast<int64_t>(lhs | static_cast<int64_t>(rhs));
}
constexpr int64_t operator|(const ::vendor::tct::iqibridge::V1_0::iq_porting_io_status lhs, const int64_t rhs) {
    return static_cast<int64_t>(static_cast<int64_t>(lhs) | rhs);
}
constexpr int64_t operator&(const ::vendor::tct::iqibridge::V1_0::iq_porting_io_status lhs, const ::vendor::tct::iqibridge::V1_0::iq_porting_io_status rhs) {
    return static_cast<int64_t>(static_cast<int64_t>(lhs) & static_cast<int64_t>(rhs));
}
constexpr int64_t operator&(const int64_t lhs, const ::vendor::tct::iqibridge::V1_0::iq_porting_io_status rhs) {
    return static_cast<int64_t>(lhs & static_cast<int64_t>(rhs));
}
constexpr int64_t operator&(const ::vendor::tct::iqibridge::V1_0::iq_porting_io_status lhs, const int64_t rhs) {
    return static_cast<int64_t>(static_cast<int64_t>(lhs) & rhs);
}
constexpr int64_t &operator|=(int64_t& v, const ::vendor::tct::iqibridge::V1_0::iq_porting_io_status e) {
    v |= static_cast<int64_t>(e);
    return v;
}
constexpr int64_t &operator&=(int64_t& v, const ::vendor::tct::iqibridge::V1_0::iq_porting_io_status e) {
    v &= static_cast<int64_t>(e);
    return v;
}

//
// type header definitions for package
//

template<>
inline std::string toString<::vendor::tct::iqibridge::V1_0::iq_porting_base_status>(int64_t o) {
    using ::android::hardware::details::toHexString;
    std::string os;
    ::android::hardware::hidl_bitfield<::vendor::tct::iqibridge::V1_0::iq_porting_base_status> flipped = 0;
    bool first = true;
    if ((o & ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_WRITABLE) == static_cast<int64_t>(::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_WRITABLE)) {
        os += (first ? "" : " | ");
        os += "IQ_PORTING_IOEVENT_WRITABLE";
        first = false;
        flipped |= ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_WRITABLE;
    }
    if ((o & ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_WRITE_COMPLETE) == static_cast<int64_t>(::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_WRITE_COMPLETE)) {
        os += (first ? "" : " | ");
        os += "IQ_PORTING_IOEVENT_WRITE_COMPLETE";
        first = false;
        flipped |= ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_WRITE_COMPLETE;
    }
    if ((o & ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_READABLE) == static_cast<int64_t>(::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_READABLE)) {
        os += (first ? "" : " | ");
        os += "IQ_PORTING_IOEVENT_READABLE";
        first = false;
        flipped |= ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_READABLE;
    }
    if ((o & ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_READ_COMPLETE) == static_cast<int64_t>(::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_READ_COMPLETE)) {
        os += (first ? "" : " | ");
        os += "IQ_PORTING_IOEVENT_READ_COMPLETE";
        first = false;
        flipped |= ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_READ_COMPLETE;
    }
    if ((o & ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_ERROR) == static_cast<int64_t>(::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_ERROR)) {
        os += (first ? "" : " | ");
        os += "IQ_PORTING_IOEVENT_ERROR";
        first = false;
        flipped |= ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_ERROR;
    }
    if ((o & ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_OPEN_COMPLETE) == static_cast<int64_t>(::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_OPEN_COMPLETE)) {
        os += (first ? "" : " | ");
        os += "IQ_PORTING_IOEVENT_OPEN_COMPLETE";
        first = false;
        flipped |= ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_OPEN_COMPLETE;
    }
    if ((o & ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_NETWORK_BASE) == static_cast<int64_t>(::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_NETWORK_BASE)) {
        os += (first ? "" : " | ");
        os += "IQ_PORTING_IOEVENT_NETWORK_BASE";
        first = false;
        flipped |= ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_NETWORK_BASE;
    }
    if ((o & ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_SOCKET_BASE) == static_cast<int64_t>(::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_SOCKET_BASE)) {
        os += (first ? "" : " | ");
        os += "IQ_PORTING_IOEVENT_SOCKET_BASE";
        first = false;
        flipped |= ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_SOCKET_BASE;
    }
    if ((o & ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_SMS_BASE) == static_cast<int64_t>(::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_SMS_BASE)) {
        os += (first ? "" : " | ");
        os += "IQ_PORTING_IOEVENT_SMS_BASE";
        first = false;
        flipped |= ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_SMS_BASE;
    }
    if (o != flipped) {
        os += (first ? "" : " | ");
        os += toHexString(o & (~flipped));
    }os += " (";
    os += toHexString(o);
    os += ")";
    return os;
}

static inline std::string toString(::vendor::tct::iqibridge::V1_0::iq_porting_base_status o) {
    using ::android::hardware::details::toHexString;
    if (o == ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_WRITABLE) {
        return "IQ_PORTING_IOEVENT_WRITABLE";
    }
    if (o == ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_WRITE_COMPLETE) {
        return "IQ_PORTING_IOEVENT_WRITE_COMPLETE";
    }
    if (o == ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_READABLE) {
        return "IQ_PORTING_IOEVENT_READABLE";
    }
    if (o == ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_READ_COMPLETE) {
        return "IQ_PORTING_IOEVENT_READ_COMPLETE";
    }
    if (o == ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_ERROR) {
        return "IQ_PORTING_IOEVENT_ERROR";
    }
    if (o == ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_OPEN_COMPLETE) {
        return "IQ_PORTING_IOEVENT_OPEN_COMPLETE";
    }
    if (o == ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_NETWORK_BASE) {
        return "IQ_PORTING_IOEVENT_NETWORK_BASE";
    }
    if (o == ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_SOCKET_BASE) {
        return "IQ_PORTING_IOEVENT_SOCKET_BASE";
    }
    if (o == ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_SMS_BASE) {
        return "IQ_PORTING_IOEVENT_SMS_BASE";
    }
    std::string os;
    os += toHexString(static_cast<int64_t>(o));
    return os;
}

template<>
inline std::string toString<::vendor::tct::iqibridge::V1_0::iq_porting_status>(int64_t o) {
    using ::android::hardware::details::toHexString;
    std::string os;
    ::android::hardware::hidl_bitfield<::vendor::tct::iqibridge::V1_0::iq_porting_status> flipped = 0;
    bool first = true;
    if ((o & ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_OK) == static_cast<int64_t>(::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_OK)) {
        os += (first ? "" : " | ");
        os += "IQ_PORTING_OK";
        first = false;
        flipped |= ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_OK;
    }
    if ((o & ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_ERROR) == static_cast<int64_t>(::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_ERROR)) {
        os += (first ? "" : " | ");
        os += "IQ_PORTING_ERROR";
        first = false;
        flipped |= ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_ERROR;
    }
    if ((o & ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_NOT_IMPLEMENTED) == static_cast<int64_t>(::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_NOT_IMPLEMENTED)) {
        os += (first ? "" : " | ");
        os += "IQ_PORTING_NOT_IMPLEMENTED";
        first = false;
        flipped |= ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_NOT_IMPLEMENTED;
    }
    if ((o & ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_INVALID_PARAM) == static_cast<int64_t>(::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_INVALID_PARAM)) {
        os += (first ? "" : " | ");
        os += "IQ_PORTING_INVALID_PARAM";
        first = false;
        flipped |= ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_INVALID_PARAM;
    }
    if ((o & ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_TIMEOUT) == static_cast<int64_t>(::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_TIMEOUT)) {
        os += (first ? "" : " | ");
        os += "IQ_PORTING_TIMEOUT";
        first = false;
        flipped |= ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_TIMEOUT;
    }
    if ((o & ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_OUT_OF_MEMORY) == static_cast<int64_t>(::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_OUT_OF_MEMORY)) {
        os += (first ? "" : " | ");
        os += "IQ_PORTING_OUT_OF_MEMORY";
        first = false;
        flipped |= ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_OUT_OF_MEMORY;
    }
    if ((o & ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_SHUTDOWN_COMPLETE) == static_cast<int64_t>(::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_SHUTDOWN_COMPLETE)) {
        os += (first ? "" : " | ");
        os += "IQ_PORTING_SHUTDOWN_COMPLETE";
        first = false;
        flipped |= ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_SHUTDOWN_COMPLETE;
    }
    if ((o & ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_IO_ERROR_BASE) == static_cast<int64_t>(::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_IO_ERROR_BASE)) {
        os += (first ? "" : " | ");
        os += "IQ_PORTING_IO_ERROR_BASE";
        first = false;
        flipped |= ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_IO_ERROR_BASE;
    }
    if ((o & ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_FILE_ERROR_BASE) == static_cast<int64_t>(::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_FILE_ERROR_BASE)) {
        os += (first ? "" : " | ");
        os += "IQ_PORTING_FILE_ERROR_BASE";
        first = false;
        flipped |= ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_FILE_ERROR_BASE;
    }
    if ((o & ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_SERIAL_ERROR_BASE) == static_cast<int64_t>(::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_SERIAL_ERROR_BASE)) {
        os += (first ? "" : " | ");
        os += "IQ_PORTING_SERIAL_ERROR_BASE";
        first = false;
        flipped |= ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_SERIAL_ERROR_BASE;
    }
    if ((o & ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_NET_ERROR_BASE) == static_cast<int64_t>(::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_NET_ERROR_BASE)) {
        os += (first ? "" : " | ");
        os += "IQ_PORTING_NET_ERROR_BASE";
        first = false;
        flipped |= ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_NET_ERROR_BASE;
    }
    if ((o & ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_CLIENT_ERROR_BASE) == static_cast<int64_t>(::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_CLIENT_ERROR_BASE)) {
        os += (first ? "" : " | ");
        os += "IQ_PORTING_CLIENT_ERROR_BASE";
        first = false;
        flipped |= ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_CLIENT_ERROR_BASE;
    }
    if ((o & ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_SERVER_ERROR_BASE) == static_cast<int64_t>(::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_SERVER_ERROR_BASE)) {
        os += (first ? "" : " | ");
        os += "IQ_PORTING_SERVER_ERROR_BASE";
        first = false;
        flipped |= ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_SERVER_ERROR_BASE;
    }
    if (o != flipped) {
        os += (first ? "" : " | ");
        os += toHexString(o & (~flipped));
    }os += " (";
    os += toHexString(o);
    os += ")";
    return os;
}

static inline std::string toString(::vendor::tct::iqibridge::V1_0::iq_porting_status o) {
    using ::android::hardware::details::toHexString;
    if (o == ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_OK) {
        return "IQ_PORTING_OK";
    }
    if (o == ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_ERROR) {
        return "IQ_PORTING_ERROR";
    }
    if (o == ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_NOT_IMPLEMENTED) {
        return "IQ_PORTING_NOT_IMPLEMENTED";
    }
    if (o == ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_INVALID_PARAM) {
        return "IQ_PORTING_INVALID_PARAM";
    }
    if (o == ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_TIMEOUT) {
        return "IQ_PORTING_TIMEOUT";
    }
    if (o == ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_OUT_OF_MEMORY) {
        return "IQ_PORTING_OUT_OF_MEMORY";
    }
    if (o == ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_SHUTDOWN_COMPLETE) {
        return "IQ_PORTING_SHUTDOWN_COMPLETE";
    }
    if (o == ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_IO_ERROR_BASE) {
        return "IQ_PORTING_IO_ERROR_BASE";
    }
    if (o == ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_FILE_ERROR_BASE) {
        return "IQ_PORTING_FILE_ERROR_BASE";
    }
    if (o == ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_SERIAL_ERROR_BASE) {
        return "IQ_PORTING_SERIAL_ERROR_BASE";
    }
    if (o == ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_NET_ERROR_BASE) {
        return "IQ_PORTING_NET_ERROR_BASE";
    }
    if (o == ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_CLIENT_ERROR_BASE) {
        return "IQ_PORTING_CLIENT_ERROR_BASE";
    }
    if (o == ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_SERVER_ERROR_BASE) {
        return "IQ_PORTING_SERVER_ERROR_BASE";
    }
    std::string os;
    os += toHexString(static_cast<int64_t>(o));
    return os;
}

template<>
inline std::string toString<::vendor::tct::iqibridge::V1_0::iq_porting_io_status>(int64_t o) {
    using ::android::hardware::details::toHexString;
    std::string os;
    ::android::hardware::hidl_bitfield<::vendor::tct::iqibridge::V1_0::iq_porting_io_status> flipped = 0;
    bool first = true;
    if ((o & ::vendor::tct::iqibridge::V1_0::iq_porting_io_status::IQ_PORTING_IO_COMPLETED) == static_cast<int64_t>(::vendor::tct::iqibridge::V1_0::iq_porting_io_status::IQ_PORTING_IO_COMPLETED)) {
        os += (first ? "" : " | ");
        os += "IQ_PORTING_IO_COMPLETED";
        first = false;
        flipped |= ::vendor::tct::iqibridge::V1_0::iq_porting_io_status::IQ_PORTING_IO_COMPLETED;
    }
    if ((o & ::vendor::tct::iqibridge::V1_0::iq_porting_io_status::IQ_PORTING_IO_WOULDBLOCK) == static_cast<int64_t>(::vendor::tct::iqibridge::V1_0::iq_porting_io_status::IQ_PORTING_IO_WOULDBLOCK)) {
        os += (first ? "" : " | ");
        os += "IQ_PORTING_IO_WOULDBLOCK";
        first = false;
        flipped |= ::vendor::tct::iqibridge::V1_0::iq_porting_io_status::IQ_PORTING_IO_WOULDBLOCK;
    }
    if ((o & ::vendor::tct::iqibridge::V1_0::iq_porting_io_status::IQ_PORTING_IO_ASYNC_PENDING) == static_cast<int64_t>(::vendor::tct::iqibridge::V1_0::iq_porting_io_status::IQ_PORTING_IO_ASYNC_PENDING)) {
        os += (first ? "" : " | ");
        os += "IQ_PORTING_IO_ASYNC_PENDING";
        first = false;
        flipped |= ::vendor::tct::iqibridge::V1_0::iq_porting_io_status::IQ_PORTING_IO_ASYNC_PENDING;
    }
    if ((o & ::vendor::tct::iqibridge::V1_0::iq_porting_io_status::IQ_PORTING_IO_BROKEN) == static_cast<int64_t>(::vendor::tct::iqibridge::V1_0::iq_porting_io_status::IQ_PORTING_IO_BROKEN)) {
        os += (first ? "" : " | ");
        os += "IQ_PORTING_IO_BROKEN";
        first = false;
        flipped |= ::vendor::tct::iqibridge::V1_0::iq_porting_io_status::IQ_PORTING_IO_BROKEN;
    }
    if (o != flipped) {
        os += (first ? "" : " | ");
        os += toHexString(o & (~flipped));
    }os += " (";
    os += toHexString(o);
    os += ")";
    return os;
}

static inline std::string toString(::vendor::tct::iqibridge::V1_0::iq_porting_io_status o) {
    using ::android::hardware::details::toHexString;
    if (o == ::vendor::tct::iqibridge::V1_0::iq_porting_io_status::IQ_PORTING_IO_COMPLETED) {
        return "IQ_PORTING_IO_COMPLETED";
    }
    if (o == ::vendor::tct::iqibridge::V1_0::iq_porting_io_status::IQ_PORTING_IO_WOULDBLOCK) {
        return "IQ_PORTING_IO_WOULDBLOCK";
    }
    if (o == ::vendor::tct::iqibridge::V1_0::iq_porting_io_status::IQ_PORTING_IO_ASYNC_PENDING) {
        return "IQ_PORTING_IO_ASYNC_PENDING";
    }
    if (o == ::vendor::tct::iqibridge::V1_0::iq_porting_io_status::IQ_PORTING_IO_BROKEN) {
        return "IQ_PORTING_IO_BROKEN";
    }
    std::string os;
    os += toHexString(static_cast<int64_t>(o));
    return os;
}


}  // namespace V1_0
}  // namespace iqibridge
}  // namespace tct
}  // namespace vendor

//
// global type declarations for package
//

namespace android {
namespace hardware {
namespace details {
template<> constexpr std::array<::vendor::tct::iqibridge::V1_0::iq_porting_base_status, 9> hidl_enum_values<::vendor::tct::iqibridge::V1_0::iq_porting_base_status> = {
    ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_WRITABLE,
    ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_WRITE_COMPLETE,
    ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_READABLE,
    ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_READ_COMPLETE,
    ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_ERROR,
    ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_OPEN_COMPLETE,
    ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_NETWORK_BASE,
    ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_SOCKET_BASE,
    ::vendor::tct::iqibridge::V1_0::iq_porting_base_status::IQ_PORTING_IOEVENT_SMS_BASE,
};
}  // namespace details
}  // namespace hardware
}  // namespace android

namespace android {
namespace hardware {
namespace details {
template<> constexpr std::array<::vendor::tct::iqibridge::V1_0::iq_porting_status, 13> hidl_enum_values<::vendor::tct::iqibridge::V1_0::iq_porting_status> = {
    ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_OK,
    ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_ERROR,
    ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_NOT_IMPLEMENTED,
    ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_INVALID_PARAM,
    ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_TIMEOUT,
    ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_OUT_OF_MEMORY,
    ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_SHUTDOWN_COMPLETE,
    ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_IO_ERROR_BASE,
    ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_FILE_ERROR_BASE,
    ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_SERIAL_ERROR_BASE,
    ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_NET_ERROR_BASE,
    ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_CLIENT_ERROR_BASE,
    ::vendor::tct::iqibridge::V1_0::iq_porting_status::IQ_PORTING_SERVER_ERROR_BASE,
};
}  // namespace details
}  // namespace hardware
}  // namespace android

namespace android {
namespace hardware {
namespace details {
template<> constexpr std::array<::vendor::tct::iqibridge::V1_0::iq_porting_io_status, 4> hidl_enum_values<::vendor::tct::iqibridge::V1_0::iq_porting_io_status> = {
    ::vendor::tct::iqibridge::V1_0::iq_porting_io_status::IQ_PORTING_IO_COMPLETED,
    ::vendor::tct::iqibridge::V1_0::iq_porting_io_status::IQ_PORTING_IO_WOULDBLOCK,
    ::vendor::tct::iqibridge::V1_0::iq_porting_io_status::IQ_PORTING_IO_ASYNC_PENDING,
    ::vendor::tct::iqibridge::V1_0::iq_porting_io_status::IQ_PORTING_IO_BROKEN,
};
}  // namespace details
}  // namespace hardware
}  // namespace android


#endif  // HIDL_GENERATED_VENDOR_TCT_IQIBRIDGE_V1_0_TYPES_H
