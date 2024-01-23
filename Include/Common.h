#ifndef COMMON_H
#define COMMON_H

#include <cstdint>
#include <string>
#include <vector>
#include <array>
#include <set>
#include <map>
#include <queue>
#include <deque>
#include <stack>
#include <optional>
#include <memory>
#include <functional>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <string_view>
#include <ranges>
#include <iterator>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using f32 = float;
using f64 = double;

// Strings 
using String = std::string;

using StringView = std::string_view;

// Iterators
template <typename T>
using Range = std::ranges<T>;

template <typename T>
using Iterator = std::iterator<T>;

// Collections
template <typename T, unsigned int N>
using Array = std::array<T, N>;

template<typename T>
using List = std::vector<T>;

template<typename T>
using Set = std::set<T>;

template<typename K, typename V>
using Map = std::map<K, V>;

template<typename T>
using Queue = std::queue<T>;

template<typename T>
using Deque = std::deque<T>;

template<typename T>
using Stack = std::stack<T>;

// Smart Pointers
template<typename T>
using Optional = std::optional<T>;

#define Some(val) std::make_optional(val)
#define None() std::nullopt

template<typename T>
using Result = std::result<T>;

template<typename T>
using Box = std::unique_ptr<T>;

#define BoxOf(ptr) std::make_unique(ptr)

template<typename T>
using Ref = std::shared_ptr<T>;

#define RefOf(ptr) std::make_shared(ptr)

template<typename T>
using WeakRef = std::weak_ptr<T>;

// Concurrency
template<typename T>
using Atomic = std::atomic<T>;

template<typename T>
using Mutex = std::mutex<T>;

template<typename T>
using Lock = std::lock<T>;

template<typename T>
using Condition = std::condition<T>;

template<typename T>
using Thread = std::thread<T>;

// Functional
template<typename T>
using Fn = std::function<T>;

#endif // COMMON_H
