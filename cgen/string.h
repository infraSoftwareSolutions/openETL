#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cgen/micros/structure.h"

#ifndef METACORE___CGEN___STRING_H
#define METACORE___CGEN___STRING_H

    #define cstrptr char * 

    #define cstr(name, sizeValue) \
        char name[sizeValue]

    static inline size_t length(const char * value) { return (value != NULL) ? strlen(value) : 0; }

    static inline bool equal(const char * value_1, const char * value_2)
    {
        if (value_1 == NULL || value_2 == NULL)
        return false;
        return strcmp(value_1, value_2) == 0 ? true : false;
    }

    static inline cstrptr concatenate(char* value_1, const char * value_2)
    {
        if (value_1 == NULL || value_2 == NULL)
        return value_1;
        return strcat(value_1, value_2);
    }

    static inline bool is_empty(const char * value) { return (value == NULL || strlen(value) == 0) ? true : false; }

    /**
     * @brief Clear string content by reallocating to empty string
     * @param value The string to clear
     * @return Pointer to cleared string or NULL if input is NULL
     * @note Properly handles memory reallocation for empty string
     */
    static void *cstr_empty(char* value)
    {
        if (value == NULL)
        return NULL;
        
        // Free old memory and allocate fresh 1 byte for empty string
        cstrptr temp = (char*) malloc(1);
        if (temp != NULL) {
        temp[0] = '\0';
        free(value);
        return temp;
        }
        return NULL;
    }

    /**
     * @brief Free allocated string memory
     * @param value The string to free
     * @note Safely handles NULL pointers, frees any non-NULL string regardless of content
     */
    static void cstr_free(char* value)
    {
        if (value == NULL)
        {
        printf("Warning: attempting to free NULL pointer.\n");
        return;
        }
        free(value);
    }

    static bool exist(const char * value, char c)
    {
        if (value == NULL || is_empty(value))
        {
        printf("bad input: input string is empty.\n");
        return false;
        }
        for (size_t i = 0, e = length(value); i < e; i++)
        {
        if (value[i] == c)
            return true;
        }
        return false;
    }

    /**
     * @brief Check if substring exists in string
     * @param value_1 The main string to search in
     * @param value_2 The substring to search for
     * @return true if substring is found, false otherwise
     * @note Uses standard strstr for reliable substring search with proper pattern handling
     */
    static bool sub_exist(const char * value_1, const char * value_2)
    {
        if (value_1 == NULL || value_2 == NULL || is_empty(value_1) || is_empty(value_2))
        {
        printf("bad input: one of the input strings is empty.\n");
        return false;
        }
        
        // Use standard strstr function for reliable substring search
        // This properly handles overlapping patterns and multiple occurrences
        return strstr(value_1, value_2) != NULL ? true : false;
    }

    static size_t count(const char * value, char c)
    {
        if (value == NULL || is_empty(value))
        {
        printf("bad input: input string is empty.");
        return (size_t)0;
        }
        size_t result = 0;
        for (size_t i = 0, e = length(value); i < e; i++)
        {
        if (value[i] == c)
            result++;
        }
        return result;
    }

static inline size_t length(const char * _str_)
{
    size_t len = 0;
    while (_str_[len] != '\0')
    {
        len++;
    }
    return len;
}

static inline size_t find(const char * _str_, char ch)
{
    size_t index = 0;
    while (_str_[index] != '\0')
    {
        if (_str_[index] == ch)
        {
            return index;
        }
        index++;
    }
    return -1; // Not found
}

static inline bool compare(const char * _str_1, const char * _str_2)
{
    size_t index = 0;
    while (_str_1[index] != '\0' && _str_2[index] != '\0')
    {
        if (_str_1[index] != _str_2[index])
        {
            return false;
        }
        index++;
    }
    return _str_1[index] == '\0' && _str_2[index] == '\0'; // Both should end at the same time
}

static inline void copy(char* destination, const char * source)
{
    size_t index = 0;
    while (source[index] != '\0')
    {
        destination[index] = source[index];
        index++;
    }
    destination[index] = '\0'; // Null-terminate the destination _str_ing
}

static inline size_t count_char(const char * _str_, char ch)
{
    size_t count = 0;
    size_t index = 0;
    while (_str_[index] != '\0')
    {
        if (_str_[index] == ch)
        {
            count++;
        }
        index++;
    }
    return count;
}

