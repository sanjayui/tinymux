/*! \file stringutil.h
 * \brief string utilities.
 *
 * $Id$
 *
 */

#ifndef STRINGUTIL_H
#define STRINGUTIL_H

#define mux_strlen(x)   strlen((const char *)x)

inline bool isEmpty(const UTF8 *p)
{
    return ((NULL == p) || ('\0' == p[0]));
}

extern const bool mux_isprint_ascii[256];
extern const bool mux_isprint_latin1[256];
extern const bool mux_isdigit[256];
extern const bool mux_isxdigit[256];
extern const bool mux_isazAZ[256];
extern const bool mux_isalpha[256];
extern const bool mux_isalnum[256];
extern const bool mux_islower_ascii[256];
extern const bool mux_isupper_ascii[256];
extern const bool mux_isspace[256];
extern const bool mux_issecure[256];
extern const bool mux_isescape[256];
extern const unsigned char mux_hex2dec[256];
extern const unsigned char mux_toupper_ascii[256];
extern const unsigned char mux_tolower_ascii[256];
extern const UTF8 TableATOI[16][10];

#define UTF8_SIZE1     1
#define UTF8_SIZE2     2
#define UTF8_SIZE3     3
#define UTF8_SIZE4     4
#define UTF8_CONTINUE  5
#define UTF8_ILLEGAL   6
extern const unsigned char utf8_FirstByte[256];
extern const UTF8 *latin1_utf8[256];
#define latin1_utf8(x) ((const UTF8 *)latin1_utf8[(unsigned char)x])

// This function trims the string back to the first valid UTF-8 sequence it
// finds, but it does not validate the entire string.
//
extern const int g_trimoffset[4][4];
inline size_t TrimPartialSequence(size_t n, const UTF8 *p)
{
    for (size_t i = 0; i < n; i++)
    {
        int j = utf8_FirstByte[p[n-i-1]];
        if (j < UTF8_CONTINUE)
        {
            if (i < 4)
            {
                return n - g_trimoffset[i][j-1];
            }
            else
            {
                return n - i + j - 1;
            }
        }
    }
    return 0;
}

#define mux_isprint_ascii(x) (mux_isprint_ascii[(unsigned char)(x)])
#define mux_isprint_latin1(x) (mux_isprint_latin1[(unsigned char)(x)])
#define mux_isdigit(x) (mux_isdigit[(unsigned char)(x)])
#define mux_isxdigit(x)(mux_isxdigit[(unsigned char)(x)])
#define mux_isazAZ(x)  (mux_isazAZ[(unsigned char)(x)])
#define mux_isalpha(x) (mux_isazAZ[(unsigned char)(x)])
#define mux_isalnum(x) (mux_isalnum[(unsigned char)(x)])
#define mux_islower_ascii(x) (mux_islower_ascii[(unsigned char)(x)])
#define mux_isupper_ascii(x) (mux_isupper_ascii[(unsigned char)(x)])
#define mux_isspace(x) (mux_isspace[(unsigned char)(x)])
#define mux_hex2dec(x) (mux_hex2dec[(unsigned char)(x)])
#define mux_toupper_ascii(x) (mux_toupper_ascii[(unsigned char)(x)])
#define mux_tolower_ascii(x) (mux_tolower_ascii[(unsigned char)(x)])
#define TableATOI(x,y) (TableATOI[(unsigned char)(x)][(unsigned char)(y)])

#define mux_issecure(x)           (mux_issecure[(unsigned char)(x)])
#define mux_isescape(x)           (mux_isescape[(unsigned char)(x)])

#define UNI_EOF ((UTF32)-1)

#define UNI_REPLACEMENT_CHAR ((UTF32)0x0000FFFDUL)
#define UNI_MAX_BMP          ((UTF32)0x0000FFFFUL)
#define UNI_MAX_UTF16        ((UTF32)0x0010FFFFUL)
#define UNI_MAX_UTF32        ((UTF32)0x7FFFFFFFUL)
#define UNI_MAX_LEGAL_UTF32  ((UTF32)0x0010FFFFUL)
#define UNI_SUR_HIGH_START   ((UTF32)0x0000D800UL)
#define UNI_SUR_HIGH_END     ((UTF32)0x0000DBFFUL)
#define UNI_SUR_LOW_START    ((UTF32)0x0000DC00UL)
#define UNI_SUR_LOW_END      ((UTF32)0x0000DFFFUL)
#define UNI_PU1_START        ((UTF32)0x0000E000UL)
#define UNI_PU1_END          ((UTF32)0x0000F8FFUL)
#define UNI_PU2_START        ((UTF32)0x000F0000UL)
#define UNI_PU2_END          ((UTF32)0x000FFFFDUL)
#define UNI_PU3_START        ((UTF32)0x00100000UL)
#define UNI_PU3_END          ((UTF32)0x0010FFFDUL)

#define utf8_NextCodePoint(x)      (x + utf8_FirstByte[(unsigned char)*x])

typedef struct
{
    size_t n_bytes;
    size_t n_points;
    const UTF8 *p;
} string_desc;

// Beginning of Unicode Table Definitions.
//

// utf/cl_Printable.txt
//
// 100312 included, 1013800 excluded, 0 errors.
// 198 states, 95 columns, 19066 bytes
//
#define CL_PRINT_START_STATE (0)
#define CL_PRINT_ACCEPTING_STATES_START (198)
extern const unsigned char cl_print_itt[256];
extern const unsigned char cl_print_stt[198][95];

