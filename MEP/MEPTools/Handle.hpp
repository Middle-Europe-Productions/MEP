#pragma once

#ifdef _DEBUG
	#include <crtdbg.h>
	#define ASSERT _ASSERTE
#else 
	#define ASSERT __noop
#endif

template <typename T>
struct HandleTraits {
	using Type = T;
	static Type Invalid() noexcept {
		return nullptr;
	}
};

template <typename Traits>
class  Handle {
	using Type = decltype(Traits::Invalid());
	Type m_value;

	void Close() noexcept {
		if (*this) {
			Traits::Close(m_value);
		}
	}
public:
	Handle(Handle const&) = delete;
	Handle& operator=(Handle const &) = delete;

	explicit Handle(Type value = Traits::Invalid())noexcept : m_value(value) {}

	Handle(Handle&& x)noexcept : m_value(x.Detach()) {}
	Handle operator=(Handle&& x) noexcept {
		if (this != &x) {
			Reset(x.Detach());
		}
		return *this;
	}
	~Handle() noexcept {
		Close();
	}
	explicit operator bool() const noexcept {
		return m_value != Traits::Invalid();
	}
	Type Get() const noexcept {
		return m_value;
	}
	Type* Set() noexcept {
		ASSERT(!*this);
		return &m_value;
	}
	Type Detach() noexcept {
		Type value = m_value;
		m_value = Traits::Invalid();
		return value;
	}
	bool Reset(Type value = Traits::Invalid()) noexcept {
		if (m_value != value) {
			Close();
			m_value = value;
		}
		return static_cast<bool>(*this);
	}
	void Swap(Handle<Traits>& x) noexcept {
		Type temp = m_value;
		m_value = x.m_value;
		x.m_value = temp;
	}
};

template <typename Traits>
void swap(Handle<Traits>& left, Handle<Traits>& right) noexcept {
	left.Swap(right);
}

template <typename Traits>
bool operator==(Handle<Traits> const &left, Handle<Traits> const &right) noexcept {
	return left.Get() == right.Get();
}
template <typename Traits>
bool operator!=(Handle<Traits> const &left, Handle<Traits> const &right) noexcept {
	return !(left == right);
}