static size_t count_substr(const char * _str_, const char * sub_str_)
{
    size_t count = 0;
    size_t index = 0;
    size_t sub_str__len = length(sub_str_);
    while (_str_[index] != '\0')
    {
        if (compare(_str_ + index, sub_str_))
        {
            count++;
            index += sub_str__len; // Move past the found sub_str_ing
        }
        else
        {
            index++;
        }
    }
    return count;
}

static int *locations(const char * _str_, char ch, size_t out_count)
{
    size_t char_count = count_char(_str_, ch);
    int *indices = (int *)malloc(char_count * sizeof(int));
    size_t index = 0;
    size_t found_index = 0;
    while (_str_[index] != '\0')
    {
        if (_str_[index] == ch)
        {
            indices[found_index++] = index;
        }
        index++;
    }
    out_count = char_count;
    return indices;
}


cobject
{
    cstrptr data;
    size_t length;
    size_t capacity;
}
cstring;

/**
 * @brief Initialize a cstring object.
 *
 * Allocates an initial buffer of 16 bytes, sets the length to zero and
 * ensures the string is null-terminated.  The caller must eventually
 * call cstring_free() to release the allocated memory.
 *
 * @param str Pointer to the cstring structure to initialize.
 */
void cstring_init(cstring *_str)
{
    _str->capacity = 16;
    _str->length = 0;
    _str->data = (char* )malloc(_str->capacity);
    _str->data[0] = '\0';
}

/**
 * @brief Append a C‑style string to a cstring.
 *
 * Ensures there is enough capacity (doubling when necessary), then
 * copies the contents of @p src to the end of @p dest and updates the
 * length field.  The destination must have been initialized.
 *
 * @param dest Pointer to the target cstring.
 * @param src  Null‑terminated source string to append.
 */
static inline void cstring_append(cstring *dest, const char * src)
{
    size_t src_len = strlen(src);

    if (dest->length + src_len + 1 > dest->capacity)
    {
        dest->capacity = (dest->length + src_len + 1) * 2;
        dest->data = (char* )realloc(dest->data, dest->capacity);
    }

    strcpy(dest->data + dest->length, src);
    dest->length += src_len;
}

/**
 * @brief Release memory held by a cstring.
 *
 * Frees the heap buffer associated with the string.  After this call the
 * cstring is no longer valid unless re‑initialized by cstring_init().
 *
 * @param str Pointer to the cstring to free.
 */
static inline void cstring_free(cstring *_str)
{
    free(_str->data);
}

/**
 * @brief Assign a raw C string to a cstring (by value).
 *
 * This function operates on a *copy* of the destination structure, so it
 * has no effect on the caller's object.  It simply illustrates intended
 * semantics; consider using a pointer or returning the updated struct
 * instead.
 *
 * @param destination Copy of the destination cstring structure.
 * @param source      Null‑terminated C string to assign.
 */
static inline void set(cstring destination, char* source)
{
    destination.data = source;
    destination.length = strlen(destination.data);
}

/**
 * @brief Assign one cstring to another (by value).
 *
 * Like the other overload, this modifies only the local copy of
 * @p destination.  It does not copy the character data.
 *
 * @param destination Copy of the destination cstring.
 * @param source      Source cstring to copy from.
 */
static inline void set(cstring destination, cstring source)
{
    destination.data = source.data;
    destination.length = source.length;
}

/**
 * @brief Change the length of a cstring (on a copy).
 *
 * Adjusts the capacity if necessary and updates the length field.  The
 * passed structure is modified by value, so the caller's string is
 * unaffected.  After increasing the length the contents beyond the old
 * length are undefined except for the terminating null.
 *
 * @param str     cstring structure to resize (copied).
 * @param NLength New desired length (not including terminating null).
 */
static inline void resize(cstring _str, size_t NLength)
{
    if (NLength + 1 > _str.capacity)
    {
        _str.capacity = (NLength + 1) * 2;
        _str.data = (char* )realloc(_str.data, _str.capacity);
    }
    _str.length = NLength;
    _str.data[NLength] = '\0';
}

/**
 * @brief Copy cstring contents into a C buffer.
 *
 * The destination buffer must be large enough to hold the string plus
 * terminating null.
 *
 * @param destination Buffer where data will be stored.
 * @param source      Source cstring to copy from.
 */
static inline void copy(char* destination, cstring source) { strcpy(destination, source.data); }

/**
 * @brief Return the length of a cstring.
 *
 * @param source cstring whose length is queried.
 * @return Number of characters in the string (excluding null).
 */
