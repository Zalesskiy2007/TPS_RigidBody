#include "mth/mth.h"

#define TimeBetweenFrames 0.02

class rigidbody
{
  /*
    =========TODO=========
    1) Creating RigidBody should be with shape (to set the I0)
    2) 'Vertex of shape should be created as if the CenterOfMass of this shape in (0,0,0) point'
        Is it correct?
    3) Make a posibility to create a rigidbody that consist of lot of shapes
      (find the I0 and maybe the CenterOfMass)
    4) Make sure that ' (!*!) ' is correct idea
       Or maybe just set that 2) is correct and let users set the shape as in 2)
  */
private:
  struct DataContext
  {
    float Mass;
    vec3 CenterOfMass; // <- (!*!)
    vec3 F;
    tensor I0;
    vec3 T;

    void Reset( void )
    {
      F = T = vec3(0, 0, 0);
    }
  } Context;

  struct DataX
  {
    vec3 C;
    tensor R;
    vec3 P;
    vec3 L;

    DataX operator+( const DataX &D )
    {
      DataX Result;

      Result.C = C + D.C;
      Result.P = P + D.P;
      Result.L = L + D.L;
      Result.R = R + D.R;

      return Result;
    }

    DataX operator*( float q )
    {
      DataX Result;

      Result.C = C * q;
      Result.P = P * q;
      Result.L = L * q;
      Result.R = R * q;

      return Result;
    }
  } X;

  struct DataOther
  {
    vec3 W;
    tensor I;

    void Calculate( DataX &D, DataContext &C )
    {
      I = (D.R * C.I0) * D.R.Transpose();
      W = I.Inverse() * D.L;
    }
  } Other;

  DataX DotFunc( DataX &Src )
  {
    DataX Xdot;

    Xdot.C = Src.P / Context.Mass;
    Xdot.R = tensor().Star(Other.W) * Src.R;
    Xdot.P = Context.F;
    Xdot.L = Context.T;

    return Xdot;
  }

  DataX MiddlePoint( double DeltaTime )
  {
    double dt = DeltaTime / 2.0;
    DataX Result;

    DataX K = X + (DotFunc(X) * dt);
    Result = X + (DotFunc(K) * DeltaTime);

    return Result;
  }

public:
  void AddForce( const vec3 &F )
  {
    Context.F += F;
  }

  void AddTorque( const vec3 &T )
  {
    Context.T += T;
  }

  void AddForceAtPosition( const vec3 &F, const vec3 &P )
  {
    vec3 T = (P - X.C) % F; // Cross product

    AddForce(F);
    AddTorque(T);
  }

  void SetMass( float NewM )
  {
    Context.Mass = NewM;
  }

  void SetCenterOfMass( const vec3 &NewC ) // <- (!*!)
  {
    Context.CenterOfMass = NewC;
  }

  void UpdatePhysic( void )
  {
    // X.C - Position, X.R - Rotation;
    // Here add P and L if have collision;

    Other.Calculate(X, Context);
    X = MiddlePoint(TimeBetweenFrames);
    Context.Reset();
  }

  matr GetPosition( void ) // or (tensor Get...)
  {
    return matr().Translate(X.C);
  }

  matr GetRotation( void ) // or (tensor Get...)
  {
    // return X.R * matr().Translate(Context.CenterOfMass).Inverse(); (or swap positions of X.R and Translate) 
    //                                     ^
    //                                     |
    //
    //                                   (!*!)

    return matr().Identity(); // !!TEMPORARY HOLDER!!
  }
};

int main( void )
{
  return 0;
}