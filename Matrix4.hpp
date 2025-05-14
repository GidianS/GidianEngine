#pragma once

template <floating_point T>
class Vector4;

template <floating_point T>
class Matrix2;

template <floating_point T>
class Matrix3;

template <floating_point T = float>
class Matrix4
{
public:
    T m[4][4];

public:
    constexpr Matrix4() noexcept
        : m{{0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}} {}

    template <arithmetic K>
    constexpr Matrix4(K v) noexcept
        : m{{T(v), 0, 0, 0},
            {0, T(v), 0, 0},
            {0, 0, T(v), 0},
            {0, 0, 0, T(v)}} {}

    template <arithmetic K>
    constexpr Matrix4(const K (&mat)[4][4]) noexcept
        : m{{T(mat[0][0]), T(mat[0][1]), T(mat[0][2]), T(mat[0][3])},
            {T(mat[1][0]), T(mat[1][1]), T(mat[1][2]), T(mat[1][3])},
            {T(mat[2][0]), T(mat[2][1]), T(mat[2][2]), T(mat[2][3])},
            {T(mat[3][0]), T(mat[3][1]), T(mat[3][2]), T(mat[3][3])}} {}

    template <arithmetic A, arithmetic B, arithmetic C, arithmetic D,
              arithmetic E, arithmetic F, arithmetic G, arithmetic H,
              arithmetic I, arithmetic J, arithmetic K, arithmetic L,
              arithmetic M, arithmetic N, arithmetic O, arithmetic P>
    constexpr Matrix4(A a, B b, C c, D d,
                      E e, F f, G g, H h,
                      I i, J j, K k, L l,
                      M m, N n, O o, P p) noexcept
        : m{{T(a), T(b), T(c), T(d)},
            {T(e), T(f), T(g), T(h)},
            {T(i), T(j), T(k), T(l)},
            {T(m), T(n), T(o), T(p)}} {}

    template <floating_point A, floating_point B,
              floating_point C, floating_point D>
    constexpr Matrix4(const Vector4<A> &a, const Vector4<B> &b,
                      const Vector4<C> &c, const Vector4<D> &d) noexcept
        : m{{T(a.x), T(a.y), T(a.z), T(a.w)},
            {T(b.x), T(b.y), T(b.z), T(b.w)},
            {T(c.x), T(c.y), T(c.z), T(c.w)},
            {T(d.x), T(d.y), T(d.z), T(d.w)}} {}

    template <floating_point K>
    constexpr explicit Matrix4(const Matrix2<K> &rhs) noexcept
        : m{{T(rhs[0][0]), T(rhs[0][1]), 0, 0},
            {T(rhs[1][0]), T(rhs[1][1]), 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}} {}

    template <floating_point K>
    constexpr explicit Matrix4(const Matrix3<K> &rhs) noexcept
        : m{{T(rhs[0][0]), T(rhs[0][1]), T(rhs[0][2]), 0},
            {T(rhs[1][0]), T(rhs[1][1]), T(rhs[1][2]), 0},
            {T(rhs[2][0]), T(rhs[2][1]), T(rhs[2][2]), 0},
            {0, 0, 0, 1}} {}

    template <floating_point K>
    constexpr Matrix4(const Matrix4<K> &rhs) noexcept
        : m{{T(rhs[0][0]), T(rhs[0][1]), T(rhs[0][2]), T(rhs[0][3])},
            {T(rhs[1][0]), T(rhs[1][1]), T(rhs[1][2]), T(rhs[1][3])},
            {T(rhs[2][0]), T(rhs[2][1]), T(rhs[2][2]), T(rhs[2][3])},
            {T(rhs[3][0]), T(rhs[3][1]), T(rhs[3][2]), T(rhs[3][3])}} {}

    ~Matrix4() = default;

    inline static constexpr Matrix4 zero{0}, identity{1};

    constexpr auto determinant() const noexcept
    {
        T r{};

        for (size_t j = 0; j < 4; ++j)
        {
            auto minor = get_submatrix(0, j).determinant();
            auto cof = ((j % 2 == 0) ? 1 : -1) * m[0][j] * minor;
            r += cof;
        }

        return r;
    }

    constexpr Matrix4 inverse() const noexcept
    {
        auto det = determinant();

        if (det == 0)
            return *this;

        Matrix4<T> r;

        for (size_t i = 0; i < 4; ++i)
        {
            for (size_t j = 0; j < 4; ++j)
            {
                auto minor = get_submatrix(i, j).determinant();
                auto cof = (((i + j) % 2) == 0 ? 1 : -1) * minor;
                r[j][i] = cof / det;
            }
        }

        return r;
    }

    constexpr Matrix4 transpose() const noexcept
    {
        Matrix4<T> r;

        for (size_t i = 0; i < 4; ++i)
            for (size_t j = 0; j < 4; ++j)
                r[i][j] = m[j][i];

        return r;
    }

    constexpr Matrix3<T> get_submatrix(size_t row, size_t col) const noexcept
    {
        Matrix3<T> r{};

        for (size_t i = 0, row_c = 0; i < 4; ++i)
        {
            if (i == row)
                continue;
            for (size_t j = 0, col_c = 0; j < 4; ++j)
            {
                if (j == col)
                    continue;
                r[row_c][col_c++] = m[i][j];
            }
            ++row_c;
        }

        return r;
    }

