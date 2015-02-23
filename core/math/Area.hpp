#ifndef __HEADER_SN_MATH_AREA__
#define __HEADER_SN_MATH_AREA__

#include <core/math/Vector.hpp>

namespace sn
{

template <typename T, unsigned int N>
class Area
{
public:
    //-----------------------------
    static Area fromPositionSize(const T x_, const T y_, const T w_, const T h_)
    {
        return Area(x_, y_, w_, h_);
    }

    //-----------------------------
    static Area fromPositionSize(const T x_, const T y_, const T z_, const T w_, const T h_, const T d_)
    {
        return Area(x_, y_, z_, w_, h_, d_);
    }

    //-----------------------------
    static Area fromMinMax(T minX, T minY, T maxX, T maxY)
    {
        SN_STATIC_ASSERT(N == 2);
        if (minX > maxX)
        {
            T temp = maxX;
            maxX = minX;
            minX = temp;
        }
        if (minY > maxY)
        {
            T temp = maxY;
            maxY = minY;
            minY = temp;
        }
        return Area(minX, minY, maxX - minX, maxY - minY);
    }

    //-----------------------------
    static Area fromMinMax(T minX, T minY, T minZ, T maxX, T maxY, T maxZ)
    {
        SN_STATIC_ASSERT(N == 3);
        if (minX > maxX)
        {
            T temp = maxX;
            maxX = minX;
            minX = temp;
        }
        if (minY > maxY)
        {
            T temp = maxY;
            maxY = minY;
            minY = temp;
        }
        if (minZ > maxZ)
        {
            T temp = maxZ;
            maxZ = minZ;
            minZ = temp;
        }
        return Area(minX, minY, minZ, maxX - minX, maxY - minY, maxZ - minZ);
    }

    //-----------------------------
    Area() {}

    //-----------------------------
    Area(T px, T py, T width, T height) :
        m_origin(px, py),
        m_size(width, height)
    {}

    //-----------------------------
    Area(T px, T py, T pz, T width, T height, T depth) :
        m_origin(px, py, pz),
        m_size(width, height, depth)
    {}

    //-----------------------------
    bool contains(T px, T py)
    {
        SN_STATIC_ASSERT(N >= 2);
        return px >= x() 
            && py >= y() 
            && px < x() + width() 
            && py < y() + height();
    }

    //-----------------------------
    bool contains(T px, T py, T pz)
    {
        SN_STATIC_ASSERT(N == 3);
        return px >= x() 
            && py >= y() 
            && pz >= z() 
            && px < x() + width() 
            && py < y + height() 
            && pz < z + depth();
    }

    //-----------------------------
    bool intersects(const Area<T, 2> & other) const
    {
        SN_STATIC_ASSERT(N >= 2);
        return maxX() >= other.minX()
            && maxY() >= other.minY() 
            && minX() <= other.maxX() 
            && minY() <= other.maxY();
    }

    //-----------------------------
    bool intersects(const Area<T, 3> & other) const
    {
        SN_STATIC_ASSERT(N == 3);
        return maxX() >= other.minX()
            && maxY() >= other.minY()
            && maxZ() >= other.minZ()
            && minX() <= other.maxX()
            && minY() <= other.maxY()
            && minZ() <= other.maxZ();
    }

    //-----------------------------
    bool intersectsQuad(const T px, const T py, const T ps) const
    {
        SN_STATIC_ASSERT(N >= 2);
        return maxX() >= px
            && maxY() >= py 
            && minX() <= px + ps 
            && minY() <= py + ps;
    }

    //-----------------------------
    bool intersectsQuad(const T px, const T py, const T pz, const T ps) const
    {
        SN_STATIC_ASSERT(N >= 3);
        return maxX() >= px
            && maxY() >= py
            && maxZ() >= py
            && minX() <= px + ps
            && minY() <= px + ps
            && minZ() <= py + ps;
    }

