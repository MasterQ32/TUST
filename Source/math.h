#ifndef _MATH_H_
#define _MATH_H_

/**
 * \file math.h
 * \brief Math helpers and other function
 * Provides math helpers and useful functions.
 */

#include "list.h"



#define PI 3.14159265

/**
 * \brief   Interpolates a single angle.
 * \param	a1	The first angle.
 * \param	a2	The second angle.
 * \param	f	The interpolation factor between a1 and a2.
 * \return		Interpolated angle.
 */
var ang_lerp_single(var a1, var a2, var f);

/**
 * \brief   Interpolates an euler angle.
 * \param	a1	The first angle.
 * \param	a2	The second angle.
 * \param	f	The interpolation factor between a1 and a2.
 * \return		Interpolated angle.
 */
ANGLE* ang_lerp(ANGLE* a, ANGLE* a1, ANGLE* a2, var f);

/**
 * \brief   Rotates a vector about an orthogonal axis.
 * \param   vec      The vector.
 * \param   angle    Angle of rotation
 */
void vec_rotateXY ( VECTOR *vec, var angle );

/**
 * \brief   Rotates a vector about an orthogonal axis.
 * \param   vec      The vector.
 * \param   angle    Angle of rotation
 */
void vec_rotateXZ ( VECTOR *vec, var angle );

/**
 * \brief   Rotates a vector about an orthogonal axis.
 * \param   vec      The vector.
 * \param   angle    Angle of rotation
 */
void vec_rotateYZ ( VECTOR *vec, var angle );

/**
 * \brief   Return the length of the XY components of a VECTOR
 * \param   vec      The vector.
 * \return  The length of the XY vector
 */
var vec_lengthXY ( VECTOR *vec );

/**
 * \brief   Return the length of the XZ components of a VECTOR
 * \param   vec      The vector.
 * \return  The length of the XZ vector
 */
var vec_lengthXZ ( VECTOR *vec );

/**
 * \brief   Return the length of the YZ components of a VECTOR
 * \param   vec      The vector.
 * \return  The length of the YZ vector
 */
var vec_lengthYZ ( VECTOR *vec );

/**
 * \brief   Sets the XY components of the vector vR to the difference of the XY components of v1 and v2.
 * \param   vR       The vector to be filled.
 * \param   v1       The first vector.
 * \param   v2       The second vector.
 */
void vec_diffXY ( VECTOR *vR, VECTOR *v1, VECTOR *v2 );

/**
 * \brief   Sets the XZ components of the vector vR to the difference of the XZ components of v1 and v2.
 * \param   vR       The vector to be filled.
 * \param   v1       The first vector.
 * \param   v2       The second vector.
 */
void vec_diffXZ ( VECTOR *vR, VECTOR *v1, VECTOR *v2 );

/**
 * \brief   Sets the YZ components of the vector vR to the difference of the YZ components of v1 and v2.
 * \param   vR       The vector to be filled.
 * \param   v1       The first vector.
 * \param   v2       The second vector.
 */
void vec_diffYZ ( VECTOR *vR, VECTOR *v1, VECTOR *v2 );

/**
 * \brief   Computes the distance in XY plane between two points.
 * \param   p1       The fisrt point.
 * \param   p2       The second point.
 * \return  The distance in XY plane between two points.
 */
var vec_distXY ( VECTOR *p1, VECTOR *p2 );

/**
 * \brief   Computes the distance in XZ plane between two points.
 * \param   p1       The fisrt point.
 * \param   p2       The second point.
 * \return  The distance in XZ plane between two points.
 */
var vec_distXZ ( VECTOR *p1, VECTOR *p2 );

/**
 * \brief   Computes the distance in YZ plane between two points.
 * \param   p1       The fisrt point.
 * \param   p2       The second point.
 * \return  The distance in YZ plane between two points.
 */
var vec_distYZ ( VECTOR *p1, VECTOR *p2 );

/**
 * \brief   Copies the XY components of the second vector to the first, thus overwriting the first vector. 
 * \param   v1       The fisrt vector.
 * \param   v2       The second vector.
 */
void vec_setXY ( VECTOR *v1, VECTOR *v2 );

/**
 * \brief   Copies the XZ components of the second vector to the first, thus overwriting the first vector. 
 * \param   v1       The fisrt vector.
 * \param   v2       The second vector.
 */
void vec_setXZ ( VECTOR *v1, VECTOR *v2 );

/**
 * \brief   Copies the YZ components of the second vector to the first, thus overwriting the first vector. 
 * \param   v1       The fisrt vector.
 * \param   v2       The second vector.
 */
void vec_setYZ ( VECTOR *v1, VECTOR *v2 );

/**
 * \brief   Adds the XY components of the second vector to the first. 
 * \param   v1       The fisrt vector.
 * \param   v2       The second vector.
 */
void vec_addXY ( VECTOR *v1, VECTOR *v2 );

/**
 * \brief   Adds the XZ components of the second vector to the first. 
 * \param   v1       The fisrt vector.
 * \param   v2       The second vector.
 */
void vec_addXZ ( VECTOR *v1, VECTOR *v2 );

