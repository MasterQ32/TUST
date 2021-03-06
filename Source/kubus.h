#ifndef _KUBUS_H_
#define _KUBUS_H_

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/**
 * \defgroup  KubusSampleModule Kubus Example
 * \ingroup   ExampleModule
 * A small example for the kubus voxelizer system.
 *
 * \{
 * \include kubus.c
 * \}
 */
 #endif
 
 /**
 * \defgroup  KubusModule Kubus Voxelizer
 * \ingroup   GenericScriptLibrary
 * \brief     Provides functions to create levels based on voxels.
 *
 * Kubus is a complete system for voxel data visualization. It allows you to build levels out of small cubes,
 * every cube is textured and can store additional data.
 * 
 * In Kubus, a voxel is called block and is 16x16x16 quants large. A block contains two informations: The type of the
 * block and a pointer to user data.
 * The user data is a free to use pointer for additional game information. It can be read with \ref kubus_get_blockdata and
 * set with \ref kubus_set_blockdata.
 * The block type is a pointer to a structure defined by Kubus. It contains the texturing information as well as additional
 * block flags for transparency or a custom construction method.
 * A block type is defined like this:
 * \code{.cpp}
 * BlockType *blockGlas = 
 * {
 * 	textureTop = 96;
 * 	textureBottom = 96;
 * 	textureSide = 96;
 * 	flags = TRANSLUCENT; // We want our block to be transparent.
 * }
 * \endcode 
 * As you can see, the block type definition here contains the three necessary texture definitions as well as an additional
 * flag definition.
 * Textures in kubus are stored in an atlas map. The map needs to contain 16 slots in both directions. Kubus supports a max. of 
 * 256 textures at the moment caused by this restriction. The texture ID used in the block type definition is mapped to the texture
 * in this way:
 * \image html kubus_textures.png
 *
 * \{
 *
 * \file kubus.h
 * \brief Header of the kubus voxelizer.
 *
 * \file kubus.c
 * \brief Code of the kubus voxelizer.
 */

#ifndef CHUNK_COUNT_X
	/**
	 * \brief Defines the number of chunks in x-direction.
	 */
	#define CHUNK_COUNT_X 64
#endif
#ifndef CHUNK_COUNT_Y
	/**
	 * \brief Defines the number of chunks in y-direction.
	 */
	#define CHUNK_COUNT_Y 64
#endif
#ifndef CHUNK_COUNT_Z
	/**
	 * \brief Defines the number of chunks in z-direction.
	 */
	#define CHUNK_COUNT_Z 16
#endif

/**
 * \brief Block type description.
 * The block type descripton defines all parameters
 * of a block. It contains texture data and construction
 * flags.
 */
typedef struct 
{
	/**
	 * \brief Texture id of the top side of the block.
	 */
	int textureTop;
	
	/**
	 * \brief Texture id of the bottom side of the block.
	 */
	int textureBottom;
	
	/**
	 * \brief Texture id of the other sides of the block.
	 */
	int textureSide;
	
#ifdef DOXYGEN_SHOULD_SKIP_THIS
	/**
	 * \brief Pointer to a construction function.
	 *
	 * If this function pointer is non-NULL, Kubus uses the
	 * function to create the block instead of the internal
	 * block creation. This allows the creation of custom
	 * block shapes. Center of the created block is at (16 * x, 16 * y, 16 * z).
	 *
	 * \param model  The \ref DynamicModel that is used for this chunk. Add your custom faces to this model.
	 * \param type   The block type of the block that should be constructed.
	 * \param x      Local chunk coordinate of the block that should be created.
	 * \param y      Local chunk coordinate of the block that should be created.
	 * \param z      Local chunk coordinate of the block that should be created.
	 */
	void construct(DynamicModel *model, BlockType *type, int x, int y, int z);
#else
	void *construct;
#endif
	/**
	 * \brief Flags of the block type.
	 *
	 * If \ref TRANSLUCENT is set, the acts as a translucent block.
	 * The flag should be set if the block texture contains transparent parts.
	 */
	int flags;
	
	/**
	 * \brief ID of the block material.
	 *
	 * This value can be set as you like, it is thought for
	 * block material identifying via switch statement.
	 * More than one block type can share one ID.
	 */
	int ID;
} BlockType;

/**
 * \brief Initializes Kubus.
 * Initializes and sets up Kubus. All needed parameters are set.
 *
 * \remarks DMDLSettings.flags is set to 0 because Kubus uses DynamicModels and need this setting.
 */
void kubus_init(BMAP *texpack);

/**
 * \brief Updates chunks.
 * Updates all chunks in the view range around the camera.
 * kubus_update creates, removes and modifies chunk meshes.
 */
void kubus_update();

/**
 * \brief Gets the block type at a specific position.
 * \param  x The x position of the block.
 * \param  y The y position of the block.
 * \param  z The z position of the block.
 * \return   \ref BlockType at (x,y,z).
 */
BlockType *kubus_get_block(int x, int y, int z);

/**
 * \brief Sets teh block type at a specific position.
 * \param x         The x position of the block.
 * \param y         The y position of the block.
 * \param z         The z position of the block.
 * \param blockType The block type of the block.
 * 
 * \remarks         If blockType is NULL, the block will be empty.
 */
void kubus_set_block(int x, int y, int z, BlockType *blockType);

/**
 * \brief Gets the block data at a specific position.
 * Block data is a free-to-use pointer for free use.
 * \param  x The x position of the block.
 * \param  y The y position of the block.
 * \param  z The z position of the block.
 * \return   The block data at (x,y,z).
 */
void *kubus_get_blockdata(int x, int y, int z);

/**
 * \brief Sets the block data at a specific position.
 * Block data is a free-to-use pointer for free use.
 * \param  x    The x position of the block.
 * \param  y    The y position of the block.
 * \param  z    The z position of the block.
 * \param  data The block data at (x,y,z).
 */
void kubus_set_blockdata(int x, int y, int z, void *data);

/**
 * \brief Gets the block position after a c_trace call.
 * The function calculates the position of the block hit by
 * the last \ref c_trace call.
 * \return A temporary vector containing the (x,y,z) position of the block that was hit.
 *
 * \remarks Use \ref USE_POLYGON for the c_trace call to get correct results.
 * \remarks The vector returned is created by the lite-c function \ref vector.
 */
VECTOR *kubus_pos_from_hit(void);

/**
 * \brief Forces a refresh of all chunks.
 */
void kubus_force_refresh();

/**
 * \brief Sets the maximum view range in chunks.
 * \param range New view range of Kubus.
 */
void kubus_set_viewrange(int range);

/**
 * \brief Gets the maximum view range in chunks.
 * \return Current view range of Kubus.
 */
int kubus_get_viewrange();

#include "kubus.c"
#endif