    //-----------------------------
    void addPoint(const T px, const T py)
    {
        SN_STATIC_ASSERT(N >= 2);

        if (px < m_origin.x()) m_origin.x() = px;
        if (py < m_origin.y()) m_origin.y() = py;

        if (px - m_origin.x() >= m_size.x()) m_size.x() = px - m_origin.x();
        if (py - m_origin.y() >= m_size.y()) m_size.y() = py - m_origin.y();
    }

    //-----------------------------
    void addPoint(const T px, const T py, const T pz)
    {
        SN_STATIC_ASSERT(N >= 3);
        
        if (px < m_origin.x()) m_origin.x() = px;
        if (py < m_origin.y()) m_origin.y() = py;
        if (pz < m_origin.z()) m_origin.z() = pz;

        if (px - m_origin.x() >= m_size.x()) m_size.x() = px - m_origin.x();
        if (py - m_origin.y() >= m_size.y()) m_size.y() = py - m_origin.y();
        if (pz - m_origin.z() >= m_size.z()) m_size.z() = pz - m_origin.z();
    }

    //-----------------------------
    std::string toString() const
    {
        std::stringstream ss;
        ss << "(origin=" << sn::toString(m_origin) << ", size=" << sn::toString(m_size) << ")";
        return ss.str();
    }

    //-----------------------------
    Vector<T, N> & origin() const { return m_origin; }
    Vector<T, N> & size() const { return m_size; }

    //-----------------------------
    Vector<T, N> getMin() const { return m_origin; }
    Vector<T, N> getMax() const { return m_origin + m_size; }

    //-----------------------------
    T & x() { SN_STATIC_ASSERT(N >= 1); return m_origin.x(); }
    T & y() { SN_STATIC_ASSERT(N >= 2); return m_origin.y(); }
    T & z() { SN_STATIC_ASSERT(N >= 3); return m_origin.z(); }

    //-----------------------------
    const T & x() const { SN_STATIC_ASSERT(N >= 1); return m_origin.x(); }
    const T & y() const { SN_STATIC_ASSERT(N >= 2); return m_origin.y(); }
    const T & z() const { SN_STATIC_ASSERT(N >= 3); return m_origin.z(); }

    //-----------------------------
    T & width()  { SN_STATIC_ASSERT(N >= 1); return m_size.x(); }
    T & height() { SN_STATIC_ASSERT(N >= 2); return m_size.y(); }
    T & depth()  { SN_STATIC_ASSERT(N >= 3); return m_size.z(); }

    //-----------------------------
    const T & width()  const { SN_STATIC_ASSERT(N >= 1); return m_size.x(); }
    const T & height() const { SN_STATIC_ASSERT(N >= 2); return m_size.y(); }
    const T & depth()  const { SN_STATIC_ASSERT(N >= 3); return m_size.z(); }

    //-----------------------------
    T minX() const { SN_STATIC_ASSERT(N >= 1); return m_origin.x(); }
    T minY() const { SN_STATIC_ASSERT(N >= 2); return m_origin.y(); }
    T minZ() const { SN_STATIC_ASSERT(N >= 3); return m_origin.z(); }

    //-----------------------------
    T maxX() const { SN_STATIC_ASSERT(N >= 1); return m_origin.x() + m_size.x(); }
    T maxY() const { SN_STATIC_ASSERT(N >= 2); return m_origin.y() + m_size.y(); }
    T maxZ() const { SN_STATIC_ASSERT(N >= 3); return m_origin.z() + m_size.z(); }

private:
    Vector<T, N> m_origin;
    Vector<T, N> m_size;

};

//template <typename T>
//bool operator!=(const TRect<T> & a, const TRect<T> & b)
//{
//    return a.x != b.x
//        && a.y != b.y
//        && a.width != b.width
//        && a.height != b.height;
//}

typedef Area<s32, 3> IntAABB;
typedef Area<f32, 3> FloatAABB;

} // namespace sn

#endif // __HEADER_SN_MATH_AREA__