    template <floating_point K>
    static constexpr Matrix4<K> translation(const Vector3<K> &rhs) noexcept
    {
        Matrix4<K> r{identity};
        r[0][3] = rhs.x, r[1][3] = rhs.y, r[2][3] = rhs.z;
        return r;
    }

    template <floating_point K>
    constexpr Matrix4 translate(const Vector3<K> &rhs) const noexcept
    {
        return (*this * translation(rhs));
    }

    std::string to_string() const noexcept
    {
        return std::format("[({}, {}, {}, {}), ({}, {}, {}, {}), ({}, {}, {}, {}), ({}, {}, {}, {})]",
                           m[0][0], m[0][1], m[0][2], m[0][3],
                           m[1][0], m[1][1], m[1][2], m[1][3],
                           m[2][0], m[2][1], m[2][2], m[2][3],
                           m[3][0], m[3][1], m[3][2], m[3][3]);
    }

    constexpr T *operator[](size_t row) noexcept
    {
        assert(row < 4 && "Matrix4::[] : Index out of range");
        return m[row];
    }

    constexpr const T *operator[](size_t row) const noexcept
    {
        assert(row < 4 && "Matrix4::[] : Index out of range");
        return m[row];
    }

    template <floating_point K>
    constexpr Matrix4 &operator=(const Matrix4<K> &rhs) noexcept
    {
        if (this != &rhs)
            for (size_t i = 0; i < 4; ++i)
                for (size_t j = 0; j < 4; ++j)
                    m[i][j] = rhs[i][j];

        return *this;
    }

    template <floating_point K>
    constexpr Matrix4 operator+(const Matrix4<K> &rhs) const noexcept
    {
        Matrix4<T> r;

        for (size_t i = 0; i < 4; ++i)
            for (size_t j = 0; j < 4; ++j)
                r[i][j] = m[i][j] + rhs[i][j];

        return r;
    }

    template <floating_point K>
    constexpr Matrix4 &operator+=(const Matrix4<K> &rhs) noexcept
    {
        *this = *this + rhs;
        return *this;
    }

    constexpr Matrix4 operator-() const noexcept
    {
        return (*this * -1);
    }

    template <floating_point K>
    constexpr Matrix4 operator-(const Matrix4<K> &rhs) const noexcept
    {
        Matrix4<T> r;

        for (size_t i = 0; i < 4; ++i)
            for (size_t j = 0; j < 4; ++j)
                r[i][j] = m[i][j] - rhs[i][j];

        return r;
    }

    template <floating_point K>
    constexpr Matrix4 &operator-=(const Matrix4<K> &rhs) noexcept
    {
        *this = *this - rhs;
        return *this;
    }

    template <arithmetic A>
    constexpr Matrix4 operator*(A scalar) const noexcept
    {
        Matrix4<T> r;

        for (size_t i = 0; i < 4; ++i)
            for (size_t j = 0; j < 4; ++j)
                r[i][j] = m[i][j] * scalar;

        return r;
    }

    template <arithmetic A, floating_point K>
    friend constexpr Matrix4 operator*(A scalar, const Matrix4<K> &rhs) noexcept
    {
        return (rhs * scalar);
    }

    template <floating_point K>
    constexpr Matrix4 operator*(const Matrix4<K> &rhs) const noexcept
    {
        Matrix4<T> r{};

        for (size_t i = 0; i < 4; ++i)
            for (size_t j = 0; j < 4; ++j)
                for (size_t k = 0; k < 4; ++k)
                    r[i][j] += m[i][k] * rhs[k][j];

        return r;
    }

    template <floating_point K>
    constexpr Vector4<K> operator*(const Vector4<K> &rhs) const noexcept
    {
        Vector4<K> r{};

        for (size_t i = 0; i < 4; ++i)
            for (size_t j = 0; j < 4; ++j)
                r[i] += m[i][j] * rhs[j];

        return r;
    }

    template <arithmetic A>
    constexpr Matrix4 &operator*=(A scalar) noexcept
    {
        *this = *this * scalar;
        return *this;
    }

    template <floating_point K>
    constexpr Matrix4 &operator*=(const Matrix4<K> &rhs) noexcept
    {
        *this = *this * rhs;
        return *this;
    }

    template <arithmetic A>
    constexpr Matrix4 operator/(A scalar) const noexcept
    {
        return (*this * (1 / T(scalar)));
    }

    template <arithmetic A>
    constexpr Matrix4 &operator/=(A scalar) noexcept
    {
        *this = *this / scalar;
        return *this;
    }

    template <floating_point K>
    constexpr bool operator==(const Matrix4<K> &rhs) const noexcept
    {
        for (size_t i = 0; i < 4; ++i)
            for (size_t j = 0; j < 4; ++j)
                if (m[i][j] != rhs[i][j])
                    return false;

        return true;
    }

    template <floating_point K>
    constexpr bool operator!=(const Matrix4<K> &rhs) const noexcept
    {
        return !(*this == rhs);
    }
};

using Matrix4f = Matrix4<float>;
using Matrix4d = Matrix4<double>;