// utf/cl_AttrNameInitial.txt
//
// 177 included, 1113935 excluded, 0 errors.
// 6 states, 14 columns, 340 bytes
//
#define CL_ATTRNAMEINITIAL_START_STATE (0)
#define CL_ATTRNAMEINITIAL_ACCEPTING_STATES_START (6)
extern const unsigned char cl_attrnameinitial_itt[256];
extern const unsigned char cl_attrnameinitial_stt[6][14];

// utf/cl_AttrName.txt
//
// 203 included, 1113909 excluded, 0 errors.
// 6 states, 14 columns, 340 bytes
//
#define CL_ATTRNAME_START_STATE (0)
#define CL_ATTRNAME_ACCEPTING_STATES_START (6)
extern const unsigned char cl_attrname_itt[256];
extern const unsigned char cl_attrname_stt[6][14];

// utf/cl_ObjectName.txt
//
// 257 included, 1113855 excluded, 0 errors.
// 8 states, 23 columns, 440 bytes
//
#define CL_OBJECTNAME_START_STATE (0)
#define CL_OBJECTNAME_ACCEPTING_STATES_START (8)
extern const unsigned char cl_objectname_itt[256];
extern const unsigned char cl_objectname_stt[8][23];

// utf/cl_PlayerName.txt
//
// 190 included, 1113922 excluded, 0 errors.
// 6 states, 14 columns, 340 bytes
//
#define CL_PLAYERNAME_START_STATE (0)
#define CL_PLAYERNAME_ACCEPTING_STATES_START (6)
extern const unsigned char cl_playername_itt[256];
extern const unsigned char cl_playername_stt[6][14];

// utf/cl_8859_1.txt
//
// 191 included, 1113921 excluded, 0 errors.
// 3 states, 6 columns, 274 bytes
//
#define CL_8859_1_START_STATE (0)
#define CL_8859_1_ACCEPTING_STATES_START (3)
extern const unsigned char cl_8859_1_itt[256];
extern const unsigned char cl_8859_1_stt[3][6];

// utf/cl_8859_2.txt
//
// 191 included, 1113921 excluded, 0 errors.
// 6 states, 21 columns, 382 bytes
//
#define CL_8859_2_START_STATE (0)
#define CL_8859_2_ACCEPTING_STATES_START (6)
extern const unsigned char cl_8859_2_itt[256];
extern const unsigned char cl_8859_2_stt[6][21];

// utf/tr_utf8_latin1.txt
//
// 2461 code points.
// 97 states, 193 columns, 37698 bytes
//
#define TR_LATIN1_START_STATE (0)
#define TR_LATIN1_ACCEPTING_STATES_START (97)
extern const unsigned char tr_latin1_itt[256];
extern const unsigned short tr_latin1_stt[97][193];

// utf/tr_utf8_ascii.txt
//
// 2424 code points.
// 95 states, 193 columns, 18591 bytes
//
#define TR_ASCII_START_STATE (0)
#define TR_ASCII_ACCEPTING_STATES_START (95)
extern const unsigned char tr_ascii_itt[256];
extern const unsigned char tr_ascii_stt[95][193];

// utf/tr_tolower.txt
//
// 1023 code points.
// 46 states, 86 columns, 4212 bytes
//
#define TR_TOLOWER_START_STATE (0)
#define TR_TOLOWER_ACCEPTING_STATES_START (46)
extern const unsigned char tr_tolower_itt[256];
extern const unsigned char tr_tolower_stt[46][86];

#define TR_TOLOWER_DEFAULT (0)
#define TR_TOLOWER_LITERAL_START (1)
#define TR_TOLOWER_XOR_START (13)
extern const string_desc tr_tolower_ott[97];

// utf/tr_toupper.txt
//
// 1030 code points.
// 48 states, 90 columns, 4576 bytes
//
#define TR_TOUPPER_START_STATE (0)
#define TR_TOUPPER_ACCEPTING_STATES_START (48)
extern const unsigned char tr_toupper_itt[256];
extern const unsigned char tr_toupper_stt[48][90];

#define TR_TOUPPER_DEFAULT (0)
#define TR_TOUPPER_LITERAL_START (1)
#define TR_TOUPPER_XOR_START (11)
extern const string_desc tr_toupper_ott[102];

// utf/tr_totitle.txt
//
// 1034 code points.
// 48 states, 90 columns, 4576 bytes
//
#define TR_TOTITLE_START_STATE (0)
#define TR_TOTITLE_ACCEPTING_STATES_START (48)
extern const unsigned char tr_totitle_itt[256];
extern const unsigned char tr_totitle_stt[48][90];

#define TR_TOTITLE_DEFAULT (0)
#define TR_TOTITLE_LITERAL_START (1)
#define TR_TOTITLE_XOR_START (11)
extern const string_desc tr_totitle_ott[100];

// utf/tr_Color.txt
//
// 517 code points.
// 5 states, 13 columns, 321 bytes
//
#define TR_COLOR_START_STATE (0)
#define TR_COLOR_ACCEPTING_STATES_START (5)
extern const unsigned char tr_color_itt[256];
extern const unsigned char tr_color_stt[5][13];

//
// End of Unicode Table Definitions.

// utf/cl_Printable.txt
//
inline bool mux_isprint(const unsigned char *p)
{
    int iState = CL_PRINT_START_STATE;
    do
    {
        unsigned char ch = *p++;
        iState = cl_print_stt[iState][cl_print_itt[(unsigned char)ch]];
    } while (iState < CL_PRINT_ACCEPTING_STATES_START);
    return ((iState - CL_PRINT_ACCEPTING_STATES_START) == 1) ? true : false;
}

