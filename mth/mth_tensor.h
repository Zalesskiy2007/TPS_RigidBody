/* FILE NAME   : mth_tensor.h
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 01.09.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Math module.
 *               3D math tensor implementation module.
 */

#ifndef __mth_tensor_h_
#define __mth_tensor_h_

#include "mth_def.h"

 /* Pi math constant */
#define PI 3.14159265358979323846

/* Degrees to radians conversion */
#define D2R(A) ((A) * (PI / 180.0))
#define Degree2Radian(a) D2R(a)

/* Radians to degrees conversion */
#define R2D(A) ((A) * (180.0 / PI))
#define Radian2Degree(a) R2D(a)

/* Math namespace */
namespace mth
{
  /* tensor representation type */
  template<typename Type>
  class tensor
  {
    template<typename Type1>
    friend class camera;
  public:
    Type A[3][3]; // tensor elements

  public:
    /* tensor default constructor */
    tensor(void)
    {
    }
    /* tensor constructor by 16 elements */
    tensor(Type A00, Type A01, Type A02,
      Type A10, Type A11, Type A12,
      Type A20, Type A21, Type A22)
    {
      A[0][0] = A00;
      A[0][1] = A01;
      A[0][2] = A02;
      A[1][0] = A10;
      A[1][1] = A11;
      A[1][2] = A12;
      A[2][0] = A20;
      A[2][1] = A21;
      A[2][2] = A22;
    } /* End of 'tensor' constructor */

    /* tensor constructor by array */
    tensor(Type a[3][3])
    {
      A[0][0] = a[0][0];
      A[0][1] = a[0][1];
      A[0][2] = a[0][2];
      A[1][0] = a[1][0];
      A[1][1] = a[1][1];
      A[1][2] = a[1][2];
      A[2][0] = a[2][0];
      A[2][1] = a[2][1];
      A[2][2] = a[2][2];
    } /* End of 'tensor' constructor */

    /* Multiply two tensores function.
     * ARGUMENTS:
     *   - reference to second tensor:
     *       tensor &A;
     * RETURNS:
     *   (tensor) result new tensor.
     */
    tensor operator*(const tensor<Type>& M) const
    {
      tensor<Type> r = Identity();
      r.A[0][0] = r.A[1][1] = r.A[2][2] = 0;
      int i, j, k;

      for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
          for (r.A[i][j] = 0, k = 0; k < 3; k++)
            r.A[i][j] += A[i][k] * M.A[k][j];

      return r;
    } /* End of 'operator*' function */

    vec3<Type> operator*( const vec3<Type> &V ) const
    {
      return vec3<Type>(V[0] * A[0][0] + V[1] * A[1][0] + V[2] * A[2][0],
                        V[0] * A[0][1] + V[1] * A[1][1] + V[2] * A[2][1],
                        V[0] * A[0][2] + V[1] * A[1][2] + V[2] * A[2][2]);
    }

    tensor<Type> operator+( const tensor<Type> &T ) const
    {
      return tensor<Type>(A[0][0] + T.A[0][0], A[0][1] + T.A[0][1], A[0][2] + T.A[0][2],
                          A[1][0] + T.A[1][0], A[1][1] + T.A[1][1], A[1][2] + T.A[1][2],
                          A[2][0] + T.A[2][0], A[2][1] + T.A[2][1], A[2][2] + T.A[2][2]);
    }

    tensor<Type> operator*( Type T ) const
    {
      return tensor<Type>(A[0][0] * T, A[0][1] * T, A[0][2] * T,
                          A[1][0] * T, A[1][1] * T, A[1][2] * T,
                          A[2][0] * T, A[2][1] * T, A[2][2] * T);
    }

    tensor<Type> Star( vec3<Type> &W )
    {
      return tensor<Type>(0, -W[2], W[1],
                          W[2], 0, -W[0],
                          -W[1], W[0], 0);
    }
    /* Get determ of 3x3 tensor function.
     * ARGUMENTS:
     *   - tensor elements:
     *       Type &A11, Type &A12, Type &A13,
     *       Type &A21, Type &A22, Type &A23,
     *       Type &A31, Type &A32, Type &A33;
     * RETURNS:
     *   (Type) result of operation.
     */
    Type GetDeterm3x3(Type A11, Type A12, Type A13,
      Type A21, Type A22, Type A23,
      Type A31, Type A32, Type A33) const
    {
      return A11 * A22 * A33 + A12 * A23 * A31 + A13 * A21 * A32 -
        A11 * A23 * A32 - A12 * A21 * A33 - A13 * A22 * A31;
    } /* End of 'GetDeterm3x3' function */

    /* Get determ of 4x4 tensor function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (Type) result of operation.
     */
    Type operator!(VOID) const
    {
      return GetDeterm3x3(A[0][0], A[0][1], A[0][2],
                          A[1][0], A[1][1], A[1][2],
                          A[2][0], A[2][1], A[2][2]);
    } /* End of 'operator!' function */

    /* Get identity tensor function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (tensor) result new tensor.
     */
    inline tensor<Type> Identity(VOID) const
    {
      return tensor<Type>(1, 0, 0,
                    0, 1, 0,
                    0, 0, 1);
    } /* End of 'Identity' function */

    /* Get inverse tensor function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (tensor) result new tensor.
     */
    tensor<Type> Inverse(VOID) const
    {
      Type det = !*this;
      tensor M;

      if (det == 0)
        return Identity();

      //TODO MAKE!!!

      return Identity();//return M;
    } /* End of 'Inverse' function */


    /* Get transpose tensor function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (tensor) result new tensor.
     */
    inline tensor<Type> Transpose(VOID) const
    {
      tensor<Type> M;

      for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
          M.A[i][j] = A[j][i];
      return M;
    } /* End of 'Transpose' function */
  }; /* End of 'tensor' class */
} /* end of 'mth' namespace */

#endif /* __mth_tensor_h_ */

/* END OF 'mth_tensor.h' FILE */