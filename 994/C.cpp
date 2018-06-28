// C++ routines for computational geometry.

#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

double INF = 1e100;
double EPS = 1e-12;

struct PT {
    double x, y;
    PT() {}
    PT(double x, double y) : x(x), y(y) {}
    PT(const PT &p) : x(p.x), y(p.y) {}
    PT operator+(const PT &p) const { return PT(x + p.x, y + p.y); }
    PT operator-(const PT &p) const { return PT(x - p.x, y - p.y); }
    PT operator*(double c) const { return PT(x * c, y * c); }
    PT operator/(double c) const { return PT(x / c, y / c); }
};

double dot(PT p, PT q) { return p.x * q.x + p.y * q.y; }
double dist2(PT p, PT q) { return dot(p - q, p - q); }
double cross(PT p, PT q) { return p.x * q.y - p.y * q.x; }
ostream &operator<<(ostream &os, const PT &p) {
    return os << "(" << p.x << "," << p.y << ")";
}

// rotate a point CCW or CW around the origin
PT RotateCCW90(PT p) { return PT(-p.y, p.x); }
PT RotateCW90(PT p) { return PT(p.y, -p.x); }
PT RotateCCW(PT p, double t) {
    return PT(p.x * cos(t) - p.y * sin(t), p.x * sin(t) + p.y * cos(t));
}

// project point c onto line through a and b
// assuming a != b
PT ProjectPointLine(PT a, PT b, PT c) {
    return a + (b - a) * dot(c - a, b - a) / dot(b - a, b - a);
}

// project point c onto line segment through a and b
PT ProjectPointSegment(PT a, PT b, PT c) {
    double r = dot(b - a, b - a);
    if (fabs(r) < EPS) return a;
    r = dot(c - a, b - a) / r;
    if (r < 0) return a;
    if (r > 1) return b;
    return a + (b - a) * r;
}

// compute distance from c to segment between a and b
double DistancePointSegment(PT a, PT b, PT c) {
    return sqrt(dist2(c, ProjectPointSegment(a, b, c)));
}

// compute distance between point (x,y,z) and plane ax+by+cz=d
double DistancePointPlane(double x, double y, double z, double a, double b,
                          double c, double d) {
    return fabs(a * x + b * y + c * z - d) / sqrt(a * a + b * b + c * c);
}

// determine if lines from a to b and c to d are parallel or collinear
bool LinesParallel(PT a, PT b, PT c, PT d) {
    return fabs(cross(b - a, c - d)) < EPS;
}

bool LinesCollinear(PT a, PT b, PT c, PT d) {
    return LinesParallel(a, b, c, d) && fabs(cross(a - b, a - c)) < EPS &&
           fabs(cross(c - d, c - a)) < EPS;
}

// determine if line segment from a to b intersects with
// line segment from c to d
bool SegmentsIntersect(PT a, PT b, PT c, PT d) {
    if (LinesCollinear(a, b, c, d)) {
        if (dist2(a, c) < EPS || dist2(a, d) < EPS || dist2(b, c) < EPS ||
            dist2(b, d) < EPS)
            return true;
        if (dot(c - a, c - b) > 0 && dot(d - a, d - b) > 0 &&
            dot(c - b, d - b) > 0)
            return false;
        return true;
    }
    if (cross(d - a, b - a) * cross(c - a, b - a) > 0) return false;
    if (cross(a - c, d - c) * cross(b - c, d - c) > 0) return false;
    return true;
}

#include <bits/stdc++.h>
// #define LOCAL
#ifdef LOCAL
#define DEBUG(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define DEBUG(fmt, ...)
#endif

using namespace std;
#define szof(v) ((int)(v).size())
#define allof(v) begin(v), end(v)
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

ii sq1[4], sq2[4];