// utf/cl_AttrNameInitial.txt
//
inline bool mux_isattrnameinitial(const unsigned char *p)
{
    int iState = CL_ATTRNAMEINITIAL_START_STATE;
    do
    {
        unsigned char ch = *p++;
        iState = cl_attrnameinitial_stt[iState][cl_attrnameinitial_itt[(unsigned char)ch]];
    } while (iState < CL_ATTRNAMEINITIAL_ACCEPTING_STATES_START);
    return ((iState - CL_ATTRNAMEINITIAL_ACCEPTING_STATES_START) == 1) ? true : false;
}

// utf/cl_AttrName.txt
//
inline bool mux_isattrname(const unsigned char *p)
{
    int iState = CL_ATTRNAME_START_STATE;
    do
    {
        unsigned char ch = *p++;
        iState = cl_attrname_stt[iState][cl_attrname_itt[(unsigned char)ch]];
    } while (iState < CL_ATTRNAME_ACCEPTING_STATES_START);
    return ((iState - CL_ATTRNAME_ACCEPTING_STATES_START) == 1) ? true : false;
}

// utf/cl_Objectname.txt
//
inline bool mux_isobjectname(const unsigned char *p)
{
    int iState = CL_OBJECTNAME_START_STATE;
    do
    {
        unsigned char ch = *p++;
        iState = cl_objectname_stt[iState][cl_objectname_itt[(unsigned char)ch]];
    } while (iState < CL_OBJECTNAME_ACCEPTING_STATES_START);
    return ((iState - CL_OBJECTNAME_ACCEPTING_STATES_START) == 1) ? true : false;
}

// utf/cl_PlayerName.txt
//
inline bool mux_isplayername(const unsigned char *p)
{
    int iState = CL_PLAYERNAME_START_STATE;
    do
    {
        unsigned char ch = *p++;
        iState = cl_playername_stt[iState][cl_playername_itt[(unsigned char)ch]];
    } while (iState < CL_PLAYERNAME_ACCEPTING_STATES_START);
    return ((iState - CL_PLAYERNAME_ACCEPTING_STATES_START) == 1) ? true : false;
}

// utf/cl_8859_1.txt
//
inline bool mux_is8859_1(const unsigned char *p)
{
    int iState = CL_8859_1_START_STATE;
    do
    {
        unsigned char ch = *p++;
        iState = cl_8859_1_stt[iState][cl_8859_1_itt[(unsigned char)ch]];
    } while (iState < CL_8859_1_ACCEPTING_STATES_START);
    return ((iState - CL_8859_1_ACCEPTING_STATES_START) == 1) ? true : false;
}

// utf/cl_8859_2.txt
//
inline bool mux_is8859_2(const unsigned char *p)
{
    int iState = CL_8859_2_START_STATE;
    do
    {
        unsigned char ch = *p++;
        iState = cl_8859_2_stt[iState][cl_8859_2_itt[(unsigned char)ch]];
    } while (iState < CL_8859_2_ACCEPTING_STATES_START);
    return ((iState - CL_8859_2_ACCEPTING_STATES_START) == 1) ? true : false;
}

// utf/tr_utf8_latin1.txt
//
const char *ConvertToLatin(const UTF8 *pString);

// utf/tr_utf8_ascii.txt
//
const char *ConvertToAscii(const UTF8 *pString);

// utf/tr_tolower.txt
//
inline const string_desc *mux_tolower(const unsigned char *p, bool &bXor)
{
    int iState = TR_TOLOWER_START_STATE;
    do
    {
        unsigned char ch = *p++;
        iState = tr_tolower_stt[iState][tr_tolower_itt[(unsigned char)ch]];
    } while (iState < TR_TOLOWER_ACCEPTING_STATES_START);

    if (TR_TOLOWER_DEFAULT == iState - TR_TOLOWER_ACCEPTING_STATES_START)
    {
        bXor = false;
        return NULL;
    }
    else
    {
        bXor = (TR_TOLOWER_XOR_START <= iState - TR_TOLOWER_ACCEPTING_STATES_START);
        return tr_tolower_ott + iState - TR_TOLOWER_ACCEPTING_STATES_START - 1;
    }
}

// utf/tr_toupper.txt
//
inline const string_desc *mux_toupper(const unsigned char *p, bool &bXor)
{
    int iState = TR_TOUPPER_START_STATE;
    do
    {
        unsigned char ch = *p++;
        iState = tr_toupper_stt[iState][tr_toupper_itt[(unsigned char)ch]];
    } while (iState < TR_TOUPPER_ACCEPTING_STATES_START);

    if (TR_TOUPPER_DEFAULT == iState - TR_TOUPPER_ACCEPTING_STATES_START)
    {
        bXor = false;
        return NULL;
    }
    else
    {
        bXor = (TR_TOUPPER_XOR_START <= iState - TR_TOUPPER_ACCEPTING_STATES_START);
        return tr_toupper_ott + iState - TR_TOUPPER_ACCEPTING_STATES_START - 1;
    }
}

// utf/tr_totitle.txt
//
inline const string_desc *mux_totitle(const unsigned char *p, bool &bXor)
{
    int iState = TR_TOTITLE_START_STATE;
    do
    {
        unsigned char ch = *p++;
        iState = tr_totitle_stt[iState][tr_totitle_itt[(unsigned char)ch]];
    } while (iState < TR_TOTITLE_ACCEPTING_STATES_START);

    if (TR_TOTITLE_DEFAULT == iState - TR_TOTITLE_ACCEPTING_STATES_START)
    {
        bXor = false;
        return NULL;
    }
    else
    {
        bXor = (TR_TOTITLE_XOR_START <= iState - TR_TOTITLE_ACCEPTING_STATES_START);
        return tr_totitle_ott + iState - TR_TOTITLE_ACCEPTING_STATES_START - 1;
    }
}

