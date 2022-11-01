/*
  David Vandensteen
  2018
*/
  // short  ->  2 bytes
  // word   ->  2 bytes
  // dword  ->  4 bytes
  // char   ->  1 byte
  // int    ->  4 bytes
  // byte   ->  1 byte


#ifndef NEOCORE_H
#define NEOCORE_H
#include <DATlib.h>
#include <math.h>

#define NEOCORE_INIT \
  typedef struct bkp_ram_info { \
    WORD debug_dips; \
    BYTE stuff[254]; \
  } bkp_ram_info; \
  bkp_ram_info bkp_data;

#define __ALIGN1__      __attribute__ ((aligned (1)))
#define __ALIGN2__      __attribute__ ((aligned (2)))
#define __ALIGN4__      __attribute__ ((aligned (4)))
#define __ALIGN64__     __attribute__ ((aligned (64)))
#define __ALIGN128__    __attribute__ ((aligned (128)))

#define MULT2              << 1
#define MULT4              << 2
#define MULT8              << 3
#define MULT16             << 4
#define MULT32             << 5
#define MULT64             << 6
#define DIV2               >> 1
#define DIV4               >> 2
#define DIV8               >> 3
#define DIV16              >> 4
#define DIV32              >> 5
#define DIV64              >> 6

#define Y_OFFSCREEN 240
#define X 0
#define Y 1

#define SHRUNK_TABLE_PROP_SIZE    0x2fe

#define JOYPAD            BYTE p1, ps;
#define JOYPAD_READ       p1 = volMEMBYTE(P1_CURRENT); ps = volMEMBYTE(PS_CURRENT);
#define JOYPAD_READ_EDGE  p1 = volMEMBYTE(P1_EDGE); ps = volMEMBYTE(PS_EDGE);
#define JOYPAD_IS_UP      p1&JOY_UP
#define JOYPAD_IS_DOWN    p1&JOY_DOWN
#define JOYPAD_IS_LEFT    p1&JOY_LEFT
#define JOYPAD_IS_RIGHT   p1&JOY_RIGHT
#define JOYPAD_IS_START   ps&P1_START
#define JOYPAD_IS_A       p1&JOY_A
#define JOYPAD_IS_B       p1&JOY_B
#define JOYPAD_IS_C       p1&JOY_C
#define JOYPAD_IS_D       p1&JOY_D

#define LOGGER_ON
#define LOGGER_X_INIT   1
#define LOGGER_Y_INIT   2

#define BOXCOPY(bFrom, bTo)   memcpy(bTo, bFrom, sizeof(Box))

#define FIX(value) value * 65536
#define RAND(value) rand() % value

#define SHRUNK_EXTRACT_X(value) value >> 8
#define SHRUNK_EXTRACT_Y(value) (BYTE)value

#define SPRITE_INDEX_MANAGER_MAX  384
#define PALETTE_INDEX_MANAGER_MAX 256

#define MANUALBOX 0
#define AUTOBOX 1

enum direction { NONE, UP, DOWN, LEFT, RIGHT };

/**
 * \struct Vec2int
 * \brief content x & y int coordinate
 */
typedef struct Vec2int Vec2int;
struct Vec2int {
  int x;
  int y;
};

/**
 * \struct Vec2short
 * \brief content x & y short coordinate
 */
typedef struct Vec2short Vec2short;
struct Vec2short {
  short x;
  short y;
};

/**
 * \struct Vec2byte
 * \brief content x & y byte coordinate
 */
typedef struct Vec2byte Vec2byte;
struct Vec2byte {
  BYTE x;
  BYTE y;
};

/**
 * \struct Box
 * \brief collider definition
 * * can be init by box_make constructor
 * - 4 vector short points (x, y)
 * - Width & height of the box
 * - Offset for reducing the box
 */
typedef struct Box Box;
struct Box {
  Vec2short p0;       /*!< coordinate 0 of the box (x, y) */
  Vec2short p1;       /*!< coordinate 1 of the box (x, y) */
  Vec2short p2;       /*!< coordinate 2 of the box (x, y) */
  Vec2short p3;       /*!< coordinate 3 of the box (x, y) */
  Vec2short p4;       /*!< coordinate 4 of the box (x, y) */
  short width;        /*!< width of the box */
  short height;       /*!< height of the box */
  short widthOffset;  /*!< width box reducing */
  short heightOffset; /*!< height box reducing */
};