static inline size_t length(cstring source) { return source.length; }

/**
 * @brief Create a lowercase copy of a cstring.
 *
 * Allocates a new buffer and returns a cstring whose characters are the
 * lowercase equivalents of those in @p source.  The caller must free the
 * returned string's data when finished.
 *
 * @param source Input string to convert.
 * @return New cstring containing lowercase text.
 */
static cstring lower(cstring source)
{
    cstring result;
    result.data = (char* )malloc(source.length + 1);
    strcpy(result.data, source.data);
    result.length = source.length;
    result.capacity = source.capacity;
    for (size_t i = 0; i < result.length; i++) {
        result.data[i] = tolower(result.data[i]);
    }
    return result;
}

/**
 * @brief Create an uppercase copy of a cstring.
 *
 * Similar to lower(), but converts characters to uppercase.
 *
 * @param source Input string to convert.
 * @return New cstring containing uppercase text.
 */
static cstring upper(cstring source)
{
    cstring result;
    result.data = (char* )malloc(source.length + 1);
    strcpy(result.data, source.data);
    result.length = source.length;
    result.capacity = source.capacity;
    for (size_t i = 0; i < result.length; i++) {
        result.data[i] = toupper(result.data[i]);
    }
    return result;
}

/**
 * @brief Concatenate two cstrings and return a new one.
 *
 * Allocates a fresh cstring containing the contents of @p destination
 * followed by @p source.  The original arguments are not modified.
 *
 * @param destination First operand.
 * @param source      Second operand to append.
 * @return Newly allocated cstring with combined text.
 */
static cstring append_cstring(cstring destination, cstring source)
{
    cstring result;
    result.data = (char* )malloc(destination.length + source.length + 1);
        if(destination.capacity <= destination.length + source.length) {
        result.capacity = destination.capacity + source.length + source.length / 2;
    } else {
        result.capacity = destination.capacity;
    }
    strcpy(result.data, destination.data);
    strcat(result.data, source.data);
    result.length = strlen(result.data);
    return result;
}

/**
 * @brief Append a C string to a cstring, returning a new object.
 *
 * Similar to the previous overload but takes a raw C string as second
 * argument.
 *
 * @param destination Base string.
 * @param source      Null‑terminated C string to append.
 * @return New cstring containing the concatenation.
 */
static cstring append_string(cstring destination, char* source)
{
    cstring result;
    result.data = (char* )malloc(destination.length + strlen(source) + 1);
    if(destination.capacity <= destination.length + strlen(source)) {
        result.capacity = destination.capacity + strlen(source) + strlen(source) / 2;
    } else {
        result.capacity = destination.capacity;
    }
    strcpy(result.data, destination.data);
    strcat(result.data, source);
    result.length = strlen(result.data);
    return result;
}

/**
 * @brief Append a single character to a cstring, returning a new one.
 *
 * Allocates space for the extra character and null terminator.  The
 * original string is left unchanged.
 *
 * @param destination Original string.
 * @param source      Character to append.
 * @return New cstring containing the result.
 */
static cstring append_char(cstring destination, char source)
{
    cstring result;
    result.data = (char* )malloc(destination.length + 2);
    strcpy(result.data, destination.data);
    result.capacity = destination.capacity + 2;
    result.data[destination.length] = source;
    result.data[destination.length + 1] = '\0';
    result.length = strlen(result.data);
    return result;
}

/**
 * @brief Determine if a character exists in the string.
 *
 * @param source The string to search.
 * @param target Character to look for.
 * @return true if @p target appears anywhere, false otherwise.
 */
static inline bool search(cstring source, char target)
{
    for (size_t i = 0; i < source.length; i++)
    {
        if (source.data[i] == target)
            return true;
    }
    return false;
}

/**
 * @brief Search for a C string inside the cstring.
 *
 * @param source The string to scan.
 * @param target Null‑terminated substring to find.
 * @return true if @p target is found, false otherwise.
 */
static inline bool search(cstring source, char* target)
{
    return strstr(source.data, target) != NULL;
}

/**
 * @brief Search for another cstring within this one.
 *
 * @param source Source string to examine.
 * @param target cstring to search for.
 * @return true if @p target is a substring of @p source.
 */
static inline bool search(cstring source, cstring target)
{
    return strstr(source.data, target.data) != NULL;
}