// utf/tr_Color.txt
//
inline int mux_color(const unsigned char *p)
{
    int iState = TR_COLOR_START_STATE;
    do
    {
        unsigned char ch = *p++;
        iState = tr_color_stt[iState][tr_color_itt[(unsigned char)ch]];
    } while (iState < TR_COLOR_ACCEPTING_STATES_START);
    return iState - TR_COLOR_ACCEPTING_STATES_START;
}

#define COLOR_NOTCOLOR   0
#define COLOR_RESET      "\xEF\x94\x80"    // 1
#define COLOR_INTENSE    "\xEF\x94\x81"    // 2
#define COLOR_UNDERLINE  "\xEF\x94\x84"    // 3
#define COLOR_BLINK      "\xEF\x94\x85"    // 4
#define COLOR_INVERSE    "\xEF\x94\x87"    // 5
#define COLOR_FG_BLACK   "\xEF\x98\x80"    // 6
#define COLOR_FG_RED     "\xEF\x98\x81"    // 7
#define COLOR_FG_GREEN   "\xEF\x98\x82"    // 8
#define COLOR_FG_YELLOW  "\xEF\x98\x83"    // 9
#define COLOR_FG_BLUE    "\xEF\x98\x84"    // 10
#define COLOR_FG_MAGENTA "\xEF\x98\x85"    // 11
#define COLOR_FG_CYAN    "\xEF\x98\x86"    // 12
#define COLOR_FG_WHITE   "\xEF\x98\x87"    // 13
#define COLOR_BG_BLACK   "\xEF\x9C\x80"    // 14
#define COLOR_BG_RED     "\xEF\x9C\x81"    // 15
#define COLOR_BG_GREEN   "\xEF\x9C\x82"    // 16
#define COLOR_BG_YELLOW  "\xEF\x9C\x83"    // 17
#define COLOR_BG_BLUE    "\xEF\x9C\x84"    // 18
#define COLOR_BG_MAGENTA "\xEF\x9C\x85"    // 19
#define COLOR_BG_CYAN    "\xEF\x9C\x86"    // 20
#define COLOR_BG_WHITE   "\xEF\x9C\x87"    // 21
#define COLOR_LAST_CODE  21

#define mux_haswidth(x) mux_isprint(x)

bool utf8_strlen(const UTF8 *pString, size_t &nString);

typedef struct
{
    UTF8 *pString;
    UTF8 aControl[256];
} MUX_STRTOK_STATE;

void mux_strtok_src(MUX_STRTOK_STATE *tts, UTF8 *pString);
void mux_strtok_ctl(MUX_STRTOK_STATE *tts, const UTF8 *pControl);
UTF8 *mux_strtok_parseLEN(MUX_STRTOK_STATE *tts, size_t *pnLen);
UTF8 *mux_strtok_parse(MUX_STRTOK_STATE *tts);

size_t mux_ltoa(long val, UTF8 *buf);
UTF8 *mux_ltoa_t(long val);
void safe_ltoa(long val, UTF8 *buff, UTF8 **bufc);
size_t mux_i64toa(INT64 val, UTF8 *buf);
UTF8 *mux_i64toa_t(INT64 val);
void safe_i64toa(INT64 val, UTF8 *buff, UTF8 **bufc);
long mux_atol(const UTF8 *pString);
INT64 mux_atoi64(const UTF8 *pString);
double mux_atof(const UTF8 *szString, bool bStrict = true);
UTF8 *mux_ftoa(double r, bool bRounded, int frac);

bool is_integer(const UTF8 *str, int *pDigits = NULL);
bool is_rational(const UTF8 *str);
bool is_real(const UTF8 *str);

// Color State
//
typedef UINT16 ColorState;

#define COLOR_INDEX_RESET       1
#define COLOR_INDEX_INTENSE     2
#define COLOR_INDEX_UNDERLINE   3
#define COLOR_INDEX_BLINK       4
#define COLOR_INDEX_INVERSE     5

#define COLOR_INDEX_ATTR        2
#define COLOR_INDEX_FG          6
#define COLOR_INDEX_BG          14

#define COLOR_INDEX_BLACK       0
#define COLOR_INDEX_RED         1
#define COLOR_INDEX_GREEN       2
#define COLOR_INDEX_YELLOW      3
#define COLOR_INDEX_BLUE        4
#define COLOR_INDEX_MAGENTA     5
#define COLOR_INDEX_CYAN        6
#define COLOR_INDEX_WHITE       7
#define COLOR_INDEX_DEFAULT     8

#define COLOR_INDEX_FG_WHITE    (COLOR_INDEX_FG + COLOR_INDEX_WHITE)

typedef struct
{
    ColorState  cs;
    ColorState  csMask;
    const char *pAnsi;
    size_t      nAnsi;
    const UTF8 *pUTF;
    size_t      nUTF;
    const UTF8 *pEscape;
    size_t      nEscape;
} MUX_COLOR_SET;

extern const MUX_COLOR_SET aColors[];