/**
 * \struct Flash
 * \brief
 * - frequency
 * - lengh
 * - visible
 * - enabled
 */
typedef struct Flash Flash;
struct Flash {
  WORD frequency;
  short lengh;
  BOOL visible;
  BOOL enabled;
};

/**
 * \struct GFX_Animated_Sprite
 * \brief DATLib aSprite structure encapsulation
 */
typedef struct GFX_Animated_Sprite GFX_Animated_Sprite;
struct GFX_Animated_Sprite {
  aSprite as;         /*!< - as is aSprite DATLib definition */
  spriteInfo *si;     /*!< - si is a pointer to DATLib spriteInfo structure */
  paletteInfo *pali;  /*!< - pali is a pointer to DATLib paletteInfo structure */
  Flash flash;        /*!< - Flash */
};

/**
 * \struct GFX_Image
 * \brief DATLib picture structure encapsulation
 */
typedef struct GFX_Image GFX_Image;
struct GFX_Image {
  picture pic;        /*!< - pic is picture DATLib definition */
  pictureInfo *pi;    /*!< - pi is a pointer to DATLib pictureInfo structure */
  paletteInfo *pali;  /*!< - pali is a pointer to DATLib paletteInfo structure */
  Flash flash;        /*!< - Flash */
};

/**
 * \struct GFX_Animated_Sprite_Physic
 * \brief GFX_Animated_Sprite encapsulation with Box
 *
 *  GFX_Animated_Sprite_Physic can be collide with another Box structure
 */
typedef struct GFX_Animated_Sprite_Physic GFX_Animated_Sprite_Physic;
struct GFX_Animated_Sprite_Physic {
  GFX_Animated_Sprite gfx_animated_sprite;  /*!< - GFX_Animated_Sprite */
  Box box;                          /*!< - Box */
  BOOL physic_enabled;              /*!< - enable physic (for collide detection capalities) */
};

/**
 * \struct GFX_Image_Physic
 * \brief GFX_Image encapsulation with Box
 *
 *  GFX_Image_Physic can be collide with another Box structure
 */
typedef struct GFX_Image_Physic GFX_Image_Physic;
struct GFX_Image_Physic {
  GFX_Image gfx_image;  /*!< - GFX_Image */
  Box box;              /*!< - Box */
  BOOL autobox_enabled; /*!< - enable autobox */
  BOOL physic_enabled;  /*!< - enable physic (for collide detection capabilities) */
};

/**
 * \struct GFX_Scroller
 * \brief DATLib scroller structure encapsulation
 */
typedef struct GFX_Scroller GFX_Scroller;
struct GFX_Scroller {
  scroller s;          /*!< - s is a pointer to DATLib scroller struture */
  scrollerInfo *si;    /*!< - si is a pointer to DATLib scrollerInfo structure */
  paletteInfo *pali;   /*!< - pali is a pointer to DATLib paletteInfo structure */
};

  //--------------------------------------------------------------------------//
 //                                  -B                                      //
//--------------------------------------------------------------------------//
/**
 * \brief check if a box is colliding with a box list
 * @param Box* Box pointer
 * @param Box* Box list pointer
 * @param box_max Box quantity
 * \return BYTE the box id collider or 0
 */
BYTE boxes_collide(Box *b, Box *boxes[], BYTE box_max);

/**
 * \brief check if two box is colliding
 * @param Box* box1 pointer
 * @param Box* box2 pointer
 * \return BOOL
 */
BOOL box_collide(Box *b1, Box *b2);

/**
 * @param Box* Box pointer
 * @param width
 * @param height
 * @param width_offset width Box reduce
 * @param height_offset height Box reduce
 */
void box_init(Box *b, short width, short height, short widthOffset, short heightOffset);

/**
 * \brief refresh Box position
 * @param Box* Box pointer
 * @param x
 * @param y
 */
void box_update(Box *b, short x, short y);
// void box_debug_update(picture5 *pics, Box *box); // todo (minor)
// void box_display(picture5 *pics, Box *box, pictureInfo *pi, paletteInfo *pali); // todo (minor)

/**
 *
 */

// todo (minor)
void box_shrunk(Box *b, Box *bOrigin, WORD shrunkValue);
// todo (minor) - deprecated ?
void box_resize(Box *Box, short edge); // todo (minor) - deprecated ?

  //--------------------------------------------------------------------------//
 //                                  -C                                      //
