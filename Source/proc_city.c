#ifndef _PROC_CITY_C_
#define _PROC_CITY_C_

// ----------------------------------------------------------------------------------------
// Street tool
// ----------------------------------------------------------------------------------------

Street *street_create(int _streetWidth, int _streetHeight)
{
	Street *street = sys_malloc(sizeof(Street));
	
	street->points = list_create();
	
	street->width = _streetWidth; // 320
	street->groundDist = 16;
	street->height = _streetHeight; // 48
	street->slopewidth = 3;
	street->segmentLength = 64;
	
	return street;
}

void street_remove(Street *street)
{
	list_clear_content (street->points, sys_free );
	list_delete(street->points);
	if(street->ent != NULL)
		ent_remove(street->ent);
	sys_free(street);
}

void street_addpos(Street *street, VECTOR *pos)
{
	VECTOR *vec = sys_malloc(sizeof(VECTOR));
	vec_set(vec, pos);
	list_add(street->points, vec);
}

var street_getground(Street *street, VECTOR *pos, VECTOR *offset, int mirror)
{
	var zStart = 0;
	var valset = 0;
	
	VECTOR left, right;
	vec_set(&left, pos);
	vec_add(&left, offset);
	vec_set(&right, pos);
	vec_sub(&right, offset);
	
	if(mirror < 0)
		vec_set(&left, &right);
	
	if(c_trace(	vector(left.x, left.y, left.z + 1024),
				vector(left.x, left.y, left.z - 1024),
				IGNORE_MODELS | IGNORE_SPRITES | IGNORE_PASSABLE | IGNORE_PASSENTS | USE_POLYGON))
	{
		zStart = target.z;
		valset = 1;
	}
	if(mirror > 0)
	{
		if(c_trace(	vector(right.x, right.y, right.z + 1024),
					vector(right.x, right.y, right.z - 1024),
					IGNORE_MODELS | IGNORE_SPRITES | IGNORE_PASSABLE | IGNORE_PASSENTS | USE_POLYGON))
		{
			if(valset)
				zStart = maxv(zStart, target.z);
			else
				zStart = target.z;
		}
	}
	return zStart;
}

int street_create_separator(DynamicModel *model, D3DVERTEX *left, D3DVERTEX *right)
{
	int index = model->vertexCount;
	
	memcpy(&model->vertexBuffer[index + 0], left, sizeof(D3DVERTEX));
	memcpy(&model->vertexBuffer[index + 1], right, sizeof(D3DVERTEX));
	
	model->vertexCount += 2;
	return index;
}

void street_create_segment(DynamicModel *model, int sep1, int sep2)
{
	int index = 3 * model->faceCount;
	
	model->indexBuffer[index + 0] = sep1 + 0;
	model->indexBuffer[index + 1] = sep2 + 0;
	model->indexBuffer[index + 2] = sep1 + 1;
	
	model->indexBuffer[index + 3] = sep1 + 1;
	model->indexBuffer[index + 4] = sep2 + 0;
	model->indexBuffer[index + 5] = sep2 + 1;
	
	model->faceCount += 2;
}

void street_build_median(D3DVERTEX *a, D3DVERTEX *b)
{
	b->x = 0.5 * (a->x + b->x); a->x = b->x;
	b->y = 0.5 * (a->y + b->y); a->y = b->y;
	b->z = 0.5 * (a->z + b->z); a->z = b->z;
	
	b->nx = 0.5 * (a->nx + b->nx); a->nx = b->nx;
	b->ny = 0.5 * (a->ny + b->ny); a->ny = b->ny;
	b->nz = 0.5 * (a->nz + b->nz); a->nz = b->nz;
	
	b->u1 = 0.5 * (a->u1 + b->u1); a->u1 = b->u1;
	b->u2 = 0.5 * (a->u2 + b->u2); a->u2 = b->u2;
}

