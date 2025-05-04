#pragma once

#include <cmath>
#include <string>
#include <format>
#include "Concepts.hpp"

namespace GE::Math
{
    template <GE::Concepts::arithmetic T = float>

    class Vector2 final
    {
    public:
        T x, y;

    public:
        constexpr Vector2() noexcept : x{}, y{} {}
        constexpr explicit Vector2(T v) noexcept : x{v}, y{v} {}
        constexpr Vector2(T x, T y) noexcept : x{x}, y{y} {}

        template <GE::Concepts::arithmetic K, GE::Concepts::arithmetic L>
        constexpr Vector2(K x, L y) noexcept : x(x), y(y) {}

        template <GE::Concepts::arithmetic K>
        constexpr Vector2(const Vector2<K> &rhs) noexcept : x(rhs.x), y(rhs.y) {}

        template <GE::Concepts::arithmetic K>
        constexpr Vector2(Vector2<K> &&rhs) noexcept : x(std::move(rhs.x)), y(std::move(rhs.y)) {}

        ~Vector2() = default;

        inline static constexpr Vector2 up{0, 1}, down{0, -1}, right{1, 0},
            left{-1, 0}, one{1}, zero{0};

        constexpr auto length() const noexcept
        {
            return std::sqrt(length_squared());
        }

        constexpr auto length_squared() const noexcept
        {
            return (x * x + y * y);
        }

        constexpr Vector2 abs() const noexcept
        {
            return Vector2(std::abs(x), std::abs(y));
        }

        template <GE::Concepts::arithmetic K>
        constexpr Vector2 max(const Vector2<K> &rhs) const noexcept
        {
            return Vector2(std::max(x, static_cast<T>(rhs.x)),
                           std::max(y, static_cast<T>(rhs.y)));
        }

        template <GE::Concepts::arithmetic K>
        constexpr Vector2 min(const Vector2<K> &rhs) const noexcept
        {
            return Vector2(std::min(x, static_cast<T>(rhs.x)),
                           std::min(y, static_cast<T>(rhs.y)));
        }

        constexpr auto normalized() const noexcept
        {
            using R = std::conditional_t<std::is_integral_v<T>, double, T>;
            R len = length();

            if (len == static_cast<R>(0))
                return Vector2<R>::zero;

            return Vector2<R>(x / len, y / len);
        }

        void normalize() noexcept requires std::is_floating_point_v<T>
        {
            auto len = length();

            if (len == static_cast<T>(0))
                return;

            x /= len, y /= len;
        }

        template <GE::Concepts::arithmetic K>
        constexpr auto dot(const Vector2<K> &rhs) const noexcept
        {
            return (x * rhs.x + y * rhs.y);
        }

        template <GE::Concepts::arithmetic K>
        constexpr auto cross(const Vector2<K> &rhs) const noexcept
        {
            return (x * rhs.y - y * rhs.x);
        }

        template <GE::Concepts::arithmetic K>
        constexpr auto distance(const Vector2<K> &rhs) const noexcept
        {
            return std::sqrt(distance_squared(rhs));
        }

        template <GE::Concepts::arithmetic K>
        constexpr auto distance_squared(const Vector2<K> &rhs) const noexcept
        {
            using R = std::common_type_t<T, K>;
            R dx = x - rhs.x, dy = y - rhs.y;
            return (dx * dx + dy * dy);
        }

        template <GE::Concepts::arithmetic K>
        constexpr Vector2 reflect(const Vector2<K> &normal) const noexcept
        {
            return (*this - normal * 2 * dot(normal));
        }

        template <GE::Concepts::arithmetic K>
        constexpr Vector2 slide(const Vector2<K> &normal) const noexcept
        {
            return *this - normal * dot(normal);
        }

        template <GE::Concepts::arithmetic K>
        constexpr auto angle(const Vector2<K> &rhs) const noexcept
        {
            return std::atan2(cross(rhs), dot(rhs));
        }

        template <GE::Concepts::arithmetic A>
        constexpr auto rotated(A angle) const noexcept
        {
            using R = std::common_type_t<T, A>;
            R cos_a = std::cos(angle), sin_a = std::sin(angle);
            return Vector2<R>(x * cos_a - y * sin_a,
                              x * sin_a + y * cos_a);
        }

        template <GE::Concepts::arithmetic K, GE::Concepts::arithmetic A>
        constexpr auto lerp(const Vector2<K> &rhs, A t) const noexcept
        {
            using R = std::common_type_t<T, K, A>;
            return Vector2<R>(std::lerp(static_cast<R>(x), static_cast<R>(rhs.x), static_cast<R>(t)),
                              std::lerp(static_cast<R>(y), static_cast<R>(rhs.y), static_cast<R>(t)));
        }