//--------------------------------------------------------------------------//
/**
 *  \brief VRAM Clear
 */
void inline clear_vram();

/**
 * \brief clear sprite index table
 */
void clear_sprite_index_table();

/**
 * \brief clear palette inde table
 */
void clear_palette_index_table();

/**
 * \brief Play CD Audio Track
 * @param track
 */
void cdda_play(BYTE track);

  //--------------------------------------------------------------------------//
 //                                  -F                                      //
//--------------------------------------------------------------------------//
/**
 * @param x
 * @param y
 * @param label
 */
void inline fix_print_neocore(int x, int y, char *label);

/**
 * @param Flash* Flash pointer
 * @param enabled
 * @param frequency
 * @param lengh
 */
void flash_init(Flash *flash, BOOL enabled, short frequency, short lengh);

/**
 * \brief return estimated free RAM
 */
WORD free_ram_info();


  //--------------------------------------------------------------------------//
 //                                  -G                                      //
//--------------------------------------------------------------------------//

  /*----------------------*/
 /*      -gfx_image      */
/*----------------------*/
/**
 * @param GFX_Image* GFX_Image pointer
 * @param pictureInfo* pointer to DATLib structure
 * @param paletteInfo* pointer to DATLib structure
 */
void gfx_image_init(GFX_Image *gfx_image, pictureInfo *pi, paletteInfo *pali);

/**
 * @param GFX_Image* GFX_Image pointer
 * @param x
 * @param y
 */
void gfx_image_display(GFX_Image *gfx_image, short x, short y);

/**
 * @param GFX_Image* GFX_Image pointer
 * @param x offset
 * @param y offset
 */
#define gfx_image_move(gfx_image, x_offset, y_offset) pictureMove(gfx_image.pic, x_offset, y_offset)

/**
 * @param GFX_Image* GFX_Image pointer
 * @param x
 * @param y
 */
void gfx_image_set_position(GFX_Image *gfx_image, short x, short y);

/**
 * \brief hide GFX_Image
 * @param GFX_Image* GFX_Image pointer
 */
void gfx_image_hide(GFX_Image *gfx_image);

/**
 * \brief show GFX_Image
 * @param GFX_Image* GFX_Image pointer
 */
void gfx_image_show(GFX_Image *gfx_image);

/**
 * @param GFX_Image* GFX_Image pointer
 * \return BOOL true if GFX_Image is visible or false
 */
void gfx_image_is_visible(GFX_Image *gfx_image);

/**
 * @param GFX_Image* GFX_Image pointer
 */
BOOL gfx_image_flash(GFX_Image *gfx_image);

/**
 * @param GFX_Image* GFX_Image pointer
 * @param x center position
 * @param y center position
 * @param shrunk use shrunk_forge function for make a WORD with width & heigh value
 */
void gfx_image_shrunk_centroid(GFX_Image *gfx_image, short center_x, short center_y, WORD shrunk_value);

/**
 * \brief GFX_Image destroy
 * @param GFX_Image* GFX_Image pointer
 */
void gfx_image_destroy(GFX_Image *gfx_image);

  /*----------------------*/
 /*  -gfx_image_physic   */
/*----------------------*/
/**
 * @param GFX_Image_Physic* GFX_Image_Physic pointer
 * @param pictureInfo* pointer to DATLib structure
 * @param paletteInfo* pointer to DATLib structure
 * @param width Box width
 * @param height Box height
 * @param width_offset Box offset reduce
 * @param height_offset Box offset reduce
 */
void gfx_image_physic_init(
  GFX_Image_Physic *gfx_image_physic,
  pictureInfo *pi,
  paletteInfo *pali,
  short box_witdh,
  short box_height,
  short box_width_offset,
  short box_height_offset,
  BOOL autobox_enabled
);

/**
 * @param GFX_Image_Physic* pointer
 * @param x
 * @param y
 */
void gfx_image_physic_display(GFX_Image_Physic *gfx_image_physic, short x, short y);

/**
 * @param GFX_Image_Physic* pointer
 * @param x offset
 * @param y offset
 */
void gfx_image_physic_move(GFX_Image_Physic *gfx_image_physic, short x_offset, short y_offset);