UTF8 *convert_color(const UTF8 *pString, bool bNoBleed);
UTF8 *strip_color(const UTF8 *pString, size_t *pnLength = 0, size_t *pnPoints = 0);
UTF8 *munge_space(const UTF8 *);
UTF8 *trim_spaces(const UTF8 *);
UTF8 *grabto(UTF8 **, UTF8);
int  string_compare(const UTF8 *, const UTF8 *);
int  string_prefix(const UTF8 *, const UTF8 *);
const UTF8 * string_match(const UTF8 * ,const UTF8 *);
UTF8 *replace_string(const UTF8 *, const UTF8 *, const UTF8 *);
UTF8 *replace_tokens
(
    const UTF8 *s,
    const UTF8 *pBound,
    const UTF8 *pListPlace,
    const UTF8 *pSwitch
);
#if 0
char *BufferCloneLen(const UTF8 *pBuffer, unsigned int nBuffer);
#endif // 0
bool minmatch(const UTF8 *str, const UTF8 *target, int min);
UTF8 *StringCloneLen(const UTF8 *str, size_t nStr);
UTF8 *StringClone(const UTF8 *str);
void safe_copy_str(const UTF8 *src, UTF8 *buff, UTF8 **bufp, size_t nSizeOfBuffer);
void safe_copy_str_lbuf(const UTF8 *src, UTF8 *buff, UTF8 **bufp);
size_t safe_copy_buf(const UTF8 *src, size_t nLen, UTF8 *buff, UTF8 **bufp);
size_t safe_fill(UTF8 *buff, UTF8 **bufc, UTF8 chFile, size_t nSpaces);
void safe_chr_utf8(const UTF8 *src, UTF8 *buff, UTF8 **bufp);
#define utf8_safe_chr safe_chr_utf8
UTF8 *ConvertToUTF8(UTF32 ch);
UTF8 *ConvertToUTF8(const char *p, size_t *pn);
UTF16 *ConvertToUTF16(UTF32 ch);
UTF32 ConvertFromUTF8(const UTF8 *p);
size_t ConvertFromUTF16(UTF16 *pString, UTF32 &ch);
UTF16 *ConvertFromUTF8ToUTF16(const UTF8 *pString, size_t *pnString);
UTF8  *ConvertFromUTF16ToUTF8(const UTF16 *pSTring);
void mux_strncpy(UTF8 *dest, const UTF8 *src, size_t nSizeOfBuffer);
bool matches_exit_from_list(UTF8 *, const UTF8 *);
UTF8 *translate_string(const UTF8 *, bool);
int mux_stricmp(const UTF8 *a, const UTF8 *b);
int mux_memicmp(const void *p1_arg, const void *p2_arg, size_t n);
UTF8 *mux_strlwr(const UTF8 *a, size_t &n);
UTF8 *mux_strupr(const UTF8 *a, size_t &n);

typedef struct tag_itl
{
    bool bFirst;
    char chPrefix;
    char chSep;
    UTF8 *buff;
    UTF8 **bufc;
    size_t nBufferAvailable;
} ITL;

void ItemToList_Init(ITL *pContext, UTF8 *arg_buff, UTF8 **arg_bufc,
    UTF8 arg_chPrefix = 0, UTF8 arg_chSep = ' ');
bool ItemToList_AddInteger(ITL *pContext, int i);
bool ItemToList_AddInteger64(ITL *pContext, INT64 i);
bool ItemToList_AddString(ITL *pContext, const UTF8 *pStr);
bool ItemToList_AddStringLEN(ITL *pContext, size_t nStr, const UTF8 *pStr);
void ItemToList_Final(ITL *pContext);

size_t DCL_CDECL mux_vsnprintf(UTF8 *buff, size_t count, const char *fmt, va_list va);
void DCL_CDECL mux_sprintf(UTF8 *buff, size_t count, const char *fmt, ...);
size_t GetLineTrunc(UTF8 *Buffer, size_t nBuffer, FILE *fp);

typedef struct
{
    size_t m_d[256];
    size_t m_skip2;
} BMH_State;

extern void BMH_Prepare(BMH_State *bmhs, size_t nPat, const UTF8 *pPat);
extern bool BMH_Execute(BMH_State *bmhs, size_t *pnMatched, size_t nPat, const UTF8 *pPat, size_t nSrc, const UTF8 *pSrc);
extern bool BMH_StringSearch(size_t *pnMatched, size_t nPat, const UTF8 *pPat, size_t nSrc, const UTF8 *pSrc);
extern void BMH_PrepareI(BMH_State *bmhs, size_t nPat, const UTF8 *pPat);
extern bool BMH_ExecuteI(BMH_State *bmhs, size_t *pnMatched, size_t nPat, const UTF8 *pPat, size_t nSrc, const UTF8 *pSrc);
extern bool BMH_StringSearchI(size_t *pnMatched, size_t nPat, const UTF8 *pPat, size_t nSrc, const UTF8 *pSrc);

struct ArtRuleset
{
    ArtRuleset* m_pNextRule;

    void* m_pRegexp;
    void *m_pRegexpStudy;
    int m_bUseAn;
};

typedef struct
{
    int         iLeadingSign;
    int         iString;
    const UTF8  *pDigitsA;
    size_t      nDigitsA;
    const UTF8  *pDigitsB;
    size_t      nDigitsB;
    int         iExponentSign;
    const UTF8  *pDigitsC;
    size_t      nDigitsC;
    const UTF8  *pMeat;
    size_t      nMeat;

} PARSE_FLOAT_RESULT;

extern bool ParseFloat(PARSE_FLOAT_RESULT *pfr, const UTF8 *str, bool bStrict = true);

class mux_field
{
public:
    LBUF_OFFSET m_byte;
    LBUF_OFFSET m_column;

    inline mux_field(size_t byte = 0, size_t column = 0)
    {
        m_byte = static_cast<LBUF_OFFSET>(byte);
        m_column = static_cast<LBUF_OFFSET>(column);
    };

    inline void operator =(const mux_field &c)
    {
        m_byte = c.m_byte;
        m_column = c.m_column;
    };

    inline void operator ()(size_t byte, size_t column)
    {
        m_byte = static_cast<LBUF_OFFSET>(byte);
        m_column = static_cast<LBUF_OFFSET>(column);
    };

