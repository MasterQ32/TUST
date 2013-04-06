#ifndef _MATH_H_
#define _MATH_H_

/**
 * \file math.h
 * Provides math helpers and useful functions.
 */

/**
 * Interpolates a single angle.
 * \param	a1	The first angle.
 * \param	a2	The second angle.
 * \param	f	The interpolation factor between a1 and a2.
 * \return		Interpolated angle.
 */
var ang_lerp_single(var a1, var a2, var f);

/**
 * Interpolates an euler angle.
 * \param	a1	The first angle.
 * \param	a2	The second angle.
 * \param	f	The interpolation factor between a1 and a2.
 * \return		Interpolated angle.
 */
ANGLE* ang_lerp(ANGLE* a, ANGLE* a1, ANGLE* a2, var f);

/**
 * Rotates a vector about an orthogonal axis.
 * \param	vec		The vector.
 * \param	angle		Angle of rotation
 */
void vec_rotateXY ( VECTOR *vec, var angle );
void vec_rotateXZ ( VECTOR *vec, var angle );
void vec_rotateYZ ( VECTOR *vec, var angle );

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

#include "math.c"
#endif