/**
 * @param GFX_Image_Physic* pointer
 * @param x
 * @param y
 */
void gfx_image_physic_set_position(GFX_Image_Physic *gfx_image_physic, short x, short y);

/**
 * \brief Hide Image_Physic & disable physic
 * @param GFX_Image_Physic* Pointer
 */
void gfx_image_physic_hide(GFX_Image_Physic *gfx_image_physic);

/**
 * \brief Show GFX_Image_Physic & enable physic
 * @param GFX_Image_Physic Pointer
 */
void gfx_image_physic_show(GFX_Image_Physic *gfx_image_physic);

/**
 * @param GFX_Image_Physic* Pointer
 */
void gfx_image_physic_flash(GFX_Image_Physic *gfx_image_physic);

/**
 * @param GFX_Image_Physic* pointer
 * @param shrunk Factor
 */
void gfx_image_physic_shrunk(GFX_Image_Physic *gfx_image_physic, WORD shrunk_value); // todo (minor) - shrunk box

/* todo (minor) - deprecated
void image_physic_shrunk_centroid_init(picturePhysicShrunkCentroid *pps, pictureInfo *pi, paletteInfo *pali, short xCenter, short yCenter);
void image_physic_shrunk_centroid_set_position(picturePhysicShrunkCentroid *pps, short x, short y);
void image_physic_shrunk_centroid_move(picturePhysicShrunkCentroid *pps, short xShift, short yShift);
void image_physic_shrunk_centroid_update(picturePhysicShrunkCentroid *pps, WORD shrunk);
void image_physic_shrunk_centroid_display(picturePhysicShrunkCentroid *pps, WORD shrunk);
void image_physic_display(picturePhysic *pp, pictureInfo *pi, paletteInfo *pali, short posX, short posY);
void image_physic_set_position(picturePhysic *pp, short x, short y);
void image_physic_move(picturePhysic *pp, short x, short y);
void image_shrunk(picture *p, pictureInfo *pi, WORD shrunk_value);
void images_show(picture *p, WORD max, BOOL visible);
void image5_show(picture5 *pics, BOOL visible);
void image_display(picture *p, pictureInfo *pi, paletteInfo *pali, short posX, short posY);
void image_shrunk_centroid(picture *p, pictureInfo *pi, short centerPosX, short centerPosY, WORD shrunk_value);
void image_flash(picture *p, BYTE freq);
WORD image_get_sprite_index_autoinc(pictureInfo *pi);
*/

/**
 * \brief destroy Image_Physic
 * @param GFX_Image_Physic pointer
 */
void gfx_image_physic_destroy(GFX_Image_Physic *gfx_image_physic);

  /*----------------------*/
 /* -gfx_animated_sprite */
/*----------------------*/
/**
 * @param GFX_Animated_Sprite_Physic* GFX_Animated_Sprite_Physic pointer
 * @param paletteInfo* pointer to DATLib structure
 * @param witdh of the physic box
 * @param height of the physic box
 * @param width offset to reduce physic box
 * @param height offset to reduce physic box
 */
void gfx_animated_sprite_physic_init(
  GFX_Animated_Sprite_Physic *gfx_animated_sprite_physic,
  spriteInfo *si,
  paletteInfo *pali,
  short box_witdh,
  short box_height,
  short box_width_offset,
  short box_height_offset
);

/**
 * @param GFX_Animated_Sprite* GFX_Animated_Sprite pointer
 * @param spriteInfo* spriteInfo pointer to DATLib structure
 * @param paletteInfo* paletteInfo pointer to DATLib structure
 */
void gfx_animated_sprite_init(GFX_Animated_Sprite *gfx_animated_sprite ,spriteInfo *si, paletteInfo *pali);

/**
 * @param GFX_Animated_Sprite* GFX_Animated_Sprite pointer
 * @param x position
 * @param y position
 * @param anim DATLib macro
 */
void gfx_animated_sprite_display(GFX_Animated_Sprite *gfx_animated_sprite, short x, short y, WORD anim);

/**
 * @param GFX_Animated_Sprite* GFX_Animated_Sprite pointer
 * @param x offset
 * @param y offset
 */
#define gfx_animated_sprite_move(gfx_animated_sprite, x_offset, y_offset) aSpriteMove(gfx_animated_sprite.as, x_offset, y_offset)