    inline bool operator <(const mux_field &a) const
    {
        return (  m_byte < a.m_byte
               && m_column < a.m_column);
    };

    inline bool operator <=(const mux_field &a) const
    {
        return (  m_byte <= a.m_byte
               && m_column <= a.m_column);
    };

    inline bool operator ==(const mux_field &a) const
    {
        return (m_byte == a.m_byte) && (m_column == a.m_column);
    };

    inline bool operator !=(const mux_field &a) const
    {
        return (m_byte != a.m_byte) || (m_column != a.m_column);
    };

    inline mux_field operator -(const mux_field &a) const
    {
        mux_field b;
        if (  a.m_byte  < m_byte
           && a.m_column < m_column)
        {
            b.m_byte  = m_byte  - a.m_byte;
            b.m_column = m_column - a.m_column;
        }
        else
        {
            b.m_byte  = 0;
            b.m_column = 0;
        }
        return b;
    };

    inline mux_field operator +(const mux_field &a) const
    {
        mux_field b;
        b.m_byte  = m_byte  + a.m_byte;
        b.m_column = m_column + a.m_column;
        return b;
    };

    inline void operator +=(const mux_field &a)
    {
        m_byte  = m_byte + a.m_byte;
        m_column = m_column + a.m_column;
    };

    inline void operator -=(const mux_field &a)
    {
        if (  a.m_byte  < m_byte
           && a.m_column < m_column)
        {
            m_byte  = m_byte - a.m_byte;
            m_column = m_column - a.m_column;
        }
        else
        {
            m_byte  = 0;
            m_column = 0;
        }
    };
};

// mux_string cursors are used for iterators internally.  They should not be
// used externally, as the external view is always that an index refers to a
// code point.
//
class mux_cursor
{
public:
    LBUF_OFFSET m_byte;
    LBUF_OFFSET m_point;

    inline mux_cursor(size_t byte = 0, size_t point = 0)
    {
        m_byte = static_cast<LBUF_OFFSET>(byte);
        m_point = static_cast<LBUF_OFFSET>(point);
    };

    inline void operator =(const mux_cursor &c)
    {
        m_byte = c.m_byte;
        m_point = c.m_point;
    };

    inline void operator ()(size_t byte, size_t point)
    {
        m_byte = static_cast<LBUF_OFFSET>(byte);
        m_point = static_cast<LBUF_OFFSET>(point);
    };

    inline bool operator <(const mux_cursor &a) const
    {
        return (  m_byte < a.m_byte
               && m_point < a.m_point);
    };

    inline bool operator <=(const mux_cursor &a) const
    {
        return (  m_byte <= a.m_byte
               && m_point <= a.m_point);
    };

    inline bool operator ==(const mux_cursor &a) const
    {
        return (m_byte == a.m_byte) && (m_point == a.m_point);
    };

    inline bool operator !=(const mux_cursor &a) const
    {
        return (m_byte != a.m_byte) || (m_point != a.m_point);
    };

    inline mux_cursor operator -(const mux_cursor &a) const
    {
        mux_cursor b;
        if (  a.m_byte  < m_byte
           && a.m_point < m_point)
        {
            b.m_byte  = m_byte  - a.m_byte;
            b.m_point = m_point - a.m_point;
        }
        else
        {
            b.m_byte  = 0;
            b.m_point = 0;
        }
        return b;
    };

    inline mux_cursor operator +(const mux_cursor &a) const
    {
        mux_cursor b;
        b.m_byte  = m_byte  + a.m_byte;
        b.m_point = m_point + a.m_point;
        return b;
    };

    inline void operator +=(const mux_cursor &a)
    {
        m_byte  = m_byte + a.m_byte;
        m_point = m_point + a.m_point;
    };

    inline void operator -=(const mux_cursor &a)
    {
        if (  a.m_byte  < m_byte
           && a.m_point < m_point)
        {
            m_byte  = m_byte - a.m_byte;
            m_point = m_point - a.m_point;
        }
        else
        {
            m_byte  = 0;
            m_point = 0;
        }
    };
};

static const mux_field fldAscii(1, 1);
static const mux_field fldMin(0, 0);

bool utf8_strlen(const UTF8 *pString, mux_cursor &nString);
mux_field StripTabsAndTruncate(const UTF8 *pString, UTF8 *pBuffer,
    size_t nLength, size_t nWidth);
mux_field PadField(UTF8 *pBuffer, size_t nMaxBytes, LBUF_OFFSET nMinWidth,
                   mux_field fldOutput = fldMin);

size_t TruncateToBuffer(const UTF8 *pString, UTF8 *pBuffer, size_t nBuffer);

static const mux_cursor CursorMin(0,0);
static const mux_cursor CursorMax(LBUF_SIZE - 1, LBUF_SIZE - 1);

static const mux_cursor curAscii(1, 1);

