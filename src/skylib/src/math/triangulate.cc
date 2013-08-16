#include <skylib/math/triangulate.h>
#include <skylib/math/definitions.h>

namespace skylib {

bool Triangulate::Process(std::vector< Vector<2> > const& face,
                          std::vector< std::vector< Vector<2> > >& result) {
  int n = face.size();
  if (n < 3) {
    return false;
  }

  int *V = new int[n];

  if (Area(face) > 0.0f) {
    for (int v = 0; v < n; v++) {
      V[v] = v;
    }
  } else {
    for (int v = 0; v < n; v++) {
      V[v] = (n - 1) - v;
    }
  }

  int nv = n;
  int count = 2 * nv;

  for (int m = 0, v = nv - 1; nv > 2;) {
    if (0 >= (count--)) {
      return false;
    }

    int u = v;
    if (nv <= u) {
      u = 0;
    }

    v = u + 1;
    if (nv <= v) {
      v = 0;
    }

    int w = v + 1;
    if (nv <= w) {
      w = 0;
    }

    if (Snip(face, u, v, w, nv, V)) {
      int a;
      int b;
      int c;
      int s;
      int t;

      a = V[u];
      b = V[v];
      c = V[w];

      std::vector< Vector<2> > triangle;
      triangle.push_back(face[a]);
      triangle.push_back(face[b]);
      triangle.push_back(face[c]);

      result.push_back(triangle);

      m++;

      for (s = v, t = v + 1; t < nv; s++, t++) {
        V[s] = V[t];
      }

      nv--;

      count = 2 * nv;
    }
  }

  delete V;

  return true;
}

float Triangulate::Area(std::vector< Vector<2> > const& face) {
  int n = face.size();
  float A = 0.0f;

  for (int p = n - 1, q = 0; q < n; p = q++) {
    float face_p_x = face[p].At(0);
    float face_p_y = face[p].At(1);
    float face_q_x = face[q].At(0);
    float face_q_y = face[q].At(1);

    A += face_p_x * face_q_y - face_q_x * face_p_y;
  }

  return A * 0.5f;
}

bool Triangulate::InsideTriangle(std::vector< Vector<2> > const& face,
                                 Vector<2> const& point) {
  if (face.size() != 3) {
    return false;
  }

  float Ax = face[0].At(0);
  float Ay = face[0].At(1);
  float Bx = face[1].At(0);
  float By = face[1].At(1);
  float Cx = face[2].At(0);
  float Cy = face[2].At(1);
  float Px = point.At(0);
  float Py = point.At(1);

  float ax = Cx - Bx;
  float ay = Cy - By;
  float bx = Ax - Cx;
  float by = Ay - Cy;
  float cx = Bx - Ax;
  float cy = By - Ay;
  float apx = Px - Ax;
  float apy = Py - Ay;
  float bpx = Px - Bx;
  float bpy = Py - By;
  float cpx = Px - Cx;
  float cpy = Py - Cy;
  float a_cross_bp = ax * bpy - ay * bpx;
  float b_cross_cp = bx * cpy - by * cpx;
  float c_cross_ap = cx * apy - cy * apx;

  if (a_cross_bp >= 0.0f && b_cross_cp >= 0.0f && c_cross_ap >= 0.0f) {
    return true;
  }

  return false;
}

bool Triangulate::Snip(std::vector< Vector<2> > const& face, int u, int v,
                       int w, int n, int *V) {
  float Ax = face[V[u]].At(0);
  float Ay = face[V[u]].At(1);
  float Bx = face[V[v]].At(0);
  float By = face[V[v]].At(1);
  float Cx = face[V[w]].At(0);
  float Cy = face[V[w]].At(1);

  if ((((Bx - Ax) * (Cy - Ay)) - ((By - Ay) * (Cx - Ax))) < kFloatEpsilon) {
    return false;
  }

  for (int p = 0; p < n; p++) {
    if (p == u || p == v || p == w) {
      continue;
    }

    float Px = face[V[p]].At(0);
    float Py = face[V[p]].At(1);

    Vector<2> point;
    point.At(0) = Px;
    point.At(1) = Py;

    std::vector< Vector<2> > triangle;
    Vector<2> vertex;
    vertex.At(0) = Ax;
    vertex.At(1) = Ay;
    triangle.push_back(vertex);
    vertex.At(0) = Bx;
    vertex.At(1) = By;
    triangle.push_back(vertex);
    vertex.At(0) = Cx;
    vertex.At(1) = Cy;
    triangle.push_back(vertex);

    if (InsideTriangle(triangle, point)) {
      return false;
    }
  }

  return true;
}

}
