#pragma once

template <typename R, typename T>
static constexpr R scast(T val)
{
	return static_cast<R>(val);
}

template <typename R, typename T>
static constexpr R rcast(T val)
{
	return reinterpret_cast<R>(val);
}

template <typename R, typename T>
static constexpr R ccast(T val)
{
	return const_cast<R>(val);
}