class mux_string
{
    // m_nutf, m_ncs, m_autf, m_ncs, and m_pcs work together as follows:
    //
    // m_nutf is always between 0 and LBUF_SIZE-1 inclusively.  The first
    // m_nutf bytes of m_atuf[] contain the non-color UTF-8-encoded code
    // points.  A terminating '\0' at m_autf[m_nutf] is not included in this
    // size even though '\0' is a UTF-8 code point.  In this way, m_nutf
    // corresponds to strlen() in units of bytes.  The use of both a length
    // and a terminating '\0' is intentionally redundant.
    //
    // m_ncp is between 0 and LBUF_SIZE-1 inclusively and represents the
    // number of non-color UTF-8-encoded code points stored in m_autf[].
    // The terminating '\0' is not included in this size.  In this way, m_ncp
    // corresponds to strlen() in units of code points.
    //
    // If color is associated with the above code points, m_pcs will point
    // to an array of ColorStates, otherwise, it is NULL.  When m_pcs is NULL,
    // it is equivalent to every code point having CS_NORMAL color.  Each
    // color state corresponds with a UTF-8 code point in m_autf[].  There is
    // no guaranteed association between a position in m_autf[] and a position
    // in m_pcs because UTF-8 code points are variable length.
    //
    // Not all ColorStates in m_pcs may be used. m_ncs is between 0 and
    // LBUF_SIZE-1 inclusively and represents how many ColorStates are
    // allocated and available for use.  m_ncp is always less than or equal to
    // m_ncs.
    //
    // To recap, m_nutf has units of bytes while m_ncp and m_ncs are in units
    // of code points.
    //
private:
    mux_cursor  m_iLast;
    UTF8        m_autf[LBUF_SIZE];
    size_t      m_ncs;
    ColorState *m_pcs;
    void realloc_m_pcs(size_t ncs);

public:
    mux_string(void);
    mux_string(const mux_string &sStr);
    mux_string(const UTF8 *pStr);
    ~mux_string(void);

    void Validate(void) const;

    inline bool isAscii(void)
    {
        // If every byte corresponds to a point, then all the bytes must be ASCII.
        //
        return (m_iLast.m_byte == m_iLast.m_point);
    }

    void append(dbref num);
    void append(INT64 iInt);
    void append(long lLong);
    void append
    (
        const mux_string &sStr,
        mux_cursor nStart = CursorMin,
        mux_cursor iEnd   = CursorMax
    );
    void append(const UTF8 *pStr);
    void append(const UTF8 *pStr, size_t nLen);
    void append_TextPlain(const UTF8 *pStr);
    void append_TextPlain(const UTF8 *pStr, size_t nLen);
    void compress(const UTF8 *ch);
    void compress_Spaces(void);
    void delete_Chars(mux_cursor iStart, mux_cursor iEnd);
    void edit(mux_string &sFrom, const mux_string &sTo);
    UTF8 export_Char(size_t n) const;
    LBUF_OFFSET export_Char_UTF8(size_t iFirst, UTF8 *pBuffer) const;
    ColorState export_Color(size_t n) const;
    double export_Float(bool bStrict = true) const;
    INT64 export_I64(void) const;
    long export_Long(void) const;
    LBUF_OFFSET export_TextColor
    (
        UTF8 *pBuffer,
        mux_cursor iStart = CursorMin,
        mux_cursor iEnd   = CursorMax,
        size_t nBytesMax = (LBUF_SIZE-1)
    ) const;
    UTF8 *export_TextConverted
    (
        bool bColor   = true,
        bool bNoBleed = false
    ) const;
    LBUF_OFFSET export_TextPlain
    (
        UTF8 *pBuffer,
        mux_cursor iStart = CursorMin,
        mux_cursor iEnd   = CursorMax,
        size_t nBytesMax = (LBUF_SIZE-1)
    ) const;
    void import(dbref num);
    void import(INT64 iInt);
    void import(long lLong);
    void import(const mux_string &sStr, mux_cursor iStart = CursorMin);
    void import(const UTF8 *pStr);
    void import(const UTF8 *pStr, size_t nLen);

    inline mux_cursor length_cursor(void) const
    {
        return m_iLast;
    }

    inline size_t length_byte(void) const
    {
        return m_iLast.m_byte;
    }

    inline size_t length_point(void) const
    {
        return m_iLast.m_point;
    }

    void prepend(dbref num);
    void prepend(INT64 iInt);
    void prepend(long lLong);
    void prepend(const mux_string &sStr);
    void prepend(const UTF8 *pStr);
    void prepend(const UTF8 *pStr, size_t nLen);
    void replace_Chars(const mux_string &pTo, mux_cursor iStart, mux_cursor nLen);
    bool replace_Point(const UTF8 *p, mux_cursor &i);
    void reverse(void);
    bool search
    (
        const UTF8 *pPattern,
        mux_cursor *iPos = NULL,
        mux_cursor iStart = CursorMin,
        mux_cursor iEnd = CursorMax
    ) const;
    bool search
    (
        const mux_string &sPattern,
        mux_cursor *iPos = NULL,
        mux_cursor iStart = CursorMin,
        mux_cursor iEnd = CursorMax
    ) const;
    void set_Char(size_t n, const UTF8 cChar);
    void set_Color(size_t n, ColorState csColor);
    void strip
    (
        const UTF8 *pStripSet,
        mux_cursor iStart = CursorMin,
        mux_cursor iEnd = CursorMax
    );
    void stripWithTable
    (
        const bool strip_table[UCHAR_MAX+1],
        mux_cursor iStart = CursorMin,
        mux_cursor iEnd = CursorMax
    );
    void transform
    (
        mux_string &sFromSet,
        mux_string &sToSet,
        size_t nStart = 0,
        size_t nLen = (LBUF_SIZE-1)
    );
    void transform_Ascii
    (
        const UTF8 asciiTable[SCHAR_MAX+1],
        size_t nStart = 0,
        size_t nLen = (LBUF_SIZE-1)
    );
    void trim(const UTF8 ch = ' ', bool bLeft = true, bool bRight = true);
    void trim(const UTF8 *p, bool bLeft = true, bool bRight = true);
    void trim(const UTF8 *p, size_t n, bool bLeft = true, bool bRight = true);
    void truncate(mux_cursor iEnd);

    static void * operator new(size_t size)
    {
        mux_assert(size == sizeof(mux_string));
        return alloc_string("new");
    }