ENTITY *street_build(Street *street, ENTITY* _terrain, BMAP* _streetTexture)
{
	int i, j, iPointCount;
	VECTOR center;
	
	iPointCount = list_get_count(street->points);
	
	ENTITY *entSpline = ent_create("", vector(0, 0, 0), NULL);
	
	path_create(entSpline, iPointCount, iPointCount);
	
	VECTOR **spline = sys_malloc(sizeof(VECTOR*) * iPointCount);
	list_copy_to(street->points, spline, iPointCount);
	
	vec_set(&center, vector(0, 0, 0));
	for(i = 0; i < iPointCount; i++)
	{
		vec_add(&center, spline[i]);
		path_setnode(entSpline, i + 1, spline[i], NULL);
	}
	vec_scale(&center, 1.0 / iPointCount);
	
	DynamicModel *model = dmdl_create();
	model->skin[0] = _streetTexture;
	
	DYNAMIC_QUAD quad;
	
	D3DVERTEX left;
	D3DVERTEX right;
	
	var isLooped = vec_dist(&spline[0], &spline[iPointCount-1]) < 0.1;
	
	var length = 10 * path_length(entSpline);
	var distance = 0;
	int previousSeparator = 0;
	
	for (distance = 0; distance < length; distance += street->segmentLength)
	{
		VECTOR startSegment, endSegment, dir;
		//vec_set(&startSegment, &spline[i]);
		path_spline(entSpline, &startSegment, distance);
		
		if(i < (iPointCount - 1) || 1)
		{
			path_spline(entSpline, &endSegment, distance + 10);
		}
		else
		{
			// For loop, just break out and connect first and last
			if(isLooped)
				break;
			else
			{
				// Take the last distance and reverse it
				vec_set(&endSegment, &spline[i - 1]);
				vec_diff(&dir, &endSegment, &startSegment);
				vec_inverse(&dir);
				vec_set(&endSegment, &startSegment);
				vec_add(&endSegment, &dir);
			}
		}
	
		vec_diff(&dir, &endSegment, &startSegment);
		dir.z = 0;
		vec_to_angle(&dir, &dir);
		
		VECTOR offset;
		vec_set(&offset, vector(0, 0.5 * street->width, 0));
		vec_rotate(&offset, &dir);

		var zStart = street_getground(street, &startSegment, &offset, 1);
		var zStartLeft = street_getground(street, vector(startSegment.x + offset.x, startSegment.y + offset.y, startSegment.z), vector(0, 0, 0), 0);
		var zStartRight = street_getground(street, vector(startSegment.x - offset.x, startSegment.y - offset.y, startSegment.z), vector(0, 0, 0), 0);
		zStart += street->groundDist;
		zStartLeft += street->groundDist;
		zStartRight += street->groundDist;

		// Lower start of street and end of street
		if(!isLooped)
		{
			if(i == 0 && j == 0)
			{
				zStart -= 1.5 * street->height;
			}
		}
		
		/************************************************************************************************/
		/*	Build Street Surface																		*/
		/************************************************************************************************/
		
		left.x = startSegment.x + offset.x;
		left.y = zStartLeft;
		left.z = startSegment.y + offset.y;
		left.nx = 0; left.ny = 1; left.nz = 0;
		left.u1 = 0;
		left.v1 = 0.001 * (distance);
		
		right.x = startSegment.x - offset.x;
		right.y = zStartRight;
		right.z = startSegment.y - offset.y;
		right.nx = 0; right.ny = 1; right.nz = 0;
		right.u1 = 1;
		right.v1 = 0.001 * (distance);
		
		// We got a start element AND not the first element
		if(j == 0 && i > 0)
		{
			//street_build_median(&left, &model->vertexBuffer[previousSeparator + 0]);
			//street_build_median(&right, &model->vertexBuffer[previousSeparator + 1]);
		}	
		
		int separator = street_create_separator(model, &left, &right);
		if(i > 0 && j > 0)
			street_create_segment(model, previousSeparator, separator);
		previousSeparator = separator;
	}
	
	// Connect to loop
	if(isLooped)
		street_create_segment(model, previousSeparator, 0);
	
	ENTITY *ent = dmdl_create_instance(model, vector(0, 0, 0), NULL);
	
	dmdl_delete(model);
	sys_free(spline);
	
	return ent;
}

#endif