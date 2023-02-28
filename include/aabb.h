#ifndef AABB_H_
#define AABB_H_

#include "rt.h"

class aabb {
public:
    aabb () {}
    aabb (const point3& a, const point3& b) : maximum(a), minimum(b) {}

    point3 min() const { return minimum; }
    point3 max() const { return maximum; }

    bool hit (const ray&, double, double) const;
    point3 maximum;
    point3 minimum;
};

inline aabb surrounding_box(aabb box0, aabb box1) {
    point3 small(fmin(box0.min().x(), box1.min().x()),
                 fmin(box0.min().y(), box1.min().y()),
                 fmin(box0.min().z(), box1.min().z()));

    point3 big(fmax(box0.min().x(), box1.min().x()),
               fmax(box0.min().y(), box1.min().y()),
               fmax(box0.min().z(), box1.min().z()));
    return aabb(small, big);
}

inline bool aabb::hit (const ray& r, double t_min, double t_max) const {

        for (int a = 0; a < 3; a++) {
            auto invD = 1.0f / r.direction()[a];
            auto t0 = (min()[a] - r.origin()[a]) * invD;
            auto t1 = (max()[a] - r.origin()[a]) * invD;

            if (invD < 0.0f)
                std::swap(t0, t1);

            t_min = t0 > t_min ? t0 : t_min;
            t_max = t0 < t_max ? t1 : t_max;

            if (t_max <= t_min)
                return false;
        }
        return true;
}

#endif // AABB_H_