/**
 * @param GFX_Animated_Sprite* GFX_Animated_Sprite pointer
 * @param x
 * @param y
 */
#define gfx_animated_sprite_set_position(gfx_animated_sprite, x, y) aSpriteSetPos(gfx_animated_sprite.as, x, y)

/**
 * @param GFX_Animated_Sprite* GFX_Animated_Sprite pointer
 */
void gfx_animated_sprite_hide(GFX_Animated_Sprite *gfx_animated_sprite);

/**
 * @param GFX_Animated_Sprite* GFX_Animated_Sprite pointer
 */
void gfx_animated_sprite_show(GFX_Animated_Sprite *gfx_animated_sprite);

/**
 * @param GFX_Animated_Sprite* GFX_Animated_Sprite pointer
 * @param anim DATLib macro
 */
void gfx_animated_sprite_set_animation(GFX_Animated_Sprite *gfx_animated_sprite, WORD anim);

/**
 * \brief refresh animation frame
 * @param GFX_Animated_Sprite* GFX_Animated_Sprite pointer
 */
#define gfx_animated_sprite_animate(gfx_animated_sprite) aSpriteAnimate(gfx_animated_sprite.as)

/**
 * \brief refresh animation frame
 * @param GFX_Animated_Sprite_Physic* GFX_Animated_Sprite_Physic pointer
 */
#define gfx_animated_sprite_physic_animate(gfx_animated_sprite_physic) gfx_animated_sprite_animate(gfx_animated_sprite_physic.gfx_animated_sprite)

/**
 * \brief refresh flash
 * @param GFX_Animated_Sprite* GFX_Animated_Sprite pointer
 * \return BOOL
 */
BOOL gfx_animated_sprite_flash(GFX_Animated_Sprite *gfx_animated_sprite);

/**
 * \brief destroy animated sprite
 * @param GFX_Animated_Sprite* GFX_Animated_Sprite pointer
 * \return void
*/
void gfx_animated_sprite_destroy(GFX_Animated_Sprite *gfx_animated_sprite);

  /*------------------------------*/
 /* -gfx_animated_sprite_physic  */
/*------------------------------*/
/**
 * @param GFX_Animated_Sprite_Physic* GFXAnimated_Sprite_Physic pointer
 * @param x
 * @param y
 * @param anim DATLib macro
 */
void gfx_animated_sprite_physic_display(GFX_Animated_Sprite_Physic *gfx_animated_sprite_physic, short x, short y, WORD anim);
// void animated_sprite_physic_collide(aSpritePhysic *asp, Box *box); // todo - not implementd ??? needed ???

/**
 * @param GFX_Animated_Sprite_Physic* GFX_Animated_Sprite_Physic pointer
 * @param x
 * @param y
 */
void gfx_animated_sprite_physic_set_position(GFX_Animated_Sprite_Physic *gfx_animated_sprite_physic, short x, short y);

/**
 * @param GFX_Animated_Sprite_Physic* GFX_Animated_Sprite_Physic pointer
 * @param x offset
 * @param y offset
 */
void gfx_animated_sprite_physic_move(GFX_Animated_Sprite_Physic *gfx_animated_sprite_physic, short x_offset, short y_offset);

/**
 * @param GFX_Animated_Sprite_Physic* GFX_Animated_Sprite_Physic pointer
 * @param shrunk use shrunk_forge function for make a WORD with width & heigh value
 */
void gfx_animated_sprite_physic_shrunk(GFX_Animated_Sprite_Physic *gfx_animated_sprite_physic, WORD shrunk_value); // todo (minor)

/**
 * \brief hide a GFX_Animated_Sprite_Physic
 * @param GFX_Animated_Sprite_Physic* GFX_Animated_Sprite_Physic pointer
 */
void gfx_animated_sprite_physic_hide(GFX_Animated_Sprite_Physic *gfx_animated_sprite_physic);

/**
 * \brief show a GFX_Animated_Sprite_Physic
 * @param GFX_Animated_Sprite_Physic* GFX_Animated_Sprite_Physic pointer
 */
void gfx_animated_sprite_physic_show(GFX_Animated_Sprite_Physic *gfx_animated_sprite_physic);

/**
 * \brief refresh a GFX_Animated_Sprite_Physic flash
 * @param GFX_Animated_Sprite_Physic* GFX_Animated_Sprite_Physic pointer
 */