bool intersect() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (sq1[i] == sq2[j]) {
                return true;
            }
        }
    }

    for (int e1 = 0; e1 < 4; ++e1) {
        for (int e2 = 0; e2 < 4; ++e2) {
            // case 1 horizontal
            if (sq1[e1].second == sq1[(e1 + 1) % 4].second) {
                int boundy = sq1[e1].second;
                int x1 = sq2[e2].first, x2 = sq2[(e2 + 1) % 4].first;
                int y1 = sq2[e2].second, y2 = sq2[(e2 + 1) % 4].second;

                if (y1 > y2) {
                    swap(x1, x2);
                    swap(y1, y2);
                }

                if (y1 > boundy || y2 < boundy) {
                    continue;
                }

                int lox = min(sq1[e1].first, sq1[(e1 + 1) % 4].first);
                int hix = max(sq1[e1].first, sq1[(e1 + 1) % 4].first);

                if (x1 < x2) {
                    int h1 = boundy - y1;
                    int intx = x1 + h1;
                    if (lox <= intx && intx <= hix) {
                        return true;
                    }
                } else {
                    int h1 = boundy - y1;
                    int intx = x1 - h1;
                    if (lox <= intx && intx <= hix) {
                        return true;
                    }
                }

            } else {
                assert(sq1[e1].first == sq1[(e1 + 1) % 4].first);

                int boundx = sq1[e1].first;
                int x1 = sq2[e2].first, x2 = sq2[(e2 + 1) % 4].first;
                int y1 = sq2[e2].second, y2 = sq2[(e2 + 1) % 4].second;

                if (x1 > x2) {
                    swap(x1, x2);
                    swap(y1, y2);
                }

                if (x2 < boundx || x1 > boundx) {
                    continue;
                }

                int loy = min(sq1[e1].second, sq1[(e1 + 1) % 4].second);
                int hiy = max(sq1[e1].second, sq1[(e1 + 1) % 4].second);

                if (y1 < y2) {
                    int inty = y1 + boundx - x1;
                    if (loy <= inty && inty <= hiy) {
                        return true;
                    }
                } else {
                    int inty = y1 - (boundx - x1);
                    if (loy <= inty && inty <= hiy) {
                        return true;
                    }
                }
            }

            // PT p1 = PT(sq1[e1].first, sq1[e1].second);
            // PT p2 = PT(sq1[(e1 + 1) % 4].first, sq1[(e1 + 1) % 4].second);
            // PT p3 = PT(sq2[e2].first, sq2[e2].second);
            // PT p4 = PT(sq2[(e2 + 1) % 4].first, sq2[(e2 + 1) % 4].second);
            // if (SegmentsIntersect(p1, p2, p3, p4)) {
            //     return true;
            // }
        }
    }
    return false;
}

bool sq1_contains(ii p) {
    int lft = sq1[0].first;
    int rt = sq1[0].first;
    int tp = sq1[0].second;
    int btm = sq1[0].second;
    for (int i = 1; i < 4; ++i) {
        lft = min(lft, sq1[i].first);
        rt = max(rt, sq1[i].first);

        tp = max(tp, sq1[i].second);
        btm = min(btm, sq1[i].second);
    }

    return lft <= p.first && p.first <= rt && btm <= p.second && p.second <= tp;
}

bool sq2_contains(int x, int y) {
    int lft = sq2[0].first;
    int rt = sq2[0].first;
    int tp = sq2[0].second;
    int btm = sq2[0].second;
    for (int i = 1; i < 4; ++i) {
        lft = min(lft, sq2[i].first);
        rt = max(rt, sq2[i].first);

        tp = max(tp, sq2[i].second);
        btm = min(btm, sq2[i].second);
    }
    if (!(lft <= x && x <= rt && btm <= y && y <= tp)) {
        return false;
    }

    int midx = (lft+rt)/2;
    int midy = (btm+tp)/2;


    x -= midx;
    y -= midy;

    int s = (rt-lft)/2;
    if (x+y > s) {
        return false;
    }

    if (x+y < -s) {
        return false;
    }

    if (x-y > s) {
        return false;
    }

    if (x-y < -s) {
        return false;
    }

    return true;
}

void mmain() {
    for (int i = 0; i < 4; ++i) {
        scanf("%d%d", &sq1[i].first, &sq1[i].second);
    }
    for (int i = 0; i < 4; ++i) {
        scanf("%d%d", &sq2[i].first, &sq2[i].second);
    }

    if (intersect()) {
        printf("YES\n");
        return;
    }
    DEBUG("NO INTERSECTIONS\n");
    if (sq1_contains(sq2[0])) {
        printf("YES\n");
        return;
    }
    for (int i = 0; i < 4; ++i) {
        if (sq2_contains(sq1[i].first, sq1[i].second)) {
            printf("YES\n");
            return;
        }
    }
    printf("NO\n");
}

int main() {
#ifdef LOCAL
    clock_t begin = clock();
    printf("*********Starting program*********\n\n");
    freopen("data.txt", "r", stdin);
#endif
    mmain();
#ifdef LOCAL
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    printf("\nTime taken: %lf\n", elapsed_secs);
#endif
}