/**
 * \brief   Adds the YZ components of the second vector to the first. 
 * \param   v1       The fisrt vector.
 * \param   v2       The second vector.
 */
void vec_addYZ ( VECTOR *v1, VECTOR *v2 );

/**
 * \brief   Substract the XY components of the second vector from the first. 
 * \param   v1       The fisrt vector.
 * \param   v2       The second vector.
 */
void vec_subXY ( VECTOR *v1, VECTOR *v2 );

/**
 * \brief   Substract the XZ components of the second vector from the first. 
 * \param   v1       The fisrt vector.
 * \param   v2       The second vector.
 */
void vec_subXZ ( VECTOR *v1, VECTOR *v2 );

/**
 * \brief   Substract the YZ components of the second vector from the first. 
 * \param   v1       The fisrt vector.
 * \param   v2       The second vector.
 */
void vec_subYZ ( VECTOR *v1, VECTOR *v2 );

/**
 * \brief   Scales the XY components of the vector to the magnitude given by length. 
 * \param   vec      The vector.
 * \param   length   The length.
 */
void vec_normalizeXY ( VECTOR *vec, var length );

/**
 * \brief   Scales the XZ components of the vector to the magnitude given by length. 
 * \param   vec      The vector.
 * \param   length   The length.
 */
void vec_normalizeXZ ( VECTOR *vec, var length );

/**
 * \brief   Scales the YZ components of the vector to the magnitude given by length. 
 * \param   vec      The vector.
 * \param   length   The length.
 */
void vec_normalizeYZ ( VECTOR *vec, var length );

/**
 * \brief   Scales the XY components of the vector by a factor. 
 * \param   vec      The vector.
 * \param   f        The length.
 */
void vec_scaleXY ( VECTOR *vec, var f );

/**
 * \brief   Scales the XZ components of the vector by a factor. 
 * \param   vec      The vector.
 * \param   f        The length.
 */
void vec_scaleXZ ( VECTOR *vec, var f );

/**
 * \brief   Scales the YZ components of the vector by a factor. 
 * \param   vec      The vector.
 * \param   f        The length.
 */
void vec_scaleYZ ( VECTOR *vec, var f );

/**
 * Gives the distance from a point to a line described by two other points
 * \param	px, py		Coords of the point
 * \param	l1x, l1y		Coords of a point in the line
 * \param	l2x, l2y		Coords of a different point in the line
 * \return					The distance to the line
 * 
 * WARNING! this function results in a division by zero when both line description points are same!
 */
var point_to_line2D_dist ( var px, var py, var l1x, var l1y, var l2x, var l2y );

/**
 * Gives the escalar of the orthogonal projection of a point over a vector described by two other points
 * \param	px, py		Coords of the point
 * \param	l1x, l1y		Coords of a point in the line
 * \param	l2x, l2y		Coords of a different point in the line
 * \return					The escalar of the projection to the line vector
 * 
 * WARNING! this function results in a division by zero when both line description points are same!
 */
var point_to_line2D_escalar ( var px, var py, var l1x, var l1y, var l2x, var l2y );


/**
 * Calculates a spline
 * \param	List*(VECTOR*)	Input points
 * \param	int				Details. Set how many VECTOR*s are returned
 * \return						List*(VECTOR*) of Points that make the spline more detailed
 * 
 */
List* calculate_spline(List* _points,  int _detail);

/**
 * Calculates a spline
 * \param	points      Input points
 * \param	pointcount  Number of points in points.
 * \param	pos         Interpolation position between 0 and 1.
 * \return	            Vector at pos.
 * 
 */
VECTOR* math_get_spline(VECTOR* points, int pointcount, float pos);


/**
 * Calculates a position on a bezier courve
 * \param	pos         Vector to store result in.
 * \param	points      Pointer to a vector array that stores all points for the bezier courve.
 * \param	count       Number of vectors in the points array.
 * \param	p           Interpolation factor, between 0 and 1.
 * \return	            Point on the bezier courve.
 */
VECTOR *vec_to_bezier(VECTOR *pos, VECTOR *points, int count, float p);


/**
 * Calculates a position on a catmull courve
 * \param	pos         Vector to store result in.
 * \param	points      Pointer to a vector array that stores all points for the bezier courve.
 * \param	count       Number of vectors in the points array.
 * \param	p           Interpolation factor, between 0 and 1.
 * \return	            Point on the catmull courve.
 */
VECTOR *vec_to_catmull(VECTOR *pos, VECTOR *v0, VECTOR *v1, VECTOR *v2, VECTOR *v3, float s);

/**
 * Compares 2 float values with a precision of %.2f
 * \param	_f1         First float
 * \param   _f2         Second float
 * \return	            "1" if _f1 > _f2, "-1" if _f2 > _f1, "0" if _f1 == _f2
 */
int float_cmp(float _f1, float _f2);

/**
 * \brief   Computes the world to custom coordinates tranformation matrix (matView)
 * \param   _matrix         Pointer to a float matrix to be filled 
 * \param   _vecPos         World position vector of the coordinate system
 * \param   _vecDir         World direction vector of the coordinate system
 */
void mat_eye ( float *_matrix, VECTOR *_vecPos, VECTOR *_vecDir );

#include "math.c"

#endif