void gfx_animated_sprite_physic_flash(GFX_Animated_Sprite_Physic *gfx_animated_sprite_physic);

/**
 * \brief destroy GFX_Animated_Sprite_Physic
 * @param GFX_Animated_Sprite_Physic* GFX_Animated_Sprite_Physic pointer
 */
void gfx_animated_sprite_physic_destroy(GFX_Animated_Sprite_Physic *gfx_animated_sprite_physic);

/**
 * \brief init gpu
 */
void inline gpu_init();

/**
 * @param index
 * \return WORD a proportionnal value (shrink x, y) from an index of precalculated table
 */
WORD        get_shrunk_proportional_table(WORD index);

/**
 * @param index
 */
char        get_sin(WORD index);

/**
 * \brief return max free sprite index
 * \return WORD
 */
WORD        get_max_free_sprite_index();

/**
 * \brief return max sprite index used
 * \return WORD
 */
WORD        get_max_sprite_index_used();

/**
 * \brief return max free palette index
 * \return WORD
 */
WORD      get_max_free_palette_index();

/**
 * \brief return max palette index used
 * \return WORD
 */
 WORD     get_max_palette_index_used();

/**
 * \brief return picture info from GFX_Image
 * @param GFX_Image struct GFX_Image
 * \return struct
*/
#define get_gfx_image_pictureInfo(gfx_image) gfx_image.pi

/**
 * \brief return palette info from GFX_Image
 * @param GFX_Image struct GFX_Image
 * \return struct
*/
#define get_gfx_image_paletteInfo(gfx_image) gfx_image.pali

/**
 * \brief return baseSprite from GFX_Image
 * @param GFX_Image struct GFX_Image
 * \return WORD
*/
#define get_gfx_image_baseSprite(gfx_image) gfx_image.pic.baseSprite

/**
 * \brief return tileWitdh from GFX_Image
 * @param GFX_Image struct GFX_Image
 * \return WORD
*/
#define get_gfx_image_tileWidth(gfx_image) gfx_image.pic.info->tileWidth

/**
 * \brief return posX from GFX_Image
 * @param GFX_Image struct GFX_Image
 * \return short
*/
#define get_gfx_image_position_x(gfx_image) gfx_image.pic.posX

/**
 * \brief return posY from GFX_Image
 * @param GFX_Image struct GFX_Image
 * \return short
*/
#define get_gfx_image_position_y(gfx_image) gfx_image.pic.posY

  //--------------------------------------------------------------------------//
 //                                  -I                                      //
//--------------------------------------------------------------------------//
/**
 * @param Flash* Flash pointer
 * \return BOOL
 */
BOOL is_visible(Flash *flash);




  //--------------------------------------------------------------------------//
 //                                  -J                                      //
//--------------------------------------------------------------------------//
  /*----------*/
 /* -joypad  */
/*----------*/
void        joypad_update();
void        joypad_update_edge();
BOOL        joypad_is_up();
BOOL        joypad_is_down();
BOOL        joypad_is_left();
BOOL        joypad_is_right();
BOOL        joypad_is_start();
BOOL        joypad_is_a();
BOOL        joypad_is_b();
BOOL        joypad_is_c();
BOOL        joypad_is_d();
void inline joypad_debug();

  //--------------------------------------------------------------------------//
 //                                  -L                                       //
//--------------------------------------------------------------------------//
  /*----------*/
 /* -logger  */
/*----------*/
void        logger_init();
void        logger_set_position(WORD _x, WORD _y);
WORD inline logger_info(char *txt);
void inline logger_word(char *label, WORD value);
void inline logger_int(char *label, int value);
void inline logger_dword(char *label, DWORD value);
void inline logger_short(char *label, short value);
void inline logger_byte(char *label, BYTE value);
void inline logger_bool(char *label, BOOL value);
void inline logger_animated_sprite(char *label, GFX_Animated_Sprite *gfx_animated_sprite);
void inline logger_spriteInfo(char *label, spriteInfo *si);
void inline logger_box(char *label, Box *b);
void inline logger_pictureInfo(char *label, pictureInfo *pi);

  //--------------------------------------------------------------------------//
 //                                  -P                                      //
//--------------------------------------------------------------------------//
/**
 * \brief palette destroy
 * @param paletteInfo*
 */