        template <GE::Concepts::arithmetic K, GE::Concepts::arithmetic A>
        constexpr auto slerp(const Vector2<K> &rhs, A t) const noexcept
        { 
            using R = std::common_type_t<T, K, A>;
            R len_sq = length_squared(), rhs_len_sq = rhs.length_squared();

            if (len_sq == static_cast<R>(0) || rhs_len_sq == static_cast<R>(0))
                return lerp(rhs, t);
            
            R scale = (std::lerp(std::sqrt(len_sq), std::sqrt(rhs_len_sq), static_cast<R>(t)) / std::sqrt(len_sq));

            return rotated(angle(rhs) * t) * scale;
        }

        template <GE::Concepts::arithmetic K>
        constexpr auto project(const Vector2<K> &rhs) const noexcept
        {
            return (rhs * (dot(rhs) / rhs.length_squared()));
        }

        constexpr bool is_zero() const noexcept
        {
            return (x == static_cast<T>(0) && y == static_cast<T>(0));
        }

        constexpr bool is_normalized() const noexcept
        {
            return std::abs(length_squared() - 1) < static_cast<T>(1e-5);
        }

        std::string to_string() const noexcept
        {
            return std::format("({}, {})", x, y);
        }

        template <GE::Concepts::arithmetic K>
        constexpr Vector2 &operator=(const Vector2<K> &rhs) noexcept
        {
            if (this != &rhs)
                x = rhs.x, y = rhs.y;

            return *this;
        }

        template <GE::Concepts::arithmetic K>
        constexpr Vector2 &operator=(Vector2<K> &&rhs) noexcept
        {
            if (this != &rhs)
                x = std::move(rhs.x), y = std::move(rhs.y);

            return *this;
        }

        template <GE::Concepts::arithmetic K>
        constexpr Vector2 operator+(const Vector2<K> &rhs) const noexcept
        {
            return Vector2(x + rhs.x, y + rhs.y);
        }

        template <GE::Concepts::arithmetic K>
        Vector2 &operator+=(const Vector2<K> &rhs) noexcept
        {
            x += rhs.x, y += rhs.y;
            return *this;
        }

        template <GE::Concepts::arithmetic K>
        constexpr Vector2 operator-(const Vector2<K> &rhs) const noexcept
        {
            return Vector2(x - rhs.x, y - rhs.y);
        }

        template <GE::Concepts::arithmetic K>
        Vector2 &operator-=(const Vector2<T> &rhs) noexcept
        {
            x -= rhs.x, y -= rhs.y;
            return *this;
        }

        template <GE::Concepts::arithmetic A>
        constexpr Vector2 operator*(A scalar) const noexcept
        {
            return Vector2(x * scalar, y * scalar);
        }

        template <GE::Concepts::arithmetic A>
        Vector2 &operator*=(A scalar) noexcept
        {
            x *= scalar, y *= scalar;
            return *this;
        }

        constexpr Vector2 operator/(T scalar) const noexcept
        {
            return Vector2(x / scalar, y / scalar);
        }

        Vector2 &operator/=(T scalar) noexcept
        {
            x /= scalar, y /= scalar;
            return *this;
        }

        template <GE::Concepts::arithmetic K>
        constexpr bool operator==(const Vector2<K> &rhs) const noexcept
        {
            if constexpr (std::is_floating_point_v<T> || std::is_floating_point_v<K>)
            {
                constexpr auto epsilon = static_cast<T>(1e-6);
                return (std::abs(x - static_cast<T>(rhs.x)) <= epsilon &&
                        std::abs(y - static_cast<T>(rhs.y) <= epsilon));
            } else
            {
                return (x == static_cast<T>(rhs.x) && y == static_cast<T>(rhs.y));
            }
        }

        template <GE::Concepts::arithmetic K>
        constexpr bool operator!=(const Vector2<K> &rhs) const noexcept
        {
            return !(*this == rhs);
        }

        template <GE::Concepts::arithmetic K>
        constexpr bool operator>(const Vector2<K> &rhs) const noexcept
        {
            using R = std::common_type_t<T, K>;
            return (static_cast<R>(length_squared()) > static_cast<R>(rhs.length_squared()));
        }

        template <GE::Concepts::arithmetic K>
        constexpr bool operator>=(const Vector2<K> &rhs) const noexcept
        {
            using R = std::common_type_t<T, K>;
            return (static_cast<R>(length_squared()) >= static_cast<R>(rhs.length_squared()));
        }

        template <GE::Concepts::arithmetic K>
        constexpr bool operator<(const Vector2<K> &rhs) const noexcept
        {
            using R = std::common_type_t<T, K>;
            return (static_cast<R>(length_squared()) < static_cast<R>(rhs.length_squared()));
        }

        template <GE::Concepts::arithmetic K>
        constexpr bool operator<=(const Vector2<K> &rhs) const noexcept
        {
            using R = std::common_type_t<T, K>;
            return (static_cast<R>(length_squared()) <= static_cast<R>(rhs.length_squared()));
        }
    };

    using Vector2f = Vector2<float>;
    using Vector2d = Vector2<double>;
    using Vector2i = Vector2<int>;
}