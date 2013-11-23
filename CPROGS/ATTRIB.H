/*attrib.h     video attributes for use with the usrlibs library */


/* attributes that have meaning in MS-DOS */
#define NORMAL_VID          0x07
#define HIGH_INTENSITY_VID  0x0F
#define REVERSE_VID         0x70
#define BLINK_BIT           0x80
#define BLNK_NORMAL_VID     (NORMAL_VID ^ BLINK_BIT)

/* internal flags for use by usrlibs */
#define SINGLE_LINE          1
#define DOUBLE_LINE          2