    static void operator delete(void *p)
    {
        if (NULL != p)
        {
            free_string(p);
        }
    }

    void UpperCase(void);
    void LowerCase(void);
    void UpperCaseFirst(void);

    // mux_string_cursor c;
    // cursor_start(c);
    // while (cursor_next(c))
    // {
    // }
    //
    inline bool cursor_start(mux_cursor &c) const
    {
        c.m_byte  = 0;
        c.m_point = 0;
        return (0 != m_iLast.m_point);
    }

    inline bool cursor_next(mux_cursor &c) const
    {
        if ('\0' != m_autf[c.m_byte])
        {
#ifdef NEW_MUX_STRING_PARANOID
            size_t n = utf8_FirstByte[m_autf[c.m_byte]];
            mux_assert(n < UTF8_CONTINUE);
            while (n--)
            {
                c.m_byte++;
                mux_assert(UTF8_CONTINUE == utf8_FirstByte[m_autf[c.m_byte]]);
            }
            mux_assert(0 <= c.m_point && c.m_point < m_ncp);
#else
            c.m_byte = (LBUF_OFFSET)(c.m_byte + utf8_FirstByte[m_autf[c.m_byte]]);
#endif // NEW_MUX_STRING_PARANOID
            c.m_point++;
            return true;
        }
        return false;
    };

    // mux_cursor c;
    // cursor_end(c);
    // while (cursor_prev(c))
    // {
    // }
    //
    inline void cursor_end(mux_cursor &c) const
    {
        c = m_iLast;
    }

    inline bool cursor_prev(mux_cursor &c) const
    {
        if (0 < c.m_byte)
        {
#ifdef NEW_MUX_STRING_PARANOID
            size_t n = 1;
            while (UTF8_CONTINUE == utf8_FirstByte[m_autf[c.m_byte - n]])
            {
                n++;
                mux_assert(0 < c.m_byte - n);
            }
            mux_assert(utf8_FirstByte[m_autf[c.m_byte - n]] < UTF8_CONTINUE);
            c.m_byte -= n;
            mux_assert(0 < c.m_byte && c.m_byte <= m_ncp);
#else
            c.m_byte--;
            while (  0 < c.m_byte
                  && UTF8_CONTINUE == utf8_FirstByte[m_autf[c.m_byte]])
            {
                c.m_byte--;
            }
#endif // NEW_MUX_STRING_PARANOID
            c.m_point--;
            return true;
        }
        return false;
    };

    inline bool cursor_from_point(mux_cursor &c, LBUF_OFFSET iPoint) const
    {
        if (iPoint <= m_iLast.m_point)
        {
            if (m_iLast.m_point == m_iLast.m_byte)
            {
                // Special case of ASCII.
                //
                c.m_byte  = iPoint;
                c.m_point = iPoint;
            }
            else if (iPoint < m_iLast.m_point/2)
            {
                // Start from the beginning.
                //
                cursor_start(c);
                while (  c.m_point < iPoint
                      && cursor_next(c))
                {
                    ; // Nothing.
                }
            }
            else
            {
                // Start from the end.
                //
                cursor_end(c);
                while (  iPoint < c.m_point
                      && cursor_prev(c))
                {
                    ; // Nothing.
                }
            }
            return true;
        }
        cursor_end(c);
        return false;
    }

    inline bool cursor_from_byte(mux_cursor &c, LBUF_OFFSET iByte) const
    {
        if (iByte <= m_iLast.m_byte)
        {
            if (m_iLast.m_point == m_iLast.m_byte)
            {
                // Special case of ASCII.
                //
                c.m_byte  = iByte;
                c.m_point = iByte;
            }
            else if (iByte < m_iLast.m_byte/2)
            {
                // Start from the beginning.
                //
                cursor_start(c);
                while (  c.m_byte < iByte
                      && cursor_next(c))
                {
                    ; // Nothing.
                }
            }
            else
            {
                // Start from the end.
                //
                cursor_end(c);
                while (  iByte < c.m_byte
                      && cursor_prev(c))
                {
                    ; // Nothing.
                }
            }
            return true;
        }
        return false;
    }

    inline bool IsEscape(mux_cursor &c)
    {
        return mux_isescape(m_autf[c.m_byte]);
    }

    friend class mux_words;
};

inline bool isEmpty(const mux_string *p)
{
    return ((NULL == p) || (0 == p->length_byte()));
}

// String buffers are LBUF_SIZE, so maximum string length is LBUF_SIZE-1.
// That means the longest possible list can consist of LBUF_SIZE-1 copies
// of the delimiter, making for LBUF_SIZE words in the list.
//
#define MAX_WORDS LBUF_SIZE

class mux_words
{
private:
    bool        m_aControl[UCHAR_MAX+1];
    LBUF_OFFSET m_nWords;
    mux_cursor m_aiWordBegins[MAX_WORDS];
    mux_cursor m_aiWordEnds[MAX_WORDS];
    const mux_string *m_s;

public:

    mux_words(const mux_string &sStr);
    void export_WordColor(LBUF_OFFSET n, UTF8 *buff, UTF8 **bufc = NULL);
    LBUF_OFFSET find_Words(void);
    LBUF_OFFSET find_Words(const UTF8 *pDelim);
    void ignore_Word(LBUF_OFFSET n);
    void set_Control(const UTF8 *pControlSet);
    void set_Control(const bool table[UCHAR_MAX+1]);
    mux_cursor wordBegin(LBUF_OFFSET n) const;
    mux_cursor wordEnd(LBUF_OFFSET n) const;
};

#endif // STRINGUTIL_H