/**
 * @brief Split a cstring into tokens on a delimiter.
 *
 * The function uses strtok() on a writable copy of the data and returns
 * an array of freshly initialized cstrings.  The caller is responsible for
 * freeing each element and the array itself.
 *
 * @param source    The string to split; its contents are modified.
 * @param delimiter Character used as separator (default is space).
 * @param count     If non‑NULL, receives the number of tokens produced.
 * @return Pointer to dynamically allocated array of cstring tokens.
 */
static cstring *split(cstring source, char delimiter, size_t *count)
{
    size_t capacity = 4;
    size_t length = 0;
    cstring *result = (cstring *)malloc(capacity * sizeof(cstring));

    cstrptr token = strtok(source.data, delimiter);
    while (token != NULL)
    {
        if (length >= capacity)
        {
            capacity *= 2;
            result = (cstring *)realloc(result, capacity * sizeof(cstring));
        }
        cstring_init(&result[length]);
        cstring_append(&result[length], token);
        length++;
        token = strtok(NULL, delimiter);
    }
    *count = length;
    return result;
}

/**
 * @brief Extract a substring from a cstring.
 *
 * Allocates a new cstring containing @p length characters starting at
 * position @p start from @p source.  No bounds checking is performed.
 *
 * @param source The original string.
 * @param start  Zero‑based start index.
 * @param length Number of characters to include.
 * @return New cstring with the requested slice.
 */
static cstring substring(cstring source, size_t start, size_t length)
{
    cstring result;
    result.data = (char*)malloc(length + 1);
    strncpy(result.data, source.data + start, length);
    result.data[length] = '\0';
    result.length = length;
    result.capacity = source.capacity;
    return result;
}

/**
 * @brief Return a new cstring containing the reverse of the input.
 *
 * The returned string is freshly allocated; the original is unchanged.
 *
 * @param source String to reverse.
 * @return Reversed copy of @p source.
 */
static cstring reverse(cstring source)
{
    cstring result;
    result.data = (char*)malloc(source.length + 1);
    for (size_t i = 0; i < source.length; i++)
        result.data[i] = source.data[source.length - 1 - i];
    result.data[source.length] = '\0';
    result.length = source.length;
    result.capacity = source.capacity;
    return result;
}

// Insert Begning and End

/**
 * @brief Insert a substring at an arbitrary position.
 *
 * The function shifts the tail of @p source to make room for
 * @p substring.  If @p position is larger than the current length it is
 * treated as an append.  Capacity is grown if necessary.
 *
 * @param source    Pointer to the string to modify.
 * @param substring Null‑terminated substring to insert.
 * @param position  Insertion index (0 = beginning).
 */
static void insertBE(cstring *source, char* substring, size_t position)
{
    if (position > source->length)
        position = source->length;

    size_t substring_len = strlen(substring);
    size_t new_length = source->length + substring_len;

    if (new_length + 1 > source->capacity)
    {
        source->capacity = (new_length + 1) * 2;
        source->data = (char* )realloc(source->data, source->capacity);
    }

    memmove(source->data + position + substring_len, source->data + position, source->length - position + 1);
    memcpy(source->data + position, substring, substring_len);
    source->length = new_length;
}

/**
 * @brief Insert a substring at the beginning of a cstring.
 *
 * Convenience wrapper around insertBE() with position set to 0.
 *
 * @param source    Pointer to the string to modify.
 * @param substring Null‑terminated substring to insert.
 */
static inline void insertB(cstring *source, char* substring)
{
    insertBE(source, substring, 0);
}

// Insert End

/**
 * @brief Append a substring to the end of a cstring.
 *
 * Convenience wrapper around insertBE() with position equal to the
 * current string length, effectively performing an append.
 *
 * @param source    Pointer to the string to modify.
 * @param substring Null‑terminated substring to insert.
 */
static inline void insertE(cstring *source, char* substring)
{
    insertBE(source, substring, source->length);
}

static inline size_t where(cstring _str, char ch)
{
    for (size_t index = 0; index < _str.length; index++)
    {
        if (_str.data[index] == ch)
        {
            return index;
        }
    }
    return -1; // Not found
}

static inline bool exist(cstring _str, char ch)
{
    for (size_t index = 0; index < _str.length; index++)
    {
        if (_str.data[index] == ch)
        {
            return true;
        }
    }
    return false; // Not found
}

static inline bool exist(cstring _str, char* substr)
{
    return strstr(_str.data, substr) != NULL;
}

static inline bool exist(cstring _str, cstring substr)
{
    return strstr(_str.data, substr.data) != NULL;
}

#endif // METACORE___CGEN___STRING_H