void palette_destroy(paletteInfo* pi);

  //--------------------------------------------------------------------------//
 //                                  -M                                      //
//--------------------------------------------------------------------------//
//void mask_display(picture pic[], Vec2short vec[], BYTE vector_max); // todo (minor) - rename ? (vectorsDisplay)
void mask_update(short x, short y, Vec2short vec[], Vec2short offset[], BYTE vector_max); // todo (minor) - rename ? (vectorsDebug)
// todo (minor) - hardcode point\dot asset

  //--------------------------------------------------------------------------//
 //                                  -V                                      //
//--------------------------------------------------------------------------//
/**
 * \brief init a Vec2int structure
 * @param Vect2int* Pointer
 * @param x
 * @param y
 */
void vec2int_init(Vec2int *vec, int x, int y);

/**
 * \brief init a Vec2short structure
 * @param Vect2short* Pointer
 * @param x
 * @param y
 */
void vec2short_init(Vec2short *vec, short x, short y);

/**
 * \brief init a Vec2byte structure
 * @param Vect2byte* Pointer
 * @param x
 * @param y
 */
void vec2byte_init(Vec2byte *vec, BYTE x, BYTE y);

/**
 * @param Box* Pointer
 * @param Vec2short[] List
 * @param max Quantity list
 */
BOOL vectors_collide(Box *box, Vec2short vec[], BYTE vector_max);

/**
 * @param x Coord 1
 * @param y Coord 1
 * @param x Coord 2
 * @param y Coord 2
 * @param x Coord 3
 * @param y Coord 3
 */
BOOL vector_is_left(short x, short y, short v1x, short v1y, short v2x, short v2y);

  //--------------------------------------------------------------------------//
 //                                  -S                                      //
//--------------------------------------------------------------------------//
  /*---------------*/
 /* -gfx_scroller */
/*---------------*/
/**
 * @param GFX_Scroller* Pointer
 * @param scrollerInfo* Pointer to DATLib structure
 * @param paletteInfo* Pointer to DATLib structure
 */
void        gfx_scroller_init(GFX_Scroller *s, scrollerInfo *si, paletteInfo *pali);

/**
 * @param GFX_Scroller* Pointer
 * @param x
 * @param y
 */
void        gfx_scroller_display(GFX_Scroller *s, short x, short y);

/**
 * @param GFX_Scroller* Pointer
 * @param x offset
 * @param y offset
 */
void        gfx_scroller_move(GFX_Scroller *s, short x, short y);

/**
 * @param GFX_Scroller* Pointer
 * @param x
 * @param y
 */
void        gfx_scroller_set_position(GFX_Scroller *s, short x, short y);

/**
 * \brief GFX_Scroller destroy
 * @param GFX_Scroller* pointer
 */
void       gfx_scroller_destroy(GFX_Scroller *s);

  /*-----------*/
 /* -shrunk   */
/*-----------*/
/**
 * @param x Center position
 * @param y Center position
 * @param width Tile width
 * @param shrunkX Shrunk width factor
 * \return int
 */
int         shrunk_centroid_get_translated_x(short centerPosX, WORD tileWidth, BYTE shrunkX);

/**
 * @param x Center position
 * @param y Center position
 * @param width Tile width
 * @param shrunkY Shrunk height factor
 * \return int
 */
int         shrunk_centroid_get_translated_y(short centerPosY, WORD tileHeight, BYTE shrunkY);

/**
 * @param index Base sprite index
 * @param width Shrunk width factor
 * @param value
 */
void        shrunk(WORD base_sprite, WORD max_width, WORD value);

/**
 * @param x Shrunk width factor
 * @param y Shrunk height factor
 * \return WORD
 */
WORD        shrunk_forge(BYTE xc, BYTE yc);

/**
 * @param addr
 * @param value Shrunk factor
 */
void inline shrunk_addr(WORD addr, WORD shrunk_value);

/**
 * @param addr Address start
 * @param addr Adress end
 * @param value Shrunk factor
 */
WORD        shrunk_range(WORD addr_start, WORD addr_end, WORD shrunk_value);

  //--------------------------------------------------------------------------//
 //                                  -W                                      //
//--------------------------------------------------------------------------//
/**
 * @param vbl Number of frames to wait
 */
DWORD inline wait_vbl_max(WORD nb);
#define wait_vbl(); waitVBlank();

#endif
